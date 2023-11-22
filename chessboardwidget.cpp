#include "chessboardwidget.h"
#include <QPainter>

ChessBoardWidget::ChessBoardWidget(QWidget* parent) : QWidget(parent) {
    setFixedSize(700, 700);

    // Loading the sprite image
    spritesheetImage.load(":/images/chessPieces.png");

    // Extracting individual piece
    const int pieceWidth = spritesheetImage.width() / 6;
    const int pieceHeight = spritesheetImage.height() / 2;
    qDebug() << "Piece width: " << pieceWidth << " Piece Height: " << pieceHeight;
    // Loading the pieces from the sprite image provided by us
    // ! --> Note: We are rendering the pieces based on the (row x width(200) & height)
    // It takes 200 x 200 pixel image for 1 piece and 200 x 200 for next one and so one with row & col
    whiteKingPixmap = QPixmap::fromImage(spritesheetImage.copy(0, 0, pieceWidth, pieceHeight));
    whiteQueenPixmap = QPixmap::fromImage(spritesheetImage.copy(pieceWidth, 0, pieceWidth, pieceHeight));
    whiteBishopPixmap = QPixmap::fromImage(spritesheetImage.copy(2 * pieceWidth, 0, pieceWidth, pieceHeight));
    whiteKnightPixmap = QPixmap::fromImage(spritesheetImage.copy(3 * pieceWidth, 0, pieceWidth, pieceHeight));
    whiteRookPixmap = QPixmap::fromImage(spritesheetImage.copy(4 * pieceWidth, 0, pieceWidth, pieceHeight));
    whitePawnPixmap = QPixmap::fromImage(spritesheetImage.copy(5 * pieceWidth, 0, pieceWidth, pieceHeight));

    blackKingPixmap = QPixmap::fromImage(spritesheetImage.copy(0, pieceHeight, pieceWidth, pieceHeight));
    blackQueenPixmap = QPixmap::fromImage(spritesheetImage.copy(pieceWidth, pieceHeight, pieceWidth, pieceHeight));
    blackBishopPixmap = QPixmap::fromImage(spritesheetImage.copy(2 * pieceWidth, pieceHeight, pieceWidth, pieceHeight));
    blackKnightPixmap = QPixmap::fromImage(spritesheetImage.copy(3 * pieceWidth, pieceHeight, pieceWidth, pieceHeight));
    blackRookPixmap = QPixmap::fromImage(spritesheetImage.copy(4 * pieceWidth, pieceHeight, pieceWidth, pieceHeight));
    blackPawnPixmap = QPixmap::fromImage(spritesheetImage.copy(5 * pieceWidth, pieceHeight, pieceWidth, pieceHeight));
    // _____________________ All pieces are loaded and saved into variables

    // Instance of ChessBoard class
    chessBoard = new ChessBoard();
    chessBoard->initialBoard();
}

ChessBoardWidget::~ChessBoardWidget()
{
    delete chessBoard;
}

void ChessBoardWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawChessBoard(painter);
    drawAllChessPieces(painter);

    if(isDragging){
        painter.drawPixmap(dragStartPosition, draggedPiece);
    }
}

// Code related to the board itself
void ChessBoardWidget::drawChessBoard(QPainter& painter) {
    const int boardSize = 8;
    const int squareSize = width() / boardSize;

    QBrush lightBrush(Qt::white);
    QBrush darkBrush(Qt::darkGray);

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            // Set the brush color based on the square position
            painter.fillRect(col * squareSize, row * squareSize, squareSize, squareSize,
                             (row + col) % 2 == 0 ? lightBrush : darkBrush);
        }
    }
}

void ChessBoardWidget::drawChessPiece(QPainter& painter, int row, int col, QColor color, const QPixmap& pixmap) {
    const int squareSize = width() / 8;

    // Enable anti-aliasing for smoother rendering
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // Use high-quality interpolation mode
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    painter.drawPixmap(col * squareSize, row * squareSize, squareSize, squareSize, pixmap);
}

void ChessBoardWidget::drawAllChessPieces(QPainter& painter) {
    const int boardSize = 8;
    const int squareSize = width() / boardSize;

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            // Getting chess piece at the current board position
            ChessPiece piece = chessBoard->getPiece(row, col);
//            qDebug() << "Piece at (" << row << ", " << col << "): Type=" << static_cast<int>(piece.getType()) << ", Color=" << static_cast<int>(piece.getColor());
            // Rendering board based on the piece information
            if(!piece.isEmpty()){
                drawChessPiece(painter, row, col, (piece.getColor() == ChessPiece::Color::White) ? Qt::white : Qt::black, getPiecePixmap(piece.getType(), piece.getColor()));
            }
        }
    }

    // Below is previous implementation
//    // White pieces
//    drawChessPiece(painter, 0, 0, Qt::white, whiteRookPixmap); // Rook
//    drawChessPiece(painter, 0, 1, Qt::white, whiteKnightPixmap); // Knight
//    drawChessPiece(painter, 0, 2, Qt::white, whiteBishopPixmap); // Bishop
//    drawChessPiece(painter, 0, 3, Qt::white, whiteQueenPixmap); // Queen
//    drawChessPiece(painter, 0, 4, Qt::white, whiteKingPixmap); // King
//    drawChessPiece(painter, 0, 5, Qt::white, whiteBishopPixmap); // Bishop
//    drawChessPiece(painter, 0, 6, Qt::white, whiteKnightPixmap); // Knight
//    drawChessPiece(painter, 0, 7, Qt::white, whiteRookPixmap); // Rook

//    for (int col = 0; col < boardSize; ++col) {
//        drawChessPiece(painter, 1, col, Qt::white, whitePawnPixmap); // Pawn
//    }

//    // Black pieces
//    for (int col = 0; col < boardSize; ++col) {
//        drawChessPiece(painter, 6, col, Qt::black, blackPawnPixmap); // Pawn
//    }

//    drawChessPiece(painter, 7, 0, Qt::black, blackRookPixmap); // Rook
//    drawChessPiece(painter, 7, 1, Qt::black, blackKnightPixmap); // Knight
//    drawChessPiece(painter, 7, 2, Qt::black, blackBishopPixmap); // Bishop
//    drawChessPiece(painter, 7, 3, Qt::black, blackQueenPixmap); // Queen
//    drawChessPiece(painter, 7, 4, Qt::black, blackKingPixmap); // King
//    drawChessPiece(painter, 7, 5, Qt::black, blackBishopPixmap); // Bishop
//    drawChessPiece(painter, 7, 6, Qt::black, blackKnightPixmap); // Knight
//    drawChessPiece(painter, 7, 7, Qt::black, blackRookPixmap); // Rook
}

// Implementation of drag and drop interface

void ChessBoardWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        int col = event->pos().x() / (width() / 8);
        int row = event->pos().y() / (height() / 8);

        if(isValidChessSquare(row, col)){
            ChessPiece clickedPiece = chessBoard->getPiece(row, col);

            if(!clickedPiece.isEmpty()){
            dragStartRow = row;
            dragStartCol = col;
           // Capture the piece to be dragged
            dragStartPosition = event->pos();
            qDebug() << "Start postion" << dragStartPosition;
            draggedPiece = getPiecePixmap(chessBoard->getPiece(row, col).getType(), chessBoard->getPiece(row, col).getColor());
            qDebug() << "Dragged Piece: " << draggedPiece;
            isDragging = true;
            }
        }
    }
}

void ChessBoardWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragging){
        QPoint currentPos = event->pos();
        QRect rect = draggedPiece.rect();
        rect.moveTopLeft(currentPos - dragStartPosition);

        // Ensure the piece stays within the board
        if(rect.left() < 0) rect.moveLeft(0);
        if(rect.top() < 0) rect.moveTop(0);
        if(rect.right() > width()) rect.moveRight(width());
        if(rect.bottom() > height()) rect.moveBottom(height());

        dragStartPosition = currentPos;
        update(); // Trigger a refresh
    }
}

void ChessBoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && isDragging){
        int col = event->pos().x() / (width() / 8);
        int row = event->pos().y() / (height() / 8);

        if(isValidChessSquare(row, col)){
            chessBoard->movePiece(dragStartRow, dragStartCol, row, col);
            // Todo: Validation check
            qDebug() << "Dropped at row: " << row << " column: " << col;
        }

        isDragging = false;
        update(); // Updating the board

    }
}

bool ChessBoardWidget::isValidChessSquare(int row, int col) const
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

//QPixmap ChessBoardWidget::getChessPiecePixmap(int row, int col) const
//{
//    const int spriteWidth = spritesheetImage.width() / 6;
//    const int spriteHeight = spritesheetImage.height() / 2;

//    // Use the correct sprite width and height for copying from the spritesheet
//    // width
//    qDebug() << "Row: " << row << " column: " << col;
//    return QPixmap::fromImage(spritesheetImage.copy(0, col * spriteHeight, spriteWidth, spriteHeight));
//}

QPixmap ChessBoardWidget::getPiecePixmap(ChessPiece::Type type, ChessPiece::Color color)
{
    // Implementation of getting piece based on type and color
    const int spriteWidth = spritesheetImage.width() / 6;
    const int spriteHeight = spritesheetImage.height() / 2;

    return QPixmap::fromImage(spritesheetImage.copy((static_cast<int>(type) % 6) * spriteWidth, (static_cast<int>(color) % 2) * spriteHeight, spriteWidth, spriteHeight));
}

