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
/// TODO:
/// 1. a simple version that does not need to save puzConfigs
/// 2. check whether the removable group can be disassembled
/// 3. Disassembly mode: fix the last piece or move/remove the small one (have to fix the last piece)
// 
///////////////////////////////////////////////////////////////

#include "Utility/HelpDefine.h"
#include "Utility/HelpPuz.h"
#include "PieceFace.h"
#include "Piece.h"
#include "PieceGroup.h"
#include "PuzConfig.h"
#include "PuzAction.h"
#include "ExpVolume.h"
#include "PuzSolver.h"
#include "Volume.h"
#include <iostream>
#include <algorithm>


extern Vector3i neiborPos[6];
extern char axisArray[6][4];


///=========================================================================================///
///                                    Initialization
///=========================================================================================///

PuzSolver::PuzSolver()
{
	expVolume = NULL;
}

PuzSolver::~PuzSolver()
{
    if( expVolume != NULL )
    {
        delete expVolume;
        expVolume = NULL;
    }
}

void PuzSolver::InitPuzSolver(vector<Piece*> puzPieces, Vector3i puzVolumeSize)
{
    if( puzPieces.size() == 0 )
    {
        printf("Warning: The input puzzle to pieceCreator is empty! \n");
        return;
    }

    // Push back puzzle piece pointers
    for (int i=0; i<puzPieces.size(); i++)
    {
        pieceList.push_back(puzPieces[i]);
    }

    for (int i=0; i<pieceList.size(); i++)
    {
        pieceList[i]->ClearPiece();
    }

    if( expVolume != NULL )
        delete expVolume;

    expVolume = new ExpVolume();

    expVolume->InitExpVolume(puzPieces, puzVolumeSize, false);
}

void PuzSolver::InitPuzSolver(vector<Piece*> puzPieces, Vector3i puzVolumeSize, int expVolumeScalarSize)
{
    if( puzPieces.size() == 0 )
    {
        printf("Warning: The input puzzle to pieceCreator is empty! \n");
        return;
    }

    // Push back puzzle piece pointers
    for (int i=0; i<puzPieces.size(); i++)
    {
        pieceList.push_back(puzPieces[i]);
    }

    for (int i=0; i<pieceList.size(); i++)
    {
        pieceList[i]->ClearPiece();
    }

    if( expVolume != NULL )
        delete expVolume;

    expVolume = new ExpVolume();

    expVolume->expVolumeSizeScaler = expVolumeScalarSize;

    expVolume->InitExpVolume(puzPieces, puzVolumeSize, false);
}





///=========================================================================================///
///                              Compute a Complete Disassembly Plan
///=========================================================================================///

int PuzSolver::DisassemblyPuzzzle(int disassMode)
{
    vector<PuzConfig*> graphConfigs;
    vector<PuzConfig*> pathConfigs;
    int puzzleLevel;

    int buildState = DisassemblyPuzzzle_Graph(disassMode, graphConfigs, pathConfigs, puzzleLevel);

    for (int i = 0; i < graphConfigs.size(); ++i)
    {
        delete graphConfigs[i];
    }

    return buildState;
}

int PuzSolver::DisassemblyPuzzzle_Graph(int disassMode, vector<PuzConfig*> &graphConfigs, vector<PuzConfig*> &pathConfigs, int &puzzleLevel)
{
    vector<int> pieceIDList = GetPieceIDList();

    // Initialize the root puzzle config specified by pieceIDList
    PuzConfig *rootPuzConfig = new PuzConfig();
    rootPuzConfig->InitiConfig(pieceIDList);
    rootPuzConfig->configType = PUZ_CONFIG_ROOT;

    pathConfigs.clear();

    int graphState = BuildPuzConfigGraph_Full(disassMode, rootPuzConfig,graphConfigs, puzzleLevel);

    if( graphState != DISASSEMBLY_GRAPH_REMOVABLE_PIECE )
        return PUZZLE_NO_REMOVE_GROUP;

#ifndef COMPUTE_KERNAL_GRAPH_ONLY
    int partialGraphState = BuildPuzConfigGraph_Partial(disassMode,graphConfigs);

    if ( partialGraphState != DISASSEMBLY_GRAPH_REMOVABLE_PIECE)
        return PUZZLE_NOT_BUILDABLE;
#endif

    ComputeDisassemblyPath(graphConfigs, pathConfigs);

    //printf("Computing Disassembly Path Finished.\n");

    return PUZZLE_NORMAL_BUILDABLE;
}

void PuzSolver::ComputeDisassemblyPlan(vector<PuzConfig*> pathConfigs, vector<PuzAction> &puzActionList, bool isFixLastPiece)
{
    if( pathConfigs.size() < 2 )
        return;

    if(!isFixLastPiece)
        ChangeDisassemblyReference(pathConfigs);

    vector<int> currGroupRemoveIDs;

    for (int i = 1; i < pathConfigs.size(); i++)
    {

        PuzAction currPuzAction;

        PuzConfig *prevConfig;

        for (int j = 0; j < pathConfigs.size(); ++j)
        {
            if (std::find(pathConfigs[j]->nextPuzConfigs.begin(), pathConfigs[j]->nextPuzConfigs.end(), pathConfigs[i]) != pathConfigs[j]->nextPuzConfigs.end())
            {
                prevConfig = pathConfigs[j];
                break;
            }
        }

        if (prevConfig != pathConfigs[i-1])
            continue;

        PuzConfig *currConfig = pathConfigs[i];

        GetPuzActionFromConfigs(currConfig, prevConfig, currPuzAction, isFixLastPiece);

        puzActionList.push_back( currPuzAction );
    }
}

void PuzSolver::GetPuzActionFromConfigs(const PuzConfig *currConfig, const PuzConfig *prevConfig, PuzAction &currPuzAction, bool isFixLastPiece)
{
    if (isFixLastPiece)
    {
        /// Case 1: a pieceMove action
        if( currConfig->pieceIDList== prevConfig->pieceIDList )
        {
            currPuzAction.isMoveAction = true;

            for (int i=0; i<currConfig->piecePosList.size(); i++)
            {
                    Vector3i currPiecePos = currConfig->piecePosList[i];
                    Vector3i prevPiecePos = prevConfig->piecePosList[i];

                    if( currPiecePos != prevPiecePos )
                    {
                        currPuzAction.movePieceIDs.push_back( currConfig->pieceIDList[i] );
                        currPuzAction.moveVector = currPiecePos - prevPiecePos;
                    }
            }
        }

        /// Case 2: a pieceRemove action
        else
        {
            currPuzAction.isMoveAction = false;

            currPuzAction.remvPieceIDs = prevConfig->remvPieceIDs;
            currPuzAction.remvAxisIDs.push_back(prevConfig->remvAxisIDs[0]);
        }
    }

    else
    {
        /// Case 1: a pieceMove action
        if( currConfig->pieceIDList== prevConfig->pieceIDList )
        {
            currPuzAction.isMoveAction = true;

            for (int i=0; i<currConfig->piecePosList.size(); i++)
            {
                Vector3i currPiecePos = currConfig->piecePosList[i];
                Vector3i prevPiecePos = prevConfig->piecePosList[i];

                if( currPiecePos != prevPiecePos )
                {
                    currPuzAction.movePieceIDs.push_back( currConfig->pieceIDList[i] );
                    currPuzAction.moveVector = currPiecePos - prevPiecePos;
                }
            }
        }

        /// Case 2: a pieceRemove action
        else
        {
            currPuzAction.isMoveAction = false;

            if (prevConfig->remvPieceIDs.size() <= float(prevConfig->pieceIDList.size()) / 2.0)
            {
                currPuzAction.remvPieceIDs = prevConfig->remvPieceIDs;
                currPuzAction.remvAxisIDs  = prevConfig->remvAxisIDs;
            }

            else
            {
                vector<int> remvPieceIDs;

                for (int i = 0; i < prevConfig->pieceIDList.size(); ++i)
                {
                    if (std::find(prevConfig->remvPieceIDs.begin(), prevConfig->remvPieceIDs.end(), prevConfig->pieceIDList[i]) == prevConfig->remvPieceIDs.end())
                        remvPieceIDs.push_back(prevConfig->pieceIDList[i]);
                }

                currPuzAction.remvPieceIDs = remvPieceIDs;

                int currRemvAxis = prevConfig->remvAxisIDs[0];

//                printf("currRemvAxis: %d\n", currRemvAxis);

                if (currRemvAxis == 0)      currRemvAxis = 1;
                else if (currRemvAxis == 1)      currRemvAxis = 0;
                else if (currRemvAxis == 2)      currRemvAxis = 3;
                else if (currRemvAxis == 3)      currRemvAxis = 2;
                else if (currRemvAxis == 4)      currRemvAxis = 5;
                else if (currRemvAxis == 5)      currRemvAxis = 4;

                currPuzAction.remvAxisIDs.push_back(currRemvAxis);

//                printf("currRemvAxis: %d\n", currPuzAction.remvAxisIDs[0]);
            }

        }

    }
}

void PuzSolver::ChangeDisassemblyReference(vector<PuzConfig *> &pathConfigs)
{

    int lastPieceID = pathConfigs[0]->pieceIDList[pathConfigs[0]->pieceIDList.size() - 1];

    for (int i = 1; i < pathConfigs.size(); ++i) {
        PuzConfig *prevConfig = pathConfigs[i - 1];
        PuzConfig *currConfig = pathConfigs[i];

        if (currConfig->pieceIDList.size() != prevConfig->pieceIDList.size())
            continue;

        int samePosNum = 0;
        int diffPosNum = 0;

        vector<int> samePosIDs;
        vector<int> diffPosIDs;

        Vector3i moveVector;

        for (int j = 0; j < currConfig->piecePosList.size(); ++j) {
            if (currConfig->piecePosList[j] == prevConfig->piecePosList[j]) {
                ++samePosNum;
                samePosIDs.push_back(j);
            } else {
                ++diffPosNum;
                diffPosIDs.push_back(j);
                moveVector = currConfig->piecePosList[j] - prevConfig->piecePosList[j];
            }
        }

        if (diffPosNum > samePosNum) {
            for (int k = i; k < pathConfigs.size(); ++k) {
                for (int m = 0; m < pathConfigs[k]->pieceIDList.size(); ++m) {
                    pathConfigs[k]->piecePosList[m] = pathConfigs[k]->piecePosList[m] - moveVector;
                }
            }
        }

    }
}




///=========================================================================================///
///                          Build PuzConfig Graph for Disassembly
///=========================================================================================///

void PuzSolver::ComputeDisassemblyPath(vector<PuzConfig *> graphConfigs, vector<PuzConfig*> &pathConfigs)
{
    pathConfigs.clear();

    /// Set the isTraced flag to false for further tracing
    for (int i = 0; i < graphConfigs.size(); ++i)
    {
        graphConfigs[i]->isTraced = false;
    }

    /// Find the end node of the given full graph
    ComputeShortestDistanceToRootConfig(graphConfigs, 0);

    int currFurthestNodeID = 0;

    for (int i = 0; i < graphConfigs.size(); ++i)
    {
        if (graphConfigs[i]->distToRoot > graphConfigs[currFurthestNodeID]->distToRoot and graphConfigs[i]->configType == PUZ_CONFIG_PIECE_ONLY)
            currFurthestNodeID = i;
    }
    graphConfigs[currFurthestNodeID]->configType = PUZ_CONFIG_END_NODE;

    /// Compute the main shortest path
    pathConfigs.clear();

    ComputeShortestPathConfigs(graphConfigs[currFurthestNodeID], graphConfigs, pathConfigs);

    reverse(pathConfigs.begin(), pathConfigs.end());

    /// Compute the sub-paths
//    vector< vector<PuzConfig*> > subPathConfigsList;
    for (int i = 0; i < graphConfigs.size(); ++i)
    {
        if (graphConfigs[i]->configType == PUZ_CONFIG_PIECE_REMOVE or graphConfigs[i]->configType == PUZ_CONFIG_TARGET)
        {
            for (int j = 0; j < graphConfigs[i]->nextPuzConfigs.size(); ++j)
            {
                if (graphConfigs[i]->nextPuzConfigs[j]->pieceIDList.size() < graphConfigs[i]->pieceIDList.size() and graphConfigs[i]->nextPuzConfigs[j]->pieceIDList.size() > 1
                    and std::find(pathConfigs.begin(), pathConfigs.end(), graphConfigs[i]->nextPuzConfigs[j]) == pathConfigs.end())
                {
                    graphConfigs[i]->nextPuzConfigs[j]->configType = PUZ_CONFIG_GROUP_REMOVE;
//                    pieceRemvGroupConfigs.push_back(graphConfigs[i]->nextPuzConfigs[j]);

                    vector<PuzConfig*> subPathConfigs;
                    vector<PuzConfig*> subGraphConfigs;

                    TracePuzConfigGraph(graphConfigs[i]->nextPuzConfigs[j], subGraphConfigs, false);

                    for (int k = 0; k < graphConfigs.size(); ++k)
                    {
                        graphConfigs[k]->isTraced = false;
                    }

                    currFurthestNodeID = 0;

                    for (int k = 0; k < subGraphConfigs.size(); ++k)
                    {
                        if (subGraphConfigs[k]->distToRoot > subGraphConfigs[currFurthestNodeID]->distToRoot and subGraphConfigs[k]->configType == PUZ_CONFIG_PIECE_ONLY)
                            currFurthestNodeID = k;
                    }

                    ComputeShortestPathConfigs(subGraphConfigs[0], subGraphConfigs[currFurthestNodeID], subGraphConfigs, subPathConfigs);

                    reverse(subPathConfigs.begin(), subPathConfigs.end());

                    // Find the config index in the path configs
                    int index = 0;
                    for (int k = 0; k < pathConfigs.size(); ++k)
                    {
                        if (pathConfigs[k] == graphConfigs[i])
                        {
                            index = k;
                            break;
                        }
                    }

                    // Insert the subpath to the main path
                    for (int k = subPathConfigs.size() - 1; k >= 0; --k)
                    {
                        pathConfigs.insert(pathConfigs.begin() + index + 1, subPathConfigs[k]);
                    }
                }
            }
        }
    }

    /// Mark the path
    for (int i = 0; i < pathConfigs.size(); ++i)
    {
        if (pathConfigs[i]->configType == PUZ_CONFIG_UNKNOWN)
            pathConfigs[i]->configType = PUZ_CONFIG_SHORTEST_PATH;
    }

}

int PuzSolver::BuildPuzConfigGraph_Full(int disassMode, vector<PuzConfig*> &graphConfigs, int &puzzleLevel)
{
    vector<int> pieceIDList = GetPieceIDList();

    // Initialize the root puzzle config specified by pieceIDList
    PuzConfig *rootPuzConfig = new PuzConfig();
    rootPuzConfig->InitiConfig(pieceIDList);
    rootPuzConfig->configType = PUZ_CONFIG_ROOT;

    int graphState = BuildPuzConfigGraph_Full(disassMode, rootPuzConfig,graphConfigs, puzzleLevel);

    return graphState;
}

int PuzSolver::BuildPuzConfigGraph_Full(int disassMode, PuzConfig* rootPuzConfig, vector<PuzConfig*> &graphConfigs, int &puzzleLevel)
{
    // Maximum number of puzConfigs that should be visited
    const int maxExistingConfigNum = 2000;

    // Push back the deep copied root config to BSF queue
    vector<PuzConfig *> visitedConfigs;
    vector<PuzConfig *> bfsConfigQueue;
    bfsConfigQueue.push_back(rootPuzConfig);

    vector<PuzConfig *> existingConfigs;
    existingConfigs.push_back(rootPuzConfig);

    vector<PuzConfig *> targetConfigs;

    while (bfsConfigQueue.size() > 0)
    {
        // Pop up the first PuzConfig in the BFS queue
        PuzConfig *currPuzConfig = bfsConfigQueue[0];
        bfsConfigQueue.erase(bfsConfigQueue.begin());

        if ( FindPuzConfigInList(currPuzConfig, visitedConfigs) == CONFIG_OUT_LIST )
            visitedConfigs.push_back(currPuzConfig);

        vector<int> remvPieceIDs;
        vector<int> remvAxisIDs;

        expVolume->BuildConfigContactGraph(currPuzConfig, pieceList);
        bool isRemovableGroup = DetermineNextConfigs(*currPuzConfig, disassMode, remvPieceIDs,remvAxisIDs, existingConfigs);

        if (existingConfigs.size() > maxExistingConfigNum)
        {
            printf("Warning: More than %d existing configs in the graph! \n\n", maxExistingConfigNum);
            return DISASSEMBLY_GRAPH_TOO_LARGE;
        }

//        printf("%lu\n", existingConfigs.size());

        if (isRemovableGroup)
        {
            currPuzConfig->configType    = PUZ_CONFIG_TARGET_CANDI;
            currPuzConfig->remvPieceIDs  = remvPieceIDs;
            currPuzConfig->remvAxisIDs   = remvAxisIDs;

            if ( FindPuzConfigInList(currPuzConfig, targetConfigs) == CONFIG_OUT_LIST)
            {
                targetConfigs.push_back(currPuzConfig);
            }
        }
        else
        {
            // Push back the next PuzConfigs into the BSF queue
            for (int i = 0; i < currPuzConfig->nextPuzConfigs.size(); i++)
            {
                if( FindPuzConfigInList(currPuzConfig->nextPuzConfigs[i], visitedConfigs) == CONFIG_OUT_LIST )
                {
                    bfsConfigQueue.push_back(currPuzConfig->nextPuzConfigs[i]);
                }
            }
//            printf("Size of bfsCongigQueue: %lu\n", bfsConfigQueue.size());
        }
    }

    // Using BFS to find the shortest distance from every node to the root node.
    TracePuzConfigGraph(rootPuzConfig, graphConfigs, true);

    // Mark all the config nodes here as Kernel Graph Nodes
    for (int i = 0; i < graphConfigs.size(); ++i)
    {
        graphConfigs[i]->isInKernelGraph = true;
    }

    ComputeShortestDistanceToRootConfig(graphConfigs, 0);

    if (targetConfigs.size() == 0)
    {
        return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
    }
    else
    {
        ComputePuzzleLevel(targetConfigs, puzzleLevel);

        return DISASSEMBLY_GRAPH_REMOVABLE_PIECE;
    }
}

int PuzSolver::BuildPuzConfigGraph_Partial(int disassMode, vector<PuzConfig *> &graphConfigs)
{
    int graphState = DISASSEMBLY_GRAPH_REMOVABLE_PIECE;
    vector<PuzConfig*> remvRootConfigs;

    PuzConfig * targetConfig = NULL;

    // Find the last target node
    for (int i = 0; i < graphConfigs.size(); ++i)
    {
        if (graphConfigs[i]->configType == PUZ_CONFIG_TARGET){
            targetConfig = graphConfigs[i];
            break;
        }
    }

    if (targetConfig == NULL)
    {
        return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
    }

    while( true )
    {
        // The remaining puzzle pieces are removing together.
        if ( targetConfig->remvPieceIDs.size() == targetConfig->pieceIDList.size() and targetConfig->pieceIDList.size() > 1)
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("Error: the remaining puzzle pieces are removed together. \n\n");
#endif
            return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
        }

        // There is no removing piece.
        if ( targetConfig->remvPieceIDs.size() == 0 and targetConfig->pieceIDList.size() > 1)
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("Error: there is no removing piece. \n\n");
#endif
            return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
        }

        // Create a new local root config for further disassemble
        PuzConfig *locaRootConfig = new PuzConfig();
        targetConfig->RemovePieceIDs(targetConfig->remvPieceIDs, locaRootConfig);

        targetConfig->nextPuzConfigs.push_back(locaRootConfig);

        // Create a new removing root config
        PuzConfig *remvRootConfig = new PuzConfig();
        targetConfig->RemovePieceIDs(locaRootConfig->pieceIDList, remvRootConfig);

        targetConfig->nextPuzConfigs.push_back(remvRootConfig);


        if (remvRootConfig->pieceIDList.size() == 1)
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("Message: find a removing piece. \n\n");
#endif
            remvRootConfig->configType = PUZ_CONFIG_PIECE_ONLY;
            remvRootConfig->puzConfigID = graphConfigs.size();

            graphConfigs.push_back( remvRootConfig );
        }

        if (remvRootConfig->pieceIDList.size() > 1)
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("Warning: more than one puzzle piece is removed at a time. \n\n");
#endif

            remvRootConfigs.push_back(remvRootConfig);
        }

        if( locaRootConfig->pieceIDList.size() == 1 )
        {
            locaRootConfig->configType = PUZ_CONFIG_PIECE_ONLY;
            locaRootConfig->puzConfigID = graphConfigs.size();

            graphConfigs.push_back( locaRootConfig );

            break;
        }

        if ( locaRootConfig->pieceIDList.size() > 1 )
        {

            vector<PuzConfig*> locaGraphConfigs;

            int currGraphState = BuildPuzConfigGraph_Partial(disassMode, locaRootConfig, locaGraphConfigs, targetConfig);

            if( currGraphState != DISASSEMBLY_GRAPH_REMOVABLE_PIECE)
            {
#ifdef PRINT_DEBUG_MESSAGE
                printf("Warning: the remaining puzzle pieces cannot be disassembled \n\n");
#endif
                return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
            }

            for (int i = 0; i < locaGraphConfigs.size(); ++i)
            {
                locaGraphConfigs[i]->puzConfigID = graphConfigs.size();

                graphConfigs.push_back( locaGraphConfigs[i]);
            }

        }
    }


    for (int i = 0; i < remvRootConfigs.size(); ++i)
    {
        vector<PuzConfig*> remvGraphConfigs;
//        vector<PuzConfig*> remvPathConfigs;

        int currGraphState = BuildRemvPuzConfigGraph_Partial(disassMode, remvRootConfigs[i]);

        if( graphState == DISASSEMBLY_GRAPH_REMOVABLE_PIECE and currGraphState != DISASSEMBLY_GRAPH_REMOVABLE_PIECE )
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("Warning: the remaining puzzle pieces cannot be disassembled \n\n");
#endif
            graphState = DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
        }

        TracePuzConfigGraph(remvRootConfigs[i], remvGraphConfigs, true);

        for (int i = 0; i < remvGraphConfigs.size(); ++i)
        {
            remvGraphConfigs[i]->puzConfigID = graphConfigs.size();

            graphConfigs.push_back( remvGraphConfigs[i]);
        }
    }

    return graphState;
}

int PuzSolver::BuildPuzConfigGraph_Partial(int disassMode, PuzConfig* rootPuzConfig, vector<PuzConfig*> &graphConfigs, PuzConfig * &targetConfig)
{

    // Maximum number of puzConfigs that should be visited
    const int maxExistingConfigNum = 2000;

    // Push back the deep copied root config to BSF queue
    vector<PuzConfig *> visitedConfigs;
    vector<PuzConfig *> bfsConfigQueue;
    bfsConfigQueue.push_back(rootPuzConfig);

    vector<PuzConfig *> existingConfigs;
    existingConfigs.push_back(rootPuzConfig);

    targetConfig = NULL;

    while (bfsConfigQueue.size() > 0)
    {
        // Pop up the first PuzConfig in the BFS queue
        PuzConfig *currPuzConfig = bfsConfigQueue[0];
        bfsConfigQueue.erase(bfsConfigQueue.begin());

        if ( FindPuzConfigInList(currPuzConfig, visitedConfigs) == CONFIG_OUT_LIST )
            visitedConfigs.push_back(currPuzConfig);

        vector<int> remvPieceIDs;
        vector<int> remvAxisIDs;

        expVolume->BuildConfigContactGraph(currPuzConfig, pieceList);

        bool isRemovableGroup = DetermineNextConfigs(*currPuzConfig, disassMode, remvPieceIDs,remvAxisIDs, existingConfigs);

        if (existingConfigs.size() > maxExistingConfigNum)
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("Warning: More than %d existing configs in the graph! \n\n", maxExistingConfigNum);
#endif
            return DISASSEMBLY_GRAPH_TOO_LARGE;
        }

        if (isRemovableGroup)
        {
            targetConfig = currPuzConfig;

            targetConfig->configType   = PUZ_CONFIG_PIECE_REMOVE;
            targetConfig->remvPieceIDs = remvPieceIDs;
            targetConfig->remvAxisIDs  = remvAxisIDs;

//            targetConfig->nextPuzConfigs.push_back(currPuzConfig);

            /*printf("remove pieces: ");
            for (int i = 0; i < remvPieceIDs.size(); ++i)
            {
                printf("  %d  ", remvPieceIDs[i]);
            }
            printf("\n");*/

            break;
        }
        else
        {
            // Push back the next PuzConfigs into the BSF queue
            for (int i = 0; i < currPuzConfig->nextPuzConfigs.size(); i++)
            {
                if( FindPuzConfigInList(currPuzConfig->nextPuzConfigs[i], visitedConfigs) == CONFIG_OUT_LIST )
                {
                    bfsConfigQueue.push_back(currPuzConfig->nextPuzConfigs[i]);
                }
            }
        }
    }

    if( targetConfig == NULL )
    {
        //printf("no piece removable \n");
        return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
    }
    else
    {
        TracePuzConfigGraph(rootPuzConfig, graphConfigs, true);

        return DISASSEMBLY_GRAPH_REMOVABLE_PIECE;
    }
}

int PuzSolver::BuildRemvPuzConfigGraph_Partial(int disassMode, PuzConfig *rootPuzConfig)
{
    int graphState = DISASSEMBLY_GRAPH_REMOVABLE_PIECE;
    // Maximum number of puzConfigs that should be visited
    const int maxExistingConfigNum = 2000;

    // Push back the deep copied root config to BSF queue
    vector<PuzConfig *> visitedConfigs;
    vector<PuzConfig *> bfsConfigQueue;
    bfsConfigQueue.push_back(rootPuzConfig);

    vector<PuzConfig *> existingConfigs;
    existingConfigs.push_back(rootPuzConfig);

    PuzConfig * targetConfig = NULL;

    while (bfsConfigQueue.size() > 0)
    {
        // Pop up the first PuzConfig in the BFS queue
        PuzConfig *currPuzConfig = bfsConfigQueue[0];
        bfsConfigQueue.erase(bfsConfigQueue.begin());

        if ( FindPuzConfigInList(currPuzConfig, visitedConfigs) == CONFIG_OUT_LIST )
            visitedConfigs.push_back(currPuzConfig);

        vector<int> remvPieceIDs;
        vector<int> remvAxisIDs;

//        currPuzConfig->PrintPuzConfig(false);
        expVolume->BuildConfigContactGraph(currPuzConfig, pieceList);

        bool isRemovableGroup = DetermineNextConfigs(*currPuzConfig, disassMode, remvPieceIDs,remvAxisIDs, existingConfigs);

        if (existingConfigs.size() > maxExistingConfigNum)
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("Warning: More than %d existing configs in the graph! \n\n", maxExistingConfigNum);
#endif
            return DISASSEMBLY_GRAPH_TOO_LARGE;
        }

        if (isRemovableGroup)
        {
//            printf("Removable pieces: ");
//            for (int i = 0; i < remvPieceIDs.size(); ++i)
//            {
//                printf("  %d  ", remvPieceIDs[i]);
//            }
//            printf("\n");

            targetConfig = currPuzConfig;

            targetConfig->configType   = PUZ_CONFIG_PIECE_REMOVE;
            targetConfig->remvPieceIDs = remvPieceIDs;
            targetConfig->remvAxisIDs  = remvAxisIDs;

            PuzConfig *locaRootConfig = new PuzConfig();
            targetConfig->RemovePieceIDs(remvPieceIDs, locaRootConfig);

            targetConfig->nextPuzConfigs.push_back(locaRootConfig);

            if (locaRootConfig->pieceIDList.size() == 1)
            {
                locaRootConfig->configType = PUZ_CONFIG_PIECE_ONLY ;
            }

            if (locaRootConfig->pieceIDList.size() > 1)
            {
//                locaRootConfig->nextPuzConfigs.push_back(targetConfig);

                int currGraphState = BuildRemvPuzConfigGraph_Partial(disassMode, locaRootConfig);

                if (graphState == DISASSEMBLY_GRAPH_REMOVABLE_PIECE and currGraphState != DISASSEMBLY_GRAPH_REMOVABLE_PIECE)
                {
                    graphState = DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
                }
            }

            PuzConfig *remvRootConfig = new PuzConfig();
            targetConfig->RemovePieceIDs(locaRootConfig->pieceIDList, remvRootConfig);

            targetConfig->nextPuzConfigs.push_back(remvRootConfig);

            if (remvRootConfig->pieceIDList.size() == 1)
            {
                remvRootConfig->configType = PUZ_CONFIG_PIECE_ONLY ;
            }

            if (remvRootConfig->pieceIDList.size() > 1)
            {
//                remvRootConfig->nextPuzConfigs.push_back(targetConfig);

                int currGraphState = BuildRemvPuzConfigGraph_Partial(disassMode, remvRootConfig);

                if (graphState == DISASSEMBLY_GRAPH_REMOVABLE_PIECE and currGraphState != DISASSEMBLY_GRAPH_REMOVABLE_PIECE)
                {
                    graphState = DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
                }
            }

            break;
        }
        else
        {
            // Push back the next PuzConfigs into the BSF queue
            for (int i = 0; i < currPuzConfig->nextPuzConfigs.size(); i++)
            {
                if( FindPuzConfigInList(currPuzConfig->nextPuzConfigs[i], visitedConfigs) == CONFIG_OUT_LIST )
                {
                    bfsConfigQueue.push_back(currPuzConfig->nextPuzConfigs[i]);
                }
            }
        }
    }

    if( graphState == DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE)
    {
        //printf("no piece removable \n");
        return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
    }
    else
    {
        if( targetConfig == NULL )
        {
            //printf("no piece removable \n");
            return DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE;
        }

        return DISASSEMBLY_GRAPH_REMOVABLE_PIECE;
    }
}

bool PuzSolver::DetermineNextConfigs(PuzConfig &puzConfig, int disassMode, vector<int> &remvPieceIDs, vector<int> &remvPieceAxisIDs, vector<PuzConfig*> &existingConfigs)
{
    ////////////////////////////////////////////////////////////////
    // Detect if there exists any movable / removable group of pieces

    int configPieceNum = puzConfig.pieceIDList.size();

    PieceGroup *currPieceGroup = new PieceGroup();

    for ( int m=1; m<= pow(2.0, configPieceNum-1)-1; m++ )
    {
        /////////////////////////////////////////////////////////////
        // Generate a possible combination
        vector<int> pieceIDIndices;

        vector<bool> selectPiece = vector<bool>(configPieceNum, false);
        GetPieceCombination(configPieceNum, m, selectPiece, disassMode);

        /////////////////////////////////////////////////////////////
        // Build the group pieces
        currPieceGroup->ClearGroup();

        for (int i=0; i<selectPiece.size(); i++)
        {
            int pieceID       = puzConfig.pieceIDList[i];
            Vector3i piecePos = puzConfig.piecePosList[i];

            if ( selectPiece[i] )
            {
                currPieceGroup->AddPiece(pieceList[pieceID], piecePos);
                pieceIDIndices.push_back(i);
            }
        }

        /////////////////////////////////////////////////////////////
        // Motion analysis of current piece group
        bool isGroupConnected = currPieceGroup->CheckGroupConnectivity();

        if ( isGroupConnected )
        {
            currPieceGroup->ComputeGroupFace();
            currPieceGroup->ComputeNeighborPiece();
            currPieceGroup->ComputeMovableAxis();

            // Detect any removable piece/group
            vector<int> remvAxisIDs;
            for (int i=0; i<currPieceGroup->movableAxis.size(); i++)
            {
                int axisID = currPieceGroup->movableAxis[i];

                bool isGroupRemovable = GroupRemovableAlongAxis(currPieceGroup, axisID);
                if ( isGroupRemovable )
                {
                    remvAxisIDs.push_back( axisID );
                }
            }

            // If there exist any removable piece/group
            if ( remvAxisIDs.size() > 0 )
            {
                remvPieceIDs     = currPieceGroup->pieceIDList;
                remvPieceAxisIDs = remvAxisIDs;

                delete currPieceGroup;

                return true;
            }

            // Else, compute next PuzConfigs
            else
            {
                ComputeNextPuzConfigs(puzConfig, existingConfigs, pieceIDIndices, currPieceGroup);
            }
        }
    }

    delete currPieceGroup;

    return false;
}

bool PuzSolver::GroupRemovableAlongAxis(PieceGroup *currPieceGroup, int axisID)
{
    ////////////////////////////////////////////////////////////////
    /// The tested pieceGroup should be movable along axisID

    if( currPieceGroup->pieceFace[axisID].contactVoxel.size() > 0 )
    {
        int contactPieceID = currPieceGroup->pieceFace[axisID].contactVoxel[0]->piece;
        printf("Error: The tested pieceGroup is not movable along axis %s blocked by piece %d! \n", axisArray[axisID], contactPieceID);
        return false;
    }


    ////////////////////////////////////////////////////////////////
    /// The removable pieceGroup should not have any (far away) blocking voxel along axisID

    int moveStep = 1;

    while( true )
    {
        bool isOutExpVolume;
        bool isOverlap = IsVoxelOverlap(currPieceGroup, axisID, moveStep, isOutExpVolume);

        if( isOverlap )
        {
            return false;
        }

        if( isOutExpVolume )
        {
            return true;
        }

        moveStep++;
    }
}

void PuzSolver::ComputeNextPuzConfigs(PuzConfig &puzConfig, vector<PuzConfig*> &existingConfigs, vector<int> currPieceIDIndices, PieceGroup *currPieceGroup)
{
    for (int i=0; i<currPieceGroup->movableAxis.size(); i++)
    {
        int moveAxisID = currPieceGroup->movableAxis[i];

        int moveStep = 1;

        while( true )
        {
            bool isOutExpVolume;
            bool isOverlap = IsVoxelOverlap(currPieceGroup, moveAxisID, moveStep, isOutExpVolume);

            if( isOverlap )
            {
                break;
            }

            puzConfig.CreateNextConfig(currPieceIDIndices, moveAxisID, moveStep, existingConfigs);

            moveStep++;
        }
    }
}

bool PuzSolver::IsVoxelOverlap(PieceGroup *currPieceGroup, int axisID, int moveStep, bool &isOutExpVolume)
{
    for (int i=0; i<currPieceGroup->pieceFace[axisID].surfaceVoxel.size(); i++)
    {
        int pieceID = currPieceGroup->pieceFace[axisID].surfaceVoxel[i]->piece;
        int pieceIndex = GetPieceIndexInList(currPieceGroup->pieceIDList, pieceID);
        Vector3i piecePos = currPieceGroup->piecePosList[pieceIndex];

        Vector3i expVoxelPos = expVolume->Org2ExpVoxel(currPieceGroup->pieceFace[axisID].surfaceVoxel[i]->pos + piecePos);

        Vector3i tempExpVoxelPos = expVoxelPos + moveStep * neiborPos[axisID];

        /// TODO: need to check if this condition is sufficient
        if (expVolume->VoxelInsideExpVolume(tempExpVoxelPos, EXPA_VOLUME) == false)
        {
            isOutExpVolume = true;
            return false;
        }

        Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(tempExpVoxelPos, EXPA_VOLUME);
        if (tempExpVoxel->piece != NONE_PIECE &&
            std::find(currPieceGroup->pieceIDList.begin(), currPieceGroup->pieceIDList.end(), tempExpVoxel->piece) == currPieceGroup->pieceIDList.end())
        {
            return true;
        }
    }

    return false;
}

void PuzSolver::TracePuzConfigGraph(PuzConfig *rootConfig, vector<PuzConfig*> &graphConfigs, bool isMarkSequenceID)
{
    //////////////////////////////////////////////////////////////////////////
    /// 1. Find all puzConfigs in the graph using breadth-first search

    vector<PuzConfig*> bfsConfigQueue;
    vector<PuzConfig*> visitedConfigs;

    bfsConfigQueue.push_back(rootConfig);

    while (bfsConfigQueue.size()>0)
    {
        PuzConfig *currPuzConfig = bfsConfigQueue[0];
        bfsConfigQueue.erase( bfsConfigQueue.begin() );

        if( currPuzConfig->isTraced == false  )
        {
            currPuzConfig->isTraced = true;
            visitedConfigs.push_back( currPuzConfig );
        }

        for (int i=0; i<currPuzConfig->nextPuzConfigs.size(); i++)
        {
            PuzConfig *nextPuzConfig = currPuzConfig->nextPuzConfigs[i];

            if( nextPuzConfig->isTraced == false )
            {
                bfsConfigQueue.push_back( nextPuzConfig );
            }

        }
    }

    graphConfigs = visitedConfigs;


    //////////////////////////////////////////////////////////////////////////
    /// 2. Assign an ID to each puzConfig in the list

    if (isMarkSequenceID)
    {
        for (int i = 0; i < graphConfigs.size(); ++i)
        {
            PuzConfig *puzConfig = graphConfigs[i];
            puzConfig->puzConfigID = i;
        }
    }

}




///=========================================================================================///
///                               Compute Puzzle Level
///=========================================================================================///

void PuzSolver::ComputePuzzleLevel(vector<PuzConfig*> targetConfigs, int &puzzleLevel)
{
    int minDist = MAX_INT;
    int minDistTargetConfigIndex = -1;
    for (int i = 0; i < targetConfigs.size(); i++)
    {
        if (targetConfigs[i]->distToRoot < minDist)
        {
            minDist = targetConfigs[i]->distToRoot;

            minDistTargetConfigIndex = i;
        }
    }

    PuzConfig *minDistTargetConfig;
    if (minDistTargetConfigIndex != -1)
    {
        minDistTargetConfig = targetConfigs[minDistTargetConfigIndex];
        //minDistTargetConfig->type = PUZ_CONFIG_SHORTEST_PATH;
    }

    minDistTargetConfig->configType = PUZ_CONFIG_TARGET;

    vector<PuzConfig*> pathConfigs;
    ComputeShortestPathConfigs(minDistTargetConfig, pathConfigs);

    puzzleLevel = pathConfigs.size();

    //printf("puzzle level: %d \n", puzzleLevel);
}


void PuzSolver::ComputeShortestDistanceToRootConfig(vector<PuzConfig*> graphConfigs, int rootConfigIndex)
{
    int configNum = graphConfigs.size();
    std::vector<PuzConfig*> bfsQueue;
    std::vector<bool> visited(configNum, false);

    // Find a root for Breadth-First Search Traversal
    PuzConfig *rootConfig;
    rootConfig = graphConfigs[rootConfigIndex];
    rootConfig->distToRoot = 0;
    visited[rootConfigIndex] = true;
    bfsQueue.push_back(rootConfig);

    // Start Breadth-First Search Traversal
    while( !bfsQueue.empty() )
    {
        PuzConfig *currVisit = bfsQueue[0];
        bfsQueue.erase( bfsQueue.begin() );
        PuzConfig *nextVisit;

        for (int i=0; i<currVisit->nextPuzConfigs.size(); i++)
        {
            PuzConfig *nextPuzConfig = currVisit->nextPuzConfigs[i];

            int index = FindPuzConfigInList(nextPuzConfig, graphConfigs);
            if( index != VOXEL_OUT_LIST )
            {
                nextVisit = graphConfigs[index];
                if( !visited[index] )
                {
                    visited[index] = true;
                    bfsQueue.push_back(nextVisit);
                    nextVisit->distToRoot = currVisit->distToRoot + 1;
                }
            }
        }
    }
}

void PuzSolver::ComputeShortestPathConfigs(PuzConfig* targetConfig, vector<PuzConfig*> &pathConfigs)
{
    // Find the shortest path from the root node to the removable node.
    PuzConfig* currConfig = targetConfig;
    int currDist = currConfig->distToRoot;

    //printf("currDist: %d \n", currDist);

    pathConfigs.push_back(currConfig);

    while (currDist > 0)
    {
//        printf("currDist: %d \n", currDist);
        for (int i = 0; i < currConfig->nextPuzConfigs.size(); ++i)
        {
            PuzConfig *nextConfig = currConfig->nextPuzConfigs[i];

            //printf("currDist_1: %d \n", currConfig->nextPuzConfigs[i]->distToRoot);

            if (nextConfig->distToRoot == currDist - 1)
            {
                pathConfigs.push_back(nextConfig);

                currConfig = nextConfig;

                currDist--;
                break;
            }
        }
    }
}

void PuzSolver::ComputeShortestPathConfigs(PuzConfig* targetConfig, vector<PuzConfig*> graphConfigs, vector<PuzConfig*> &pathConfigs)
{
    // Find the shortest path from the root node to the removable node.
    PuzConfig* currConfig = targetConfig;
    int currDist = currConfig->distToRoot;

    pathConfigs.push_back(currConfig);

//    printf("currDist: %d \n", currDist);

//    printf("Size of graphConfigs: %lu\n", graphConfigs.size());
    while (currDist > 0)
    {
//        printf("currDist: %d \n", currDist);
        for (int i = 0; i < graphConfigs.size(); ++i)
        {
            PuzConfig *nextConfig = graphConfigs[i];

//            printf("currDist_1: %d \n", graphConfigs[i]->distToRoot);

            if (nextConfig->distToRoot == currDist - 1 and std::find(nextConfig->nextPuzConfigs.begin(), nextConfig->nextPuzConfigs.end(), currConfig) != nextConfig->nextPuzConfigs.end())
            {
                pathConfigs.push_back(nextConfig);

                currConfig = nextConfig;

                currDist--;
                break;
            }
        }
    }
}

void PuzSolver::ComputeShortestPathConfigs(PuzConfig* rootConfig, PuzConfig* targetConfig, vector<PuzConfig*> graphConfigs, vector<PuzConfig*> &pathConfigs)
{
    // Find the shortest path from the root node to the removable node.
    PuzConfig* currConfig = targetConfig;
    int currDist = currConfig->distToRoot;

    pathConfigs.push_back(currConfig);

    while (currDist != rootConfig->distToRoot)
    {
//        printf("currDist: %d \n", currDist);
        for (int i = 0; i < graphConfigs.size(); ++i)
        {
            PuzConfig *nextConfig = graphConfigs[i];

//            printf("currDist_1: %d \n", graphConfigs[i]->distToRoot);

            if (nextConfig->distToRoot == currDist - 1 and std::find(nextConfig->nextPuzConfigs.begin(), nextConfig->nextPuzConfigs.end(), currConfig) != nextConfig->nextPuzConfigs.end())
            {
                pathConfigs.push_back(nextConfig);

                currConfig = nextConfig;

                currDist--;
                break;
            }
        }
    }
}



///=========================================================================================///
///                              Puzzle Config/Action Operations
///=========================================================================================///

vector<int> PuzSolver::GetPieceIDList()
{
    vector<int> pieceIDList;
    for (int i=0; i<pieceList.size(); i++)
        pieceIDList.push_back(pieceList[i]->pieceID);

    return pieceIDList;
}

int PuzSolver::GetPieceIndex(int tagtPieceID, vector<int> pieceIDList)
{
    for (int i = 0; i < pieceIDList.size(); ++i)
    {
        if( pieceIDList[i] == tagtPieceID )
            return i;
    }

    return -1;
}

int PuzSolver::FindPuzConfigInList(PuzConfig *tagtPuzConfig, vector<PuzConfig *> puzConfigList)
{
    for (int i=0; i<puzConfigList.size(); i++)
    {
        if ( *tagtPuzConfig == *puzConfigList[i] )
        {
            return i;
        }
    }

    return CONFIG_OUT_LIST;
}
