///////////////////////////////////////////////////////////////
//
// PuzConverter.h
//
//   Puzzle Piece to OBJ Model Conversion Class
//
// by Peng Song  ( peng_song@sutd.edu.sg )
//
// 16/Jun/2021
//
///////////////////////////////////////////////////////////////

#ifndef _PUZ_CONVERTER_H
#define _PUZ_CONVERTER_H


class Piece;
class Puzzle;
class ObjPuzzle;

class PuzConverter
{
public:
	Puzzle *puzzle;            // Input puzzle
	float tolerance;           // Range [0.0, 0.5] (w.r.t the voxel size)

	ObjPuzzle *objPuzzle;      // Output objPuzzle*

public:
	PuzConverter();
	~PuzConverter();
	void InitPuzConverter(Puzzle *_puzzle, ObjPuzzle *_objPuzzle, const float _tolerance);
	void UpdateTolerence(const float _tolerance);

	// Write the animation script file and piece OBJ models
	void ConvertPuzzle(char *puzFilePath, bool isSaveFile, bool isApplyConfig, bool isCreateGap);
	void GetPuzzleFolderPath(const char puzFilePath[], char puzFolderPath[]);
	void WritePuzzleOBJModels(char *puzFolderPath);

	// Create Puzzle Piece OBJ Models
	void CreatePuzzleOBJModels(bool isCreateGap);
	void BuildPieceOBJModel_Cube(Piece *piece, bool isCreateGap);
	int GetDiagonalVoxelPieceID(Vector3i currVoxelPos, int axisIDA, int axisIDB);
};

#endif
