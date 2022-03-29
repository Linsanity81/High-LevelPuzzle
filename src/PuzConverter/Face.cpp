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


#include "Face.h"


int quadVertices[9][4] = { {0,  4,  5, 1}, {1,  5,  6,  2}, { 2,  6,  7,  3},   // Lower  Quads
						   {4,  8,  9, 5}, {5,  9, 10,  6}, { 6, 10, 11,  7},   // Middle Quads
						   {8, 12, 13, 9}, {9, 13, 14, 10}, {10, 14, 15, 11} }; // Upper  Quads


//**************************************************************************************//
//                                    Edge Class
//**************************************************************************************//

Edge::Edge()
{

}

Edge::~Edge()
{

}

void Edge::InitEdge(int _edgeID, Vector3f _minPoint, Vector3f _maxPoint)
{
	edgeID = _edgeID;
	minPt  = _minPoint;
	maxPt  = _maxPoint;
}

void Edge::TranslateEdge(Vector3f moveVec)
{
	minPt += moveVec;
	maxPt += moveVec;
}




//**************************************************************************************//
//                                    Quad Class
//**************************************************************************************//

Quad::Quad()
{
	quadID = 0;
	isKeep = true;
}

Quad::~Quad()
{

}

Quad & Quad::operator=(const Quad & quad)
{
	if( this == &quad )
		return *this;

	this->quadID = quad.quadID;
	this->isKeep = quad.isKeep;     

	this->center = quad.center;
	for (int i=0; i<4; i++)
	{
		this->corners[i] = quad.corners[i];
	}

	return *this;
}


void Quad::InitQuad(int _quadID, bool _isKeep, Vector3f _corners[4])
{
	quadID = _quadID;
	isKeep = _isKeep;

	for (int i=0; i<4; i++)
		corners[i] = _corners[i];

	ComputeCenter();
}

void Quad::ComputeCenter()
{
	Vector3f quadCenter = Vector3f(0,0,0);
	for (int j=0; j<4; j++)
	{
		quadCenter += corners[j];
	}	

	center = 0.25f * quadCenter;
}

void Quad::ReorderCorners()
{
	// Keep a copy of original corner points
	Vector3f origCorners[4];
	for (int j=0; j<4; j++)
	{
		origCorners[j] = corners[j];
	}

	// Rearrange the corners (from CW => CCW or CCW => CW)
	corners[0] = origCorners[0];
	corners[1] = origCorners[3];
	corners[2] = origCorners[2];
	corners[3] = origCorners[1];
}

void Quad::TranslateQuad(Vector3f moveVec)
{
	center += moveVec;

	for (int i=0; i<4; i++)
	{
		corners[i] += moveVec;
	}
}




//**************************************************************************************//
//                                    Face Class
//**************************************************************************************//

///////////////////////////////////////////////////////
// Initialization
///////////////////////////////////////////////////////

Face::Face()
{
	faceID    = 0;
	tolerance = 0.1;
	cubeSize  = 1.0;
}

Face::~Face()
{

}


Face & Face::operator=(const Face & face)
{
	if( this == &face )
		return *this;

	this->faceID    = face.faceID;
	this->tolerance = face.tolerance;     
	this->cubeSize  = face.cubeSize;  

	this->minPt     = face.minPt;   
	this->maxPt     = face.maxPt;   

	for (int i=0; i<9; i++)
	{
		this->quads[i] = face.quads[i];
	}

	return *this;
}


void Face::InitFace(int _axisID, float _tolerance, float _cubeSize, Vector3f _minPt, Vector3f _maxPoint)
{
	faceID    = _axisID;
	tolerance = _tolerance;
	cubeSize  = _cubeSize;

	minPt     = _minPt;
	maxPt     = _maxPoint;
}


///////////////////////////////////////////////////////
// Compute Face
///////////////////////////////////////////////////////

void Face::ComputeQuads()
{
	vector<Vector3f> facePoints = GetFacePoints();

	// Initialize each quad on the face
	for (int i=0; i<9; i++)
	{
		// Get the corner points of each quad
		Vector3f quadCorners[4];
		for (int j=0; j<4; j++)
		{
			int index = quadVertices[i][j];
			quadCorners[j] = facePoints[index];
		}

		quads[i].InitQuad(i, true, quadCorners);
	}

	// Rearrange the points order for each quad to get correct normal
	if ( faceID == 1 || faceID == 3 || faceID == 5 )
	{
		for (int i=0; i<9; i++)
		{
			quads[i].ReorderCorners();
		}
	}
}

vector<Vector3f> Face::GetFacePoints()
{
	vector<Vector3f> facePoints;
	for (int i=0; i<16; i++)
	{
		facePoints.push_back( Vector3f(0,0,0) ) ;
	}

	// There are four kinds of distance along each direction: 
	// ( 0, tolerance, tempValue, cubeSize )
	float tempValue = cubeSize - tolerance;	

	// Face points along X-axis (4x4 = 16)
	if ( faceID == 0 || faceID == 1 )
	{
		facePoints[0]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO),              minPt(Z_INFO)             ); 
		facePoints[1]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tolerance,  minPt(Z_INFO)             ); 
		facePoints[2]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tempValue,  minPt(Z_INFO)             ); 
		facePoints[3]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + cubeSize,   minPt(Z_INFO)             ); 

		facePoints[4]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO),              minPt(Z_INFO) + tolerance ); 
		facePoints[5]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tolerance,  minPt(Z_INFO) + tolerance ); 
		facePoints[6]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tempValue,  minPt(Z_INFO) + tolerance ); 
		facePoints[7]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + cubeSize,   minPt(Z_INFO) + tolerance ); 

		facePoints[8]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO),              minPt(Z_INFO) + tempValue ); 
		facePoints[9]  = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tolerance,  minPt(Z_INFO) + tempValue ); 
		facePoints[10] = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tempValue,  minPt(Z_INFO) + tempValue ); 
		facePoints[11] = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + cubeSize,   minPt(Z_INFO) + tempValue ); 

		facePoints[12] = Vector3f( minPt(X_INFO),  minPt(Y_INFO),              minPt(Z_INFO) + cubeSize  ); 
		facePoints[13] = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tolerance,  minPt(Z_INFO) + cubeSize  ); 
		facePoints[14] = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + tempValue,  minPt(Z_INFO) + cubeSize  ); 
		facePoints[15] = Vector3f( minPt(X_INFO),  minPt(Y_INFO) + cubeSize,   minPt(Z_INFO) + cubeSize  ); 
	}

	// Face points along Y-axis (4x4 = 16)
	else if ( faceID == 2 || faceID == 3 )
	{
		facePoints[0]  = Vector3f( minPt(X_INFO),              minPt(Y_INFO),  minPt(Z_INFO)             ); 
		facePoints[1]  = Vector3f( minPt(X_INFO),              minPt(Y_INFO),  minPt(Z_INFO) + tolerance ); 
		facePoints[2]  = Vector3f( minPt(X_INFO),              minPt(Y_INFO),  minPt(Z_INFO) + tempValue ); 
		facePoints[3]  = Vector3f( minPt(X_INFO),              minPt(Y_INFO),  minPt(Z_INFO) + cubeSize  ); 

		facePoints[4]  = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO),  minPt(Z_INFO)             ); 
		facePoints[5]  = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO),  minPt(Z_INFO) + tolerance ); 
		facePoints[6]  = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO),  minPt(Z_INFO) + tempValue ); 
		facePoints[7]  = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO),  minPt(Z_INFO) + cubeSize  );

		facePoints[8]  = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO),  minPt(Z_INFO)             ); 
		facePoints[9]  = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO),  minPt(Z_INFO) + tolerance ); 
		facePoints[10] = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO),  minPt(Z_INFO) + tempValue ); 
		facePoints[11] = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO),  minPt(Z_INFO) + cubeSize  ); 

		facePoints[12] = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO),  minPt(Z_INFO)             ); 
		facePoints[13] = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO),  minPt(Z_INFO) + tolerance ); 
		facePoints[14] = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO),  minPt(Z_INFO) + tempValue ); 
		facePoints[15] = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO),  minPt(Z_INFO) + cubeSize  ); 
	}

	// Face points along Z-axis (4x4 = 16)
	else if ( faceID == 4 || faceID == 5 )
	{
		facePoints[0]  = Vector3f( minPt(X_INFO),              minPt(Y_INFO),              minPt(Z_INFO) ); 
		facePoints[1]  = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO),              minPt(Z_INFO) ); 
		facePoints[2]  = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO),              minPt(Z_INFO) ); 
		facePoints[3]  = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO),              minPt(Z_INFO) ); 

		facePoints[4]  = Vector3f( minPt(X_INFO),              minPt(Y_INFO) + tolerance,  minPt(Z_INFO) ); 
		facePoints[5]  = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO) + tolerance,  minPt(Z_INFO) ); 
		facePoints[6]  = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO) + tolerance,  minPt(Z_INFO) ); 
		facePoints[7]  = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO) + tolerance,  minPt(Z_INFO) ); 

		facePoints[8]  = Vector3f( minPt(X_INFO),              minPt(Y_INFO) + tempValue,  minPt(Z_INFO) ); 
		facePoints[9]  = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO) + tempValue,  minPt(Z_INFO) ); 
		facePoints[10] = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO) + tempValue,  minPt(Z_INFO) ); 
		facePoints[11] = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO) + tempValue,  minPt(Z_INFO) ); 

		facePoints[12] = Vector3f( minPt(X_INFO),              minPt(Y_INFO) + cubeSize,   minPt(Z_INFO) ); 
		facePoints[13] = Vector3f( minPt(X_INFO) + tolerance,  minPt(Y_INFO) + cubeSize,   minPt(Z_INFO) ); 
		facePoints[14] = Vector3f( minPt(X_INFO) + tempValue,  minPt(Y_INFO) + cubeSize,   minPt(Z_INFO) ); 
		facePoints[15] = Vector3f( minPt(X_INFO) + cubeSize,   minPt(Y_INFO) + cubeSize,   minPt(Z_INFO) ); 
	}

	return facePoints;
}