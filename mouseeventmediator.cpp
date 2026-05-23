#include "mouseeventmediator.h"
#include "customsetupmode.h"
#include "gamemode.h"
#include "gamescene.h"
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
    QObject::disconnect(_customSetupMode, nullptr, nullptr, nullptr);

    if (_gamemode != nullptr && _scene != nullptr) {
        QObject::connect(_scene, &GameScene::mousePressedToMove, _gamemode,
                         &GameMode::move);
        QObject::connect(_gamemode, &GameMode::startGame, _scene,
                         &GameScene::showStopButtons);
        if (_scene->homeButton) {
            QObject::connect(_scene->homeButton, &QPushButton::clicked,
                             _gamemode, [this] { emit _gamemode->home(); });
        }
    }
    if (_customSetupMode != nullptr && _scene != nullptr) {
        QObject::connect(_scene, &GameScene::mousePressedToChoose,
                         _customSetupMode, &CustomSetupMode::addPiece);
    }
}
