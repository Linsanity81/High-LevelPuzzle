///////////////////////////////////////////////////////////////
//
// libigl_Render.cpp
//
//   Rendering various 3D contents with libigl
//
// by Rulin Chen and Peng Song
//
// 22/Aug/2021
//
//
///////////////////////////////////////////////////////////////


#include <utility>
#include <vector>
#include <Eigen/Eigen>
#include "libigl_Render.h"
#include "Puzzle/Puzzle.h"
#include "Puzzle/Volume.h"
#include "Mesh/MeshObject.h"
#include "Puzzle/PuzAction.h"


///=========================================================================================///
///                                        Initialization
///=========================================================================================///

libigl_Render::libigl_Render()
{
    groundMeshNum = 0;
    axesMeshNum = 0;
    puzCubeNum = 0;
    puzSkelNum = 0;
    puzzleMeshNum = 0;

    puzzleContaVoxelMeshNum = 0;
    puzzleSeedVoxelMeshNum = 0;
    puzzleSeedKeptMeshNum = 0;
    puzzleSeedPathMeshNum = 0;
    puzzleBlockVoxelMeshNum = 0;
    puzzleBlockKeptMeshNum = 0;
    puzzleBlockPathMeshNum = 0;
    puzzleExtdMeshNum = 0;
    puzzleMeshNum_debug = 0;

    puzzleSmoothMeshNum = 0;
    puzzleSmoothInputMeshNum = 0;
}

libigl_Render::~libigl_Render()
{

}



///=========================================================================================///
///                                     Render Ground and Axes
///=========================================================================================///

void libigl_Render::RenderScene(iglViewer &viewer)
{
    DrawGround(viewer, Vector3d(0,0,0), 4.0, 10, 10);

    DrawWorldAxes(viewer, Vector3d(0,0,0), 2.0, 20);

    //DrawMeshForDebug(viewer);
}

void libigl_Render::DrawGround(iglViewer &viewer, Vector3d origin, double size, int gridNum, int sampNum)
{
    MeshObject meshObject;
    vector<igl::opengl::ViewerData> viewerDataList =  meshObject.CreateGround(std::move(origin), size, gridNum, sampNum);

    AppendDataToViewer( viewer, viewerDataList );

    groundMeshNum = viewerDataList.size();
}

void libigl_Render::DrawWorldAxes(iglViewer &viewer, Vector3d origin, double size, int sampNum)
{
    MeshObject meshObject;
    vector<igl::opengl::ViewerData> viewerDataList =  meshObject.CreateAxes(std::move(origin), size, sampNum);

    AppendDataToViewer( viewer, viewerDataList );

    axesMeshNum = viewerDataList.size();
}




///=========================================================================================///
///                                       Render Puzzle
///=========================================================================================///

void libigl_Render::RenderPuzzle(iglViewer &viewer, Puzzle &myPuzzle, int disassStateID)
{
    vector<Eigen::MatrixXf> voxelMinPtsList;
    vector<Eigen::MatrixXf> voxelMaxPtsList;
    vector<Eigen::MatrixXf> voxelCenPtsList;
    vector<Eigen::MatrixXf> cylinTopPtsList;
    vector<Eigen::MatrixXf> cylinBotPtsList;

    float ballRadius = 0.08  * myPuzzle.volume->GetVoxelSize().norm();
    float cyliRadius = 0.015 * myPuzzle.volume->GetVoxelSize().norm();

    int pieceNum = myPuzzle.pieceList.size();

    myPuzzle.CreatePuzzleGeometry(voxelMinPtsList, voxelMaxPtsList, voxelCenPtsList, cylinTopPtsList, cylinBotPtsList, disassStateID);

    ClearViewer( viewer );

    DrawPuzzle(viewer, voxelMinPtsList, voxelMaxPtsList, voxelCenPtsList, cylinTopPtsList, cylinBotPtsList, ballRadius, cyliRadius, pieceNum);

    vector<Eigen::MatrixXf> posVectors = myPuzzle.GetPieceAssemblyPos(disassStateID);

    if (myPuzzle.smoothPieceVerticeList.size() != 0 and myPuzzle.smoothPieceFaceList.size() != 0)
    {
        DrawSmoothPuzzle(viewer, myPuzzle.smoothPieceVerticeList, myPuzzle.smoothPieceFaceList, myPuzzle.pieceList.size(), posVectors);
    }
}

void libigl_Render::DrawPuzzle(iglViewer &viewer,
                               vector<Eigen::MatrixXf> voxelMinPts,
                               vector<Eigen::MatrixXf> voxelMaxPts,
                               vector<Eigen::MatrixXf> voxelCenPts,
                               vector<Eigen::MatrixXf> cylinTopPts,
                               vector<Eigen::MatrixXf> cylinBotPts,
                               float ballRadius,
                               float cylinRadius,
                               int pieceNum)
{
    MeshObject meshObject;

    /// Draw the puzzle
    vector<igl::opengl::ViewerData> puzzleViewerDataList = meshObject.CreatePuzzle(voxelMinPts, voxelMaxPts, pieceNum);
    AppendDataToViewer( viewer, puzzleViewerDataList );
    puzCubeNum = puzzleViewerDataList.size();

    /// Draw the puzzle skeleton
    vector<igl::opengl::ViewerData> puzSkelViewerDataList = meshObject.CreatePuzzleSkeleton(voxelCenPts, cylinTopPts, cylinBotPts, ballRadius, cylinRadius, pieceNum);
    AppendDataToViewer( viewer, puzSkelViewerDataList );
    puzSkelNum = puzSkelViewerDataList.size();

    /// Number of meshes for rendering the puzzle and its skeleton
    puzzleMeshNum = puzzleViewerDataList.size() + puzSkelViewerDataList.size();
}

void libigl_Render::DrawSmoothPuzzle(iglViewer &viewer, vector<Eigen::MatrixXd> smoothPieceVerticeList,
                                     vector<Eigen::MatrixXi> smoothPieceFaceList, int pieceNum, vector<Eigen::MatrixXf> posVectors){

    MeshObject meshObject;

    /// Draw the smooth puzzle
    vector<igl::opengl::ViewerData> puzzleViewerDataList = meshObject.CreateSmoothPuzzle(smoothPieceVerticeList, smoothPieceFaceList, pieceNum, posVectors);
    AppendDataToViewer( viewer, puzzleViewerDataList );
    puzzleSmoothMeshNum = puzzleViewerDataList.size();
}




///=========================================================================================///
///                                     Show/hide Objects
///=========================================================================================///

void libigl_Render::ShowGround(iglViewer &viewer, bool isVisible) const
{
    for(int i = 1; i <= groundMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowAxes(iglViewer &viewer, bool isVisible) const
{
    for(int i = groundMeshNum+1; i <= groundMeshNum + axesMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowPuzzle(iglViewer &viewer, bool isVisible)
{
    for(int i = groundMeshNum + axesMeshNum +1; i <= groundMeshNum + axesMeshNum + puzCubeNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowPuzzleSkeleton(iglViewer &viewer, bool isVisible)
{
    for(int i = groundMeshNum + axesMeshNum + puzCubeNum + 1; i <= groundMeshNum + axesMeshNum + puzCubeNum + puzzleMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowSmoothPuzzle(iglViewer &viewer, bool isVisible) {
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum;

    for (int i = prevMeshNum + 1; i <= prevMeshNum + puzzleSmoothMeshNum; ++i)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}




///=========================================================================================///
///                               Append/Remove Data from Viewer
///=========================================================================================///

void libigl_Render::AppendDataToViewer(iglViewer &viewer, vector<igl::opengl::ViewerData> viewerDataList)
{
    for (const auto & i : viewerDataList)
    {
        viewer.data_list.push_back( i );
    }
}

void libigl_Render::ClearViewer(iglViewer &viewer)
{
    if ( (puzzleMeshNum + puzzleMeshNum_debug) != 0)
    {
        ClearMesh(viewer, (puzzleMeshNum + puzzleMeshNum_debug + puzzleSmoothMeshNum + puzzleSmoothInputMeshNum));

        puzCubeNum = 0;                // Number of mesh models for rendering puzzle voxels (i.e., cubes)
        puzSkelNum = 0;
        puzzleMeshNum = 0;          // Number of mesh models for rendering puzzle and its skeleton

        puzzleContaVoxelMeshNum = 0;
        puzzleSeedVoxelMeshNum = 0;
        puzzleSeedKeptMeshNum = 0;
        puzzleSeedPathMeshNum = 0;
        puzzleBlockVoxelMeshNum = 0;
        puzzleBlockKeptMeshNum = 0;
        puzzleBlockPathMeshNum = 0;
        puzzleExtdMeshNum = 0;
        puzzleMeshNum_debug = 0;    // Number of mesh models for construction framework debug. E.g Seed Voxels etc.

        puzzleSmoothMeshNum = 0;
        puzzleSmoothInputMeshNum = 0;

    }
}

// Clear last N meshes added to viewerDataList recently
void libigl_Render::ClearMesh(iglViewer &viewer,int meshNum)
{
    for (int i = 0; i < meshNum; i++)
    {
        viewer.selected_data_index = viewer.data_list.size()-1;
        viewer.erase_mesh(viewer.selected_data_index);
        viewer.data(viewer.selected_data_index).clear();
    }
}




///=========================================================================================///
///                                        Set Camera
///=========================================================================================///

void libigl_Render::SetCamera(iglViewer &viewer, float zoom, Vector3f eyePos)
{
    // change the camera parameters here
    // the rest of the parameters can be found at line 127(ViewerCore.h)

    viewer.core().camera_zoom  =  zoom;
    viewer.core().camera_eye   =  eyePos;
}



