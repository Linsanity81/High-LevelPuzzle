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
// TODO List:
// (1) Have top priority to select the seed voxels that allow the previous pieces to move back
// (2) Check the voxel selection which should be random and heuristic (e.g., based on voxel
//     reachability value, distance to certain voxel such as SeedVoxel)
// 
///////////////////////////////////////////////////////////////

#include "Utility/HelpDefine.h"
#include "PieceFace.h"
#include "Piece.h"
#include "PuzConfig.h"
#include "ExpVolume.h"
#include "PieceCreator.h"


extern Vector3i neiborPos[6];
extern char axisArray[6][4];

///=========================================================================================///
///                                    Initialization
///=========================================================================================///

PieceCreator::PieceCreator()
{
	expVolume = NULL;
}

PieceCreator::~PieceCreator()
{
	ClearPieceCreator();
}

void PieceCreator::ClearPieceCreator()
{
	if( expVolume != NULL )
    {
        delete expVolume;
        expVolume = NULL;
    }

	for (int i=0; i<pieceList.size(); i++)
	{
		pieceList[i]->ClearPiece();
	}
	pieceList.clear();
}

void PieceCreator::InitPieceCreator(vector<Piece*> puzPieces, Vector3i puzVolumeSize, bool isCopyReachValue)
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

	expVolume->InitExpVolume(puzPieces, puzVolumeSize, isCopyReachValue);
}




///=========================================================================================///
///                                    Utility Functions
///=========================================================================================///

int PieceCreator::RandomlySelectVoxel(vector<Voxel*> voxelList, float beta)
{
    vector<float> voxelPossibList;
    for (int i=0; i<voxelList.size(); i++)
    {
        float voxelPossib = (MAX_VOXEL_REACH - voxelList[i]->reach);

        voxelPossibList.push_back( voxelPossib );
    }

    int voxelIndex;

    // If alpha is equal to -1, select extend voxel with largest possibility value
    if ( beta < 0 )
    {
        vector<int> extdIndices = BubbleSort(voxelPossibList, false);
        voxelIndex = extdIndices[0];
    }
    // Else, select extend voxel based on mapped its possibility value
    else
    {
        voxelIndex = GetRandomObjIndex( voxelPossibList, beta );
    }

    return voxelIndex;
}

bool PieceCreator::IsRemainPieceConnected(int lastPieceID, vector<Vector3i> mainPathVoxels, Vector3i mainPathCandiVoxel)
{
    vector<Vector3i> remainVoxels;
    for (int i = 0; i < pieceList[lastPieceID]->voxelList.size(); ++i)
    {
        Vector3i voxelPos = pieceList[lastPieceID]->voxelList[i]->pos;

        if (std::find(mainPathVoxels.begin(), mainPathVoxels.end(), voxelPos) == mainPathVoxels.end() &&
            voxelPos != mainPathCandiVoxel )
        {
            remainVoxels.push_back( voxelPos );
        }
    }

    if ( CheckVoxelsConnectivity(remainVoxels) == false )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool PieceCreator::IsRemainPieceConnected(int lastPieceID, vector<Vector3i> mainPathVoxels)
{
    vector<Vector3i> remainVoxels;
    for (int i = 0; i < pieceList[lastPieceID]->voxelList.size(); ++i)
    {
        Vector3i voxelPos = pieceList[lastPieceID]->voxelList[i]->pos;

        if (std::find(mainPathVoxels.begin(), mainPathVoxels.end(), voxelPos) == mainPathVoxels.end() )
        {
            remainVoxels.push_back( voxelPos );
        }
    }

    if ( CheckVoxelsConnectivity(remainVoxels) == false )
    {
        return false;
    }
    else
    {
        return true;
    }
}




///=========================================================================================///
///                                  Subdivide the Key Piece
///=========================================================================================///

///----------------------------------------------------------------------
/// Compute MainPath for the key piece
///----------------------------------------------------------------------

bool PieceCreator::ComputeMainPath(int remvVoxelNum, MainPath &mainPath)
{
    ////////////////////////////////////////////////////////////////
    /// 1. Build contacting graph for the initial volume/puzzle

    PuzConfig tagtPuzConfig;
    tagtPuzConfig.pieceIDList.push_back(0);
    tagtPuzConfig.piecePosList.push_back(Vector3i(0,0,0));
    expVolume->BuildConfigContactGraph(&tagtPuzConfig, pieceList);


    ////////////////////////////////////////////////////////////////
    /// 2. Create SeedPath and check its motion space

    mainPath.isValid = false;

    vector<Vector3i> emptyVoxels = expVolume->ComputeEmptyVoxels(pieceList);

    //vector<Vector3i> voxelList = emptyVoxels;
    //for (int i = 0; i < voxelList.size(); ++i)
    //{
    //    printf("%d %d %d.\n", voxelList[i](0), voxelList[i](1), voxelList[i](2));
    //}

    SeedPath seedPath = CreateSeedPath(remvVoxelNum, emptyVoxels);

    if ( !seedPath.isValid )
        return false;

    seedPath.moveAxisIDs = expVolume->CheckSeedPathMotion(seedPath.pieceAxisID, seedPath.pathVoxels);


    ////////////////////////////////////////////////////////////////
    /// 3. Create blockPath from blockVoxel to seedPath

    BlockPath blockPath;
    if ( seedPath.moveAxisIDs.size() != 0 )
    {
        blockPath = CreateBlockPath(seedPath, remvVoxelNum);

        if ( blockPath.pathVoxels.size() == 0 )
            return false;
    }


    ////////////////////////////////////////////////////////////////
    /// 4. Check if the mainPath is valid or not

    mainPath.pathVoxels = seedPath.pathVoxels;
    for (int i=0; i<blockPath.pathVoxels.size(); i++)
    {
        mainPath.pathVoxels.push_back( blockPath.pathVoxels[i] );
    }
    //mainPath.pathOrgVoxels = expVolume->Exp2OrgVoxels( mainPath.pathVoxels );

    if ( mainPath.pathVoxels.size() > remvVoxelNum)
        return false;

    //if( IsRemainPieceConnected(seedPath.pieceID, mainPath.pathOrgVoxels ) == false )
    //{
    //    return false;
    //}


    ////////////////////////////////////////////////////////////////
    /// 5. Extend mainPath to include fragmental voxels

    mainPath.pieceID      = seedPath.pieceID;
    mainPath.pieceAxisID  = seedPath.pieceAxisID;
    mainPath.keptVoxels   = blockPath.keptVoxels;
    mainPath.keptVoxels.push_back( seedPath.keptVoxels[0] ); // Note: SeedPath of the key piece only has one seedVoxel and one keptVoxel
    mainPath.pathOrgVoxels = expVolume->Exp2OrgVoxels( mainPath.pathVoxels );

    //printf("Key Piece: Main path number: %lu\n", mainPath.pathVoxels.size());


    /*if( mainPath.pathVoxels.size() < 0.8*remvVoxelNum)
    {
        ExtendMainPath(mainPath, remvVoxelNum);

        if (  mainPath.pathVoxels.size() > 1.2*remvVoxelNum)
            return false;
    }*/

    ExtendMainPath(mainPath, remvVoxelNum);

    if ( mainPath.pathVoxels.size() != remvVoxelNum )
        return false;

    mainPath.isValid  = true;
    return true;
}


///----------------------------------------------------------------------
/// Compute Seed Path for the key piece
///----------------------------------------------------------------------

SeedPath PieceCreator::CreateSeedPath(int remvVoxelNum, vector<Vector3i> emptyVoxels)
{
	int lastPieceID = 0;
	SeedPath seedPath;

	// Find possible SeedVoxels for the remvPiece
	vector<SeedPath> tempPathCandis = FindPieceSeedVoxels(emptyVoxels);

	if ( tempPathCandis.size() == 0 )
		return seedPath;

	// Compute the corresponding SeedPath for each SeedVoxel
	for (int i=0; i<tempPathCandis.size(); i++)
	{
		ComputeSeedPathVoxels(tempPathCandis[i]);

		int pathVoxelNum = tempPathCandis[i].pathVoxels.size();
		if ( pathVoxelNum == 1 || pathVoxelNum > 0.8*remvVoxelNum )
			tempPathCandis[i].isValid = false;
		else
			tempPathCandis[i].isValid = true;
	}

	// Remove the invalid SeedPath
	vector<SeedPath> seedPathCandis;
	for (int i=0; i<tempPathCandis.size(); i++)
	{
		if ( tempPathCandis[i].isValid )
		{
			seedPathCandis.push_back( tempPathCandis[i] );
		}
	}

	//printf(" temp: %d  seed: %d \n ", tempPathCandis.size(), seedPathCandis.size() );

	if ( seedPathCandis.size() == 0 )
		return seedPath;

	// Calculate the possibility value of each seedPath candidate
	vector<float> pathPossibList;
	for (int i=0; i<seedPathCandis.size(); i++)
	{
		float pathPossib = 0;
		for (int j=0; j<seedPathCandis[i].pathVoxels.size(); j++)
		{
			Vector3i voxelPos = seedPathCandis[i].pathVoxels[j];
            Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(voxelPos, EXPA_VOLUME);

			//pathPossib += seedPathCandis[i].pathVoxels[j]->reach;
			pathPossib += tempExpVoxel->reach;
		}

		if ( pathPossib != 0 )
			pathPossib = 1.0 / pathPossib;
		pathPossibList.push_back(pathPossib);
	}

	// Randomly select one seedPath
	int pathCandiIndex = GetRandomObjIndex(pathPossibList, 3);
	seedPath = seedPathCandis[pathCandiIndex];

	//printf("number of seed path: %d\n", seedPathCandis.size());

	return seedPath;
}

vector<SeedPath> PieceCreator::FindPieceSeedVoxels(vector<Vector3i> emptyVoxels)
{
    ///////////////////////////////////////////////////////
    // 1. Find all the seed voxel candidates

    int lastPieceID = 0;
    vector<SeedPath> tempSeedCandis;

    for (int j=0; j<6; j++)
    {
        for (int i=0; i<emptyVoxels.size(); i++)
        {
            // Possible SeedVoxel is the neighboring voxel of emptyVoxel in all the six directions
            Vector3i seedVoxelPos = emptyVoxels[i] + neiborPos[j];
            Voxel* seedExpVoxel = expVolume->GetExpVolumeVoxel(seedVoxelPos, EXPA_VOLUME);

            int pieceAxisID = GetReverseAxisID( j );
            int moveStepNum = expVolume->GetVoxelMoveSteps( seedVoxelPos, pieceAxisID);

            // The SeedVoxel should be on the volume and not be removable along revsAxisID
            if ( seedExpVoxel->piece == lastPieceID && moveStepNum != MAX_INT )
            {
                //Vector3i seedOrgVoxelPos = expVolume->Exp2OrgVoxel( seedVoxelPos );
                //int volumeAxisSize = expVolume->GetVolumeAxisSize( pieceAxisID );
                //int extremeAxisPos = expVolume->GetExtremeAxisPos( pieceAxisID );
                //int voxelAxisPos = expVolume->GetVoxelAxisPos( seedOrgVoxelPos, pieceAxisID );
                //int voxelAxisDist = abs(extremeAxisPos - voxelAxisPos);

                //int value = volumeAxisSize - voxelAxisDist;
                //printf("[%d %d %d] axisID: %d  volumeAxisSize: %d  extremeAxisPos: %d  voxelAxisPos: %d  dist: %d  value: %d \n",
                //        seedOrgVoxelPos[0], seedOrgVoxelPos[1], seedOrgVoxelPos[2],pieceAxisID, volumeAxisSize, extremeAxisPos, voxelAxisPos, voxelAxisDist, value);

                Vector3i keptVoxelPos = seedVoxelPos + (moveStepNum+1)*neiborPos[pieceAxisID];

                SeedPath tempSeedPath;
                tempSeedPath.pieceID     = lastPieceID;
                tempSeedPath.pieceAxisID = pieceAxisID;
                tempSeedPath.moveStep    = moveStepNum;
                tempSeedPath.seedPossib  = 0.6*moveStepNum + 0.4*(MAX_VOXEL_REACH-seedExpVoxel->reach);
                //tempSeedPath.seedPossib  = (MAX_VOXEL_REACH-seedExpVoxel->reach);
                //tempSeedPath.seedPossib  = 0.3f*(volumeAxisSize - voxelAxisDist) + 0.7f*(MAX_VOXEL_REACH-seedExpVoxel->reach);
                tempSeedPath.seedVoxels.push_back( seedVoxelPos );
                tempSeedPath.keptVoxels.push_back( keptVoxelPos );

                tempSeedCandis.push_back( tempSeedPath );
            }
        }
    }


    ///////////////////////////////////////////////////////
    // 2. Select up to six seed voxel candidates (with priority)

    vector<SeedPath> seedPathCandis;

    // Return if there is no seed voxel candidate
    const int maxSeedNum = 6;
    int seedVoxelNum = _MIN(maxSeedNum, tempSeedCandis.size());
    if ( seedVoxelNum == 0 )
        return seedPathCandis;

    // Get the indices of the selected candidates
    vector<float> seedPossibList;
    for (int i=0; i<tempSeedCandis.size(); i++)
        seedPossibList.push_back(tempSeedCandis[i].seedPossib);
    vector<int> seedIndices = GetRandomObjIndexList(seedPossibList, 3, seedVoxelNum);

    // Return these seed voxel candidates
    for (int i=0; i<seedIndices.size(); i++)
    {
        seedPathCandis.push_back( tempSeedCandis[seedIndices[i]] );
    }

    return seedPathCandis;
}

void PieceCreator::ComputeSeedPathVoxels(SeedPath &seedPath)
{
	if ( seedPath.seedVoxels.size() == 0 )
	{
		printf("Warning: There is no valid seed voxel. \n\n");
		return;
	}

	int pieceID     = seedPath.pieceID;
	int pieceAxisID = seedPath.pieceAxisID;

	// Find all the neighboring voxel on the volume along the perpendicular directions of pieceAxisID
	vector<int> perpAxisIDs = GetPerpAxisIDs( pieceAxisID );
	vector<Voxel*> neiborVoxelList;
	for (int i=0; i<perpAxisIDs.size(); i++ )
	{
		int axisID = perpAxisIDs[i];
		Vector3i neiborVoxelPos = seedPath.seedVoxels[0] + neiborPos[axisID];
		Voxel* currExpVoxel = expVolume->GetExpVolumeVoxel(seedPath.seedVoxels[0], EXPA_VOLUME);
        Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

        // Here consider the connectivity constraints
		if ( neiborExpVoxel->piece == pieceID)
		{
		    if (currExpVoxel->neiborVoxel[axisID] == NEIGHBOR_CONNECTED)
			    neiborVoxelList.push_back( neiborExpVoxel );
		}
	}

	// Randomly select one neighboring voxel and link this voxel to the piece surface along pieceAxisID
	seedPath.isValid = false;
	if ( neiborVoxelList.size() > 0 )
	{
		//int neiborIndex = neiborVoxelList.size() * rand()/(RAND_MAX+1.0);

        int neiborIndex = RandomlySelectVoxel(neiborVoxelList, 2.0);

        vector<Vector3i> linkedVoxels = expVolume->GetLinkedVoxels(neiborVoxelList[neiborIndex]->pos, pieceID, pieceAxisID, true);

		seedPath.pathVoxels = linkedVoxels;
		seedPath.pathVoxels.push_back( seedPath.seedVoxels[0] );

		seedPath.isValid = true;
	}
}


///----------------------------------------------------------------------
/// Compute BlockPath for a given SeedVoxel
///----------------------------------------------------------------------

BlockPath PieceCreator::CreateBlockPath(SeedPath seedPath, int remvVoxelNum)
{
	BlockPath blockPath;

	///////////////////////////////////////////////////////////////////
	// 1. Find blockVoxels; Return false if cannot find any blockVoxel

	vector<BlockPath> blockPaths = FindPieceBlockVoxels(seedPath);

	if ( blockPaths.size() == 0 )
		return blockPath;


	///////////////////////////////////////////////////////////////////
	// 2. Compute blockPath corresponding to each blockVoxel
	//    Return false if cannot find any non-empty blockPath

	vector<BlockPath> blkPathCandis;
	for (int i=0; i<blockPaths.size(); i++)
	{
		ComputeBlockPathVoxels(blockPaths[i], seedPath);

		if ( blockPaths[i].pathVoxels.size() > 0 &&
			 blockPaths[i].pathVoxels.size() < (remvVoxelNum - seedPath.pathVoxels.size()) )
			blkPathCandis.push_back(blockPaths[i]);
	}

	if ( blkPathCandis.size() == 0 )
		return blockPath;


	///////////////////////////////////////////////////////////////////
	// 3. Calculate possibility value of each blockPath
	//    Return one randomly selected blockPath

	vector<float> pathPossibList;
	for (int i=0; i<blkPathCandis.size(); i++)
	{
		float pathPossib = 0;
		for (int j=0; j<blkPathCandis[i].pathVoxels.size(); j++)
		{
			Vector3i voxelPos = blkPathCandis[i].pathVoxels[j];
            Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(voxelPos, EXPA_VOLUME);

			pathPossib += tempExpVoxel->reach;
		}

		if ( pathPossib != 0 )
			pathPossib = 1.0 / pathPossib;
		pathPossibList.push_back(pathPossib);
	}

	// Select one block path according to the possibility value
	int pathIndex = GetRandomObjIndex(pathPossibList, 3);
	return blkPathCandis[pathIndex];
}


vector<BlockPath> PieceCreator::FindPieceBlockVoxels(SeedPath seedPath)
{
	int pieceID     = seedPath.pieceID;
	int pieceAxisID = seedPath.pieceAxisID;
	vector<int> moveAxisIDs = seedPath.moveAxisIDs;

	////////////////////////////////////////////////////////////////
	// 1. Find appropriate blockVoxel candidates

	const int distSurfThres  = 3; // Unit: number of voxel
	const int maxBlkCandiNum = 20;
	vector<BlockPath> blkPathCandis;

	for (int i=0; i<pieceList[pieceID]->voxelList.size(); i++)
	{
		Vector3i orgVoxelPos = pieceList[pieceID]->voxelList[i]->pos;

        Vector3i expVoxelPos = expVolume->Org2ExpVoxel( orgVoxelPos );
        Voxel* expVoxel = expVolume->GetExpVolumeVoxel( expVoxelPos, EXPA_VOLUME );

		// The blockVoxel should not be the KeptVoxel of the seed path
		// The blockVoxel should not be in the PathVoxel list of the seed path
		if(	std::find(seedPath.keptVoxels.begin(), seedPath.keptVoxels.end(), expVoxelPos) == seedPath.keptVoxels.end() &&
			std::find(seedPath.pathVoxels.begin(), seedPath.pathVoxels.end(), expVoxelPos) == seedPath.pathVoxels.end() )
		{
			// The blockVoxel should be close to the piece surface along removePiece moving axis
            int blockDistSurf = expVolume->GetVoxelDistToPieceSurface(orgVoxelPos, pieceID, pieceAxisID);
			if(  blockDistSurf <= distSurfThres )
			{
				// The blockVoxel cannot move along the axis in pathMoveAxisIDs
				bool isBlockVoxel = true;
				for (int j=0; j<moveAxisIDs.size(); j++)
				{
					int axisID = moveAxisIDs[j];
					Vector3i neiborVoxelExpPos = expVoxelPos + neiborPos[axisID];
                    Voxel* neiborVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );

					if ( neiborVoxel->piece != pieceID ||
						 std::find(seedPath.pathVoxels.begin(), seedPath.pathVoxels.end(), neiborVoxelExpPos) != seedPath.pathVoxels.end())
					{
						isBlockVoxel = false;
					}
				}

				if ( isBlockVoxel )
				{
					BlockPath blockPath;
					blockPath.pieceID     = pieceID;
					blockPath.pieceAxisID = pieceAxisID;
					blockPath.blockVoxel  = expVoxelPos;
					blockPath.blkPossib   = 0.4*(distSurfThres-blockDistSurf) + 0.6*(MAX_VOXEL_REACH-expVoxel->reach);

					blkPathCandis.push_back( blockPath );
				}
			}
		}

		if ( blkPathCandis.size() >= maxBlkCandiNum )
		{
			break;
		}
	}

	vector<BlockPath> blockPaths;
	if ( blkPathCandis.size() == 0 )
		return blockPaths;


	////////////////////////////////////////////////////////////////
	// 2. Select up to six blockVoxels according their possibility value

	// Compute the possibility value of the block voxel candidates
	vector<float> possibList;
	for (int i=0; i<blkPathCandis.size(); i++)
	{
		possibList.push_back(blkPathCandis[i].blkPossib);
		//pieceList[origPieceID]->voxelList[voxelIndex]->color = 1.8*voxelPossib;
	}

	vector<int> voxelIndices = BubbleSort(possibList, false);
	int blockVoxelNum = _MIN(6.0, blkPathCandis.size()-1);

	for (int i=0; i<blockVoxelNum; i++)
	{
		int voxelIndex = voxelIndices[i];
		blockPaths.push_back(blkPathCandis[voxelIndex]);
	}


	////////////////////////////////////////////////////////////////
	// 3. Compute the linkVoxels and keptVoxels of each blockVoxel

	for (int i=0; i<blockPaths.size(); i++)
	{
		ComputeBlockKeptVoxels(blockPaths[i], seedPath);
	}

	return blockPaths;
}


void PieceCreator::ComputeBlockKeptVoxels(BlockPath &blockPath, SeedPath seedPath)
{
	int origPieceID = blockPath.pieceID;
	vector<int> seedPathAxisIDs = seedPath.moveAxisIDs;

	int revsAxisID = GetReverseAxisID( seedPath.pieceAxisID );

	////////////////////////////////////////////////////////////////////
	// Find the voxels that should be kept to block the blockVoxel

	vector<Vector3i> keptVoxels;
	for (int i=0; i<seedPathAxisIDs.size(); i++)
	{
		int axisID = seedPathAxisIDs[i];
		Vector3i neiborVoxelPos = blockPath.blockVoxel + neiborPos[axisID];

        Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);
		if ( neiborExpVoxel->piece == origPieceID )
		{
            vector<Vector3i> linkedVoxles = expVolume->GetLinkedVoxels(neiborVoxelPos, origPieceID, revsAxisID, true);

			for (int j=0; j<linkedVoxles.size(); j++)
			{
				if( std::find(keptVoxels.begin(), keptVoxels.end(), linkedVoxles[j]) == keptVoxels.end() )
				{
					keptVoxels.push_back( linkedVoxles[j] );
				}
			}
		}
	}

	blockPath.keptVoxels = keptVoxels;
}

void PieceCreator::ComputeBlockPathVoxels(BlockPath &blockPath, SeedPath seedPath)
{
	int pieceID     = blockPath.pieceID;
	int pieceAxisID = blockPath.pieceAxisID;

	//////////////////////////////////////////////////////////////////
	// 1. Create the voxel space in which to find the shortest path

	vector<Voxel*> voxelList;
	for (int i=0; i<pieceList[pieceID]->voxelList.size(); i++)
	{
		Voxel *tempOrgVoxel = pieceList[pieceID]->voxelList[i];
        Vector3i voxelExpPos = expVolume->Org2ExpVoxel( tempOrgVoxel->pos );

		if ( std::find(seedPath.keptVoxels.begin(),  seedPath.keptVoxels.end(),  voxelExpPos) == seedPath.keptVoxels.end() &&
			 std::find(blockPath.keptVoxels.begin(), blockPath.keptVoxels.end(), voxelExpPos) == blockPath.keptVoxels.end() )
		{
			voxelList.push_back( tempOrgVoxel );
		}
	}

	//////////////////////////////////////////////////////////////////
	// 2. Compute shortest path between the seedPath and the blockVoxel

    Vector3i srcVoxelPos = expVolume->Exp2OrgVoxel(  blockPath.blockVoxel );

	vector<Vector3i> tagtVoxelPosList;
    tagtVoxelPosList = expVolume->Exp2OrgVoxels( seedPath.pathVoxels );

	blockPath.isValid = false;

	// Here we consider the connectivity constraints when computing the shortest path
	vector<Vector3i> tempOrgVoxels = ComputeShortestPath(voxelList, srcVoxelPos, tagtVoxelPosList, false);


	//////////////////////////////////////////////////////////////////
	// 3. Construct the shortest path that connects the blockVoxel and seedPath

	if ( tempOrgVoxels.size() != 0 )
	{
		// Compute the shortest path voxels in ExpVolume
		vector<Vector3i> tempExpVoxels;
        tempExpVoxels = expVolume->Org2ExpVoxels( tempOrgVoxels );

		// Generate movable path in ExpVolume
		PuzConfig tagtPuzConfig;
		tagtPuzConfig.pieceIDList.push_back(0);
		tagtPuzConfig.piecePosList.push_back(Vector3i(0,0,0));
		vector<Vector3i> tempPathVoxels = GenerateMovablePath(&tagtPuzConfig, pieceID, pieceAxisID, tempExpVoxels);

		// Avoid duplicated voxels inside both SeedPath and BlockPath
		blockPath.isValid = true;
		blockPath.pathVoxels.clear();
		for (int i=0; i<tempPathVoxels.size(); i++)
		{
			if ( std::find(seedPath.pathVoxels.begin(), seedPath.pathVoxels.end(), tempPathVoxels[i]) == seedPath.pathVoxels.end() )
			{
				blockPath.pathVoxels.push_back( tempPathVoxels[i] );
			}
		}
	}
}


///----------------------------------------------------------------------
/// Extend MainPath to include fragmental voxels
///----------------------------------------------------------------------

void PieceCreator::ExtendMainPath(MainPath &mainPath, int remvVoxelNum)
{
	int lastPieceID = mainPath.pieceID;
	//int pieceAxisID = mainPath.pieceAxisID;

	////////////////////////////////////////////////////////////////////////////////
	/// 1. Find all the possible extendVoxels before mainPath extension

	vector<Voxel*> extdExpVoxelCandis;
	for (int i=0; i<mainPath.pathVoxels.size(); i++)
	{
		for (int j=0; j<6; j++)
		{
			Vector3i neiborVoxelExpPos = mainPath.pathVoxels[i] + neiborPos[j];
			Voxel* currExpVoxel = expVolume->GetExpVolumeVoxel( mainPath.pathVoxels[i], EXPA_VOLUME );
            Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );

			if( IsExtendVoxel(mainPath, neiborVoxelExpPos) )
			{
				if ( GetVoxelIndexInList(extdExpVoxelCandis, neiborVoxelExpPos) == VOXEL_OUT_LIST )
				{
				    if (currExpVoxel->neiborVoxel[j] == NEIGHBOR_CONNECTED)
					    extdExpVoxelCandis.push_back( neiborExpVoxel );
				}
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////////
	/// 2. Perform mainPath extension

	while( true )
	{
		int mainPathVoxelNum = mainPath.pathVoxels.size();
		if ( mainPathVoxelNum >= remvVoxelNum || extdExpVoxelCandis.size() == 0 )
			break;

		// Push back a randomly selected extendVoxel to the mainPath
		const int extdBeta = 3;
		int extdIndex = SelectExtendVoxel( mainPath, extdExpVoxelCandis, extdBeta);
		Voxel* extdExpVoxel = extdExpVoxelCandis[extdIndex];

        mainPath.pathOrgVoxels.push_back( expVolume->Exp2OrgVoxel ( extdExpVoxel->pos ) );
		mainPath.pathVoxels.push_back( extdExpVoxel->pos );

		// Update the extendVoxel candidates
		extdExpVoxelCandis.erase( extdExpVoxelCandis.begin() + extdIndex );

		for (int i=0; i<6; i++)
		{
			Vector3i neiborVoxelExpPos = extdExpVoxel->pos + neiborPos[i];
            Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );
            Voxel* currExpVoxel = expVolume->GetExpVolumeVoxel( extdExpVoxel->pos, EXPA_VOLUME );

			if ( IsExtendVoxel(mainPath, neiborVoxelExpPos))
			{
				if ( GetVoxelIndexInList(extdExpVoxelCandis, neiborVoxelExpPos) == VOXEL_OUT_LIST )
				{
                    if (extdExpVoxel->neiborVoxel[i] == NEIGHBOR_CONNECTED)
					    extdExpVoxelCandis.push_back( neiborExpVoxel );
				}
			}
		}
	}
}

bool PieceCreator::IsExtendVoxel(MainPath mainPath, Vector3i expVoxelPos)
{
	int lastPieceID = mainPath.pieceID;
	int pieceAxisID = mainPath.pieceAxisID;

    Voxel* testExpVoxel = expVolume->GetExpVolumeVoxel( expVoxelPos, EXPA_VOLUME);

    /// 1. The test voxel should be on the remaining volume
    if ( testExpVoxel->piece != lastPieceID )
        return false;

    /// 2. The test voxel should not be in the path voxels of mainPath
    if( std::find(mainPath.pathVoxels.begin(), mainPath.pathVoxels.end(), expVoxelPos) != mainPath.pathVoxels.end() )
        return false;

    /// 3. The test voxel should not be in the kept voxels of mainPath
    if( std::find(mainPath.keptVoxels.begin(), mainPath.keptVoxels.end(), expVoxelPos) != mainPath.keptVoxels.end() )
        return false;

    /// 4. The neighbor voxel of extendVoxel along pieceAxisID should be empty or belong to mainPath
    ///    so that the piece still can move along pieceAxisID after adding the extendVoxel
    Vector3i neiborVoxelPos = expVoxelPos + neiborPos[pieceAxisID];
    Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelPos, EXPA_VOLUME );
    if ( neiborExpVoxel->piece != NONE_PIECE &&
         std::find(mainPath.pathVoxels.begin(), mainPath.pathVoxels.end(), neiborVoxelPos) == mainPath.pathVoxels.end() )
    {
        return false;
    }

    /// TODO:
    /// 5. The test voxel should not be an articulation node in the graph of the remaining volume
    ///   (to avoid disconnecting the remaining volume)

   /* Vector3i orgVoxelPos = expVolume->Exp2OrgVoxel( expVoxelPos );

    if( IsRemainPieceConnected(lastPieceID, mainPath.pathOrgVoxels, orgVoxelPos ) == false )
    {
        return false;
    }*/

    return true;
}

int PieceCreator::SelectExtendVoxel(MainPath mainPath, vector<Voxel*> extdExpCandis, float beta)
{
    int lastPieceID = mainPath.pieceID;

    ////////////////////////////////////////////////////////////////////////
    // Compute the possibility value for each extend voxel

    vector<float> extdPossibs;
    for (int i=0; i<extdExpCandis.size(); i++)
    {
        ///////////////////////////////////////////////////////////////
        // The selection possibility value of each extendVoxel is based on both its reachability
        // value and its number of neighboring voxels of the extendVoxel that is on mainPath
        // Note: the piece shape will be less snaky by using this formula

        /*int neiborRemaVoxelNum = 0;
        for (int j=0; j<6; j++)
        {
        	Vector3i neiborVoxelPos = extdExpCandis[i]->pos + neiborPos[j];
            Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelPos, EXPA_VOLUME );

        	if ( neiborExpVoxel->piece == lastPieceID &&
        	     std::find(mainPath.pathVoxels.begin(), mainPath.pathVoxels.end(), neiborVoxelPos) == mainPath.pathVoxels.end() )
        	{
                neiborRemaVoxelNum++;
        	}
        }*/
        //float voxelPossib = (MAX_VOXEL_REACH - extdCandis[i]->reach) + 2.0*neiborPathVoxelNum;
        //extdPossibs.push_back( voxelPossib );

        //float voxelPossib = 6 - neiborRemaVoxelNum;

        float voxelPossib = (MAX_VOXEL_REACH - extdExpCandis[i]->reach);

        extdPossibs.push_back( voxelPossib );
    }


    ////////////////////////////////////////////////////////////////////////
    // Select an extend voxel based on its possibility value

    int voxelIndex;

    // If alpha is equal to -1, select extend voxel with largest possibility value
    if ( beta < 0 )
    {
        vector<int> extdIndices = BubbleSort(extdPossibs, false);
        voxelIndex = extdIndices[0];
    }
    // Else, select extend voxel based on mapped its possibility value
    else
    {
        voxelIndex = GetRandomObjIndex( extdPossibs, beta );
    }

    return voxelIndex;
}




///=========================================================================================///
///                CREATE MULTI-STEP PUZZLE: Subdivide Normal Puzzle Piece
///=========================================================================================///

///----------------------------------------------------------------------
/// Compute MainPath for a normal piece
///----------------------------------------------------------------------

MainPath PieceCreator::ComputeMainPath(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, int lastPieceID, int remvVoxelNum)
{
    MainPath mainPath;
    mainPath.isValid = false;

    ////////////////////////////////////////////////////////////////
    /// 1. Create SeedPath and check its motion space

    vector<vector<Vector3i>> contaVoxelsSet = ComputeContactVoxelsCandis(tracedPuzConfigs, tagtIndex, lastPieceID);

    SeedPath seedPath = CreateSeedPath(tracedPuzConfigs[tagtIndex], lastPieceID, remvVoxelNum, contaVoxelsSet);

    if ( !seedPath.isValid )
    {
#ifdef PRINT_DEBUG_MESSAGE
        printf("case 1: No valid seed path. \n");
#endif
        return mainPath;
    }

//    printf("Step1: create seed path. \n");

#ifndef DEBUG_CHECK_REMV_AXIS
    vector<int> moveAxisIDUnion;
    int maxConfigIndex = CheckSeedPathMotionSpace(tracedPuzConfigs, tagtIndex, seedPath, moveAxisIDUnion);

#else
    vector<int> removeAxisIDUnion;
    int maxRemvConfigIndex = CheckSeedPathRemovalAxis(tracedPuzConfigs, tagtIndex, seedPath, removeAxisIDUnion);

#endif
//    printf("Step2: check seed path motion. \n");

    /*printf("SeedPath MoveAxisIDs: ");
    for (int i=0; i<moveAxisIDUnion.size(); i++)
    {
        printf(" %d ", moveAxisIDUnion[i]);
    }
    printf("\n");*/


    ////////////////////////////////////////////////////////////////
    /// 2. Create blockPath from blockVoxel to seedPath

    BlockPath blockPath;

#ifndef DEBUG_CHECK_REMV_AXIS
    if ( moveAxisIDUnion.size() != 0 )
    {
        blockPath = CreateBlockPath(tracedPuzConfigs, tagtIndex, seedPath, maxConfigIndex, moveAxisIDUnion, remvVoxelNum);

        //printf("Step3: create block path. \n");

        if ( blockPath.pathVoxels.size() == 0 )
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("case 2: No valid block path. \n");
#endif
            return mainPath;
        }
    }

#else
    if (removeAxisIDUnion.size() != 0)
    {
        blockPath = CreateBlockPath(tracedPuzConfigs, tagtIndex, seedPath, maxRemvConfigIndex, removeAxisIDUnion, remvVoxelNum);

        //printf("Step3: create block path. \n");

        if ( blockPath.pathVoxels.size() == 0 )
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("case 2: No valid block path. \n");
#endif
            return mainPath;
        }
    }
#endif

//    printf("Step 3: Block Voxel: %d %d %d\n", blockPath.blockVoxel[0], blockPath.blockVoxel[1], blockPath.blockVoxel[2]);

    ////////////////////////////////////////////////////////////////
    /// 3. Create mainPath by combining seedPath and blockPath

    mainPath.pathVoxels = seedPath.pathVoxels;
    mainPath.keptVoxels = seedPath.keptVoxels;
    for (int i=0; i<blockPath.pathVoxels.size(); i++)
        mainPath.pathVoxels.push_back( blockPath.pathVoxels[i] );
    for (int i=0; i<blockPath.keptVoxels.size(); i++)
        mainPath.keptVoxels.push_back( blockPath.keptVoxels[i] );

    if ( mainPath.pathVoxels.size() > remvVoxelNum)
    {
#ifdef PRINT_DEBUG_MESSAGE
        printf("case 3: Too many voxels on main path. \n");
#endif
        return mainPath;
    }

    //mainPath.pathOrgVoxels = expVolume->Exp2OrgVoxels( mainPath.pathVoxels );
    //if( IsRemainPieceConnected(seedPath.pieceID, mainPath.pathOrgVoxels ) == false )
    //{
    //    return mainPath;
    //}

    mainPath.pieceID       = seedPath.pieceID;
    mainPath.pieceAxisID   = seedPath.pieceAxisID;
    mainPath.moveStep      = seedPath.moveStep;


    ////////////////////////////////////////////////////////////////
    /// 4. Extend mainPath to include fragmental voxels

    /*if( mainPath.pathVoxels.size() < 0.8*remvVoxelNum)
    {
        ExtendMainPath(tracedPuzConfigs[tagtIndex], mainPath, remvVoxelNum);

        if (  mainPath.pathVoxels.size() > 1.2*remvVoxelNum)
        {
#ifdef PRINT_DEBUG_MESSAGE
            printf("case 4: No valid main path. \n");
#endif
            return mainPath;
        }
    }*/

    ExtendMainPath(tracedPuzConfigs[tagtIndex], mainPath, remvVoxelNum);

    if (  mainPath.pathVoxels.size() != remvVoxelNum)
    {
#ifdef PRINT_DEBUG_MESSAGE
        printf("case 4: No valid main path. \n");
#endif
        return mainPath;
    }

    mainPath.isValid  = true;
    mainPath.pathOrgVoxels = expVolume->Exp2OrgVoxels( mainPath.pathVoxels );

    return mainPath;
}

vector<vector<Vector3i>> PieceCreator::ComputeContactVoxelsCandis(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, int lastPieceID)
{
	///////////////////////////////////////////////////
	// Compute the empty voxels inside the target node

	vector<Vector3i> emptyVoxels;
	GetEmptyVoxelExpPos(tracedPuzConfigs[tagtIndex], lastPieceID, emptyVoxels);

	///////////////////////////////////////////////////
	// Compute the solid voxels inside the previous nodes

	vector<vector<Vector3i>> solidVoxelsSet;
	for (int i=0; i<tagtIndex; i++)
	{ 
		vector<Vector3i> solidVoxels;
		GetSolidVoxelExpPos(tracedPuzConfigs[i], emptyVoxels, solidVoxels);

		solidVoxelsSet.push_back(solidVoxels);

		//printf("\n===============PuzConfig %d==============\n", i);
		//tracedPuzConfigs[i].PrintPuzConfig(false, false);
	}

	///////////////////////////////////////////////////
	// Compute all the possible contactVoxel set with maximum size equal to 2

	vector<vector<Vector3i>> contaVoxelsSet = ComputeContactVoxelsSet(solidVoxelsSet);

	return contaVoxelsSet;
}

void PieceCreator::GetEmptyVoxelExpPos(PuzConfig *tagtPuzConfig, int pieceID, vector<Vector3i> &emptyVoxelPosList)
{
    expVolume->BuildConfigContactGraph( tagtPuzConfig, pieceList );

	for (int i=0; i<6; i++)
	{
		for (int j=0; j<pieceList[pieceID]->pieceFace[i].surfaceVoxel.size(); j++)
		{
			Vector3i coreVoxelPos = pieceList[pieceID]->pieceFace[i].surfaceVoxel[j]->pos + neiborPos[i];
			Vector3i piecePos = tagtPuzConfig->GetPiecePos( pieceID );

            Vector3i expVoxelPos = expVolume->Org2ExpVoxel( coreVoxelPos + piecePos );
            Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(expVoxelPos, EXPA_VOLUME);

			if( tempExpVoxel->piece == NONE_PIECE &&
				std::find(emptyVoxelPosList.begin(), emptyVoxelPosList.end(), expVoxelPos) == emptyVoxelPosList.end() )
				emptyVoxelPosList.push_back(expVoxelPos);
		}
	}
}

void PieceCreator::GetSolidVoxelExpPos(PuzConfig *prevPuzConfig, vector<Vector3i> emptyVoxelPosList, vector<Vector3i> &solidVoxelPosList)
{
	solidVoxelPosList.clear();

    expVolume->BuildConfigContactGraph( prevPuzConfig, pieceList );

	//printf(" Contact Voxels: \n");
	for (int i=0; i<emptyVoxelPosList.size(); i++)
	{
        Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(emptyVoxelPosList[i], EXPA_VOLUME);

		if( tempExpVoxel->piece != NONE_PIECE )
		{
			solidVoxelPosList.push_back(emptyVoxelPosList[i]);
			//printf(" Voxel [%d %d %d] PieceID: %d \n", emptyVoxelPosList[i](X_INFO), emptyVoxelPosList[i](Y_INFO), emptyVoxelPosList[i](Z_INFO), tempExpVoxel.piece);
		}
	}
	//printf("\n");
}


///----------------------------------------------------------------------
/// Compute SeedPath for a normal piece
///----------------------------------------------------------------------

SeedPath PieceCreator::CreateSeedPath(PuzConfig *tagtPuzConfig, int lastPieceID, int remvVoxelNum, vector<vector<Vector3i>> contaVoxelsSet)
{
	SeedPath seedPath;
	seedPath.isValid = false;

	// Find possible SeedSets for the remvPiece
	vector<SeedPath> tempPathCandis = FindPieceSeedVoxels(tagtPuzConfig, lastPieceID, contaVoxelsSet);

	if ( tempPathCandis.size() == 0 )
		return seedPath;

	// Compute the corresponding SeedPath for each SeedSet
	for (int i=0; i<tempPathCandis.size(); i++)
	{
		ComputeSeedPathVoxels( tagtPuzConfig, tempPathCandis[i] );

		int pathVoxelNum = tempPathCandis[i].pathVoxels.size();
		if ( pathVoxelNum == 1 || pathVoxelNum > 0.8*remvVoxelNum )
			tempPathCandis[i].isValid = false;
		else
			tempPathCandis[i].isValid = true;
	}

	// Remove the invalid SeedPath
	vector<SeedPath> seedPathCandis;
	for (int i=0; i<tempPathCandis.size(); i++)
	{
		if ( tempPathCandis[i].isValid )
		{
			seedPathCandis.push_back( tempPathCandis[i] );
		}
	}

	if ( seedPathCandis.size() == 0 )
    {
	    seedPath.isValid = false;
        return seedPath;
    }

	// Calculate the possibility value of each seedPath candidate
	vector<float> pathPossibList;
	for (int i=0; i<seedPathCandis.size(); i++)
	{
		float pathPossib = 0;
		for (int j=0; j<seedPathCandis[i].pathVoxels.size(); j++)
		{
			Vector3i voxelPos = seedPathCandis[i].pathVoxels[j];
            Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(voxelPos, EXPA_VOLUME);

			pathPossib += tempExpVoxel->reach;
		}

		if ( pathPossib != 0 )
			pathPossib = 1.0 / pathPossib;
		pathPossibList.push_back(pathPossib);
	}

	// Randomly select one seedPath 
	int pathCandiIndex = GetRandomObjIndex(pathPossibList, 3);
	seedPath = seedPathCandis[pathCandiIndex];

	return seedPath;
}

vector<SeedPath> PieceCreator::FindPieceSeedVoxels(PuzConfig *tagtPuzConfig, int lastPieceID, vector<vector<Vector3i>> contaVoxelsSet)
{
    expVolume->UpdateExpVolumeShape(tagtPuzConfig, pieceList);

	// Get the movable pieces and moving direction in prevPuzConfig
	/*vector<int> movePieceIDs;
	Vector3i moveVector;
	int moveAxisID;
	tagtPuzConfig->GetMovePieceAndAxis(movePieceIDs, moveVector, moveAxisID);

	printf("\n++++++++++++++++++++++++++++\n");
	for(int i =0; i<movePieceIDs.size(); i++)
    {
	    printf(" %d ", movePieceIDs[i]);
    }
	printf("\n");

	int reveAxisID = GetReverseAxisID( moveAxisID );

    printf("[%d %d %d ]  %d  %d  \n", moveVector[0], moveVector[1], moveVector[2], moveAxisID, reveAxisID);*/


	///////////////////////////////////////////////////////
	// 1. Find the number of available voxels for the new piece for each direction

	vector<int> availVoxelNums;
	for (int i=0; i<6; i++)
	{
		vector<Voxel*> availVoxels = FindAvailableFillVoxels(tagtPuzConfig, lastPieceID, i);
		availVoxelNums.push_back( availVoxels.size() );
	}


	///////////////////////////////////////////////////////
	// 2. Find all the SeedVoxel set or SeedSet (i.e., one or two seed voxels) candidates

	vector<SeedPath> tempSeedCandis;

	for (int i=0; i<6; i++)
	{
		/// TODO: The moving direction of seed path cannot be the same as that in prevPuzConfig
		//if ( i == reveAxisID )
		//	continue;

		for (int j=0; j<contaVoxelsSet.size(); j++)
		{
			vector<float> seedReachs; // Save reachability value of each seed voxel in SeedSet

			SeedPath tempSeedPath;
			tempSeedPath.pieceID     = lastPieceID;
			tempSeedPath.contaVoxels = contaVoxelsSet[j];
			tempSeedPath.pieceAxisID = GetReverseAxisID( i );
			tempSeedPath.moveStep    = MAX_INT;

			///////////////////////////////////////////////////////
			// 1.1 Check valid SeedSet which are the neighboring voxels of contactVoxels 
			//     in one of the six directions and cannot be removed directly

			bool isValidSeedSet = true;
			for (int k=0; k<contaVoxelsSet[j].size(); k++)
			{
				Vector3i contaVoxelPos = contaVoxelsSet[j][k];  
				Vector3i seedVoxelPos  = contaVoxelPos + neiborPos[i];
                Voxel* expVoxel = expVolume->GetExpVolumeVoxel(seedVoxelPos, EXPA_VOLUME);

				// All the SeedVoxels should be from the last piece
				if ( expVoxel->piece == lastPieceID )
				{
                    int seedMoveStep = expVolume->GetVoxelMoveSteps(expVoxel->pos, tempSeedPath.pieceAxisID);

					tempSeedPath.seedVoxels.push_back( expVoxel->pos );
					tempSeedPath.seedMoveSteps.push_back( seedMoveStep );
					seedReachs.push_back( expVoxel->reach );

					// The moveStep of SeedSet is the minimum moveStep of all the seed voxels
					if ( tempSeedPath.moveStep >= seedMoveStep )
						tempSeedPath.moveStep = seedMoveStep;
				}
				// Else, invalid SeedVoxels
				else
				{
					isValidSeedSet = false;
					break;
				}
			}

			//printf("SeedPathStep: %d \n", tempSeedPath.moveStep);
			if ( !isValidSeedSet || tempSeedPath.moveStep == MAX_INT )
				continue;

			///////////////////////////////////////////////////////
			// 1.2 Compute one KeptVoxel (from the last piece) for a valid SeedSet 
			//     note: such KeptVoxel may not be needed as it could be one voxel from other pieces

			for (int k=0; k<tempSeedPath.seedVoxels.size(); k++)
			{
				Vector3i seedExpVoxel = tempSeedPath.seedVoxels[k];
				int seedMoveStep = tempSeedPath.moveStep;
				int pieceAxisID  = tempSeedPath.pieceAxisID;
	
				Vector3i keptExpVoxelPos = seedExpVoxel + (seedMoveStep+1)*neiborPos[pieceAxisID];
                Voxel* keptExpVoxel = expVolume->GetExpVolumeVoxel( keptExpVoxelPos, EXPA_VOLUME );

				// The keptVoxel from the last piece prevents the seedPath from removing 
				// along pieceAxisID and cannot be from the SeedSet
				if ( keptExpVoxel->piece == lastPieceID &&
					 std::find(tempSeedPath.seedVoxels.begin(), tempSeedPath.seedVoxels.end(), keptExpVoxelPos) == tempSeedPath.seedVoxels.end() )
				{
					tempSeedPath.keptVoxels.clear();
					tempSeedPath.keptVoxels.push_back( keptExpVoxelPos );
					break;
				}
			}

			///////////////////////////////////////////////////////
			// 1.3 Compute possibility value of the SeedSet
			//     TODO: increase possibility if the SeedSet encourages back motion

			// Seed Voxel Possibility: average seed reachability value for the SeedSet
			float seedAvgReach = 0;
			for (int m=0; m<seedReachs.size(); m++)
			{
				seedAvgReach += seedReachs[m];
			}
			seedAvgReach = seedAvgReach / (float)seedReachs.size();

			// Seed Voxel Possibility: number of available voxels for the pieceAxisID
			float availValue =  10.0*availVoxelNums[i] /(float)pieceList[lastPieceID]->voxelList.size();

			// Seed Voxel Possibility: number of neighbors for the kept voxel
			float keptValue = 0.0;
			if ( tempSeedPath.keptVoxels.size() == 0 )
			{
				keptValue = 10.0;
			}
			else if ( tempSeedPath.keptVoxels.size() == 1 )
			{
				Vector3i keptVoxelPos = tempSeedPath.keptVoxels[0];
                keptValue = 2.0 * expVolume->GetNeighborVoxelNum(keptVoxelPos, EXPA_VOLUME, lastPieceID);
			}

			// Seed Voxel Possibility: formula
			//tempSeedPath.seedPossib  = 0.4*avilValue + 0.6*(MAX_VOXEL_REACH-seedAvgReach);
			//tempSeedPath.seedPossib  = 0.6*tempSeedPath.moveStep + 0.4*(MAX_VOXEL_REACH-seedAvgReach);
			//tempSeedPath.seedPossib  = (MAX_VOXEL_REACH-seedAvgReach);
			tempSeedPath.seedPossib  = 0.2*availValue + 0.2*keptValue + 0.6*(MAX_VOXEL_REACH-seedAvgReach);

			tempSeedCandis.push_back( tempSeedPath );
		}
	}


	///////////////////////////////////////////////////////
	// 3. Select up to six SeedSet candidates (with priority)

	vector<SeedPath> seedPathCandis;

	// Return if there is no SeedSet candidate
	const int maxSeedNum = 6;
	int seedVoxelNum = _MIN(maxSeedNum, tempSeedCandis.size());

	if ( seedVoxelNum == 0 )
		return seedPathCandis;

	// Get the indices of the selected candidates
	vector<float> seedPossibList;
	for (int i=0; i<tempSeedCandis.size(); i++)
		seedPossibList.push_back(tempSeedCandis[i].seedPossib);
	vector<int> seedIndices = GetRandomObjIndexList(seedPossibList, 3, seedVoxelNum);

	// Return these seed voxel candidates
	for (int i=0; i<seedIndices.size(); i++)
	{
		seedPathCandis.push_back( tempSeedCandis[seedIndices[i]] );
	}

	return seedPathCandis;
}


void PieceCreator::ComputeSeedPathVoxels(PuzConfig *tagtPuzConfig, SeedPath &seedPath)
{
	int lastPieceID = seedPath.pieceID;
	int pieceAxisID = seedPath.pieceAxisID;

	//////////////////////////////////////////////////////////////////
	// 1. Compute voxel space in which to create seed path

	// Find the available voxels that can be on the blockPath (note: remove the keptVoxels)
	vector<Voxel*> avaiVoxels = FindAvailableFillVoxels(tagtPuzConfig, lastPieceID, pieceAxisID);

	// Remove the keptVoxels from the voxel space
	vector<Voxel*> voxelList;
	for (int i=0; i<avaiVoxels.size(); i++)
	{
        Vector3i voxelExpPos = expVolume->Org2ExpVoxel( avaiVoxels[i]->pos );

		if ( std::find(seedPath.keptVoxels.begin(),  seedPath.keptVoxels.end(),  voxelExpPos) == seedPath.keptVoxels.end() )
		{
			voxelList.push_back( avaiVoxels[i] );
		}
	}


	//////////////////////////////////////////////////////////////////
	// 2.1 Case 1: Create seed path for one seed voxel

	seedPath.isValid = false;

	if ( seedPath.seedVoxels.size() == 1 )
	{
		// Find all the neighboring voxel in the last piece along the perpendicular directions of pieceAxisID
		vector<Vector3i> neiborVoxelList;
		vector<int> perpAxisIDs = GetPerpAxisIDs( pieceAxisID );
		for (int i=0; i<perpAxisIDs.size(); i++ )
		{
			int axisID = perpAxisIDs[i];
			Vector3i neiborExpPos = seedPath.seedVoxels[0] + neiborPos[axisID];

            Vector3i neiborOrgPos = expVolume->Exp2OrgVoxel( neiborExpPos );
            Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel(neiborExpPos, EXPA_VOLUME);
            Voxel* currExpVoxel = expVolume->GetExpVolumeVoxel(seedPath.seedVoxels[0], EXPA_VOLUME);

			if ( neiborExpVoxel->piece != lastPieceID )
				continue;
			
			if( GetVoxelIndexInList(voxelList, neiborOrgPos) != VOXEL_OUT_LIST )
			{
			    if ( currExpVoxel->neiborVoxel[axisID] == NEIGHBOR_CONNECTED)
				    neiborVoxelList.push_back( neiborExpPos );
			}
		}

		// Randomly select one neighboring voxel and link this voxel to the piece surface along pieceAxisID
		if ( neiborVoxelList.size() > 0 )
		{
			int neiborIndex = neiborVoxelList.size() * rand()/(RAND_MAX+1.0);
            vector<Vector3i> linkedVoxels = expVolume->GetLinkedVoxels(neiborVoxelList[neiborIndex], lastPieceID, pieceAxisID, true);

			seedPath.pathVoxels = linkedVoxels;
			seedPath.pathVoxels.push_back( seedPath.seedVoxels[0] );
			seedPath.isValid = true;
		}
	}


	//////////////////////////////////////////////////////////////////
	// 2.2 Case 2: Create seed path for two seed voxels

	else if ( seedPath.seedVoxels.size() == 2 )
	{
        Vector3i srcVoxelPos  = expVolume->Exp2OrgVoxel ( seedPath.seedVoxels[0] );
        Vector3i tagtVoxelPos = expVolume->Exp2OrgVoxel ( seedPath.seedVoxels[1] );

		vector<Vector3i> tagtVoxelPosList;
		tagtVoxelPosList.push_back( tagtVoxelPos );

		vector<Vector3i> tempOrgVoxels = ComputeShortestPath(voxelList, srcVoxelPos, tagtVoxelPosList, true);

		if( tempOrgVoxels.size() > 0 )
		{
			// Compute the shortest path voxels in ExpVolume
			vector<Vector3i> tempExpVoxels;
            tempExpVoxels = expVolume->Org2ExpVoxels( tempOrgVoxels );

			// Generate movable path in ExpVolume
			seedPath.pathVoxels = GenerateMovablePath(tagtPuzConfig, lastPieceID, pieceAxisID, tempExpVoxels);
			seedPath.isValid = true;
		}
	}
}

/// Function: found all the voxels on the last piece that can be included in the shortest path
///           while keep the path (seedPath or blockPath) movable in the tagtPuzConfig
vector<Voxel*> PieceCreator::FindAvailableFillVoxels(PuzConfig *tagtPuzConfig, int pieceID, int pieceAxisID)
{
	expVolume->BuildConfigContactGraph( tagtPuzConfig, pieceList );

	// Find all the voxles on the last piece that contacts with the other pieces
	vector<Vector3i> contaFillVoxels;
	for (int i=0; i<pieceList[pieceID]->voxelList.size(); i++)
	{
		int neiborPieceID = pieceList[pieceID]->voxelList[i]->neiborPiece[pieceAxisID];
		if ( neiborPieceID != pieceID && 
			neiborPieceID != NONE_PIECE )
		{
            Vector3i tempVoxelPos = expVolume->Org2ExpVoxel ( pieceList[pieceID]->voxelList[i]->pos );
			contaFillVoxels.push_back( tempVoxelPos );
		}
	}


	// Find all the voxels that are connected with contaFillVoxles along -pieceAxisID direction
	vector<Vector3i> remvFillVoxels;
	for (int i=0; i<contaFillVoxels.size(); i++)
	{
		int linkAxisID = GetReverseAxisID( pieceAxisID );
        vector<Vector3i> linkedVoxels = expVolume->GetLinkedVoxels(contaFillVoxels[i], pieceID, linkAxisID, true);

		// TODO: need to improve this
		for (int j=0; j<linkedVoxels.size(); j++)
			remvFillVoxels.push_back( linkedVoxels[j]);
	}

	// Remove the voxels on the last piece that cannot be included
	vector<Voxel*> avaiFillVoxels;
	for (int i=0; i<pieceList[pieceID]->voxelList.size(); i++)
	{
		Voxel *orgVoxel = pieceList[pieceID]->voxelList[i];
        Vector3i expVoxelPos = expVolume->Org2ExpVoxel( orgVoxel->pos );

		if ( std::find(remvFillVoxels.begin(), remvFillVoxels.end(), expVoxelPos) == remvFillVoxels.end() )
		{
			avaiFillVoxels.push_back( orgVoxel );
		}
	}

	return avaiFillVoxels;
}

/// Function: Given a connected voxel list, extend the voxels along pieceAxisID to make sure
///           the extended path can move along pieceAxisID
vector<Vector3i> PieceCreator::GenerateMovablePath(PuzConfig *tagtPuzConfig, int pieceID, int pieceAxisID, vector<Vector3i> inputExpVoxels)
{
    expVolume->UpdateExpVolumeShape( tagtPuzConfig, pieceList );

	// Find all the faceVoxels in the inputExpVoxels whoes neighboring voxels along pieceAxisID 
	// is from pieceID but out of inputExpVoxels.
	vector<Vector3i> faceVoxels;
	for (int i=0; i<inputExpVoxels.size(); i++)
	{
		Vector3i tempExpVoxelPos = inputExpVoxels[i] + neiborPos[pieceAxisID];
        Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(tempExpVoxelPos, EXPA_VOLUME);

		if ( tempExpVoxel->piece == pieceID &&
			std::find(inputExpVoxels.begin(), inputExpVoxels.end(), tempExpVoxelPos) == inputExpVoxels.end() )
			faceVoxels.push_back( inputExpVoxels[i] );
	}

	// Push back linked voxels along pieceAxisID for each faceVoxel
	vector<Vector3i> outputExpVoxels = inputExpVoxels;
	for (int i=0; i<faceVoxels.size(); i++)
	{
        vector<Vector3i> linkedVoxels = expVolume->GetLinkedVoxels(faceVoxels[i], pieceID, pieceAxisID, false);

		for (int j=0; j<linkedVoxels.size(); j++)
			outputExpVoxels.push_back( linkedVoxels[j] );
	}

	return outputExpVoxels;
}


int PieceCreator::CheckSeedPathMotionSpace(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath &seedPath, vector<int> &moveAxisIDUnion)
{
	if ( !seedPath.isValid )
	{
//		printf("Warning: The input seedPath is invalid. \n\n");
		return -1;
	}

	int pieceAxisID = seedPath.pieceAxisID;
	int revseAxisID = GetReverseAxisID( pieceAxisID );


	////////////////////////////////////////////////////////////////////////
	/// 1. Compute the seed path motion space in the prevPuzConfigs and the previous
	///    PuzConfig index that the SeedPath has the maximum motion space

	int maxMotionSize  = 0;
	int maxConfigIndex = 0; 
	for (int i=0; i<tagtIndex; i++)
	{
		//printf("\n-----------------------------------\n");
		//tracedPuzConfigs[i]->PrintPuzConfig(false, false);

		// Assign the motion space to the puzConfig
        vector<int> moveAxisIDs = expVolume->CheckSeedPathMotionInConfig(tracedPuzConfigs[i], pieceList, seedPath.pathVoxels);

		tracedPuzConfigs[i]->moveAxisIDs = moveAxisIDs;

		// Get the puzConfig index with maximum motion space
		if ( moveAxisIDs.size() >= maxMotionSize )
		{
			maxMotionSize = moveAxisIDs.size();
			maxConfigIndex = i;
		}
	}


	////////////////////////////////////////////////////////////////////////
	/// 2. Compute the seed path motion space in the tagtPuzConfig

    vector<int> moveAxisIDs = expVolume->CheckSeedPathMotionInConfig( tracedPuzConfigs[tagtIndex], pieceList, seedPath.pathVoxels );

	// Remove the pieceAxisID of the seedPath from the moveAxisIDs of the tagtPuzConfig
	for (int i=0; i<moveAxisIDs.size(); i++)
	{
		if ( moveAxisIDs[i] == pieceAxisID )
		{
			moveAxisIDs.erase( moveAxisIDs.begin() + i );
		}
	}

	// Assign the motion space to the puzConfig
	tracedPuzConfigs[tagtIndex]->moveAxisIDs = moveAxisIDs;


	////////////////////////////////////////////////////////////////////////
	/// 3. Compute the motion space of moved seed path in the tagtPuzConfig
	///    (i.e., the seed path move along pieceAxisID for one step)

    moveAxisIDs = expVolume->CheckMovedSeedPathMotionInConfig( tracedPuzConfigs[tagtIndex], pieceList, seedPath.pieceID, seedPath.pieceAxisID, seedPath.pathVoxels );

	// Remove the pieceAxisID and revseAxisID from the moveAxisIDs in the tagtPuzConfig
	vector<int> _moveAxisIDs;
	for (int i=0; i<moveAxisIDs.size(); i++)
	{
		if ( moveAxisIDs[i] != pieceAxisID &&
			 moveAxisIDs[i] != revseAxisID )
		{
			_moveAxisIDs.push_back( moveAxisIDs[i] );
		}
	}

	seedPath.moveAxisIDs = _moveAxisIDs;

	//printf(" => MoveAxisIDs %d : ", _moveAxisIDs.size());
	//for (int i=0; i<_moveAxisIDs.size(); i++)
	//	printf(" %s ", axisArray[_moveAxisIDs[i]]);
	//printf("\n");


	////////////////////////////////////////////////////////////////////////
	/// 4. Compute the union for the motion space in different puzConfigs

	moveAxisIDUnion.clear();

	for (int i=0; i<=tagtIndex; i++)
	{
		vector<int> moveAxisIDs = tracedPuzConfigs[i]->moveAxisIDs;

		for (int j=0; j<moveAxisIDs.size(); j++)
		{
			if ( std::find(moveAxisIDUnion.begin(), moveAxisIDUnion.end(), moveAxisIDs[j]) == moveAxisIDUnion.end() )
			{
				moveAxisIDUnion.push_back( moveAxisIDs[j] );
			}
		}
	}

//	printf("tagtIndex: %d   MaxMotion Size: %d  Index: %d \n", tagtIndex, maxMotionSize, maxConfigIndex);

	return maxConfigIndex;
}

int PieceCreator::CheckSeedPathRemovalAxis(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath &seedPath, vector<int> &removeAxisIDUnion)
{
    if ( !seedPath.isValid or seedPath.pathVoxels.size() == 0 )
    {
//        printf("Warning: The input seedPath is invalid. \n\n");
        return -1;
    }

//    printf("Size of seedPathVoxels: %lu\n", seedPath.pathVoxels.size());
    int pieceAxisID = seedPath.pieceAxisID;
    int revseAxisID = GetReverseAxisID( pieceAxisID );


    ////////////////////////////////////////////////////////////////////////
    /// 1. Compute the seed path removal motion space in the prevPuzConfigs and the previous
    ///    PuzConfig index that the SeedPath has the maximum motion space

    int maxMotionSize  = 0;
    int maxConfigIndex = 0;
    for (int i=0; i<tagtIndex; i++)
    {
        //printf("\n-----------------------------------\n");
        //tracedPuzConfigs[i]->PrintPuzConfig(false, false);

        // Assign the motion space to the puzConfig
        vector<int> remvAxisIDs = expVolume->CheckSeedPathRemovalMotionInConfig(tracedPuzConfigs[i], pieceList, seedPath.pathVoxels);

        tracedPuzConfigs[i]->remvAxisIDs = remvAxisIDs;

        // Get the puzConfig index with maximum motion space
        if ( remvAxisIDs.size() >= maxMotionSize )
        {
            maxMotionSize = remvAxisIDs.size();
            maxConfigIndex = i;
        }
    }

    ////////////////////////////////////////////////////////////////////////
    /// 2. Compute the seed path removal motion space in the tagtPuzConfig

    vector<int> remvAxisIDs = expVolume->CheckSeedPathRemovalMotionInConfig( tracedPuzConfigs[tagtIndex], pieceList, seedPath.pathVoxels );

    // Remove the pieceAxisID of the seedPath from the moveAxisIDs of the tagtPuzConfig
    for (int i=0; i<remvAxisIDs.size(); i++)
    {
        if ( remvAxisIDs[i] == pieceAxisID )
        {
            remvAxisIDs.erase( remvAxisIDs.begin() + i );
        }
    }

    // Assign the motion space to the puzConfig
    tracedPuzConfigs[tagtIndex]->remvAxisIDs = remvAxisIDs;


    ////////////////////////////////////////////////////////////////////////
    /// 3. Compute the motion space of moved seed path in the tagtPuzConfig
    ///    (i.e., the seed path move along pieceAxisID for one step)


    vector<int> moveAxisIDs = expVolume->CheckMovedSeedPathMotionInConfig( tracedPuzConfigs[tagtIndex], pieceList, seedPath.pieceID, seedPath.pieceAxisID, seedPath.pathVoxels );

    // Remove the pieceAxisID and revseAxisID from the moveAxisIDs in the tagtPuzConfig
    vector<int> _moveAxisIDs;
    for (int i=0; i<moveAxisIDs.size(); i++)
    {
        if ( moveAxisIDs[i] != pieceAxisID &&
             moveAxisIDs[i] != revseAxisID )
        {
            _moveAxisIDs.push_back( moveAxisIDs[i] );
        }
    }

    seedPath.moveAxisIDs = _moveAxisIDs;

    //printf(" => MoveAxisIDs %d : ", _moveAxisIDs.size());
    //for (int i=0; i<_moveAxisIDs.size(); i++)
    //	printf(" %s ", axisArray[_moveAxisIDs[i]]);
    //printf("\n");


    ////////////////////////////////////////////////////////////////////////
    /// 4. Compute the union for the removal motion space in different puzConfigs

    removeAxisIDUnion.clear();

    for (int i=0; i<=tagtIndex; i++)
    {
        vector<int> currRemoveAxisIDs = tracedPuzConfigs[i]->remvAxisIDs;

        for (int j=0; j<currRemoveAxisIDs.size(); j++)
        {
            if ( std::find(removeAxisIDUnion.begin(), removeAxisIDUnion.end(), currRemoveAxisIDs[j]) == removeAxisIDUnion.end() )
            {
                removeAxisIDUnion.push_back( currRemoveAxisIDs[j] );
            }
        }
    }

//    printf("tagtIndex: %d   MaxRemvMotion Size: %d  Index: %d \n", tagtIndex, maxMotionSize, maxConfigIndex);

    return maxConfigIndex;
}

///----------------------------------------------------------------------
/// Compute BlockPath for a given SeedVoxel
///----------------------------------------------------------------------

BlockPath PieceCreator::CreateBlockPath(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath seedPath, int maxIndex, vector<int> moveAxisIDUnion, int remvVoxelNum)
{
	BlockPath blockPath;

	///////////////////////////////////////////////////////////////////
	/// 1. Find blockVoxels; Return false if cannot find any blockVoxel

	vector<BlockPath> blockPaths = FindPieceBlockVoxels(tracedPuzConfigs, tagtIndex, seedPath, maxIndex, moveAxisIDUnion);

	if ( blockPaths.size() == 0 )
	{
#ifdef PRINT_DEBUG_MESSAGE
		printf("case 2.1: no valid block voxel. \n");
#endif
		return blockPath;
	}

//	printf("Step 3 (1).\n");

	///////////////////////////////////////////////////////////////////
	/// 2. Compute blockPath corresponding to each blockVoxel; Return false if cannot find any non-empty blockPath

	vector<BlockPath> blkPathCandis;
	for (int i=0; i<blockPaths.size(); i++)
	{
		ComputeBlockPathVoxels(tracedPuzConfigs[tagtIndex], seedPath, blockPaths[i]);

		if ( blockPaths[i].pathVoxels.size() > 0 &&
			 blockPaths[i].pathVoxels.size() < (remvVoxelNum - seedPath.pathVoxels.size()) )
			 blkPathCandis.push_back(blockPaths[i]);
	}

	if ( blkPathCandis.size() == 0 )
	{
#ifdef PRINT_DEBUG_MESSAGE
		printf("case 2.2: cannot find block path. \n");
#endif
		return blockPath;
	}

//    printf("Step 3 (2).\n");

	///////////////////////////////////////////////////////////////////
	/// 3. Calculate possibility value of each blockPath; Return one randomly selected blockPath


#ifndef DEBUG_INTERNAL_BLOCK_PATH
	vector<float> pathPossibList;
	for (int i=0; i<blkPathCandis.size(); i++)
	{
		float pathPossib = 0;
		for (int j=0; j<blkPathCandis[i].pathVoxels.size(); j++)
		{
			Vector3i voxelPos = blkPathCandis[i].pathVoxels[j];
            Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(voxelPos, EXPA_VOLUME);

			pathPossib += tempExpVoxel->reach;
		}

		if ( pathPossib != 0 )
			pathPossib = 1.0 / pathPossib;
		pathPossibList.push_back(pathPossib);
	}

#else
    vector<float> pathPossibList;
    for (int i=0; i<blkPathCandis.size(); i++)
    {
        float pathPossib = 0;
        for (int j=0; j<blkPathCandis[i].pathVoxels.size(); j++)
        {
            Vector3i voxelPos = blkPathCandis[i].pathVoxels[j];
            Voxel* tempExpVoxel = expVolume->GetExpVolumeVoxel(voxelPos, EXPA_VOLUME);

            pathPossib += tempExpVoxel->reach;
        }


        pathPossib = pathPossib / float(blkPathCandis[i].pathVoxels.size());
        pathPossibList.push_back(pathPossib);
    }
#endif

	// Select one block path according to the possibility value
	int pathIndex = GetRandomObjIndex(pathPossibList, 3);
	blockPath = blkPathCandis[pathIndex];

//    printf("Step 3 (3).\n");

	return blockPath;
}


vector<BlockPath> PieceCreator::FindPieceBlockVoxels(vector<PuzConfig*> tracedPuzConfigs, int tagtIndex, SeedPath seedPath, int maxIndex, vector<int> moveAxisIDUnion)
{
	/////////////////////////////////////////////////////////////
	// 1. Compute the blockVoxel candidates in the maxPuzConfig

	vector<Vector3i> blockVoxelCandis = ComputeBlockVoxelsInConfig(tracedPuzConfigs[maxIndex], tracedPuzConfigs[tagtIndex], seedPath);


	/////////////////////////////////////////////////////////////
	// 2. Check valid and linkable blockVoxel candidates for all the previous PuzConfigs

	vector<BlockPath> blkPathCandis;
	const int maxBlkCandiNum = 20;

	//printf("====== Find Block ====== \n");

	for (int i=0; i<blockVoxelCandis.size(); i++)
	{
        bool isBlockVoxel = true;

#ifndef DEBUG_CHECK_BLOCK_VOXEL_REMV
		/////////////////////////////////////////////////////////////
		// 1.1 Check if the candidate is a real blockVoxel in all the previous PuzConfigs
		//     note: the path should be still movable along pieceAxisID in tagtPuzConfig

		for (int j=0; j<=tagtIndex; j++)
		{
			bool isBlockInConfig = CheckBlockVoxelInConfig(blockVoxelCandis[i], seedPath, tracedPuzConfigs[j]);
			if ( !isBlockInConfig )
			{	
				isBlockVoxel = false;
				break;
			}
		}

		if ( !isBlockVoxel )
			continue;

#else
        /////////////////////////////////////////////////////////////
        // 1.1 Check if the candidate is a real blockVoxel in all the previous PuzConfigs
        //     note: the path should be still movable along pieceAxisID in tagtPuzConfig
        //     and maybe the path can be moved but cannot be removed in prev Config

        for (int j=0; j<=tagtIndex; j++)
        {
            bool isBlockInConfig = CheckBlockVoxelRemvInConfig(blockVoxelCandis[i], seedPath, tracedPuzConfigs[j], pieceList);

            if ( !isBlockInConfig )
            {
                isBlockVoxel = false;
                break;
            }
        }

        if ( !isBlockVoxel )
            continue;
#endif

		/////////////////////////////////////////////////////////////
		// 1.2 Check if the blockVoxel can be linked to the seedPath, i.e., at least one
		//     neighboring voxel in the last piece is not a keptVoxel

		vector<Vector3i> keptVoxels;
		bool isBlkVoxelLinkable = false;
		for (int j=0; j<6; j++)
		{
			Vector3i neiborVoxelPos = blockVoxelCandis[i] + neiborPos[j];
            Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

			if ( neiborExpVoxel->piece == seedPath.pieceID )
			{
				if ( std::find(moveAxisIDUnion.begin(), moveAxisIDUnion.end(), j) != moveAxisIDUnion.end() )
				{
					int pieceAxisID = GetReverseAxisID( seedPath.pieceAxisID );
                    vector<Vector3i> linkedVoxels = expVolume->GetLinkedVoxels(neiborVoxelPos, seedPath.pieceID, pieceAxisID, true);

					for (int k=0; k<linkedVoxels.size(); k++)
					{
						keptVoxels.push_back( linkedVoxels[k] );
					}
				}
				else
				{
					isBlkVoxelLinkable = true;
				}
			}
		}

		if ( !isBlkVoxelLinkable )
			continue;

		/////////////////////////////////////////////////////////////
		// 1.3 Check if the candidate is a real blockVoxel in the tagtPuzConfig
		//     after the seed path move along pieceAxisID for one step
		//     note: the program will still work after comment this part

		//vector<Vector3i> keptExpVoxels;
		//bool isBlockInNextConfig = CheckBlockVoxelInNextConfig(blockVoxelCandis[i], seedPath, tracedPuzConfigs[tagtIndex], keptExpVoxels);
		//if ( !isBlockInNextConfig )
		//	continue;

		// Merge the two list of keptVoxels
		//for (int i=0; i<keptExpVoxels.size(); i++)
		//{
		//	if( std::find(keptVoxels.begin(), keptVoxels.end(), keptExpVoxels[i]) ==  keptVoxels.end() )
		//	{
		//		keptVoxels.push_back( keptExpVoxels[i] );
		//	}
		//}
	

		/////////////////////////////////////////////////////////////
		// 1.4 If the blockVoxel is valid and linkable, then push it back

		BlockPath blockPath;
		blockPath.pieceID     = seedPath.pieceID;
		blockPath.pieceAxisID = seedPath.pieceAxisID;
		blockPath.blockVoxel  = blockVoxelCandis[i];
		blockPath.keptVoxels  = keptVoxels;

		// Block voxel possibility: number of neighbors for each kept voxel
		float neiborSum = 0;
		for (int j=0; j<moveAxisIDUnion.size(); j++)
		{
			int axisID = moveAxisIDUnion[j];
			Vector3i neiborVoxelPos = blockVoxelCandis[i] + neiborPos[axisID];
            int neiborNum = expVolume->GetNeighborVoxelNum(neiborVoxelPos, EXPA_VOLUME, seedPath.pieceID);

			neiborSum += neiborNum-1; // Consider the connections of keptVoxel except that from the block voxel
		}
		float keptValue = 3.0 *  neiborSum / (float)moveAxisIDUnion.size();

		// Block Voxel Possibility: formula
        Voxel* expVoxel = expVolume->GetExpVolumeVoxel( blockPath.blockVoxel, EXPA_VOLUME );
		blockPath.blkPossib = 0.4*keptValue + 0.6*(MAX_VOXEL_REACH-expVoxel->reach);
		//blockPath.blkPossib = (MAX_VOXEL_REACH-expVoxel.reach);

		blkPathCandis.push_back( blockPath );

		// Avoid too may blockVoxel candidates
		if ( blkPathCandis.size() >= maxBlkCandiNum )
			break;
	}


	////////////////////////////////////////////////////////////////
	// 3. Select up to six blockVoxels according their possibility value

	vector<BlockPath> blockPaths;
	if ( blkPathCandis.size() == 0 )
		return blockPaths;

	// Compute the possibility value of the block voxel candidates
	vector<float> possibList;
	for (int i=0; i<blkPathCandis.size(); i++)
	{	
		possibList.push_back(blkPathCandis[i].blkPossib);
	}

	vector<int> voxelIndices = BubbleSort(possibList, false);
	int blockVoxelNum = _MIN(6.0, blkPathCandis.size()-1);

	for (int i=0; i<blockVoxelNum; i++)
	{
		int voxelIndex = voxelIndices[i];
		blockPaths.push_back(blkPathCandis[voxelIndex]);
	}

	return blockPaths;
}


/// Function: Find appropriate blockVoxel candidates in the maxMotion PuzConfig
vector<Vector3i> PieceCreator::ComputeBlockVoxelsInConfig(PuzConfig *prevPuzConfig, PuzConfig *tagtPuzConfig, SeedPath seedPath)
{
	////////////////////////////////////////
	// Compute available voxel positions that can be occupied by the block voxel

	int pieceID     = seedPath.pieceID;
	int pieceAxisID = seedPath.pieceAxisID;
	vector<Voxel*> avaiFillVoxels = FindAvailableFillVoxels(tagtPuzConfig, pieceID, pieceAxisID);

	vector<Voxel*> connectVoxels;
    Vector3i srcVoxelPos = expVolume->Exp2OrgVoxel( seedPath.seedVoxels[0] ); // This can be any voxel on the SeedPath

	int srcVoxelIndex = GetVoxelIndexInList( avaiFillVoxels, srcVoxelPos);
	BFSConnectedVoxels(avaiFillVoxels, srcVoxelIndex, connectVoxels);


	////////////////////////////////////////////////////////////////
	// Find appropriate blockVoxel candidates.

	vector<Vector3i> blockVoxelSet;

	for (int i=0; i<pieceList[pieceID]->voxelList.size(); i++)
	{		
		Vector3i orgVoxelPos = pieceList[pieceID]->voxelList[i]->pos;
        Vector3i expVoxelPos = expVolume->Org2ExpVoxel( orgVoxelPos );

		// The blockVoxel should not be the same as the keptVoxel of SeedPath
		if ( seedPath.keptVoxels.size() == 1 &&
			 seedPath.keptVoxels[0] == expVoxelPos )
		{
			continue;
		}

		// The blockVoxel should be in the connected available voxel list
		// but should not be in the SeedPath voxel list or keptVoxel
		if ( GetVoxelIndexInList(connectVoxels, orgVoxelPos) != VOXEL_OUT_LIST &&
			 std::find(seedPath.pathVoxels.begin(), seedPath.pathVoxels.end(), expVoxelPos) == seedPath.pathVoxels.end() )
		{
			// TODO: need to test this constraint (whether it is useful)
			// The blockVoxel should be close to the piece surface along removePiece moving axis
            int blockDistSurf = expVolume->GetVoxelDistToPieceSurface(orgVoxelPos, pieceID, pieceAxisID);

			const int distSurfThres  = 2; // Unit: number of voxel

            if(  blockDistSurf <= distSurfThres)
            {
                bool isBlockVoxel = CheckBlockVoxelInConfig(expVoxelPos, seedPath, prevPuzConfig);

                if ( isBlockVoxel )
                {
                    blockVoxelSet.push_back(expVoxelPos);
                }
            }
		}
	}

	return blockVoxelSet;
}

bool PieceCreator::CheckBlockVoxelInConfig(Vector3i expVoxelPos, SeedPath seedPath, PuzConfig *prevPuzConfig)
{
    expVolume->UpdateExpVolumeShape( prevPuzConfig, pieceList );

	vector<int> pathMoveAxisIDs = prevPuzConfig->moveAxisIDs;
	bool isBlockVoxel = true;


#ifndef DEBUG_BLOCK_VOXEL_NEAR_BY_EMPTY_VOXEL
	// The blockVoxel cannot move along the axis in pathMoveAxisIDs
	for (int i=0; i<pathMoveAxisIDs.size(); i++)
	{
		int axisID = pathMoveAxisIDs[i];
		Vector3i neiborVoxelExpPos = expVoxelPos + neiborPos[axisID];
        Voxel* neiborVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );

        // TODO: (1) need to test to see which one is better
		//       (2) consider the blocking direction that is the same as the moving direction of prevPiece
		//if ( neiborVoxel.piece!= seedPath.pieceID ||
		if ( neiborVoxel->piece == NONE_PIECE ||
			 std::find(seedPath.pathVoxels.begin(), seedPath.pathVoxels.end(), neiborVoxelExpPos) != seedPath.pathVoxels.end())
		{
			isBlockVoxel = false;
			break;
		}
	}

#else
// The blockVoxel can move but cannot be removed along the axis in pathMoveAxisIDs
    for (int i=0; i<pathMoveAxisIDs.size(); i++)
    {
        int axisID = pathMoveAxisIDs[i];
        Vector3i neiborVoxelExpPos = expVoxelPos + neiborPos[axisID];
        Voxel* neiborVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );

        // TODO: (1) need to test to see which one is better
        //       (2) consider the blocking direction that is the same as the moving direction of prevPiece
        //if ( neiborVoxel.piece!= seedPath.pieceID ||
        if ( neiborVoxel->piece != NONE_PIECE ||
             std::find(seedPath.pathVoxels.begin(), seedPath.pathVoxels.end(), neiborVoxelExpPos) != seedPath.pathVoxels.end())
        {
            isBlockVoxel = false;
            break;
        }

        vector<Vector3i> potentialBlockVoxel;
        potentialBlockVoxel.push_back(expVoxelPos);

        bool isBlockVoxelRemovable = expVolume->VoxelGroupRemovableAlongAxis(potentialBlockVoxel, axisID);

        if (isBlockVoxelRemovable)
        {
            isBlockVoxel = false;
            break;
        }
    }
#endif

	return isBlockVoxel;
}

bool PieceCreator::CheckBlockVoxelRemvInConfig(Vector3i expVoxelPos, SeedPath seedPath, PuzConfig *prevPuzConfig, vector<Piece*> pieceList)
{
    expVolume->UpdateExpVolumeShape( prevPuzConfig, pieceList );

    vector<int> pathRemoveAxisIDs = prevPuzConfig->remvAxisIDs;
    bool isBlockVoxel = true;

    // The blockVoxel cannot remove along the axis in pathRemoveAxisIDs
    for (int i=0; i<pathRemoveAxisIDs.size(); i++)
    {
        int axisID = pathRemoveAxisIDs[i];

        vector<Vector3i> tempVoxel;
        tempVoxel.push_back(expVoxelPos);
//        seedPath.pathVoxels.push_back(expVoxelPos);

        bool isSeedPathRemovable = expVolume->VoxelGroupRemovableAlongAxis(tempVoxel, axisID);

//        seedPath.pathVoxels.pop_back();

        if (isSeedPathRemovable)
        {
            isBlockVoxel = false;
            break;
        }
    }

    return isBlockVoxel;
}


bool PieceCreator::CheckBlockVoxelInNextConfig(Vector3i expVoxelPos, SeedPath seedPath, PuzConfig *tagtPuzConfig, vector<Vector3i> &keptExpVoxels)
{
	int lastPieceID = seedPath.pieceID;
	int pieceAxisID = seedPath.pieceAxisID;
	vector<int> pathMoveAxisIDs = seedPath.moveAxisIDs;

	///////////////////////////////////////////////////////////////
	// 1. Generate the moved seed path voxels (note: move along pieceAxisID for one step)
	//    TODO: need to consider the cast that the seed path moved for more than one step

	vector<Vector3i> movedSeedPathVoxels;
	for (int i=0; i<seedPath.pathVoxels.size(); i++)
	{
		Vector3i expVoxelPos = seedPath.pathVoxels[i] + neiborPos[pieceAxisID];
		movedSeedPathVoxels.push_back( expVoxelPos );
	}


	///////////////////////////////////////////////////////////////
	// 2. Update the ExpVolume based on tagtPuzConfig and moved seed path

    expVolume->UpdateExpVolumeShape( tagtPuzConfig, pieceList );

	// Set the voxels on the static seed path to be empty
	for (int i=0; i<seedPath.pathVoxels.size(); i++)
	{
		Vector3i currExpVoxelPos = seedPath.pathVoxels[i];
        expVolume->SetExoVolumeVoxelPieceID(currExpVoxelPos, EXPA_VOLUME, NONE_PIECE);
	}

	// Set the voxels on the moved seed path to be solid
	for (int i=0; i<movedSeedPathVoxels.size(); i++)
	{
		Vector3i expVoxelPos = movedSeedPathVoxels[i];
        expVolume->SetExoVolumeVoxelPieceID(expVoxelPos, EXPA_VOLUME, lastPieceID);
	}


	///////////////////////////////////////////////////////////////
	// 3. Check if it is a block voxel for moved seed path in tagtPuzConfig

	Vector3i movedExpVoxelPos = expVoxelPos + neiborPos[pieceAxisID];

	bool isBlockVoxel = true;
	keptExpVoxels.clear();

	// The blockVoxel cannot move along the axis in pathMoveAxisIDs
	for (int i=0; i<pathMoveAxisIDs.size(); i++)
	{
		int axisID = pathMoveAxisIDs[i];

		Vector3i neiborVoxelExpPos = movedExpVoxelPos + neiborPos[axisID];
		keptExpVoxels.push_back( neiborVoxelExpPos );

        Voxel* neiborVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );
		if ( neiborVoxel->piece == NONE_PIECE ||
			std::find(movedSeedPathVoxels.begin(), movedSeedPathVoxels.end(), neiborVoxelExpPos) != movedSeedPathVoxels.end())
		{
			isBlockVoxel = false;
		}
	}


	///////////////////////////////////////////////////////////////
	// 4. Update the ExpVolume to be tagtPuzConfig

    expVolume->UpdateExpVolumeShape( tagtPuzConfig, pieceList );

	return isBlockVoxel;
}


void PieceCreator::ComputeBlockPathVoxels(PuzConfig *tagtPuzConfig, SeedPath seedPath, BlockPath &blockPath)
{
	int pieceID     = blockPath.pieceID;
	int pieceAxisID = blockPath.pieceAxisID;

	//////////////////////////////////////////////////////////////////
	// 1. Create the voxel space in which to find the shortest path

	// Find the available voxels that can be on the blockPath (note: remove the keptVoxels)
	vector<Voxel*> avaiVoxels = FindAvailableFillVoxels(tagtPuzConfig, pieceID, pieceAxisID);

	// Remove the keptVoxels from the voxel space
	vector<Voxel*> voxelList;
	for (int i=0; i<avaiVoxels.size(); i++)
	{
        Vector3i voxelExpPos = expVolume->Org2ExpVoxel( avaiVoxels[i]->pos );

		if ( std::find(seedPath.keptVoxels.begin(),  seedPath.keptVoxels.end(),  voxelExpPos) == seedPath.keptVoxels.end() &&
			 std::find(blockPath.keptVoxels.begin(), blockPath.keptVoxels.end(), voxelExpPos) == blockPath.keptVoxels.end() )
		{
			voxelList.push_back( avaiVoxels[i] );
		}
	}


	//////////////////////////////////////////////////////////////////
	// 2. Compute shortest path between the seedPath and the blockVoxel

    Vector3i srcVoxelPos =  expVolume->Exp2OrgVoxel( blockPath.blockVoxel );

	vector<Vector3i> tagtVoxelPosList;
    tagtVoxelPosList = expVolume->Exp2OrgVoxels( seedPath.pathVoxels );

	blockPath.isValid = false;
	vector<Vector3i> tempOrgVoxels = ComputeShortestPath(voxelList, srcVoxelPos, tagtVoxelPosList, false);


	//////////////////////////////////////////////////////////////////
	// 3. Construct the shortest path that connects the blockVoxel and seedPath

	if ( tempOrgVoxels.size() != 0 )
	{
		// Compute the shortest path voxels in ExpVolume
		vector<Vector3i> tempExpVoxels;
        tempExpVoxels = expVolume->Org2ExpVoxels( tempOrgVoxels );

		// Generate movable path in ExpVolume
		vector<Vector3i> tempPathVoxels = GenerateMovablePath(tagtPuzConfig, pieceID, pieceAxisID, tempExpVoxels);

		// Avoid duplicated voxels in both SeedPath and BlockPath
		blockPath.isValid = true;
		blockPath.pathVoxels.clear();
		for (int i=0; i<tempPathVoxels.size(); i++)
		{
			if ( std::find(seedPath.pathVoxels.begin(), seedPath.pathVoxels.end(), tempPathVoxels[i]) == seedPath.pathVoxels.end() )
			{
				blockPath.pathVoxels.push_back( tempPathVoxels[i] );
			}
		}
	}
}



///----------------------------------------------------------------------
/// Extend MainPath to include fragmental voxels
///----------------------------------------------------------------------

void PieceCreator::ExtendMainPath(PuzConfig *tagtPuzConfig, MainPath &mainPath, int remvVoxelNum)
{
	// Update the volume to the initial state
	int lastPieceID = mainPath.pieceID;
	int pieceAxisID = mainPath.pieceAxisID;
	vector<Voxel*> avaiFillVoxels = FindAvailableFillVoxels(tagtPuzConfig, lastPieceID, pieceAxisID);

	////////////////////////////////////////////////////////////////////////////////
	/// 1. Find all the possible extendVoxels before mainPath extension

	vector<Voxel*> extdExpVoxelCandis;
	for (int i=0; i<mainPath.pathVoxels.size(); i++)
	{
		for (int j=0; j<6; j++)
		{
			Vector3i neiborVoxelExpPos = mainPath.pathVoxels[i] + neiborPos[j];
			Voxel* currExpVoxel = expVolume->GetExpVolumeVoxel( mainPath.pathVoxels[i], EXPA_VOLUME );
            Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );

			if( IsExtendVoxel(mainPath, neiborVoxelExpPos, avaiFillVoxels) )
			{
				if ( GetVoxelIndexInList(extdExpVoxelCandis, neiborVoxelExpPos) == VOXEL_OUT_LIST )
				{
				    // Here consider the connectivity constraints.
                    if (currExpVoxel->neiborVoxel[j] == NEIGHBOR_CONNECTED)
					    extdExpVoxelCandis.push_back( neiborExpVoxel );
				}
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////////
	/// 2. Perform mainPath extension

	while( true )
	{
		int mainPathVoxelNum = mainPath.pathVoxels.size();
		if ( mainPathVoxelNum >= remvVoxelNum || extdExpVoxelCandis.size() == 0 )
			break;

		// Push back a randomly selected extendVoxel to the mainPath
		// TODO: need to investigate this parameter
//		const int extdBeta = -1;
		const int extdBeta = 6;
		int extdIndex = SelectExtendVoxel( mainPath, extdExpVoxelCandis, extdBeta );

		Voxel* extdExpVoxel = extdExpVoxelCandis[extdIndex];
		mainPath.pathVoxels.push_back( extdExpVoxel->pos );
        mainPath.pathOrgVoxels.push_back( expVolume->Exp2OrgVoxel( extdExpVoxel->pos )  );

		// Update the extendVoxel candidates 
		extdExpVoxelCandis.erase( extdExpVoxelCandis.begin() + extdIndex );

		for (int i=0; i<6; i++)
		{
			Vector3i neiborVoxelExpPos = extdExpVoxel->pos + neiborPos[i];
            Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelExpPos, EXPA_VOLUME );

			if ( IsExtendVoxel(mainPath, neiborVoxelExpPos, avaiFillVoxels) )
			{
				if ( GetVoxelIndexInList(extdExpVoxelCandis, neiborVoxelExpPos) == VOXEL_OUT_LIST )
				{
                    if (extdExpVoxel->neiborVoxel[i] == NEIGHBOR_CONNECTED)
					    extdExpVoxelCandis.push_back( neiborExpVoxel );
				}
			}
		}
	}
}


/*bool PieceCreator::IsExtendVoxel(MainPath mainPath, Vector3i expVoxelPos, vector<Voxel*> avaiFillVoxels)
{
	int lastPieceID = mainPath.pieceID;
	int pieceAxisID = mainPath.pieceAxisID;

    Voxel* testExpVoxel = expVolume->GetExpVolumeVoxel( expVoxelPos, EXPA_VOLUME);
    Vector3i orgVoxelPos = expVolume->Exp2OrgVoxel( expVoxelPos );

    // The extendVoxel should be in the available voxel list
	if ( GetVoxelIndexInList(avaiFillVoxels, orgVoxelPos) == VOXEL_OUT_LIST )
	{
		return false;
	}

	// The extendVoxel should be in the origPiece but cannot be from mainPath or keptVoxels
	if ( testExpVoxel->piece == lastPieceID &&
		std::find(mainPath.keptVoxels.begin(), mainPath.keptVoxels.end(), expVoxelPos) == mainPath.keptVoxels.end() &&
		std::find(mainPath.pathVoxels.begin(), mainPath.pathVoxels.end(), expVoxelPos) == mainPath.pathVoxels.end() )
	{
		Vector3i neiborVoxelPos = expVoxelPos + neiborPos[pieceAxisID];
        Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelPos, EXPA_VOLUME );

		// The neighbor voxel of extendVoxel along pieceAxisID should be empty or belong to mainPath
		// So that the piece still can move along pieceAxisID after adding the extendVoxel
		if ( neiborExpVoxel->piece == NONE_PIECE ||
			std::find(mainPath.pathVoxels.begin(), mainPath.pathVoxels.end(), neiborVoxelPos) != mainPath.pathVoxels.end() )
		{
			return true;
		}
	}

	return false;
}*/

bool PieceCreator::IsExtendVoxel(MainPath mainPath, Vector3i expVoxelPos, vector<Voxel*> avaiFillVoxels)
{
    int lastPieceID = mainPath.pieceID;
    int pieceAxisID = mainPath.pieceAxisID;

    Voxel* testExpVoxel = expVolume->GetExpVolumeVoxel( expVoxelPos, EXPA_VOLUME);

    /// 0. The extendVoxel should be in the available voxel list
    Vector3i orgVoxelPos = expVolume->Exp2OrgVoxel( expVoxelPos );
    if ( GetVoxelIndexInList(avaiFillVoxels, orgVoxelPos) == VOXEL_OUT_LIST )
    {
        return false;
    }

    /// 1. The test voxel should be on the remaining volume
    if ( testExpVoxel->piece != lastPieceID )
        return false;

    /// 2. The test voxel should not be in the path voxels of mainPath
    if( std::find(mainPath.pathVoxels.begin(), mainPath.pathVoxels.end(), expVoxelPos) != mainPath.pathVoxels.end() )
        return false;

    /// 3. The test voxel should not be in the kept voxels of mainPath
    if( std::find(mainPath.keptVoxels.begin(), mainPath.keptVoxels.end(), expVoxelPos) != mainPath.keptVoxels.end() )
        return false;

    /// 4. The neighbor voxel of extendVoxel along pieceAxisID should be empty or belong to mainPath
    ///    so that the piece still can move along pieceAxisID after adding the extendVoxel
    Vector3i neiborVoxelPos = expVoxelPos + neiborPos[pieceAxisID];
    Voxel* neiborExpVoxel = expVolume->GetExpVolumeVoxel( neiborVoxelPos, EXPA_VOLUME );
    if ( neiborExpVoxel->piece != NONE_PIECE &&
         std::find(mainPath.pathVoxels.begin(), mainPath.pathVoxels.end(), neiborVoxelPos) == mainPath.pathVoxels.end() )
    {
        return false;
    }

    /// TODO:
    /// 5. The test voxel should not be an articulation node in the graph of the remaining volume
    ///   (to avoid disconnecting the remaining volume)

    //if( IsRemainPieceConnected(lastPieceID, mainPath.pathOrgVoxels, orgVoxelPos ) == false )
    //{
    //    return false;
    //}

    return true;
}



