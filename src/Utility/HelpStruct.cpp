///////////////////////////////////////////////////////////////
//
// HelpStruct.cpp
//
//   Common Structures
//
// by Peng SONG ( songpenghit@gmail.com )
//
// 02/Sep/2015
//
// Changed by Yingjie Cheng 2020/11/04
//
///////////////////////////////////////////////////////////////


#include "HelpStruct.h"

///==============================================================================//
///                              3D box
///==============================================================================//

Box::Box()
{
    minPt = Vector3d(0, 0, 0);
    maxPt = Vector3d(0, 0, 0);
    cenPt = Vector3d(0, 0, 0);
}

Box & Box::operator=(const Box &box)
{
    if( this == &box )
        return *this;

    this->minPt = box.minPt;
    this->maxPt = box.maxPt;
    this->cenPt = box.cenPt;

    this->size  = box.size;

    return *this;
}

void Box::PrintBox()
{
    printf("Box: [%7.3f  %7.3f  %7.3f]      [%7.3f  %7.3f  %7.3f] \n",
            minPt(0), minPt(1), minPt(2), maxPt(0), maxPt(1), maxPt(2));
}


Vector3d Box::GetCenter()
{
    cenPt = 0.5f * ( minPt + maxPt );
    return cenPt;
}

Vector3d Box::GetSize()
{
    size = maxPt - minPt;
    return size;
}

void Box::GetMinMaxPts()
{
    minPt = cenPt - 0.5f * size;
    maxPt = cenPt + 0.5f * size;
}

vector<Vector3d> Box::GetCorners()
{
    Vector3d tempCorners[8];

    tempCorners[0] = Vector3d(minPt(0), minPt(1), minPt(2));
    tempCorners[1] = Vector3d(minPt(0), maxPt(1), minPt(2));
    tempCorners[2] = Vector3d(maxPt(0), maxPt(1), minPt(2));
    tempCorners[3] = Vector3d(maxPt(0), minPt(1), minPt(2));

    tempCorners[4] = Vector3d(minPt(0), minPt(1), maxPt(2));
    tempCorners[5] = Vector3d(minPt(0), maxPt(1), maxPt(2));
    tempCorners[6] = Vector3d(maxPt(0), maxPt(1), maxPt(2));
    tempCorners[7] = Vector3d(maxPt(0), minPt(1), maxPt(2));

    //vector<Vector3d> cornerList;
    corners.clear();
    for (int i = 0; i < 8; i++)
    {
        corners.push_back(tempCorners[i]);
    }

    return corners;
}

vector<vector<int>> Box::GetEdges()
{
    // TODO: change the initialization
    int edges[12][2] =
            {
                    0, 3,  // Along X-axis
                    1, 2,
                    5, 6,
                    4, 7,

                    0, 1,  // Along Y-axis
                    4, 5,
                    7, 6,
                    3, 2,

                    0, 4,  // Along Z-axis
                    3, 7,
                    2, 6,
                    1, 5
            };


    vector<vector<int>> edgeList;

    for (int i = 0; i < 12; i++)
    {
        vector<int> edge;
        for (int j = 0; j < 2; j++)
        {
            edge.push_back(edges[i][j]);
        }

        edgeList.push_back(edge);
    }

    return edgeList;
}


vector<vector<int>> Box::GetQuadFaces()
{
    int faces[6][4] =
            {
                    0, 4, 5, 1,  // Normal X-axis
                    3, 2, 6, 7,

                    0, 3, 7, 4,  // Normal Y-axis
                    1, 5, 6, 2,

                    0, 1, 2, 3,  // Normal Z-axis
                    4, 7, 6, 5
            };

    vector<vector<int>> faceList;
    for (int i = 0; i < 6; i++)
    {
        vector<int> face;
        for (int j = 0; j < 4; j++)
        {
            face.push_back(faces[i][j]);
        }

        faceList.push_back(face);
    }

    return faceList;
}


vector<Vector3i> Box::GetTriFaces()
{
    int faces[12][3] =
            {
                    0, 4, 5,  // Normal X-axis
                    5, 1, 0,
                    3, 2, 6,
                    6, 7, 3,

                    0, 3, 7,  // Normal Y-axis
                    7, 4, 0,
                    1, 5, 6,
                    6, 2, 1,

                    0, 1, 2,  // Normal Z-axis
                    2, 3, 0,
                    4, 7, 6,
                    6, 5, 4
            };

    vector<Vector3i> faceList;
    for (int i = 0; i < 12; i++)
    {
        Vector3i triFace = Vector3i(faces[i][0], faces[i][1], faces[i][2]);

        faceList.push_back(triFace);
    }

    return faceList;
}



void Box::Transform(Vector3d transVec, Vector3d scale)
{
    minPt(0) *= scale(0);  minPt(1) *= scale(1);  minPt(2) *= scale(2);
    maxPt(0) *= scale(0);  maxPt(1) *= scale(1);  maxPt(2) *= scale(2);
    cenPt(0) *= scale(0);  cenPt(1) *= scale(1);  cenPt(2) *= scale(2);

    minPt += transVec;
    maxPt += transVec;
    cenPt += transVec;
}

double Box::GetQuadArea()
{
    Vector3d dimen = maxPt - minPt;
    double quadArea = 0;

    if      ( dimen(0) == 0 && dimen(1)  > 0 &&  dimen(2)  > 0 )
        quadArea = dimen(1) * dimen(2);  // y-z plane quad
    else if ( dimen(0)  > 0 && dimen(1) == 0 &&  dimen(2)  > 0 )
        quadArea = dimen(0) * dimen(2);  // x-z plane quad
    else if ( dimen(0)  > 0 && dimen(1)  > 0 &&  dimen(2) == 0 )
        quadArea = dimen(0) * dimen(1);  // x-y plane quad
    else
        printf("Warning: The box is not degenerated into a quad. \n");

    return quadArea;
}




///==============================================================================//
///                              3D Triangle
///==============================================================================//

void Triangle::Init(Vector3d _v0, Vector3d _v1, Vector3d _v2)
{
    v[0] = _v0;
    v[1] = _v1;
    v[2] = _v2;
}

Triangle & Triangle::operator=(const Triangle &tri)
{
    if( this == &tri )
        return *this;

    for (int i=0; i<3; i++)
    {
        this->v[i] = tri.v[i];
    }

    this->normal = tri.normal;
    this->center = tri.center;
    this->area   = tri.area;

    return *this;
}

bool Triangle::IsEqual(Triangle *tri)
{
    if( this->v[0] == tri->v[0] &&
        this->v[1] == tri->v[1] &&
        this->v[2] == tri->v[2] )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Triangle::PrintTriangle()
{
    printf("v0: [%.12f %.12f %.12f] \n", v[0](0), v[0](1), v[0](2));
    printf("v1: [%.12f %.12f %.12f] \n", v[1](0), v[1](1), v[1](2));
    printf("v2: [%.12f %.12f %.12f] \n", v[2](0), v[2](1), v[2](2));
    printf("\n");
}


void Triangle::ComputeCenter()
{
    center = (v[0]+v[1]+v[2])/3.0f;
}


void Triangle::ComputeArea()
{
    Vector3d normal  = (v[1] - v[0]).cross(v[2] - v[0]);
    area  = 0.5f * normal.norm();
}

void Triangle::ComputeNormal()
{
    Vector3d tempNor = (v[1] - v[0]).cross(v[2] - v[0]);  // Assume the vertices are saved in counter-clockwise
    double tempNorLen = (tempNor).norm();

    if ( tempNorLen != 0 )    normal = tempNor / tempNorLen;
    else                      normal = Vector3d(1,0,0);     // Note: this default vector also can be others
}

void Triangle::CorrectNormal(Vector3d tagtNormal)
{
    // Compute initial normal
    ComputeNormal();

    // Rearrange vertex order if needed
    double dotp = normal.dot(tagtNormal);
    if ( dotp < 0 )
    {
        Vector3d triVers[3];
        for (int i=0; i<3; i++)
        {
            triVers[i] = v[i];
        }

        v[0] = triVers[0];
        v[1] = triVers[2];
        v[2] = triVers[1];
    }

    // Recompute the normal
    ComputeNormal();
}
