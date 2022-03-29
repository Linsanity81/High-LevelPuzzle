///////////////////////////////////////////////////////////////
//
// Helper.cpp
//
//   Utility Tool Functions
//
// by Peng Song
//
// 27/Aug/2021
//

///////////////////////////////////////////////////////////////

#include "Utility/HelpDefine.h"
#include "Puzzle/PieceFace.h"
#include "Utility/HelpPuz.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <igl/readOBJ.h>


///////////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////////

// Neighbor position along six direction
Vector3i neiborPos[6] = { DIR_NEGATIVE_X, DIR_POSITIVE_X,
                          DIR_NEGATIVE_Y, DIR_POSITIVE_Y,
						  DIR_NEGATIVE_Z, DIR_POSITIVE_Z };

// Six movable axes for printing
char axisArray[6][4] = {"-x", "+x", "-y", "+y", "-z", "+z"};


///=========================================================================================///
///                              High-Level Puzzle Related
///=========================================================================================///

struct UniqueVoxel
{
	Vector3i voxelPos;
	vector<int> setIndices;
};

///////////////////////////////////////////////////////////////////////////////////////
// Input:   (1) solidVoxels: a group/vector of voxels in ExpVolume
//          (2) solidVoxelsSet: a group/vector of solidVoxels     
//
// OutPut:  (1) contactVoxels: a group/vector of voxels in ExpVolume (with one or two voxels)     
//          (2) contactVoxelsSet: a group/vector of contactVoxels 
//
// Note:    (1) For each solidVoxels Si and one contactVoxels C, the intersection between
//              Si and C can not be empty.
///////////////////////////////////////////////////////////////////////////////////////

vector<vector<Vector3i>> ComputeContactVoxelsSet(vector<vector<Vector3i>> solidVoxelsSet)
{
	//printf("\n\n===================Solid Voxel Sets====================\n\n");
	//for (int i=0; i<solidVoxelsSet.size(); i++)
	//{
	//	printf("Set %d: ", i);
	//	for (int j=0; j<solidVoxelsSet[i].size(); j++)
	//	{
	//		printf(" [%d %d %d] ", solidVoxelsSet[i][j](X_INFO), solidVoxelsSet[i][j](Y_INFO), solidVoxelsSet[i][j](Z_INFO));
	//	}
	//	printf("\n");
	//}

	///////////////////////////////////////////////////////////////////////
	// Compute the unique expVoxel position and the configIndices that this voxel falls into

	vector<UniqueVoxel> uniqueVoxels;
	for (int i=0; i<solidVoxelsSet.size(); i++)
	{
		for (int j=0; j<solidVoxelsSet[i].size(); j++)
		{
			Vector3i tempVoxelPos = solidVoxelsSet[i][j];
			bool isNewCrossVoxel = true;

			for(int k=0; k<uniqueVoxels.size(); k++)
			{
				if ( uniqueVoxels[k].voxelPos == tempVoxelPos )
				{
					uniqueVoxels[k].setIndices.push_back(i);
					isNewCrossVoxel = false;
				}
			}

			if ( isNewCrossVoxel )
			{
				UniqueVoxel tempVoxel;
				tempVoxel.voxelPos = tempVoxelPos;
				tempVoxel.setIndices.push_back(i);
				uniqueVoxels.push_back( tempVoxel );
			}
		}
	}

	//printf("\n\n=============Unique Voxels (Before Sorting)==============\n\n");
	//for (int i=0; i<uniqueVoxels.size(); i++)
	//{
	//	printf("Voxel [%d %d %d]: ", uniqueVoxels[i].voxelPos(X_INFO), uniqueVoxels[i].voxelPos(Y_INFO), uniqueVoxels[i].voxelPos(Z_INFO));
	//	for (int j=0; j<uniqueVoxels[i].setIndices.size(); j++)
	//	{
	//		printf(" %d ", uniqueVoxels[i].setIndices[j]);
	//	}
	//	printf("\n");
	//}

	///////////////////////////////////////////////////////////////////////
	// Sort the uniqueVoxels according to the number of its setIndices

	vector<float> setIndexNums;
	for (int i=0; i<uniqueVoxels.size(); i++)
	{
		float tempNum = (float)uniqueVoxels[i].setIndices.size();
		setIndexNums.push_back(tempNum);
	}
	vector<int> sortedIndices = BubbleSort(setIndexNums, false);
	vector<UniqueVoxel> sortedVoxels;
	for (int i=0; i<sortedIndices.size(); i++)
	{
		int voxelIndex = sortedIndices[i];
		UniqueVoxel tempVoxel = uniqueVoxels[voxelIndex];
		sortedVoxels.push_back(tempVoxel);
	}
	uniqueVoxels = sortedVoxels;

	//printf("\n\n=============Unique Voxels (After Sorting)===============\n\n");
	//for (int i=0; i<uniqueVoxels.size(); i++)
	//{
	//	printf("Voxel [%d %d %d]: ", uniqueVoxels[i].voxelPos(X_INFO), uniqueVoxels[i].voxelPos(Y_INFO), uniqueVoxels[i].voxelPos(Z_INFO));
	//	for (int j=0; j<uniqueVoxels[i].setIndices.size(); j++)
	//	{
	//		printf(" %d ", uniqueVoxels[i].setIndices[j]);
	//	}
	//	printf("\n");
	//}

	///////////////////////////////////////////////////////////////////////
	// Compute the contact voxels set (only contain one or two unique voxels)

	int solidSetNum = solidVoxelsSet.size();
	vector<int> fullIndices;
	for (int i=0; i<solidSetNum; i++)
		fullIndices.push_back(i);

	vector<Vector3i> contaVoxels;
	vector<vector<Vector3i>> contaVoxelsSet;

	for (int i=0; i<uniqueVoxels.size(); i++)
	{
		// Case 1: One contactVoxel set only contains one unique voxel
		if ( uniqueVoxels[i].setIndices.size() == solidSetNum )
		{
			contaVoxels.clear();
			contaVoxels.push_back(uniqueVoxels[i].voxelPos);
			contaVoxelsSet.push_back(contaVoxels);
		}

		// Case 2: One contactVoxel set contains two unique voxels
		else
		{
			if ( i < uniqueVoxels.size()-1 )
			{
				// Since we already sort the uniqueVoxels
				int currSetNum = uniqueVoxels[i].setIndices.size();
				int nextSetNum = uniqueVoxels[i+1].setIndices.size();
				if ( currSetNum+nextSetNum < solidSetNum )
					break;

				vector<int> missIndices;
				missIndices = CompareTwoSets(fullIndices, uniqueVoxels[i].setIndices);
				for (int j=i+1; j<uniqueVoxels.size(); j++)
				{
					if ( CheckSubset(uniqueVoxels[j].setIndices, missIndices))
					{
						contaVoxels.clear();
						contaVoxels.push_back(uniqueVoxels[i].voxelPos);
						contaVoxels.push_back(uniqueVoxels[j].voxelPos);
						contaVoxelsSet.push_back(contaVoxels);			
					}
				}
			}
		}
	}

	//printf("\n\n==================Contact Voxel Sets===================\n\n");
	//for (int i=0; i<contaVoxelsSet.size(); i++)
	//{
	//	printf("Set %d: ", i);
	//	for (int j=0; j<contaVoxelsSet[i].size(); j++)
	//	{
	//		printf(" [%d %d %d] ", contaVoxelsSet[i][j](X_INFO), contaVoxelsSet[i][j](Y_INFO), contaVoxelsSet[i][j](Z_INFO));
	//	}
	//	printf("\n");
	//}

	return contaVoxelsSet;
}


///////////////////////////////////////////////////////////////////////////////////////
// Function:  Find the values that inside setA but outside of setB
///////////////////////////////////////////////////////////////////////////////////////

vector<int> CompareTwoSets(vector<int> setA, vector<int> setB)
{
	vector<int> setC;
	for (int i=0; i<setA.size(); i++)
	{
		if ( std::find(setB.begin(), setB.end(), setA[i]) == setB.end() )
		{
			setC.push_back( setA[i] );
		}
	}

	return setC;
}


///////////////////////////////////////////////////////////////////////////////////////
// Function:  Check if setB is a subset of setA
///////////////////////////////////////////////////////////////////////////////////////

bool CheckSubset(vector<int> setA, vector<int> setB)
{
	if ( setA.size() < setB.size() )
		return false;

	bool isSubset = true;
	for (int i=0; i<setB.size(); i++)
	{
		if ( std::find(setA.begin(), setA.end(), setB[i]) == setA.end() )
		{
			isSubset = false;
			break;
		}
	}

	return isSubset;
}




///=========================================================================================///
///                                  Puzzle Voxel Related
///=========================================================================================///

//---------------------------------------------------
//  Voxel Operations
//---------------------------------------------------

bool CheckVoxelsConnectivity(vector<Vector3i> voxelPosList)
{
	// Build a voxel list according to their positions
	vector<Voxel*> voxelList;
	for (int i=0; i<voxelPosList.size(); i++)
	{
		Voxel *voxel = new Voxel();
		voxel->pos = voxelPosList[i];
		voxelList.push_back( voxel );
	}

	// Check the connectivity of the voxel list
	bool isConnected = CheckVoxelsConnectivity( voxelList );

	// Delete and clean the voxel list
	for (int i=0; i<voxelList.size(); i++)
		delete voxelList[i];
	voxelList.clear();

	//if( isConnected )
	//	printf("connected. \n");
	//else
	//	printf("disconnected. \n");

	return isConnected;
}

bool CheckVoxelsConnectivity(vector<Voxel*> inputVoxels)
{	
	if ( inputVoxels.size() == 0 )
	{
		//printf("Warning: The tested voxel list is empty! \n");
		return false;
	}
	else if( inputVoxels.size() == 1 )
	{
		//printf("Warning: The voxel list only contains one voxel! \n");
		return true;
	}
	else
	{
		vector<Voxel*> connectVoxels;
		BFSConnectedVoxels(inputVoxels, 0, connectVoxels);

		if( inputVoxels.size() == connectVoxels.size() )
			return true;
		else
			return false;
	}
}

void GroupConnectedVoxels(vector<Voxel*> inputVoxels, vector<vector<Voxel*>> &voxelGroups)
{
	while ( inputVoxels.size() > 0 )
	{
		// Find a group of voxels that are connected
		vector<Voxel*> connectVoxels;
		BFSConnectedVoxels(inputVoxels, 0, connectVoxels);

		// Remove the voxels in the group from the input voxel list
		for (int i=0; i<inputVoxels.size(); i++)
		{
			for (int j=0; j<connectVoxels.size(); j++)
			{
				if( inputVoxels[i]->pos == connectVoxels[j]->pos )
					inputVoxels.erase(inputVoxels.begin()+i);
			}
		}

		// Save the group of connected voxels
		voxelGroups.push_back(connectVoxels);
	}
}

void BFSConnectedVoxels(vector<Voxel*> inputVoxels, int sourceVoxelIndex, vector<Voxel*> &connectVoxles)
{
	int inputVoxelNum = inputVoxels.size();
	std::vector<Voxel*> bfsQueue;
	std::vector<bool> visited(inputVoxelNum, false);
	int connectedVoxelNum = 0;
	bool isVisitAllVoxels = false;

	// Find a root (i.e. the first element) for Breadth-First Search Traversal 
	Voxel *root;
	root = inputVoxels[sourceVoxelIndex];
	visited[sourceVoxelIndex] = true;
	connectedVoxelNum++;
	bfsQueue.push_back(root);

	// Start Breadth-First Search Traversal based on voxel position
	while( !bfsQueue.empty() )
	{
		Voxel *currVisit = bfsQueue[0];
		bfsQueue.erase( bfsQueue.begin() );
		Voxel *nextVisit;

		for (int i=0; i<6; i++)
		{
			int index = GetVoxelIndexInList(inputVoxels, currVisit->pos + neiborPos[i]);
			if( index != VOXEL_OUT_LIST )
			{
				nextVisit = inputVoxels[index];
				if( !visited[index] )
				{
					visited[index] = true;
					bfsQueue.push_back(nextVisit);
					connectedVoxelNum++;
				}
			}

			// Stop searching if all the voxels are visited/connected
			if( connectedVoxelNum == inputVoxelNum )
			{
				isVisitAllVoxels = true;
				break;
			}
		}

		if ( isVisitAllVoxels )
			break;
	}

	// Push back all the visited/connected voxels
	for (int i=0; i<visited.size(); i++)
	{
		if (visited[i])
		{
			connectVoxles.push_back(inputVoxels[i]);
		}
	}
}

bool BFSConnectedVoxels_DisconnectTest(vector<Voxel*> inputVoxels, int sourceVoxelIndex, Voxel * targetVoxel)
{
    int inputVoxelNum = inputVoxels.size();
    std::vector<Voxel*> bfsQueue;
    std::vector<bool> visited(inputVoxelNum, false);
    int connectedVoxelNum = 0;
    bool isVisitAllVoxels = false;

    // Find a root (i.e. the first element) for Breadth-First Search Traversal
    Voxel *root;
    root = inputVoxels[sourceVoxelIndex];
    visited[sourceVoxelIndex] = true;
    connectedVoxelNum++;
    bfsQueue.push_back(root);

    // Start Breadth-First Search Traversal based on voxel position
    while( !bfsQueue.empty() )
    {
        Voxel *currVisit = bfsQueue[0];
        bfsQueue.erase( bfsQueue.begin() );
        Voxel *nextVisit;

        for (int i=0; i<6; i++)
        {
            int index = GetVoxelIndexInList(inputVoxels, currVisit->pos + neiborPos[i]);
            if( index != VOXEL_OUT_LIST and currVisit->neiborVoxel[i] == NEIGHBOR_CONNECTED)
            {
                nextVisit = inputVoxels[index];
                if( !visited[index] )
                {
                    visited[index] = true;

                    if (inputVoxels[index]->pos == targetVoxel->pos)
                        return true;

                    bfsQueue.push_back(nextVisit);
                    connectedVoxelNum++;
                }
            }

            // Stop searching if all the voxels are visited/connected
            if( connectedVoxelNum == inputVoxelNum )
            {
                isVisitAllVoxels = true;
                break;
            }
        }

        if ( isVisitAllVoxels )
            break;
    }

    return false;
}

int GetVoxelIndexInList(vector<Voxel*> testVoxels, Vector3i targetVoxelPos)
{
	// Index = -1 means cannot find the target voxel in the tested voxel list
	int indexInList = VOXEL_OUT_LIST;
	int targetVoxelNum = 0;

	// Voxel search based on its position
	for (int i=0; i<testVoxels.size(); i++)
	{
		if(testVoxels[i]->pos == targetVoxelPos)
		{
			indexInList = i;
			targetVoxelNum++;
		}
	}

	// Warning info for debugging
	if ( targetVoxelNum > 1 )
	{
		printf("Warning: More than one target voxel exist in the tested voxel list! \n");
	}

	return indexInList;
}


//---------------------------------------------------
//  BSF Search in Given Voxel List
//---------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////
// Input:   (1) voxelList: the voxel space that includes srcVoxel and tagtVoxel (connected or disconnected)
//          (2) srcVoxelPos: the original position of the source voxel
//          (3) tagtVoxelPos: the original position of the target voxel
//
// Output:  (1) The shortest distance values between srcVoxel and other voxles in voxelList;
//          (2) Return a bool value to indicate whether srcVoxel and tagtVoxel can be linked.
//
// Note:    (1) Stop the BSF search once find the tagtVoxel;
//          (2) All the input voxel positions are in OrigVolume. 
///////////////////////////////////////////////////////////////////////////////////////

bool ComputeShortestDistance(vector<Voxel*> &voxelList, Vector3i srcVoxelPos, Vector3i tagtVoxelPos)
{
	// Get the source voxel index in the list
	int srcVoxelIndex = GetVoxelIndexInList(voxelList, srcVoxelPos);
	if ( srcVoxelIndex == VOXEL_OUT_LIST )
	{
		printf("Warning: The source voxel is out of the list! \n\n");
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	// Initialization of each voxel before BSF search
	vector<Voxel*> bfsQueue;
	for (int i=0; i<voxelList.size(); i++)
	{
		voxelList[i]->dist = MIN_INT;
		voxelList[i]->visited = false;
	}

	// Find a root for Breadth-First Search Traversal 
	Voxel *root;
	root = voxelList[srcVoxelIndex];
	root->dist = 0;
	root->visited = true;
	bfsQueue.push_back(root);

	// Start Breadth-First Search Traversal
	bool isFindTagtVoxel = false;
	while( !bfsQueue.empty() )
	{
		Voxel *currVisit = bfsQueue[0];
		bfsQueue.erase( bfsQueue.begin() );
		Voxel *nextVisit;

		for (int j=0; j<6; j++)
		{
			Vector3i neiborVoxelPos = currVisit->pos + neiborPos[j];
			int index = GetVoxelIndexInList(voxelList, neiborVoxelPos);
			if( index != VOXEL_OUT_LIST )
			{
				nextVisit = voxelList[index];
				if( !voxelList[index]->visited )
				{
					voxelList[index]->visited = true;
					bfsQueue.push_back(nextVisit);
					nextVisit->dist = currVisit->dist + 1;
				}

				if ( neiborVoxelPos == tagtVoxelPos )
				{
					isFindTagtVoxel = true;
					break;
				}
			}
		}

		if ( isFindTagtVoxel )
			break;
	}

	return isFindTagtVoxel;
}


///////////////////////////////////////////////////////////////////////////////////////
// Input:   (1) voxelList: the voxel space that includes srcVoxel and tagtVoxels (connected or disconnected)
//          (2) srcVoxelPos: the original position of the source voxel
//          (3) tagtVoxelPosList: the original positions of the target voxels (connected)
//          (4) isPushTagtVoxel: a bool value to indicate whether to push back the tagtVoxel into the pathVoxels
//
// Output:  (1) Return the voxels on the shortest path from tagtVoxels to srcVoxel.
//          (2) The returned voxels (vector) is empty if cannot find the shortest path
///////////////////////////////////////////////////////////////////////////////////////

vector<Vector3i> ComputeShortestPath(vector<Voxel*> &voxelList, Vector3i srcVoxelPos, vector<Vector3i> tagtVoxelPosList, bool isPushTagtVoxel)
{
	Vector3i linkTagtVoxelPos;
	bool isFindTagtVoxel = ComputeShortestDistance(voxelList, linkTagtVoxelPos, srcVoxelPos, tagtVoxelPosList);

	vector<Vector3i> pathVoxels;
	if ( isFindTagtVoxel )
	{
		pathVoxels = ComputeShortestPathVoxels(voxelList, linkTagtVoxelPos, isPushTagtVoxel);
	}

	//CleanVolumeVoxels(voxelList);

	return pathVoxels;
}



///////////////////////////////////////////////////////////////////////////////////////
// Input:   (1) voxelList: the voxel space that includes srcVoxel and tagtVoxel (connected or disconnected)
//          (2) srcVoxelPos: the original position of the source voxel
//          (3) tagtVoxelPosList: the original positions of the target voxels (connected)
//
// Output:  (1) The shortest distance values between srcVoxel and other voxles in voxelList;
//          (2) One tagtVoxel (i.e. the linkTagtVoxel) that is closest to the srcVoxel
//          (3) Return a bool value to indicate whether srcVoxel and tagtVoxels can be linked
//
// Note:    (1) Stop the BSF search once find one voxel in tagtVoxelList (i.e., the linkTagtVoxel);
//          (2) All the input voxel positions are in OrigVolume. 
///////////////////////////////////////////////////////////////////////////////////////

bool ComputeShortestDistance(vector<Voxel*> &voxelList, Vector3i &linkTagtVoxelPos, Vector3i srcVoxelPos, vector<Vector3i> tagtVoxelPosList)
{
	// Get the source voxel index in the list
	int srcVoxelIndex = GetVoxelIndexInList(voxelList, srcVoxelPos);
	if ( srcVoxelIndex == VOXEL_OUT_LIST )
	{
		printf("Warning: The source voxel [%d %d %d] is out of the list! \n\n", srcVoxelPos(X_INFO), srcVoxelPos(Y_INFO), srcVoxelPos(Z_INFO));
		return false;
	}

	////////////////////////////////////////////////////////////////////////////////
	// Initialization of each voxel before BSF search
	vector<Voxel*> bfsQueue;
	for (int i=0; i<voxelList.size(); i++)
	{
		voxelList[i]->dist = MIN_INT;
		voxelList[i]->visited = false;
	}

	// Find a root for Breadth-First Search Traversal 
	Voxel *root;
	root = voxelList[srcVoxelIndex];
	root->dist = 0;
	root->visited = true;
	bfsQueue.push_back(root);

	// Start Breadth-First Search Traversal
	bool isFindTagtVoxel = false;
	while( !bfsQueue.empty() )
	{
		Voxel *currVisit = bfsQueue[0];
		bfsQueue.erase( bfsQueue.begin() );
		Voxel *nextVisit;

		for (int j=0; j<6; j++)
		{
			Vector3i neiborVoxelPos = currVisit->pos + neiborPos[j];
			int index = GetVoxelIndexInList(voxelList, neiborVoxelPos);
			if( index != VOXEL_OUT_LIST and currVisit->neiborVoxel[j] == NEIGHBOR_CONNECTED )
			{
				nextVisit = voxelList[index];
				if( !voxelList[index]->visited )
				{
					voxelList[index]->visited = true;
					bfsQueue.push_back(nextVisit);
					nextVisit->dist = currVisit->dist + 1;
				}

				//if ( neiborVoxelPos == tagtVoxelPos )
				if( std::find(tagtVoxelPosList.begin(), tagtVoxelPosList.end(), neiborVoxelPos) != tagtVoxelPosList.end() )
				{
					isFindTagtVoxel = true;
					linkTagtVoxelPos = neiborVoxelPos;
					break;
				}
			}
		}

		if ( isFindTagtVoxel )
			break;
	}

	return isFindTagtVoxel;
}


///////////////////////////////////////////////////////////////////////////////////////
// Input:   (1) voxelList: the voxel space that includes tagtVoxel (connected or disconnected)
//          (2) tagtVoxelPos: the original positions of the tagtVoxel or the linkTagtVoxel
//          (3) isPushTagtVoxel: a bool value to indicate whether to push back the tagtVoxel into the pathVoxels
//
// Output:  (1) Clean the distance value for all the voxels in voxelList;
//          (2) Return the voxels on the shortest path from tagtVoxel to srcVoxel.
//
// Note:    (1) Need to call ComputeShortestDistance(..) first and make sure it return true;
//          (2) All the input voxel positions are in OrigVolume. 
/////////////////////////////////////////////////////////////////////////////////////// 

vector<Vector3i> ComputeShortestPathVoxels(vector<Voxel*> &voxelList, Vector3i tagtVoxelPos, bool isPushTagtVoxel)
{
	vector<Vector3i> pathVoxels; 

	// Get the target voxel index in the list
	int tagtVoxelIndex = GetVoxelIndexInList(voxelList, tagtVoxelPos);
	if ( tagtVoxelIndex == VOXEL_OUT_LIST )
	{
		printf("Warning: The target voxel is out of the list! \n\n");
		return pathVoxels;
	}

	if ( isPushTagtVoxel )
		pathVoxels.push_back(tagtVoxelPos);

	Voxel *currVoxel = voxelList[tagtVoxelIndex];
	while ( true )
	{
		Vector3i currVoxelPos = currVoxel->pos;
		int currDist = currVoxel->dist;
        int currVoxelIndex = GetVoxelIndexInList(voxelList, currVoxelPos);

		// Stop searching once reach the source voxel
		if ( currDist == 0 )
			break;

		// Find all the neighbor voxel whose distance value is (currDist-1)
		vector<Voxel*> nextVoxels;
		for (int i=0; i<6; i++)
		{
			Vector3i neiborVoxelPos = currVoxel->pos + neiborPos[i];
			int index = GetVoxelIndexInList(voxelList, neiborVoxelPos);

			// Here we consider the connectivity constraints
			if( index != VOXEL_OUT_LIST && voxelList[index]->dist == currDist - 1 and currVoxel->neiborVoxel[i] == NEIGHBOR_CONNECTED)
			{
//                if ( currTempVoxel->neiborVoxel[i] == NEIGHBOR_CONNECTED)
				    nextVoxels.push_back(voxelList[index]);
			}

		}

		// Sort these voxels according to their reachability value
		vector<float> nextPossibs;
		for (int i=0; i<nextVoxels.size(); i++)
		{
			float reachValue = MAX_VOXEL_REACH - nextVoxels[i]->reach;
			nextPossibs.push_back(reachValue);
		}

		// Select the voxel with smallest reachability value
		//vector<int> nextIndices = BubbleSort(nextPossibs, true);
		//int voxelIndex = nextIndices[0];

		// Randomly select the voxel based on its reachability value (prefer small one)
		int voxelIndex = GetRandomObjIndex(nextPossibs, 2);

		currVoxel = nextVoxels[voxelIndex];
		pathVoxels.push_back(currVoxel->pos);   
	}

	// Clean the properties of the voxels in the list
	for (int i=0; i<voxelList.size(); i++)
	{
		voxelList[i]->dist = MIN_INT;
		voxelList[i]->visited = false;
	}

	return pathVoxels;
}


//-----------------------------------------------------------------------------------------
//  BSF Search in Given Voxel List (Compute the path with the minimum reachability value)
//-----------------------------------------------------------------------------------------



///=========================================================================================///
///                                  Puzzle Piece Related
///=========================================================================================///

//---------------------------------------------------
// Piece Moving Axis
//---------------------------------------------------

int GetMoveAxisID(Vector3i moveVec)
{
	//{"-x", "+x", "-y", "+y", "-z", "+z"};

	if ( moveVec(X_INFO) <  0 && moveVec(Y_INFO) == 0 && moveVec(Z_INFO) == 0)		return 0;
	else if ( moveVec(X_INFO) >  0 && moveVec(Y_INFO) == 0 && moveVec(Z_INFO) == 0)   return 1;
	else if ( moveVec(X_INFO) == 0 && moveVec(Y_INFO) <  0 && moveVec(Z_INFO) == 0)   return 2;
	else if ( moveVec(X_INFO) == 0 && moveVec(Y_INFO) >  0 && moveVec(Z_INFO) == 0)   return 3;
	else if ( moveVec(X_INFO) == 0 && moveVec(Y_INFO) == 0 && moveVec(Z_INFO) <  0)   return 4;
	else if ( moveVec(X_INFO) == 0 && moveVec(Y_INFO) == 0 && moveVec(Z_INFO) >  0)   return 5;
	else															return -1;
}

int GetReverseAxisID(int axisID)
{
	int revsAxisID;

	int axisSign = axisID%2;
	if (axisSign == 0)  revsAxisID = axisID+1;
	else                revsAxisID = axisID-1;

	//printf("ReverseID: %d \n", revsAxisID);
	return revsAxisID;
}

vector<int> GetPerpAxisIDs(int axisID)
{
	int revsAxisID = GetReverseAxisID( axisID );

	vector<int> perpAxisIDs;
	for (int i=0; i<6; i++)
	{
		if ( i != axisID && i!= revsAxisID )
			perpAxisIDs.push_back( i );
	}

	return perpAxisIDs;
}

vector<int> GetRemainMoveAxisIDs(vector<int> moveAxisIDs)
{
	vector<int> remainAxisIDs;

	// Test whether the prevPiece with moveAxisIDs can be a key piece
	if( !MovableAxesTest(moveAxisIDs))
	{
		printf("Warning: The prevPiece cannot be a key piece! \n\n");
		return remainAxisIDs;
	}

	// Compute the axisIDs of currPiece that should be removed
	vector<int> removeAxisIDs;
	for (int i=0; i<moveAxisIDs.size(); i++)
		removeAxisIDs.push_back( moveAxisIDs[i] );

	for (int i=0; i<moveAxisIDs.size(); i++)
	{
		int revsAxisID = GetReverseAxisID( moveAxisIDs[i] );
		if ( std::find(removeAxisIDs.begin(), removeAxisIDs.end(), revsAxisID) == removeAxisIDs.end() )
			removeAxisIDs.push_back(revsAxisID);
	}

	// Compute the remaining axisIDs of currPiece
	for (int i=0; i<6; i++)
	{
		if ( std::find(removeAxisIDs.begin(), removeAxisIDs.end(), i) == removeAxisIDs.end() )
			remainAxisIDs.push_back(i);
	}

	//printf("RemainMoveAxis: ");
	//for (int i=0; i<remainAxisIDs.size(); i++)
	//	printf(" %d ", remainAxisIDs[i]);
	//printf("\n");

	return remainAxisIDs;
}

bool MovableAxesTest(vector<int> movableAxes)
{
	int movableAxesNum = movableAxes.size();

	// The tested piece can be a key 
	if( movableAxesNum>0 && movableAxesNum<3 )
	{
		return true;
	}
	if( movableAxesNum == 3 )
	{
		if( (std::find(movableAxes.begin(), movableAxes.end(), 0) !=  movableAxes.end() &&
			std::find(movableAxes.begin(), movableAxes.end(), 1) !=  movableAxes.end()) ||

			(std::find(movableAxes.begin(), movableAxes.end(), 2) !=  movableAxes.end() &&
			std::find(movableAxes.begin(), movableAxes.end(), 3) !=  movableAxes.end()) ||

			(std::find(movableAxes.begin(), movableAxes.end(), 4) !=  movableAxes.end() &&
			std::find(movableAxes.begin(), movableAxes.end(), 5) !=  movableAxes.end()))
		{
			return true;
		}
	}

	//printf("AxesNum: %d \n", movableAxesNum);
	//for (int i=0; i<movableAxes.size(); i++)
	//	printf(" %s", axisArray[movableAxes[i]]);
	//printf("\n\n");

	// The tested piece cannot be a key
	return false;
}


//---------------------------------------------------
// Piece and Piece Group
//---------------------------------------------------

vector<int> GetPieceVoxelNum(int pieceNum, int volVoxelNum, float voxelNumVar, float variance)
{
	float avgVoxelNum = volVoxelNum / (float)pieceNum;
	int minVoxelNum = floor( (1-voxelNumVar)*avgVoxelNum );
	int maxVoxelNum =  ceil( (1+voxelNumVar)*avgVoxelNum );
	float voxelNumStep = (maxVoxelNum-minVoxelNum)/(pieceNum-1.0);
	//printf("Min: %d  Max: %d \n", minVoxelNum, maxVoxelNum);

	// Pass 1: calculate rough piece voxel number
	int pieceVoxelSum = minVoxelNum;
	vector<int> pieceVoxelNums;
	pieceVoxelNums.push_back( minVoxelNum );
	for (int i=1; i<pieceNum; i++)
	{
		int voxelNum = floor( minVoxelNum + i*voxelNumStep +0.5);
		if ( voxelNum > maxVoxelNum )
			voxelNum = maxVoxelNum;

		pieceVoxelNums.push_back(voxelNum);
		pieceVoxelSum += voxelNum;
	}

	// Pass 2: reduce voxelNum for the first few pieces
	if ( pieceVoxelSum > volVoxelNum )
	{
		int voxelNumDiff = pieceVoxelSum - volVoxelNum;
		int reducePieceNum = 0;
		for (int i=0; i<pieceVoxelNums.size(); i++)
		{
			if ( pieceVoxelNums[i] > minVoxelNum )
			{
				pieceVoxelNums[i] -= 1;
				reducePieceNum++;
			}

			if ( reducePieceNum == voxelNumDiff )
				break;
		}
	}
	// Pass 2: increase voxelNum for the last few pieces
	else if ( pieceVoxelSum < volVoxelNum )
	{
		int voxelNumDiff = volVoxelNum - pieceVoxelSum;
		int increasePieceNum = 0;
		for (int i=pieceVoxelNums.size()-1; i>=0; i--)
		{
			if ( pieceVoxelNums[i] < maxVoxelNum )
			{
				pieceVoxelNums[i] += 1;
				increasePieceNum++;
			}

			if ( increasePieceNum == voxelNumDiff )
				break;
		}
	}

	int varianceVoxelNum = avgVoxelNum * variance;

	for (int i = 0; i < pieceVoxelNums.size() - 1; ++i)
    {
        pieceVoxelNums[i] -= varianceVoxelNum;
        pieceVoxelNums[pieceVoxelNums.size() - 1] += varianceVoxelNum;
    }

	//int totalVoxelNum = 0;
	//for (int i=0; i<pieceVoxelNums.size(); i++)
	//{
	//	totalVoxelNum += pieceVoxelNums[i];
	//	printf(" i=%d  voxelNum: %d \n", i, pieceVoxelNums[i]);
	//}
	//printf("VoxelNum: %d \n", totalVoxelNum);

	return pieceVoxelNums;
}

int GetPieceIndexInList(vector<int> testPieceIDList, int targetPieceID)
{
	// Index = -1 means cannot find the target voxel in the tested voxel list
	int indexInList = PIECE_OUT_LIST;
	int targetPieceNum = 0;

	// Voxel search based on its position
	for (int i=0; i<testPieceIDList.size(); i++)
	{
		if(testPieceIDList[i] == targetPieceID)
		{
			indexInList = i;
			targetPieceNum++;
		}
	}

	// Warning info for debugging
	if ( targetPieceNum > 1 )
	{
		printf("Warning: More than one target pieceID exist in the tested pieceID list! \n");
	}
	return indexInList;
}

int GetPieceCombination(int pieceNum, int decmialValue, vector<bool> &binaryValue, int disassMode)
{
	int halfPieceNum = floor(pieceNum/2.0);

	/////////////////////////////////////////////////////////////
	// Compute corresponding combination (i.e. the binary value)
	int n = decmialValue;
	int k=0;
	int trueCounter = 0;
	while (n != 0 )
	{
		bool flag = bool(n%2);
		if ( flag ) trueCounter++;
		binaryValue[k] = flag;
		n = n/2;
		k++;
	}

	// Reverse the combination if more than K/2 pieces are selected
	if ( disassMode == DISASS_MOVE_SMALL_GROUP )
	{
		if ( trueCounter > halfPieceNum )
		{
			for (int i=0; i<binaryValue.size(); i++)
			{
				binaryValue[i] = !binaryValue[i];
			}
			trueCounter = pieceNum - trueCounter;
		}
	}

	else if ( disassMode == DISASS_FIX_LAST_PIECE )
	{
		if ( binaryValue[pieceNum-1] == 1 )
		{
			for (int i=0; i<binaryValue.size(); i++)
			{
				binaryValue[i] = !binaryValue[i];
			}
			trueCounter = pieceNum - trueCounter;
		}
	}

	return trueCounter;
}


//---------------------------------------------------
// Piece Material
//---------------------------------------------------

Vector3f GenerateRandomMTL(Vector3f existColors[10], int colorNum)
{
	const float colorDistThres = 0.25;
	const float colorSatuThres = 0.80;

	while( true ) 
	{
		Vector3f randColor;
		randColor(X_INFO) = rand()/(RAND_MAX+1.0);
		randColor(Y_INFO) = rand()/(RAND_MAX+1.0);
		randColor(Z_INFO) = rand()/(RAND_MAX+1.0);

		float maxValue = _MAX(randColor(X_INFO), _MAX(randColor(Y_INFO), randColor(Z_INFO)));
		float minValue = _MIN(randColor(X_INFO), _MIN(randColor(Y_INFO), randColor(Z_INFO)));
		float saturation = (maxValue-minValue) / maxValue;

		float minColorDist = GetMinColorDistance(existColors, colorNum, randColor);	

		if ( minColorDist > colorDistThres && 
			saturation   < colorSatuThres )
		{
			return randColor;
		}
	}
}

float GetMinColorDistance(Vector3f existColors[10], int colorNum, Vector3f randColor)
{
	float minColorDist = MAX_FLOAT;

	for (int i=0; i<colorNum; i++)
	{
		//float tempDist = dist(existColors[i], randColor);
		float tempDist = (existColors[i] - randColor).norm();
		if ( tempDist < minColorDist)
		{
			minColorDist = tempDist;
		}
	}

	return minColorDist;
}




///=========================================================================================///
///                                 Vector, Matrix and Array
///=========================================================================================///

void PrintMatrix(double matrix[])
{
	for (int i=0; i<16; i++)
	{
		printf("%.1f ", matrix[i]);
		if( (i+1)%4 == 0 )
			printf("\n");
	}
	printf("\n");	
}

vector<int> BubbleSort(vector<float> &Array, bool isAscend)
{
	vector<int> Indices;
	for (int i=0; i<Array.size(); i++)
		Indices.push_back(i);

	//printf("Before Sorting: ");
	//for (int i=0; i<Array.size(); i++)
	//	printf(" %d: %.2f ", Indices[i], Array[i]);
	//printf("\n");

	int i, j, flag = 1; // Set flag to 1 to start first pass
	float tempValue;    // Holding variable
	int tempIndex;      // Holding variable index 
	int num = Array.size(); 
	for(i = 1; (i <= num) && flag; i++)
	{
		flag = 0;
		for (j=0; j < (num -1); j++)
		{
			if  ( ( isAscend && Array[j+1] < Array[j]) ||
				(!isAscend && Array[j+1] > Array[j]) )
			{ 
				// Swap the values in the array
				tempValue = Array[j];   
				Array[j] = Array[j+1];
				Array[j+1] = tempValue;

				// Swap the index of these two values
				tempIndex = Indices[j];
				Indices[j] = Indices[j+1];
				Indices[j+1] = tempIndex;

				flag = 1;              
			}
		}
	}

	//printf("After Sorting:  ");
	//for (int i=0; i<Array.size(); i++)
	//	printf(" %d: %.2f ", Indices[i], Array[i]);
	//printf("\n");

	return Indices;
}




///=========================================================================================///
///                                      Random Stuff
///=========================================================================================///

vector<int> GetRandomObjIndexList(vector<float> possibList, float alpha, int objNum)
{
	vector<int> objIndexList;
	if ( objNum > possibList.size() || objNum <= 0 )
	{
		printf("Warning: The input objNum is not correct %d ! \n\n", objNum);
		return objIndexList;
	}

	while( objIndexList.size() < objNum )
	{
		int tempIndex = GetRandomObjIndex(possibList, alpha);
		if ( std::find(objIndexList.begin(), objIndexList.end(), tempIndex) == objIndexList.end() )
		{
			objIndexList.push_back(tempIndex);
		}
	}

	return objIndexList;
}


// Input:  the selection possibility value of each object
// Output: randomly selected object index
int GetRandomObjIndex(vector<float> possibList, float alpha)
{
	if ( possibList.size() == 0)
		return -1;

	if ( possibList.size() == 1)
		return 0;

	vector<float> possibMapList = PossibExpMapping(possibList, alpha);

	// Compute possibility regions for objects with possibility value [P0, P1, P2, ..., P(k-1), Pk]
	// which is [P0, P0+P1, P0+P1+P2, ..., P0+P1+..+P(k-1), P0+P1+..+P(k-1)+Pk]
	vector<float> possibRegions;
	for (int i=0; i<possibMapList.size(); i++)
	{
		float possibSum = 0;
		for (int j=0; j<=i; j++)
		{
			possibSum += possibMapList[j];
		}
		possibRegions.push_back(possibSum);
	}

	// Generate a random value in range [0, P0+P1+..+P(k-1)+Pk)
	int lastObjIndex = possibMapList.size() - 1;
	float randValue = (rand()/(RAND_MAX+1.0)) * possibRegions[lastObjIndex];

	// Return object index by finding which region the random value falls into
	for (int i=0; i<possibRegions.size(); i++)
	{
		// Find each object's possibility range
		float regionMinValue, regionMaxValue;
		if ( i == 0 ) 
		{
			regionMinValue = 0;
			regionMaxValue = possibRegions[0];
		}
		else           
		{
			regionMinValue = possibRegions[i-1]; 
			regionMaxValue = possibRegions[i];
		}

		// Return the randomly selected object index
		if ( randValue >= regionMinValue &&
			 randValue <= regionMaxValue )
		{
			return i;
		}
	}

	printf("Warning: the return random value may not be correct. \n");

	return 0;
}


vector<float> PossibExpMapping(vector<float> possibList, float alpha)
{
	// Check if the input possibility values are correct
	for (int i=0; i<possibList.size(); i++)
	{
		if ( possibList[i] < 0 || possibList[i] > MAX_INT )
		{
			printf("Warning: The input possibility values [i=%2d  P=%.2f] are not correct! \n\n", i, possibList[i]);
		}
	}

	// Possibility value exponential mapping 
	vector<float> possibMapList;
	for (int i=0; i<possibList.size(); i++)
	{
		float tempPossib = pow(possibList[i], alpha);
		possibMapList.push_back(tempPossib);
		//printf("i=%d  P1 %.2f  P2 %.2f \n", i, possibList[i], possibMapList[i]);
	}

	// Calculate the sum of all the possibility values in each list
	//float totalPossib1 = 0;
	//float totalPossib2 = 0;
	//for (int i=0; i<possibList.size(); i++)
	//{
	//	totalPossib1 += possibList[i];
	//	totalPossib2 += possibMapList[i];
	//}
	////printf("Total Possib 1: %.2f \n", totalPossib1);
	////printf("Total Possib 2: %.2f \n", totalPossib2);

	//// Normalize the possibility values in each list
	//for (int i=0; i<possibList.size(); i++)
	//{
	//	possibList[i]    /= totalPossib1;
	//	possibMapList[i] /= totalPossib2;
	//	//printf("i=%d  P1 %.2f  P2 %.2f \n", i, possibList[i], possibMapList[i]);
	//}

	return possibMapList;
}


// Return a float value in [0 1)
float GetRandomNumber(int seedIndex)
{
	if ( seedIndex < 1 )
		printf("Warning: seedIndex cannot be smaller than 1! \n\n");

	float randValue = seedIndex * rand()/(RAND_MAX+1.0);

	if( randValue > 1.0 )
		randValue = randValue - floor(randValue);
	else if( randValue == 1.0 )
		randValue = 0.999999;

	return randValue;
}