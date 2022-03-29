///////////////////////////////////////////////////////////////
//
// Piece.cpp
//
//   Puzzle Piece Class
//
// by Peng Song  ( peng_song@sutd.edu.sg )
//
// 12/Jun/2021
//
///////////////////////////////////////////////////////////////


#include <Eigen/Eigen>
#include "Utility/HelpPuz.h"
#include "PieceFace.h"
#include "Piece.h"


extern Vector3i neiborPos[6];
extern char axisArray[6][4];


///=========================================================================================///
///                                   Initialization
///=========================================================================================///

Piece::Piece()
{
	isPicked  =  false;
	pieceID   =  NONE_PIECE;

	pieceFace =  new PieceFace[6];
}

Piece::~Piece()
{
	for (int i=0; i<voxelList.size(); i++)
	{
		delete voxelList[i];
	}

	delete [] pieceFace;

	voxelList.clear();
	neiborPiece.clear();
	movableAxis.clear();
}

Piece & Piece::operator=(const Piece & piece)
{
    /// Note:
    /// pieceFace is not copied and require calling ComputePieceFace() to get the value

	this->isPicked  = piece.isPicked;
	this->pieceID   = piece.pieceID;

	for (int i=0; i<piece.voxelList.size(); i++)
	{
		Voxel *voxel = new Voxel();
		*voxel = *piece.voxelList[i];
		this->voxelList.push_back( voxel );
	}

	this->neiborPiece = piece.neiborPiece;
    this->movableAxis = piece.movableAxis;

	return *this;
}

void Piece::AddVoxel(Voxel *voxel)
{
	// Set pieceID for voxel in the volume
	voxel->piece = pieceID;

	Voxel *tempVoxel = new Voxel;
	tempVoxel->center = voxel->center;
	tempVoxel->size   = voxel->size;
	tempVoxel->pos    = voxel->pos;
	tempVoxel->state  = voxel->state;
	tempVoxel->piece  = voxel->piece;

	for (int i = 0; i < 6; i++)
    {
        tempVoxel->neiborVoxel[i] = voxel->neiborVoxel[i];
    }

	voxelList.push_back(tempVoxel);
}

/*bool Piece::CheckConnectivity()
{
	bool isConnected = CheckVoxelsConnectivity(voxelList);

	return isConnected;
}*/

bool Piece::CheckConnectivity()
{
    bool isConnected = CheckVoxelsConnectivity(voxelList);

    return isConnected;
}

int Piece::ConnectivityAnalysis()
{
    vector<vector<Voxel*>> voxelGroups;

    GroupConnectedVoxels(voxelList, voxelGroups);

    if( voxelGroups.size() == 0 )
    {
        printf("Warning:  there is no connected group.  voxelNum: %lu \n\n", voxelList.size());
    }

    return voxelGroups.size();
}




///=========================================================================================///
///                             Puzzle Piece Motion Analysis
///=========================================================================================///

void Piece::ComputePieceFace()
{
	// Clear the piece face voxels and contact pieces
	for (int i=0; i<6; i++)
	{
		pieceFace[i].ClearPieceFace();
	}

	// Compute all the voxels on each piece face
	for (int i=0; i<voxelList.size(); i++)
	{
		for (int j=0; j<6; j++)
		{
			if( voxelList[i]->neiborPiece[j] == NONE_PIECE )
			{
				pieceFace[j].AddSurfaceVoxel(voxelList[i]);
			}
			else if( voxelList[i]->neiborPiece[j] != pieceID )
			{
				pieceFace[j].AddContactVoxel(voxelList[i]);
			}
		}
	}

	// Compute contacting pieces of current piece's each face 
	for (int i=0; i<6; i++)
	{
		pieceFace[i].SetPieceFaceID(i);
		pieceFace[i].ComputeContactPiece();
	}
}

void Piece::ComputeNeighborPiece()
{
	neiborPiece.clear();

	for (int i=0; i<6; i++)
	{
		for (int j=0; j<pieceFace[i].contactedPiece.size(); j++)
		{
			if (std::find(neiborPiece.begin(), neiborPiece.end(), pieceFace[i].contactedPiece[j]) == neiborPiece.end() )
				neiborPiece.push_back(pieceFace[i].contactedPiece[j]);
		}
	}
}

void Piece::ComputeMovableAxis()
{
	movableAxis.clear();

	for (int i=0; i<6; i++)
	{
		if( pieceFace[i].contactedPiece.size() == 0 )
		{
			movableAxis.push_back(i);
		}
	}
}

void Piece::ClearPiece()
{
	for (int i=0; i<6; i++)
	{
		pieceFace[i].ClearPieceFace();
	}

	neiborPiece.clear();
	movableAxis.clear();
}

void Piece::PrintPieceInfo()
{
	printf("Piece %d  : \n", pieceID);

	//printf("VoxelNum: %d \n", voxelList.size());

	printf("Piece Voxel: \n");
	for (int i=0; i<voxelList.size(); i++)
	{
		printf("%d: Voxel [%d %d %d] \n", i, voxelList[i]->pos(X_INFO), voxelList[i]->pos(Y_INFO), voxelList[i]->pos(Z_INFO));
	}

	printf("Piece Face: \n");
	for (int i=0; i<6; i++)
	{
		pieceFace[i].PrintPieceFace();
	}

	printf("Neighbor: ");
	for (int i=0; i<neiborPiece.size(); i++)
	{
		printf(" %d ", neiborPiece[i]);
	}
	printf("\n");

	printf("MoveAxes: ");
	for (int i=0; i<movableAxis.size(); i++)
	{
		printf(" %s", axisArray[movableAxis[i]]);
	}
	printf("\n\n");
}




///=========================================================================================///
///                                  Piece Drawing Data
///=========================================================================================///

void Piece::CreatePieceGeometry(Vector3f puzTransVec,
                                Eigen::MatrixXf &voxelMinPts,
                                Eigen::MatrixXf &voxelMaxPts,
                                Eigen::MatrixXf &voxelCenPts,
                                Eigen::MatrixXf &cylinTopPts,
                                Eigen::MatrixXf &cylinBotPts)
{
    ///////////////////////////////////////////////////////////////
    /// 1. Extract the voxel center, min, and max points

    voxelMinPts.resize(voxelList.size(),3);
    voxelMaxPts.resize(voxelList.size(),3);
    voxelCenPts.resize(voxelList.size(),3);

    for (int i = 0; i < voxelList.size(); i++)
    {
        Voxel *voxel = voxelList[i];

        for (int j = 0; j < 3; ++j)
        {
            voxelCenPts(i,j) = 1.0f*voxel->pos(j)*voxel->size(j) + puzTransVec(j);  // puzTransVec for making the puzzle centered at the origin

            voxelMinPts(i,j) = voxelCenPts(i,j) - 0.5f*voxel->size(j);
            voxelMaxPts(i,j) = voxelCenPts(i,j) + 0.5f*voxel->size(j);

            voxelList[i]->center(j) = voxelCenPts(i,j);
        }
    }


    ///////////////////////////////////////////////////////////////
    /// 2. Compute the number of cylinders

    int numCylinder = 0;
    for (int i = 0; i < voxelList.size(); i++)
    {
        Voxel *currVoxel = voxelList[i];

        for (int j = 0; j < 6; j++)
        {
            Vector3i neiborVoxelPos = currVoxel->pos + neiborPos[j];

            for (int k = 0; k < voxelList.size(); k++)
            {
                Voxel *tempVoxel = voxelList[k];
                if (tempVoxel->pos == neiborVoxelPos)
                {
                    numCylinder++;
                }
            }
        }
    }

    cylinTopPts.resize(numCylinder,3);
    cylinBotPts.resize(numCylinder,3);


    ///////////////////////////////////////////////////////////////
    /// 3. Extract the cylinder endpoints

    int cylinID = 0;

    for (int i = 0; i < voxelList.size(); i++)
    {
        Voxel *currVoxel = voxelList[i];

        for (int j = 0; j < 6; j++)
        {
            Vector3i neiborVoxelPos = currVoxel->pos + neiborPos[j];

            for (int k = 0; k < voxelList.size(); k++)
            {
                Voxel *neibVoxel = voxelList[k];

                if (neibVoxel->pos == neiborVoxelPos)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        cylinTopPts(cylinID, k) = 1.0f*currVoxel->pos(k)*currVoxel->size(k) + puzTransVec(k);
                        cylinBotPts(cylinID, k) = 1.0f*neibVoxel->pos(k)*neibVoxel->size(k) + puzTransVec(k);
                    }

                    cylinID++;
                }
            }
        }
    }
}



void Piece::CreatePieceGeometry(Eigen::MatrixXf &voxelMinPts,
                                Eigen::MatrixXf &voxelMaxPts,
                                Eigen::MatrixXf &voxelCenPts,
                                Eigen::MatrixXf &cylinTopPts,
                                Eigen::MatrixXf &cylinBotPts)
{
    ///////////////////////////////////////////////////////////////
    /// 1. Extract the voxel center, min, and max points

    voxelMinPts.resize(voxelList.size(),3);
    voxelMaxPts.resize(voxelList.size(),3);
    voxelCenPts.resize(voxelList.size(),3);

    for (int i = 0; i < voxelList.size(); i++)
    {
        Voxel *voxel = voxelList[i];

        voxelCenPts(i,0) = 1.0f*voxel->pos(0)*voxel->size(0);
        voxelCenPts(i,1) = 1.0f*voxel->pos(1)*voxel->size(1);
        voxelCenPts(i,2) = 1.0f*voxel->pos(2)*voxel->size(2);

        voxelMinPts(i,0) = voxelCenPts(i,0) - 0.5f*voxel->size(0);
        voxelMinPts(i,1) = voxelCenPts(i,1) - 0.5f*voxel->size(1);
        voxelMinPts(i,2) = voxelCenPts(i,2) - 0.5f*voxel->size(2);

        voxelMaxPts(i,0) = voxelCenPts(i,0) + 0.5f*voxel->size(0);
        voxelMaxPts(i,1) = voxelCenPts(i,1) + 0.5f*voxel->size(1);
        voxelMaxPts(i,2) = voxelCenPts(i,2) + 0.5f*voxel->size(2);

        voxelList[i]->center(0) = voxelCenPts(i,0);
        voxelList[i]->center(1) = voxelCenPts(i,1);
        voxelList[i]->center(2) = voxelCenPts(i,2);

        //printf("MinPt [%.3f %.3f %.3f] \n", voxelMinPts(i,0), voxelMinPts(i,1), voxelMinPts(i,2));
        //printf("MaxPt [%.3f %.3f %.3f] \n", voxelMaxPts(i,0), voxelMaxPts(i,1), voxelMaxPts(i,2));
    }


    ///////////////////////////////////////////////////////////////
    /// 2. Compute the number of cylinders

    int numCylinder = 0;
    for (int i = 0; i < voxelList.size(); i++)
    {
        Voxel *currVoxel = voxelList[i];

        for (int j = 0; j < 6; j++)
        {
            Vector3i neiborVoxelPos = currVoxel->pos + neiborPos[j];

            for (int k = 0; k < voxelList.size(); k++)
            {
                Voxel *tempVoxel = voxelList[k];
                if (tempVoxel->pos == neiborVoxelPos)
                {
                    numCylinder++;
                }
            }
        }
    }

    cylinTopPts.resize(numCylinder,3);
    cylinBotPts.resize(numCylinder,3);


    ///////////////////////////////////////////////////////////////
    /// 3. Extract the cylinder endpoints

    int cylinID = 0;

    for (int i = 0; i < voxelList.size(); i++)
    {
        Voxel *currVoxel = voxelList[i];

        for (int j = 0; j < 6; j++)
        {
            Vector3i neiborVoxelPos = currVoxel->pos + neiborPos[j];

            for (int k = 0; k < voxelList.size(); k++)
            {
                Voxel *neibVoxel = voxelList[k];

                if (neibVoxel->pos == neiborVoxelPos)
                {
                    cylinTopPts(cylinID, 0) = 1.0f*currVoxel->pos(0)*currVoxel->size(0);
                    cylinTopPts(cylinID, 1) = 1.0f*currVoxel->pos(1)*currVoxel->size(1);
                    cylinTopPts(cylinID, 2) = 1.0f*currVoxel->pos(2)*currVoxel->size(2);

                    cylinBotPts(cylinID, 0) = 1.0f*neibVoxel->pos(0)*neibVoxel->size(0);
                    cylinBotPts(cylinID, 1) = 1.0f*neibVoxel->pos(1)*neibVoxel->size(1);
                    cylinBotPts(cylinID, 2) = 1.0f*neibVoxel->pos(2)*neibVoxel->size(2);

                    cylinID++;
                }
            }
        }
    }
}

