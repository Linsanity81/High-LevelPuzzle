///////////////////////////////////////////////////////////////
//
// Cube.cpp
//
//   Cube with 54 Quads Class
//
// by Song Peng ( song0083@ntu.edu.sg )
// 
// 02/Jul/2013
//
///////////////////////////////////////////////////////////////

#ifndef _CUBE_H
#define _CUBE_H

#include "Utility/HelpPuz.h"

class Quad;
class Face;
class Edge;

struct FaceQuad 
{
	int faceID;   // Range [0, 5]
	int quadID;   // Range [0, 8]
};


class Cube
{
public:
	Vector3f cubeCenter;  // Cube center position
	float cubeSize;       // Cube size
	float tolerance;      // Tolerance value

	Edge *edgeList;       // All the cube edges
	Face *origFaceList;   // Original cube faces
	Face *currFaceList;   // Deformed cube faces

    vector<Edge> drawEdgeList;   // edges used to draw opengl content
    //Vector3f cubeDrawCenter;  // Cube center position to draw
    Vector3f edgeListCenter;  // Cube center computed by edgeList

public:
	Cube();
	~Cube();
	void InitCube(float _tolerance, float _cubeSize, Vector3f _cubeCenter);

	// Cube Faces
	void ComputeFaces();
	void MoveFaceInside(int currFaceID);
	vector<FaceQuad> GetFaceRelatedQuads( int faceID );

	// Cube Edges
	void ComputeEdges();
	void MoveEdgeInside(int currEdgeID);
	vector<FaceQuad> GetEdgeRelatedQuads( int edgeID );
	void UpdateQuadPosition(int faceID, int quadID, Vector3f moveVec);

	// Get Output Quads
	void TranslateCube(Vector3f moveVec);
	vector<Quad> GetOutputQuads();

	void resetDrawContent();
};

#endif