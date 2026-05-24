#ifndef MOUSEEVENTMEDIATOR_H
#define MOUSEEVENTMEDIATOR_H
#include <QPointF>

class GameMode;
class GameScene;
class CustomSetupMode;
class MouseEventMediator {
   public:
    void setGameMode(GameMode* gamemode) { _gamemode = gamemode; }
    void setScene(GameScene* scene) { _scene = scene; }
    void setCustom(CustomSetupMode* customSetupMode) {
        _customSetupMode = customSetupMode;
    }
    void setConnection();
    QPointF getCell() const { return pieceMoveTo; }
    int getIndex() const { return indexOfLastButton; }
    int getIndexOfTakingOnPassage() const { return indexOfTakingOnPassage; }
    static MouseEventMediator* getInstance();
    void updateCell(QPointF coordinates);
    void updateIndex(int i);
    void updateIndexOfTakingOnPassage(int i);
    void clearGamemode() {
        _gamemode = nullptr;
        _customSetupMode = nullptr;
    }

   private:
    GameMode* _gamemode = nullptr;
    GameScene* _scene = nullptr;
    CustomSetupMode* _customSetupMode = nullptr;
    static MouseEventMediator* instance;
    MouseEventMediator();
    QPointF pieceMoveTo = QPointF(-1, -1);
    int indexOfLastButton = -1;
    int indexOfTakingOnPassage = -1;
};

#endif	// MOUSEEVENTMEDIATOR_H
