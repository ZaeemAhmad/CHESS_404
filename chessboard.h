#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#pragma once
#include "chesspiece.h"
#include"link_list.h"
class ChessBoard :public ChessPiece
{
public:
    ChessBoard();
    void initialBoard();
    void setPieceType(int row, int col, Type t);
    link_list white,black;
    static int onlyOnce;

    void updateLinkList(Color currentPieceColor,Color nextPieceColor,int fromRow,int fromCol,int toRow,int toCol);
    void setList();
    bool CHECK();
//temporary function for checking
    void displayLinkList();

    // Piece Movement Logic
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool isSquareOccupied(int row, int col) const;
    void removePiece(int row, int col);// Remove piece functionality is optional(not necessary).but it is efficient.
    bool VALIDMOVE(Type type, int fromRow, int fromCol, int toRow, int toCol);


    // To check if the given coordinates are between 8x8
    bool isValidChessSquare(int row, int col) const;

    // Getters
    const ChessPiece& getPiece(int row, int col) const;
    Color getPieceColor(int row, int col) const;
    Type getPieceType(int row, int col) const;

private:
    ChessPiece board[8][8];
};
//bool ChessBoard::onlyOnce=1;
#endif // CHESSBOARD_H
