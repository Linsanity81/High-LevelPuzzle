///////////////////////////////////////////////////////////////
//
// ExpVolume.h
//
//   Expanded volume class piece
//
// by Peng Song
//
// 07/Jun/2021
// 
///////////////////////////////////////////////////////////////

#include "Utility/HelpDefine.h"
#include "Utility/HelpPuz.h"
#include "PieceFace.h"
#include "Piece.h"
#include "PieceGroup.h"
#include "PuzConfig.h"
#include "ExpVolume.h"


extern Vector3i neiborPos[6];


///=========================================================================================///
///                                   Initialization
///=========================================================================================///

ExpVolume::ExpVolume()
{
    expBBox = NULL;

    outExpBBoxVoxel = new Voxel();
    outExpBBoxVoxel->state = VOXEL_OUT_EXP_BBOX;
    outExpBBoxVoxel->piece = NONE_PIECE;

	volumeSize = Vector3i(0, 0, 0);
	voxelSize = Vector3f(0, 0, 0);

	expVolumeSize = Vector3i(0, 0, 0);
	//expVolumeVoxelNum = 0;

	expVolumeSizeScaler = 1;
}

ExpVolume::~ExpVolume()
{
    ClearExpVolume();
}

void ExpVolume::ClearExpVolume()
{
	if( expBBox != NULL )
	{
		delete expBBox;
		expBBox = NULL;
	}

    if( outExpBBoxVoxel != NULL )
        delete outExpBBoxVoxel;

    for (int i=0; i<expVoxelGrid.size(); i++)
    {
        delete expVoxelGrid[i];
    }
    expVoxelGrid.clear();
}

void ExpVolume::InitExpVolume(vector<Piece*> puzPieces, Vector3i puzVolumeSize, bool isCopyReachValue)
{
    if( puzPieces.size() == 0 )
    {
        printf("Warning: The input puzzle to pieceCreator is empty! \n");
        return;
    }

    if( puzPieces[0]->voxelList.size() == 0 )
    {
        printf("Warning: The input puzzle's first piece is empty! \n");
        return;
    }

    // Set expanded volume info
    voxelSize = puzPieces[0]->voxelList[0]->size;
    volumeSize = puzVolumeSize;
    expVolumeSize =(2*expVolumeSizeScaler + 1)*volumeSize;

//    printf("expVolumeSize: %d %d %d\n", expVolumeSize(X_INFO) , expVolumeSize(Y_INFO) , expVolumeSize(Z_INFO));

    expBBox = new BoundingBox();
    expBBox->minPt = Vector3f(-0.5*expVolumeSize(X_INFO)*voxelSize(X_INFO), -0.5*expVolumeSize(Y_INFO)*voxelSize(Y_INFO), -0.5*expVolumeSize(Z_INFO)*voxelSize(Z_INFO));
    expBBox->maxPt = Vector3f( 0.5*expVolumeSize(X_INFO)*voxelSize(X_INFO),  0.5*expVolumeSize(Y_INFO)*voxelSize(Y_INFO),  0.5*expVolumeSize(Z_INFO)*voxelSize(Z_INFO));

    int expVolumeVoxelNum = expVolumeSize(X_INFO) * expVolumeSize(Y_INFO) * expVolumeSize(Z_INFO);

    if ( expVoxelGrid.size() > 0 )
    {
        for(int i=0; i<expVoxelGrid.size(); i++)
        {
            delete expVoxelGrid[i];
        }
        expVoxelGrid.clear();
    }

    for (int i=0; i<expVolumeVoxelNum; i++)
    {
        Voxel* tempVoxel = new Voxel();
        expVoxelGrid.push_back(tempVoxel);
    }

    for (int k=0; k<expVolumeVoxelNum; k++)
    {
        expVoxelGrid[k]->piece = NONE_PIECE;

        expVoxelGrid[k]->state = VOXEL_IN_EXP_BBOX;

        expVoxelGrid[k]->pos(Z_INFO) = floor( k/((float)expVolumeSize(Y_INFO)*expVolumeSize(X_INFO)) );
        int tempRemain = k - expVoxelGrid[k]->pos(Z_INFO)*(expVolumeSize(Y_INFO)*expVolumeSize(X_INFO));
        expVoxelGrid[k]->pos(Y_INFO) = floor( tempRemain/((float)expVolumeSize(X_INFO)) );
        expVoxelGrid[k]->pos(X_INFO) = k - expVoxelGrid[k]->pos(Z_INFO)*(expVolumeSize(Y_INFO)*expVolumeSize(X_INFO)) - expVoxelGrid[k]->pos(Y_INFO)*expVolumeSize(X_INFO);

        expVoxelGrid[k]->size = voxelSize;
        expVoxelGrid[k]->center(X_INFO) = expBBox->minPt(X_INFO) + (expVoxelGrid[k]->pos(X_INFO)+0.5)*voxelSize(X_INFO);
        expVoxelGrid[k]->center(Y_INFO) = expBBox->maxPt(Y_INFO) - (expVoxelGrid[k]->pos(Y_INFO)+0.5)*voxelSize(Y_INFO);
        expVoxelGrid[k]->center(Z_INFO) = expBBox->maxPt(Z_INFO) - (expVoxelGrid[k]->pos(Z_INFO)+0.5)*voxelSize(Z_INFO);

//        for (int i = 0; i < 6; i++)
//        {
//            expVoxelGrid[k]->neiborVoxel[i] = NEIGHBOR_NONE_AVAILABLE;
//        }
    }


    // Set pieceID info for voxels in expanded volume
    for (int i=0; i<puzPieces.size(); i++)
    {
        for (int j=0; j<puzPieces[i]->voxelList.size(); j++)
        {
            Vector3i voxelPos = puzPieces[i]->voxelList[j]->pos;
            int expVoxelIndex = GetExpVolumeVoxelIndex(voxelPos, ORIG_VOLUME);
            expVoxelGrid[expVoxelIndex]->piece = puzPieces[i]->voxelList[j]->piece;

            // Copy the voxel reachability values
            if( isCopyReachValue )
            {
                expVoxelGrid[expVoxelIndex]->reach = puzPieces[i]->voxelList[j]->reach; // Copy reachability value

                //printf(" %.2f ", expVoxelGrid[expVoxelIndex].reach);
                //printf("[%d %d %d] %.2f ", expVoxelGrid[expVoxelIndex].pos(X_INFO), expVoxelGrid[expVoxelIndex].pos(Y_INFO), expVoxelGrid[expVoxelIndex].pos(Z_INFO), expVoxelGrid[expVoxelIndex].reach);

            }

//            printf("voxelList Connectivity: %d %d %d %d %d %d\n", puzPieces[i]->voxelList[j]->neiborVoxel[0], puzPieces[i]->voxelList[j]->neiborVoxel[1], puzPieces[i]->voxelList[j]->neiborVoxel[2]
//                    , puzPieces[i]->voxelList[j]->neiborVoxel[3], puzPieces[i]->voxelList[j]->neiborVoxel[4], puzPieces[i]->voxelList[j]->neiborVoxel[5]);

            // Copy the connectivity data
            for (int m = 0; m < 6; m++)
            {
                expVoxelGrid[expVoxelIndex]->neiborVoxel[m] = puzPieces[i]->voxelList[j]->neiborVoxel[m];
            }

//            printf("Connectivity: %d %d %d %d %d %d\n", expVoxelGrid[expVoxelIndex]->neiborVoxel[0], expVoxelGrid[expVoxelIndex]->neiborVoxel[1], expVoxelGrid[expVoxelIndex]->neiborVoxel[2]
//                    , expVoxelGrid[expVoxelIndex]->neiborVoxel[3], expVoxelGrid[expVoxelIndex]->neiborVoxel[4], expVoxelGrid[expVoxelIndex]->neiborVoxel[5]);
        }
    }
}

void ExpVolume::PrintExpVolume()
{
    printf("ExpVolume Info: \n ");
	for (int i=0; i<expVoxelGrid.size(); i++)
	{
		int pieceID = expVoxelGrid[i]->piece;
		Vector3i voxelPos = expVoxelGrid[i]->pos-volumeSize;

		if( expVoxelGrid[i]->marked )
        {
            printf("i=%2d Voxel [%2d %2d %2d] Piece: %d \n", i, voxelPos(X_INFO), voxelPos(Y_INFO), voxelPos(Z_INFO), expVoxelGrid[i]->piece);
        }


		/*if( pieceID != NONE_PIECE )
		{
			printf("Voxel [%2d %2d %2d]  PieceID %2d   Neighbor ", voxelPos(X_INFO), voxelPos(Y_INFO), voxelPos(Z_INFO), expVoxelGrid[i]->piece);

			for (int j=0; j<6; j++)
			{
				printf(" %2d ", expVoxelGrid[i]->neiborPiece[j]);
			}
			printf("\n");
		}*/
	}

	printf("\n");
}

int ExpVolume::GetVolumeAxisSize(int axisID)
{
    if     ( axisID == 0 || axisID == 1 )    return volumeSize[0];
    else if( axisID == 2 || axisID == 3 )    return volumeSize[1];
    else if( axisID == 4 || axisID == 5 )    return volumeSize[2];
}

int ExpVolume::GetExtremeAxisPos(int axisID)
{
    if      ( axisID == 0 )    return 0;
    else if ( axisID == 1 )    return volumeSize[0]-1;
    else if ( axisID == 2 )    return 0;
    else if ( axisID == 3 )    return volumeSize[1]-1;
    else if ( axisID == 4 )    return 0;
    else if ( axisID == 5 )    return volumeSize[2]-1;
}

int ExpVolume::GetVoxelAxisPos(Vector3i voxelPos, int axisID)
{
    if     ( axisID == 0 || axisID == 1 )    return voxelPos[0];
    else if( axisID == 2 || axisID == 3 )    return voxelPos[1];
    else if( axisID == 4 || axisID == 5 )    return voxelPos[2];
}



///=========================================================================================///
///                                 Volume Get Operations
///=========================================================================================///

Voxel* ExpVolume::GetExpVolumeVoxel(Vector3i voxelPos, int volumeType)
{
	if( VoxelInsideExpVolume(voxelPos, volumeType) )
	{
		int expVoxelIndex = GetExpVolumeVoxelIndex(voxelPos, volumeType);
//        printf("expVoxelGridIndex: %d\n", expVoxelIndex);
		return expVoxelGrid[expVoxelIndex];
	}
	else
	{
//	    printf("outExpBBoxVoxel\n");
        return outExpBBoxVoxel;
	}
}

Voxel* ExpVolume::GetExpVolumeVoxel_new(Vector3i voxelPos, int volumeType)
{
    if( VoxelInsideExpVolume(voxelPos, volumeType) )
    {
        int expVoxelIndex = GetExpVolumeVoxelIndex(voxelPos, volumeType);
        printf("expVoxelGridIndex: %d\n", expVoxelIndex);
        return expVoxelGrid[expVoxelIndex];
    }
    else
    {
	    printf("outExpBBoxVoxel\n");
        return outExpBBoxVoxel;
    }
}

int ExpVolume::GetExpVolumeVoxelIndex(Vector3i voxelPos, int volumeType)
{
	Vector3i expVoxelPos;
	if( volumeType == EXPA_VOLUME )   expVoxelPos = voxelPos;
	if( volumeType == ORIG_VOLUME )   expVoxelPos = voxelPos + volumeSize * expVolumeSizeScaler;

	int expVoxelIndex = expVoxelPos(Z_INFO)*expVolumeSize(Y_INFO)*expVolumeSize(X_INFO) + expVoxelPos(Y_INFO)*expVolumeSize(X_INFO) + expVoxelPos(X_INFO);
	return expVoxelIndex;
}

int ExpVolume::GetNeighborVoxelNum(Vector3i voxelPos, int volumeType, int pieceID)
{
	int neiborVoxelNum = 0;

	for (int i=0; i<6; i++)
	{
		Vector3i neiborVoxelPos = voxelPos + neiborPos[i];
		Voxel* neiborVoxel = GetExpVolumeVoxel(neiborVoxelPos, volumeType);

		if ( neiborVoxel->piece == pieceID )
			neiborVoxelNum += 1;
	}

	return neiborVoxelNum;
}




///=========================================================================================///
///                                 Volume Set Operations
///=========================================================================================///

void ExpVolume::SetExoVolumeVoxelPieceID(Vector3i voxelPos, int volumeType, const int pieceID)
{
    int expVoxelIndex = GetExpVolumeVoxelIndex(voxelPos, volumeType);

    expVoxelGrid[expVoxelIndex]->piece = pieceID;
}

void ExpVolume::MarkExpVolumeVoxels(PieceGroup* pieceGroup, bool markValue)
{
    for (int i = 0; i < pieceGroup->pieceIDList.size(); i++)
    {
        Piece *piece = pieceGroup->pieceList[i];
        Vector3i piecePos = pieceGroup->piecePosList[i];

        for (int j = 0; j < piece->voxelList.size(); ++j)
        {
            Vector3i voxelPos = piece->voxelList[j]->pos + piecePos;
            Voxel *expVoxel = GetExpVolumeVoxel(voxelPos, ORIG_VOLUME);

            if( expVoxel->state == VOXEL_OUT_EXP_BBOX)
            {
                //printf("Warning: the voxel is out of the expVolume. \n");
            }
            else
            {
                expVoxel->marked = markValue;
            }
        }
    }
}




///=========================================================================================///
///                             Volume Voxel Conversion
///=========================================================================================///

vector<Vector3i> ExpVolume::Exp2OrgVoxels(vector<Vector3i> expVoxels)
{
	vector<Vector3i> orgVoxels;

	for (int i=0; i<expVoxels.size(); i++)
	{
		Vector3i orgVoxelPos = expVoxels[i] - volumeSize * expVolumeSizeScaler;
		orgVoxels.push_back( orgVoxelPos );
	}

	return orgVoxels;
}

vector<Vector3i> ExpVolume::Org2ExpVoxels(vector<Vector3i> orgVoxels)
{
	vector<Vector3i> expVoxels;

	for (int i=0; i<orgVoxels.size(); i++)
	{
		Vector3i expVoxelPos = orgVoxels[i] + volumeSize * expVolumeSizeScaler;
		expVoxels.push_back( expVoxelPos );
	}

	return expVoxels;
}

Vector3i ExpVolume::Exp2OrgVoxel(Vector3i expVoxelPos)
{
    Vector3i orgVoxelPos = expVoxelPos - volumeSize * expVolumeSizeScaler;

    return orgVoxelPos;
}

Vector3i ExpVolume::Org2ExpVoxel(Vector3i orgVoxelPos)
{
    Vector3i expVoxelPos = orgVoxelPos + volumeSize * expVolumeSizeScaler;

    return expVoxelPos;
}




///=========================================================================================///
///                                Inside/outside Volume
///=========================================================================================///

bool ExpVolume::ConfigInsideExpVolume(PuzConfig *puzConfig, vector<Piece*> pieceList)
{
	for (int i=0; i<puzConfig->pieceIDList.size(); i++)
	{
		int pieceID = puzConfig->pieceIDList[i];
		Vector3i piecePos = puzConfig->piecePosList[i];

		for (int j=0; j<pieceList[pieceID]->voxelList.size(); j++)
		{
			Vector3i tempVoxelPos = pieceList[pieceID]->voxelList[j]->pos + piecePos;
			bool isVoxelInExpVolume = VoxelInsideExpVolume(tempVoxelPos, ORIG_VOLUME);

			if( !isVoxelInExpVolume )
				return false;
		}
	}

	return true;
}

bool ExpVolume::VoxelInsideExpVolume(Vector3i voxelPos, int volumeType)
{
    Vector3i expVoxelPos;
    if( volumeType == EXPA_VOLUME )
    {
//        printf("222\n");
        expVoxelPos = voxelPos;
    }
    if( volumeType == ORIG_VOLUME )
    {
        expVoxelPos = voxelPos + volumeSize * expVolumeSizeScaler;
    }

    if( expVoxelPos(X_INFO) < 0 || expVoxelPos(X_INFO) > expVolumeSize(X_INFO)-1 ||
        expVoxelPos(Y_INFO) < 0 || expVoxelPos(Y_INFO) > expVolumeSize(Y_INFO)-1 ||
        expVoxelPos(Z_INFO) < 0 || expVoxelPos(Z_INFO) > expVolumeSize(Z_INFO)-1 )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool ExpVolume::VoxelInsideOrgVolume(Vector3i voxelPos, int volumeType)
{
    Vector3i orgVoxelPos;
    if( volumeType == EXPA_VOLUME )    orgVoxelPos = voxelPos - volumeSize * expVolumeSizeScaler;
    if( volumeType == ORIG_VOLUME )    orgVoxelPos = voxelPos;

    if( orgVoxelPos(X_INFO) < 0 || orgVoxelPos(X_INFO) > volumeSize(X_INFO)-1 ||
        orgVoxelPos(Y_INFO) < 0 || orgVoxelPos(Y_INFO) > volumeSize(Y_INFO)-1 ||
        orgVoxelPos(Z_INFO) < 0 || orgVoxelPos(Z_INFO) > volumeSize(Z_INFO)-1 )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool ExpVolume::VoxelOnPuzzleSurface(Vector3i voxelPos)
{
    for (int j = 0; j < 6; ++j)
    {
        Vector3i neiborVoxelPos = voxelPos + neiborPos[j];
        Voxel* neiborExpVoxel = GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

        bool isOut = VoxelInsideOrgVolume(voxelPos, EXPA_VOLUME);

        if (isOut)
        {
            return true;
        }
    }

    return false;
}




///=========================================================================================///
///                             Build Config Contacting Graph
///=========================================================================================///

void ExpVolume::BuildConfigContactGraph(PuzConfig *puzConfig, vector<Piece*> pieceList)
{
    // Build contacting graph at voxel level
    ComputeVoxelContactPiece(puzConfig, pieceList);

    for (int i=0; i<puzConfig->pieceIDList.size(); i++)
    {
        int pieceID = puzConfig->pieceIDList[i];

        // Build contacting graph at pieceFace level
        pieceList[pieceID]->ComputePieceFace();

        // Build contacting graph at piece level
        pieceList[pieceID]->ComputeNeighborPiece();

        // Check each piece's motion space
        pieceList[pieceID]->ComputeMovableAxis();

        //pieceList[pieceID]->PrintPieceInfo();
    }
}


void ExpVolume::ComputeVoxelContactPiece(PuzConfig *puzConfig, vector<Piece*> pieceList)
{
    UpdateExpVolumeShape(puzConfig, pieceList);

    for (int i=0; i<puzConfig->pieceIDList.size(); i++)
    {
        int pieceID = puzConfig->pieceIDList[i];
        for (int j=0; j<pieceList[pieceID]->voxelList.size(); j++)
        {
            Vector3i expVoxelPos = pieceList[pieceID]->voxelList[j]->pos + volumeSize * expVolumeSizeScaler + puzConfig->piecePosList[i];

            GetExpVoxelContactPiece(expVoxelPos, pieceList[pieceID]->voxelList[j]->neiborPiece);
        }
    }
}

void ExpVolume::GetExpVoxelContactPiece(Vector3i expVoxelPos, int neiborPieceID[6])
{
	Voxel* currExpVoxel = GetExpVolumeVoxel(expVoxelPos, EXPA_VOLUME);

	for (int k=0; k<6; k++)
	{
		Voxel* tempExpVoxel = GetExpVolumeVoxel(currExpVoxel->pos + neiborPos[k], EXPA_VOLUME);
		neiborPieceID[k] = tempExpVoxel->piece;
	}
}

void ExpVolume::UpdateExpVolumeShape(PuzConfig *puzConfig, vector<Piece*> pieceList)
{
    // Set pieceID for voxels in the expanded volume to be empty
    ResetExpVolumeShape();

    // Set pieceID for voxels on the moved piece in the expanded volume
    for (int i=0; i<puzConfig->pieceIDList.size(); i++)
    {
        int pieceID = puzConfig->pieceIDList[i];
        Piece *piece = pieceList[pieceID];

        Vector3i piecePos = puzConfig->piecePosList[i];
        UpdatePieceInExpVolume(piece, piecePos);
    }
}

void ExpVolume::ResetExpVolumeShape()
{
	for (int i=0; i<expVoxelGrid.size(); i++)
	{
		expVoxelGrid[i]->piece = NONE_PIECE;
		expVoxelGrid[i]->reach = -1.0;
	}
}

void ExpVolume::UpdatePieceInExpVolume(Piece *piece, Vector3i piecePos)
{
    for (int i=0; i<piece->voxelList.size(); i++)
    {
        Vector3i currExpVoxelPos = piece->voxelList[i]->pos + volumeSize * expVolumeSizeScaler + piecePos;
        int currExpVoxelIndex = GetExpVolumeVoxelIndex(currExpVoxelPos, EXPA_VOLUME);

        expVoxelGrid[currExpVoxelIndex]->piece = piece->voxelList[i]->piece;
        expVoxelGrid[currExpVoxelIndex]->reach = piece->voxelList[i]->reach;

//        printf("Index: %d    pieceID: %d\n", currExpVoxelIndex, piece->voxelList[i]->piece);
//        printf("")
    }
}




///=========================================================================================///
///                                 Computation Operations
///=========================================================================================///

/// TODO: use a more simple way to identify empty voxels
vector<Vector3i> ExpVolume::ComputeEmptyVoxels(vector<Piece*> pieceList)
{
    int pieceID = 0;

    vector<Vector3i> emptyVoxels;
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<pieceList[pieceID]->pieceFace[i].surfaceVoxel.size(); j++)
        {
            Vector3i orgVoxelPos  = pieceList[pieceID]->pieceFace[i].surfaceVoxel[j]->pos;
            Vector3i expVoxelPos  = Org2ExpVoxel( orgVoxelPos );

            Vector3i neiborVoxelPos = expVoxelPos + neiborPos[i];
            Voxel* neiborExpVoxel = GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

            // Empty voxel should have one neighboring voxel along direction d(-i)
            if( neiborExpVoxel->piece == NONE_PIECE &&
                std::find(emptyVoxels.begin(), emptyVoxels.end(), neiborVoxelPos) == emptyVoxels.end() )
            {
                // Empty voxel should also have one (far) neighboring voxel along direction d(i)
                if ( GetVoxelMoveSteps(expVoxelPos, i) != MAX_INT )
                {
                    emptyVoxels.push_back( neiborVoxelPos );
                }
            }
        }
    }

    return emptyVoxels;
}

int ExpVolume::GetVoxelDistToPieceSurface(Vector3i orgVoxelPos, int pieceID, int distAxisID)
{
    Vector3i moveNeiborDir = neiborPos[distAxisID];
    int moveVoxelNum = 0;

    // Return 0 if the tested voxel is on piece surface
    while ( true )
    {
        moveVoxelNum++;
        Vector3i tempExpVoxelPos = orgVoxelPos + moveVoxelNum*neiborPos[distAxisID] + volumeSize * expVolumeSizeScaler;
        Voxel* tempExpVoxel = GetExpVolumeVoxel(tempExpVoxelPos, EXPA_VOLUME);

        if ( tempExpVoxel->piece != pieceID )
        {
            moveVoxelNum -= 1;
            break;
        }
    }

    return moveVoxelNum;
}

int ExpVolume::GetVoxelMoveSteps(Vector3i voxelExpPos, int pieceAxisID)
{
    Vector3i tempExpVoxelPos = voxelExpPos;
    int moveStep = 0;

    // Return 0 if the neighboring voxel of the tested voxel along pieceAxisID is not empty
    while ( VoxelInsideExpVolume(tempExpVoxelPos, EXPA_VOLUME) )
    {
        moveStep++;
        tempExpVoxelPos = voxelExpPos + moveStep*neiborPos[pieceAxisID];
        Voxel* tempExpVoxel = GetExpVolumeVoxel(tempExpVoxelPos, EXPA_VOLUME);

        if ( tempExpVoxel->piece != NONE_PIECE )
            return (moveStep-1);
    }

    return MAX_INT;
}

vector<Vector3i> ExpVolume::GetLinkedVoxels(Vector3i startVoxelExpPos, int pieceID, int linkAxisID, bool isIncludeStartVoxel)
{
    vector<Vector3i> linkedVoxels;
    int moveStep = 0;
    Vector3i tempExpVoxelPos = startVoxelExpPos;

    // Push back the starting voxel
    if ( isIncludeStartVoxel )
        linkedVoxels.push_back(startVoxelExpPos);

    // Compute the voxels that is from pieceID and linked with starting voxel along pieceAxisID
    while ( VoxelInsideOrgVolume(tempExpVoxelPos, EXPA_VOLUME) )
    {
        moveStep++;
        tempExpVoxelPos = startVoxelExpPos + moveStep*neiborPos[linkAxisID];
        Voxel* tempExpVoxel = GetExpVolumeVoxel(tempExpVoxelPos, EXPA_VOLUME);

        if ( tempExpVoxel->piece == pieceID )
            linkedVoxels.push_back( tempExpVoxelPos );
        else
            break;
    }

    return linkedVoxels;
}




///=========================================================================================///
///                              Check Motion of Voxel Groups
///=========================================================================================///

vector<int> ExpVolume::CheckSeedPathMotion(int seedAxisID, vector<Vector3i> seedPathVoxels)
{
    // Compute all the blocked directions of the seedPath
    vector<int> blockAxisIDs;
    for (int j=0; j<6; j++)
    {
        for (int i=0; i<seedPathVoxels.size(); i++)
        {
            Vector3i neiborVoxelPos = seedPathVoxels[i] + neiborPos[j];
            Voxel* neiborExpVoxel = GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

            if ( neiborExpVoxel->piece != NONE_PIECE &&
                 std::find(seedPathVoxels.begin(), seedPathVoxels.end(), neiborVoxelPos) == seedPathVoxels.end())
            {
                blockAxisIDs.push_back(j);
                break;
            }
        }
    }

    // Remove the pieceAxisID of the SeedPath from the moveAxisIDs
    vector<int> moveAxisIDs;
    for (int i=0; i<6; i++)
    {
        if ( std::find(blockAxisIDs.begin(), blockAxisIDs.end(), i) == blockAxisIDs.end() &&
             i != seedAxisID )
        {
            moveAxisIDs.push_back(i);
        }
    }

    //printf(" => MoveAxisIDs %d : ", moveAxisIDs.size());
    //for (int i=0; i<moveAxisIDs.size(); i++)
    //	printf(" %s ", axisArray[moveAxisIDs[i]]);
    //printf("\n");

    //seedPath.moveAxisIDs = moveAxisIDs;
    return moveAxisIDs;
}

vector<int> ExpVolume::CheckSeedPathMotionInConfig(PuzConfig *prevPuzConfig, vector<Piece*> pieceList, vector<Vector3i> seedPathVoxels)
{
    UpdateExpVolumeShape( prevPuzConfig, pieceList );

    vector<int> blockAxisIDs;

    for (int i=0; i<seedPathVoxels.size(); i++)
    {
        for (int j=0; j<6; j++)
        {
            Vector3i neiborVoxelPos = seedPathVoxels[i] + neiborPos[j];
            Voxel* neiborExpVoxel = GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

            if ( neiborExpVoxel->piece != NONE_PIECE &&
                 std::find(seedPathVoxels.begin(), seedPathVoxels.end(), neiborVoxelPos) == seedPathVoxels.end())
            {
                blockAxisIDs.push_back(j);
            }
        }
    }

    vector<int> moveAxisIDs;
    for (int i=0; i<6; i++)
    {
        if ( std::find(blockAxisIDs.begin(), blockAxisIDs.end(), i) == blockAxisIDs.end() )
        {
            moveAxisIDs.push_back(i);
        }
    }

    //printf(" => MoveAxisIDs %d : ", moveAxisIDs.size());
    //for (int i=0; i<moveAxisIDs.size(); i++)
    //	printf(" %s ", axisArray[moveAxisIDs[i]]);
    //printf("\n");

    return moveAxisIDs;
}

vector<int> ExpVolume::CheckSeedPathRemovalMotionInConfig(PuzConfig *prevPuzConfig, vector<Piece*> pieceList, vector<Vector3i> seedPathVoxels)
{
    UpdateExpVolumeShape( prevPuzConfig, pieceList );

    vector<int> blockAxisIDs;

//    printf("1");
    for (int i=0; i<seedPathVoxels.size(); i++)
    {
        for (int j=0; j<6; j++)
        {
            Vector3i neiborVoxelPos = seedPathVoxels[i] + neiborPos[j];
            Voxel* neiborExpVoxel = GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

            if ( neiborExpVoxel->piece != NONE_PIECE &&
                 std::find(seedPathVoxels.begin(), seedPathVoxels.end(), neiborVoxelPos) == seedPathVoxels.end())
            {
                blockAxisIDs.push_back(j);
            }
        }
    }

    vector<int> moveAxisIDs;
    for (int i=0; i<6; i++)
    {
        if ( std::find(blockAxisIDs.begin(), blockAxisIDs.end(), i) == blockAxisIDs.end() )
        {
            moveAxisIDs.push_back(i);
        }
    }

//    printf("2");
    vector<int> remvAxisIDs;
    for (int i = 0; i < moveAxisIDs.size(); ++i)
    {
        int axisID = moveAxisIDs[i];
        bool isSeedPathRemovable = VoxelGroupRemovableAlongAxis(seedPathVoxels, axisID);

        if (isSeedPathRemovable)
        {
            remvAxisIDs.push_back(axisID);
        }
    }

    return remvAxisIDs;
}

bool ExpVolume::VoxelGroupRemovableAlongAxis(vector<Vector3i> seedPathVoxels, int axisID)
{
    ////////////////////////////////////////////////////////////////
    /// The removable pieceGroup should not have any (far away) blocking voxel along axisID

    int moveStep = 1;

    while (1)
    {
        bool isOutExpVolume;
        bool isOverlap = IsVoxelOverlap(seedPathVoxels, axisID, moveStep, isOutExpVolume);

        if( isOverlap )
        {
//            printf("isOverlap\n");
            return false;
        }

        if( isOutExpVolume )
        {
//            printf("isOutExp\n");
            return true;
        }

//        printf("moveStep: %d\n", moveStep);

        moveStep++;

    }
}

bool ExpVolume::IsVoxelOverlap(vector<Vector3i> seedPathVoxels, int axisID, int moveStep, bool &isOutExpVolume)
{
//    printf("Size of seedPathVoxels: %lu\n", seedPathVoxels.size());
    for (int i = 0; i < seedPathVoxels.size(); ++i)
    {
        Vector3i neiborVoxelPos = seedPathVoxels[i] + moveStep * neiborPos[axisID];
        Voxel* neiborExpVoxel = GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

//        printf("Pos: %d %d %d\n", neiborVoxelPos(0), neiborVoxelPos(1), neiborVoxelPos(2));

        if ( neiborExpVoxel->piece != NONE_PIECE &&
             std::find(seedPathVoxels.begin(), seedPathVoxels.end(), neiborVoxelPos) == seedPathVoxels.end())
        {
            return true;
        }

        if (VoxelInsideExpVolume(neiborVoxelPos, EXPA_VOLUME) == false)
        {
            isOutExpVolume = true;

            return false;
        }
    }

    return false;
}

vector<int> ExpVolume::CheckMovedSeedPathMotionInConfig(PuzConfig *tagtPuzConfig, vector<Piece*> pieceList, int seedPieceID, int seedAxisID, vector<Vector3i> seedPathVoxels)
{
    //int lastPieceID = seedPath.pieceID;
    //int pieceAxisID = seedPath.pieceAxisID;

    ///////////////////////////////////////////////////////////////
    // 1. Generate the moved seed path voxels (move along pieceAxisID for one step)
    //    TODO: here we only consider the seed path moved for one step (possible to be more than one)

    vector<Vector3i> movedSeedPathVoxels;
    for (int i=0; i<seedPathVoxels.size(); i++)
    {
        Vector3i expVoxelPos = seedPathVoxels[i] + neiborPos[seedAxisID];
        movedSeedPathVoxels.push_back( expVoxelPos );
    }


    ///////////////////////////////////////////////////////////////
    // 2. Update the ExpVolume based on tagtPuzConfig and moved seed path

    UpdateExpVolumeShape( tagtPuzConfig, pieceList );

    // Set the voxels on the static seed path to be empty
    for (int i=0; i<seedPathVoxels.size(); i++)
    {
        Vector3i currExpVoxelPos = seedPathVoxels[i];

        SetExoVolumeVoxelPieceID(currExpVoxelPos, EXPA_VOLUME, NONE_PIECE);
    }

    // Set the voxels on the moved seed path to be solid
    for (int i=0; i<movedSeedPathVoxels.size(); i++)
    {
        Vector3i expVoxelPos = movedSeedPathVoxels[i];

       SetExoVolumeVoxelPieceID(expVoxelPos, EXPA_VOLUME, seedPieceID);
    }


    ///////////////////////////////////////////////////////////////
    // 3. Get the blocked axisIDs for the moved seed path

    vector<int> blockAxisIDs;
    for (int i=0; i<movedSeedPathVoxels.size(); i++)
    {
        for (int j=0; j<6; j++)
        {
            Vector3i neiborVoxelPos = movedSeedPathVoxels[i] + neiborPos[j];
            Voxel* neiborExpVoxel = GetExpVolumeVoxel(neiborVoxelPos, EXPA_VOLUME);

            if ( neiborExpVoxel->piece != NONE_PIECE &&
                 std::find(movedSeedPathVoxels.begin(), movedSeedPathVoxels.end(), neiborVoxelPos) == movedSeedPathVoxels.end())

            {
                blockAxisIDs.push_back(j);
            }
        }
    }


    ///////////////////////////////////////////////////////////////
    // 4. Get the motion space of the moved seed path

    vector<int> moveAxisIDs;
    for (int i=0; i<6; i++)
    {
        if ( std::find(blockAxisIDs.begin(), blockAxisIDs.end(), i) == blockAxisIDs.end() )
        {
            moveAxisIDs.push_back(i);
        }
    }


    ///////////////////////////////////////////////////////////////
    // 5. Update the ExpVolume to the tagtPuzConfig

    UpdateExpVolumeShape( tagtPuzConfig, pieceList );

    //printf(" => MoveAxisIDs %d : ", moveAxisIDs.size());
    //for (int i=0; i<moveAxisIDs.size(); i++)
    //	printf(" %s ", axisArray[moveAxisIDs[i]]);
    //printf("\n");

    return moveAxisIDs;

}