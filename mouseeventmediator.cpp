#include "mouseeventmediator.h"
#include "customsetupmode.h"
#include "gamemode.h"
#include "gamescene.h"
#include "readonlymode.h"

MouseEventMediator* MouseEventMediator::instance = nullptr;
MouseEventMediator::MouseEventMediator() {}

MouseEventMediator* MouseEventMediator::getInstance() {
    if (!instance) {
        instance = new MouseEventMediator();
    }
    return instance;
}

void MouseEventMediator::updateCell(QPointF coordinates) {
    pieceMoveTo = coordinates;
}

void MouseEventMediator::updateIndex(int i) {
    indexOfLastButton = i;
}

void MouseEventMediator::updateIndexOfTakingOnPassage(int i) {
    indexOfTakingOnPassage = i;
}

void MouseEventMediator::setConnection() {
    QObject::disconnect(_scene, nullptr, nullptr, nullptr);
    QObject::disconnect(_gamemode, nullptr, nullptr, nullptr);
    QObject::disconnect(_scene->homeButton, nullptr, nullptr, nullptr);
    QObject::disconnect(_scene->giveUpButton, nullptr, nullptr, nullptr);
    QObject::disconnect(_scene->drawButton, nullptr, nullptr, nullptr);

    if (_gamemode != nullptr && _scene != nullptr) {
        QObject::connect(_scene, &GameScene::mousePressedToMove, _gamemode,
                         &GameMode::move);
        QObject::connect(_gamemode, &GameMode::startGame, _scene,
                         &GameScene::showStopButtons);
        QObject::connect(_gamemode, &GameMode::home, _scene,
                         &GameScene::hideStopButtons);
        if (_scene->homeButton) {
            QObject::connect(_scene->homeButton, &QPushButton::clicked,
                             _gamemode, [this] { emit _gamemode->home(); });
        }
        if (_scene->giveUpButton) {
            QObject::connect(_scene->giveUpButton, &QPushButton::clicked,
                             _gamemode, [this] {
                                 _gamemode->giveUp();
                                 emit _gamemode->home();
                             });
        }
        if (_scene->drawButton) {
            QObject::connect(_scene->drawButton, &QPushButton::clicked,
                             _gamemode, [this] {
                                 _gamemode->draw();
                                 emit _gamemode->home();
                             });
        }
    }
    if (dynamic_cast<CustomSetupMode*>(_gamemode) != nullptr &&
        _scene != nullptr) {
        QObject::connect(_scene, &GameScene::mousePressedToChoose,
                         dynamic_cast<CustomSetupMode*>(_gamemode),
                         &CustomSetupMode::addPiece);
    }
    if (dynamic_cast<ReadOnlyMode*>(_gamemode) != nullptr &&
        _scene != nullptr) {
        QObject::connect(dynamic_cast<ReadOnlyMode*>(_gamemode),
                         &ReadOnlyMode::startReadOnlyMode, _scene,
                         &GameScene::showReadOnlyMenu);
        QObject::connect(_gamemode, &GameMode::home, _scene,
                         &GameScene::hideReadOnlyMenu);
        QObject::connect(_scene, &GameScene::right,
                         dynamic_cast<ReadOnlyMode*>(_gamemode),
                         &ReadOnlyMode::right);
        QObject::connect(_scene, &GameScene::left,
                         dynamic_cast<ReadOnlyMode*>(_gamemode),
                         &ReadOnlyMode::left);
    }
}
