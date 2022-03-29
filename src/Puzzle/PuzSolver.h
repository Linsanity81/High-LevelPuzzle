///////////////////////////////////////////////////////////////
//
// PuzSolver.h
//
//   Compute a disassembly graph of a given puzzle
//
// by Peng Song and Rulin Chen
// 
// 25/Aug/2021
//
///////////////////////////////////////////////////////////////

#ifndef _PUZ_SOLVER_H
#define _PUZ_SOLVER_H


class Piece;
class ExpVolume;
class PuzConfig;
class PuzAction;

#define DISASSEMBLY_GRAPH_TOO_LARGE            -1
#define DISASSEMBLY_GRAPH_REMOVABLE_PIECE       1
#define DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE    2

class PuzSolver
{
private:
    ExpVolume *expVolume;                        // Expanded volume of the puzzle
    vector<Piece*> pieceList;                    // Puzzle piece list


public:
    PuzSolver();
	~PuzSolver();
	void InitPuzSolver(vector<Piece*> puzPieces, Vector3i puzVolumeSize);
    void InitPuzSolver(vector<Piece*> puzPieces, Vector3i puzVolumeSize, int expVolumeScalarSize);

	/// Compute a Complete Disassembly Plan
    int DisassemblyPuzzzle(int disassMode);
    int DisassemblyPuzzzle_Graph(int disassMode, vector<PuzConfig*> &graphConfigs, vector<PuzConfig*> &pathConfigs, int &puzzleLevel);
    void ComputeDisassemblyPlan(vector<PuzConfig*> pathConfigs, vector<PuzAction> &puzActionList, bool isFixLastPiece);
    void GetPuzActionFromConfigs(const PuzConfig *currConfig, const PuzConfig *prevConfig, PuzAction &currPuzAction, bool isFixLastPiece);
    void ChangeDisassemblyReference(vector<PuzConfig*> &pathConfigs);

    /// Build PuzConfig Graph for Disassembly
    void ComputeDisassemblyPath(vector<PuzConfig*> graphConfigs, vector<PuzConfig*> &pathConfigs);
    int BuildPuzConfigGraph_Full(int disassMode, vector<PuzConfig*> &graphConfigs, int &puzzleLevel);
    int BuildPuzConfigGraph_Full(int disassMode, PuzConfig* rootPuzConfig, vector<PuzConfig*> &graphConfigs, int &puzzleLevel);
    int BuildPuzConfigGraph_Partial(int disassMode, vector<PuzConfig*> &graphConfigs);
    int BuildPuzConfigGraph_Partial(int disassMode, PuzConfig* rootPuzConfig, vector<PuzConfig*> &graphConfigs, PuzConfig * &targetConfig);
    int BuildRemvPuzConfigGraph_Partial(int disassMode, PuzConfig* rootPuzConfig);
    bool DetermineNextConfigs(PuzConfig &puzConfig, int disassMode, vector<int> &remvPieceIDs, vector<int> &remvPieceAxisIDs, vector<PuzConfig*> &existingConfigs);
    bool GroupRemovableAlongAxis(PieceGroup *currPieceGroup, int axisID);
    void ComputeNextPuzConfigs(PuzConfig &puzConfig, vector<PuzConfig*> &existingConfigs, vector<int> currPieceIDIndices, PieceGroup *currPieceGroup);
    bool IsVoxelOverlap(PieceGroup *currPieceGroup, int axisID, int moveStep, bool &isOutExpVolume);
    void TracePuzConfigGraph(PuzConfig *rootPuzConfig, vector<PuzConfig*> &graphConfigs, bool isMarkSequenceID);

    /// Compute Puzzle Level
    void ComputePuzzleLevel(vector<PuzConfig*> targetConfigs, int &puzzleLevel);
    void ComputeShortestDistanceToRootConfig(vector<PuzConfig*> graphConfigs, int rootConfigIndex);
    void ComputeShortestPathConfigs(PuzConfig* targetConfig, vector<PuzConfig*> &pathConfigs);
    void ComputeShortestPathConfigs(PuzConfig* targetConfig, vector<PuzConfig*> graphConfigs, vector<PuzConfig*> &pathConfigs);
    void ComputeShortestPathConfigs(PuzConfig* rootConfig, PuzConfig* targetConfig, vector<PuzConfig*> graphConfigs, vector<PuzConfig*> &pathConfigs);

    /// Puzzle Config/Action Operations
    vector<int> GetPieceIDList();
    int GetPieceIndex(int tagtPieceID, vector<int> pieceIDList);
    int FindPuzConfigInList(PuzConfig *tagtPuzConfig, vector<PuzConfig *> puzConfigList);
};

#endif