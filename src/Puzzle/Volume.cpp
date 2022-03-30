///////////////////////////////////////////////////////////////
//
// Volume.cpp
//
//   3D Volume Class
//
// by Peng SONG ( peng_song@sutd.edu.sg )
// 
// 13/Jun/2021
//
//
///////////////////////////////////////////////////////////////


#include "Utility/HelpDefine.h"
#include "Utility/HelpPuz.h"
#include "PieceFace.h"
#include "Piece.h"
#include "Volume.h"

extern Vector3i neiborPos[6];


///=========================================================================================///
///                                   Initialization
///=========================================================================================///

Volume::Volume()
{
    bbox = NULL;

    outBBoxVoxel = new Voxel();
    outBBoxVoxel->state = VOXEL_OUT_BBOX;
    outBBoxVoxel->piece = NONE_PIECE;

    volumeSize  = Vector3i(0, 0, 0);
    voxelSize   = Vector3f(0, 0, 0);
    volVoxelNum = 0;
}

Volume::~Volume()
{
    ClearVolume();
}

void Volume::ClearVolume()
{
    if( bbox != NULL )
        delete bbox;

    if( outBBoxVoxel != NULL )
        delete outBBoxVoxel;

    for (int i=0; i<voxelGrid.size(); i++)
        delete voxelGrid[i];
    voxelGrid.clear();

    volumeSize  = Vector3i(0, 0, 0);
    voxelSize   = Vector3f(0, 0, 0);
    volVoxelNum = 0;
}

Volume & Volume::operator=(const Volume & volume)
{
    ClearVolume();

    this->bbox = new BoundingBox();
    *(this->bbox) = *volume.bbox;

    this->outBBoxVoxel = new Voxel();
    *(this->outBBoxVoxel) = *volume.outBBoxVoxel;

    for (int i = 0; i < volume.voxelGrid.size(); i++)
    {
        Voxel *voxel = new Voxel();
        *voxel = *volume.voxelGrid[i];
        this->voxelGrid.push_back( voxel );
    }

    this->volumeSize  = volume.volumeSize;
    this->voxelSize   = volume.voxelSize;
    this->volVoxelNum = volume.volVoxelNum;

    return *this;
}

void Volume::PrintVolume()
{
    for (int i=0; i<voxelGrid.size(); i++)
    {
        printf(" %d ",voxelGrid[i]->piece);

        //printf("Voxel [%f %f %f]  Piece [%d] Neighbor [%d %d %d %d %d %d] \n",
        //       voxelGrid[i]->center(X_INFO), voxelGrid[i]->center(Y_INFO), voxelGrid[i]->center(Z_INFO), voxelGrid[i]->piece,
        //       voxelGrid[i]->neiborPiece[0], voxelGrid[i]->neiborPiece[1], voxelGrid[i]->neiborPiece[2],
        //       voxelGrid[i]->neiborPiece[3], voxelGrid[i]->neiborPiece[4], voxelGrid[i]->neiborPiece[5]);
    }

    printf("\n");
}




///=========================================================================================///
///                                    Init/Write Volume
///=========================================================================================///

int Volume::InitVolume(const Vector3i _volumeSize, const Vector3f _voxelSize, const vector<int> puzzleData)
{
    // Volume info
    volumeSize = _volumeSize;
    voxelSize  = _voxelSize;

    int volumeVoxelNum = volumeSize(X_INFO) * volumeSize(Y_INFO) * volumeSize(Z_INFO);

#ifdef SHOW_INFO
    printf("Volume Size:  %d %d %d\n", volumeSize(X_INFO), volumeSize(Y_INFO), volumeSize(Z_INFO));
    printf("Voxel Size:   %.3f %.3f %.3f\n", voxelSize(X_INFO), voxelSize(Y_INFO), voxelSize(Z_INFO));
    printf("Volume Voxel Number:  %d\n", volumeVoxelNum);
#endif

    // Volume bounding box
    if (bbox != NULL)
        delete bbox;
    bbox = new BoundingBox();
    bbox->minPt = Vector3f(-0.5*volumeSize(X_INFO)*voxelSize(X_INFO), -0.5*volumeSize(Y_INFO)*voxelSize(Y_INFO), -0.5*volumeSize(Z_INFO)*voxelSize(Z_INFO));
    bbox->maxPt = Vector3f( 0.5*volumeSize(X_INFO)*voxelSize(X_INFO),  0.5*volumeSize(Y_INFO)*voxelSize(Y_INFO),  0.5*volumeSize(Z_INFO)*voxelSize(Z_INFO));

    // Voxel grid info
    int pieceNum = 0;

    if ( voxelGrid.size() > 0 )
    {
        for(int i=0; i<voxelGrid.size(); i++)
            delete voxelGrid[i];
        voxelGrid.clear();
    }

    for (int i=0; i<volumeVoxelNum; i++)
    {
        Voxel* tempVoxel = new Voxel();
        voxelGrid.push_back(tempVoxel);
    }

    for (int k=0; k<voxelGrid.size(); k++)
    {
        voxelGrid[k]->piece = puzzleData[k] - 1;

        if( voxelGrid[k]->piece > pieceNum )
            pieceNum = voxelGrid[k]->piece;

        if( voxelGrid[k]->piece == NONE_PIECE )
            voxelGrid[k]->state = VOXEL_OUT_VOLUME;
        else
            voxelGrid[k]->state = VOXEL_ON_VOLUME;

        voxelGrid[k]->pos(Z_INFO) = floor( k/((float)volumeSize(Y_INFO)*volumeSize(X_INFO)) );
        int tempRemain = k - voxelGrid[k]->pos(Z_INFO)*(volumeSize(Y_INFO)*volumeSize(X_INFO));
        voxelGrid[k]->pos(Y_INFO) = floor( tempRemain/((float)volumeSize(X_INFO)) );
        voxelGrid[k]->pos(X_INFO) = k - voxelGrid[k]->pos(Z_INFO)*(volumeSize(Y_INFO)*volumeSize(X_INFO)) - voxelGrid[k]->pos(Y_INFO)*volumeSize(X_INFO);

        voxelGrid[k]->size = voxelSize;
        voxelGrid[k]->center(X_INFO) = bbox->minPt(X_INFO) + (voxelGrid[k]->pos(X_INFO)+0.5)*voxelSize(X_INFO);
        voxelGrid[k]->center(Y_INFO) = bbox->maxPt(Y_INFO) - (voxelGrid[k]->pos(Y_INFO)+0.5)*voxelSize(Y_INFO);
        voxelGrid[k]->center(Z_INFO) = bbox->maxPt(Z_INFO) - (voxelGrid[k]->pos(Z_INFO)+0.5)*voxelSize(Z_INFO);

//        printf("Pos: %d %d %d\n", voxelGrid[k]->pos(X_INFO), voxelGrid[k]->pos(Y_INFO), voxelGrid[k]->pos(Z_INFO));

        // Initialize the connectivity data
        for (int i=0; i<6; i++)
        {
            Vector3i neiborVoxelPos = voxelGrid[k]->pos + neiborPos[i];

            if (neiborVoxelPos(X_INFO) < 0 or neiborVoxelPos(X_INFO) > volumeSize(X_INFO) - 1
                or neiborVoxelPos(Y_INFO) < 0 or neiborVoxelPos(Y_INFO) > volumeSize(Y_INFO) - 1
                or neiborVoxelPos(Z_INFO) < 0 or neiborVoxelPos(Z_INFO) > volumeSize(Z_INFO) - 1 )
            {
                voxelGrid[k]->neiborVoxel[i] = NEIGHBOR_NONE_PIECE;
//                printf("%d\n", i);
            }
        }
    }

    // Puzzle voxel number
    volVoxelNum = 0;
    for (int i=0; i<voxelGrid.size(); i++)
    {
        if( voxelGrid[i]->state == VOXEL_ON_VOLUME )
            volVoxelNum++;
    }
#ifdef SHOW_INFO
    printf("Puzzle Voxel Number:  %d \n", volVoxelNum);
#endif

    return pieceNum;
}

vector<Piece*> Volume::ConvertVolume2Puzzle(int pieceNum)
{
    // Puzzle piece number
    pieceNum += 1;
#ifdef SHOW_INFO
    printf("Puzzle Piece Number:  %d\n\n", pieceNum);
#endif

    Piece **piecePool;
    piecePool = new Piece*[pieceNum];
    for (int i=0; i<pieceNum; i++)
    {
        piecePool[i] = new Piece;
        piecePool[i]->pieceID = i;
    }

    // Construct puzzle pieces
    for (int i=0; i<voxelGrid.size(); i++)
    {
        if( voxelGrid[i]->piece != NONE_PIECE )
        {
            int pieceID = voxelGrid[i]->piece;
            piecePool[pieceID]->AddVoxel(voxelGrid[i]);

//            printf("%d %d %d %d %d %d\n", voxelGrid[i]->neiborVoxel[0], voxelGrid[i]->neiborVoxel[1], voxelGrid[i]->neiborVoxel[2],
//                   voxelGrid[i]->neiborVoxel[3], voxelGrid[i]->neiborVoxel[4], voxelGrid[i]->neiborVoxel[5]);
        }
    }

    vector<Piece*> pieceList;
    // Build puzzle
    for (int i=0; i<pieceNum; i++)
    {
        pieceList.push_back(piecePool[i]);
    }
    delete [] piecePool;

    return pieceList;
}

void Volume::WritePuzzleFile(const char fileName[], const float generationTime)
{
    FILE *fp;
    if ((fp=fopen(fileName,"w+"))==NULL)
    {
        printf("Error: file not exists! \n");
    }
    else
    {
        if (generationTime != 0)
        {
            fprintf(fp, "# %.3f\n", generationTime);
        }
        fprintf(fp, "%d %d %d\n", volumeSize[0], volumeSize[1], volumeSize[2]);
        fprintf(fp, "%.6f %.6f %.6f\n", voxelSize[0], voxelSize[1], voxelSize[2]);

        for (int k=0; k<voxelGrid.size(); k++)
        {
            // Note: For merging the last few pieces
            //if (voxelGrid[k].piece > 1 )
            //	voxelGrid[k].piece = 1;

            fprintf(fp,"%d ", voxelGrid[k]->piece+1);
        }
    }

    fclose(fp);
}




///=========================================================================================///
///                             Volume Get Operations
///=========================================================================================///

int Volume::GetVolumeVoxelNum()
{
    return volVoxelNum;
}

Vector3i Volume::GetVolumeSize()
{
    return volumeSize;
}

Vector3f Volume::GetVoxelSize()
{
    return voxelSize;
}

vector<Voxel*> Volume::GetVoxelGrid()
{
    return voxelGrid;
}




///=========================================================================================///
///                             Volume Voxel Operations
///=========================================================================================///

Voxel* Volume::GetVolumeVoxel(Vector3i voxelPos)
{
	if( voxelPos(X_INFO) < 0 || voxelPos(X_INFO) > volumeSize(X_INFO)-1 ||
		voxelPos(Y_INFO) < 0 || voxelPos(Y_INFO) > volumeSize(Y_INFO)-1 ||
		voxelPos(Z_INFO) < 0 || voxelPos(Z_INFO) > volumeSize(Z_INFO)-1 )
	{
		return outBBoxVoxel;
	}
	else
	{
		int voxelIndex = GetVolumeVoxelIndex(voxelPos);
		return voxelGrid[voxelIndex];
	}
}

int Volume::GetVolumeVoxelIndex(Vector3i voxelPos)
{
	int voxelIndex = voxelPos(Z_INFO)*volumeSize(Y_INFO)*volumeSize(X_INFO) + voxelPos(Y_INFO)*volumeSize(X_INFO) + voxelPos(X_INFO);
	return voxelIndex;
}

float Volume::GetNeighborVoxelNum(Vector3i voxelPos, int pieceID)
{
    float neiborVoxelNum = 0;

    for (int i=0; i<6; i++)
    {
        Vector3i neiborVoxelPos = voxelPos + neiborPos[i];
        Voxel* neiborVoxel = GetVolumeVoxel(neiborVoxelPos);

        if ( neiborVoxel->piece == pieceID )
            neiborVoxelNum += 1.0;
    }

    return neiborVoxelNum;
}

void Volume::GetVolumeVoxelNeighbors(Vector3i voxelPos, int neiborPieceIDs[6])
{
    Voxel* currVoxel = GetVolumeVoxel (voxelPos );

    for (int k=0; k<6; k++)
    {
        Voxel* tempVoxel = GetVolumeVoxel(currVoxel->pos + neiborPos[k]);
        neiborPieceIDs[k] = tempVoxel->piece;
    }
}

void Volume::GetVolumeVoxelPosByIndex(int voxelIndex, Vector3i &voxelCentPos)
{
    Voxel* currVoxel = voxelGrid[voxelIndex];

    voxelCentPos = currVoxel->pos;
}




///=========================================================================================///
///                               Puzzle Piece Operations
///=========================================================================================///

void Volume::InitializeRootPiece(Piece *rootPiece)
{
    for (int i=0; i<voxelGrid.size(); i++)
    {
        if( voxelGrid[i]->state == VOXEL_ON_VOLUME )
            rootPiece->AddVoxel(voxelGrid[i]);
    }
}

void Volume::UpdateVolume_PieceID(Piece *piece)
{
    for (int i=0; i<piece->voxelList.size(); i++)
    {
        SetVolumeVoxelPieceID(piece->voxelList[i]->pos, piece->pieceID);
    }
}

void Volume::UpdateVolume_Reach(Piece *piece)
{
    for (int i=0; i<piece->voxelList.size(); i++)
    {
        SetVolumeVoxelReach(piece->voxelList[i]->pos, piece->voxelList[i]->reach);
    }
}

void Volume::SetVolumeVoxelReach(Vector3i voxelPos, const float reach)
{
    int volVoxelIndex = GetVolumeVoxelIndex( voxelPos );
    voxelGrid[volVoxelIndex]->reach = reach;
}

void Volume::SetVolumeVoxelPieceID(Vector3i voxelPos, const int pieceID)
{
    int voxelIndex = GetVolumeVoxelIndex( voxelPos );
    voxelGrid[voxelIndex]->piece = pieceID;
}




///=========================================================================================///
///                                        Volume Info
///=========================================================================================///

void Volume::ComputeVoxelContactPiece(vector<Piece*> pieceList)
{
    // Update the volume shape according to the pieceID in the group
    UpdateVolumeShape(pieceList);

    //printf("Volume shape has been updated.\n");

    for (int i=0; i<pieceList.size(); i++)
    {
        Piece *piece = pieceList[i];

        for (int j=0; j<piece->voxelList.size(); j++)
        {
            GetVolumeVoxelNeighbors( piece->voxelList[j]->pos, piece->voxelList[j]->neiborPiece );
        }
    }

    // Reset the volume to original/complete state
    ResetVolumeShape(pieceList);
}

void Volume::UpdateVolumeShape(vector<Piece*> pieceList)
{
    // Reset volume to original puzzle state
    ClearPieceInfo();

    //printf("Volume piece has been cleared.\n");

    // The pieceIDList saves all the pieceID that should be kept in the volume
    for (int i=0; i<pieceList.size(); i++)
    {
        Piece *piece = pieceList[i];

        for (int j=0; j<piece->voxelList.size(); j++)
        {
            Vector3i voxelPos = piece->voxelList[j]->pos;
            int pieceID = piece->pieceID;

            SetVolumeVoxelPieceID(voxelPos, pieceID);
        }
    }
}

void Volume::ResetVolumeShape(vector<Piece*> pieceList)
{
    ClearPieceInfo();

    for (int i=0; i<pieceList.size(); i++)
    {
        for (int j=0; j<pieceList[i]->voxelList.size(); j++)
        {
            Vector3i voxelPos = pieceList[i]->voxelList[j]->pos;
            int voxelPieceID  = pieceList[i]->voxelList[j]->piece;

            SetVolumeVoxelPieceID(voxelPos, voxelPieceID);
        }
    }
}

void Volume::ClearPieceInfo()
{
    for (int i=0; i<voxelGrid.size(); i++)
    {
        voxelGrid[i]->piece = NONE_PIECE;
    }
}