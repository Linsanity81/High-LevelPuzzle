///////////////////////////////////////////////////////////////
//
// PieceCreator.h
//
//   Construct each individual puzzle piece
//
// by Peng Song and Rulin Chen
//
// 27/Aug/2021
//
///////////////////////////////////////////////////////////////

#ifndef _PIECE_CREATOR_H
#define _PIECE_CREATOR_H

#include "Utility/HelpPuz.h"
#include <math.h>
#include "Puzzle_debug/Piece_debug.h"


class Voxel;
class Piece;
class PieceGroup;
class PuzConfig;
class Piece_debug;
class PuzSolver;


struct SeedPath
{
	int pieceID;                        // The pieceID that is going to be subdivided
	int pieceAxisID;                    // The moving axis of the remvPiece/seedPath
	bool isValid;                       // Is the seedPath valid

	vector<Vector3i> contaVoxels;       // The voxels that seed voxels should contact along one direction

	vector<Vector3i> seedVoxels;        // The SeedVoxel positions in ExpVolume (one seedVoxel for the key)
	vector<Vector3i> keptVoxels;        // The expVoxels that prevents the seedPath from removing (one keptVoxel for the key)
	float seedPossib;                   // Possibility to select this candidate as an actual seed voxel

	vector<Vector3i> pathVoxels;        // All the expVoxels on the seedPath
	vector<int> moveAxisIDs;            // For the key piece,  it saves motion space of the pathVoxels in the tagtPuzConfig
	                                    // For a normal piece, it saves motion space of the pathVoxels in the nextPuzConfig

	vector<int> seedMoveSteps;          // The number of steps that each seedVoxel can move
	int moveStep;                       // The number of steps that the seedPath can move
	bool enableBackMotion;              // If the SeedPath encourages back motion of prevPiece after it moves
								        // TODO: may need to compute the number of steps (still allow back motion)
};

struct BlockPath
{
	int pieceID;                        // The pieceID that is going to be subdivided
	int pieceAxisID;                    // The moving axis of the remvPiece
	bool isValid;                       // Is the blockPath valid

	Vector3i blockVoxel;                // The block voxel position in ExpVolume
	vector<Vector3i> keptVoxels;        // The expVoxels that prevents the blockVoxel from moving
	float blkPossib;                    // Possibility to select this candidate as an actural block voxel

	vector<Vector3i> pathVoxels;        // All the expVoxels on the blockPath
};

struct MainPath
{
    int pieceID;                        // The pieceID that is going to be subdivided
	int pieceAxisID;                    // The moving axis of the remvPiece
	bool isValid;                       // Is the mainPath valid

	int moveStep;                       // The number of steps that the seedPath can move

	vector<Vector3i> keptVoxels;        // Combined kept expVoxels of seedPath and blockPath
	vector<Vector3i> pathVoxels;        // All the expVoxels on the mainPath
	vector<Vector3i> pathOrgVoxels;     // All the orgVoxels on the mainPath

    ////////////////////////////////////////////////////////////////////
    // Note: These variables are for debug

    vector<Vector3i> _ContaVoxels;      // Draw the voxels for debug

    vector<Vector3i> _SeedVoxels;
    vector<Vector3i> _SeedKeptVoxels;
    vector<Vector3i> _SeedPathVoxels;

    vector<Vector3i> _BlockVoxel;
    vector<Vector3i> _BlockKeptVoxels;
    vector<Vector3i> _BlockPathVoxels;

    vector<Vector3i> _ExtdVoxels;

    ////////////////////////////////////////////////////////////////////
};

class ExpVolume;

class PieceCreator
{
private:
    ExpVolume *expVolume;                // Expanded volume of the puzzle
	vector<Piece*> pieceList;            // Puzzle piece list

public:
	PieceCreator();
	~PieceCreator();
	void InitPieceCreator(vector<Piece*> puzPieces, Vector3i puzVolumeSize, bool isCopyReachValue);
	void ClearPieceCreator();

    /// Utility functions
    int RandomlySelectVoxel(vector<Voxel*> voxelList, float beta);
    bool IsRemainPieceConnected(int lastPieceID, vector<Vector3i> mainPathVoxels);
    bool IsRemainPieceConnected(int lastPieceID, vector<Vector3i> mainPathVoxels, Vector3i mainPathCandiVoxel);

	////////////////////////////////////////////////////
	/// Subdivide the Key Puzzle Piece
	////////////////////////////////////////////////////

	/// Compute MainPath for the Key Piece
    bool ComputeMainPath(int remvVoxelNum, MainPath &mainPath, Piece_debug & piece_debug);

	/// Seed Path
	SeedPath CreateSeedPath(int remvVoxelNum, vector<Vector3i> emptyVoxels);
	vector<SeedPath> FindPieceSeedVoxels(vector<Vector3i> emptyVoxels);
	void ComputeSeedPathVoxels(SeedPath &seedPath);

	/// Block Path
	BlockPath CreateBlockPath(SeedPath seedPath, int remvVoxelNum);
	vector<BlockPath> FindPieceBlockVoxels(SeedPath seedPath);
	void ComputeBlockKeptVoxels(BlockPath &blockVoxel, SeedPath seedPath);
	void ComputeBlockPathVoxels(BlockPath &blockPath, SeedPath seedPath);
	
	/// Extend Main Path
	void ExtendMainPath(MainPath &mainPath, int remvVoxelNum);
	bool IsExtendVoxel(MainPath mainPath, Vector3i expVoxelPos);
	int SelectExtendVoxel(MainPath mainPath, vector<Voxel*> extdExpCandis, float beta);

	////////////////////////////////////////////////////
	/// Subdivide Normal Puzzle Piece
	///////////////////////////////////////////////////

	/// Compute MainPath for a Normal Piece
    MainPath ComputeMainPath(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, int lastPieceID, int remvVoxelNum, Piece_debug & piece_debug);
	vector<vector<Vector3i>> ComputeContactVoxelsCandis(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, int lastPieceID);
	void GetEmptyVoxelExpPos(PuzConfig *tagtPuzConfig, int pieceID, vector<Vector3i> &emptyVoxelPosList);
	void GetSolidVoxelExpPos(PuzConfig *prevPuzConfig, vector<Vector3i> emptyVoxelPosList, vector<Vector3i> &solidVoxelPosList);

	/// Seed Path
	SeedPath CreateSeedPath(PuzConfig *tagtPuzConfig, int lastPieceID, int remvVoxelNum, vector<vector<Vector3i>> contaVoxelsSet);
	vector<SeedPath> FindPieceSeedVoxels(PuzConfig *tagtPuzConfig, int lastPieceID, vector<vector<Vector3i>> contaVoxelsSet);
	void ComputeSeedPathVoxels(PuzConfig *tagtPuzConfig, SeedPath &seedPath);
	vector<Voxel*> FindAvailableFillVoxels(PuzConfig *tagtPuzConfig, int pieceID, int pieceAxisID);
	vector<Vector3i> GenerateMovablePath(PuzConfig *tagtPuzConfig, int pieceID, int pieceAxisID, vector<Vector3i> inputExpVoxels);
	int CheckSeedPathMotionSpace(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath &seedPath, vector<int> &moveAxisIDUnion);
	int CheckSeedPathRemovalAxis(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath &seedPath, vector<int> &removeAxisIDUnion);

	/// Block Path
	BlockPath CreateBlockPath(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath seedPath, int maxIndex, vector<int> moveAxisIDUnion, int remvVoxelNum);
	vector<BlockPath> FindPieceBlockVoxels(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath seedPath, int maxIndex, vector<int> moveAxisIDUnion);
	vector<Vector3i> ComputeBlockVoxelsInConfig(PuzConfig *prevPuzConfig, PuzConfig *tagtPuzConfig, SeedPath seedPath);
	bool CheckBlockVoxelInConfig(Vector3i expVoxelPos, SeedPath seedPath, PuzConfig *prevPuzConfig);
    bool CheckBlockVoxelRemvInConfig(Vector3i expVoxelPos, SeedPath seedPath, PuzConfig *prevPuzConfig, vector<Piece*> pieceList);
	bool CheckBlockVoxelInNextConfig(Vector3i expVoxelPos, SeedPath seedPath, PuzConfig *tagtPuzConfig, vector<Vector3i> &keptExpVoxels);
	void ComputeBlockPathVoxels(PuzConfig *tagtPuzConfig, SeedPath seedPath, BlockPath &blockPath);

	/// Extend Main Path
	void ExtendMainPath(PuzConfig *tagtPuzConfig, MainPath &mainPath, int remvVoxelNum);
	bool IsExtendVoxel(MainPath mainPath, Vector3i expVoxelPos, vector<Voxel*> avaiFillVoxels);
};

#endif