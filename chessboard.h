#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include "chesspiece.h"
#include"link_list.h"

class ChessBoard : public QObject, public ChessPiece
{
    Q_OBJECT
public:
    ChessBoard(QObject* parent = nullptr);
    ~ChessBoard();
    void initialBoard();
    void setPieceType(int row, int col, Type t);
    void updateLinkedListPiece(int row, int col, Type t);
    link_list white, black;

    void updateLinkList(Color currentPieceColor,Color nextPieceColor,int fromRow,int fromCol,int toRow,int toCol);
    void setList(ChessPiece board, int row, int col);
    bool CHECK();
//temporary function for checking
    void displayLinkList(Color color, int row, int col);

    // Piece Movement Logic
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool isSquareOccupied(int row, int col) const;
    void removePiece(int row, int col);// Remove piece functionality is optional(not necessary).but it is efficient.
    bool VALIDMOVE(Type type, int fromRow, int fromCol, int toRow, int toCol);

    // Special Case
    bool isPawnPromotion(ChessPiece::Type type, int fromRow, int toRow, int fromCol);

    // To check if the given coordinates are between 8x8
    bool isValidChessSquare(int row, int col) const;

    // Getters
    const ChessPiece& getPiece(int row, int col) const;
    Color getPieceColor(int row, int col) const;
    Type getPieceType(int row, int col) const;

signals:
    void pawnPromotionSignal(int fromRow, int toRow, int fromCol, int toCol);
private:
    ChessPiece board[8][8];
};
//bool ChessBoard::onlyOnce=1;
#endif // CHESSBOARD_H
