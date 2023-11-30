#include "chessboardwidget.h"
#include <QPainter>

ChessBoardWidget::ChessBoardWidget(QWidget* parent) : QWidget(parent) {
    setFixedSize(700, 700);
    dragStartRow = -1;
    dragStartCol = -1;

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
    game = new Game(chessBoard);
//    chessBoard->initialBoard();
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

void ChessBoardWidget::drawChessPiece(QPainter& painter, int row, int col, const QPixmap& pixmap) {
    const int squareSize = width() / 8;

    // Enable anti-aliasing for smoother rendering
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // Use high-quality interpolation mode
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    painter.drawPixmap(col * squareSize, row * squareSize, squareSize, squareSize, pixmap);
}

void ChessBoardWidget::highlightValidMoves(int row, int col)
{

}

void ChessBoardWidget::drawAllChessPieces(QPainter& painter) {
    const int boardSize = 8;
    const int squareSize = width() / 8;

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            // Getting chess piece at the current board position
            ChessPiece piece = chessBoard->getPiece(row, col);


            // Highlight the selected piece
            if (row == dragStartRow && col == dragStartCol) {
                painter.fillRect(col * squareSize, row * squareSize, squareSize, squareSize, QColor(0, 255, 0, 128));
            }
            // Rendering board based on the piece information
            if(!piece.isEmpty()){
                drawChessPiece(painter, row, col, getPiecePixmap(piece.getType(), piece.getColor()));
            }
        }
    }
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
                currentPieceType = chessBoard->getPieceType(dragStartRow, dragStartCol);
                //           // Capture the piece to be dragged
                dragStartPosition = event->pos();
                //            qDebug() << "Start postion" << dragStartPosition;
                draggedPiece = getPiecePixmap(chessBoard->getPiece(row, col).getType(), chessBoard->getPiece(row, col).getColor());
                //            qDebug() << "Dragged Piece: " << draggedPiece;
                isDragging = true;
                chessBoard->setPieceType(dragStartRow, dragStartCol, ChessPiece::Type::Empty);
            }
        }
    }
}

void ChessBoardWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragging){
        dragStartPosition = event->pos() - QPoint(draggedPiece.width() / 2, draggedPiece.height() / 2);
        draggedPiece = draggedPiece.scaled(QSize(100, 100));

        update(); // Trigger a refresh
    }
}

void ChessBoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && isDragging){
        int col = event->pos().x() / (width() / 8);
        int row = event->pos().y() / (height() / 8);

        chessBoard->setPieceType(dragStartRow, dragStartCol, currentPieceType);

        if(isValidChessSquare(row, col)){
//            chessBoard->movePiece(dragStartRow, dragStartCol, row, col);
            game->makeMove(dragStartRow, dragStartCol, row, col);
            // Todo: Validation check
            qDebug() << "Dropped at row: " << row << " column: " << col;
        }
//        game->getPiece(dragStartRow, dragStartCol);

        isDragging = false;
        update(); // Updating the board

    }
}

bool ChessBoardWidget::isValidChessSquare(int row, int col) const
{
    return (row >= 0 && row < 8 && col >= 0 && col < 8);
}

QPixmap ChessBoardWidget::getPiecePixmap(ChessPiece::Type type, ChessPiece::Color color)
{
    // Implementation of getting piece based on type and color
    const int spriteWidth = spritesheetImage.width() / 6;
    const int spriteHeight = spritesheetImage.height() / 2;

    return QPixmap::fromImage(spritesheetImage.copy((type % 6) * spriteWidth, (color % 2) * spriteHeight, spriteWidth, spriteHeight));
}
