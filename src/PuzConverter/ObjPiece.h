///////////////////////////////////////////////////////////////
//
// ObjPiece.h
//
//   Piece OBJ Model Class
//
// by Peng Song  ( peng_song@sutd.edu.sg )
//
// 16/Jun/2021
//
///////////////////////////////////////////////////////////////

#ifndef _OBJ_PIECE_H
#define _OBJ_PIECE_H


class Quad;
class Cube;
class Piece;


class ObjPiece 
{
public:
	int cubeNum;              // Number of cubes on the piece
	Cube *cubeList;           // Cube list of the piece


public:
	ObjPiece();
	~ObjPiece();
	void InitPiece(int voxelNum);

	// Compute Piece OBJ Model
	void ComputeOBJPiece(Piece *piece, float tolerance);

	// Save Piece OBJ model
	void SavePieceOBJFile(char fileName[]);
	vector<Quad> RemoveDuplicatedQuads();
	vector<Vector3f> GetPieceVertices(vector<Quad> quadList);
	vector<vector<int>> GetPieceQuadrangles(vector<Quad> quadList, vector<Vector3f> pieceVertices);
	void SaveOBJModel(vector<Vector3f> pieceVertices, vector<vector<int>> pieceQuads, char pieceFileName[]);
	int GetQuadNumInList(Quad testQuad, vector<Quad> quadList);
	int GetVertexIndexInList(Vector3f testPoint, vector<Vector3f> vertexList);
};

#endif
