#include "game.h"


Game::Game(ChessBoard* chessboard, QObject *parent) : QObject(parent), chessboard(chessboard), isPawnPromotion(false)
{
    whiteTimer.setHMS(0, 5, 0);
    blackTimer.setHMS(0, 5, 0);
    chessboard->initialBoard();
    currentPlayer = ChessPiece::White;
    QObject::connect(&whiteTimerUpdateTimer, &QTimer::timeout, this, &Game::updateWhiteTimer);
    QObject::connect(&blackTimerUpdateTimer, &QTimer::timeout, this, &Game::updateBlackTimer);
    QObject::connect(chessboard, &ChessBoard::pawnPromotionSignal, this, &Game::pawnPromotionHandler);

}

// Add slots to update the timers
void Game::updateWhiteTimer()
{
    if (currentPlayer == ChessPiece::Color::White && whiteTimer > QTime(0, 0)) {
        whiteTimer = whiteTimer.addSecs(-1);
        emit whiteTimerUpdated(whiteTimer);
    }
}

void Game::updateBlackTimer()
{
    if (currentPlayer == ChessPiece::Color::Black && blackTimer > QTime(0, 0)) {
        blackTimer = blackTimer.addSecs(-1);
        emit blackTimerUpdated(blackTimer);
    }
}

void Game::pawnPromotionHandler(int fromRow, int toRow, int fromCol, int toCol)
{
    emit pawnPromotionGUI(fromRow, toRow, fromCol, toCol);
    isPawnPromotion = true;
    qDebug() << "mf reacher this";
}

void Game::makeMove(int fromRow, int fromCol, int toRow, int toCol)
{
    ChessPiece pieceToMove = chessboard->getPiece(fromRow, fromCol);

    if(!pieceToMove.isEmpty() && pieceToMove.getColor() == currentPlayer){
        // Check if the move is valid
        if(chessboard->VALIDMOVE(pieceToMove.getType(), fromRow, fromCol, toRow, toCol)){
            chessboard->movePiece(fromRow, fromCol, toRow, toCol);
            // Switches the turn
            if(!isPawnPromotion)
                currentPlayer = (currentPlayer == ChessPiece::Color::White) ? ChessPiece::Color::Black : ChessPiece::Color::White;

            // Starts the timer only when the first move is made
            blackTimerUpdateTimer.start(1000);
            whiteTimerUpdateTimer.start(1000);

            if(currentPlayer == ChessPiece::Color::White){
                qDebug() << "white timer: " << whiteTimer;
                blackTimerUpdateTimer.start(1000);

            }else{
                qDebug() << "black timer: " << blackTimer;
                whiteTimerUpdateTimer.start(1000);

            }
        }
    }
    isPawnPromotion = false;
}

ChessPiece::Color Game::getCurrentPlayer() const
{
    return currentPlayer;
}

QTime Game::getWhiteTimer() const
{
    return whiteTimer;
}

QTime Game::getBlackTimer() const
{
    return blackTimer;
}
