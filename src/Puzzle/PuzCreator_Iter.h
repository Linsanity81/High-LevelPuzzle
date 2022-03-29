//
// Created by Linsanity on 14/12/21.
//

#ifndef HIGHLEVELPUZZLE_LIBIGL_PUZCREATOR_ITER_H
#define HIGHLEVELPUZZLE_LIBIGL_PUZCREATOR_ITER_H

#include "PieceCreator.h"
#include "PuzConfig.h"
#include "Puzzle.h"

class Piece;
class Puzzle;

class PuzCreator_Iter
{
private:
//    Puzzle inputPuzzle;
    vector<int> inputPuzzleData;
    vector<float> inputPuzVoxelPossList;

    vector<vector<int>> puzzleCandidates;

    int cellNum;
    int pieceNum;
    int initLevel;
    int initTotalMoves;
    int initDissComplexity;

    Vector3i initVolumeSize;
    Vector3f initVoxelSize;

public:
    PuzCreator_Iter();
    ~PuzCreator_Iter();
    void InitPuzzleCreator_Iter(Puzzle * inputPuzzle);

    /// Create Interlocking, Buildable and High-level Puzzle
    Puzzle * CreateBuildablePuzzle_Iter(int keyLevel = 20, float convergenceTime = 600, float timeIter = 600);

    /// Helper Functions
    void ComputePieceReachability(Puzzle *puzzle, int pieceID);
};

#endif //HIGHLEVELPUZZLE_LIBIGL_PUZCREATOR_ITER_H
