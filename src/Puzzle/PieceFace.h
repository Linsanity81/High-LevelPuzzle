///////////////////////////////////////////////////////////////
//
// PieceFace.h
//
//   Puzzle Piece Class
//
// by Song Peng ( song0083@ntu.edu.sg )
// 
// 06/Mar/2013
//
///////////////////////////////////////////////////////////////

#ifndef _PIECE_FACE_H
#define _PIECE_FACE_H

#include "Utility/HelpPuz.h"

///////////////////////////////////////////////////////////////
//                   3D Bounding Box Class
///////////////////////////////////////////////////////////////

class BoundingBox 
{
public:
	Vector3f minPt;  // Minimum corner point 
	Vector3f maxPt;  // Maximum corner point
	Vector3f cenPt;  // Box center point

public:
	BoundingBox()
    {
	    minPt = Vector3f(0, 0, 0);
	    maxPt = Vector3f(0, 0, 0);
	    cenPt = Vector3f(0, 0, 0);
    }

    BoundingBox & operator=(const BoundingBox & bbox)
    {
        this->minPt = bbox.minPt;
        this->maxPt = bbox.maxPt;
        this->cenPt = bbox.cenPt;

        return *this;
    }
};




///////////////////////////////////////////////////////////////
//                      Voxel Class
///////////////////////////////////////////////////////////////

class Voxel 
{
public:
	Vector3f center;    // Voxel center position
	Vector3f size;      // Voxel size
	Vector3i pos;       // Discrete position in the volume
	int state;          // Voxel [ON]/[OUT] puzzle 

	int piece;          // Piece ID
	int neiborPiece[6]; // Neighbor piece ID
	int neiborVoxel[6]; // Neighbor voxel type

	float reach;        // Reachability value
	float color;        // Color mapping value for debugging

	int dist;           // Discrete distance to specified source in BSF search
	bool visited;       // Is voxel visited in BSF search

    int type;           // Voxel type during piece construction (i.e., MainPath expansion)
    bool marked;        // Is (grid) voxel is marked for speeding up the checking of whether a specified voxel is in a given voxel list

//    vector<int> distToOutOfBBoxList;

public:
	Voxel();
	~Voxel();

	Voxel & operator=(const Voxel & voxel);

	bool IsEqual(Voxel temp);
	void PrintVoxel();
};

///////////////////////////////////////////////////////////////
//                      Piece Face Class
///////////////////////////////////////////////////////////////

class PieceFace 
{
public:
	int faceID;                        // Face/Axis ID corresponding to directions in [-x +x -y +y -z +z]

	vector<Voxel*> surfaceVoxel;       // All the voxels on this face; each voxel's neighboring voxel in faceID axis is out of the volume
	vector<Voxel*> contactVoxel;       // All the voxels on this face; each voxel's neighboring voxel in faceID axis is on the volume but not from this piece
	vector<int> contactedPiece;        // All the piece indices that have voxel(s) contacting with contactVoxel in faceID axis w.r.t this piece

public:
	PieceFace();
	~PieceFace();

	void SetPieceFaceID(int pieceFaceID );
	void PrintPieceFace();

	// Piece face voxel and contact pieces
	void AddSurfaceVoxel(Voxel *voxel);
	void AddContactVoxel(Voxel *voxel);
	void ComputeContactPiece();
	void ClearPieceFace();
};

#endif