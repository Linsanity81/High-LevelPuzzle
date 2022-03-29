///////////////////////////////////////////////////////////////
//
// MeshObject.h
//
//   An object represented as a group of meshes, mainly for rendering
//
// by Rulin Chen and Peng Song
//
// 29/May/2021
//
//
///////////////////////////////////////////////////////////////


#ifndef _MESH_OBJECT_H
#define _MESH_OBJECT_H

//#include <igl/opengl/ViewerData.h>
#include "Utility/HelpTypedef.h"
#include "Utility/HelpPuz.h"
#include "Puzzle/PieceCreator.h"
using namespace std;
using namespace Eigen;

class Mesh;

class MeshObject
{

public:
    MeshObject() {};
    ~MeshObject() {};

    /// Ground
    vector<igl::opengl::ViewerData> CreateGround(Vector3d origin, double size, int gridNum, int sampNum);

    /// Axes
    vector<igl::opengl::ViewerData> CreateAxes(Vector3d origin, double size, int sampNum);

    /// Puzzle
    vector<igl::opengl::ViewerData> CreatePuzzle(vector<Eigen::MatrixXf> minPt,
                                                 vector<Eigen::MatrixXf> maxPt,
                                                 int pieceNum);

    vector<igl::opengl::ViewerData> CreatePuzzleSkeleton(vector<Eigen::MatrixXf> voxelCenPts,
                                                         vector<Eigen::MatrixXf> cylinTopPts,
                                                         vector<Eigen::MatrixXf> cylinBotPts,
                                                         float ballRadius,
                                                         float cylinRadius,
                                                         int pieceNum);

    void CreatePuzzleSkeleton(vector<Eigen::MatrixXf> voxelCenPts,
                              vector<Eigen::MatrixXf> cylinTopPts,
                              vector<Eigen::MatrixXf> cylinBotPts,
                              float ballRadius,
                              float cylinRadius,
                              vector<Mesh*> &puzzlePieceSkelMesh);

    vector<igl::opengl::ViewerData> CreateSmoothPuzzle(vector<Eigen::MatrixXd> smoothPieceVerticeList,
                                                       vector<Eigen::MatrixXi> smoothPieceFaceList, int pieceNum, vector<Eigen::MatrixXf> posVectors);

    /// Connectivity
    vector<igl::opengl::ViewerData> CreateDisconnectedEdge(Eigen::MatrixXf cylinTopPts,
                                                         Eigen::MatrixXf cylinBotPts,
                                                         float ballRadius,
                                                         float cylinRadius);

    ////////////////////////////////////////////////////////////////////
    // Note: These functions are for debug

    vector<igl::opengl::ViewerData> CreatePuzzleDebug(vector<Eigen::Vector3i> voxelList,
                                                      Vector3f voxelSize,
                                                      Vector3i volumeSize,
                                                      float ballRadius,
                                                      int debugInfo);

    ////////////////////////////////////////////////////////////////////

};

#endif //_MESH_OBJECT_H
