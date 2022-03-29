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


#include "Cube.h"
#include "Face.h"


//**************************************************************************************//
//                                   Initialization
//**************************************************************************************//

Cube::Cube()
{
	cubeCenter = Vector3f(0, 0, 0);
	cubeSize   = 1.0;
	tolerance  = 0.1;

	origFaceList = new Face[6];
	currFaceList = new Face[6];
	
	edgeList = new Edge[12];
    drawEdgeList.resize(12);
}

Cube::~Cube()
{
	delete [] origFaceList;
	delete [] currFaceList;
	delete [] edgeList;
}


void Cube::InitCube(float _tolerance, float _cubeSize, Vector3f _cubeCenter)
{
	tolerance  = _tolerance;
	cubeSize   = _cubeSize;
	cubeCenter = _cubeCenter;
    drawEdgeList.resize(12);
}




//**************************************************************************************//
//                                   Cube Faces
//**************************************************************************************//

void Cube::ComputeFaces()
{
	// Initialize each face
	origFaceList[0].InitFace(0, tolerance, cubeSize, Vector3f(0,        0,        0       ), Vector3f(0,        cubeSize, cubeSize));
	origFaceList[1].InitFace(1, tolerance, cubeSize, Vector3f(cubeSize, 0,        0       ), Vector3f(cubeSize, cubeSize, cubeSize));
	origFaceList[2].InitFace(2, tolerance, cubeSize, Vector3f(0,        0,        0       ), Vector3f(cubeSize, 0,        cubeSize));
	origFaceList[3].InitFace(3, tolerance, cubeSize, Vector3f(0,        cubeSize, 0       ), Vector3f(cubeSize, cubeSize, cubeSize));
	origFaceList[4].InitFace(4, tolerance, cubeSize, Vector3f(0,        0,        0       ), Vector3f(cubeSize, cubeSize, 0       ));
	origFaceList[5].InitFace(5, tolerance, cubeSize, Vector3f(0,        0,        cubeSize), Vector3f(cubeSize, cubeSize, cubeSize));

	// Compute quads on each face  
	for (int i=0; i<6; i++)
	{
		origFaceList[i].ComputeQuads();
	}

	// Translate quads on each face
	const Vector3f cubeOffset = -Vector3f(0.5f*cubeSize, 0.5f*cubeSize, 0.5f*cubeSize);
	for (int i=0; i<6; i++)
	{
		// TODO: do I need to update these two variables
		//origFaceList[i].minPt -= cubePos;
		//origFaceList[i].maxPt -= cubePos;

		for (int j=0; j<9; j++)
		{
			origFaceList[i].quads[j].TranslateQuad( cubeOffset );
			origFaceList[i].quads[j].TranslateQuad( cubeCenter );
		}
	}

	// Initialize currFaceList
	for (int i=0; i<6; i++)
	{
		currFaceList[i] = origFaceList[i];
	}
}

void Cube::MoveFaceInside(int currFaceID)
{
	//float tempValue = tolerance - 0.01;
	float tempValue = tolerance;

	// Get the face moving vector
	Vector3f moveVec;
	if ( currFaceID == 0 )	   moveVec = Vector3f( tempValue,  0,          0        );
	if ( currFaceID == 1 )	   moveVec = Vector3f(-tempValue,  0,          0        );
	if ( currFaceID == 2 )	   moveVec = Vector3f( 0,          tempValue,  0        );
	if ( currFaceID == 3 )	   moveVec = Vector3f( 0,         -tempValue,  0        );
	if ( currFaceID == 4 )	   moveVec = Vector3f( 0,          0,          tempValue);
	if ( currFaceID == 5 )	   moveVec = Vector3f( 0,          0,         -tempValue);

	// Update 9 quads on the face
	for (int i=0; i<9; i++)
	{
		currFaceList[currFaceID].quads[i].TranslateQuad( moveVec );
	}

	// Remove 12 quads related to the face
	vector<FaceQuad> relatedQuads = GetFaceRelatedQuads( currFaceID );
	for (int i=0; i<relatedQuads.size(); i++)
	{
		int faceID = relatedQuads[i].faceID;
		int quadID = relatedQuads[i].quadID;
		currFaceList[faceID].quads[quadID].isKeep = false;
	}
}

vector<FaceQuad> Cube::GetFaceRelatedQuads( int faceID )
{
	int faceQuadIDs[72][2] = { 
	{2, 0}, {2, 1}, {2, 2}, {3, 0}, {3, 1}, {3, 2}, {4, 0}, {4, 3}, {4, 6}, {5, 0}, {5, 3}, {5, 6},
	{2, 6}, {2, 7}, {2, 8}, {3, 6}, {3, 7}, {3, 8}, {4, 2}, {4, 5}, {4, 8}, {5, 2}, {5, 5}, {5, 8},
	{0, 0}, {0, 3}, {0, 6}, {1, 0}, {1, 3}, {1, 6}, {4, 0}, {4, 1}, {4, 2}, {5, 0}, {5, 1}, {5, 2},
	{0, 2}, {0, 5}, {0, 8}, {1, 2}, {1, 5}, {1, 8}, {4, 6}, {4, 7}, {4, 8}, {5, 6}, {5, 7}, {5, 8},
	{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 3}, {2, 6}, {3, 0}, {3, 3}, {3, 6},
	{0, 6}, {0, 7}, {0, 8}, {1, 6}, {1, 7}, {1, 8}, {2, 2}, {2, 5}, {2, 8}, {3, 2}, {3, 5}, {3, 8}
	};  

	vector<FaceQuad> relatedQuads;
	for (int i=0; i<12; i++)
	{
		int j = 12*faceID + i;

		FaceQuad faceQuad;
		faceQuad.faceID = faceQuadIDs[j][0];
		faceQuad.quadID = faceQuadIDs[j][1];

		relatedQuads.push_back( faceQuad );
	}

	return relatedQuads;
}




//**************************************************************************************//
//                                   Cube Edges
//**************************************************************************************//

void Cube::ComputeEdges()
{
	// X-axis aligned edges
	edgeList[0].InitEdge(  0,  Vector3f(0,        0,        0       ),  Vector3f(cubeSize, 0,        0       ) );
	edgeList[1].InitEdge(  1,  Vector3f(0,        cubeSize, 0       ),  Vector3f(cubeSize, cubeSize, 0       ) );
	edgeList[2].InitEdge(  2,  Vector3f(0,        cubeSize, cubeSize),  Vector3f(cubeSize, cubeSize, cubeSize) );
	edgeList[3].InitEdge(  3,  Vector3f(0,        0,        cubeSize),  Vector3f(cubeSize, 0,        cubeSize) );

	// Y-axis aligned edges
	edgeList[4].InitEdge(  4,  Vector3f(0,        0,        0       ),  Vector3f(0,        cubeSize, 0       ) );
	edgeList[5].InitEdge(  5,  Vector3f(0,        0,        cubeSize),  Vector3f(0,        cubeSize, cubeSize) );
	edgeList[6].InitEdge(  6,  Vector3f(cubeSize, 0,        cubeSize),  Vector3f(cubeSize, cubeSize, cubeSize) );
	edgeList[7].InitEdge(  7,  Vector3f(cubeSize, 0,        0       ),  Vector3f(cubeSize, cubeSize, 0       ) );

	// Z-axis aligned edges
	edgeList[8].InitEdge(  8,  Vector3f(0,        0,        0       ),  Vector3f(0,        0,        cubeSize) );
	edgeList[9].InitEdge(  9,  Vector3f(cubeSize, 0,        0       ),  Vector3f(cubeSize, 0,        cubeSize) );
	edgeList[10].InitEdge( 10, Vector3f(cubeSize, cubeSize, 0       ),  Vector3f(cubeSize, cubeSize, cubeSize) );
	edgeList[11].InitEdge( 11, Vector3f(0,        cubeSize, 0       ),  Vector3f(0,        cubeSize, cubeSize) );

	// Translate all the edges
	const Vector3f cubeOffset = -Vector3f(0.5f*cubeSize, 0.5f*cubeSize, 0.5f*cubeSize);
	for (int i=0; i<12; i++)
	{
		edgeList[i].TranslateEdge( cubeOffset );
		edgeList[i].TranslateEdge( cubeCenter );
	}
}

void Cube::MoveEdgeInside(int currEdgeID)
{
	//float tempValue = tolerance - 0.01;
	float tempValue = tolerance;

	Vector3f moveVecA, moveVecB;
	if ( currEdgeID == 0 )	   { moveVecA = Vector3f( 0,  tempValue,  0 );  moveVecB = Vector3f(0,  0,  tempValue); }
	if ( currEdgeID == 1 )	   { moveVecA = Vector3f( 0, -tempValue,  0 );  moveVecB = Vector3f(0,  0,  tempValue); }
	if ( currEdgeID == 2 )	   { moveVecA = Vector3f( 0, -tempValue,  0 );  moveVecB = Vector3f(0,  0, -tempValue); }
	if ( currEdgeID == 3 )	   { moveVecA = Vector3f( 0,  tempValue,  0 );  moveVecB = Vector3f(0,  0, -tempValue); }

	if ( currEdgeID == 4 )	   { moveVecA = Vector3f( tempValue,  0,  0 );  moveVecB = Vector3f(0,  0,  tempValue); }
	if ( currEdgeID == 5 )	   { moveVecA = Vector3f( tempValue,  0,  0 );  moveVecB = Vector3f(0,  0, -tempValue); }
	if ( currEdgeID == 6 )	   { moveVecA = Vector3f(-tempValue,  0,  0 );  moveVecB = Vector3f(0,  0, -tempValue); }
	if ( currEdgeID == 7 )	   { moveVecA = Vector3f(-tempValue,  0,  0 );  moveVecB = Vector3f(0,  0,  tempValue); }

	if ( currEdgeID == 8 )	   { moveVecA = Vector3f( tempValue,  0,  0 );  moveVecB = Vector3f(0,  tempValue,  0); }
	if ( currEdgeID == 9 )	   { moveVecA = Vector3f(-tempValue,  0,  0 );  moveVecB = Vector3f(0,  tempValue,  0); }
	if ( currEdgeID == 10)	   { moveVecA = Vector3f(-tempValue,  0,  0 );  moveVecB = Vector3f(0, -tempValue,  0); }
	if ( currEdgeID == 11)	   { moveVecA = Vector3f( tempValue,  0,  0 );  moveVecB = Vector3f(0, -tempValue,  0); }

	vector<FaceQuad> relatedQuads = GetEdgeRelatedQuads( currEdgeID );

	for (int i=0; i<8; i++)
	{
		int faceID = relatedQuads[i].faceID;
		int quadID = relatedQuads[i].quadID;

		if ( i < 3 )
			UpdateQuadPosition(faceID, quadID, moveVecA);
		else if ( i < 6 )
			UpdateQuadPosition(faceID, quadID, moveVecB);
		else
			currFaceList[faceID].quads[quadID].isKeep = false;
	}
}

vector<FaceQuad> Cube::GetEdgeRelatedQuads( int edgeID )
{
	int edgeQuadIDs[96][2] = { 
		{2, 0}, {2, 3}, {2, 6}, {4, 0}, {4, 1}, {4, 2}, {0, 0}, {1, 0},
		{3, 0}, {3, 3}, {3, 6}, {4, 6}, {4, 7}, {4, 8}, {0, 2}, {1, 2},
		{3, 2}, {3, 5}, {3, 8}, {5, 6}, {5, 7}, {5, 8}, {0, 8}, {1, 8},
		{2, 2}, {2, 5}, {2, 8}, {5, 0}, {5, 1}, {5, 2}, {0, 6}, {1, 6},

		{0, 0}, {0, 1}, {0, 2}, {4, 0}, {4, 3}, {4, 6}, {2, 0}, {3, 0},
		{0, 6}, {0, 7}, {0, 8}, {5, 0}, {5, 3}, {5, 6}, {2, 2}, {3, 2},
		{1, 6}, {1, 7}, {1, 8}, {5, 2}, {5, 5}, {5, 8}, {2, 8}, {3, 8},
		{1, 0}, {1, 1}, {1, 2}, {4, 2}, {4, 5}, {4, 8}, {2, 6}, {3, 6},

		{0, 0}, {0, 3}, {0, 6}, {2, 0}, {2, 1}, {2, 2}, {4, 0}, {5, 0},
		{1, 0}, {1, 3}, {1, 6}, {2, 6}, {2, 7}, {2, 8}, {4, 2}, {5, 2},
		{1, 2}, {1, 5}, {1, 8}, {3, 6}, {3, 7}, {3, 8}, {4, 8}, {5, 8},
		{0, 2}, {0, 5}, {0, 8}, {3, 0}, {3, 1}, {3, 2}, {4, 6}, {5, 6},
	};  

	vector<FaceQuad> relatedQuads;

	for (int i=0; i<8; i++)
	{
		int j = 8*edgeID + i;

		FaceQuad faceQuad;
		faceQuad.faceID = edgeQuadIDs[j][0];
		faceQuad.quadID = edgeQuadIDs[j][1];

		relatedQuads.push_back( faceQuad );
	}

	return relatedQuads;
}

void Cube::UpdateQuadPosition(int faceID, int quadID, Vector3f moveVec)
{
	currFaceList[faceID].quads[quadID].center = origFaceList[faceID].quads[quadID].center + moveVec;

	for (int i=0; i<4; i++)
	{
		currFaceList[faceID].quads[quadID].corners[i] = origFaceList[faceID].quads[quadID].corners[i] + moveVec;
	}
}




//**************************************************************************************//
//                                   Get Output Quads
//**************************************************************************************//

void Cube::TranslateCube(Vector3f moveVec)
{
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<9; j++)
		{
			origFaceList[i].quads[j].TranslateQuad( moveVec );
			currFaceList[i].quads[j].TranslateQuad( moveVec );
		}
	}

	for (int i=0; i<12; i++)
	{
		edgeList[i].TranslateEdge( moveVec );
	}
}

vector<Quad> Cube::GetOutputQuads()
{
	vector<Quad> outQuadList;

	for (int i=0; i<6; i++)
	{
		for (int j=0; j<9; j++)
		{
			if ( currFaceList[i].quads[j].isKeep )
			{
				outQuadList.push_back( currFaceList[i].quads[j] );
			}
		}
	}

	//printf("Quad Num: %d \n", outQuadList.size());
	return outQuadList;
}


void Cube::resetDrawContent()
{
    for (int i = 0; i < 12; ++i) {
        drawEdgeList[i] = edgeList[i];
    }
}