#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>

class ChessBoard;

class ChessPiece
{
public:
    enum Type { King, Queen, Bishop, Knight, Rook, Pawn, Empty };
    enum Color { White, Black, NONE };

    ChessPiece(Type type = Empty, Color color = NONE);
    Type getType() const;
    Color getColor() const;
    void setType(Type t);
    bool isEmpty() const;

    // Validation functions
    bool isValidMove_Rook(Type type, int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;
    bool isValidMove_King(Type type,int fromRow, int fromCol, int toRow, int toCol, ChessBoard& board) const;
    bool isValidMove_Pawn( int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;
    void specialEnPassantMove(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;
    bool isValidMove_Knight(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;
    bool isValidMove_Bishop( int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;

    bool isValidCapture(int fromRow, int fromCol, int toRow, int toCol, const ChessBoard& board) const;
private:
    Type type;
    Color color;
};

#endif // CHESSPIECE_H
