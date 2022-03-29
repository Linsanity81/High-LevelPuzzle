///////////////////////////////////////////////////////
//HelpFunc.h
//
// Additional Functions
//
// Created by Yingjie Cheng on 2020/11/05.
//
////////////////////////////////////////////////////////

#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <vector>
#include "HelpStruct.h"

using namespace std;
using namespace Eigen;

#ifndef vec
#define vec Vector3d
#endif

///////////////////////////////////////////////////////////////
// Define Variables
///////////////////////////////////////////////////////////////

/// Default element ID
#define ELEMENT_OUT_LIST            -1
#define HEAP_SORT_Type            double


///////////////////////////////////////////////////////////////
// Function Declaration
///////////////////////////////////////////////////////////////

// String Operations
void GetFolderPath(string filePath, string &folderPath);
void GetFolderPath(const char filePath[], char folderPath[]);
string GetFileType(const char filePath[]);

// Mesh Volume
Box ComputeBBox(vector<Vector3d> verList, bool isPrint);
double ComputeMeshVolume(vector<Triangle*> triList);
double ComputeMeshVolume(vector<Triangle> triList);
Vector3d ComputeMeshCentroid(vector<Triangle*> triList);

// Area Calculation
double Area2DPolygon(vector<Vector3d> vertices);

// Distance
double PointLineDistance(const Vector3d& tagtPt, const Vector3d& endPt1, const Vector3d& endPt2);
double PointPlaneDistance(const Vector3d& tagtPt, const Vector3d& point, const Vector3d& normal);
double PointPolygonDistance(const Vector3d& p, vector<Vector3d> polyPoints);

// Projection
Vector3d ProjectPointToLine(const Vector3d& tagtPt, const Vector3d& linePt, Vector3d lineDir);
double ProjectPointToLine_Dist(const Vector3d& tagtPt, const Vector3d& linePt, Vector3d lineDir);
Vector3d ProjectPointToPlane(const Vector3d& tagtPt, const Plane& plane);
Triangle* ProjectTriangleToPlane(Triangle *tri, const Plane& plane);

// Intersection
double LineHitTriangle(vec rayOrg, vec rayDir, const Triangle& triangle, vec &hitCoord, bool isPrint);
bool IsPointInsideTriangle(vec point, const Triangle& triangle, bool isPrint);
int TriTriIntersect(Triangle *meshTri, Triangle linkTri);
bool IsPointOnLine(const Vector3d& tagtPt, const Vector3d& linePt1, const Vector3d& linePt2);
double AngleBetweenVectors(Vector3d vec1, Vector3d vec2);

// Sorting and Search
vector<int> HeapSort(vector<HEAP_SORT_Type> &Array, bool isAscend);
void siftDown(vector<HEAP_SORT_Type> &Array, vector<int> &Indices, int start, int end, bool isAscend);
vector<int> BubbleSort(vector<double> &Array, bool isAscend);
vector<int> BubbleSort(vector<int> &Array, bool isAscend);
int GetElementIndexInList(vector<int> elementList, int targtElement);

// Vector(Col) and Matrix(Row major)
Vector4d liftVec(Vector3d vec3);
Vector4d liftVec(RowVector3d vec3);
Matrix3d GetRotationFromAffine(Matrix4d AffineM);
Matrix4d GetAffine(Matrix3d RotM);
Matrix4d GetAffine(Matrix3d RotM, Vector3d TransVec);
void MultiplyPoint(vec inPt, const Matrix4d& inMat, vec &outPt);
void MultiplyVector(vec inVec, Matrix4d inMat, vec &outVec);
void MultiplyNormal(vec inNor, const Matrix4d& inMat, vec &outNor);

Matrix4d GetTransformMatrix(Vector3d eulerAngles, Vector3d position);
Matrix4d GetRotationMatrix(double rotAngle, Vector3d rotAxis);
Matrix4d GetRotationMatrix(double rotAngle, Vector3d rotAxis, const Vector3d& rotCenter);
Matrix4d GetRotationMatrix(Vector3d eulerAngles);
Matrix4d GetTranslateMatrix(Vector3d transVec);
Matrix4d GetScaleMatrix(Vector3d scaleVec);

// Utility Function
double SolveEqua(double a, double b, double c);
double SolveEqua2(double a, double b, double c);
double SolvePointToCircleK1(double Pointx, double Pointy, double Cx, double Cy, double r);
double SolvePointToCircleK2(double Pointx, double Pointy, double Cx, double Cy, double r);
void UpIntersectionOfCircles(double ans[2], double O1_x, double O1_y, double O1_R, double O2_x, double O2_y, double O2_R);
void DownIntersectionOfCircles(double ans[2], double O1_x, double O1_y, double O1_R, double O2_x, double O2_y, double O2_R);
bool isIntersectOfCircles(double O1_x, double O1_y, double O1_R, double O2_x, double O2_y, double O2_R);

// Line To Cylinder
double DisPointToLine(const Vector3d& P0, const Vector3d& P1, Vector3d V1);
double DisLineToLine(const Vector3d& P1, Vector3d v1, const Vector3d& P2, Vector3d v2);
bool LineToCylinder(const Vector3d& P, Vector3d VL, const Vector3d& Q, Vector3d VC, double r, double &t1, double &t2);

//polyline
double ReturnInto2PI(double s);
int FindNeighbor(double s, int Nsize);
int FindNeighbor(double s, vector<double> paras);
void GetId(double s, int &id, int &id2, double &wL, double &wR, int NSize);
Vector3d GetPolyLine(double s, const vector<Vector3d> &pitchCurve);

#endif //HELPFUNC_H

