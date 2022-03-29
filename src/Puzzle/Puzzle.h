///////////////////////////////////////////////////////////////
//
// Puzzle.h
//
//   3D Puzzle Class
//
// by Peng Song and Rulin Chen
//
// 14/Aug/2021
//
//
///////////////////////////////////////////////////////////////

#ifndef _PUZZLE_H
#define _PUZZLE_H

#include <string>
#include "PieceCreator.h"
#include "Utility/HelpPuz.h"

class Piece;
class PuzAction;
class PuzConfig;
class Volume;
struct MainPath;

class Puzzle 
{
public:
    Volume *volume;                       // Volume with a set of voxels

	vector<Piece*> pieceList;             // Puzzle piece array

	int puzLockState;				      // Puzzle locking state
	int puzBuildState;				      // Puzzle buildable state
	int puzLevel;                         // Number of movable steps to remove the first piece
	int puzGraphConfigsNum;               // Number of configs in disassembly graph
	int puzTotalMoves;
    vector<PuzAction> puzActionList;       // A plan to disassemble the whole puzzle

    bool puzDisconnectivityState;

    float generationTime;

    int dissComplexity;

    int kernalGraphConfigNum;

    vector<Eigen::MatrixXd> smoothPieceVerticeList;
    vector<Eigen::MatrixXi> smoothPieceFaceList;

    Eigen::MatrixXd smoothShape_V;
    Eigen::MatrixXi smoothShape_F;

//    vector< vector<int> > disconnectedEdgeList;

public:
	Puzzle();
	~Puzzle();
    void ClearPuzzle();
    Puzzle & operator=(const Puzzle & puzzle);
    void SetVolume(Volume* _volume);
	void PrintPuzzle();
	vector<int> ExtractPuzzleData();

	/// Check Puzzle States (Interlocking, Buildable, and Levels)
	int CheckPuzzleState(bool isPrint, bool isFixLastPiece);
    bool CheckValidPuzzle();
    void CheckConnectivityState();
    vector<Eigen::MatrixXf> GetPieceAssemblyPos(int disassemblyStateID);

    /// Test Global Interlocking
    int CheckPuzzleLockState();
    void BuildPuzzleContactGraph();
    int GetPuzLockState(int pieceNum, int movePieceNum, int moveGroupNum, vector<int> pieceMovableAxes);

    /// Puzzle Rendering Data
    void CreatePuzzleGeometry(vector<Eigen::MatrixXf> &voxelMinPtsList,
                              vector<Eigen::MatrixXf> &voxelMaxPtsList,
                              vector<Eigen::MatrixXf> &voxelCenPtsList,
                              vector<Eigen::MatrixXf> &cylinTopPtsList,
                              vector<Eigen::MatrixXf> &cylinBotPtsList,
                              int disassStateID);

    void CreatePuzzleGeometry(vector<Eigen::MatrixXf> &voxelMinPtsList,
                              vector<Eigen::MatrixXf> &voxelMaxPtsList,
                              vector<Eigen::MatrixXf> &voxelCenPtsList,
                              vector<Eigen::MatrixXf> &cylinTopPtsList,
                              vector<Eigen::MatrixXf> &cylinBotPtsList,
                              PuzConfig currPuzConfig);

    void CreatePuzzleConnectivityGeo(Eigen::MatrixXf &cylinTopPts,
                                     Eigen::MatrixXf &cylinBotPts);

	/// Read Puzzle File
    void ReadPuzzleFile(string fileName);
    void ReadSmoothPuzzleFile(string fileName);
    void InitPuzzle(const Vector3i volumeSize, const Vector3f voxelSize, const vector<int> puzzleData, const vector<vector <int>> connectivityEdgeList);

    /// Save Puzzle Files
    void SavePuzzleFiles(string puzFolderPath, float puzTolerance, bool isFixLastPiece);
    void SaveCSGPuzzleFiles(string puzFolderPath, string voxelizedPuzFolderPath, float puzTolerance, bool isFixLastPiece, Eigen::MatrixXd smoothShape_V, Eigen::MatrixXi smoothShape_F);
    void WriteDisassemblyGraph(string folderPath, vector<PuzConfig*> tracedPuzConfigs, string puzzlePureName);
    void WriteDisassemblyKernelGraph(string folderPath, vector<PuzConfig*> tracedPuzConfigs, string puzzlePureName);
    void UpdateKernelGraph(string folderPath);
    void WriteDisassemblyMotion(string folderPath, vector<PuzAction> puzActionList);
    void WritePieceOBJs_voxel(string folderPath, float puzTolerance);
    void WritePieceOBJs_skel(string folderPath);

};

#endif
