///////////////////////////////////////////////////////////////
//
// PuzzleCreator.cpp
//
//   3D Puzzle Creator Class
//
// by Peng Song and Rulin Chen
//
// 27/Aug/2021
//
//
///////////////////////////////////////////////////////////////

#include "time.h"
#include "Utility/HelpDefine.h"
#include "Utility/HelpPuz.h"
#include "PieceFace.h"
#include "Piece.h"
#include "PieceGroup.h"
#include "PuzAction.h"
#include "PuzSolver.h"
#include "Volume.h"
#include "Puzzle.h"
#include "PuzzleCreator.h"

#ifdef DEBUG_PUZZLE
vector<int> failCaseNums;
vector<int> failDisconnCaseNums;
vector<int> disconnGroupNums;
#endif

extern Vector3i neiborPos[6];


///=========================================================================================///
///                                   Initialization
///=========================================================================================///

PuzzleCreator::PuzzleCreator()
{
    volume = NULL;
}

PuzzleCreator::~PuzzleCreator()
{

}

void PuzzleCreator::InitPuzzleCreator(Volume *_volume)
{
    volume = _volume;
}




///=========================================================================================///
///               Create Interlocking, Buildable and Multi-Steps Puzzle
///=========================================================================================///

Puzzle* PuzzleCreator::CreateBuildablePuzzle(int pieceNum, int keyLevel, bool isFixLastPiece, float variance)
{
    Puzzle *puzzle = NULL;
    int trialNum = 0;
    int highestLevel = 0;
    int levelPuzCount[100] = {0};
    float timePuzCount[100]  = {0};
    int graphConfigNumCount[100] = {0};
    int successPuzNum = 0;
    int num = 0;

    clock_t beginTime = clock();
    clock_t endTime;
    float elapsed;

    while ( true )
    {
        trialNum++;

        printf("\n========================\n");
        printf("TrialNum: %d \n", trialNum);

        if( puzzle != NULL )
        {
            delete puzzle;
            puzzle = NULL;
        }

        puzzle = new Puzzle();
        puzzle->SetVolume( volume );

        PartitionVolume_Subdiv(puzzle, pieceNum, keyLevel, variance);

        if ( puzzle->pieceList.size() != pieceNum )
            continue;

        puzzle->CheckPuzzleState(false, true);
        //puzzle->PrintPuzzle();

        if ( puzzle->puzLockState  == PUZZLE_INTER_LOCK &&
             puzzle->puzBuildState == PUZZLE_NORMAL_BUILDABLE &&
             puzzle->puzDisconnectivityState == true)
        {
            levelPuzCount[puzzle->puzLevel] += 1;

            if (timePuzCount[puzzle->puzLevel] == 0)
            {
                endTime = clock();
                timePuzCount[puzzle->puzLevel] = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);
            }

            graphConfigNumCount[puzzle->puzLevel] += puzzle->puzGraphConfigsNum;

            successPuzNum++;

            printf("level: %d \n", puzzle->puzLevel);

            if (puzzle->puzLevel >= keyLevel)
            {
                highestLevel = puzzle->puzLevel;

#ifdef ANTO_SAVE
                endTime = clock();
                elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);

                printf("Saving current puzzle.\n");
                printf("kernelGraphConfigNum: %d\n", puzzle->kernalGraphConfigNum);

                string puzFolderPath;
                if (puzzle->kernalGraphConfigNum <= pieceNum + 1)
                    puzFolderPath = "/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/puzzle_highest_level/Cube_5x5x5_E1/Cube_5x5x5_E1_K" + to_string(pieceNum) + "_auto_save_small_graph";
                else if (puzzle->kernalGraphConfigNum >= pieceNum * 4)
                    puzFolderPath = "/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/puzzle_highest_level/Cube_5x5x5_E1/Cube_5x5x5_E1_K" + to_string(pieceNum) + "_auto_save_big_graph";
                else
                    puzFolderPath = "/Users/linsanity/Documents/Github/DisassemblyPuzzle/SourceCode/Multi-LevelPuzzle/puzzle_highest_level/Cube_5x5x5_E1/Cube_5x5x5_E1_K" + to_string(pieceNum) + "_auto_save_normal_graph";

                string puzzleName = "Cube_5x5x5_E1_K" + to_string(pieceNum) + "_L" + to_string(puzzle->puzLevel) + "_" + to_string(num) + "_" + to_string(puzzle->kernalGraphConfigNum);

                num++;

                string puzzleFullName = puzFolderPath + "/" + puzzleName;

                puzzle->volume->WritePuzzleFile(puzzleFullName.c_str(), elapsed);

#else
                break;
#endif
            }

        }

        endTime = clock();
        elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);

        if (elapsed > 120)
            break;
    }

#ifdef DEBUG_PUZZLE
    int totalNum = 0;
    for (int i=0; i<failCaseNums.size(); i++)
        totalNum += failCaseNums[i];

    printf("\n====================Failure Case Statistics====================\n");
    printf("case 1: fail to construct the key       num: %4d    ratio: %4.1f %%\n", failCaseNums[0], 100*failCaseNums[0]/(float)totalNum);
    printf("case 2: fail to construct a piece       num: %4d    ratio: %4.1f %%\n", failCaseNums[1], 100*failCaseNums[1]/(float)totalNum);
    printf("case 3: remainPiece disconnected        num: %4d    ratio: %4.1f %%",   failCaseNums[2], 100*failCaseNums[2]/(float)totalNum);
    printf("  failDisconnCaseNums: ");
    for (int i = 0; i < failDisconnCaseNums.size(); ++i)
    {
        printf(" %d ", failDisconnCaseNums[i]);
    }
    printf("  disconnGroupNums: ");
    for (int i = 0; i < disconnGroupNums.size(); ++i)
    {
        printf(" %d ", disconnGroupNums[i]);
    }
    printf("\n");
    printf("case 4: keyPiece not movable            num: %4d    ratio: %4.1f %%\n", failCaseNums[3], 100*failCaseNums[3]/(float)totalNum);
    printf("case 5: keyPiece not disassembled       num: %4d    ratio: %4.1f %%\n", failCaseNums[4], 100*failCaseNums[4]/(float)totalNum);
    printf("case 6: interPuzzle not interlocking    num: %4d    ratio: %4.1f %%\n", failCaseNums[5], 100*failCaseNums[5]/(float)totalNum);
    printf("case 7: interPuzzle removable group     num: %4d    ratio: %4.1f %%\n", failCaseNums[6], 100*failCaseNums[6]/(float)totalNum);
    printf("case 8: finalPuzzle not interlocking    num: %4d    ratio: %4.1f %%\n", failCaseNums[7], 100*failCaseNums[7]/(float)totalNum);
    printf("case 9: finalPuzzle not disassembled    num: %4d    ratio: %4.1f %%\n", failCaseNums[8], 100*failCaseNums[8]/(float)totalNum);
    printf("\n");

#endif

    printf("\n=======================Level Statistics========================\n");
    for (int i = 2; i <= highestLevel; i++)
    {
        printf("Level: %d      num: %4d    ratio: %4.1f       time: %.3f mins       averageConfigNum: %4.1f\n", i, levelPuzCount[i], 100*levelPuzCount[i]/(float)successPuzNum, timePuzCount[i], graphConfigNumCount[i] / (float)levelPuzCount[i]);
    }
    printf("\n");

    /// Print the puzzle piece information
    printf("----------------------------------------------\n");
    printf("Puzzle Piece Number:  %d \n\n", pieceNum);
    for (int i=0; i<puzzle->pieceList.size(); i++)
        printf("Piece %2d: %3ld voxels \n", puzzle->pieceList[i]->pieceID, puzzle->pieceList[i]->voxelList.size());
    printf("\n");

    endTime = clock();
    //elapsed = ((float) (endTime - beginTime)) / (CLOCKS_PER_SEC);
    //printf("\nThe time taken to create buildable puzzle is %.3f seconds \n\n", elapsed);

    elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);
    printf("\nThe time taken to create buildable puzzle is %.3f mins \n\n", elapsed);

    puzzle->generationTime = elapsed;

    return puzzle;
}

void PuzzleCreator::PartitionVolume_Subdiv(Puzzle *puzzle, int pieceNum, int keyLevel, float variance)
{
    int maxSubdivTimes = 0.6*puzzle->volume->GetVolumeVoxelNum(); // Maximum subdivision times
    vector<int> pieceVoxelNums = GetPieceVoxelNum(pieceNum, puzzle->volume->GetVolumeVoxelNum(), 0, variance); // Number of voxels of each piece

    // The whole puzzle is the first original piece
    Piece *rootPiece = new Piece;
    rootPiece->pieceID = 0;
    puzzle->volume->InitializeRootPiece(rootPiece);

    puzzle->pieceList.push_back(rootPiece);

    while ( true )
    {
        bool isSuceess = ConstructPiece(puzzle, pieceNum, keyLevel, maxSubdivTimes, pieceVoxelNums);

        //puzzle->volume->PrintVolume();

        if ( isSuceess == false || puzzle->pieceList.size() == pieceNum )
            break;
    }
}

vector< vector<int> > PuzzleCreator::CreateBuildablePuzzle_creator(int pieceNum, int keyLevel, bool isFixLastPiece, float variance, float timeLimit, int k, bool & isNeedModification)
{
    Puzzle *puzzle = NULL;

    int trialNum = 0;
    int highestLevel = 0;
    int levelPuzCount[100] = {0};
    float timePuzCount[100]  = {0};
    int graphConfigNumCount[100] = {0};
    int successPuzNum = 0;

    vector< vector<int> > puzzleCandidates;
    vector<int> puzzleCandidatesLevel;
    for (int i = 0; i < k; ++i)
    {
        puzzleCandidatesLevel.push_back(0);
    }

    clock_t beginTime = clock();
    clock_t endTime;
    float elapsed;

    printf("begin.\n");

    while ( true )
    {
        trialNum++;

        printf("\n========================\n");
        printf("TrialNum: %d \n", trialNum);

        if( puzzle != NULL )
        {
            delete puzzle;
            puzzle = NULL;
        }

        puzzle = new Puzzle();
        puzzle->SetVolume( volume );

        PartitionVolume_Subdiv(puzzle, pieceNum, keyLevel, variance);

        if ( puzzle->pieceList.size() != pieceNum )
            continue;

        puzzle->CheckPuzzleState(true, true);

        if ( puzzle->puzLockState  == PUZZLE_INTER_LOCK &&
             puzzle->puzBuildState == PUZZLE_NORMAL_BUILDABLE &&
             puzzle->puzDisconnectivityState == true)
        {
            graphConfigNumCount[puzzle->puzLevel] += puzzle->puzGraphConfigsNum;
            successPuzNum++;

            levelPuzCount[puzzle->puzLevel] += 1;

            if (timePuzCount[puzzle->puzLevel] == 0)
            {
                endTime = clock();
                timePuzCount[puzzle->puzLevel] = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);
            }

            // Update current highestLevel
            if (puzzle->puzLevel > highestLevel)
            {
                highestLevel = puzzle->puzLevel;
            }

            printf("currlevel: %d \n", puzzle->puzLevel);

            // Update the puzzle candidates list
            for (int i = 0; i < k; ++i)
            {
                printf("puzzleCandidatesLevel[%d] = %d\n", i, puzzleCandidatesLevel[i]);
                if (puzzle->puzLevel > puzzleCandidatesLevel[i])
                {
                    vector< int > tempPuzzleData;
                    for (int j = 0; j < puzzle->volume->GetVoxelGrid().size(); ++j)
                    {
                        tempPuzzleData.push_back(puzzle->volume->GetVoxelGrid()[j]->piece + 1);
                    }

                    puzzleCandidatesLevel[i] = puzzle->puzLevel;

                    if (i >= puzzleCandidates.size())
                    {
                        puzzleCandidates.push_back(tempPuzzleData);
                    }
                    else
                    {
                        puzzleCandidates[i].clear();
                        puzzleCandidates[i] = tempPuzzleData;
                    }
                    break;
                }
            }

            if (puzzle->puzLevel == keyLevel)
            {
//                tempPuzzle_debug.origPuzzle = *puzzle;
                highestLevel = puzzle->puzLevel;

                puzzleCandidates.clear();

                vector< int > tempPuzzleData;
                for (int j = 0; j < puzzle->volume->GetVoxelGrid().size(); ++j)
                {
                    tempPuzzleData.push_back(puzzle->volume->GetVoxelGrid()[j]->piece + 1);
                }

                puzzleCandidates.push_back(tempPuzzleData);

                isNeedModification = false;

                break;
            }
        }

        endTime = clock();
        elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);

        if (elapsed > timeLimit)
            break;
    }

    if( puzzle != NULL )
    {
        delete puzzle;
        puzzle = NULL;
    }


    printf("\n=======================Level Statistics========================\n");
    for (int i = 2; i <= highestLevel; i++)
    {
        printf("Level: %d      num: %4d    ratio: %4.1f       time: %.3f mins       averageConfigNum: %4.1f\n", i, levelPuzCount[i], 100*levelPuzCount[i]/(float)successPuzNum, timePuzCount[i], graphConfigNumCount[i] / (float)levelPuzCount[i]);
    }
    printf("\n");

    printf("\n=======================Debug Statistics========================\n");
    printf("isNeedModification: %d\n", isNeedModification);
    for (int i = 0; i < k; ++i)
    {
        if (puzzleCandidatesLevel[i] != 0)
        {
            printf("Puzzle_%d Level: %d \n", i, puzzleCandidatesLevel[i]);
            for (int j = 0; j < puzzleCandidates[i].size(); ++j)
            {
                printf("%d ", puzzleCandidates[i][j]);
            }
            printf("\n\n");
        }
    }

    endTime = clock();
    elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);
    printf("\nThe time taken to create buildable puzzle is %.3f mins \n\n", elapsed);

    return puzzleCandidates;
}

bool PuzzleCreator::ConstructPiece(Puzzle *puzzle, int pieceNum, int keyLevel, int maxSubdivTimes, vector<int> pieceVoxelNums)
{
    int lastPieceID = puzzle->pieceList.size()-1;
    Piece *lastPiece = puzzle->pieceList[lastPieceID];
    Piece *remvPiece = NULL;
    Piece *restPiece = NULL;

    ComputePieceReachability(puzzle, lastPieceID);

    int subdivTimes = 0;

    while ( true )
    {
        // Recover the puzzle to the state before subdivision
        if( remvPiece != NULL || restPiece != NULL )
        {
            delete remvPiece;
            delete restPiece;
            puzzle->pieceList.erase(puzzle->pieceList.begin()+lastPieceID);
            puzzle->pieceList.erase(puzzle->pieceList.begin()+lastPieceID);
            puzzle->pieceList.push_back(lastPiece);

            puzzle->volume->UpdateVolume_PieceID( lastPiece );
        }

        // Stop subdivision if subdivide for too many times
        subdivTimes++;
        //printf("subdivTimes: %d \n", subdivTimes);
        if (subdivTimes > maxSubdivTimes)
            break;

        // Subdivide the last remaining piece
        int remvPieceVoxelNum = pieceVoxelNums[lastPieceID];
        remvPiece = new Piece;
        restPiece = new Piece;

        if ( lastPieceID == 0 )
        {
            SubdivideKey(puzzle, lastPiece, remvPiece, restPiece, remvPieceVoxelNum);
        }
        else
        {
            SubdividePiece(puzzle, lastPiece, remvPiece, restPiece, remvPieceVoxelNum);
        }

        puzzle->pieceList.erase(puzzle->pieceList.begin()+lastPieceID);
        puzzle->pieceList.push_back(remvPiece);
        puzzle->pieceList.push_back(restPiece);

        // Check if the subdivision is valid
        bool isSubdivisionValid = CheckPieceSubdivision( puzzle, pieceNum, keyLevel );

        if ( isSubdivisionValid )
        {
            delete lastPiece;

            return true;
        }
    }

    return false;
}




///=========================================================================================///
///                         Construct Puzzle Pieces by Subdivision
///=========================================================================================///

bool PuzzleCreator::SubdivideKey(Puzzle *puzzle, Piece *origPiece, Piece *remvPiece, Piece *restPiece, int remvAvgVoxelNum)
{
    /// 1. Construct geometry of the key piece
    PieceCreator pieceCreator;
    pieceCreator.InitPieceCreator(puzzle->pieceList, puzzle->volume->GetVolumeSize(), true);

    MainPath mainPath;
    bool isSucess = pieceCreator.ComputeMainPath(remvAvgVoxelNum, mainPath);

    //if ( !mainPath.isValid )
    if( isSucess == false )
        return false;

    /// 2. Create the key piece
    BuildRemovePiece( puzzle, origPiece, remvPiece, restPiece, mainPath.pathOrgVoxels);

    /// 3. For debugging the key piece construction
    vector<int> puzPieceIDs;
    puzPieceIDs.push_back(0);

    PuzConfig tempPuzConfig = PuzConfig();
    tempPuzConfig.InitiConfig(puzPieceIDs);

    return true;
}

bool PuzzleCreator::SubdividePiece(Puzzle *puzzle, Piece *origPiece, Piece *remvPiece, Piece *restPiece, int remvAvgVoxelNum)
{
    Vector3i volumeSize = puzzle->volume->GetVolumeSize();

    ///////////////////////////////////////////////////////////////////////////
    /// 1. Build a PuzConfig graph for the current intermediate puzzle

    PuzSolver puzSolver;
    puzSolver.InitPuzSolver(puzzle->pieceList, volumeSize);

//    printf("InitPuzSolver done.\n");

    vector<PuzConfig*> graphPuzConfigs;
    vector<PuzConfig*> pathPuzConfigs;

    int tempPuzLevel;
    int graphState = puzSolver.BuildPuzConfigGraph_Full(DISASS_FIX_LAST_PIECE, graphPuzConfigs,  tempPuzLevel);

//    printf("BuildPuzConfigGraph done.\n");

    if( graphState != DISASSEMBLY_GRAPH_NO_REMOVABLE_PIECE )
        return false;

    int maxDist = 0;
    for (int i=0; i<graphPuzConfigs.size(); i++)
    {
        if ( graphPuzConfigs[i]->distToRoot > maxDist )
        {
            maxDist = graphPuzConfigs[i]->distToRoot;
        }
    }

    //printf("\n==================================\n");
//    printf("maxDist: %d \n", maxDist );


    ///////////////////////////////////////////////////////////////////////////
    /// 2. Construct the puzzle piece in the furtherest PuzConfig

    int lastPieceID = origPiece->pieceID;

    PieceCreator pieceCreator;
    pieceCreator.InitPieceCreator(puzzle->pieceList, volumeSize, true);

    for (int i=0;  i<graphPuzConfigs.size(); i++)
    {
        if ( graphPuzConfigs[i]->distToRoot < maxDist)
            continue;

        MainPath mainPath = pieceCreator.ComputeMainPath(graphPuzConfigs, i, lastPieceID, remvAvgVoxelNum);

        if ( !mainPath.isValid )
        {
            continue;
        }

        BuildRemovePiece( puzzle, origPiece, remvPiece, restPiece,  mainPath.pathOrgVoxels);

        for (int j=0; j<graphPuzConfigs.size(); j++)
            delete graphPuzConfigs[j];

        return true;
    }

    for (int i=0; i<graphPuzConfigs.size(); i++)
        delete graphPuzConfigs[i];

    return false;
}

bool PuzzleCreator::CheckPieceSubdivision(Puzzle *puzzle, int pieceNum, int keyLevel)
{
	int removePieceID = puzzle->pieceList.size()-2;
	int remainPieceID = puzzle->pieceList.size()-1;

    /////////////////////////////////////////////////////////////////
    /// 1. Check if each piece is successfully constructed

    if( puzzle->pieceList[remainPieceID]->voxelList.size() == 0)
    {
#ifdef DEBUG_PUZZLE
        if ( puzzle->pieceList.size() == 2 )
        {
            printf("Case 0: Fail to construct the key piece! \n\n");
            failCaseNums[0]++;
        }
        else
        {
            printf("Case 1: Fail to construct a normal piece! \n\n");
            failCaseNums[1]++;
        }
#endif

        return false;
    }

	/////////////////////////////////////////////////////////////////
	/// 2. Check if the remaining piece is connected

	bool isRemainConnected = puzzle->pieceList[remainPieceID]->CheckConnectivity();
	if ( !isRemainConnected )
	{
#ifdef DEBUG_PUZZLE
		printf("Case 2: The remainPiece is disconnected! \n\n");
		failCaseNums[2]++;

		failDisconnCaseNums[remainPieceID]++;

		int disconnGroupNum = puzzle->pieceList[remainPieceID]->ConnectivityAnalysis();
		disconnGroupNums[disconnGroupNum]++;
#endif
		return false;

		//if ( pieceList.size() == 2 )	return false;
		//else						    return true;
	}


	/////////////////////////////////////////////////////////////////
	/// 3. Check the subdivision of the key piece

	if ( puzzle->pieceList.size() == 2 )
	{
		vector<int> pieceIDList;
		pieceIDList.push_back(removePieceID);
		pieceIDList.push_back(remainPieceID);

		// The key piece should be movable
        int puzLockState = puzzle->CheckPuzzleLockState();

		if ( puzLockState != PUZZLE_PIECE_MOVE )
		{
#ifdef DEBUG_PUZZLE
			//printf("Case 3: The key piece is not movable. \n\n");
			failCaseNums[3]++;
#endif
			return false;
		}

		// The key piece should not be able to disassembled with the rest piece
        PuzSolver puzSolver;
        puzSolver.InitPuzSolver(puzzle->pieceList, puzzle->volume->GetVolumeSize());

        int buildState = puzSolver.DisassemblyPuzzzle(DISASS_FIX_LAST_PIECE);
		if( buildState != PUZZLE_NO_REMOVE_GROUP )
		{
#ifdef DEBUG_PUZZLE
			printf("Case 4: The key piece and remainPiece can be disassembled. \n\n");
			failCaseNums[4]++;
#endif
			return false;
		}
	}


	/////////////////////////////////////////////////////////////////
	/// 4. Check the subdivision of a intermediate piece

	else if ( puzzle->pieceList.size() >= 3 && puzzle->pieceList.size() < pieceNum )
	{
		// The current puzzle should be interlocking
        int puzLockState = puzzle->CheckPuzzleLockState();

		if ( puzLockState != PUZZLE_INTER_LOCK )
		{
#ifdef DEBUG_PUZZLE
			printf("Case 5: The intermediate puzzle is not interlocking. \n\n");
			failCaseNums[5]++;
#endif
			return false;
		}

		// Before the subdivision of piece with certain index, no piece is removable
		// TODO: need to investigate this parameter
		//if ( puzzle->pieceList.size() < 0.8*pieceNum )
		//if ( pieceList.size() <= pieceNum-1 )
		{
            PuzSolver puzSolver;
            puzSolver.InitPuzSolver(puzzle->pieceList, puzzle->volume->GetVolumeSize());

            int buildState = puzSolver.DisassemblyPuzzzle(DISASS_FIX_LAST_PIECE);
			if( buildState != PUZZLE_NO_REMOVE_GROUP )
			{
#ifdef DEBUG_PUZZLE
				printf("Case 6: There exists removable group in the intermediate puzzle. \n\n");
				failCaseNums[6]++;
#endif
				return false;
			}
		}
	}


	/////////////////////////////////////////////////////////////////
	/// 5. Check the subdivision of the last piece

	else if( puzzle->pieceList.size() == pieceNum )
	{
		// The current puzzle should be interlocking
        int puzLockState = puzzle->CheckPuzzleLockState();

		if ( puzLockState != PUZZLE_INTER_LOCK )
		{
#ifdef DEBUG_PUZZLE
			printf("Case 7: The final puzzle is not interlocking! \n\n");
			failCaseNums[7]++;
#endif
			return false;
		}

		// The puzzle should be disassemblable
        PuzSolver puzSolver;
        puzSolver.InitPuzSolver(puzzle->pieceList, puzzle->volume->GetVolumeSize());

        int buildState = puzSolver.DisassemblyPuzzzle(DISASS_FIX_LAST_PIECE);
		if( buildState != PUZZLE_NORMAL_BUILDABLE )
		{
#ifdef DEBUG_PUZZLE
			printf("Case 8: The final puzzle cannot be disassembled! \n\n");
			failCaseNums[8]++;
#endif
			return false;
		}
	}
	return true;	
}

void PuzzleCreator::ComputePieceReachability(Puzzle *puzzle, int pieceID)
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

	//float maxReach = -1;
	//float minReach = 100000;
	//for (int i=0; i<pieceList[pieceID]->voxelList.size(); i++)
	//{
	//	if ( pieceList[pieceID]->voxelList[i]->reach > maxReach )
	//		maxReach = pieceList[pieceID]->voxelList[i]->reach;

	//	if ( pieceList[pieceID]->voxelList[i]->reach < minReach )
	//		minReach = pieceList[pieceID]->voxelList[i]->reach;
	//}
	//printf("MaxReach: %.3f  MinReach: %.3f\n", maxReach, minReach);
}


void PuzzleCreator::BuildRemovePiece(Puzzle *puzzle, Piece *origPiece, Piece *remvPiece, Piece *restPiece, vector<Vector3i> remvVoxels)
{
	int origVoxelNum = origPiece->voxelList.size();
	vector<bool> isRemoveVoxel(origVoxelNum, false);

	// Generate the removePiece
	remvPiece->pieceID = origPiece->pieceID;
	for (int i=0; i<remvVoxels.size(); i++)
	{
		int origVoxelIndex = GetVoxelIndexInList(origPiece->voxelList, remvVoxels[i]);
		isRemoveVoxel[origVoxelIndex] = true;
		remvPiece->AddVoxel(origPiece->voxelList[origVoxelIndex]);

		Vector3i origVoxelPos = origPiece->voxelList[origVoxelIndex]->pos;

        puzzle->volume->SetVolumeVoxelPieceID(origVoxelPos, remvPiece->pieceID);
	}

	// Generate the remaining piece
	restPiece->pieceID = origPiece->pieceID + 1;
	for (int i=0; i<isRemoveVoxel.size(); i++)
	{
		if ( !isRemoveVoxel[i] )
		{
			restPiece->AddVoxel(origPiece->voxelList[i]);

			// Don't change pieceID of the voxels on origPiece
			origPiece->voxelList[i]->piece = origPiece->pieceID;

            puzzle->volume->SetVolumeVoxelPieceID(origPiece->voxelList[i]->pos, restPiece->pieceID);
		}
	}
}

void PuzzleCreator::DeleteCurrPiece(Puzzle *puzzle, Piece *origPiece, Piece *remvPiece, Piece *restPiece, vector<Vector3i> remvVoxels)
{

}
