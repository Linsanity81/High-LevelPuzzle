//
// Created by Linsanity on 14/12/21.
//

#include "time.h"
#include "Utility/HelpDefine.h"
#include "Utility/HelpPuz.h"
#include "PieceFace.h"
#include "Piece.h"
#include "PuzAction.h"
#include "Volume.h"
#include "Puzzle.h"
#include "PuzCreator_Iter.h"

extern Vector3i neiborPos[6];

///=========================================================================================///
///                                   Initialization
///=========================================================================================///

PuzCreator_Iter::PuzCreator_Iter()
{
//    inputPuzzle = NULL;
}

PuzCreator_Iter::~PuzCreator_Iter()
{
    inputPuzzleData.clear();
    inputPuzVoxelPossList.clear();
}

void PuzCreator_Iter::InitPuzzleCreator_Iter(Puzzle * inputPuzzle)
{
    for (int i = 0; i < inputPuzzle->pieceList.size(); ++i)
    {
        ComputePieceReachability(inputPuzzle, i);
    }

    printf("Input Puzzle: \n");
    for (int i=0; i< inputPuzzle->volume->GetVoxelGrid().size(); i++)
    {
        inputPuzzleData.push_back( inputPuzzle->volume->GetVoxelGrid()[i]->piece + 1);
        printf("%d ", inputPuzzle->volume->GetVoxelGrid()[i]->piece + 1);
        inputPuzVoxelPossList.push_back(MAX_VOXEL_REACH - inputPuzzle->volume->GetVoxelGrid()[i]->reach);
    }
    printf("\n\n");

    /// Check the input puzzle state first
    inputPuzzle->CheckPuzzleState(false, true);

    /// Initialize the puzzle parameters
    cellNum = inputPuzzle->volume->voxelGrid.size();
    pieceNum = inputPuzzle->pieceList.size();
    initLevel = inputPuzzle->puzLevel;
    initTotalMoves = inputPuzzle->puzActionList.size();
    initDissComplexity = inputPuzzle->dissComplexity;
    initVolumeSize = inputPuzzle->volume->volumeSize;
    initVoxelSize = inputPuzzle->volume->voxelSize;
}

///=========================================================================================///
///               Create Interlocking, Buildable and Multi-Steps Puzzle
///=========================================================================================///

Puzzle * PuzCreator_Iter::CreateBuildablePuzzle_Iter(int keyLevel, float convergenceTime, float timeIter)
{
    Puzzle *currPuzzle = NULL;

    clock_t beginTime = clock();
    clock_t endTime;
    float elapsed = 0;
    float lastUpdatedTime = 0;

    vector<int> currPuzData = inputPuzzleData;
    int currLevel = initLevel;
    int currKernelNodesNum = 0;
    int currTotalMoves = initTotalMoves;
    int currDissComplexity = initDissComplexity;

    int trialNum = 0;

    printf("\n========================\n");
    printf("TrialNum: %d \n", trialNum);
    printf("currLevel: %d \n", currLevel);
    printf("currTotalMoves: %d \n", currTotalMoves);
    printf("currDissComplexity: %d \n", currDissComplexity);
    printf("\n========================\n");

    while (1)
    {
        endTime = clock();
        elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);

        if (elapsed - lastUpdatedTime > convergenceTime)
        {
            printf("Reach the convergence condition.\n");
            break;
        }

        trialNum++;

        vector<int> tempPuzData = currPuzData;

        /// Flip the cell
        int flipIndex = rand() % cellNum;
//        int flipIndex = GetRandomObjIndex( inputPuzVoxelPossList, 2 );

        if (tempPuzData[flipIndex] != 0)
        {
            tempPuzData[flipIndex] = rand() % pieceNum + 1;
        }
        else
        {
            continue;
        }

        /// Convert the puzzle data to puzzle class
        if( currPuzzle != NULL )
        {
            delete currPuzzle;
            currPuzzle = NULL;
        }

        currPuzzle = new Puzzle();
        currPuzzle->InitPuzzle(initVolumeSize, initVoxelSize, tempPuzData);

        /// Check if the puzzle is valid
        bool isValid = currPuzzle->CheckValidPuzzle();
        if (!isValid)
            continue;

        /// Check the puzzle state
        currPuzzle->CheckPuzzleState(false, true);

        /// If the puzzle is valid, then check if its level or total moves are better
//        if ( currPuzzle->puzLockState  != PUZZLE_DEAD_LOCK && currPuzzle->puzBuildState == PUZZLE_NORMAL_BUILDABLE && currPuzzle->puzDisconnectivityState == true)
        if ( currPuzzle->puzLockState  == PUZZLE_INTER_LOCK && currPuzzle->puzBuildState == PUZZLE_NORMAL_BUILDABLE)
        {
            if (currPuzzle->puzLevel >= currLevel
            or (currPuzzle->puzActionList.size() >= currTotalMoves and currPuzzle->puzLevel >= currLevel)
            or (currPuzzle->puzLevel >= currLevel and currPuzzle->dissComplexity > currDissComplexity))
//                if (currPuzzle->puzLevel == currLevel and currPuzzle->kernalGraphConfigNum > currKernelNodesNum)
            {
                currLevel = currPuzzle->puzLevel;
                currKernelNodesNum = currPuzzle->kernalGraphConfigNum;
                currTotalMoves = currPuzzle->puzActionList.size();
                currPuzData = tempPuzData;
                currDissComplexity = currPuzzle->dissComplexity;

                endTime = clock();
                elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);

                if (currPuzzle->puzLevel > currLevel and currPuzzle->dissComplexity > currDissComplexity and currPuzzle->puzActionList.size() > currTotalMoves)
                    lastUpdatedTime = elapsed;

                currPuzzle->generationTime = elapsed;

                printf("\n========================\n");
                printf("TrialNum: %d \n", trialNum);
                printf("currLevel: %d \n", currLevel);
                printf("currTotalMoves: %d \n", currTotalMoves);
                printf("currDissComplexity: %d \n", currDissComplexity);
                printf("currKernelNodesNum: %d \n", currKernelNodesNum);
                printf("\nThe time taken to create buildable puzzle is %.3f mins \n\n", elapsed);
                currPuzzle->PrintPuzzle();
                printf("\n========================\n");

                if (currLevel >= keyLevel)
                    break;

                // Stop Condition
                if (elapsed > timeIter)
                    break;

            }
            else
                continue;
        }
        else
        {
            continue;
        }
    }

    return currPuzzle;
}

///=========================================================================================///
///                                     Helper Functions
///=========================================================================================///

void PuzCreator_Iter::ComputePieceReachability(Puzzle *puzzle, int pieceID)
{
    // Compute number of neighbor voxels of each voxel
    for (int i=0; i<puzzle->pieceList[pieceID]->voxelList.size(); i++)
    {
        Vector3i currVoxelPos = puzzle->pieceList[pieceID]->voxelList[i]->pos;

        puzzle->pieceList[pieceID]->voxelList[i]->reach = puzzle->volume->GetNeighborVoxelNum(currVoxelPos, pieceID);
    }

    // Apply the mean filter for three times
    for (int k=0; k<3; k++)
    {
        // Calculate the neighbor voxel reachability value based on previous iteration
        vector<float> neiborReaches;
        for (int i=0; i<puzzle->pieceList[pieceID]->voxelList.size(); i++)
        {
            int neiborReachValues[6];
            Vector3i currVoxelPos = puzzle->pieceList[pieceID]->voxelList[i]->pos;

            for (int j=0; j<6; j++)
            {
                Vector3i neiborVoxelPos = currVoxelPos + neiborPos[j];
                int neiborIndex = GetVoxelIndexInList(puzzle->pieceList[pieceID]->voxelList, neiborVoxelPos);

                if ( neiborIndex == VOXEL_OUT_LIST )
                    neiborReachValues[j] = 0;
                else
                    neiborReachValues[j] = puzzle->pieceList[pieceID]->voxelList[neiborIndex]->reach;
            }

            float neiborReachSum = 0;
            for (int j=0; j<6; j++)
            {
                neiborReachSum += pow(0.1f, float(k+1)) * neiborReachValues[j];
            }
            neiborReaches.push_back( neiborReachSum );
        }

        // Plus reachability value of current voxel with that of neighbor voxels
        for (int i=0; i<puzzle->pieceList[pieceID]->voxelList.size(); i++)
        {
            puzzle->pieceList[pieceID]->voxelList[i]->reach += neiborReaches[i];
        }
    }

    // Copy the voxel reachability value info of origPiece
    puzzle->volume->UpdateVolume_Reach(puzzle->pieceList[pieceID]);
}
