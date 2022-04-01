///////////////////////////////////////////////////////////////
//
// PuzAction.cpp
//
//   Piece Disassembly Action Class
//
// by Peng SONG ( peng_song@sutd.edu.sg )
// 
// 22/Aug/2021
//
// Note:
// (1) A PuzAction is an action for disassembling puzzle. It can be either moving
//     a group of pieces together or removing a single piece.
//
///////////////////////////////////////////////////////////////

#include "PuzAction.h"

extern char axisArray[6][4];

///=========================================================================================///
///                                   Initialization
///=========================================================================================///

PuzAction::PuzAction()
{
	diassOrder = 0;
	isMoveAction = false;

	moveVector = Vector3i(0, 0, 0);
}

PuzAction::~PuzAction()
{
	movePieceIDs.clear();
	remvAxisIDs.clear();
}

PuzAction & PuzAction::operator=(const PuzAction &puzAction)
{
	this->diassOrder     =   puzAction.diassOrder;
	this->isMoveAction   =   puzAction.isMoveAction;

	this->movePieceIDs   =   puzAction.movePieceIDs;
	this->moveVector     =   puzAction.moveVector;

	this->remvPieceIDs   =   puzAction.remvPieceIDs;
	this->remvAxisIDs    =   puzAction.remvAxisIDs;

	return *this;
}

void PuzAction::PrintPuzAction()
{
    if( isMoveAction )
    {
        printf("DiassOrder %d:  Move", diassOrder);

        for (int i=0; i<movePieceIDs.size(); i++)
            printf(" P%d", movePieceIDs[i]);

        printf("   MoveVec:   [%d %d %d] \n", moveVector(X_INFO), moveVector(Y_INFO), moveVector(Z_INFO));
    }
    else
    {
        printf("DiassOrder %d:  Remv", diassOrder);

        for (int i=0; i<remvPieceIDs.size(); i++)
            printf(" P%d", remvPieceIDs[i]);

        for (int i=0; i<remvAxisIDs.size(); i++)
        {
            printf(" %s ", axisArray[remvAxisIDs[i]]);
        }
        printf("\n\n");
    }
}




///=========================================================================================///
///                                PuzAction Operations
///=========================================================================================///

void PuzAction::GetPieceGroupMoveVector(Vector3i volumeSize, Vector3f voxelSize, vector<int> &actualMovePieceIDs, Vector3f &actualMoveVector)
{
    Vector3f tempMoveVector;
    const float moveDistCoeff = 1.4;

    if( isMoveAction )
    {
        actualMovePieceIDs = movePieceIDs;

        tempMoveVector(0) = moveVector(0);
        tempMoveVector(1) = moveVector(1);
        tempMoveVector(2) = moveVector(2);
    }
    else
    {
        actualMovePieceIDs = remvPieceIDs;

        int moveAxisID = remvAxisIDs[0];

        if      ( moveAxisID == 0 )     tempMoveVector = moveDistCoeff * volumeSize[0] * Vector3f(-1,  0,  0 );
        else if ( moveAxisID == 1 )     tempMoveVector = moveDistCoeff * volumeSize[0] * Vector3f( 1,  0,  0 );
        else if ( moveAxisID == 2 )     tempMoveVector = moveDistCoeff * volumeSize[1] * Vector3f( 0, -1,  0 );
        else if ( moveAxisID == 3 )     tempMoveVector = moveDistCoeff * volumeSize[1] * Vector3f( 0,  1,  0 );
        else if ( moveAxisID == 4 )     tempMoveVector = moveDistCoeff * volumeSize[2] * Vector3f( 0,  0, -1 );
        else if ( moveAxisID == 5 )     tempMoveVector = moveDistCoeff * volumeSize[2] * Vector3f( 0,  0,  1 );
    }

    actualMoveVector(0) = tempMoveVector(0) * voxelSize(0);
    actualMoveVector(1) = tempMoveVector(1) * voxelSize(1);
    actualMoveVector(2) = tempMoveVector(2) * voxelSize(2);
}


void PuzAction::WritePuzAction(FILE *fp, Vector3f voxelSize, Vector3i volumeSize)
{
    int movePieceID;
    int rmvPieceID;
    int rmvAxisID;
    int frameNum;
    int volumeAvgSize = (volumeSize(X_INFO) + volumeSize(Y_INFO) + volumeSize(Z_INFO)) / 3.0;
    int moveStepNum = 1.0 * volumeAvgSize;

    Vector3f curmoveVector;
    Vector3f moveStep;
    Vector3f rmvVector;

    Vector3f puzAxes[6] = {Vector3f(-1.0,  0.0, 0.0), Vector3f(1.0, 0.0,  0.0), Vector3f(0.0, -1.0, 0.0),
                           Vector3f( 0.0,  1.0, 0.0), Vector3f(0.0, 0.0, -1.0), Vector3f(0.0,  0.0, 1.0)};

    if ( isMoveAction )
    {
        for (int i = 0; i < movePieceIDs.size(); i++)
            movePieceID = movePieceIDs[i];

        moveStep(X_INFO) =  moveVector(X_INFO);
        moveStep(Y_INFO) =  moveVector(Y_INFO);
        moveStep(Z_INFO) =  moveVector(Z_INFO);
        curmoveVector(X_INFO) = moveStep(X_INFO) * voxelSize(X_INFO);
        curmoveVector(Y_INFO) = moveStep(Y_INFO) * voxelSize(Y_INFO);
        curmoveVector(Z_INFO) = moveStep(Z_INFO) * voxelSize(Z_INFO);

        frameNum = moveStep.norm() * 30;

        fprintf(fp, "Begin Action %d\n", frameNum);
        fprintf(fp, "Move id %d [%.2f, %.2f, %.2f]\n", movePieceID + 1, curmoveVector(X_INFO),  curmoveVector(Y_INFO),  curmoveVector(Z_INFO));
        fprintf(fp, "End\n");
    }


    else
    {
        for (int i=0; i<remvPieceIDs.size(); i++)
            rmvPieceID = remvPieceIDs[i];
        for (int i = 0; i < remvAxisIDs.size(); i++)
            rmvAxisID = remvAxisIDs[i];

        rmvVector(X_INFO) = puzAxes[rmvAxisID](X_INFO) * voxelSize(X_INFO) * moveStepNum;
        rmvVector(Y_INFO) = puzAxes[rmvAxisID](Y_INFO) * voxelSize(Y_INFO) * moveStepNum;
        rmvVector(Z_INFO) = puzAxes[rmvAxisID](Z_INFO) * voxelSize(Z_INFO) * moveStepNum;

        frameNum = moveStepNum * 10;

        fprintf(fp, "Begin Action %d\n", frameNum);
        fprintf(fp, "Move id %d [%.2f, %.2f, %.2f]\n", rmvPieceID + 1, rmvVector(X_INFO),  rmvVector(Y_INFO),  rmvVector(Z_INFO));
        fprintf(fp, "End\n");
    }
}


