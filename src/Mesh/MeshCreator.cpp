///////////////////////////////////////////////////////////////
//
// MeshCreator.cpp
//
//   Construct libigl mesh of various primitive shapes
//
// by Yingjie Cheng and Peng Song
//
// 28/Nov/2020
//
//
///////////////////////////////////////////////////////////////


#include <vector>
#include <iostream>
#include <Eigen/Eigen>
#include "Mesh.h"
#include "../Utility/HelpFunc.h"
#include "MeshCreator.h"


///=========================================================================================///
///                                        Cuboid
///=========================================================================================///

/// Create an axis-aligned cuboid with the given parameters
///   minPt: corner point with the small x, y, z values
///   maxPt: corner point with the large x, y, z values

Mesh* MeshCreator::CreateCuboid(Vector3d minPt, Vector3d maxPt)
{
    // Create a cuboid with the computed size
    Vector3d size = maxPt - minPt;
    Mesh* mesh = CreateCuboid(size);

    // Compute the translation matrix
    Vector3d center = 0.5f * (minPt + maxPt);
    Matrix4d mat = GetTranslateMatrix( center );

    // Translate the cuboid to its computed position
    mesh->TransformMesh( mat );

    return mesh;
}

Mesh* MeshCreator::CreateCuboid(Vector3d size)
{
    vector<Vector3d> verList;
    vector<Vector3i> triList;

    /////////////////////////////////////////////////////////////////////////
    /// 1. Computer vertices of the cuboid

    double minX = -0.5f * size[0];
    double minY = -0.5f * size[1];
    double minZ = -0.5f * size[2];

    double maxX =  0.5f * size[0];
    double maxY =  0.5f * size[1];
    double maxZ =  0.5f * size[2];

    verList.emplace_back( minX, minY, maxZ );
    verList.emplace_back( maxX, minY, maxZ );
    verList.emplace_back( maxX, maxY, maxZ );
    verList.emplace_back( minX, maxY, maxZ );

    verList.emplace_back( minX, minY, minZ );
    verList.emplace_back( maxX, minY, minZ );
    verList.emplace_back( maxX, maxY, minZ );
    verList.emplace_back( minX, maxY, minZ );


    /////////////////////////////////////////////////////////////////////////
    /// 2. Computer triangles of the cuboid

    triList.emplace_back(5,4,7 );
    triList.emplace_back(5,7,6 );
    triList.emplace_back(7,2,6 );
    triList.emplace_back(7,3,2 );

    triList.emplace_back(1,0,4 );
    triList.emplace_back(1,3,0 );
    triList.emplace_back(5,6,2 );
    triList.emplace_back(5,2,1 );

    triList.emplace_back(4,5,1 );
    triList.emplace_back(1,2,3 );
    triList.emplace_back(0,3,4 );
    triList.emplace_back(4,3,7 );


    /////////////////////////////////////////////////////////////////////////
    /// 3. Construct a triangular mesh of the sphere

    Mesh *mesh = new Mesh(verList, triList);

    return mesh;
}




///=========================================================================================///
///                                         Sphere
///=========================================================================================///

/// Create a sphere with the given parameters
///   radius:     radius of the sphere
///   position:   position of the sphere center
///   polarSamp:  number of samples for the polar angle [-PI/2.0, PI/2.0]
///   azimuSamp:  number of samples for the azimuthal angle [0, 2.0*PI]

Mesh* MeshCreator::CreateSphere(double radius, Vector3d position, int polarSamp, int azimuSamp)
{
    // Create a sphere with the given radius, centered at the origin
    Mesh* mesh = CreateSphere(radius, polarSamp, azimuSamp);

    // Compute the translation matrix
    Matrix4d mat = GetTranslateMatrix( position );

    // Translate the sphere to its target position
    mesh->TransformMesh( mat );

    return mesh;
}

Mesh* MeshCreator::CreateSphere(double radius, int polarSamp, int azimuSamp)
{
    vector<Vector3d> verList;
    vector<Vector3i> triList;

    /////////////////////////////////////////////////////////////////////////
    /// 1. Computer vertices of the sphere

    verList.emplace_back(0, 0, radius);
    for(int i = 1; i < polarSamp; i++)
    {
        double alpha = M_PI/2.0 - i*M_PI/polarSamp;
        for(int j = 0; j < azimuSamp; j++)
        {
            double beta = j*2.0*M_PI/azimuSamp;
            double x,y,z;
            x = radius * cos(alpha) * cos(beta);
            y = radius * cos(alpha) * sin(beta);
            z = radius * sin(alpha);
            verList.emplace_back(x, y, z);
        }
    }
    verList.emplace_back(0, 0, -radius);


    /////////////////////////////////////////////////////////////////////////
    /// 2. Computer triangles of the sphere

    // Top ring of triangles
    for(int j = 0; j < azimuSamp-1; j++)
    {
        triList.emplace_back(0,j+1,j+2);
    }
    triList.emplace_back(0, azimuSamp, 1);

    // Middle rings of triangles
    int StartId = 1;
    for(int i = 1; i < polarSamp-1; i++)
    {
        for(int j = 0; j < azimuSamp-1; j++)
        {
            triList.emplace_back(StartId + j, StartId + azimuSamp + j,     StartId + azimuSamp + j + 1);
            triList.emplace_back(StartId + j, StartId + azimuSamp + j + 1, StartId + 1 + j);
        }
        triList.emplace_back(StartId + azimuSamp - 1, StartId + 2*azimuSamp - 1, StartId + azimuSamp);
        triList.emplace_back(StartId + azimuSamp - 1, StartId + azimuSamp, StartId);
        StartId += azimuSamp;
    }

    // Bottom ring of triangles
    int verNum = verList.size();
    for(int j=0; j<azimuSamp-1; j++)
    {
        triList.emplace_back(verNum - 1, j + 1 + StartId, j + StartId);
    }
    triList.emplace_back(verNum - 1, StartId, StartId + azimuSamp -1);


    /////////////////////////////////////////////////////////////////////////
    /// 3. Construct a triangular mesh of the sphere

    Mesh *mesh = new Mesh(verList, triList);

    return mesh;
}




///=========================================================================================///
///                                         Cylinder
///=========================================================================================///

/// Create a cylinder with the given parameters
///   capCenterA:  center point of one cap
///   capCenterB:  center point of the other cap
///   radius:      radius of the two caps
///   radSamp:     number of samples for the boundary of each cap

Mesh* MeshCreator::CreateCylinder(Vector3d capCenterA, Vector3d capCenterB, double radius, int radSamp)
{
    // Create a cylinder with the given radius and computed length
    double length = (capCenterB - capCenterA).norm();
    Mesh* mesh = CreateCylinder(length, radius, radSamp);

    // Compute the translation matrix
    Vector3d center = 0.5f * (capCenterA + capCenterB);
    Matrix4d traMat = GetTranslateMatrix( center );

    // Compute the rotation matrix (note: default cylinder is aligned with x-axis)
    Vector3d xAxis = Vector3d(1, 0, 0);
    Vector3d vector = (capCenterB - capCenterA).normalized();
    Vector3d rotAxis = xAxis.cross( vector );
    double dotP = xAxis.dot( vector );
    double rotAngle = acos( dotP );
    Matrix4d rotMat = GetRotationMatrix(rotAngle, rotAxis);

    // if para with x-axis, use y-axis
    if( rotAxis.norm() < 0.0001)
    {
        rotAxis = Vector3d (0,1,0).cross( vector );
        rotAngle = acos( Vector3d(0,1,0).dot(vector));
        rotMat = GetRotationMatrix(rotAngle, rotAxis) * GetRotationMatrix(Vector3d(0,0,M_PI/2));
    }

    // Compute the trannsform matrix on the cylinder
    Matrix4d transMat = traMat * rotMat;

    // Transform the cylinder to its target position and orientation
    mesh->TransformMesh( transMat );

    return mesh;
}


/// Create a cylinder that is centered at the origin and aligned with the x-axis)

Mesh* MeshCreator::CreateCylinder(double length, double radius, int radSamp)
{
    vector<Vector3d> verList;
    vector<Vector3i> triList;

    /////////////////////////////////////////////////////////////////////////
    /// 1. Computer vertices of the cylinder

    double halfLen = 0.5f * length;

    // Center point of the right cap
    verList.emplace_back(halfLen, 0, 0);

    // Sampled points on the right cap
    for(int j = 0; j < radSamp; j++)
    {
        double beta = j * 2.0 * M_PI / radSamp;

        double x, y, z;
        x = halfLen;
        y = radius * cos(beta);
        z = radius * sin(beta);

        verList.emplace_back(x, y, z);
    }

    // Sampled points on the left cap
    for(int j = 0; j < radSamp; j++)
    {
        double beta = j * 2.0 * M_PI / radSamp;

        double x, y, z;
        x = -halfLen;
        y = radius * cos(beta);
        z = radius * sin(beta);

        verList.emplace_back(x, y, z);
    }

    // Center point of the left cap
    verList.emplace_back(-halfLen, 0, 0);


    /////////////////////////////////////////////////////////////////////////
    /// 2. Computer triangles of the cylinder

    // Triangles of the right cap
    for(int j = 0; j < radSamp - 1; j++)
    {
        triList.emplace_back(0, j+1, j+2);
    }
    triList.emplace_back(0, radSamp, 1);

    // Triangles of the cylinder body
    int StartId = 1;
    for(int j=0;j<radSamp-1;j++)
    {
        triList.emplace_back(StartId + j, StartId + radSamp + j,     StartId + radSamp + j + 1);
        triList.emplace_back(StartId + j, StartId + radSamp + j + 1, StartId + 1 + j);
    }
    triList.emplace_back(StartId+radSamp - 1, StartId + 2*radSamp - 1, StartId + radSamp);
    triList.emplace_back(StartId+radSamp - 1, StartId + radSamp,       StartId);
    StartId += radSamp;

    // Triangles of the left cap
    int verNum = verList.size();
    for(int j = 0; j < radSamp - 1; j++)
    {
        triList.emplace_back(verNum - 1, j + 1 + StartId, j + StartId);
    }
    triList.emplace_back(verNum - 1, StartId, StartId + radSamp - 1);


    /////////////////////////////////////////////////////////////////////////
    /// 3. Construct a triangular mesh of the cylinder

    Mesh *mesh = new Mesh(verList, triList);

    return mesh;
}




///=========================================================================================///
///                                          Cone
///=========================================================================================///

/// Create a cone with the given parameters
///   baseCenter:  center point of the cone base
///   apexPoint:   point of the cone apex
///   radius:      radius of the cone base
///   radSamp:     number of samples for the base boundary

Mesh* MeshCreator::CreateCone(Vector3d baseCenter, Vector3d apexPoint, double radius, int radSamp)
{
    // Create a cylinder with the given radius and computed length
    double length = (apexPoint - baseCenter).norm();
    Mesh* mesh = CreateCone(length, radius, radSamp);

    // Compute the translation matrix
    Matrix4d traMat = GetTranslateMatrix( baseCenter );

    // Compute the rotation matrix (note: default cylinder is aligned with x-axis)
    Vector3d xAxis = Vector3d(1, 0, 0);
    Vector3d vector = (apexPoint - baseCenter).normalized();
    Vector3d rotAxis = xAxis.cross( vector );
    double dotP = xAxis.dot( vector );
    double rotAngle = acos( dotP );
    Matrix4d rotMat = GetRotationMatrix(rotAngle, rotAxis);

    // Compute the trannsform matrix on the cylinder
    Matrix4d transMat = traMat * rotMat;

    // Transform the cylinder to its target position and orientation
    mesh->TransformMesh( transMat );

    return mesh;
}


/// Create a cone that is oriented along the +x-axis; its base is centered at the origin

Mesh* MeshCreator::CreateCone(double length, double radius, int radSamp)
{
    vector<Vector3d> verList;
    vector<Vector3i> triList;

    /////////////////////////////////////////////////////////////////////////
    /// 1. Computer vertices of the cone

    // Base center point
    verList.emplace_back(0, 0, 0);

    // Sampled points on the base
    for(int j = 0; j < radSamp; j++)
    {
        double beta = j * 2.0 * M_PI / radSamp;

        double x, y, z;
        x = 0;
        y = radius * cos(beta);
        z = radius * sin(beta);

        verList.emplace_back(x,y,z);
    }

    // Apex point
    verList.emplace_back(length, 0, 0);


    /////////////////////////////////////////////////////////////////////////
    /// 2. Computer triangles of the cone

    // Triangles of the base
    for(int j = 0; j < radSamp - 1; j++)
    {
        triList.emplace_back(0, j+2, j+1);
    }
    triList.emplace_back(0, 1, radSamp);

    // Triangles of the cone body
    int StartID = 1+radSamp;
    for(int j = 0; j < radSamp - 1; j++)
    {
        triList.emplace_back(StartID, j+1, j+2);
    }
    triList.emplace_back(StartID, radSamp, 1);


    /////////////////////////////////////////////////////////////////////////
    /// 3. Construct a triangular mesh of the cylinder

    Mesh *mesh = new Mesh(verList, triList);

    return mesh;
}




///=========================================================================================///
///                                          Fan
///=========================================================================================///

/// Create a fan with the given parameters
///   radius:     large radius of the fan
///   length:     difference between the large radius and the small radius
///   thickness:  thickness of the fan (along y-axis)
///   angle:      opening angle of the fan

Mesh* MeshCreator::CreateFan(double radius, double length, double thickness, double angle)
{
    vector<Vector3d> verList;
    vector<Vector3i> triList;

    /////////////////////////////////////////////////////////////////////////
    /// 1. Computer vertices of the fan

    double r = thickness/2.0;

    double x1 = (radius - length) * sin(angle) + r * cos(angle);
    double x2 = 1.1*(radius/cos(angle) + r*tan(angle))*sin(angle) + r*cos(angle);

    double z1 = (radius - length) * cos(angle) - r * sin(angle);
    double z2 = 1.1*(radius/cos(angle) + r*tan(angle))*cos(angle) - r*sin(angle);

    verList.emplace_back( x1, -r,  z1);
    verList.emplace_back( x2, -r,  z2);
    verList.emplace_back(-x2, -r,  z2);
    verList.emplace_back(-x1, -r,  z1);

    verList.emplace_back( x1,  r,  z1);
    verList.emplace_back( x2,  r,  z2);
    verList.emplace_back(-x2,  r,  z2);
    verList.emplace_back(-x1,  r,  z1);

    /////////////////////////////////////////////////////////////////////////
    /// 2. Computer triangles of the fan

    triList.emplace_back(0, 1, 2);
    triList.emplace_back(0, 2, 3);
    triList.emplace_back(1, 5, 6);
    triList.emplace_back(1, 6, 2);
    triList.emplace_back(0, 4, 5);
    triList.emplace_back(0, 5, 1);
    triList.emplace_back(2, 6, 7);
    triList.emplace_back(2, 7, 3);
    triList.emplace_back(0, 3, 7);
    triList.emplace_back(0, 7, 4);
    triList.emplace_back(4, 7, 6);
    triList.emplace_back(4, 6, 5);


    /////////////////////////////////////////////////////////////////////////
    /// 3. Construct a triangular mesh of the cylinder

    Mesh *mesh = new Mesh(verList, triList);

    return mesh;
}