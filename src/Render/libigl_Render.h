///////////////////////////////////////////////////////////////
//
// libigl_Render.h
//
//   Rendering various 3D contents with libigl
//
// by Rulin Chen and Peng Song
//
// 22/Aug/2021
//
//
///////////////////////////////////////////////////////////////


#ifndef _LIBIGL_RENDER_H
#define _LIBIGL_RENDER_H


#include "Utility/HelpTypedef.h"
#include "Utility/HelpDefine.h"
#include "Utility/HelpPuz.h"
#include "Mesh/Mesh.h"
#include "Puzzle/PieceCreator.h"
#include "Puzzle_debug/Piece_debug.h"

using namespace std;
using namespace Eigen;

class Puzzle;
class Puzzle_debug;


class libigl_Render
{
public:
    int groundMeshNum;              // Number of mesh models for rendering the ground
    int axesMeshNum;                // Number of mesh models for rendering the world
    int puzCubeNum;                 // Number of mesh models for rendering puzzle voxels (i.e., cubes)
    int puzSkelNum ;
    int puzzleDisconnectedEdgeMeshNum;
    int puzzleMeshNum;              // Number of mesh models for rendering puzzle and its skeleton

    int puzzleContaVoxelMeshNum;
    int puzzleSeedVoxelMeshNum;
    int puzzleSeedKeptMeshNum;
    int puzzleSeedPathMeshNum;
    int puzzleBlockVoxelMeshNum;
    int puzzleBlockKeptMeshNum;
    int puzzleBlockPathMeshNum;
    int puzzleExtdMeshNum;
    int puzzleMeshNum_debug;          // Number of mesh models for construction framework debug. E.g Seed Voxels etc.

    int puzzleSmoothMeshNum;
    int puzzleSmoothInputMeshNum;


public:
    libigl_Render();
    ~libigl_Render();

    /// Render Ground and Axes
    void RenderScene(iglViewer &viewer);
    void DrawGround(iglViewer &viewer, Vector3d origin, double size, int gridNum, int sampNum);
    void DrawWorldAxes(iglViewer &viewer, Vector3d origin, double size, int sampNum);

    /// Render Puzzle
    void RenderPuzzle(iglViewer &viewer, Puzzle &myPuzzle, int disassStateID);
    void DrawPuzzle(iglViewer &viewer,
                    vector<Eigen::MatrixXf> voxelMinPts,
                    vector<Eigen::MatrixXf> voxelMaxPts,
                    vector<Eigen::MatrixXf> voxelCenPts,
                    vector<Eigen::MatrixXf> cylinTopPts,
                    vector<Eigen::MatrixXf> cylinBotPts,
                    float ballRadius,
                    float cylinRadius,
                    int pieceNum);
    void DrawDisconnectedEdge(iglViewer &viewer,
                    Eigen::MatrixXf cylinTopPts,
                    Eigen::MatrixXf cylinBotPts,
                    float ballRadius,
                    float cylinRadius);

    void RenderPuzzle_debug(iglViewer &viewer, Puzzle_debug &myPuzzle_debug, int pieceID_debug, Puzzle &myPuzzle);

    void DrawSmoothPuzzle(iglViewer &viewer, vector<Eigen::MatrixXd> smoothPieceVerticeList,
                          vector<Eigen::MatrixXi> smoothPieceFaceList, int pieceNum, vector<Eigen::MatrixXf> posVectors);

    /// Show/hide Objects
    void ShowGround(iglViewer &viewer,bool isVisible) const;
    void ShowAxes(iglViewer &viewer, bool isVisible) const;
    void ShowPuzzle(iglViewer &viewer, bool isVisible);
    void ShowPuzzleSkeleton(iglViewer &viewer, bool isVisible);
    void ShowSmoothPuzzle(iglViewer &viewer, bool isVisible);

    /// Append/Remove Data from Viewer
    void AppendDataToViewer(iglViewer &viewer, vector<iglViewerData> viewerDataList);
    void ClearViewer(iglViewer &viewer);
    void ClearMesh(iglViewer &viewer, int meshNum);

    /// Set Camera
    void SetCamera(iglViewer &viewer, float zoom, Vector3f eyePos);

    ////////////////////////////////////////////////////////////////////
    // Note: These functions are for debug

    /// Render the Construction Path Info for Debug
    void DrawConstrucInfo(iglViewer &viewer,
                          MainPath mainPath,
                          Vector3f voxelSize,
                          Vector3i volumeSize,
                          float ballRadius);

    void DrawConstrucInfo(iglViewer &viewer,
                          Piece_debug piece_debug,
                          Vector3f voxelSize,
                          Vector3i volumeSize,
                          float ballRadius);

    /// Show/hide Objects for Construction Framework Debug
    void ShowContaVoxels(iglViewer &viewer, bool isVisible);
    void ShowSeedVoxels(iglViewer &viewer, bool isVisible);
    void ShowSeedKeptVoxels(iglViewer &viewer, bool isVisible);
    void ShowSeedPathVoxels(iglViewer &viewer, bool isVisible);
    void ShowBlockVoxels(iglViewer &viewer, bool isVisible);
    void ShowBlockKeptVoxels(iglViewer &viewer, bool isVisible);
    void ShowBlockPathVoxels(iglViewer &viewer, bool isVisible);
    void ShowExtdVoxels(iglViewer &viewer, bool isVisible);
    void ShowDisconnectedEdges(iglViewer &viewer, bool isVisible);

    ////////////////////////////////////////////////////////////////////
};

#endif //_LIBIGL_RENDER_H
