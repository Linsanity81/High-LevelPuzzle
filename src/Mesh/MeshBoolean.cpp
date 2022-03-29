//////////////////////////////////////////////////
//MeshBoolean.h
//
// MeshBoolean Class, AUB A∆B A\B
//
// Created by Yingjie Cheng on 2020/11/20.
//
///////////////////////////////////////////////////

#include "MeshBoolean.h"
#include "Mesh.h"

MeshBoolean::MeshBoolean()
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_UNION;
}

MeshBoolean::MeshBoolean(MatrixXd _VA, MatrixXi _FA, MatrixXd _VB, MatrixXi _FB)
{
    VA = _VA;
    VB = _VB;
    FA = _FA;
    FB = _FB;

    boolean_type = igl::MESH_BOOLEAN_TYPE_UNION;
}
MeshBoolean::~MeshBoolean() {}

///==============================================================================//
///                              Boolean
///==============================================================================//

void MeshBoolean::MeshUnion(MatrixXd &VC, MatrixXi &FC)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_UNION;
    igl::copyleft::cgal::mesh_boolean(VA,FA,VB,FB,boolean_type,VC,FC,J);
}

void MeshBoolean::MeshUnion(const MatrixXd _VA, const MatrixXi _FA, const MatrixXd _VB,
        const MatrixXi _FB, MatrixXd &VC, MatrixXi &FC)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_UNION;
    igl::copyleft::cgal::mesh_boolean(_VA,_FA,_VB,_FB,boolean_type,VC,FC,J);
}

void MeshBoolean::MeshIntersect(MatrixXd &VC, MatrixXi &FC)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_INTERSECT;
    igl::copyleft::cgal::mesh_boolean(VA,FA,VB,FB,boolean_type,VC,FC,J);
}

void MeshBoolean::MeshIntersect(const MatrixXd _VA, const MatrixXi _FA,
        const MatrixXd _VB, const MatrixXi _FB, MatrixXd &VC, MatrixXi &FC)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_INTERSECT;
    igl::copyleft::cgal::mesh_boolean(_VA,_FA,_VB,_FB,boolean_type,VC,FC,J);
}

void MeshBoolean::MeshMinus(MatrixXd &VC, MatrixXi &FC)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_MINUS;
    igl::copyleft::cgal::mesh_boolean(VA,FA,VB,FB,boolean_type,VC,FC,J);
}

void MeshBoolean::MeshMinus(const MatrixXd _VA, const MatrixXi _FA,
        const MatrixXd _VB, const MatrixXi _FB, MatrixXd &VC, MatrixXi &FC)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_MINUS;
    igl::copyleft::cgal::mesh_boolean(_VA,_FA,_VB,_FB,boolean_type,VC,FC,J);
}

Mesh* MeshBoolean::MeshUnion(Mesh *A, Mesh *B)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_UNION;
    MatrixXd VC;
    MatrixXi FC, J;

    igl::copyleft::cgal::mesh_boolean(A->verM, A->triM, B->verM, B->triM, boolean_type, VC, FC, J);
    Mesh *UnionMesh = new Mesh(VC, FC);
    return UnionMesh;
}

Mesh* MeshBoolean::MeshIntersect(Mesh *A, Mesh *B)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_INTERSECT;
    MatrixXd VC;
    MatrixXi FC, J;

    igl::copyleft::cgal::mesh_boolean(A->verM, A->triM, B->verM, B->triM, boolean_type, VC, FC, J);
    Mesh *InterMesh = new Mesh(VC, FC);
    return InterMesh;
}

Mesh* MeshBoolean::MeshMinus(Mesh *A, Mesh *B)
{
    boolean_type = igl::MESH_BOOLEAN_TYPE_MINUS;
    MatrixXd VC;
    MatrixXi FC, J;

    igl::copyleft::cgal::mesh_boolean(A->verM, A->triM, B->verM, B->triM, boolean_type, VC, FC, J);
    Mesh *MinusMesh = new Mesh(VC, FC);
    return MinusMesh;
}