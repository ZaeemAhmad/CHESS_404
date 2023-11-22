#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>
#include <chesspiece.h>
#include <chessboard.h>

class ChessBoardWidget : public QWidget {
    Q_OBJECT
public:
    ChessBoardWidget(QWidget* parent = nullptr);
    ~ChessBoardWidget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage spritesheetImage;
    // Member variables to store the spritesheet image and each chess piece
    QPixmap whitePawnPixmap, whiteRookPixmap, whiteKnightPixmap, whiteBishopPixmap, whiteQueenPixmap, whiteKingPixmap;
    QPixmap blackPawnPixmap, blackRookPixmap, blackKnightPixmap, blackBishopPixmap, blackQueenPixmap, blackKingPixmap;
    ChessBoard* chessBoard;
    QPixmap draggedPiece;
    QPoint dragStartPosition;
    bool isDragging = false;
    int dragStartRow;
    int dragStartCol;

    void drawChessBoard(QPainter& painter);
    void drawAllChessPieces(QPainter& painter);
    void drawChessPiece(QPainter& painter, int row, int col, QColor color, const QPixmap& pixmap);
    bool isValidChessSquare(int row, int col) const;
    QPixmap getPiecePixmap(ChessPiece::Type type, ChessPiece::Color color);

};

#endif // CHESSBOARDWIDGET_H
