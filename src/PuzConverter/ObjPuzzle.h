///////////////////////////////////////////////////////////////
//
// ObjPuzzle.h
//
//   OBJ Puzzle Class
//
// by Peng Song  ( peng_song@sutd.edu.sg )
//
// 16/Jun/2021
//
///////////////////////////////////////////////////////////////

#ifndef _OBJ_PUZZLE_H
#define _OBJ_PUZZLE_H

#include <vector>

class Piece;
class ObjPiece;

using namespace std;
typedef vector<ObjPiece*> ObjectList;


class ObjPuzzle
{
public:
	ObjectList objList;          // A list of ObjPiece in the Puzzle

public:
	ObjPuzzle();
	~ObjPuzzle();
	void CleanPuzzle();

	// Initialization
	void InitPuzzle(vector<Piece*> pieceList);
	void SetPiece(Piece *piece, float tolerance);
};

#endif