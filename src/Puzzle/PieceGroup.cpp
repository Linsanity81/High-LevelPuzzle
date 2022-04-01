///////////////////////////////////////////////////////////////
//
// PieceGroup.cpp
//
//   Piece Group Class
//
// by Song Peng ( song0083@ntu.edu.sg )
// 
// 21/Feb/2012
//
///////////////////////////////////////////////////////////////

#include "PieceFace.h"
#include "Piece.h"
#include "PieceGroup.h"

extern char axisArray[6][4];


//**************************************************************************************//
//                                   Initialization
//**************************************************************************************//

PieceGroup::PieceGroup()
{
	pieceFace = new PieceFace[6];	

	isConnected = false;
}

PieceGroup::~PieceGroup()
{
	delete [] pieceFace;

	pieceList.clear();
	pieceIDList.clear();
	piecePosList.clear();
	groupVoxelList.clear();

	neiborPiece.clear();
	movableAxis.clear();
}

void PieceGroup::ClearGroup()
{
	pieceList.clear();
	pieceIDList.clear();
	piecePosList.clear();
	groupVoxelList.clear();
}

void PieceGroup::AddPiece(Piece *piece)
{
	pieceList.push_back(piece);
	pieceIDList.push_back(piece->pieceID);

	for (int i=0; i<piece->voxelList.size(); i++)
	{
		groupVoxelList.push_back(piece->voxelList[i]);
	}
}

void PieceGroup::AddPiece(Piece *piece, Vector3i piecePos)
{
	pieceList.push_back( piece );
	pieceIDList.push_back( piece->pieceID );
	piecePosList.push_back( piecePos );

	for (int i=0; i<piece->voxelList.size(); i++)
	{
//	    piece->voxelList[i]->pos += piecePos;
		groupVoxelList.push_back(piece->voxelList[i]);
	}
}



//**************************************************************************************//
//                               Process Piece Group
//**************************************************************************************//

bool PieceGroup::CheckGroupConnectivity()
{
	int groupPieceNum = pieceList.size();
	if ( groupPieceNum == 0 )
	{
//		printf("Error: The piece group is empty! \n");
		isConnected = false;
	}
	else if( groupPieceNum == 1 )
	{
		//printf("Warning: The piece group only contains one piece! \n");
		isConnected = true;
	}
	else
	{
		std::vector<Piece*> bfsQueue;
		std::vector<bool> visited(groupPieceNum, false);
		int connectedPieceNum = 0;

		// Find a root for Breadth-First Search Traversal 
		Piece *root;
		root = pieceList[0];
		visited[0] = true;
		connectedPieceNum++;
		bfsQueue.push_back(root);

		// Start Breadth-First Search Traversal
		while( !bfsQueue.empty() )
		{
			Piece *currVisit = bfsQueue[0];
			bfsQueue.erase( bfsQueue.begin() );
			Piece *nextVisit;

			for (int i=0; i<currVisit->neiborPiece.size(); i++)
			{
				int index = GetPieceIndexInGroup( currVisit->neiborPiece[i] );
				if( index >=0 )
				{
					nextVisit = pieceList[index];
					if( !visited[index] )
					{
						visited[index] = true;
						bfsQueue.push_back(nextVisit);
						connectedPieceNum++;
					}
				}

				// Just return if all the pieces are connected
				if( connectedPieceNum == groupPieceNum )
				{
					isConnected = true;
					return isConnected;
				}
			}
		}

		if( connectedPieceNum == groupPieceNum )
			isConnected = true;
		else
			isConnected = false;
	}

	return isConnected;
}

int PieceGroup::GetPieceIndexInGroup(int pieceID)
{
	// Example: Pieces in Group: [1, 5, 2, 7, 6]
	// Given PieceID 7, find its index 4th in group

	int indexInGroup = -1;
	for (int i=0; i<pieceIDList.size(); i++)
	{
		if(pieceIDList[i] == pieceID)
		{
			indexInGroup = i;
		}
	}
	return indexInGroup;
}

void PieceGroup::ComputeGroupFace()
{
	// Clear the data saved in group piece face
	for (int i=0; i<6; i++)
	{
		pieceFace[i].ClearPieceFace();
	}

	// Save all the voxels on the piece faces
	for (int i=0; i<groupVoxelList.size(); i++)
	{
		for (int j=0; j<6; j++)
		{
			int pieceID = groupVoxelList[i]->neiborPiece[j];
			if( pieceID == NONE_PIECE )
			{
				pieceFace[j].AddSurfaceVoxel(groupVoxelList[i]);
			}
			else if( std::find(pieceIDList.begin(), pieceIDList.end(), pieceID) == pieceIDList.end() )
			{
				pieceFace[j].AddContactVoxel(groupVoxelList[i]);
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

void PieceGroup::ComputeNeighborPiece()
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

void PieceGroup::ComputeMovableAxis()
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




//**************************************************************************************//
//                                 Piece Group Debug
//**************************************************************************************//

void PieceGroup::PrintGroupInfo(bool isPrintMotion)
{
	// Piece indices in group
	printf("Group   : ");
	for (int i=0; i<pieceList.size(); i++)
	{
		printf(" %d ", pieceList[i]->pieceID);
	}
	printf("\n");

	if ( isPrintMotion )
	{
		if( !isConnected )
		{
			printf("           Disconnected \n");
		}
		else
		{
			// Neighbor pieces
			printf("Neighbor: ");
			for (int i=0; i<neiborPiece.size(); i++)
			{
				printf(" %d ", neiborPiece[i]);
			}
			printf("\n");

			// Movable axes
			printf("MoveAxes: ");
			for (int i=0; i<movableAxis.size(); i++)
			{
				printf(" %s", axisArray[movableAxis[i]]);
			}
			printf("\n");
		}
		printf("\n");
	}
}


void PieceGroup::SaveGroupInfo(char fileName[])
{
	FILE *fp;
	if ((fp=fopen(fileName,"a+"))==NULL)
	{
		printf("Error: file not exists! \n");	
	}
	else
	{
		fprintf(fp, "Group   : ");
		for (int i=0; i<pieceList.size(); i++)
		{
			fprintf(fp, " %d ", pieceList[i]->pieceID);
		}
		fprintf(fp, "\n");

		if( !isConnected )
		{
			fprintf(fp, "           Disconnected \n");
		}
		else
		{
			fprintf(fp, "MoveAxes: ");
			for (int i=0; i<movableAxis.size(); i++)
			{
				fprintf(fp, " %s", axisArray[movableAxis[i]]);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
	}
	fclose(fp); 
}