///////////////////////////////////////////////////////////////
//
// MeshObject.cpp
//
//   An object represented as a group of meshes, mainly for rendering
//
// by Rulin Chen and Peng Song
//
// 29/May/2021
//
//
///////////////////////////////////////////////////////////////


#include <vector>
#include <iostream>
#include <Eigen/Eigen>
#include "Utility/HelpFunc.h"
#include "Mesh.h"
#include "MeshCreator.h"
#include "MeshObject.h"
#include "MeshBoolean.h"

RowVector3d puzColor[16] = {
        RowVector3d(0.5, 0.9, 0.5),   //  1: Green
        RowVector3d(0.5, 0.9, 0.9),   //  2: Cyan
        RowVector3d(0.9, 0.6, 0.9),   //  3: Purple
        RowVector3d(0.6, 0.6, 0.9),   //  4: Blue
        RowVector3d(0.9, 0.9, 0.5),   //  5: Yellow
        RowVector3d(0.9, 0.6, 0.6),   //  6: Red
        RowVector3d(0.9, 0.6, 0.4),   //  7: Orange
        RowVector3d(0.9, 0.4, 0.7),   //  8: Pink
        RowVector3d(0.4, 0.9, 0.9),   //  9: Cyan
        RowVector3d(0.8, 0.8, 0.8),   // 10: Light Gray

        RowVector3d(0.6, 0.4, 0.3),   // 11: Brown
        RowVector3d(0.9, 0.6, 0.5),   // 12: LightSalmon
        RowVector3d(0.5, 0.2, 0.5),   // 13: Dark Purple
        RowVector3d(0.4, 0.8, 0.7),   // 14: Dark Cyan
        RowVector3d(0.3, 0.4, 0.7),   // 15: Dark Blue
        RowVector3d(0.7, 0.8, 0.9),   // 16: Light blue
};


/*
RowVector3d puzColor[16] = {
        RowVector3d(0.9, 0.5, 0.5),   //  1: Red
        RowVector3d(0.4, 0.9, 0.4),   //  2: Green
        RowVector3d(0.4, 0.4, 0.9),   //  3: Blue
        RowVector3d(0.9, 0.9, 0.5),   //  4: Yellow
        RowVector3d(0.7, 0.3, 0.9),   //  5: Purple
        RowVector3d(0.4, 0.9, 0.9),   //  6: Cyan

        RowVector3d(0.9, 0.6, 0.4),   //  7: Orange
        RowVector3d(0.6, 0.6, 0.9),   //  8: Light Blue
        RowVector3d(0.8, 0.8, 0.8),   //  9: Light Gray
        RowVector3d(0.9, 0.3, 0.6),   // 10: Pink
        RowVector3d(0.6, 0.4, 0.3),   // 11: Brown
        RowVector3d(0.9, 0.6, 0.5),   // 12: LightSalmon

        RowVector3d(0.5, 0.2, 0.5),   // 13: Dark Purple
        RowVector3d(0.4, 0.8, 0.7),   // 14: Dark Cyan
        RowVector3d(0.3, 0.4, 0.7),   // 15: Dark Blue
        RowVector3d(0.6, 0.6, 0.3),   // 16: Dark Yellow
};

RowVector3d puzColor[16] = {
        RowVector3d(0.9, 0.6, 0.4),   //  1: Orange
        RowVector3d(0.6, 0.6, 0.9),   //  2: Light Blue
        RowVector3d(0.4, 0.9, 0.4),   //  3: Green
        RowVector3d(0.4, 0.4, 0.9),   //  4: Blue
        RowVector3d(0.8, 0.8, 0.8),   //  5: Light Gray

        RowVector3d(0.9, 0.5, 0.5),   //  6: Red
        RowVector3d(0.9, 0.9, 0.5),   //  7: Yellow
        RowVector3d(0.7, 0.3, 0.9),   //  8: Purple
        RowVector3d(0.4, 0.9, 0.9),   //  9: Cyan
        RowVector3d(0.9, 0.3, 0.6),   // 10: Pink
        RowVector3d(0.6, 0.4, 0.3),   // 11: Brown
        RowVector3d(0.9, 0.6, 0.5),   // 12: LightSalmon

        RowVector3d(0.5, 0.2, 0.5),   // 13: Dark Purple
        RowVector3d(0.4, 0.8, 0.7),   // 14: Dark Cyan
        RowVector3d(0.3, 0.4, 0.7),   // 15: Dark Blue
        RowVector3d(0.6, 0.6, 0.3),   // 16: Dark Yellow
};*/


///=========================================================================================///
///                                        Ground
///=========================================================================================///

vector<igl::opengl::ViewerData> MeshObject::CreateGround(Vector3d origin, double size, int gridNum, int sampNum)
{
    double halfSize = 0.5f * size;
    double cyliRadius = 0.002 * size;


    /////////////////////////////////////////////////////////////////////////
    /// 1. Create 7 meshes for the axes (3 cylinders, 3 cones, and 1 sphere)

    MeshCreator meshCreator;
    MeshBoolean meshBoolean;

    vector<Mesh*> meshList;

    for (int i = 0; i <= gridNum; i++)
    {
        double z = -halfSize + (i/(double)gridNum) * size;

        Vector3d point1 = origin + Vector3d( -halfSize, 0, z);
        Vector3d point2 = origin + Vector3d(  halfSize, 0 ,z);

        Mesh *cylinder = meshCreator.CreateCylinder(point1, point2, cyliRadius, sampNum);

        meshList.push_back( cylinder );

    }

    for (int i = 0; i <= gridNum; i++)
    {
        double x = -halfSize + (i/(double)gridNum) * size;

        Vector3d point1 = origin + Vector3d( x, 0,  -halfSize);
        Vector3d point2 = origin + Vector3d( x, 0,   halfSize);

        Mesh *cylinder = meshCreator.CreateCylinder(point1, point2, cyliRadius, sampNum);

        meshList.push_back( cylinder );
    }

    /////////////////////////////////////////////////////////////////////////
    /// 1&1/2. Merge all cylinders as a ground
    /*
    Mesh* MGround = meshList[0];
    for(auto mcy : meshList)
        MGround = meshBoolean.MeshUnion(mcy, MGround);
    meshList.clear();
    meshList.push_back(MGround);
    */
    /////////////////////////////////////////////////////////////////////////
    /// 2. Create viewerData for each mesh to render it

    vector<igl::opengl::ViewerData> viewerDataList;

    for (auto mesh : meshList)
    {
        igl::opengl::ViewerData viewerData;
        viewerData.set_mesh(mesh->verM, mesh->triM);

        viewerData.set_colors(Eigen::RowVector3d(0.8, 0.8, 0.8));

        viewerData.show_lines = unsigned (0);
        viewerData.face_based = true;

        viewerDataList.push_back( viewerData );
    }


    /////////////////////////////////////////////////////////////////////////
    /// 3. Release memory for the meshList

    for (auto & i : meshList)
    {
        delete i;
    }
    meshList.clear();

    return viewerDataList;
}




///=========================================================================================///
///                                         Axes
///=========================================================================================///

vector<igl::opengl::ViewerData> MeshObject::CreateAxes(Vector3d origin, double size, int sampNum)
{
    /////////////////////////////////////////////////////////////////////////
    /// 1. Compute and specify parameters for the axes

    Vector3d xPoint1 = origin + Vector3d( 0.9*size, 0,         0);
    Vector3d xPoint2 = origin + Vector3d( 1.0*size, 0,         0);
    Vector3d yPoint1 = origin + Vector3d( 0,         0.9*size, 0);
    Vector3d yPoint2 = origin + Vector3d( 0,         1.0*size, 0);
    Vector3d zPoint1 = origin + Vector3d( 0,         0,         0.9*size);
    Vector3d zPoint2 = origin + Vector3d( 0,         0,         1.0*size);

    double cyliRadius = 0.02 * size;
    double coneRadius = 0.04 * size;
    double spheRadius = 0.04 * size;


    /////////////////////////////////////////////////////////////////////////
    /// 2. Create 7 meshes for the axes (3 cylinders, 3 cones, and 1 sphere)

    MeshCreator meshCreator;

    Mesh *cylinderX = meshCreator.CreateCylinder(origin, xPoint1, cyliRadius, sampNum);
    Mesh *cylinderY = meshCreator.CreateCylinder(origin, yPoint1, cyliRadius, sampNum);
    Mesh *cylinderZ = meshCreator.CreateCylinder(origin, zPoint1, cyliRadius, sampNum);

    Mesh *coneX = meshCreator.CreateCone(xPoint1, xPoint2, coneRadius, sampNum);
    Mesh *coneY = meshCreator.CreateCone(yPoint1, yPoint2, coneRadius, sampNum);
    Mesh *coneZ = meshCreator.CreateCone(zPoint1, zPoint2, coneRadius, sampNum);

    Mesh *sphere = meshCreator.CreateSphere(spheRadius, origin, sampNum, 2*sampNum);

    vector<Mesh*> meshList;

    meshList.push_back( cylinderX );
    meshList.push_back( coneX );

    meshList.push_back( cylinderY );
    meshList.push_back( coneY );

    meshList.push_back( cylinderZ );
    meshList.push_back( coneZ );

    meshList.push_back( sphere );


    /////////////////////////////////////////////////////////////////////////
    /// 3. Create viewerData for each mesh to render it

    vector<igl::opengl::ViewerData> viewerDataList;

    for (int i = 0; i < meshList.size(); i++)
    {
        Mesh *mesh = meshList[i];

        igl::opengl::ViewerData viewerData;
        viewerData.set_mesh(mesh->verM, mesh->triM);

        if     ( i == 0 || i == 1 )    viewerData.set_colors(Eigen::RowVector3d(0.9, 0.4, 0.4));
        else if( i == 2 || i == 3 )    viewerData.set_colors(Eigen::RowVector3d(0.4, 0.9, 0.4));
        else if( i == 4 || i == 5 )    viewerData.set_colors(Eigen::RowVector3d(0.4, 0.4, 0.9));
        else                           viewerData.set_colors(Eigen::RowVector3d(0.6, 0.6, 0.6));

        viewerData.show_lines = unsigned (0);
        viewerData.face_based = true;

        viewerDataList.push_back( viewerData );
    }


    /////////////////////////////////////////////////////////////////////////
    /// 4. Release memory for the meshList

    for (auto & i : meshList)
    {
        delete i;
    }
    meshList.clear();

    return viewerDataList;
}




///=========================================================================================///
///                                     Puzzle
///=========================================================================================///

vector<igl::opengl::ViewerData> MeshObject::CreatePuzzle(vector<Eigen::MatrixXf> voxelMinPts, vector<Eigen::MatrixXf> voxelMaxPts, int pieceNum)
{
    /////////////////////////////////////////////////////////////////////////
    /// 1. Create meshes for puzzle voxels

    MeshCreator meshCreator;

    Vector3d minPt;
    Vector3d maxPt;

    // Check the number of vertices and tris in each cube mesh
    minPt(0) = voxelMinPts[0](0,0);
    minPt(1) = voxelMinPts[0](0,1);
    minPt(2) = voxelMinPts[0](0,2);

    maxPt(0) = voxelMaxPts[0](0,0);
    maxPt(1) = voxelMaxPts[0](0,1);
    maxPt(2) = voxelMaxPts[0](0,2);

    Mesh *testCube = meshCreator.CreateCuboid(minPt, maxPt);
    int verNum = testCube->verM.rows();
    int triNum = testCube->triM.rows();
//    printf("verNumCube: %d.\n", verNumCube);

    vector<Mesh*> puzzlePieceCubeMesh;

    for(int i = 0; i < voxelMinPts.size(); i++)
    {
        Mesh * pieceMesh = new Mesh();
        pieceMesh->verM.resize(verNum * voxelMinPts[i].rows(), 3);
        pieceMesh->triM.resize(triNum * voxelMinPts[i].rows(), 3);
        pieceMesh->puzPieceIndex = i;

        for(int j = 0; j < voxelMinPts[i].rows(); j++)
        {
            minPt(0) = voxelMinPts[i](j,0);
            minPt(1) = voxelMinPts[i](j,1);
            minPt(2) = voxelMinPts[i](j,2);

            maxPt(0) = voxelMaxPts[i](j,0);
            maxPt(1) = voxelMaxPts[i](j,1);
            maxPt(2) = voxelMaxPts[i](j,2);

            Mesh *cuboid = meshCreator.CreateCuboid(minPt, maxPt);


            for (int z = 0; z < cuboid->verM.rows(); ++z)
            {
                pieceMesh->verM(j * verNum + z, 0) = cuboid->verM(z, 0);
                pieceMesh->verM(j * verNum + z, 1) = cuboid->verM(z, 1);
                pieceMesh->verM(j * verNum + z, 2) = cuboid->verM(z, 2);
            }

            for (int z = 0; z < cuboid->triM.rows(); ++z)
            {
                pieceMesh->triM(j * triNum + z, 0) = cuboid->triM(z, 0) + j * verNum;
                pieceMesh->triM(j * triNum + z, 1) = cuboid->triM(z, 1) + j * verNum;
                pieceMesh->triM(j * triNum + z, 2) = cuboid->triM(z, 2) + j * verNum;
            }

        }

        puzzlePieceCubeMesh.push_back(pieceMesh);
    }

    /////////////////////////////////////////////////////////////////////////
    /// 2. Create viewerData for each mesh to render it

    vector<igl::opengl::ViewerData> viewerDataList;

    int i = 0;
    for (auto mesh : puzzlePieceCubeMesh)
    {
        igl::opengl::ViewerData viewerData;
        viewerData.set_mesh(mesh->verM, mesh->triM);

        int colorIndex;

        if (mesh->puzPieceIndex == pieceNum-1)
        {
            colorIndex = 15;
        }
        else
        {
            colorIndex = mesh->puzPieceIndex % 16;;
        }

        viewerData.set_colors(puzColor[colorIndex]);

        viewerData.show_lines = unsigned (0);
        viewerData.face_based = true;
        viewerData.is_visible = true;

        viewerDataList.push_back( viewerData );
        i++;
    }

    /////////////////////////////////////////////////////////////////////////
    /// 3. Release memory for the meshList

    for (auto & i : puzzlePieceCubeMesh)
    {
        delete i;
    }
    puzzlePieceCubeMesh.clear();

    return viewerDataList;
}


vector<igl::opengl::ViewerData> MeshObject::CreatePuzzleSkeleton(vector<Eigen::MatrixXf> voxelCenPts,
                                                                 vector<Eigen::MatrixXf> cylinTopPts,
                                                                 vector<Eigen::MatrixXf> cylinBotPts,
                                                                 float ballRadius,
                                                                 float cylinRadius,
                                                                 int pieceNum)
{
    /////////////////////////////////////////////////////////////////////////
    /// 1. Create meshes for puzzle skeleton (balls and cylinders)


    MeshCreator meshCreator;
    vector<Mesh*> puzzlePieceSphereMesh;

    // Check the number of vertices and tris in each sphere mesh
    Vector3d cenPt;
    cenPt(0) = voxelCenPts[0](0,0);
    cenPt(1) = voxelCenPts[0](0,1);
    cenPt(2) = voxelCenPts[0](0,2);

    Mesh *testSphere = meshCreator.CreateSphere(ballRadius, cenPt,10,20);
    int verNumSphere = testSphere->verM.rows();
    int triNumSphere = testSphere->triM.rows();

    for(int i = 0; i < voxelCenPts.size(); i++)
    {
        Mesh * pieceSphereMesh = new Mesh();
        pieceSphereMesh->verM.resize(verNumSphere * voxelCenPts[i].rows(), 3);
        pieceSphereMesh->triM.resize(triNumSphere * voxelCenPts[i].rows(), 3);
        pieceSphereMesh->puzPieceIndex = i;

        for(int j = 0; j < voxelCenPts[i].rows(); j++)
        {
            cenPt(0) = voxelCenPts[i](j,0);
            cenPt(1) = voxelCenPts[i](j,1);
            cenPt(2) = voxelCenPts[i](j,2);

            Mesh *sphere = meshCreator.CreateSphere(ballRadius, cenPt,10,20);

            for (int z = 0; z < sphere->verM.rows(); ++z)
            {
                pieceSphereMesh->verM(j * verNumSphere + z, 0) = sphere->verM(z, 0);
                pieceSphereMesh->verM(j * verNumSphere + z, 1) = sphere->verM(z, 1);
                pieceSphereMesh->verM(j * verNumSphere + z, 2) = sphere->verM(z, 2);
            }

            for (int z = 0; z < sphere->triM.rows(); ++z)
            {
                pieceSphereMesh->triM(j * triNumSphere + z, 0) = sphere->triM(z, 0) + j * verNumSphere;
                pieceSphereMesh->triM(j * triNumSphere + z, 1) = sphere->triM(z, 1) + j * verNumSphere;
                pieceSphereMesh->triM(j * triNumSphere + z, 2) = sphere->triM(z, 2) + j * verNumSphere;
            }
        }
        puzzlePieceSphereMesh.push_back(pieceSphereMesh);
    }


    vector<Mesh*> puzzlePieceCylinderMesh;

    // Check the number of vertices and tris in each sphere mesh
    Vector3d topPt;
    Vector3d botPt;
    topPt(0) = cylinTopPts[0](0, 0);
    topPt(1) = cylinTopPts[0](0, 1);
    topPt(2) = cylinTopPts[0](0, 2);

    botPt(0) = cylinBotPts[0](0, 0);
    botPt(1) = cylinBotPts[0](0, 1);
    botPt(2) = cylinBotPts[0](0, 2);

    Mesh *testCylinder = meshCreator.CreateCylinder(topPt, botPt, cylinRadius, 200);
    int verNumCylinder = testCylinder->verM.rows();
    int triNumCylinder = testCylinder->triM.rows();

    for(int i = 0; i < cylinTopPts.size(); i++)
    {
        Mesh * pieceCylinderMesh = new Mesh();
        pieceCylinderMesh->verM.resize(verNumCylinder * cylinTopPts[i].rows(), 3);
        pieceCylinderMesh->triM.resize(triNumCylinder * cylinTopPts[i].rows(), 3);
        pieceCylinderMesh->puzPieceIndex = i;

        for(int j = 0; j < cylinTopPts[i].rows(); j++)
        {

            topPt(0) = cylinTopPts[i](j, 0);
            topPt(1) = cylinTopPts[i](j, 1);
            topPt(2) = cylinTopPts[i](j, 2);

            botPt(0) = cylinBotPts[i](j, 0);
            botPt(1) = cylinBotPts[i](j, 1);
            botPt(2) = cylinBotPts[i](j, 2);

            Mesh *cylinder = meshCreator.CreateCylinder(topPt, botPt, cylinRadius, 200);

            for (int z = 0; z < cylinder->verM.rows(); ++z)
            {
                pieceCylinderMesh->verM(j * verNumCylinder + z, 0) = cylinder->verM(z, 0);
                pieceCylinderMesh->verM(j * verNumCylinder + z, 1) = cylinder->verM(z, 1);
                pieceCylinderMesh->verM(j * verNumCylinder + z, 2) = cylinder->verM(z, 2);
            }

            for (int z = 0; z < cylinder->triM.rows(); ++z)
            {
                pieceCylinderMesh->triM(j * triNumCylinder + z, 0) = cylinder->triM(z, 0) + j * verNumCylinder;
                pieceCylinderMesh->triM(j * triNumCylinder + z, 1) = cylinder->triM(z, 1) + j * verNumCylinder;
                pieceCylinderMesh->triM(j * triNumCylinder + z, 2) = cylinder->triM(z, 2) + j * verNumCylinder;
            }

        }
        puzzlePieceCylinderMesh.push_back(pieceCylinderMesh);
    }


    // Combine sphere data and cylinder data together for exporting the skeleton .obj of each piece.
    vector<Mesh*> puzzlePieceSkelMesh;

    for (int i = 0; i < puzzlePieceSphereMesh.size(); ++i)
    {
        int verNumEachPiece = puzzlePieceSphereMesh[i]->verM.rows() + puzzlePieceCylinderMesh[i]->verM.rows();
        int triNumEachPiece = puzzlePieceSphereMesh[i]->triM.rows() + puzzlePieceCylinderMesh[i]->triM.rows();

        Mesh * pieceMesh = new Mesh();

        pieceMesh->verM.resize(verNumEachPiece, 3);
        pieceMesh->triM.resize(triNumEachPiece, 3);
        pieceMesh->puzPieceIndex = i;

        // Vertex data: Sphere vertex and Cylinder vertex
        for (int j = 0; j < puzzlePieceSphereMesh[i]->verM.rows(); ++j)
        {
            pieceMesh->verM(j, 0) = puzzlePieceSphereMesh[i]->verM(j, 0);
            pieceMesh->verM(j, 1) = puzzlePieceSphereMesh[i]->verM(j, 1);
            pieceMesh->verM(j, 2) = puzzlePieceSphereMesh[i]->verM(j, 2);
        }

        for (int j = 0; j < puzzlePieceCylinderMesh[i]->verM.rows(); ++j)
        {
            pieceMesh->verM(j + puzzlePieceSphereMesh[i]->verM.rows(), 0) = puzzlePieceCylinderMesh[i]->verM(j, 0);
            pieceMesh->verM(j + puzzlePieceSphereMesh[i]->verM.rows(), 1) = puzzlePieceCylinderMesh[i]->verM(j, 1);
            pieceMesh->verM(j + puzzlePieceSphereMesh[i]->verM.rows(), 2) = puzzlePieceCylinderMesh[i]->verM(j, 2);
        }

        // Triangle data
        for (int j = 0; j < puzzlePieceSphereMesh[i]->triM.rows(); ++j)
        {
            pieceMesh->triM(j,0) = puzzlePieceSphereMesh[i]->triM(j,0);
            pieceMesh->triM(j,1) = puzzlePieceSphereMesh[i]->triM(j,1);
            pieceMesh->triM(j,2) = puzzlePieceSphereMesh[i]->triM(j,2);
        }

        for (int j = 0; j < puzzlePieceCylinderMesh[i]->triM.rows(); ++j)
        {
            pieceMesh->triM(j + puzzlePieceSphereMesh[i]->triM.rows(),0) = puzzlePieceCylinderMesh[i]->triM(j,0) + puzzlePieceSphereMesh[i]->verM.rows();
            pieceMesh->triM(j + puzzlePieceSphereMesh[i]->triM.rows(),1) = puzzlePieceCylinderMesh[i]->triM(j,1) + puzzlePieceSphereMesh[i]->verM.rows();
            pieceMesh->triM(j + puzzlePieceSphereMesh[i]->triM.rows(),2) = puzzlePieceCylinderMesh[i]->triM(j,2) + puzzlePieceSphereMesh[i]->verM.rows();
        }

        puzzlePieceSkelMesh.push_back(pieceMesh);

    }


    /////////////////////////////////////////////////////////////////////////
    /// 2. Create viewerData for each mesh to render it

    vector<igl::opengl::ViewerData> viewerDataList;


    for (auto mesh : puzzlePieceSkelMesh)
    {
        igl::opengl::ViewerData viewerData;

        viewerData.set_mesh(mesh->verM, mesh->triM);

        int colorIndex;

        if (mesh->puzPieceIndex == pieceNum-1)
        {
            colorIndex = 15;
        }
        else
        {
            colorIndex = mesh->puzPieceIndex % 16;;
        }

        viewerData.set_colors(puzColor[colorIndex]);

        viewerData.show_lines = unsigned (0);
        viewerData.face_based = true;
        viewerData.is_visible = true;

        viewerDataList.push_back( viewerData );
    }


    /////////////////////////////////////////////////////////////////////////
    /// 3. Release memory for the meshList

    for (auto & i : puzzlePieceCylinderMesh)
    {
        delete i;
    }
    puzzlePieceCylinderMesh.clear();

    for (auto & i : puzzlePieceSphereMesh)
    {
        delete i;
    }
    puzzlePieceSphereMesh.clear();

    for (auto & i : puzzlePieceSkelMesh)
    {
        delete i;
    }
    puzzlePieceSkelMesh.clear();

    return viewerDataList;
}

vector<igl::opengl::ViewerData> MeshObject::CreateDisconnectedEdge(Eigen::MatrixXf cylinTopPts,
                                                       Eigen::MatrixXf cylinBotPts,
                                                       float ballRadius,
                                                       float cylinRadius)
{
    /////////////////////////////////////////////////////////////////////////
    /// 1. Create meshes for puzzle disconnected edges (cylinders)

    MeshCreator meshCreator;
    vector<Mesh*> puzzleDisconnectedEdgeMesh;

    Vector3d topPt;
    Vector3d botPt;
    topPt(0) = cylinTopPts(0, 0);
    topPt(1) = cylinTopPts(0, 1);
    topPt(2) = cylinTopPts(0, 2);

    botPt(0) = cylinBotPts(0, 0);
    botPt(1) = cylinBotPts(0, 1);
    botPt(2) = cylinBotPts(0, 2);

    Mesh *testCylinder = meshCreator.CreateCylinder(topPt, botPt, cylinRadius, 200);
    int verNumCylinder = testCylinder->verM.rows();
    int triNumCylinder = testCylinder->triM.rows();


    Mesh * pieceCylinderMesh = new Mesh();
    pieceCylinderMesh->verM.resize(verNumCylinder * cylinTopPts.rows(), 3);
    pieceCylinderMesh->triM.resize(triNumCylinder * cylinTopPts.rows(), 3);

    for(int j = 0; j < cylinTopPts.rows(); j++)
    {

        topPt(0) = cylinTopPts(j, 0);
        topPt(1) = cylinTopPts(j, 1);
        topPt(2) = cylinTopPts(j, 2);

        botPt(0) = cylinBotPts(j, 0);
        botPt(1) = cylinBotPts(j, 1);
        botPt(2) = cylinBotPts(j, 2);

        Mesh *cylinder = meshCreator.CreateCylinder(topPt, botPt, cylinRadius, 200);

        for (int z = 0; z < cylinder->verM.rows(); ++z)
        {
            pieceCylinderMesh->verM(j * verNumCylinder + z, 0) = cylinder->verM(z, 0);
            pieceCylinderMesh->verM(j * verNumCylinder + z, 1) = cylinder->verM(z, 1);
            pieceCylinderMesh->verM(j * verNumCylinder + z, 2) = cylinder->verM(z, 2);
        }

        for (int z = 0; z < cylinder->triM.rows(); ++z)
        {
            pieceCylinderMesh->triM(j * triNumCylinder + z, 0) = cylinder->triM(z, 0) + j * verNumCylinder;
            pieceCylinderMesh->triM(j * triNumCylinder + z, 1) = cylinder->triM(z, 1) + j * verNumCylinder;
            pieceCylinderMesh->triM(j * triNumCylinder + z, 2) = cylinder->triM(z, 2) + j * verNumCylinder;
        }

    }
    puzzleDisconnectedEdgeMesh.push_back(pieceCylinderMesh);

    /////////////////////////////////////////////////////////////////////////
    /// 2. Create viewerData for each mesh to render it

    vector<igl::opengl::ViewerData> viewerDataList;

    int i = 0;
    for (auto mesh : puzzleDisconnectedEdgeMesh)
    {
        igl::opengl::ViewerData viewerData;
        viewerData.set_mesh(mesh->verM, mesh->triM);

        viewerData.set_colors(RowVector3d(0,0,0));

        viewerData.show_lines = unsigned (0);
        viewerData.face_based = true;
        viewerData.is_visible = true;

        viewerDataList.push_back( viewerData );
        i++;
    }

    /////////////////////////////////////////////////////////////////////////
    /// 3. Release memory for the meshList

    for (auto & i : puzzleDisconnectedEdgeMesh)
    {
        delete i;
    }
    puzzleDisconnectedEdgeMesh.clear();

    return viewerDataList;

}

void MeshObject::CreatePuzzleSkeleton(vector<Eigen::MatrixXf> voxelCenPts,
                                      vector<Eigen::MatrixXf> cylinTopPts,
                                      vector<Eigen::MatrixXf> cylinBotPts,
                                      float ballRadius,
                                      float cylinRadius,
                                      vector<Mesh*> &puzzlePieceSkelMesh)
{
    /////////////////////////////////////////////////////////////////////////
    /// 1. Create meshes for puzzle skeleton (balls and cylinders)


    MeshCreator meshCreator;
    vector<Mesh*> puzzlePieceSphereMesh;

    // Check the number of vertices and tris in each sphere mesh
    Vector3d cenPt;
    cenPt(0) = voxelCenPts[0](0,0);
    cenPt(1) = voxelCenPts[0](0,1);
    cenPt(2) = voxelCenPts[0](0,2);

    Mesh *testSphere = meshCreator.CreateSphere(ballRadius, cenPt,10,20);
    int verNumSphere = testSphere->verM.rows();
    int triNumSphere = testSphere->triM.rows();

    for(int i = 0; i < voxelCenPts.size(); i++)
    {
        Mesh * pieceSphereMesh = new Mesh();
        pieceSphereMesh->verM.resize(verNumSphere * voxelCenPts[i].rows(), 3);
        pieceSphereMesh->triM.resize(triNumSphere * voxelCenPts[i].rows(), 3);
        pieceSphereMesh->puzPieceIndex = i;

        for(int j = 0; j < voxelCenPts[i].rows(); j++)
        {

            cenPt(0) = voxelCenPts[i](j,0);
            cenPt(1) = voxelCenPts[i](j,1);
            cenPt(2) = voxelCenPts[i](j,2);

            Mesh *sphere = meshCreator.CreateSphere(ballRadius, cenPt,10,20);

            for (int z = 0; z < sphere->verM.rows(); ++z)
            {
                pieceSphereMesh->verM(j * verNumSphere + z, 0) = sphere->verM(z, 0);
                pieceSphereMesh->verM(j * verNumSphere + z, 1) = sphere->verM(z, 1);
                pieceSphereMesh->verM(j * verNumSphere + z, 2) = sphere->verM(z, 2);
            }

            for (int z = 0; z < sphere->triM.rows(); ++z)
            {
                pieceSphereMesh->triM(j * triNumSphere + z, 0) = sphere->triM(z, 0) + j * verNumSphere;
                pieceSphereMesh->triM(j * triNumSphere + z, 1) = sphere->triM(z, 1) + j * verNumSphere;
                pieceSphereMesh->triM(j * triNumSphere + z, 2) = sphere->triM(z, 2) + j * verNumSphere;
            }
        }
        puzzlePieceSphereMesh.push_back(pieceSphereMesh);
    }


    vector<Mesh*> puzzlePieceCylinderMesh;

    // Check the number of vertices and tris in each sphere mesh
    Vector3d topPt;
    Vector3d botPt;
    topPt(0) = cylinTopPts[0](0, 0);
    topPt(1) = cylinTopPts[0](0, 1);
    topPt(2) = cylinTopPts[0](0, 2);

    botPt(0) = cylinBotPts[0](0, 0);
    botPt(1) = cylinBotPts[0](0, 1);
    botPt(2) = cylinBotPts[0](0, 2);

    Mesh *testCylinder = meshCreator.CreateCylinder(topPt, botPt, cylinRadius, 20);
    int verNumCylinder = testCylinder->verM.rows();
    int triNumCylinder = testCylinder->triM.rows();

    for(int i = 0; i < cylinTopPts.size(); i++)
    {
        Mesh * pieceCylinderMesh = new Mesh();
        pieceCylinderMesh->verM.resize(verNumCylinder * cylinTopPts[i].rows(), 3);
        pieceCylinderMesh->triM.resize(triNumCylinder * cylinTopPts[i].rows(), 3);
        pieceCylinderMesh->puzPieceIndex = i;

        for(int j = 0; j < cylinTopPts[i].rows(); j++)
        {

            topPt(0) = cylinTopPts[i](j, 0);
            topPt(1) = cylinTopPts[i](j, 1);
            topPt(2) = cylinTopPts[i](j, 2);

            botPt(0) = cylinBotPts[i](j, 0);
            botPt(1) = cylinBotPts[i](j, 1);
            botPt(2) = cylinBotPts[i](j, 2);

            Mesh *cylinder = meshCreator.CreateCylinder(topPt, botPt, cylinRadius, 20);

            for (int z = 0; z < cylinder->verM.rows(); ++z)
            {
                pieceCylinderMesh->verM(j * verNumCylinder + z, 0) = cylinder->verM(z, 0);
                pieceCylinderMesh->verM(j * verNumCylinder + z, 1) = cylinder->verM(z, 1);
                pieceCylinderMesh->verM(j * verNumCylinder + z, 2) = cylinder->verM(z, 2);
            }

            for (int z = 0; z < cylinder->triM.rows(); ++z)
            {
                pieceCylinderMesh->triM(j * triNumCylinder + z, 0) = cylinder->triM(z, 0) + j * verNumCylinder;
                pieceCylinderMesh->triM(j * triNumCylinder + z, 1) = cylinder->triM(z, 1) + j * verNumCylinder;
                pieceCylinderMesh->triM(j * triNumCylinder + z, 2) = cylinder->triM(z, 2) + j * verNumCylinder;
            }

        }
        puzzlePieceCylinderMesh.push_back(pieceCylinderMesh);
    }


    // Combine sphere data and cylinder data together for exporting the skeleton .obj of each piece.
    for (int i = 0; i < puzzlePieceSphereMesh.size(); ++i)
    {
        int verNumEachPiece = puzzlePieceSphereMesh[i]->verM.rows() + puzzlePieceCylinderMesh[i]->verM.rows();
        int triNumEachPiece = puzzlePieceSphereMesh[i]->triM.rows() + puzzlePieceCylinderMesh[i]->triM.rows();

        Mesh * pieceMesh = new Mesh();

        pieceMesh->verM.resize(verNumEachPiece, 3);
        pieceMesh->triM.resize(triNumEachPiece, 3);
        pieceMesh->puzPieceIndex = i;

        // Vertex data: Sphere vertex and Cylinder vertex
        for (int j = 0; j < puzzlePieceSphereMesh[i]->verM.rows(); ++j)
        {
            pieceMesh->verM(j, 0) = puzzlePieceSphereMesh[i]->verM(j, 0);
            pieceMesh->verM(j, 1) = puzzlePieceSphereMesh[i]->verM(j, 1);
            pieceMesh->verM(j, 2) = puzzlePieceSphereMesh[i]->verM(j, 2);
        }

        for (int j = 0; j < puzzlePieceCylinderMesh[i]->verM.rows(); ++j)
        {
            pieceMesh->verM(j + puzzlePieceSphereMesh[i]->verM.rows(), 0) = puzzlePieceCylinderMesh[i]->verM(j, 0);
            pieceMesh->verM(j + puzzlePieceSphereMesh[i]->verM.rows(), 1) = puzzlePieceCylinderMesh[i]->verM(j, 1);
            pieceMesh->verM(j + puzzlePieceSphereMesh[i]->verM.rows(), 2) = puzzlePieceCylinderMesh[i]->verM(j, 2);
        }

        // Triangle data
        for (int j = 0; j < puzzlePieceSphereMesh[i]->triM.rows(); ++j)
        {
            pieceMesh->triM(j,0) = puzzlePieceSphereMesh[i]->triM(j,0);
            pieceMesh->triM(j,1) = puzzlePieceSphereMesh[i]->triM(j,1);
            pieceMesh->triM(j,2) = puzzlePieceSphereMesh[i]->triM(j,2);
        }

        for (int j = 0; j < puzzlePieceCylinderMesh[i]->triM.rows(); ++j)
        {
            pieceMesh->triM(j + puzzlePieceSphereMesh[i]->triM.rows(),0) = puzzlePieceCylinderMesh[i]->triM(j,0) + puzzlePieceSphereMesh[i]->verM.rows();
            pieceMesh->triM(j + puzzlePieceSphereMesh[i]->triM.rows(),1) = puzzlePieceCylinderMesh[i]->triM(j,1) + puzzlePieceSphereMesh[i]->verM.rows();
            pieceMesh->triM(j + puzzlePieceSphereMesh[i]->triM.rows(),2) = puzzlePieceCylinderMesh[i]->triM(j,2) + puzzlePieceSphereMesh[i]->verM.rows();
        }

        puzzlePieceSkelMesh.push_back(pieceMesh);

    }

    /////////////////////////////////////////////////////////////////////////
    /// 2. Release memory for the meshList

    for (auto & i : puzzlePieceCylinderMesh)
    {
        delete i;
    }
    puzzlePieceCylinderMesh.clear();

    for (auto & i : puzzlePieceSphereMesh)
    {
        delete i;
    }
    puzzlePieceSphereMesh.clear();

}

vector<igl::opengl::ViewerData> MeshObject::CreateSmoothPuzzle(vector<Eigen::MatrixXd> smoothPieceVerticeList,
                                                   vector<Eigen::MatrixXi> smoothPieceFaceList, int pieceNum, vector<Eigen::MatrixXf> posVectors)
{
    /////////////////////////////////////////////////////////////////////////
    /// 1. Create mesh data

    vector<Mesh*> pieceSmoothMesh;

    for (int i = 0; i < pieceNum; ++i)
    {
        Mesh * currMesh = new Mesh();

        for (int k = 0; k < smoothPieceVerticeList[i].rows(); ++k)
        {
            smoothPieceVerticeList[i](k,0) += posVectors[i](0);
            smoothPieceVerticeList[i](k,1) += posVectors[i](1);
            smoothPieceVerticeList[i](k,2) += posVectors[i](2);
        }

        currMesh->verM = smoothPieceVerticeList[i];
        currMesh->triM = smoothPieceFaceList[i];

        currMesh->puzPieceIndex = i;

//        currMesh->ReverseNormal();

        pieceSmoothMesh.push_back(currMesh);
    }


    /////////////////////////////////////////////////////////////////////////
    /// 2. Create viewerData for each mesh to render it

    vector<igl::opengl::ViewerData> viewerDataList;

    int i = 0;
    for (auto mesh : pieceSmoothMesh)
    {
        igl::opengl::ViewerData viewerData;
        viewerData.set_mesh(mesh->verM, mesh->triM);

        int colorIndex;

        if (mesh->puzPieceIndex == pieceNum-1)
        {
            colorIndex = 15;
        }
        else
        {
            colorIndex = mesh->puzPieceIndex % 16;;
        }

        viewerData.set_colors(puzColor[colorIndex]);

//        printf("mesh %d\n", i);

        viewerData.show_lines = unsigned (0);
        viewerData.face_based = true;
        viewerData.is_visible = true;

        viewerDataList.push_back( viewerData );
        i++;
    }

    /////////////////////////////////////////////////////////////////////////
    /// 3. Release memory for the meshList

    for (auto & k : pieceSmoothMesh)
    {
        delete k;
    }
    pieceSmoothMesh.clear();

    return viewerDataList;
}




///=========================================================================================///
///                             These functions are for debug
///=========================================================================================///

vector<igl::opengl::ViewerData> MeshObject::CreatePuzzleDebug(vector<Eigen::Vector3i> voxelList,
                                                              Vector3f voxelSize,
                                                              Vector3i volumeSize,
                                                              float ballRadius,
                                                              int debugInfo)
{
    /////////////////////////////////////////////////////////////////////////
    /// 1. Compute real position for puzzle debug voxels

    if (debugInfo == SEED_PATH or debugInfo == BLOCK_PATH or debugInfo == EXTD_VOXEL)
    {
        ballRadius *= 1.1;
    }

    for (int i = 0; i < voxelList.size(); ++i)
    {
        voxelList[i] = voxelList[i] - volumeSize;
    }

    Eigen::MatrixXf voxelCenPts;
    voxelCenPts.resize(voxelList.size(), 3);

    for (int i = 0; i < voxelList.size(); ++i)
    {
        voxelCenPts(i,0) = 1.0f*voxelList[i](0)*voxelSize(0);
        voxelCenPts(i,1) = 1.0f*voxelList[i](1)*voxelSize(1);
        voxelCenPts(i,2) = 1.0f*voxelList[i](2)*voxelSize(2);
    }

    for (int i = 0; i < voxelCenPts.rows(); ++i)
    {
        voxelCenPts(i,0) -= 0.5f*(volumeSize(0) - 1) * voxelSize(0);
        voxelCenPts(i,1) -= 0.5f*(volumeSize(1) - 1) * voxelSize(1);
        voxelCenPts(i,2) -= 0.5f*(volumeSize(2) - 1) * voxelSize(2);
    }

    /////////////////////////////////////////////////////////////////////////
    /// 2. Create meshes for puzzle debug (balls)

    MeshCreator meshCreator;

    // Check the number of vertices and tris in each sphere mesh
    Vector3d cenPt;
    cenPt(0) = voxelCenPts(0,0);
    cenPt(1) = voxelCenPts(0,1);
    cenPt(2) = voxelCenPts(0,2);

    Mesh *testSphere = meshCreator.CreateSphere(ballRadius, cenPt,10,20);
    int verNumSphere = testSphere->verM.rows();
    int triNumSphere = testSphere->triM.rows();


    Mesh * pieceSphereMesh = new Mesh();
    pieceSphereMesh->verM.resize(verNumSphere * voxelCenPts.rows(), 3);
    pieceSphereMesh->triM.resize(triNumSphere * voxelCenPts.rows(), 3);
    pieceSphereMesh->puzPieceIndex = debugInfo;

    for(int j = 0; j < voxelCenPts.rows(); j++)
    {
        cenPt(0) = voxelCenPts(j,0);
        cenPt(1) = voxelCenPts(j,1);
        cenPt(2) = voxelCenPts(j,2);

        Mesh *sphere = meshCreator.CreateSphere(ballRadius, cenPt,10,20);

        for (int z = 0; z < sphere->verM.rows(); ++z)
        {
            pieceSphereMesh->verM(j * verNumSphere + z, 0) = sphere->verM(z, 0);
            pieceSphereMesh->verM(j * verNumSphere + z, 1) = sphere->verM(z, 1);
            pieceSphereMesh->verM(j * verNumSphere + z, 2) = sphere->verM(z, 2);
        }

        for (int z = 0; z < sphere->triM.rows(); ++z)
        {
            pieceSphereMesh->triM(j * triNumSphere + z, 0) = sphere->triM(z, 0) + j * verNumSphere;
            pieceSphereMesh->triM(j * triNumSphere + z, 1) = sphere->triM(z, 1) + j * verNumSphere;
            pieceSphereMesh->triM(j * triNumSphere + z, 2) = sphere->triM(z, 2) + j * verNumSphere;
        }
    }

    /////////////////////////////////////////////////////////////////////////
    /// 3. Create viewerData for each mesh to render it

    vector<igl::opengl::ViewerData> viewerDataList;

    igl::opengl::ViewerData viewerData;

    viewerData.set_mesh(pieceSphereMesh->verM, pieceSphereMesh->triM);

    int colorIndex;

    colorIndex = (16 + pieceSphereMesh->puzPieceIndex) % 16;

    viewerData.set_colors(puzColor[colorIndex]);

    viewerData.show_lines = unsigned (0);
    viewerData.face_based = true;
    viewerData.is_visible = true;

    viewerDataList.push_back( viewerData );

    /////////////////////////////////////////////////////////////////////////
    /// 4. Release memory for the mesh

    delete pieceSphereMesh;

    return viewerDataList;

}

