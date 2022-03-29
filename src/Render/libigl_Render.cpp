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
#include <iostream>
#include <Eigen/Eigen>
#include "libigl_Render.h"
#include "Puzzle/Puzzle.h"
#include "Puzzle/Volume.h"
#include "Mesh/MeshObject.h"

#include "Puzzle/PuzAction.h"
#include "Puzzle_debug/Puzzle_debug.h"


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

    puzzleDisconnectedEdgeMeshNum = 0;

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

    printf("disassState: %d\n", disassStateID);
    printf("size of disconnectedEdgeList: %lu\n", myPuzzle.volume->disconnectedEdgeList.size());

    if (disassStateID == 0 and myPuzzle.volume->disconnectedEdgeList.size() != 0)
    {
        Eigen::MatrixXf cylinBotPts;
        Eigen::MatrixXf cylinTopPts;

        myPuzzle.CreatePuzzleConnectivityGeo(cylinBotPts, cylinTopPts);

        DrawDisconnectedEdge(viewer, cylinBotPts, cylinTopPts, ballRadius, cyliRadius * 2);
    }

    vector<Eigen::MatrixXf> posVectors = myPuzzle.GetPieceAssemblyPos(disassStateID);

    if (myPuzzle.smoothPieceVerticeList.size() != 0 and myPuzzle.smoothPieceFaceList.size() != 0)
    {
        printf("Begin to render the smooth puzzle.\n");
        DrawSmoothPuzzle(viewer, myPuzzle.smoothPieceVerticeList, myPuzzle.smoothPieceFaceList, myPuzzle.pieceList.size(), posVectors);
    }
    else
    {
        printf("There is no smooth puzzle that need to be rendered.\n");
    }
}

void libigl_Render::RenderPuzzle_debug(iglViewer &viewer, Puzzle_debug &myPuzzle_debug, int pieceID_debug, Puzzle &myPuzzle)
{
    vector<Eigen::MatrixXf> voxelMinPtsList;
    vector<Eigen::MatrixXf> voxelMaxPtsList;
    vector<Eigen::MatrixXf> voxelCenPtsList;
    vector<Eigen::MatrixXf> cylinTopPtsList;
    vector<Eigen::MatrixXf> cylinBotPtsList;

    PuzConfig currFurthestPuzConfig = myPuzzle_debug.piece_debug_List[pieceID_debug].furthestPuzConfig;
    Piece_debug currPiece_debug = myPuzzle_debug.piece_debug_List[pieceID_debug];

    currFurthestPuzConfig.PrintPuzConfig(false);

    float ballRadius = 0.08  * myPuzzle.volume->GetVoxelSize().norm();
    float cyliRadius = 0.015 * myPuzzle.volume->GetVoxelSize().norm();

    int pieceNum = currFurthestPuzConfig.piecePosList.size() - 1;

    Vector3f voxelSize  = myPuzzle.volume->GetVoxelSize();
    Vector3i volumeSize = myPuzzle.volume->GetVolumeSize();

    ClearViewer( viewer );

    myPuzzle.CreatePuzzleGeometry(voxelMinPtsList, voxelMaxPtsList, voxelCenPtsList, cylinTopPtsList, cylinBotPtsList, currFurthestPuzConfig);

    DrawPuzzle(viewer, voxelMinPtsList, voxelMaxPtsList, voxelCenPtsList, cylinTopPtsList, cylinBotPtsList, ballRadius, cyliRadius, pieceNum);

    DrawConstrucInfo(viewer, currPiece_debug, voxelSize, volumeSize, ballRadius * 1.2);
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

void libigl_Render::DrawDisconnectedEdge(iglViewer &viewer,
                          Eigen::MatrixXf cylinTopPts,
                          Eigen::MatrixXf cylinBotPts,
                          float ballRadius,
                          float cylinRadius)
{
    MeshObject meshObject;

    /// Draw the puzzle disconnected edges
    vector<igl::opengl::ViewerData> puzzleViewerDataList = meshObject.CreateDisconnectedEdge(cylinTopPts, cylinBotPts, ballRadius, cylinRadius);
    AppendDataToViewer( viewer, puzzleViewerDataList );
    puzzleDisconnectedEdgeMeshNum = puzzleViewerDataList.size();
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

void libigl_Render::ShowDisconnectedEdges(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum;

    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleDisconnectedEdgeMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowSmoothPuzzle(iglViewer &viewer, bool isVisible) {
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum;

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
        ClearMesh(viewer, (puzzleMeshNum + puzzleMeshNum_debug + puzzleDisconnectedEdgeMeshNum + puzzleSmoothMeshNum + puzzleSmoothInputMeshNum));

        puzCubeNum = 0;                // Number of mesh models for rendering puzzle voxels (i.e., cubes)
        puzSkelNum = 0;
        puzzleMeshNum = 0;          // Number of mesh models for rendering puzzle and its skeleton

        puzzleDisconnectedEdgeMeshNum = 0;

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




///=========================================================================================///
///                      Render the Construction Path Info for Debug
///=========================================================================================///

void libigl_Render::DrawConstrucInfo(iglViewer &viewer, MainPath mainPath, Vector3f voxelSize, Vector3i volumeSize, float ballRadius)
{
    MeshObject meshObject;

    /// Draw the debug info
    if (mainPath._ContaVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerContaDataList = meshObject.CreatePuzzleDebug(mainPath._ContaVoxels, voxelSize, volumeSize, ballRadius, CONTA_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerContaDataList );
        puzzleContaVoxelMeshNum = puzDebugViewerContaDataList.size();
    }

    if (mainPath._SeedVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerSeedDataList = meshObject.CreatePuzzleDebug(mainPath._SeedVoxels, voxelSize, volumeSize, ballRadius, SEED_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerSeedDataList );
        puzzleSeedVoxelMeshNum = puzDebugViewerSeedDataList.size();
    }

    if (mainPath._SeedKeptVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerSeedKeptDataList = meshObject.CreatePuzzleDebug(mainPath._SeedKeptVoxels, voxelSize, volumeSize, ballRadius, SEED_KEPT);
        AppendDataToViewer( viewer, puzDebugViewerSeedKeptDataList );
        puzzleSeedKeptMeshNum = puzDebugViewerSeedKeptDataList.size();
    }

    if (mainPath._SeedPathVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerSeedPathDataList = meshObject.CreatePuzzleDebug(mainPath._SeedPathVoxels, voxelSize, volumeSize, ballRadius, SEED_PATH);
        AppendDataToViewer( viewer, puzDebugViewerSeedPathDataList );
        puzzleSeedPathMeshNum = puzDebugViewerSeedPathDataList.size();
    }

    if (mainPath._BlockVoxel.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerBlockDataList = meshObject.CreatePuzzleDebug(mainPath._BlockVoxel, voxelSize, volumeSize, ballRadius, BLOCK_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerBlockDataList );
        puzzleBlockVoxelMeshNum = puzDebugViewerBlockDataList.size();
    }

    if (mainPath._BlockKeptVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerBlockKeptDataList = meshObject.CreatePuzzleDebug(mainPath._BlockKeptVoxels, voxelSize, volumeSize, ballRadius, BLOCK_KEPT);
        AppendDataToViewer( viewer, puzDebugViewerBlockKeptDataList );
        puzzleBlockKeptMeshNum= puzDebugViewerBlockKeptDataList.size();
    }

    if (mainPath._BlockPathVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerBlockPathDataList = meshObject.CreatePuzzleDebug(mainPath._BlockPathVoxels, voxelSize, volumeSize, ballRadius, BLOCK_PATH);
        AppendDataToViewer( viewer, puzDebugViewerBlockPathDataList );
        puzzleBlockPathMeshNum= puzDebugViewerBlockPathDataList.size();
    }

    if (mainPath._ExtdVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerExtdDataList = meshObject.CreatePuzzleDebug(mainPath._ExtdVoxels, voxelSize, volumeSize, ballRadius, EXTD_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerExtdDataList );
        puzzleExtdMeshNum= puzDebugViewerExtdDataList.size();
    }

    /// Number of meshes for rendering the puzzle debug information
    puzzleMeshNum_debug = puzzleContaVoxelMeshNum + puzzleSeedVoxelMeshNum + puzzleSeedKeptMeshNum + puzzleSeedPathMeshNum
                          + puzzleBlockVoxelMeshNum + puzzleBlockKeptMeshNum + puzzleBlockPathMeshNum + puzzleExtdMeshNum;

}

void libigl_Render::DrawConstrucInfo(iglViewer &viewer, Piece_debug piece_debug, Vector3f voxelSize, Vector3i volumeSize, float ballRadius)
{
    MeshObject meshObject;

    /// Draw the debug info
    if (piece_debug._ContaVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerContaDataList = meshObject.CreatePuzzleDebug(piece_debug._ContaVoxels, voxelSize, volumeSize, ballRadius, CONTA_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerContaDataList );
        puzzleContaVoxelMeshNum = puzDebugViewerContaDataList.size();
    }

    if (piece_debug._SeedVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerSeedDataList = meshObject.CreatePuzzleDebug(piece_debug._SeedVoxels, voxelSize, volumeSize, ballRadius, SEED_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerSeedDataList );
        puzzleSeedVoxelMeshNum = puzDebugViewerSeedDataList.size();
    }

    if (piece_debug._SeedKeptVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerSeedKeptDataList = meshObject.CreatePuzzleDebug(piece_debug._SeedKeptVoxels, voxelSize, volumeSize, ballRadius, SEED_KEPT);
        AppendDataToViewer( viewer, puzDebugViewerSeedKeptDataList );
        puzzleSeedKeptMeshNum = puzDebugViewerSeedKeptDataList.size();
    }

    if (piece_debug._SeedPathVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerSeedPathDataList = meshObject.CreatePuzzleDebug(piece_debug._SeedPathVoxels, voxelSize, volumeSize, ballRadius, SEED_PATH);
        AppendDataToViewer( viewer, puzDebugViewerSeedPathDataList );
        puzzleSeedPathMeshNum = puzDebugViewerSeedPathDataList.size();
    }

    if (piece_debug._BlockVoxel.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerBlockDataList = meshObject.CreatePuzzleDebug(piece_debug._BlockVoxel, voxelSize, volumeSize, ballRadius, BLOCK_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerBlockDataList );
        puzzleBlockVoxelMeshNum = puzDebugViewerBlockDataList.size();
    }

    if (piece_debug._BlockKeptVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerBlockKeptDataList = meshObject.CreatePuzzleDebug(piece_debug._BlockKeptVoxels, voxelSize, volumeSize, ballRadius, BLOCK_KEPT);
        AppendDataToViewer( viewer, puzDebugViewerBlockKeptDataList );
        puzzleBlockKeptMeshNum= puzDebugViewerBlockKeptDataList.size();
    }

    if (piece_debug._BlockPathVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerBlockPathDataList = meshObject.CreatePuzzleDebug(piece_debug._BlockPathVoxels, voxelSize, volumeSize, ballRadius, BLOCK_PATH);
        AppendDataToViewer( viewer, puzDebugViewerBlockPathDataList );
        puzzleBlockPathMeshNum= puzDebugViewerBlockPathDataList.size();
    }

    if (piece_debug._ExtdVoxels.size() != 0)
    {
        vector<igl::opengl::ViewerData> puzDebugViewerExtdDataList = meshObject.CreatePuzzleDebug(piece_debug._ExtdVoxels, voxelSize, volumeSize, ballRadius, EXTD_VOXEL);
        AppendDataToViewer( viewer, puzDebugViewerExtdDataList );
        puzzleExtdMeshNum= puzDebugViewerExtdDataList.size();
    }

    /// Number of meshes for rendering the puzzle debug information
    puzzleMeshNum_debug = puzzleContaVoxelMeshNum + puzzleSeedVoxelMeshNum + puzzleSeedKeptMeshNum + puzzleSeedPathMeshNum
                          + puzzleBlockVoxelMeshNum + puzzleBlockKeptMeshNum + puzzleBlockPathMeshNum + puzzleExtdMeshNum;

}


void libigl_Render::ShowContaVoxels(iglViewer &viewer, bool isVisible){

    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleContaVoxelMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowSeedVoxels(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum + puzzleContaVoxelMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleSeedVoxelMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowSeedKeptVoxels(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum + puzzleContaVoxelMeshNum + puzzleSeedVoxelMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleSeedKeptMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowSeedPathVoxels(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum + puzzleContaVoxelMeshNum
                      + puzzleSeedVoxelMeshNum + puzzleSeedKeptMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleSeedPathMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowBlockVoxels(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum + puzzleContaVoxelMeshNum
                      + puzzleSeedVoxelMeshNum + puzzleSeedKeptMeshNum + puzzleSeedPathMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleBlockVoxelMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowBlockKeptVoxels(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum + puzzleContaVoxelMeshNum
                      + puzzleSeedVoxelMeshNum + puzzleSeedKeptMeshNum + puzzleSeedPathMeshNum + puzzleBlockVoxelMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleBlockKeptMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowBlockPathVoxels(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum + puzzleContaVoxelMeshNum
                      + puzzleSeedVoxelMeshNum + puzzleSeedKeptMeshNum + puzzleSeedPathMeshNum + puzzleBlockVoxelMeshNum + puzzleBlockKeptMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleBlockPathMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}

void libigl_Render::ShowExtdVoxels(iglViewer &viewer, bool isVisible)
{
    int prevMeshNum = groundMeshNum + axesMeshNum + puzzleMeshNum + puzzleDisconnectedEdgeMeshNum + puzzleContaVoxelMeshNum
                      + puzzleSeedVoxelMeshNum + puzzleSeedKeptMeshNum + puzzleSeedPathMeshNum
                      + puzzleBlockVoxelMeshNum + puzzleBlockKeptMeshNum + puzzleBlockPathMeshNum;
    for(int i = prevMeshNum + 1; i <= prevMeshNum + puzzleExtdMeshNum; i++)
    {
        viewer.data_list[i].is_visible = isVisible;
    }
}







