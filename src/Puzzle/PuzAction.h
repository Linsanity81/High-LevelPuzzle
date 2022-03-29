///////////////////////////////////////////////////////////////
//
// PuzAction.h
//
//   Piece Disassembly Action Class
//
// by Peng SONG ( peng_song@sutd.edu.sg )
// 
// 22/Aug/2021
//
///////////////////////////////////////////////////////////////

#ifndef _PUZ_ACTION_H
#define _PUZ_ACTION_H

#include "Utility/HelpPuz.h"


class PuzAction
{
public:
	int diassOrder;            // Disassembly sequence order
	bool isMoveAction;         // Is MoveAction or RemoveAction

	vector<int> movePieceIDs;  // The pieceIDs in the movable group
	Vector3i moveVector;       // Moving axis + moving steps for MoveAction

	vector<int> remvPieceIDs;  // Removable pieceID
	vector<int> remvAxisIDs;   // Possible removing axes for RemoveAction


public:
	PuzAction();
	~PuzAction();
	PuzAction & operator=(const PuzAction &puzAction);
	void PrintPuzAction();

	/// PuzAction Operations
    void GetPieceGroupMoveVector(Vector3i volumeSize, Vector3f voxelSize, vector<int> &actualMovePieceIDs, Vector3f &actualMoveVector);
	void WritePuzAction(FILE *fp, Vector3f voxelSize, Vector3i volumeSize);
};

#endif