#ifndef LINK_LIST_H
#define LINK_LIST_H
#include"chesspiece.h"
#include "qdebug.h"

class Node
{
private:
    ChessPiece piece;
    Node *next;
    int row,col;
public:
    Node(ChessPiece p): piece(p), next(nullptr), row(-1), col(-1) {}
    void coordinatesSet(int r,int c)    { row=r,col=c; }
    void nextSet(Node* n)   { next=n; }

    Node* NextGet() { return next;}
    ChessPiece PieceGet() {return piece;}
    void setPiece(ChessPiece::Type t) {piece.setType(t);}
    int RowGet()    {return row;}
    int ColGet()    {return col;}
};

class link_list
{
    Node* head=nullptr;
public:

    link_list();
    void insertPiece(ChessPiece pieceFromCall, int ROW, int COL)
    {
        // Stores every piece on the board with its coordinates
        if  (head==nullptr)
        {
            head = new Node(pieceFromCall);
            head->coordinatesSet(ROW,COL);
        }
        else
        {
            Node* temp=new Node(pieceFromCall);
            temp->coordinatesSet(ROW,COL);
            Node* temp2=head;
            while (temp2->NextGet()!=nullptr) { temp2=temp2->NextGet(); }
            temp2->nextSet(temp);
        }
    }
    void deletePiece(int ROW, int COL)
    {
        if(!head)
        {
            qDebug()<<"The list is Empty DipS*it.";
            return;
        }

        if (head->RowGet()==ROW && head->ColGet()==COL)
        {
            Node* toDel = head;
            head = head->NextGet();
            delete toDel;
        }
        else{
            Node* current = head;
            while(current->NextGet()){
                if(current->RowGet()==ROW && current->ColGet()==COL){
                    Node* toDel = current->NextGet();
                    current->nextSet(toDel->NextGet());
                    delete toDel;
                }else{
                    current = current->NextGet();
                }
            }
        }
    }

void updatePiece(int currentRow, int currentCol, int updateRow, int updateCol)
    {
        Node* temp = head;
        while(temp)
        {
            if (temp->RowGet()==currentRow && temp->ColGet()==currentCol)
            {
                temp->coordinatesSet(updateRow,updateCol);
                break;
            }
            else
            {
                temp=temp->NextGet();
            }
        }
    }

void updatePieceType(int currentRow, int currentCol, ChessPiece::Type type){
    Node* temp = head;
    while(temp){
        if(temp->RowGet() == currentRow && temp->ColGet() == currentCol){
            temp->setPiece(type);
                break;
        }else{
            temp = temp->NextGet();
        }
    }
}

//    void display(int row, int col){
//        qDebug() << "display all";
//        Node* temp = head;e
//        while(temp){
//            qDebug() << temp->PieceGet().getType() << "at row & col " <<  temp->RowGet() << temp->ColGet();
//            temp = temp->NextGet();
//        }
//    }
    void display(int row,int col)
    {
        Node* temp=head;
        while (temp)
        {
            if (temp->RowGet() == row && temp->ColGet() == col)
            {
                qDebug() << "in";
                ChessPiece tempPiece=temp->PieceGet();
                ChessPiece::Color tempColor=tempPiece.getColor();
                qDebug()<<"type: "<<tempPiece.getType()<<", Color: "<<tempColor << "at row & col" << row << col;
                return;
            }
            temp = temp->NextGet();
        }
        qDebug() << "Piece not found";
    }

};

#endif // LINK_LIST_H
