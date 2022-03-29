///////////////////////////////////////////////////////////////
//
// PuzConverter.cpp
//
//   Class for Converting Puzzle Piece into OBJ Model 
//
// by Peng Song  ( peng_song@sutd.edu.sg )
//
// 16/Jun/2021
//
// Features:
// (1) Input:  A puzzle file
//     Output: OBJ files and Motion file as input of PuzzleViewer
// (2) Usage:  Create a new folder and put the puzzle inside it.
//             Read the puzzle file and click the "WriteMotion" button.
//             The outputs will be saved in the folder automatically.
//
// TODO:
//(1) Rename each puzzle piece OBJ model using its ID such as Piece_001.obj
//    rather than current name grid1_piece1.obj
//(2) Test generated OBJ models for more puzzles when the tolerance is zero
//(3) Solve the piece overlapping issue when they were disassembled
//
///////////////////////////////////////////////////////////////

#include "Utility/HelpPuz.h"
#include "Puzzle/PieceFace.h"
#include "Puzzle/Piece.h"
#include "Puzzle/Puzzle.h"
#include "Puzzle/Volume.h"
#include "Cube.h"
#include "ObjPiece.h"
#include "ObjPuzzle.h"
#include "PuzConverter.h"


extern Vector3i neiborPos[6];

// After fix the coordinate issue
int edgeNeiborFaceIDs[12][2] = {
	{2, 4}, {3, 4}, {3, 5}, {2, 5},
	{0, 4}, {0, 5}, {1, 5}, {1, 4},
	{0, 2}, {1, 2}, {1, 3}, {0, 3} };


///=========================================================================================///
///                                   Initialization
///=========================================================================================///

PuzConverter::PuzConverter()
{
	puzzle    = NULL;
	objPuzzle = NULL;
	tolerance = 0.1;
}

PuzConverter::~PuzConverter()
{

}

void PuzConverter::InitPuzConverter(Puzzle *_puzzle, ObjPuzzle *_objPuzzle, const float _tolerance)
{
	puzzle    = _puzzle;
	objPuzzle = _objPuzzle;
	tolerance = _tolerance;
}

void PuzConverter::UpdateTolerence(const float _tolerance)
{
	tolerance = _tolerance;
}




///=========================================================================================///
///                                Write Animation File
///=========================================================================================///

void PuzConverter::ConvertPuzzle(char *puzFilePath, bool isSaveFile, bool isApplyConfig, bool isCreateGap)
{
	// Don't consider empty puzzle
    if( puzzle->pieceList.size() == 0 )
	{
		printf("Warning: The puzzle is empty! \n");
		return;
	}

	// Don't consider non-buildable puzzle
	if( puzzle->puzBuildState == PUZZLE_NOT_BUILDABLE ||
		puzzle->puzBuildState == PUZZLE_BUILD_UNKNOWN )
	{
		printf("Warning: The puzzle cannot be disassembled! \n");
		return;
	}

	// Create ObjPuzzle for given Puzzle and tolerance 
	CreatePuzzleOBJModels( isCreateGap );

	// Save the piece OBJ models and animation file
	if ( isSaveFile )
	{
		WritePuzzleOBJModels( puzFilePath );

		// printf("\nGenerate animation file successfully! \n");
	}
}

void PuzConverter::GetPuzzleFolderPath(const char puzFilePath[], char puzFolderPath[])
{
	string sPuzFilePath  = string( puzFilePath );

	// Subtract Puz file folder path
	size_t foundFolder = sPuzFilePath.find_last_of("\\");
	string sPuzFolderPath = sPuzFilePath.substr( 0, foundFolder+1 );
	sprintf(puzFolderPath, "%s", sPuzFolderPath.c_str());
}

void PuzConverter::WritePuzzleOBJModels(char *puzFolderPath)
{
	int pieceNum = objPuzzle->objList.size();

	for (int i=0; i<pieceNum; i++)
	{
        char pieceFileName[512];
        sprintf(pieceFileName,"%s/piece%d.obj", puzFolderPath, i+1);
		objPuzzle->objList[i]->SavePieceOBJFile( pieceFileName );
	}
}




///=========================================================================================///
///                         Create Puzzle Piece OBJ Models
///=========================================================================================///

void PuzConverter::CreatePuzzleOBJModels(bool isCreateGap)
{
	// Build puzzle contacting graph at voxel level
    puzzle->BuildPuzzleContactGraph();

	printf("Contact graph has been built up.\n");

	// Create OBJ model of each piece with specified tolerance
	for (int i=0; i<puzzle->pieceList.size(); i++)
	{
		BuildPieceOBJModel_Cube(puzzle->pieceList[i], isCreateGap);
	}
}

void PuzConverter::BuildPieceOBJModel_Cube(Piece *piece, bool isCreateGap)
{
	// Initialize the ObjPiece
	int pieceID = piece->pieceID;

	objPuzzle->SetPiece(piece, tolerance);

	// Don't deform the cube only show the cube with tolerance edges (for capturing figure)
	if ( isCreateGap == false)
		return;

	// Deform cube face for each piece voxel
	for (int j=0; j<6; j++)
	{
		for (int i=0; i<piece->voxelList.size(); i++)
		{
			// Note: make this change on 2014.06.13 for solving the issue of boolean 
			//       intersection between puzzle piece with tolerance and original model

			// For each face of each voxel, if it is the face on piece surface
#ifdef KEEP_PUZZLE_APPEARANCE
			if ( piece->voxelList[i]->neiborPiece[j] != piece->pieceID &&
				 piece->voxelList[i]->neiborPiece[j] != NONE_PIECE )
#else
			if ( piece->voxelList[i]->neiborPiece[j] != piece->pieceID )
#endif
			{
				objPuzzle->objList[pieceID]->cubeList[i].MoveFaceInside( j );
			}
		}
	}

	// Deform cube edge for each piece voxel
	for (int i=0; i<piece->voxelList.size(); i++)
	{
		for (int j=0; j<12; j++)
		{
			int faceID0 = edgeNeiborFaceIDs[j][0];
			int faceID1 = edgeNeiborFaceIDs[j][1];
			int diagPieceID = GetDiagonalVoxelPieceID(piece->voxelList[i]->pos, faceID0, faceID1 );

#ifdef KEEP_PUZZLE_APPEARANCE
			if ( piece->voxelList[i]->neiborPiece[faceID0] == piece->pieceID &&
				 piece->voxelList[i]->neiborPiece[faceID1] == piece->pieceID &&
				 diagPieceID != piece->pieceID &&
				 diagPieceID != NONE_PIECE )
#else
			if ( piece->voxelList[i]->neiborPiece[faceID0] == piece->pieceID &&
				piece->voxelList[i]->neiborPiece[faceID1] == piece->pieceID &&
				diagPieceID != piece->pieceID )
#endif
			{
				objPuzzle->objList[pieceID]->cubeList[i].MoveEdgeInside( j );
			}
		}
	}
}

int PuzConverter::GetDiagonalVoxelPieceID(Vector3i currVoxelPos, int axisIDA, int axisIDB)
{
	Vector3i diagVoxelPos = currVoxelPos + neiborPos[axisIDA] + neiborPos[axisIDB];

    Voxel* diagVoxel = puzzle->volume->GetVolumeVoxel(diagVoxelPos);

	int pieceID = diagVoxel->piece;
	return pieceID;
}




