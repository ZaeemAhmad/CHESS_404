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
    Node(ChessPiece p):piece(p),next(nullptr)   {}
    void coordinatesSet(int r,int c)    { row=r,col=c; }
    void nextSet(Node* n)   { next=n; }

    Node* NextGet() { return next;}
    ChessPiece PieceGet() {return piece;}
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
    void deletePiece(int ROW,int COL)
    {
        if (head == nullptr)
        {
            qDebug()<<"The list is Empty DipS*it.";
            return;
        }
        else
        {
            Node* temp=head;
            while (temp!=nullptr)
            {
                if (temp->RowGet()==ROW && temp->ColGet()==COL && temp==head)
                {
                    head=head->NextGet();
                    return;
                }
                else if (temp->RowGet()==ROW && temp->ColGet()==COL)
                {
                    Node* temp2=head;
                    while (temp2->NextGet()!=temp)  { temp2=temp2->NextGet(); }
                    temp2->nextSet(temp->NextGet());
                    return;
                }
                temp=temp->NextGet();
            }
        }
    }
    void updatePiece(int currentRow, int currentCol, int updateRow, int updateCol)
    {
        Node* temp=head;
        while (temp!=nullptr)
        {
            if (temp->RowGet()==currentRow && temp->ColGet()==currentCol)
            {
                temp->coordinatesSet(updateRow,updateCol);
                return;
            }
            else
            {
                temp=temp->NextGet();
            }
        }
    }

    void display(int row,int col)
    {
        Node* temp=head;
        while (temp->RowGet()!=row && temp->ColGet()!=col)
        {
            temp=temp->NextGet();
        }
        if (temp->RowGet()==row && temp->ColGet()==col)
        {
            ChessPiece tempPiece=temp->PieceGet();
            ChessPiece::Color tempColor=tempPiece.getColor();
            qDebug()<<"type: "<<tempPiece.getType()<<", Color: "<<tempColor;
        }
    }
};

#endif // LINK_LIST_H
