#ifndef PIECE_H
#define PIECE_H

#include <cell.h>
#include <consts.h>

enum PieceShape { ZShape, SShape, LineShape, TShape, SquareShape,
                   LShape, JShape };

class Piece
{
public:
    Piece(PieceShape shape);

    void rotateLeft();
    void rotateRight();

    void addX(int diff);
    void addY(int diff);

    int lx() { return x / BLOCK_SIZE; }
    int ly() { return y / BLOCK_SIZE; }

    int getX() { return x; }
    int getY() {return y; }

    Cell cells[4];

private:
    int x;
    int y;    
};

#endif // PIECE_H
