#include "chessboard.h"
#include <QDebug>

int ChessBoard::onlyOnce=0;
ChessBoard::ChessBoard(QObject* parent) : QObject(parent) {}

ChessBoard::~ChessBoard() {}

void ChessBoard::initialBoard()
{
    // Initial Board logic (Connection with gui here)
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (row == 0 || row == 7) {
                // Setup row with black and white pieces
                ChessPiece::Color color = (row == 0) ? ChessPiece::Color::Black : ChessPiece::Color::White;
                ChessPiece::Type type;

                switch (col) {
                case 0:
                case 7:
                    type = ChessPiece::Type::Rook;
                    break;
                case 1:
                case 6:
                    type = ChessPiece::Type::Knight;
                    break;
                case 2:
                case 5:
                    type = ChessPiece::Type::Bishop;
                    break;
                case 3:
                    type = ChessPiece::Type::Queen;
                    break;
                case 4:
                    type = ChessPiece::Type::King;
                    break;
                default:
                    type = ChessPiece::Type::Pawn;
                    break;
                }
                board[row][col] = ChessPiece(type, color);
                setList(board[row][col], row, col);
            }
            else if (row == 1 || row == 6) {
                // Placing pawns
                ChessPiece::Color color = (row == 1) ? ChessPiece::Color::Black : ChessPiece::Color::White;
                ChessPiece::Type type = ChessPiece::Type::Pawn;
                board[row][col] = ChessPiece(type, color);
                setList(board[row][col], row, col);
            }
            else
            {
                // Empty Squares in the middle
                ChessPiece::Type type = ChessPiece::Type::Empty;
                board[row][col] = ChessPiece(type);
            }
        }
    }
}

void ChessBoard::setPieceType(int row, int col, ChessPiece::Type type)
{
    if (isValidChessSquare(row, col)) {
        board[row][col].setType(type);
    }
}

void ChessBoard::setList(ChessPiece board, int row, int col)
{
    if ( row >= 0 && row < 2 )
    { black.insertPiece(board, row, col);
        black.display(row, col);
        qDebug() << "called" << board.getType() << row << col;
    }
    else if ( row >= 5 && row < 8)
    { white.insertPiece(board, row, col);
        white.display(row, col);
        qDebug() << "called1" << board.getType() << row << col;
    }
}

bool ChessBoard::CHECK()
{
    return true;
}
void ChessBoard::updateLinkList(Color currentPieceColor, Color nextPieceColor, int fromRow, int fromCol, int toRow, int toCol)
{
    if (nextPieceColor==NONE)
    {
        (currentPieceColor==Black)?(black.updatePiece(fromRow,fromCol,toRow,toCol)):(white.updatePiece(fromRow,fromCol,toRow,toCol));
    }
    else if (nextPieceColor==White)
    {
        white.deletePiece(toRow,toCol);
        black.updatePiece(fromRow,fromCol,toRow,toCol);
    }
    else if (nextPieceColor==Black)
    {
        black.deletePiece(toRow,toCol);
        white.updatePiece(fromRow,fromCol,toRow,toCol);
    }
}

void ChessBoard::displayLinkList()
{
    black.display(0,4);
}

void ChessBoard::removePiece(int row, int col)
{
    if (isValidChessSquare(row, col)) {
        // Set the piece at the specified position to be empty
        board[row][col] = ChessPiece();  // Assuming ChessPiece has a default constructor for an empty piece
    } else {
        qDebug() << "Invalid position for removing piece.";
    }
}

bool ChessBoard::VALIDMOVE(Type type, int fromRow, int fromCol, int toRow, int toCol)
{
    // Rook and Knight validation Jawad
    // King and Queen validation Noraiz
    // Pawn and Bishop validation Zaeem
    switch (type) {
    case Rook:
        return isValidMove_Rook(type, fromRow, fromCol, toRow, toCol, *this);
        break;
    case Knight:
        return isValidMove_Knight(fromRow, fromCol, toRow, toCol, *this);
        break;
    case Queen:
        return isValidMove_Queen(type,fromRow,fromCol,toRow,toCol,*this);
        break;
    case King:
        return isValidMove_King( type,  fromRow,fromCol,  toRow,  toCol, *this);
        break;
    case Bishop:
        return isValidMove_Bishop(fromRow,fromCol,toRow,toCol,*this);
        break;
    case Pawn:
        if(isValidMove_Pawn(fromRow,fromCol,toRow,toCol,*this)){
            if(!isPawnPromotion(fromRow, toRow, fromCol, toCol)){
                return true;
            }else{
                // Emit pawn promotion signal
                emit pawnPromotionSignal(fromRow, toRow, fromCol, toCol);
                return true;
            }
        }
        break;
    default:
        return false;
        break;
    }
}

bool ChessBoard::isPawnPromotion(int fromRow, int toRow, int fromCol, int toCol)
{
    Color color = board[fromRow][fromCol].getColor();
    if((color == Black && toRow == 7) || (color == White && toRow == 0)){
        return true;
    }
    return false;
}


void ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
    displayLinkList();
    white.displayAll();
    black.displayAll();

    // Chess Move implementation logic
    // Checking if the move is valid before upadating the board
    if ( isValidChessSquare(fromRow, fromCol) && isValidChessSquare(toRow, toCol) )
    {

        const Color currentPieceColor = getPieceColor(fromRow, fromCol);
        const Color nextPositionPieceColor = getPieceColor(toRow, toCol);
        // this condition prevents same color pieces to move upon them.
        // is condition ki waja sy same color ky pieces ek dosry ko capture nai kar skty.
        qDebug()<<"Origin: "<<fromRow<<", "<<fromCol<<"\nDestination: "<<toRow<<", "<<toCol;
        if ( currentPieceColor != nextPositionPieceColor )
        {
            if ( VALIDMOVE(getPieceType(fromRow,fromCol), fromRow, fromCol, toRow, toCol) )
            {
                updateLinkList(currentPieceColor,nextPositionPieceColor,fromRow,fromCol,toRow,toCol);
                ChessPiece pieceToMove = board[fromRow][fromCol];
                board[fromRow][fromCol] = ChessPiece(); // To clear the current square
                board[toRow][toCol] = pieceToMove; // Move the piece to the position
            }
        }
    }
    white.display(toRow, toCol);
    black.display(toRow, toCol);
}

bool ChessBoard::isSquareOccupied(int row, int col) const
{
    // Returns Truthy or Falsy based on if the current square is taken or not
    if(board[row][col].getType() != ChessPiece::Type::Empty)
        return true;
    return false;
}

bool ChessBoard::isValidChessSquare(int row, int col) const
{
    return (row>= 0 && row < 8 && col >= 0 && col < 8);
}

const ChessPiece &ChessBoard::getPiece(int row, int col) const
{
    // Returns the piece reference at current row & col
    if(isValidChessSquare(row, col)){
        return board[row][col];
    }
}

ChessPiece::Color ChessBoard::getPieceColor(int row, int col) const
{
    if(isValidChessSquare(row, col))
    {
        const ChessPiece::Color pieceColor = board[row][col].getColor();
        return pieceColor;
    }
    else
        return ChessPiece::Color::NONE;
}

ChessPiece::Type ChessBoard::getPieceType(int row, int col) const
{
    if(isValidChessSquare(row, col)){
        const ChessPiece::Type pieceType = board[row][col].getType();
        return pieceType;
    } else{
        return ChessPiece::Type::Empty;
    }
}

