///////////////////////////////////////////////////////////////
//
// PieceGroup.h
//
//   Piece Group Class
//
// by Song Peng ( song0083@ntu.edu.sg )
// 
// 21/Feb/2012
//
///////////////////////////////////////////////////////////////

#ifndef _PIECE_GROUP_H
#define _PIECE_GROUP_H

#include "Utility/HelpPuz.h"

class Voxel;
class PieceFace;
class Piece;

class PieceGroup
{
public:
	vector<Piece*> pieceList;       // Pieces in group
	vector<int> pieceIDList;        // Piece IDs in group (in the same order as pieceList)
	vector<Vector3i> piecePosList;  // Piece positions (int the same order as pieceList)

	vector<Voxel*> groupVoxelList;  // Voxels in group
	bool isConnected;               // Is all pieces are connected in group

	PieceFace *pieceFace;           // Six piece faces of group (take it as one piece even it is not connected)
	vector<int> neiborPiece;        // Neighbor piece indices of group
	vector<int> movableAxis;        // Movable axes of group

public:
	PieceGroup();
	~PieceGroup();

	// Create and Clear Piece Group
	void ClearGroup();
	void AddPiece(Piece *piece);
	void AddPiece(Piece *piece, Vector3i piecePos);
	//void AddPieceGraph(Piece *piece, Vector3i piecePos);

	// Process Piece Group
	bool CheckGroupConnectivity();
	int GetPieceIndexInGroup(int pieceID);
	void ComputeGroupFace();
	void ComputeNeighborPiece();
	void ComputeMovableAxis();

	// Piece Group Debug
	void PrintGroupInfo(bool isPrintMotion);
	void SaveGroupInfo(char fileName[]);
};

#endif