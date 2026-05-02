#ifndef CHESSTRANSLATOR_H
#define CHESSTRANSLATOR_H
#include <QList>
#include <QPointF>
#include <QString>
class ChessPiece;

class ChessTranslator {
   public:
    ChessTranslator();
    QString encryption(QList<ChessPiece*> allChessPieces, int cellSize = 100);
    QList<QPair<QPointF, QString>> decryption(QString code, int cellSize = 100);
};

#endif	// CHESSTRANSLATOR_H
