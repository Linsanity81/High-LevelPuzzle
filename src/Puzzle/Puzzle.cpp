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
///////////////////////////////////////////////////////////////

#include <iostream>
#include "Mesh/MeshObject.h"
#include "Mesh/MeshBoolean.h"
#include "pugixml.hpp"
#include "Utility/HelpFunc.h"
#include "PuzConverter/PuzConverter.h"
#include "PuzConverter/ObjPuzzle.h"
#include "PieceFace.h"
#include "Piece.h"
#include "PieceGroup.h"
#include "PuzAction.h"
#include "PuzConfig.h"
#include "PuzSolver.h"
#include "PieceCreator.h"
#include "Volume.h"
#include "Puzzle.h"
#include "Mesh/Mesh.h"
#include "igl/writeOBJ.h"
#include <algorithm>

extern Vector3i neiborPos[6];
extern char axisArray[6][4];


///=========================================================================================///
///                                   Initialization
///=========================================================================================///

Puzzle::Puzzle()
{
	volume = NULL;

	puzLockState   = PUZZLE_LOCK_UNKNOWN;
	puzBuildState  = PUZZLE_BUILD_UNKNOWN;
	puzLevel  = 0;
	puzTotalMoves = 0;

    puzDisconnectivityState = false;

    generationTime = 0;

    dissComplexity = 0;

    kernalGraphConfigNum = 0;
}

Puzzle::~Puzzle()
{
	ClearPuzzle();
}

void Puzzle::ClearPuzzle()
{
    if ( volume != NULL )
    {
        delete volume;
        volume = NULL;
    }

	for (int i=0; i<pieceList.size(); i++)
		delete pieceList[i];
	pieceList.clear();

//	disconnectedEdgeList.clear();

    puzLockState   = PUZZLE_LOCK_UNKNOWN;
    puzBuildState  = PUZZLE_BUILD_UNKNOWN;
    puzLevel  = 0;
    puzTotalMoves = 0;

    puzDisconnectivityState = false;

    generationTime = 0;

    dissComplexity = 0;

    kernalGraphConfigNum = 0;

    smoothPieceVerticeList.clear();
    smoothPieceFaceList.clear();
}

Puzzle & Puzzle::operator=(const Puzzle & puzzle)
{
    ClearPuzzle();

    volume = new Volume();
    *this->volume = *puzzle.volume;

    for (int i = 0; i < puzzle.pieceList.size(); i++)
    {
        Piece *piece = new Piece();
        *piece = *puzzle.pieceList[i];
        this->pieceList.push_back( piece );
    }

    this->puzLockState = puzzle.puzLockState;
    this->puzBuildState = puzzle.puzBuildState;
    this->puzLevel = puzzle.puzLevel;

    this->puzDisconnectivityState = puzzle.puzDisconnectivityState;

    this->generationTime = puzzle.generationTime;

    this->dissComplexity = puzzle.dissComplexity;

    this->kernalGraphConfigNum = puzzle.kernalGraphConfigNum;

    return *this;
};

void Puzzle::SetVolume(Volume* _volume)
{
    if( volume != NULL )
    {
        delete volume;
        volume = NULL;
    }

    volume = new Volume();

    *volume = *_volume;
}

void Puzzle::PrintPuzzle()
{
    printf("[ ");
    for (int i=0; i<volume->GetVoxelGrid().size(); i++)
    {
        printf(" %d ", volume->GetVoxelGrid()[i]->piece + 1);

        //printf("Voxel [%f %f %f]  Piece [%d] Neighbor [%d %d %d %d %d %d] \n",
        //       voxelGrid[i]->center(X_INFO), voxelGrid[i]->center(Y_INFO), voxelGrid[i]->center(Z_INFO), voxelGrid[i]->piece,
        //       voxelGrid[i]->neiborPiece[0], voxelGrid[i]->neiborPiece[1], voxelGrid[i]->neiborPiece[2],
        //       voxelGrid[i]->neiborPiece[3], voxelGrid[i]->neiborPiece[4], voxelGrid[i]->neiborPiece[5]);
    }
    printf("] ");

    printf("Lock: %d  Build: %d  F_Level: %d ", puzLockState, puzBuildState, puzLevel);

    printf("\n");
}




///=========================================================================================///
///               Check Puzzle States (Interlocking, Buildable, and Levels)
///=========================================================================================///

int Puzzle::CheckPuzzleState(bool isPrint, bool isFixLastPiece)
{

	// Check if the puzzle is interlocking
    puzLockState = CheckPuzzleLockState();

    // Timer
    clock_t beginTime = clock();
    clock_t endTime;
    float elapsed;

    // graphConfigs
    vector<PuzConfig*> graphPuzConfigs;
    vector<PuzConfig*> pathPuzConfigs;

    // Puzzle Solver
    PuzSolver puzSolver;
    int expVolumeScalarSize = 1;

    puzSolver.InitPuzSolver(pieceList, volume->GetVolumeSize(), expVolumeScalarSize);

    puzBuildState = puzSolver.DisassemblyPuzzzle_Graph(DISASS_FIX_LAST_PIECE, graphPuzConfigs, pathPuzConfigs, puzLevel);

    kernalGraphConfigNum = 0;
//    printf("pieceList Size: %lu\n", pieceList.size());
    for (int i = 0; i < graphPuzConfigs.size(); ++i)
    {
        if (graphPuzConfigs[i]->pieceIDList.size() == pieceList.size())
            kernalGraphConfigNum++;
    }

    if (puzBuildState == PUZZLE_NORMAL_BUILDABLE)
    {
        while(1)
        {
            expVolumeScalarSize += 1;
//            printf("currExpScalarSize: %d\n", expVolumeScalarSize);

            PuzSolver currPuzSolver;
            currPuzSolver.InitPuzSolver(pieceList, volume->GetVolumeSize(), expVolumeScalarSize);

            int currPuzBuildState;
            int currPuzLevel;
            vector<PuzConfig*> currGraphPuzConfigs;
            vector<PuzConfig*> currPathPuzConfigs;

            currPuzBuildState = currPuzSolver.DisassemblyPuzzzle_Graph(DISASS_FIX_LAST_PIECE, currGraphPuzConfigs, currPathPuzConfigs, currPuzLevel);

            if (currPuzLevel == puzLevel)
            {
                break;
            }
            else
            {
                graphPuzConfigs.clear();
                pathPuzConfigs.clear();

                graphPuzConfigs = currGraphPuzConfigs;
                pathPuzConfigs = currPathPuzConfigs;

                puzLevel = currPuzLevel;
            }
        }
    }

//    printf("currExpScalarSize: %d\n", expVolumeScalarSize - 1);

    puzGraphConfigsNum = graphPuzConfigs.size();

    endTime = clock();
    elapsed = ((float) (endTime - beginTime)) / (CLOCKS_PER_SEC); // Time unit: second
    //printf("Time used to compute the disassembly graph: %.6f\n", elapsed);

#ifdef COMPUTE_KERNAL_GRAPH_ONLY
    vector<vector<int>> edgeList;
//    int kernalGraphConfigNum = 0;
    int targetNodeNum = 0;

    // Check the number of edge in disassembly graph and the number of target nodes
    for (int i = 0; i < graphPuzConfigs.size(); ++i)
    {
        if (graphPuzConfigs[i]->configType == PUZ_CONFIG_TARGET_CANDI or graphPuzConfigs[i]->configType == PUZ_CONFIG_TARGET)
            targetNodeNum++;

        for (int j = 0; j < graphPuzConfigs[i]->nextPuzConfigs.size(); ++j)
        {
            vector<int> currEdge;
            currEdge.push_back(graphPuzConfigs[i]->puzConfigID);
            currEdge.push_back(graphPuzConfigs[i]->nextPuzConfigs[j]->puzConfigID);
            sort(currEdge.begin(), currEdge.end());

            if (find(edgeList.begin(), edgeList.end(), currEdge) == edgeList.end())
            {
                edgeList.push_back(currEdge);
//                printf("currEdge: %d %d\n", currEdge[0], currEdge[1]);
            }
        }
    }

    kernalGraphConfigNum = graphPuzConfigs.size();
#endif

    if( isPrint )
    {
        printf("\n");
        printf("Piece Num:    %lu\n", pieceList.size());
        printf("Puzzle Level: %d\n", puzLevel);
        printf("PuzLockState: %d \n", puzLockState);
        printf("graphPuzConfigs num: %lu\n", graphPuzConfigs.size());
        printf("pathPuzConfigs num:  %lu\n", pathPuzConfigs.size());

#ifdef COMPUTE_KERNAL_GRAPH_ONLY
        printf("\n\n");
        printf("kernal graph config num: %lu\n", graphPuzConfigs.size() + targetNodeNum);
        printf("kernal graph edge num: %lu\n", edgeList.size() + targetNodeNum);
        printf("target node num: %d\n", targetNodeNum);
#endif
    }

    puzActionList.clear();
    puzSolver.ComputeDisassemblyPlan(pathPuzConfigs, puzActionList, isFixLastPiece);

    dissComplexity = 0;

//    printf("size of puzActionList : %lu\n", puzActionList.size());
    if (puzActionList.size() > 1)
    {
        for (int i = 1; i < puzLevel - 1; ++i)
        {
            PuzAction currAction = puzActionList[i];
            PuzAction prevAction = puzActionList[i - 1];

            if (currAction.movePieceIDs != prevAction.movePieceIDs)
            {
//            printf("-----------------------------------\n");
//            currAction.PrintPuzAction();
//            prevAction.PrintPuzAction();
//            printf("-----------------------------------\n");
                dissComplexity++;
            }
        }
    }
//    printf("dissComplexity: %d\n", dissComplexity);

#ifdef SHOW_INFO
    for (int i = 0; i < puzActionList.size(); ++i)
    {
        puzActionList[i].PrintPuzAction();
    }
#endif

    int pathPuzConfigsSize = pathPuzConfigs.size();

    for (int i = 0; i < graphPuzConfigs.size(); ++i)
    {
        delete graphPuzConfigs[i];
    }

    return  pathPuzConfigsSize;
}

bool Puzzle::CheckValidPuzzle()
{
    // Case 1: Each puzzle piece has at least one voxel
    for (int i=0; i<pieceList.size(); i++)
    {
        if( pieceList[i]->voxelList.size() == 0 )
        {

#ifdef SHOW_INFO
            printf("Invalid Puzzle Case 1: There exists an empty puzzle piece \n");
#endif
            return false;
        }
    }

    // Case 2: Check connectivity of each puzzle piece
    for (int i=0; i<pieceList.size(); i++)
    {
        int pieceID = pieceList[i]->pieceID;
        bool isPieceConnected = pieceList[pieceID]->CheckConnectivity();

        if( !isPieceConnected )
        {
#ifdef SHOW_INFO
            printf("Piece %2d is disconnected! \n", pieceID);
#endif
            //pieceList[i]->PrintPieceInfo();
            return false;
        }
    }
#ifdef SHOW_INFO
    printf("The puzzle is valid! \n");
#endif
    return true;
}

vector<Eigen::MatrixXf> Puzzle::GetPieceAssemblyPos(int disassemblyStateID)
{
    /////////////////////////////////////////////////////////////////
    /// 0. Initialization

    vector<Eigen::MatrixXf> posVectors;
    for (int i = 0; i < pieceList.size(); ++i)
    {
        Eigen::MatrixXf piecePos(1, 3);
        piecePos(0) = 0;
        piecePos(1) = 0;
        piecePos(2) = 0;
        posVectors.push_back(piecePos);
    }

    /////////////////////////////////////////////////////////////////
    /// 1. Move the puzzle pieces to the current disassembly state

    for (int i = 0; i < disassemblyStateID; i++)
    {
        if( disassemblyStateID > puzActionList.size() )
        {
            printf("Warning: the disassembly step ID exceeds its range. \n\n");
            break;
        }

        /// Compute the moveVector for a movable/removable pieceGroup
        PuzAction puzAction = puzActionList[i];

        vector<int> actualMovePieceIDs;
        Vector3f actualMoveVector;
        puzAction.GetPieceGroupMoveVector(volume->volumeSize, volume->voxelSize, actualMovePieceIDs, actualMoveVector);

        /// Update puzzle piece positions according to the moveVector
        for (int j = 0; j < actualMovePieceIDs.size(); ++j)
        {
            int pieceID = actualMovePieceIDs[j];

            for (int l = 0; l < 3; l++)
            {
                posVectors[pieceID](l) += actualMoveVector(l);
            }
        }
    }

//    for (int i = 0; i < pieceList.size(); ++i)
//    {
//        std::cout << posVectors[i] << std::endl;
//    }

    return posVectors;
}


///=========================================================================================///
///                               Test Global Interlocking
///=========================================================================================///

int Puzzle::CheckPuzzleLockState()
{
    BuildPuzzleContactGraph();

    ////////////////////////////////////////////////////////////////
    // Detect if there exists any movable group of pieces

    int puzPieceNum = pieceList.size();
    PieceGroup *pieceGroup = new PieceGroup();

    int movePieceNum = 0;
    int moveGroupNum = 0;
    vector<int> pieceMovableAxes;

    for ( int m=1; m<= pow(2.0, puzPieceNum-1)-1; m++ )
    {
        /////////////////////////////////////////////////////////////
        // Generate a possible combination
        vector<int> pieceIDIndices;
        vector<bool> selectPiece = vector<bool>(puzPieceNum, false);
        int trueCounter = GetPieceCombination(puzPieceNum, m, selectPiece, DISASS_FIX_LAST_PIECE);

        /////////////////////////////////////////////////////////////
        // Build the group pieces
        pieceGroup->ClearGroup();
        for (int i=0; i<selectPiece.size(); i++)
        {
            if ( selectPiece[i] )
            {
                Piece *piece = pieceList[i];
                pieceGroup->AddPiece( piece );
                pieceIDIndices.push_back(i);
            }
        }

        /////////////////////////////////////////////////////////////
        // Motion analysis of current group
        pieceGroup->ComputeGroupFace();
        pieceGroup->ComputeNeighborPiece();
        pieceGroup->ComputeMovableAxis();
        //pieceGroup->PrintGroupInfo();

        if ( pieceGroup->movableAxis.size() > 0 )
        {
            // Number of movable single piece
            if ( pieceGroup->pieceIDList.size() == 1 )
            {
                movePieceNum++;
                pieceMovableAxes = pieceGroup->movableAxis;

                if ( movePieceNum >= 2)
                    break;
            }

                // Number of movable pieceGroup with at least two pieces
            else
            {
                moveGroupNum++;
                break;
            }
        }
    }

    //printf("movePieceNum: %d \n", movePieceNum);
    //printf("moveGroupNum: %d \n", moveGroupNum);

    delete pieceGroup;

    int configLockState = GetPuzLockState(puzPieceNum, movePieceNum, moveGroupNum, pieceMovableAxes);
    return configLockState;
}

void Puzzle::BuildPuzzleContactGraph()
{
    // Build contacting graph at voxel level
    //printf("Ready to compute contace piece.\n");

    volume->ComputeVoxelContactPiece(pieceList);

    //printf("Voxel contact piece has been computed.\n");

    for (int i=0; i<pieceList.size(); i++)
    {
        Piece *piece = pieceList[i];

        // Build contacting graph at pieceFace level
        piece->ComputePieceFace();

        // Build contacting graph at piece level
        piece->ComputeNeighborPiece();

        // Check each piece's motion space
        //if( isCheckMovableAxis )
        //    piece->ComputeMovableAxis();
    }
}

int Puzzle::GetPuzLockState(int pieceNum, int movePieceNum, int moveGroupNum, vector<int> pieceMovableAxes)
{
    int lockState;

    if ( movePieceNum == 0 && moveGroupNum == 0 )
    {
        lockState = PUZZLE_DEAD_LOCK;
        //printf("Puzzle State: Dead_Lock \n\n");
    }
    else if( movePieceNum == 1 && moveGroupNum == 0 )
    {
        if( pieceNum == 2 )
        {
            lockState = PUZZLE_PIECE_MOVE;
            //printf("Puzzle State: Piece_Move \n\n");
        }
        else
        {
            if( MovableAxesTest(pieceMovableAxes) )
            {
                lockState = PUZZLE_INTER_LOCK;
                //printf("Puzzle State: Inter_Lock \n\n");
            }
            else
            {
                lockState = PUZZLE_PIECE_MOVE;
                //printf("Puzzle State: Piece_Move \n\n");
            }

        }
    }
    else if( movePieceNum == 0 && moveGroupNum > 0 )
    {
        lockState = PUZZLE_GROUP_MOVE;
        //printf("Puzzle State: Group_Move \n\n");
    }
    else
    {
        lockState = PUZZLE_PIECE_MOVE;
        //printf("Puzzle State: Piece_Move \n\n");
    }

    return lockState;
}


///=========================================================================================///
///                                   Puzzle Rendering Data
///=========================================================================================///

void Puzzle::CreatePuzzleGeometry(vector<Eigen::MatrixXf> &voxelMinPtsList,
                                 vector<Eigen::MatrixXf> &voxelMaxPtsList,
                                 vector<Eigen::MatrixXf> &voxelCenPtsList,
                                 vector<Eigen::MatrixXf> &cylinTopPtsList,
                                 vector<Eigen::MatrixXf> &cylinBotPtsList,
                                 int disassStateID)
{
    /////////////////////////////////////////////////////////////////
    /// 1. Create rendering data for the puzzle at the default pose

    voxelMinPtsList.resize(pieceList.size());
    voxelMaxPtsList.resize(pieceList.size());
    voxelCenPtsList.resize(pieceList.size());

    cylinTopPtsList.resize(pieceList.size());
    cylinBotPtsList.resize(pieceList.size());

    Vector3f voxelSize = volume->GetVoxelSize();
    Vector3i volumeSize = volume->GetVolumeSize();

    Vector3f puzTransVec;
    puzTransVec(0) = -0.5f*(volumeSize(0) - 1) * voxelSize(0);
    puzTransVec(1) = -0.5f*(volumeSize(1) - 1) * voxelSize(1);
    puzTransVec(2) = -0.5f*(volumeSize(2) - 1) * voxelSize(2);

    for (int i = 0; i < pieceList.size(); i++)
    {
        pieceList[i]->CreatePieceGeometry(puzTransVec, voxelMinPtsList[i], voxelMaxPtsList[i], voxelCenPtsList[i], cylinTopPtsList[i], cylinBotPtsList[i]);
    }


    /////////////////////////////////////////////////////////////////
    /// 2. Move the puzzle pieces to the current disassembly state

    for (int i = 0; i < disassStateID; i++)
    {
        if( disassStateID > puzActionList.size() )
        {
            printf("Warning: the disassembly step ID exceeds its range. \n\n");
            break;
        }

        /// Compute the moveVector for a movable/removable pieceGroup
        PuzAction puzAction = puzActionList[i];

        vector<int> actualMovePieceIDs;
        Vector3f actualMoveVector;
        puzAction.GetPieceGroupMoveVector(volumeSize, voxelSize, actualMovePieceIDs, actualMoveVector);

        /// Update puzzle piece positions according to the moveVector
        for (int j = 0; j < actualMovePieceIDs.size(); ++j)
        {
            int pieceID = actualMovePieceIDs[j];

            for (int k = 0; k < voxelCenPtsList[pieceID].rows(); k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    voxelCenPtsList[pieceID](k,l) += actualMoveVector(l);
                    voxelMinPtsList[pieceID](k,l) += actualMoveVector(l);
                    voxelMaxPtsList[pieceID](k,l) += actualMoveVector(l);
                }
            }

            for (int k = 0; k < cylinTopPtsList[pieceID].rows(); k++)
            {
                for (int l = 0; l < 3; ++l)
                {
                    cylinTopPtsList[pieceID](k,l) += actualMoveVector(l);
                    cylinBotPtsList[pieceID](k,l) += actualMoveVector(l);
                }
            }
        }
    }
}

void Puzzle::CreatePuzzleGeometry(vector<Eigen::MatrixXf> &voxelMinPtsList,
                                  vector<Eigen::MatrixXf> &voxelMaxPtsList,
                                  vector<Eigen::MatrixXf> &voxelCenPtsList,
                                  vector<Eigen::MatrixXf> &cylinTopPtsList,
                                  vector<Eigen::MatrixXf> &cylinBotPtsList,
                                  PuzConfig currPuzConfig)
{

    /// Compute the actual number of piece we need to show
    int actualPieceNum = currPuzConfig.piecePosList.size();

    voxelMinPtsList.resize(actualPieceNum);
    voxelMaxPtsList.resize(actualPieceNum);
    voxelCenPtsList.resize(actualPieceNum);

    cylinTopPtsList.resize(actualPieceNum);
    cylinBotPtsList.resize(actualPieceNum);

    Vector3f voxelSize = volume->GetVoxelSize();
    Vector3i volumeSize = volume->GetVolumeSize();

    Vector3f puzTransVec;

    puzTransVec(0) = -0.5f*(volumeSize(0) - 1) * voxelSize(0);
    puzTransVec(1) = -0.5f*(volumeSize(1) - 1) * voxelSize(1);
    puzTransVec(2) = -0.5f*(volumeSize(2) - 1) * voxelSize(2);

    /// Create a piece that coming from merging last N pieces
    Piece * tempPiece = new Piece;

    // Merge the piece
    for (int i = actualPieceNum - 1; i < pieceList.size(); ++i)
    {
        for (int j = 0; j < pieceList[i]->voxelList.size(); ++j)
        {
            tempPiece->AddVoxel(pieceList[i]->voxelList[j]);
        }
    }

    /// Create the Rendering data for the pieces that don't need to be merged
    Vector3f offsetVector;
    Vector3f currTransVec;

    for (int i = 0; i < actualPieceNum - 1; i++)
    {
        offsetVector(0) = currPuzConfig.piecePosList[i](0) * voxelSize(0);
        offsetVector(1) = currPuzConfig.piecePosList[i](1) * voxelSize(1);
        offsetVector(2) = currPuzConfig.piecePosList[i](2) * voxelSize(2);

        currTransVec = puzTransVec + offsetVector;

        pieceList[i]->CreatePieceGeometry(currTransVec, voxelMinPtsList[i], voxelMaxPtsList[i], voxelCenPtsList[i], cylinTopPtsList[i], cylinBotPtsList[i]);
    }


    /// Create the Rendering data for the merged piece
    offsetVector(0) = currPuzConfig.piecePosList[actualPieceNum - 1](0) * voxelSize(0);
    offsetVector(1) = currPuzConfig.piecePosList[actualPieceNum - 1](1) * voxelSize(1);
    offsetVector(2) = currPuzConfig.piecePosList[actualPieceNum - 1](2) * voxelSize(2);

    currTransVec = puzTransVec + offsetVector;

    tempPiece->CreatePieceGeometry(currTransVec, voxelMinPtsList[actualPieceNum - 1], voxelMaxPtsList[actualPieceNum - 1], voxelCenPtsList[actualPieceNum - 1], cylinTopPtsList[actualPieceNum - 1], cylinBotPtsList[actualPieceNum - 1]);
}



///=========================================================================================///
///                                     Read Puzzle File
///=========================================================================================///

void Puzzle::ReadPuzzleFile(string fileName)
{
    FILE *fp;
    if ((fp=fopen(fileName.data(),"r"))==NULL)
    {
        printf("Error: file not exists! \n");
    }
    else
    {
        ClearPuzzle();

        Vector3i volumeSize;
        Vector3f voxelSize;

        char firstCh=fgetc(fp);
//        printf("The first char: %c\n", firstCh);

        if (firstCh != '#')
        {
            rewind(fp);
            fscanf(fp, "%d %d %d\n", &volumeSize[0], &volumeSize[1], &volumeSize[2]);
        }

        if (firstCh == '#')
        {
            float generationTime;
            fscanf(fp, "%f\n", &generationTime);
            fscanf(fp, "%d %d %d\n", &volumeSize[0], &volumeSize[1], &volumeSize[2]);
        }

        // Volume Size
        fscanf(fp, "%f %f %f\n", &voxelSize[0], &voxelSize[1], &voxelSize[2]);

        int volumeVoxelNum = volumeSize(X_INFO) * volumeSize(Y_INFO) * volumeSize(Z_INFO);

        // Puzzle Data
        vector<int> puzzleData(volumeVoxelNum, 0);
        for (int k=0; k<volumeVoxelNum; k++)
            fscanf(fp,"%d ", &puzzleData[k]);

        InitPuzzle(volumeSize, voxelSize, puzzleData);

    }
    fclose(fp);
}

void Puzzle::ReadSmoothPuzzleFile(string fileName)
{
    size_t foundFolder = fileName.find_last_of('/'); // Note: this applies for Mac only
    string puzFolderPath = fileName.substr(0, foundFolder);

    smoothPieceVerticeList.clear();
    smoothPieceFaceList.clear();

    for (int i = 0; i < pieceList.size(); ++i)
    {
        string currSmoothOBJName = puzFolderPath + "/smooth_piece" + to_string(i+1) + ".obj";

        FILE *fp;
        if ((fp=fopen(currSmoothOBJName.data(),"r"))==NULL)
        {
            printf("There is no smooth piece obj files stored. \n");
            break;
        }

        Eigen::MatrixXd V;
        Eigen::MatrixXi F;

        igl::readOBJ(currSmoothOBJName, V, F);

        smoothPieceVerticeList.push_back(V);
        smoothPieceFaceList.push_back(F);
    }

    string smoothInputOBJName = puzFolderPath + "/smoothinput.obj";

    FILE *fp;
    if ((fp=fopen(smoothInputOBJName.data(),"r"))==NULL)
    {
//        printf("There is no smooth input obj files stored. \n");
    }
    else
    {
        igl::readOBJ(smoothInputOBJName, smoothShape_V, smoothShape_F);
    }
}

void Puzzle::InitPuzzle(const Vector3i volumeSize, const Vector3f voxelSize, const vector<int> puzzleData)
{
    if(volume != NULL )
    {
        delete volume;
        volume = NULL;
    }

    volume = new Volume();

    int pieceNum = volume->InitVolume(volumeSize, voxelSize, puzzleData);

    pieceList = volume->ConvertVolume2Puzzle( pieceNum );

    // Interlocking, buildable, and level info
    puzLockState = PUZZLE_LOCK_UNKNOWN;
    puzBuildState = PUZZLE_BUILD_UNKNOWN;
    puzLevel = 0;

#ifdef SHOW_INFO
    for (int i=0; i<pieceList.size(); i++)
    {
        printf("Piece %2d: %3ld voxels \n", pieceList[i]->pieceID, pieceList[i]->voxelList.size());
        //pieceList[i]->PrintPieceInfo();
    }
    printf("\n");
#endif
}




///=========================================================================================///
///                                     Save Puzzle Files
///=========================================================================================///

void Puzzle::SavePuzzleFiles(string puzFolderPath, float puzTolerance, bool isFixLastPiece)
{
    //////////////////////////////////////////////////////////////////////////////
    /// 1. Setup a folder to save puzzle files

    string command;
    command = "mkdir -p " + puzFolderPath;
    system(command.c_str());


    //////////////////////////////////////////////////////////////////////////////
    /// 2. Save the puzzle file (.puz)

    // If the folder is not empty, remove the last '/'
    if (puzFolderPath[puzFolderPath.length() - 1] == '/')
        puzFolderPath = puzFolderPath.substr(0, puzFolderPath.length() - 1);

    // Get puzzle name from the folder name
    size_t foundFolder = puzFolderPath.find_last_of('/'); // Note: this applies for Mac only
    string puzzleName = puzFolderPath.substr(foundFolder+1, puzFolderPath.size());
    string puzzlePureName = puzFolderPath.substr(foundFolder+1, puzFolderPath.size());;
    puzzleName.append(".puz");

    string puzzleFullName = puzFolderPath + "/" + puzzleName;
    printf("Saving files - generation time: %.3f\n", generationTime);
    volume->WritePuzzleFile( puzzleFullName.c_str(), generationTime );


    //////////////////////////////////////////////////////////////////////////////
    /// 3. Save disassembly graph

    vector<PuzConfig*> graphPuzConfigs;
    vector<PuzConfig*> pathPuzConfigs;
    vector<PuzConfig*> kernelGraphConfigs;
    vector<PuzAction>  puzActions;

    int expScaleSize = 1;
    int currLevel;

    if (puzBuildState == PUZZLE_NORMAL_BUILDABLE)
    {
        while(1)
        {
            PuzSolver puzSolver;
            puzSolver.InitPuzSolver(pieceList, volume->GetVolumeSize(), expScaleSize);
            puzSolver.DisassemblyPuzzzle_Graph(DISASS_FIX_LAST_PIECE, graphPuzConfigs, pathPuzConfigs, currLevel);
            puzSolver.ComputeDisassemblyPlan(pathPuzConfigs, puzActions, isFixLastPiece);

            if (currLevel == puzLevel)
                break;

            expScaleSize++;
        }
    }

    graphPuzConfigs.clear();
    pathPuzConfigs.clear();
    puzActions.clear();

    PuzSolver puzSolver;
    puzSolver.InitPuzSolver(pieceList, volume->GetVolumeSize(), expScaleSize);
    puzSolver.DisassemblyPuzzzle_Graph(DISASS_FIX_LAST_PIECE, graphPuzConfigs, pathPuzConfigs, currLevel);
    puzSolver.ComputeDisassemblyPlan(pathPuzConfigs, puzActions, isFixLastPiece);

    WriteDisassemblyGraph( puzFolderPath, graphPuzConfigs, puzzlePureName + "_complete_graph");

    WriteDisassemblyKernelGraph( puzFolderPath, graphPuzConfigs, puzzlePureName + "_kernel_graph");

    WriteDisassemblyMotion( puzFolderPath, puzActions );

    for (int i = 0; i < graphPuzConfigs.size(); ++i)
    {
        delete graphPuzConfigs[i];
    }

    for (int i = 0; i < kernelGraphConfigs.size(); ++i)
    {
        delete kernelGraphConfigs[i];
    }

    //////////////////////////////////////////////////////////////////////////////
    /// 4. Save animation files (.objs)

    WritePieceOBJs_voxel( puzFolderPath, puzTolerance );
//    WritePieceOBJs_skel( puzFolderPath );
}

void Puzzle::UpdateKernelGraph(string puzFolderPath)
{
    //////////////////////////////////////////////////////////////////////////////
    /// 1. Setup a folder to save puzzle files

    string command;
    command = "mkdir -p " + puzFolderPath;
    system(command.c_str());


    //////////////////////////////////////////////////////////////////////////////
    /// 2. Save the puzzle file (.puz)

    // If the folder is not empty, remove the last '/'
    if (puzFolderPath[puzFolderPath.length() - 1] == '/')
        puzFolderPath = puzFolderPath.substr(0, puzFolderPath.length() - 1);

    // Get puzzle name from the folder name
    size_t foundFolder = puzFolderPath.find_last_of('/'); // Note: this applies for Mac only
    string puzzleName = puzFolderPath.substr(foundFolder+1, puzFolderPath.size());
    string puzzlePureName = puzFolderPath.substr(foundFolder+1, puzFolderPath.size());;
    puzzleName.append(".puz");

    string puzzleFullName = puzFolderPath + "/" + puzzleName;
//    printf("Saving files - generation time: %.3f\n", generationTime);

    vector<PuzConfig*> graphPuzConfigs;
    vector<PuzConfig*> pathPuzConfigs;
    vector<PuzConfig*> kernelGraphConfigs;
    vector<PuzAction>  puzActions;
    int currLevel;

    PuzSolver puzSolver;
    puzSolver.InitPuzSolver(pieceList, volume->GetVolumeSize(), 2);
    puzSolver.DisassemblyPuzzzle_Graph(DISASS_FIX_LAST_PIECE, graphPuzConfigs, pathPuzConfigs, currLevel);
    puzSolver.ComputeDisassemblyPlan(pathPuzConfigs, puzActions, false);

    WriteDisassemblyKernelGraph( puzFolderPath, graphPuzConfigs, puzzlePureName + "_kernel_graph");
}

void Puzzle::SaveCSGPuzzleFiles(string puzFolderPath, string voxelizedPuzFolderPath, float puzTolerance, bool isFixLastPiece, Eigen::MatrixXd smoothShape_V, Eigen::MatrixXi smoothShape_F)
{
    //////////////////////////////////////////////////////////////////////////////
    /// 1. Setup a folder to save puzzle files

    string command;
    command = "mkdir -p " + puzFolderPath;
    system(command.c_str());


    //////////////////////////////////////////////////////////////////////////////
    /// 2. Save the puzzle file (.puz)

    // If the folder is not empty, remove the last '/'
    if (puzFolderPath[puzFolderPath.length() - 1] == '/')
        puzFolderPath = puzFolderPath.substr(0, puzFolderPath.length() - 1);

    // Get puzzle name from the folder name
    size_t foundFolder = puzFolderPath.find_last_of('/'); // Note: this applies for Mac only
    string puzzleName = puzFolderPath.substr(foundFolder+1, puzFolderPath.size());
    string puzzlePureName = puzFolderPath.substr(foundFolder+1, puzFolderPath.size());;
    puzzleName.append(".puz");

    string puzzleFullName = puzFolderPath + "/" + puzzleName;
//    printf("Saving files - generation time: %.3f\n", generationTime);
    volume->WritePuzzleFile( puzzleFullName.c_str(), generationTime );


    //////////////////////////////////////////////////////////////////////////////
    /// 3. Save disassembly graph

    vector<PuzConfig*> graphPuzConfigs;
    vector<PuzConfig*> pathPuzConfigs;
    vector<PuzAction>  puzActions;

    PuzSolver puzSolver;
    puzSolver.InitPuzSolver(pieceList, volume->GetVolumeSize());
    puzSolver.DisassemblyPuzzzle_Graph(DISASS_FIX_LAST_PIECE, graphPuzConfigs, pathPuzConfigs, puzLevel);
    puzSolver.ComputeDisassemblyPlan(pathPuzConfigs, puzActions, isFixLastPiece);

    WriteDisassemblyGraph( puzFolderPath, graphPuzConfigs, puzzlePureName);

    WriteDisassemblyMotion( puzFolderPath, puzActions );

    for (int i = 0; i < graphPuzConfigs.size(); ++i)
    {
        delete graphPuzConfigs[i];
    }


    //////////////////////////////////////////////////////////////////////////////
    /// 4. Save animation files (.objs)

    Mesh * smoothShapeMesh = new Mesh();
    smoothShapeMesh->verM = smoothShape_V;
    smoothShapeMesh->triM = smoothShape_F;

    smoothShapeMesh->ReverseNormal();

    for (int i = 0; i < pieceList.size(); ++i)
    {
        string currVoxelizedPieceOBJName = voxelizedPuzFolderPath + "/piece" + to_string(i+1) + ".obj";
        cout << "currPieceOBJName: " << currVoxelizedPieceOBJName << endl;

        Eigen::MatrixXd V;
        Eigen::MatrixXi F;

        igl::readOBJ(currVoxelizedPieceOBJName, V, F);

        Mesh * currPieceMesh = new Mesh();
        currPieceMesh->verM = V;
        currPieceMesh->triM = F;

        Eigen::MatrixXd csg_V;
        Eigen::MatrixXi csg_F;

        MeshBoolean meshBoolean;
        meshBoolean.MeshIntersect(smoothShape_V, smoothShape_F, V, F, csg_V, csg_F);

        string currOBJName = puzFolderPath + "/smoothpiece" + to_string(i+1) + ".obj";
        cout << "currSmoothOBJName: " << currOBJName << endl;

        igl::writeOBJ(currOBJName, csg_V, csg_F);
    }
}

void Puzzle::WriteDisassemblyGraph(string folderPath, vector<PuzConfig*> tracedPuzConfigs, string puzzlePureName)
{
    char assemblyTreeFileName[512];
    char assemblyImageFileName[512];

    string command;
    command = "mkdir -p " + folderPath + "/assembly_graph";
    system(command.c_str());

    sprintf(assemblyTreeFileName,   "%s/assembly_graph/%s.dot",  folderPath.data(), puzzlePureName.data());
    sprintf(assemblyImageFileName,  "%s/assembly_graph/%s.png",  folderPath.data(), puzzlePureName.data());

    cout << assemblyTreeFileName << endl;

    FILE *fp;

    if ((fp=fopen(assemblyTreeFileName,"w"))==NULL)
    {
        printf("Error: file not exists! \n");
        return;
    }

    else
    {
        ////////////////////////////////////////////////////////
        /// Write piece OBJ model name and number

        fprintf(fp, "graph G {\n");
        fprintf(fp, "color = \"black\"\n");

        for (int i=0; i<tracedPuzConfigs.size(); i++)
        {
            PuzConfig *puzConfig = tracedPuzConfigs[i];

//            if(puzConfig->isInKernelGraph == false)
//                continue;

            int currID = puzConfig->puzConfigID;

            fprintf(fp, "%d [", currID);
//            fprintf(fp, "label = \"Index: %d \n", currID);
            fprintf(fp, "label = \"");

            for (int j = 0; j < puzConfig->pieceIDList.size(); j++)
            {
                //fprintf(fp, "p%d: %d %d %d \n", puzConfig->pieceIDList[j] + 1,
                fprintf(fp, "P%d: %d %d %d \n", puzConfig->pieceIDList[j] + 1,
                                                puzConfig->piecePosList[j](0),
                                                puzConfig->piecePosList[j](1),
                                                puzConfig->piecePosList[j](2));
            }

            fprintf(fp, "\"");

            if     (puzConfig->configType == PUZ_CONFIG_ROOT)               fprintf(fp, ",  style=\"filled\", fillcolor = \"#96FF96\"");
            else if(puzConfig->configType == PUZ_CONFIG_TARGET_CANDI )       fprintf(fp, ",  style=\"filled\", fillcolor = \"#FF9696\"");
            else if(puzConfig->configType == PUZ_CONFIG_TARGET )             fprintf(fp, ",  style=\"filled\", fillcolor = \"#FF9696\"");
//            else if(puzConfig->configType == PUZ_CONFIG_SHORTEST_PATH )      fprintf(fp, ", color = \"orange\"");
            else if(puzConfig->configType == PUZ_CONFIG_PIECE_ONLY)          fprintf(fp, ",  style=\"filled\", fillcolor = \"#FF96FF\"");
//            else if(puzConfig->configType == PUZ_CONFIG_PIECE_REMOVE)        fprintf(fp, ", color = \"red\"");
//            else if(puzConfig->configType == PUZ_CONFIG_GROUP_REMOVE)        fprintf(fp, ", color = \"blue\"");
            else if(puzConfig->configType == PUZ_CONFIG_END_NODE )           fprintf(fp, ", style=\"filled\", fillcolor = \"#9696FF\"");

            fprintf(fp, "];\n");
        }

        vector<vector<int>> edgeList;

        fprintf(fp, "edge [style=bold];\n");

        for (int i=0; i<tracedPuzConfigs.size(); i++)
        {
            if (tracedPuzConfigs[i]->nextPuzConfigs.empty())// == true or tracedPuzConfigs[i]->isInKernelGraph == false)
            {
                continue;
            }
            else
            {
                int currID = tracedPuzConfigs[i]->puzConfigID;

                for (int j = 0; j < tracedPuzConfigs[i]->nextPuzConfigs.size(); j++)
                {
                    vector<int> currEdge;
                    currEdge.push_back(currID);
                    currEdge.push_back(tracedPuzConfigs[i]->nextPuzConfigs[j]->puzConfigID);
                    sort(currEdge.begin(), currEdge.end());

                    int nextID = tracedPuzConfigs[i]->nextPuzConfigs[j]->puzConfigID;

                    if (find(edgeList.begin(), edgeList.end(), currEdge) == edgeList.end())
//                    and tracedPuzConfigs[currID]->pieceIDList.size() == tracedPuzConfigs[nextID]->pieceIDList.size())
                    {
                        if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_SHORTEST_PATH and
                        tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_SHORTEST_PATH)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_ROOT and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_SHORTEST_PATH)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_SHORTEST_PATH and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_TARGET)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_TARGET and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_PIECE_REMOVE)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_PIECE_REMOVE and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_SHORTEST_PATH)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_SHORTEST_PATH and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_PIECE_REMOVE)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_PIECE_REMOVE and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_PIECE_REMOVE)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_PIECE_REMOVE and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_END_NODE)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else
                        {
                            fprintf(fp, "%d -- %d [color=black];\n", currID, nextID);
                        }
//                        fprintf(fp, "%d -- %d ;\n", currID, nextID);
                        edgeList.push_back(currEdge);
                    }
                }
                fprintf(fp, "\n");
            }
        }
        fprintf(fp, "}\n");
    }

    fclose(fp);

    command = "dot -Tpng -o " + string(assemblyImageFileName) + " " + string(assemblyTreeFileName);
    system(command.c_str());
}

void Puzzle::WriteDisassemblyKernelGraph(string folderPath, vector<PuzConfig*> tracedPuzConfigs, string puzzlePureName)
{
    char assemblyTreeFileName[512];
    char assemblyImageFileName[512];

    string command;
    command = "mkdir -p " + folderPath + "/assembly_graph";
    system(command.c_str());

    sprintf(assemblyTreeFileName,   "%s/assembly_graph/%s.dot",  folderPath.data(), puzzlePureName.data());
    sprintf(assemblyImageFileName,  "%s/assembly_graph/%s.png",  folderPath.data(), puzzlePureName.data());

    cout << assemblyTreeFileName << endl;

    FILE *fp;

    if ((fp=fopen(assemblyTreeFileName,"w"))==NULL)
    {
        printf("Error: file not exists! \n");
        return;
    }

    else
    {
        ////////////////////////////////////////////////////////
        /// Write piece OBJ model name and number

        fprintf(fp, "graph G {\n");
        fprintf(fp, "color = \"black\"\n");

        for (int i=0; i<tracedPuzConfigs.size(); i++)
        {
            PuzConfig *puzConfig = tracedPuzConfigs[i];

            if(puzConfig->isInKernelGraph == false)
                continue;

            int currID = puzConfig->puzConfigID;

            fprintf(fp, "%d [", currID);
//            fprintf(fp, "label = \"Index: %d \n", currID);
            fprintf(fp, "label = \"");

            for (int j = 0; j < puzConfig->pieceIDList.size(); j++)
            {
                //fprintf(fp, "p%d: %d %d %d \n", puzConfig->pieceIDList[j] + 1,
                fprintf(fp, "P%d: %d %d %d \n", puzConfig->pieceIDList[j] + 1,
                        puzConfig->piecePosList[j](0),
                        puzConfig->piecePosList[j](1),
                        puzConfig->piecePosList[j](2));
            }

            fprintf(fp, "\"");

            if     (puzConfig->configType == PUZ_CONFIG_ROOT)               fprintf(fp, ",  style=\"filled\", fillcolor = \"#96FF96\"");
//            else if(puzConfig->configType == PUZ_CONFIG_TARGET_CANDI )       fprintf(fp, ",  style=\"filled\", fillcolor = \"#FF9696\"");
//            else if(puzConfig->configType == PUZ_CONFIG_TARGET )             fprintf(fp, ",  style=\"filled\", fillcolor = \"#FF9696\"");
//            else if(puzConfig->configType == PUZ_CONFIG_SHORTEST_PATH )      fprintf(fp, ", color = \"orange\"");
//            else if(puzConfig->configType == PUZ_CONFIG_PIECE_ONLY)          fprintf(fp, ",  style=\"filled\", fillcolor = \"#FF96FF\"");
//            else if(puzConfig->configType == PUZ_CONFIG_PIECE_REMOVE)        fprintf(fp, ", color = \"red\"");
//            else if(puzConfig->configType == PUZ_CONFIG_GROUP_REMOVE)        fprintf(fp, ", color = \"blue\"");
//            else if(puzConfig->configType == PUZ_CONFIG_END_NODE )           fprintf(fp, ", style=\"filled\", fillcolor = \"#9696FF\"");

            fprintf(fp, "];\n");

            if (tracedPuzConfigs[i]->remvPieceIDs.size() != 0)
            {
                fprintf(fp, "%d%d [", currID, currID);
//            fprintf(fp, "label = \"Index: %d \n", currID);
                fprintf(fp, "label = \"");

                for (int m = 0; m < pieceList.size(); ++m)
                {
                    if (find(tracedPuzConfigs[i]->remvPieceIDs.begin(),tracedPuzConfigs[i]->remvPieceIDs.end(),m) != tracedPuzConfigs[i]->remvPieceIDs.end())
                    {
                        if (tracedPuzConfigs[i]->remvAxisIDs[0] == 0) fprintf(fp, "P%d: +∞ %d %d \n", m+1, puzConfig->piecePosList[m](1), puzConfig->piecePosList[m](2));
                        if (tracedPuzConfigs[i]->remvAxisIDs[0] == 1) fprintf(fp, "P%d: -∞ %d %d \n", m+1, puzConfig->piecePosList[m](1), puzConfig->piecePosList[m](2));
                        if (tracedPuzConfigs[i]->remvAxisIDs[0] == 2) fprintf(fp, "P%d: %d +∞ %d \n", m+1, puzConfig->piecePosList[m](0), puzConfig->piecePosList[m](2));
                        if (tracedPuzConfigs[i]->remvAxisIDs[0] == 3) fprintf(fp, "P%d: %d -∞ %d \n", m+1, puzConfig->piecePosList[m](0), puzConfig->piecePosList[m](2));
                        if (tracedPuzConfigs[i]->remvAxisIDs[0] == 4) fprintf(fp, "P%d: %d %d +∞ \n", m+1, puzConfig->piecePosList[m](0), puzConfig->piecePosList[m](1));
                        if (tracedPuzConfigs[i]->remvAxisIDs[0] == 5) fprintf(fp, "P%d: %d %d -∞ \n", m+1, puzConfig->piecePosList[m](0), puzConfig->piecePosList[m](1));
                        printf("remvAxisID: %d\n", tracedPuzConfigs[i]->remvAxisIDs[0]);
                    }

                    else
                    {
                        fprintf(fp, "P%d: %d %d %d \n", m+1,
                                puzConfig->piecePosList[m](0),
                                puzConfig->piecePosList[m](1),
                                puzConfig->piecePosList[m](2));
                    }
//                    fprintf(fp, "];\n");
                }
                fprintf(fp, "\"");
                fprintf(fp, ",  style=\"filled\", fillcolor = \"#FF9696\"");
                fprintf(fp, "];\n");
            }
        }

        vector<vector<int>> edgeList;

        fprintf(fp, "edge [style=bold];\n");

        for (int i=0; i<tracedPuzConfigs.size(); i++)
        {
            if (tracedPuzConfigs[i]->nextPuzConfigs.empty() == true or tracedPuzConfigs[i]->isInKernelGraph == false)
            {
                continue;
            }
            else
            {
                int currID = tracedPuzConfigs[i]->puzConfigID;

                for (int j = 0; j < tracedPuzConfigs[i]->nextPuzConfigs.size(); j++)
                {
                    vector<int> currEdge;
                    currEdge.push_back(currID);
                    currEdge.push_back(tracedPuzConfigs[i]->nextPuzConfigs[j]->puzConfigID);
                    sort(currEdge.begin(), currEdge.end());

                    int nextID = tracedPuzConfigs[i]->nextPuzConfigs[j]->puzConfigID;

                    if (find(edgeList.begin(), edgeList.end(), currEdge) == edgeList.end()
                    and tracedPuzConfigs[currID]->pieceIDList.size() == tracedPuzConfigs[nextID]->pieceIDList.size())
                    {
                        if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_SHORTEST_PATH and
                            tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_SHORTEST_PATH)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_ROOT and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_SHORTEST_PATH)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else if (tracedPuzConfigs[currID]->configType == PUZ_CONFIG_SHORTEST_PATH and
                                 tracedPuzConfigs[nextID]->configType == PUZ_CONFIG_TARGET)
                        {
                            fprintf(fp, "%d -- %d [color=\"#1E96FF\", penwidth=4.0];\n", currID, nextID);
                        }
                        else
                        {
                            fprintf(fp, "%d -- %d [color=black];\n", currID, nextID);
                        }
//                        fprintf(fp, "%d -- %d ;\n", currID, nextID);
                        edgeList.push_back(currEdge);
                    }


                }
                fprintf(fp, "\n");
            }

            if (tracedPuzConfigs[i]->remvPieceIDs.size() != 0)
            {
                if (tracedPuzConfigs[i]->configType == PUZ_CONFIG_TARGET)
                    fprintf(fp, "%d -- %d%d [color=\"#1E96FF\", penwidth=4.0];\n", tracedPuzConfigs[i]->puzConfigID, tracedPuzConfigs[i]->puzConfigID, tracedPuzConfigs[i]->puzConfigID);
                else
                    fprintf(fp, "%d -- %d%d [color=black];\n", tracedPuzConfigs[i]->puzConfigID, tracedPuzConfigs[i]->puzConfigID, tracedPuzConfigs[i]->puzConfigID);
            }
        }
        fprintf(fp, "}\n");
    }

    fclose(fp);

    command = "dot -Tpng -o " + string(assemblyImageFileName) + " " + string(assemblyTreeFileName);
    system(command.c_str());
}


void Puzzle::WriteDisassemblyMotion(string folderPath, vector<PuzAction> puzActions)
{

    if (puzActions.size() == 0)
    {
        printf("There is no disassembly plan!\n");
        return;
    }

    pugi::xml_document doc;
    string folder_name(folderPath);
    pugi::xml_node root_node = doc.append_child(("Root"));

    ////////////////////////////////////////////////////////
    // Write piece OBJ model name and number
    root_node.append_attribute("start_id").set_value(1);
    root_node.append_attribute("Objects_num").set_value(pieceList.size());
    pugi::xml_node piece_node = root_node.append_child(("piece_name"));

    for (int i=0; i<pieceList.size(); i++)
    {
        pugi::xml_node p_node = piece_node.append_child("piece");
        p_node.append_attribute("id").set_value(i+1);
    }

    ////////////////////////////////////////////////////////
    // Write piece disassembly actions

    pugi::xml_node action_all_node = root_node.append_child(("action_all"));

    Vector3f voxelSize = volume->GetVoxelSize();
    Vector3i volumeSize = volume->GetVolumeSize();

    Vector3f curmoveVector(0.0,0.0,0.0);
    Vector3f moveStep(0.0,0.0,0.0);
    Vector3f emptyMoveVector(0.0,0.0,0.0);

    const float moveDistCoeff = 1.4;

    for (int i = 0; i < puzActions.size(); ++i)
    {
        if (puzActions[i].isMoveAction)
        {
            curmoveVector(X_INFO) = puzActions[i].moveVector(X_INFO) * voxelSize(X_INFO);
            curmoveVector(Y_INFO) = puzActions[i].moveVector(Y_INFO) * voxelSize(Y_INFO);
            curmoveVector(Z_INFO) = puzActions[i].moveVector(Z_INFO) * voxelSize(Z_INFO);

            int frameNum = curmoveVector.norm() * 100;

            pugi::xml_node action_node = action_all_node.append_child("action");

            action_node.append_attribute("is_move").set_value(true);

            action_node.append_attribute("frameNum").set_value(frameNum);
            action_node.append_attribute("x").set_value(curmoveVector(X_INFO));
            action_node.append_attribute("y").set_value(curmoveVector(Y_INFO));
            action_node.append_attribute("z").set_value(curmoveVector(Z_INFO));

            for (int k = 0; k < puzActions[i].movePieceIDs.size(); ++k) {
                pugi::xml_node pieceId_node = action_node.append_child("piece");
                pieceId_node.append_attribute("id").set_value(puzActions[i].movePieceIDs[k] + 1);
            }
        }

        else
        {
            if      ( puzActions[i].remvAxisIDs[0] == 0 )     curmoveVector = moveDistCoeff * volumeSize[0] * Vector3f(-1,  0,  0 );
            else if ( puzActions[i].remvAxisIDs[0] == 1 )     curmoveVector = moveDistCoeff * volumeSize[0] * Vector3f( 1,  0,  0 );
            else if ( puzActions[i].remvAxisIDs[0] == 2 )     curmoveVector = moveDistCoeff * volumeSize[1] * Vector3f( 0, -1,  0 );
            else if ( puzActions[i].remvAxisIDs[0] == 3 )     curmoveVector = moveDistCoeff * volumeSize[1] * Vector3f( 0,  1,  0 );
            else if ( puzActions[i].remvAxisIDs[0] == 4 )     curmoveVector = moveDistCoeff * volumeSize[2] * Vector3f( 0,  0, -1 );
            else if ( puzActions[i].remvAxisIDs[0] == 5 )     curmoveVector = moveDistCoeff * volumeSize[2] * Vector3f( 0,  0,  1 );

            curmoveVector(0) *= voxelSize(0);
            curmoveVector(1) *= voxelSize(1);
            curmoveVector(2) *= voxelSize(2);

            int frameNum = curmoveVector.norm() * 30;

            pugi::xml_node action_node = action_all_node.append_child("action");
            action_node.append_attribute("is_move").set_value(false);

            action_node.append_attribute("frameNum").set_value(frameNum);
            action_node.append_attribute("x").set_value(curmoveVector(X_INFO));
            action_node.append_attribute("y").set_value(curmoveVector(Y_INFO));
            action_node.append_attribute("z").set_value(curmoveVector(Z_INFO));

            for (int k = 0; k < puzActions[i].remvPieceIDs.size(); ++k) {
                pugi::xml_node pieceId_node = action_node.append_child("piece");
                pieceId_node.append_attribute("id").set_value(puzActions[i].remvPieceIDs[k] + 1);
            }
        }
    }

//    string command;
//
//    command = "mkdir -p " + folder_name + "/pieceCubeModel";
//    system(command.c_str());
//
//    command = "mkdir -p " + folder_name + "/pieceSkelModel";
//    system(command.c_str());

//    doc.save_file((folder_name + "/pieceSkelModel/animation.motion.xml").data());
//    doc.save_file((folder_name + "/pieceCubeModel/animation.motion.xml").data());

    doc.save_file((folder_name + "/animation.motion.xml").data());
}

void Puzzle::WritePieceOBJs_voxel(string folderPath, float puzTolerance)
{
    PuzConverter myConverter;

    ObjPuzzle myObjPuzzle;

    myObjPuzzle.InitPuzzle( pieceList );
    myConverter.InitPuzConverter(this, &myObjPuzzle, puzTolerance);
    myConverter.ConvertPuzzle( (char*)((folderPath).data()), true, true, true );
}

void Puzzle::WritePieceOBJs_skel(string folderPath)
{
    vector<Eigen::MatrixXf> voxelMinPts;
    vector<Eigen::MatrixXf> voxelMaxPts;
    vector<Eigen::MatrixXf> voxelCenPts;
    vector<Eigen::MatrixXf> cylinTopPts;
    vector<Eigen::MatrixXf> cylinBotPts;

    float ballRadius = 0.08  * volume->GetVoxelSize().norm();
    float cyliRadius = 0.015 * volume->GetVoxelSize().norm();

    CreatePuzzleGeometry(voxelMinPts, voxelMaxPts, voxelCenPts, cylinTopPts, cylinBotPts, 0);

    MeshObject meshObject;
    vector<Mesh*> puzzlePieceSkelMesh;

    meshObject.CreatePuzzleSkeleton(voxelCenPts, cylinTopPts, cylinBotPts, ballRadius, cyliRadius, puzzlePieceSkelMesh);

    string piece("piece");
    string obj(".obj");

    for (int i = 0; i < puzzlePieceSkelMesh.size(); ++i)
    {
        string currPieceName = piece + to_string(i + 1) + obj;
        string fullFilePath = folderPath + "/pieceSkelModel/" + currPieceName;

        igl::writeOBJ(fullFilePath, puzzlePieceSkelMesh[i]->verM, puzzlePieceSkelMesh[i]->triM);
    }
}

