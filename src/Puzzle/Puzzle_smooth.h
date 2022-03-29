//
// Created by Linsanity on 2/1/22.
//

#ifndef HIGHLEVELPUZZLE_LIBIGL_PUZZLE_SMOOTH_H
#define HIGHLEVELPUZZLE_LIBIGL_PUZZLE_SMOOTH_H

#include "PieceCreator.h"
#include "PuzConfig.h"
#include "Puzzle.h"

class Piece;
class Puzzle;

class Puzzle_smooth
{
public:
//    Puzzle inputPuzzle;
    vector<float> originalSmoothPuzzleData;
    vector<float> originalSmoothPuzzleData_full;
    vector<int> inputPuzzleData;
    vector<int> emptyVoxellist;
    vector<int> attachVoxelList;
    vector<int> attachVoxelList_full;

    // Problematic voxel location
    vector<int> inputProblemVoxelList;

    float emptyVoxelThreshold;
    float fullVoxelThreshold;

    Vector3i initVolumeSize;
    Vector3f initVoxelSize;
    Vector3f transVector;

    int emptyVoxelNum;
    int attachVoxelNum;
    int attachVoxelNum_full;
    int successAttachNum;
    int successAttachNum_full;
    int problematicVoxelNum;

    int i_Begin, i_End, j_Begin, j_End, k_Begin, k_End;

public:
    Puzzle_smooth();
    ~Puzzle_smooth();
    void ClearPuzzle_smooth();
    void InitPuzzle_smooth(float emptyThreshold = 0.01, float fullThreshold = 0.1);
//    void InitPuzzleCreator_Iter(Puzzle * inputPuzzle);

    /// Read Smooth Shape Puzzle File
    void ReadSmoothPuzzleFile(string fileName);
    void ReadSmoothPuzzleFile_full(string fileName);

    /// Attach Voxels
    Puzzle * AttachVoxel(vector<int> puzzleData, int pieceNum);
    Puzzle * AttachVoxel_full(vector<int> puzzleData, int pieceNum);

};

#endif //HIGHLEVELPUZZLE_LIBIGL_PUZZLE_SMOOTH_H
