///////////////////////////////////////////////////////////////
//
// Mesh.h
//
//   libigl mesh data structure
//
// by Yingjie Cheng and Peng Song
//
// 28/Nov/2020
//
//
///////////////////////////////////////////////////////////////


#include "Mesh.h"
#include "Utility/HelpDefine.h"
#include "Utility/HelpFunc.h"



///=========================================================================================///
///                                   Initialization
///=========================================================================================///

Mesh::Mesh()
{

}

Mesh::Mesh(vector<Vector3d> verList, vector<Vector3i> triList)
{
    verM.resize(verList.size(), 3);
    for(int i=0; i<verList.size(); i++)
    {
        verM(i,0) = verList[i].x();
        verM(i,1) = verList[i].y();
        verM(i,2) = verList[i].z();
    }

    triM.resize(triList.size(), 3);
    for(int i=0; i<triList.size(); i++)
    {
        triM(i,0) = triList[i].x();
        triM(i,1) = triList[i].y();
        triM(i,2) = triList[i].z();
    }
}

Mesh::Mesh(const MatrixXd& _verM, MatrixXi _triM)
{
    verM = _verM;
    triM = _triM;
    //todo: get normal
    //GetMeshTriangles();
}

Mesh::~Mesh()
{
    ClearMesh();
}

Mesh* Mesh::DeepCopy()
{

    Mesh *meshCopy = new Mesh();

    meshCopy->verM = this->verM;
    meshCopy->triM = this->triM;
    meshCopy->norM = this->norM;

    for (auto & triangle : this->triangles)
    {
        auto *tri = new Triangle();
        *tri = *triangle;

        meshCopy->triangles.push_back(tri);
    }

    return meshCopy;
}

void Mesh::ClearMesh()
{
    for (int i=0; i<triangles.size(); i++)
    {
        delete triangles[i];
    }
    triangles.clear();
}




///=========================================================================================///
///                         vector to Eigen matrix and inverse
///=========================================================================================///

void Mesh::VerList2VerMat(vector<Vector3d> verList)
{
    int VerSize;
    VerSize = verList.size();
    verM.resize(VerSize, 3);
    for(int i=0;i<VerSize;i++)
    {
        verM(i,0) = verList[i](0);
        verM(i,1) = verList[i](1);
        verM(i,2) = verList[i](2);
    }
}

void Mesh::TriList2TriMat(vector<Vector3i> triList)
{
    int FaceSize = triList.size();
    triM.resize(FaceSize,3);
    for(int i=0;i<FaceSize;i++)
    {
        triM(i,0) = triList[i](0);
        triM(i,1) = triList[i](1);
        triM(i,2) = triList[i](2);
    }
}

void Mesh::TriMat2TriList(vector<Vector3i> &triList)
{
    triList.clear();
    triList.reserve(triM.rows()+1);
    for(int i=0;i<triM.rows();i++)
    {
        Vector3i triface;
        triface << triM(i,0), triM(i,1), triM(i,2);
        triList.emplace_back(triface);
    }
}


void Mesh::VerMat2VerList(vector<Vector3d> &verList)
{
    verList.clear();
    verList.reserve(verM.rows()+1);
    for(int i=0;i<verM.rows();i++)
    {
        Vector3d verPoint;
        verPoint << verM(i,0), verM(i,1), verM(i,2);
        verList.emplace_back(verPoint);
    }
}

void Mesh::RestoreNormal()
{
    int rows = triangles.size();
    norM.resize(rows,3);
    for(int i=0;i<rows;i++)
    {
        norM(i,0) = triangles[i]->normal.x();
        norM(i,1) = triangles[i]->normal.y();
        norM(i,2) = triangles[i]->normal.z();
    }
}


///=========================================================================================///
///                                  Mesh Operations
///=========================================================================================///

void Mesh::GetMeshTriangles()
{
    // Clear existing triangles
    for (int i = 0; i < triangles.size(); i++)
    {
        delete triangles[i];
    }
    triangles.clear();

    // Save new triangles
    for (int i = 0; i < triM.rows(); i++)
    {
        Triangle *tri = new Triangle();

        // Get vertex indices of three corners
        for (int j=0; j<3; j++)
        {
            int verID = triM(i,j);
            tri->v[j].x() = verM(verID,0);
            tri->v[j].y() = verM(verID,1);
            tri->v[j].z() = verM(verID,2);
        }

        tri->ComputeNormal();
        tri->ComputeCenter();

        triangles.push_back(tri);
    }
    //TriList2TriMat();
    RestoreNormal();
}

void Mesh::ReverseNormal()
{
    for (int i = 0; i < triM.rows(); i++)
    {
        int tmp_y = triM(i,1);
        int tmp_z = triM(i,2);

        triM(i,1) = tmp_z;
        triM(i,2) = tmp_y;
    }

    //TriList2TriMat();
    GetMeshTriangles();
}




///=========================================================================================///
///                                  Transform Mesh
///=========================================================================================///

void Mesh::TransformMesh(Matrix4d transMat)
{
    for (int i = 0; i < verM.rows(); i++)
    {
        Vector3d origVer, currVer;
        origVer[0] = verM(i, 0);
        origVer[1] = verM(i, 1);
        origVer[2] = verM(i, 2);

        MultiplyPoint(origVer, transMat, currVer);

        verM(i, 0) = currVer[0];
        verM(i, 1) = currVer[1];
        verM(i, 2) = currVer[2];
    }
}

void Mesh::TransformMesh(Matrix4d transMat, MatrixXd &newVerM)
{
    /*
    newVerM.resize(verM.rows(), verM.cols());

    for (int i = 0; i < verM.rows(); i++)
    {
        Vector3d origVer, currVer;
        origVer[0] = verM(i, 0);
        origVer[1] = verM(i, 1);
        origVer[2] = verM(i, 2);

        MultiplyPoint(origVer, transMat, currVer);

        newVerM(i, 0) = currVer[0];
        newVerM(i, 1) = currVer[1];
        newVerM(i, 2) = currVer[2];
    }
     */

    newVerM = verM*(transMat.block(0,0,3,3).transpose());
    Eigen::RowVector3d trans = transMat.matrix().block(0,3,3,1).transpose();
    newVerM = ( newVerM.rowwise() + trans).eval();
}
