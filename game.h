// game.h
#ifndef GAME_H
#define GAME_H

#include "chessboard.h"
#include <QTime>
#include <QTimer>

class Game : public QObject
{
    Q_OBJECT
public:
    Game(ChessBoard* chessboard, QObject *parent = nullptr);

    void makeMove(int fromRow, int fromCol, int toRow, int toCol);
    ChessPiece::Color getCurrentPlayer() const;
    QTime getWhiteTimer() const;
    QTime getBlackTimer() const;

public slots:
    void updateWhiteTimer();
    void updateBlackTimer();
    void pawnPromotionHandler(int fromRow, int toRow, int fromCol, int toCol);

signals:
    // Signals indicate that something is changed
    void whiteTimerUpdated(QTime timer);
    void blackTimerUpdated(QTime timer);
    void pawnPromotionGUI(int fromRow, int toRow, int fromCol, int toCol);

private:
    ChessBoard* chessboard;
    ChessPiece::Color currentPlayer;
    QTime whiteTimer;
    QTime blackTimer;
    QTimer whiteTimerUpdateTimer;
    QTimer blackTimerUpdateTimer;
};

#endif // GAME_H
