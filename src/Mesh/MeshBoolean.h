//////////////////////////////////////////////////
//MeshBoolean.h
//
// MeshBoolean Class, AUB A∆B A\B
//
// Created by Yingjie Cheng on 2020/11/20.
//
///////////////////////////////////////////////////

#ifndef _MESH_BOOLEAN_H
#define _MESH_BOOLEAN_H

#include <igl/copyleft/cgal/mesh_boolean.h>
#include <Eigen/Eigen>
using namespace Eigen;

class Mesh;

class MeshBoolean {
public:
    MeshBoolean();
    MeshBoolean(MatrixXd _VA, MatrixXi _FA, MatrixXd _VB, MatrixXi _FB);
    ~MeshBoolean();

public:
    MatrixXd VA,VB;
    MatrixXi FA,FB;

    ///if J(idC)<A.rows, J(idC) = idA; else J(idC)-A.rows = idB
    MatrixXi J;

    igl::MeshBooleanType boolean_type;

public:
    void MeshUnion(MatrixXd &VC, MatrixXi &FC);
    void MeshIntersect(MatrixXd &VC, MatrixXi &FC);
    void MeshMinus(MatrixXd &VC, MatrixXi &FC);

    void MeshUnion(const MatrixXd _VA, const MatrixXi _FA, const MatrixXd _VB, const MatrixXi _FB,
            MatrixXd &VC, MatrixXi &FC);
    void MeshIntersect(const MatrixXd _VA, const MatrixXi _FA, const MatrixXd _VB, const MatrixXi _FB,
                   MatrixXd &VC, MatrixXi &FC);
    void MeshMinus(const MatrixXd _VA, const MatrixXi _FA, const MatrixXd _VB, const MatrixXi _FB,
                   MatrixXd &VC, MatrixXi &FC);

    Mesh* MeshUnion(Mesh* A, Mesh *B);
    Mesh* MeshIntersect(Mesh* A, Mesh* B);
    Mesh* MeshMinus(Mesh*A, Mesh* B);

    };


#endif //_MESH_BOOLEAN_H
