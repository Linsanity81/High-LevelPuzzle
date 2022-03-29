///////////////////////////////////////////////////////////////
//
// ObjPuzzle.cpp
//
//   OBJ Puzzle Class
//
// by Peng Song  ( peng_song@sutd.edu.sg )
//
// 16/Jun/2021
//
///////////////////////////////////////////////////////////////


#include "Puzzle/Piece.h"
#include "ObjPiece.h"
#include "ObjPuzzle.h"


///=========================================================================================///
///                                   Initialization
///=========================================================================================///

ObjPuzzle::ObjPuzzle()
{

}

ObjPuzzle::~ObjPuzzle()
{
	for (int i=0; i<objList.size(); i++)
    {
        delete objList[i];
    }

	objList.clear();
}

void ObjPuzzle::CleanPuzzle()
{
	for (int i=0; i<objList.size(); i++)
	{
		delete objList[i];
	}

	objList.clear();
}




///=========================================================================================///
///                                   Init OBJ Puzzle
///=========================================================================================///

void ObjPuzzle::InitPuzzle(vector<Piece*> pieceList)
{
	CleanPuzzle();

	for (int i=0; i<pieceList.size(); i++)
	{
		ObjPiece *tempObj = new ObjPiece();
		tempObj->InitPiece( pieceList[i]->voxelList.size() );

		objList.push_back( tempObj );
	}

}

void ObjPuzzle::SetPiece(Piece *piece, float tolerance)
{
	int pieceID = piece->pieceID;
	objList[pieceID]->ComputeOBJPiece( piece, tolerance );
}
