///////////////////////////////////////////////////////////////
//
// Helper.h
//
//   Utility Tool Functions
//
// by Peng Song
//
// 27/Aug/2021
//
///////////////////////////////////////////////////////////////

#ifndef _HELP_PUZ_H
#define _HELP_PUZ_H

#include <Eigen/Eigen>
#include <vector>
#include <GLFW/glfw3.h>
#include "igl/igl_inline.h"

using namespace std;
using namespace Eigen;

///////////////////////////////////////////////////////////////
// Define Variables
///////////////////////////////////////////////////////////////

//#define TRIANGLE_PIECE_OBJ

//#define COMPUTE_KERNAL_GRAPH_ONLY

//#define SHOW_INFO

//#define ANTO_SAVE

#define DEBUG_CHECK_REMV_AXIS
// Check remv axis rather than motion space before creating block path

//#define DEBUG_CHECK_BLOCK_VOXEL_REMV
// Check if the candidate is a real blockVoxel in all the previous PuzConfigs
// note: the path should be still movable along pieceAxisID in tagtPuzConfig
// and maybe the path can be moved but cannot be removed in prev Config

//#define DEBUG_INTERNAL_BLOCK_PATH
// Select the block path with high avg reachability value.

//#define DEBUG_BLOCK_VOXEL_NEAR_BY_EMPTY_VOXEL
// Prefer to select the block voxel near by empty voxels

//#define PRINT_DEBUG_MESSAGE
//#define DEBUG_PUZZLE

// Voxel Type for Piece Construction
#define  VOXEL_TYPE_UNKOWN         -1
#define  VOXEL_TYPE_REST            0
#define  VOXEL_TYPE_AVOID           1
#define  VOXEL_TYPE_EXTEND          2
#define  VOXEL_TYPE_REMOVE          3

// Voxel State
#define  VOXEL_OUT_EXP_BBOX        -1
#define  VOXEL_IN_EXP_BBOX          0

#define  VOXEL_OUT_BBOX            -1
#define  VOXEL_OUT_VOLUME           0
#define  VOXEL_ON_VOLUME            1

// Puzzle Initialization State
#define  PUZZLE_INIT_NONE          -1
#define  PUZZLE_INIT_VOLUME         0
#define  PUZZLE_INIT_PIECE          1
#define  PUZZLE_INIT_ACTION         2

// Puzzle Lock State
#define  PUZZLE_LOCK_UNKNOWN       -1
#define  PUZZLE_GROUP_MOVE          0 
#define  PUZZLE_PIECE_MOVE          1
#define  PUZZLE_DEAD_LOCK           2
#define  PUZZLE_INTER_LOCK          3

// Puzzle Buildable State
#define  PUZZLE_BUILD_UNKNOWN      -1
#define  PUZZLE_NOT_BUILDABLE       0
#define  PUZZLE_NOT_BUILD_GROUP     1
#define  PUZZLE_NO_REMOVE_GROUP     2
#define  PUZZLE_NORMAL_BUILDABLE    3
#define  PUZZLE_STRICT_BUILDABLE    4

// Voxel Neighbor Position
#define  DIR_NEGATIVE_X       Vector3i(-1,  0,  0)
#define  DIR_POSITIVE_X       Vector3i( 1,  0,  0)
#define  DIR_NEGATIVE_Y       Vector3i( 0, -1,  0)
#define  DIR_POSITIVE_Y       Vector3i( 0,  1,  0)
#define  DIR_NEGATIVE_Z       Vector3i( 0,  0, -1)
#define  DIR_POSITIVE_Z       Vector3i( 0,  0,  1)

// Voxel does not belong to any piece
#define  NONE_PIECE            -1

// Voxel Type
#define NEIGHBOR_NONE_CONNECTED          0
#define NEIGHBOR_CONNECTED               1
#define NEIGHBOR_NONE_PIECE             -1
#define NEIGHBOR_NONE_AVAILABLE         -2

// Cannot find voxel in a voxel list
#define  VOXEL_OUT_LIST        -1
#define  PIECE_OUT_LIST        -1

// Max and min integer/float
#define  MIN_INT          -10000000
#define  MAX_INT           10000000
#define  MIN_FLOAT        -10000000.0
#define  MAX_FLOAT         10000000.0

// Max voxel reachability value
#define MAX_VOXEL_REACH    11

// Group disassembly mode
#define DISASS_MOVE_SMALL_GROUP   1
#define DISASS_FIX_LAST_PIECE     2

// X Y Z Axis
#define X_INFO         0
#define Y_INFO         1
#define Z_INFO         2


// Puzzle Debug Info
#define CONTA_VOXEL   -1
#define SEED_VOXEL    -2
#define SEED_KEPT     -3
#define SEED_PATH     -4
#define BLOCK_VOXEL   -5
#define BLOCK_KEPT    -6
#define BLOCK_PATH    -7
#define EXTD_VOXEL    -8



///////////////////////////////////////////////////////////////
// Function Declaration
///////////////////////////////////////////////////////////////

class Voxel;

/////////////////////////////////////////////////////////
// (1) High-Level Puzzle Related

vector<vector<Vector3i>> ComputeContactVoxelsSet(vector<vector<Vector3i>> solidVoxelsSet);
vector<int> CompareTwoSets(vector<int> fullSet, vector<int> subSet);
bool CheckSubset(vector<int> setA, vector<int> setB);

/////////////////////////////////////////////////////////
// (2) Puzzle Voxel Related

// Voxel Operations
bool CheckVoxelsConnectivity(vector<Vector3i> voxelPosList);
bool CheckVoxelsConnectivity(vector<Voxel*> inputVoxels);
void GroupConnectedVoxels(vector<Voxel*> inputVoxels, vector<vector<Voxel*>> &voxelGroups);
void BFSConnectedVoxels(vector<Voxel*> inputVoxels,  int sourceVoxelIndex, vector<Voxel*> &connectVoxles);
bool BFSConnectedVoxels_DisconnectTest(vector<Voxel*> inputVoxels,  int sourceVoxelIndex, Voxel* targetVoxel);
int GetVoxelIndexInList(vector<Voxel*> testVoxels, Vector3i targetVoxelPos);



// BSF Search in Given Voxel List
bool ComputeShortestDistance(vector<Voxel*> &voxelList, Vector3i srcVoxelPos, Vector3i tagtVoxelPos);
vector<Vector3i> ComputeShortestPath(vector<Voxel*> &voxelList, Vector3i srcVoxelPos, vector<Vector3i> tagtVoxelPosList, bool isPushTagtVoxel);
bool ComputeShortestDistance(vector<Voxel*> &voxelList, Vector3i &linkTagtVoxelPos, Vector3i srcVoxelPos, vector<Vector3i> tagtVoxelPosList);
vector<Vector3i> ComputeShortestPathVoxels(vector<Voxel*> &voxelList, Vector3i tagtVoxelPos, bool isPushTagtVoxel);


/////////////////////////////////////////////////////////
// (3) Puzzle Piece Related

// Piece Moving Axis
int GetMoveAxisID(Vector3i moveVec);
int GetReverseAxisID(int axisID);
vector<int> GetPerpAxisIDs(int axisID);
vector<int> GetRemainMoveAxisIDs(vector<int> moveAxisIDs);
bool MovableAxesTest(vector<int> movableAxes);

// Piece and Piece Group
vector<int> GetPieceVoxelNum(int pieceNum, int volVoxelNum, float voxelNumVar, float varience);
int GetPieceIndexInList(vector<int> testPieceIDList, int targetPieceID);
int GetPieceCombination(int pieceNum, int decmialValue, vector<bool> &binaryValue, int disassMode);

// Piece Material
Vector3f GenerateRandomMTL(Vector3f existColors[10], int colorNum);
float GetMinColorDistance(Vector3f existColors[10], int colorNum, Vector3f randColor);

/////////////////////////////////////////////////////////
// (4) Linear Algebra Calculation
// Vector, Matrix and Array

void PrintMatrix(double matrix[]);
vector<int> BubbleSort(vector<float> &Array, bool isAscend);

// Random Stuff 
vector<int> GetRandomObjIndexList(vector<float> possibList, float alpha, int objNum);
int GetRandomObjIndex(vector<float> possibList, float alpha);
vector<float> PossibExpMapping(vector<float> possibList, float alpha);
float GetRandomNumber(int seedIndex);

#endif