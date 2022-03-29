///////////////////////////////////////////////////////////////
//
// PieceFace.cpp
//
//   Puzzle Piece Class
//
// by Song Peng ( song0083@ntu.edu.sg )
// 
// 06/Mar/2013
//
///////////////////////////////////////////////////////////////

#include "PieceFace.h"

extern char axisArray[6][4];


///////////////////////////////////////////////////////////////
//                      Voxel Class
///////////////////////////////////////////////////////////////

Voxel::Voxel()
{
	center  =  Vector3f(0, 0, 0);
	size    =  Vector3f(1, 1, 1);
	pos     =  Vector3i(0, 0, 0);
	state   =  VOXEL_OUT_BBOX;

	piece   =  NONE_PIECE;
	for (int i=0; i<6; i++)
		neiborPiece[i] = NONE_PIECE;

	for (int i = 0; i < 6; ++i)
    {
	    neiborVoxel[i] = NEIGHBOR_CONNECTED;
    }

	reach   =  -1.0;
	color   =  -1.0;

	dist    =  -1;
	visited = false;

	marked = false;
}

Voxel::~Voxel()
{
	;
}

Voxel & Voxel::operator=(const Voxel & voxel)
{
	if( this == &voxel )
		return *this;

	this->center  = voxel.center;
	this->size    = voxel.size;     
	this->pos     = voxel.pos;     
	this->state   = voxel.state;   

	this->piece   = voxel.piece; 
	for (int i=0; i<6; i++)
		this->neiborPiece[i] = voxel.neiborPiece[i];

	for (int i = 0; i < 6; i++)
    {
        this->neiborVoxel[i] = voxel.neiborVoxel[i];
    }
	
	this->reach   = voxel.reach;
	//this->color   = voxel.color;

	this->dist    = voxel.dist;  
	this->visited = voxel.visited;

	return *this;
}

bool Voxel::IsEqual(Voxel temp)
{
	// Note: Have not check neiborPiece[6], center, and neiborVoxel[6]
	// since the voxel center has been offset by bbox.center
	if( this->size   == temp.size &&
		this->pos    == temp.pos  &&
		this->state  == temp.state &&
		this->piece  == temp.piece )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Voxel::PrintVoxel()
{
	printf("Voxel Center: %.2f %.2f %.2f \n", this->center(X_INFO), this->center(Y_INFO), this->center(Z_INFO));
	printf("Voxel Size:   %.2f %.2f %.2f \n", this->size(X_INFO), this->size(Y_INFO), this->size(Z_INFO));
	printf("Voxel Pos:    %d %d %d \n", this->pos(X_INFO), this->pos(Y_INFO), this->pos(Z_INFO));
	printf("Voxel State:  %d \n", this->state);

	printf("Voxel Piece:  %d \n", this->piece);
	printf("Voxel Dist:   %d \n", this->dist);
	printf("Voxel Neibor: %d %d %d %d %d %d \n", this->neiborPiece[0], this->neiborPiece[1], this->neiborPiece[2], 
		                                         this->neiborPiece[3], this->neiborPiece[4], this->neiborPiece[5]);
	printf("\n");
}




///////////////////////////////////////////////////////////////
//                      Piece Face Class
///////////////////////////////////////////////////////////////

PieceFace::PieceFace()
{
	faceID = 0;
}

PieceFace::~PieceFace()
{
	surfaceVoxel.clear();
	contactVoxel.clear();
	contactedPiece.clear();
}

void PieceFace::SetPieceFaceID(int pieceFaceID )
{
	faceID = pieceFaceID;
}

void PieceFace::PrintPieceFace()
{
	printf("Dir %s : ", axisArray[faceID]);
	printf("ContactPiece: ");
	for (int i=0; i<contactedPiece.size(); i++)
	{
		printf(" %d ", contactedPiece[i]);
	}
	printf("\n");
}


//**************************************************************************************//
//                         Piece Face Voxel and Contact Pieces 
//**************************************************************************************//

void PieceFace::AddSurfaceVoxel(Voxel *voxel)
{
	surfaceVoxel.push_back(voxel);
}

void PieceFace::AddContactVoxel(Voxel *voxel)
{
	contactVoxel.push_back(voxel);
}

void PieceFace::ComputeContactPiece()
{
	for (int i=0; i<contactVoxel.size(); i++)
	{
		Voxel *currVoxel = contactVoxel[i];

		if ( currVoxel->neiborPiece[faceID] >= 0 )
		{
			if (std::find(contactedPiece.begin(), contactedPiece.end(), currVoxel->neiborPiece[faceID]) == contactedPiece.end() )
				contactedPiece.push_back(currVoxel->neiborPiece[faceID]);
		}
		else
		{
			printf("Warning: There should be a neighboring piece for any contactVoxel along faceID axis! \n");
		}
	}
}

void PieceFace::ClearPieceFace()
{
	surfaceVoxel.clear();
	contactVoxel.clear();
	contactedPiece.clear();
}