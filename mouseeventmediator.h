#ifndef MOUSEEVENTMEDIATOR_H
#define MOUSEEVENTMEDIATOR_H
#include <QPointF>
#include <QString>

class GameMode;
class GameScene;
class CustomSetupMode;
class MouseEventMediator {
   public:
    void setGameMode(GameMode* gamemode) { _gamemode = gamemode; }
    void setScene(GameScene* scene) { _scene = scene; }
    void setResult(QString result) { _result = result; }
    void setNameOfMode(QString nameOfMode) { _nameOfMode = nameOfMode; }
    void setConnection();
    QPointF getCell() const { return pieceMoveTo; }
    QString getResult() const { return _result; }
    QString getNameOfMode() const { return _nameOfMode; }
    int getIndex() const { return indexOfLastButton; }
    int getIndexOfTakingOnPassage() const { return indexOfTakingOnPassage; }
    static MouseEventMediator* getInstance();
    void updateCell(QPointF coordinates);
    void updateIndex(int i);
    void updateIndexOfTakingOnPassage(int i);
    void clearGamemode() { _gamemode = nullptr; }

   private:
    GameMode* _gamemode = nullptr;
    GameScene* _scene = nullptr;
    static MouseEventMediator* instance;
    MouseEventMediator();
    QPointF pieceMoveTo = QPointF(-1, -1);
    QString _result;
    QString _nameOfMode;
    int indexOfLastButton = -1;
    int indexOfTakingOnPassage = -1;
};

#endif	// MOUSEEVENTMEDIATOR_H
