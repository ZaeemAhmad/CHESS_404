#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <chesspiece.h>
#include <chessboard.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLCDNumber>
#include "game.h"

class ChessBoardWidget : public QWidget {
    Q_OBJECT
public:
    ChessBoardWidget(QWidget* parent = nullptr);
    ~ChessBoardWidget();

    void endGame(const QString& winner);
public slots:
    // Slots are the result of a change (signal)
    void updateGUI();
    void updateWhiteTimerSlot(QTime timer);
    void updateBlackTimerSlot(QTime timer);
    void pawnPromotionDialog(int fromRow, int toRow, int fromCol, int toCol);
protected:
    // Gui based virtual functions overriden from QWidget
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void checkTimerSlot();

private:
    // Gui objects
    QImage spritesheetImage;
    QTimer playerTimer;
    QLCDNumber* whiteTimerLCD;
    QLCDNumber* blackTimerLCD;
    QHBoxLayout* timerLayout;
    // Member variables to store the spritesheet image and each chess piece
    QPixmap whitePawnPixmap, whiteRookPixmap, whiteKnightPixmap, whiteBishopPixmap, whiteQueenPixmap, whiteKingPixmap;
    QPixmap blackPawnPixmap, blackRookPixmap, blackKnightPixmap, blackBishopPixmap, blackQueenPixmap, blackKingPixmap;
    QPixmap draggedPiece;
    QPoint dragStartPosition;

    // Connection b/w Gui & Backend
    ChessBoard* chessBoard;
    Game* game;
    ChessPiece::Type currentPieceType; // Stores the Type of current Piece on the board for moving it around the board
    bool isDragging = false;
    int dragStartRow;
    int dragStartCol;

    // Private functions related to GUI
    void drawChessBoard(QPainter& painter);
    void drawAllChessPieces(QPainter& painter);
    void drawChessPiece(QPainter& painter, int row, int col, const QPixmap& pixmap);
    bool isValidChessSquare(int row, int col) const;
    QPixmap getPiecePixmap(ChessPiece::Type type, ChessPiece::Color color);

};

#endif // CHESSBOARDWIDGET_H
