///////////////////////////////////////////////////////////////
//
// Face.cpp
//
//   Face with 9 Quads Class
//
// by Song Peng ( song0083@ntu.edu.sg )
// 
// 02/Jul/2013
//
///////////////////////////////////////////////////////////////

#ifndef _FACE_H
#define _FACE_H

#include "Utility/HelpPuz.h"


class Edge
{
public:
	int edgeID;      // Range [0, 11]

	Vector3f minPt;  // Minimum point along edge axis
	Vector3f maxPt;  // Maximum point along edge axis

public:
	Edge();
	~Edge();

	void InitEdge(int _edgeID, Vector3f _minPoint, Vector3f _maxPoint);
	void TranslateEdge(Vector3f moveVec);
};




class Quad
{
public:
	int quadID;          // Range [0, 8]
	bool isKeep;         // Should the quad be kept.

	Vector3f corners[4]; // Four corner points
	Vector3f center;     // Center point

public:
	Quad();
	~Quad();
	Quad & operator=(const Quad & quad);

	void InitQuad(int _quadID, bool _isKeep, Vector3f _corners[4]);
	void ComputeCenter();
	void ReorderCorners();
	void TranslateQuad(Vector3f moveVec);
};




class Face
{
public:
	int faceID;          // Range [0,5]; Follow face normal: [-x, +x, -y, +y, -z, +z]
	float tolerance;     // Tolerance value 
	float cubeSize;      // Cube size
 
 	Vector3f minPt;      // Minimum point on the face
	Vector3f maxPt;      // Maximum point on the face

	Quad quads[9];       // Quads on the face for generating tolerance

public:
	Face();
	~Face();
	Face & operator=(const Face & face);
	void InitFace(int _axisID, float _tolerance, float _cubeSize, Vector3f _minPoint, Vector3f _maxPoint);

	// Compute Face Quads
	void ComputeQuads();
	vector<Vector3f> GetFacePoints();

};


#endif