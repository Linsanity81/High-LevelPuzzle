///////////////////////////////////////////////////////////////
//
// Piece.h
//
//   Puzzle Piece Class
//
// by Peng Song  ( peng_song@sutd.edu.sg )
// 
// 12/Jun/2021
//
///////////////////////////////////////////////////////////////

#ifndef _PIECE_H
#define _PIECE_H

#include "Utility/HelpPuz.h"
#include "PuzConfig.h"

class Voxel;
class PieceFace;
class BoundingBox;


class Piece
{
public:
	bool isPicked;             // Is puzzle piece is selected
	int pieceID;               // Puzzle piece's ID in the volume

	vector<Voxel*> voxelList;  // Voxel array of the puzzle piece
	PieceFace *pieceFace;      // Piece faces in six directions

    vector<int> neiborPiece;   // Neighbor pieceID
	vector<int> movableAxis;   // Candidates:[0,1,2,3,4,5] corresponding to direction [-x,+x,-y,+y,-z,+z]

public:
	Piece();
	~Piece();

	Piece & operator=(const Piece & piece);

	// Create Piece
	void AddVoxel(Voxel *voxel);
	//bool CheckConnectivity();
    bool CheckConnectivity();

    int ConnectivityAnalysis();

	// Piece Motion Analysis
	void ComputePieceFace();
	void ComputeNeighborPiece();
	void ComputeMovableAxis();
	void ClearPiece();
	void PrintPieceInfo();

    // Piece Drawing Data
    void CreatePieceGeometry(Vector3f puzTransVec,
                             Eigen::MatrixXf &voxelMinPts,
                             Eigen::MatrixXf &voxelMaxPts,
                             Eigen::MatrixXf &voxelCenPts,
                             Eigen::MatrixXf &cylinTopPts,
                             Eigen::MatrixXf &cylinBotPts);

    // Piece Drawing Data
    void CreatePieceGeometry(Eigen::MatrixXf &voxelMinPts,
                             Eigen::MatrixXf &voxelMaxPts,
                             Eigen::MatrixXf &voxelCenPts,
                             Eigen::MatrixXf &cylinTopPts,
                             Eigen::MatrixXf &cylinBotPts);
};

#endif