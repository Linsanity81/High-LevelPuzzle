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

#ifndef _EXP_VOLUME_H
#define _EXP_VOLUME_H

#define  ORIG_VOLUME   0
#define  EXPA_VOLUME   1

class BoundingBox; 
class Voxel;
class Piece;
class PieceGroup;
class PuzConfig;


class ExpVolume
{
public:
    BoundingBox *expBBox;           // Expanded volume bounding box
    Voxel *outExpBBoxVoxel;         // One voxel out of expanded volume bounding box

	Vector3i volumeSize;            // Volume size [W H D] 
	Vector3f voxelSize;             // Voxel size

	Vector3i expVolumeSize;         // Expanded volume size [3*W 3*H 3*D]
    vector<Voxel*> expVoxelGrid;    // Volume voxel array (size: 3W*3H*3D)

    int expVolumeSizeScaler;

public:
    ExpVolume();
	~ExpVolume();
	void ClearExpVolume();

    void InitExpVolume(vector<Piece*> puzPieces, Vector3i puzVolumeSize, bool isCopyReachValue);
	void PrintExpVolume();

    int GetVolumeAxisSize(int axisID);
	int GetExtremeAxisPos(int axisID);
    int GetVoxelAxisPos(Vector3i voxelPos, int axisID);

	/// Volume Get Operations
	Voxel* GetExpVolumeVoxel(Vector3i voxelPos, int volumeType);
    Voxel* GetExpVolumeVoxel_new(Vector3i voxelPos, int volumeType);
	int GetExpVolumeVoxelIndex(Vector3i voxelPos, int volumeType);
	int GetNeighborVoxelNum(Vector3i voxelPos, int volumeType, int pieceID);

    /// Volume Set Operations
    void SetExoVolumeVoxelPieceID(Vector3i voxelPos, int volumeType, const int pieceID);
    void MarkExpVolumeVoxels(PieceGroup* pieceGroup, bool markValue);

    /// Volume Voxel Conversion
    vector<Vector3i> Exp2OrgVoxels(vector<Vector3i> expVoxels);
    vector<Vector3i> Org2ExpVoxels(vector<Vector3i> orgVoxels);
    Vector3i Exp2OrgVoxel(Vector3i expVoxelPos);
    Vector3i Org2ExpVoxel(Vector3i orgVoxelPos);

	/// Inside/outside Volume
    bool ConfigInsideExpVolume(PuzConfig *puzConfig, vector<Piece*> pieceList);
    bool VoxelInsideExpVolume(Vector3i voxelPos, int volumeType);
    bool VoxelInsideOrgVolume(Vector3i voxelPos, int volumeType);
    bool VoxelOnPuzzleSurface(Vector3i voxelPos);

	/// Volume Contact Operations
    void BuildConfigContactGraph(PuzConfig *puzConfig, vector<Piece*> pieceList);
    void ComputeVoxelContactPiece(PuzConfig *puzConfig, vector<Piece*> pieceList);
	void GetExpVoxelContactPiece(Vector3i expVoxelPos, int neiborPieceID[6]);
    void UpdateExpVolumeShape(PuzConfig *puzConfig, vector<Piece*> pieceList);
	void ResetExpVolumeShape();
    void UpdatePieceInExpVolume(Piece *piece, Vector3i piecePos);

    /// Computation Operations
    vector<Vector3i> ComputeEmptyVoxels(vector<Piece*> pieceList);
    int GetVoxelDistToPieceSurface(Vector3i voxelOrgPos, int pieceID, int distAxisID);
    int GetVoxelMoveSteps(Vector3i voxelExpPos, int pieceAxisID);
    vector<Vector3i> GetLinkedVoxels(Vector3i startVoxelExpPos, int pieceID, int linkAxisID, bool isIncludeStartVoxel);

    /// Check Motion of Voxel Groups
    vector<int> CheckSeedPathMotion(int seedAxisID, vector<Vector3i> seedPathVoxels);
    vector<int> CheckSeedPathMotionInConfig(PuzConfig *prevPuzConfig, vector<Piece*> pieceList, vector<Vector3i> seedPathVoxels);
    vector<int> CheckSeedPathRemovalMotionInConfig(PuzConfig *prevPuzConfig, vector<Piece*> pieceList, vector<Vector3i> seedPathVoxels);
    vector<int> CheckMovedSeedPathMotionInConfig(PuzConfig *tagtPuzConfig, vector<Piece*> pieceList, int seedPieceID, int seedAxisID, vector<Vector3i> seedPathVoxels);
    bool VoxelGroupRemovableAlongAxis(vector<Vector3i> seedPathVoxels, int axisID);
    bool IsVoxelOverlap(vector<Vector3i> seedPathVoxels, int axisID, int moveStep, bool &isOutExpVolume);
};

#endif