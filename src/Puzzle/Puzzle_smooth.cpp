//
// Created by Linsanity on 2/1/22.
//

#include "time.h"
#include "Utility/HelpDefine.h"
#include "Utility/HelpPuz.h"
#include "PieceFace.h"
#include "Piece.h"
#include "PuzAction.h"
#include "Volume.h"
#include "Puzzle.h"
#include "Puzzle_smooth.h"

extern Vector3i neiborPos[6];

///=========================================================================================///
///                                   Initialization
///=========================================================================================///

Puzzle_smooth::Puzzle_smooth()
{
    emptyVoxelNum = 0;
    attachVoxelNum = 0;
    attachVoxelNum_full = 0;
    successAttachNum = 0;
    successAttachNum_full = 0;
    problematicVoxelNum = 0;
}

Puzzle_smooth::~Puzzle_smooth()
{
    ClearPuzzle_smooth();
}

void Puzzle_smooth::ClearPuzzle_smooth()
{
    inputPuzzleData.clear();
    emptyVoxellist.clear();
    attachVoxelList.clear();
    originalSmoothPuzzleData.clear();
    originalSmoothPuzzleData_full.clear();
    inputProblemVoxelList.clear();

    emptyVoxelNum = 0;
    attachVoxelNum = 0;
    attachVoxelNum_full = 0;
    successAttachNum = 0;
    successAttachNum_full = 0;
    problematicVoxelNum = 0;
}

void Puzzle_smooth::InitPuzzle_smooth(float emptyThreshold, float fullThreshold)
{
    emptyVoxelThreshold = emptyThreshold;
    fullVoxelThreshold = fullThreshold;

    emptyVoxelNum = 0;
    attachVoxelNum = 0;
    attachVoxelNum_full = 0;
    successAttachNum = 0;
    successAttachNum_full = 0;
    problematicVoxelNum = 0;
    int fullVoxelNum = 0;

    printf("Input Puzzle Data: \n");
    for (int i = 0; i < originalSmoothPuzzleData.size(); ++i)
    {
        if (originalSmoothPuzzleData[i] > fullVoxelThreshold)
        {
            inputPuzzleData[i] = 1;
            fullVoxelNum++;
        }

//        printf("%d ", inputPuzzleData[i]);

        if (originalSmoothPuzzleData[i] > 0 and originalSmoothPuzzleData[i] <= fullVoxelThreshold)
        {
            attachVoxelList[i] = 1;
            attachVoxelNum++;
        }

//        if (originalSmoothPuzzleData[i] < emptyVoxelThreshold and originalSmoothPuzzleData[i] > 0)
//        if (originalSmoothPuzzleData[i] > 0 and )
//        {
//            emptyVoxellist[i] = 1;
//            emptyVoxelNum++;
//        }

    }

    printf("\n\n");

    printf("Size of full voxel list: %d\n", fullVoxelNum);
    printf("Size of empty voxel list: %d\n", emptyVoxelNum);
    printf("Size of attach voxel list: %d\n", attachVoxelNum);
}




///=========================================================================================///
///                              Read Smooth Shape Puzzle File
///=========================================================================================///

void Puzzle_smooth::ReadSmoothPuzzleFile_full(string fileName)
{
    attachVoxelNum_full = 0;
    successAttachNum_full = 0;

    FILE *fp;
    if ((fp=fopen(fileName.data(),"r"))==NULL)
    {
        printf("Error: file not exists! \n");
    }
    else
    {
        char firstCh=fgetc(fp);

        if (firstCh != 'S')
        {
            printf("This is not the smooth shape input puzzle file!.\n");
            return;
        }

        float tempVector[3];
        fscanf(fp, "%f %f %f ", &tempVector[0], &tempVector[1], &tempVector[2]);
//        printf("Trans Vector: %f %f %f\n", transVector[0], transVector[1], transVector[2]);

        float voxelSize;
        fscanf(fp, "%f\n", &voxelSize);

        originalSmoothPuzzleData_full.clear();

        int gridSize;
        fscanf(fp, "%d ", &gridSize);

//        // Puzzle Data
        printf("Original Smooth Puzzle Full Volume Data: \n");
        for (int k = 0; k < gridSize * gridSize * gridSize; k++)
        {
            originalSmoothPuzzleData_full.push_back(0);
            fscanf(fp,"%f ", &originalSmoothPuzzleData_full[k]);
            printf("%.2f ", originalSmoothPuzzleData_full[k]);
        }
        printf("\n\n");

        float puzzleArray[gridSize][gridSize][gridSize];

        int temp = 0;

        for (int i = 0; i < gridSize; ++i)
            for(int j = 0; j < gridSize; ++j)
                for (int k = 0; k < gridSize; ++k)
                {
                    puzzleArray[i][j][k] = originalSmoothPuzzleData_full[temp];
                    temp++;
                }

        originalSmoothPuzzleData_full.clear();
        attachVoxelList_full.clear();

        printf("Puzzle Data - Full Volume:\n\n");

        for (int i = i_Begin; i < i_End; ++i)
        {
            for (int j = j_Begin; j < j_End; ++j)
            {
                for (int k = k_Begin; k < k_End; ++k)
                {
                    originalSmoothPuzzleData_full.push_back(puzzleArray[i][j][k]);

                    attachVoxelList_full.push_back(0);

                    if (puzzleArray[i][j][k] > 0)
                        printf("1 ");

                    else
                        printf("0 ");
                }
                printf("\n");
            }
            printf("\n");
        }

        printf("\n\n");

        attachVoxelNum_full = 0;

        // Update the full volume attach voxels
        for (int i = 0; i < originalSmoothPuzzleData.size(); ++i)
        {
            if (originalSmoothPuzzleData[i] == 0 and originalSmoothPuzzleData_full[i] != 0)
            {
                attachVoxelList_full[i] = 1;
                attachVoxelNum_full ++;
//                printf("Is attach Voxel.\n");
            }

            else
                attachVoxelList_full[i] = 0;
        }

        printf("attachVoxelNum_full: %d\n", attachVoxelNum_full);

    }
}

void Puzzle_smooth::ReadSmoothPuzzleFile(string fileName)
{
    FILE *fp;
    if ((fp=fopen(fileName.data(),"r"))==NULL)
    {
        printf("Error: file not exists! \n");
    }

    else
    {
        ClearPuzzle_smooth();

        char firstCh=fgetc(fp);

        if (firstCh != 'S')
        {
            printf("This is not the smooth shape input puzzle file!.\n");
            return;
        }

        fscanf(fp, "%f %f %f ", &transVector[0], &transVector[1], &transVector[2]);
        printf("Trans Vector: %f %f %f\n", transVector[0], transVector[1], transVector[2]);

        float voxelSize;
        fscanf(fp, "%f\n", &voxelSize);

        initVoxelSize[0] = voxelSize;
        initVoxelSize[1] = voxelSize;
        initVoxelSize[2] = voxelSize;
        printf("Voxel Size: %f %f %f\n", initVoxelSize[0], initVoxelSize[1], initVoxelSize[2]);

        int volumeSize;
        fscanf(fp, "%d\n", &volumeSize);

        initVolumeSize[0] = volumeSize;
        initVolumeSize[1] = volumeSize;
        initVolumeSize[2] = volumeSize;
        printf("Volume Size: %d %d %d\n", initVolumeSize[0], initVolumeSize[1], initVolumeSize[2]);

        int volumeVoxelNum = volumeSize * volumeSize * volumeSize;

        float puzzleArray[volumeSize][volumeSize][volumeSize];

        // Puzzle Data
        printf("Original Smooth Puzzle Data: \n");
        for (int k = 0; k < volumeVoxelNum; k++)
        {
            originalSmoothPuzzleData.push_back(0);
            fscanf(fp,"%f ", &originalSmoothPuzzleData[k]);
            printf("%.2f ", originalSmoothPuzzleData[k]);

            inputPuzzleData.push_back(0);
            emptyVoxellist.push_back(0);
            attachVoxelList.push_back(0);
        }
        printf("\n\n");

        int temp = 0;

        for (int i = 0; i < volumeSize; ++i)
            for(int j = 0; j < volumeSize; ++j)
                for (int k = 0; k < volumeSize; ++k)
                {
                    puzzleArray[i][j][k] = originalSmoothPuzzleData[temp];
                    temp++;
                }

        // K Direction
        bool islastLayerVoxel = false;

        int k_BeginFlag = 0;
        int k_EndFlag = volumeSize;

        for (int k = 0; k < volumeSize; ++k)
        {
            bool isVoxel = false;

            for (int i = 0; i < volumeSize; ++i)
            {
                for (int j = 0; j < volumeSize; ++j)
                {
                    if (puzzleArray[i][j][k] > 0)
                    {
                        isVoxel = true;
                        break;
                    }
                }

                if (isVoxel)
                    break;
            }

            if (islastLayerVoxel == false and isVoxel == true)
            {
                k_BeginFlag = k;
            }

            if (islastLayerVoxel == true and isVoxel == false)
            {
                k_EndFlag = k;
            }

            islastLayerVoxel = isVoxel;
            isVoxel = false;
        }

        printf("k_BeginFlag: %d\n", k_BeginFlag);
        printf("k_EndFlag: %d\n", k_EndFlag);

        // J direction
        islastLayerVoxel = false;

        int j_BeginFlag = 0;
        int j_EndFlag = volumeSize;

        for (int j = 0; j < volumeSize; ++j)
        {
            bool isVoxel = false;

            for (int i = 0; i < volumeSize; ++i)
            {
                for (int k = 0; k < volumeSize; ++k)
                {
                    if (puzzleArray[i][j][k] > 0)
                    {
                        isVoxel = true;
                        break;
                    }
                }

                if (isVoxel)
                    break;
            }

//            printf("j: %d\n", j);
//            printf("isLastLayerVoxel : %d\n", islastLayerVoxel);
//            printf("isVoxel: %d\n", isVoxel);

            if (islastLayerVoxel == false and isVoxel == true)
            {
                j_BeginFlag = j;
            }

            if (islastLayerVoxel == true and isVoxel == false)
            {
                j_EndFlag = j;
            }

            islastLayerVoxel = isVoxel;
        }

        printf("j_BeginFlag: %d\n", j_BeginFlag);
        printf("j_EndFlag: %d\n", j_EndFlag);

        // I direction
        islastLayerVoxel = false;

        int i_BeginFlag = 0;
        int i_EndFlag = volumeSize;

        for (int i = 0; i < volumeSize; ++i)
        {
            bool isVoxel = false;

            for (int j = 0; j < volumeSize; ++j)
            {
                for (int k = 0; k < volumeSize; ++k)
                {
                    if (puzzleArray[i][j][k] > 0)
                    {
                        isVoxel = true;
                        break;
                    }
                }

                if (isVoxel)
                    break;
            }

//            printf("i: %d\n", i);
//            printf("isLastLayerVoxel : %d\n", islastLayerVoxel);
//            printf("isVoxel: %d\n", isVoxel);

            if (islastLayerVoxel == false and isVoxel == true)
            {
                i_BeginFlag = i;
            }

            if (islastLayerVoxel == true and isVoxel == false)
            {
                i_EndFlag = i;
            }

            islastLayerVoxel = isVoxel;
        }

        printf("i_BeginFlag: %d\n", i_BeginFlag);
        printf("i_EndFlag: %d\n", i_EndFlag);

        i_Begin = i_BeginFlag;
        i_End = i_EndFlag;
        j_Begin = j_BeginFlag;
        j_End = j_EndFlag;
        k_Begin = k_BeginFlag;
        k_End = k_EndFlag;

        initVolumeSize(2) = i_EndFlag - i_BeginFlag;
        initVolumeSize(1) = j_EndFlag - j_BeginFlag;
        initVolumeSize(0) = k_EndFlag - k_BeginFlag;

        volumeVoxelNum = initVolumeSize(0) * initVolumeSize(1) * initVolumeSize(2);

        printf("volumeVoxelNum: %d\n", volumeVoxelNum);

        originalSmoothPuzzleData.clear();
        inputPuzzleData.clear();
        emptyVoxellist.clear();
        attachVoxelList.clear();

        printf("Puzzle Data:\n\n");

        for (int i = i_BeginFlag; i < i_EndFlag; ++i)
        {
            for (int j = j_BeginFlag; j < j_EndFlag; ++j)
            {
                for (int k = k_BeginFlag; k < k_EndFlag; ++k)
                {
                    originalSmoothPuzzleData.push_back(puzzleArray[i][j][k]);

                    inputPuzzleData.push_back(0);
                    emptyVoxellist.push_back(0);
                    attachVoxelList.push_back(0);

                    if (puzzleArray[i][j][k] > 0.1)
                        printf("1 ");

                    else
                        printf("0 ");
                }
                printf("\n");
            }
            printf("\n");
        }

        printf("\n\n");

        printf("Volume Size: %d %d %d\n\n", initVolumeSize(0), initVolumeSize(1), initVolumeSize(2));
    }
}



///=========================================================================================///
///                                   Voxel Operation
///=========================================================================================///

Puzzle * Puzzle_smooth::AttachVoxel(vector<int> puzzleData, int pieceNum)
{
    Puzzle *currPuzzle = NULL;
    vector<int> currPuzData = puzzleData;
    vector<vector <int>> connectivityEdgeList;

//    printf("begin.\n");

    successAttachNum = 0;

    // Remove Attached Voxels (if any)
    for (int i = 0; i < attachVoxelList.size(); ++i)
    {
        if (attachVoxelList[i] == 1 and currPuzData[i] != 0)
        {
            currPuzData[i] = 0;
//            printf("1\n");
        }
    }

    // Attach Voxels
    for (int i = 0; i < attachVoxelList.size(); ++i)
    {
        if (attachVoxelList[i] == 0)
            continue;

        else
        {
            vector<int> tempPuzData = currPuzData;
            for (int k = 0; k < pieceNum; ++k)
            {
                tempPuzData[i] = k + 1;
                currPuzzle = new Puzzle();
                currPuzzle->InitPuzzle(initVolumeSize, initVoxelSize, tempPuzData, connectivityEdgeList);

                /// Check if the puzzle is valid
                bool isValid = currPuzzle->CheckValidPuzzle();
                if (!isValid)
                    continue;

                /// Check the puzzle state
                currPuzzle->CheckPuzzleState(false, true);

                if ( currPuzzle->puzLockState  == PUZZLE_INTER_LOCK && currPuzzle->puzBuildState == PUZZLE_NORMAL_BUILDABLE && currPuzzle->puzDisconnectivityState == true)
                {
                    currPuzData = tempPuzData;
                    successAttachNum++;
                    break;
                }
            }
        }
    }

    printf("Attach Voxel Num: %d\n", attachVoxelNum);
    printf("Successful Attached Voxel Num: %d\n", successAttachNum);

    return currPuzzle;
}

Puzzle * Puzzle_smooth::AttachVoxel_full(vector<int> puzzleData, int pieceNum)
{
    Puzzle *currPuzzle = NULL;
    vector<int> currPuzData = puzzleData;
    vector<vector <int>> connectivityEdgeList;

//    printf("begin.\n");

    successAttachNum_full = 0;
//    attachVoxelNum_full = 0;

    for (int i = 0; i < attachVoxelList_full.size(); ++i)
    {
        if (attachVoxelList_full[i] == 0)
            continue;

        else
        {
            vector<int> tempPuzData = currPuzData;
            for (int k = 0; k < pieceNum; ++k)
            {
                tempPuzData[i] = k + 1;
                currPuzzle = new Puzzle();
                currPuzzle->InitPuzzle(initVolumeSize, initVoxelSize, tempPuzData, connectivityEdgeList);

                /// Check if the puzzle is valid
                bool isValid = currPuzzle->CheckValidPuzzle();
                if (!isValid)
                    continue;

                /// Check the puzzle state
                currPuzzle->CheckPuzzleState(false, true);

                if ( currPuzzle->puzLockState  == PUZZLE_INTER_LOCK && currPuzzle->puzBuildState == PUZZLE_NORMAL_BUILDABLE && currPuzzle->puzDisconnectivityState == true)
                {
                    currPuzData = tempPuzData;
                    successAttachNum_full++;
                    break;
                }
            }
        }
    }

    printf("Attach Voxel Num: %d\n", attachVoxelNum_full);
    printf("Successful Attached Voxel Num: %d\n", successAttachNum_full);

    return currPuzzle;
}
