///////////////////////////////////////////////////////////////
//
// Volume.h
//
//   3D Volume Class
//
// by Peng SONG ( peng_song@sutd.edu.sg )
//
// 13/Jun/2021
//
//
///////////////////////////////////////////////////////////////

#ifndef _VOLUME_H
#define _VOLUME_H


class BoundingBox;
class Voxel;
class Piece;


class Volume
{
public:
    BoundingBox *bbox;               // Volume bounding box
    Voxel *outBBoxVoxel;             // One voxel out of volume bounding box

    Vector3i volumeSize;             // Volume size [W H D]
    Vector3f voxelSize;              // Voxel size [x y z]
    vector<Voxel*> voxelGrid;        // Volume voxel array (size: W*H*D)

    int volVoxelNum;                 // Voxel number of the puzzle

    vector< vector<int> > disconnectedEdgeList;

public:
    Volume();
	~Volume();
	void ClearVolume();
    Volume & operator=(const Volume & volume);
    void PrintVolume();

    /// Init/Write Volume
    int InitVolume(const Vector3i _volumeSize, const Vector3f _voxelSize, const vector<int> puzzleData, const vector<vector <int>> connectivityEdgeList);
    vector<Piece*> ConvertVolume2Puzzle(int pieceNum);
    void WritePuzzleFile(const char fileName[], const float generationTime);

    /// Volume Get Operations
    int GetVolumeVoxelNum();
    Vector3i GetVolumeSize();
    Vector3f GetVoxelSize();
    vector<Voxel*> GetVoxelGrid();

    /// Volume Voxel Operations
    Voxel* GetVolumeVoxel(Vector3i voxelPos);
    int GetVolumeVoxelIndex(Vector3i voxelPos);
    float GetNeighborVoxelNum(Vector3i voxelPos, int pieceID);
    void GetVolumeVoxelNeighbors(Vector3i voxelPos, int neiborPieceIDs[6]);
    void GetVolumeVoxelPosByIndex(int voxelIndex, Vector3i &voxelCentPos);

	/// Puzzle Piece Operations
    void InitializeRootPiece(Piece *rootPiece);
    void UpdateVolume_PieceID(Piece *piece);
    void UpdateVolume_Reach(Piece *piece);
    void SetVolumeVoxelPieceID(Vector3i voxelPos, const int pieceID);
    void SetVolumeVoxelReach(Vector3i voxelPos, const float reach);

    /// Volume Contact Operations
    void ComputeVoxelContactPiece(vector<Piece*> pieceList);
    void UpdateVolumeShape(vector<Piece*> pieceList);
    void ResetVolumeShape(vector<Piece*> pieceList);
    void ClearPieceInfo();
};

#endif
