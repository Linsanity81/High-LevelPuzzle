///////////////////////////////////////////////////////////////
//
// PuzConfig.cpp
//
//   Puzzle Configuration Class
//
// by Peng SONG ( peng_song@sutd.edu.sg )
//
// 22/Aug/2021
//
// Note:
// (1) A PuzConfig is a state of the remained puzzle pieces and their corresponding positions.
//
///////////////////////////////////////////////////////////////


#include "PuzConfig.h"


extern Vector3i neiborPos[6];



///=========================================================================================///
///                                   Initialization
///=========================================================================================///

PuzConfig::PuzConfig()
{
    puzConfigID = 0;

    distToRoot = 0;
    configType = PUZ_CONFIG_UNKNOWN;

    isTraced = false;
}

PuzConfig::~PuzConfig()
{
	pieceIDList.clear();
	piecePosList.clear();

	nextPuzConfigs.clear();
}

/*PuzConfig & PuzConfig::operator=(const PuzConfig & puzConfig)
{
	this->pieceIDList  = puzConfig.pieceIDList;
	this->piecePosList = puzConfig.piecePosList;

	this->nextPuzConfigs.clear();

	return *this;
}*/

bool PuzConfig::operator==(const PuzConfig & puzConfig)
{
    if ( this->pieceIDList  == puzConfig.pieceIDList &&
         this->piecePosList == puzConfig.piecePosList )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PuzConfig::InitiConfig(vector<int> puzPieceIDs)
{
	pieceIDList = puzPieceIDs;

	for (int i=0; i<pieceIDList.size(); i++)
	{
		piecePosList.push_back(Vector3i(0, 0, 0));
	}
}

void PuzConfig::PrintPuzConfig(bool isShowNextConfig)
{
    for (int i=0; i<pieceIDList.size(); i++)
    {
        printf("Piece %2d  Pos [%2d %2d %2d] \n", pieceIDList[i], piecePosList[i](X_INFO), piecePosList[i](Y_INFO), piecePosList[i](Z_INFO));
    }

    printf("Remv Axis [0] :");
    if (remvAxisIDs.size() > 0)
        printf("%d\n", remvAxisIDs[0]);

    if( isShowNextConfig )
    {
        printf("nextPuzConfigs: %lu \n", nextPuzConfigs.size());

        for (int i=0; i<nextPuzConfigs.size(); i++)
        {
            printf("Next Config: %d \n", i);
            vector<int> nextPieceIDList = nextPuzConfigs[i]->pieceIDList;
            printf("nextPieceIDList: %lu \n", nextPieceIDList.size());
            vector<Vector3i> nextPiecePosList = nextPuzConfigs[i]->piecePosList;
            printf("nextPiecePosList: %lu \n", nextPiecePosList.size());
            for (int j=0; j<nextPieceIDList.size(); j++)
            {
                printf("Piece %2d  Pos [%2d %2d %2d] \n", nextPieceIDList[j], nextPiecePosList[j](X_INFO), nextPiecePosList[j](Y_INFO), nextPiecePosList[j](Z_INFO));
                //printf("Piece %2d \n", nextPieceIDList[j]);
            }
        }
        printf("\n");
    }

    printf("\n");
}




///=========================================================================================///
///                              Create Next PuzConfig (Move Pieces)
///=========================================================================================///

void PuzConfig::CreateNextConfig(vector<int> pieceIDIndices, int moveAxisID, int moveStep, vector<PuzConfig*> &existingConfigs)
{
    ////////////////////////////////////////////////////////////////////
    /// 1. Construct the next puzConfig

    vector<Vector3i> nextPosList = this->piecePosList;
    for (int i=0; i<pieceIDIndices.size(); i++)
    {
        int pieceIDInex = pieceIDIndices[i];

        nextPosList[pieceIDInex] += moveStep * neiborPos[moveAxisID];
    }

    PuzConfig *nextConfig = new PuzConfig();
    nextConfig->pieceIDList  = this->pieceIDList;
    nextConfig->piecePosList = nextPosList;

    //printf("*********************************");
    //this->PrintPuzConfig(false, false);
    //nextConfig->PrintPuzConfig(false, false);


    ////////////////////////////////////////////////////////////////////
    /// 2. Check if the next puzConfig is in the graph

    int configIndex = FindPuzConfigInList( nextConfig, existingConfigs );


    ////////////////////////////////////////////////////////////////////
    /// 3. If the next puzConfig is not in the graph, push back it into the neighbors

    if( configIndex == CONFIG_OUT_LIST )
    {
        existingConfigs.push_back( nextConfig );

        this->nextPuzConfigs.push_back(nextConfig);
        nextConfig->nextPuzConfigs.push_back(this);
    }


    ////////////////////////////////////////////////////////////////////
    /// 4. Otherwise, push back existing puzConfig into the neighbors

    else
    {
        PuzConfig *exitingConfig = existingConfigs[configIndex];

        if( FindPuzConfigInList(exitingConfig,this->nextPuzConfigs ) == CONFIG_OUT_LIST )
        {
            this->nextPuzConfigs.push_back( exitingConfig );
        }

        if( FindPuzConfigInList(this, exitingConfig->nextPuzConfigs ) == CONFIG_OUT_LIST  )
        {
            exitingConfig->nextPuzConfigs.push_back( this );
        }

        delete nextConfig;
    }
}

int PuzConfig::FindPuzConfigInList(PuzConfig *tagtPuzConfig, vector<PuzConfig *> puzConfigList)
{
    for (int i=0; i<puzConfigList.size(); i++)
    {
        if ( *tagtPuzConfig == *puzConfigList[i] )
        {
            return i;
        }
    }

    return CONFIG_OUT_LIST;
}




///=========================================================================================///
///                             Create Next PuzConfig (Remove Pieces)
///=========================================================================================///

void PuzConfig::RemovePieceIDs(vector<int> removablePieceIDs, PuzConfig *newPuzConfig)
{
	vector<int> remainPieceIDList;
	vector<Vector3i> remainPiecePosList;

	for (int i=0; i<pieceIDList.size(); i++)
	{
		if( std::find(removablePieceIDs.begin(), removablePieceIDs.end(), pieceIDList[i]) == removablePieceIDs.end() )
		{
			remainPieceIDList.push_back(pieceIDList[i]);
			remainPiecePosList.push_back(piecePosList[i]);
		}
	}

	newPuzConfig->pieceIDList = remainPieceIDList;
	newPuzConfig->piecePosList = remainPiecePosList;

	newPuzConfig->nextPuzConfigs.clear();
}

Vector3i PuzConfig::GetPiecePos(int pieceID)
{
	int pieceIndex = GetPieceIndexInList(pieceIDList, pieceID);

	return piecePosList[pieceIndex];
}

