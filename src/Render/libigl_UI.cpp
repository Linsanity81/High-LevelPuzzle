///////////////////////////////////////////////////////////////
//
// libigl_UI.h
//
//   User interface with libigl
//
// by Rulin Chen and Peng Song
//
// 22/Aug/2021
//
//
///////////////////////////////////////////////////////////////


#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include "Utility/HelpTypedef.h"
#include "Utility/HelpPuz.h"
#include "Puzzle/Volume.h"
#include "Puzzle/Puzzle.h"
#include "Puzzle/PuzzleCreator.h"
#include "Puzzle/PieceCreator.h"
#include "Puzzle/PuzAction.h"
#include "libigl_UI.h"
#include "libigl_Render.h"
#include "Puzzle/Piece.h"
#include "Puzzle_debug/Puzzle_debug.h"
#include "Puzzle/PuzCreator_Iter.h"
#include "Puzzle/Puzzle_smooth.h"
#include "Mesh/MeshObject.h"
#include "Mesh/MeshBoolean.h"
#include "Mesh/MeshCreator.h"
#include "Mesh/Mesh.h"



///////////////////////////////////////////////////////////////
// Puzzle Related Variables
///////////////////////////////////////////////////////////////

// Puzzle
int pieceNum = 4;
int firstLevel = 4;
int seedNum = 50;
int firstLevel_Iter = 12;
int k_Value = 1;
float timeCreator = 0.5;
float timeIter = 0.5;
float convergenceTime = 0.5;
float emptyThreshold = 0.01;
float fullThreshold = 0.1;

float puzTolerance = 0;
int disassStateID = 0;
float variance = 0;

// Input volume or puzzle file name (.vol or .puz)
string inputFileName;
//string inputFileName_Iter;

// Piece Remove Mode
bool isFixLastPiece = false;

// For Consturction Framework Debug
int pieceID_debug = 0;
Puzzle_debug myPuzzle_debug;

// Smooth Shape Input
Eigen::MatrixXd V_smooth;
Eigen::MatrixXi F_smooth;

Eigen::MatrixXd V_prob;
Eigen::MatrixXi F_prob;

extern bool showContaVoxels;
extern bool showSeedVoxels;
extern bool showSeedKeptVoxels;
extern bool showSeedPathVoxels;
extern bool showBlockVoxels;
extern bool showBlockKeptVoxels;
extern bool showBlockPathVoxels;
extern bool showExtdVoxels;

Puzzle myPuzzle;
Puzzle tempPuzzle_debug;
Puzzle myPuzzle_Iter;

Puzzle_smooth myPuzzle_smooth;

extern iglViewer viewer;
extern igl::opengl::glfw::imgui::ImGuiMenu menu;
extern libigl_Render myRender;

extern bool showAxes;
extern bool showGround;
extern bool showPuzzle;
extern bool showPuzSkel;
extern bool showDisconnectedEdges;
extern bool showSmoothPuzzle;

///=========================================================================================///
///                                      Set Viewer UI
///=========================================================================================///

//// UI main function
void setViewerUI(igl::opengl::glfw::Viewer &viewer)
{
    menu.callback_draw_viewer_window = [&]()
    {
        //// color preset:
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);

        ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.50f);
        ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.50f);

        ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

        ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

        //ImGui::TextWrapped();
        //// Define window position + size
        float menu_width = 240.f * menu.menu_scaling();

        //// Warning: do get the true windows width to relocate the menu, the viewer using highdpi (see Viewer.cpp to support highdpi display）
        int width_window, height_window;
        glfwGetWindowSize(viewer.window,&width_window, &height_window);

        ImGui::SetNextWindowPos(ImVec2(width_window - menu_width, 0.0f),ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSizeConstraints(ImVec2(menu_width, -1.0f), ImVec2(menu_width, -1.0f));
        bool _viewer_menu_visible = true;
        ImGui::Begin(
                "Control Panel", &_viewer_menu_visible,
                ImGuiWindowFlags_NoSavedSettings
        );
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.4f);
        if (menu.callback_draw_viewer_menu) { menu.callback_draw_viewer_menu(); }
        ImGui::PopItemWidth();
        ImGui::End();
    };


    // Add content to the default menu window
    menu.callback_draw_viewer_menu = [&]()
    {
        //// global styles of UI
        float w = ImGui::GetContentRegionAvailWidth();
        float p = ImGui::GetStyle().FramePadding.x;
        float gap_between_controlGroups = 4.0f;

        float button_verticalGap = 2.0f;
        float button_horizontalGap = 4*p;
        float button_width = (w-button_horizontalGap)/2.f;

        float head_scale = 1.3f;
        float gap_between_paraGroups = 8.0f;
        float half_width = (w - p) / 2.f;

        ///////////////////////////////////////////////////////////////////////////
        //// Parameter Control
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Parameter Control", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            //// shell parameter setting sliders here:
            ImGui::Text("Piece Number");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##Piece Number", &pieceNum);

            ImGui::Text("First Level");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##First Level", &firstLevel);

            ImGui::Text("Seed Number");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##Seed Number", &seedNum);

            ImGui::Text("Puzzle Tolerance");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragFloat("##Puzzle Tolerance", &puzTolerance);

            ImGui::Text("Piece Number Variance");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragFloat("##Piece Number Variance", &variance);

            ImGui::Text("Fix Last Piece");
            ImGui::SameLine(half_width * 1.2, p);
            ImGui::Checkbox("##Fix Last Piece", &isFixLastPiece);

//            ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));
        }

        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));


        ///////////////////////////////////////////////////////////////////////////
        //// Status Bar
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Status Bar", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            StatusBar();
        }
        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));

        ///////////////////////////////////////////////////////////////////////////
        //// Smooth Shape Puzzle Reader
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Smooth Shape Reader", ImGuiTreeNodeFlags_DefaultOpen)) {
            //// gap between the button group and head
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            ////////////////////////////////////////////////////////////////////
            //// model&shell&parts related
            //// buttons for model/shell IO/generate

//            ImGui::Text("Empty Voxel Threshold");
//            ImGui::SameLine(half_width, p);
//            ImGui::SetNextItemWidth(half_width);
//            ImGui::DragFloat("##Empty Voxel Threshold", &emptyThreshold);

            ImGui::Text("Full Voxel Threshold");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragFloat("##Full Voxel Threshold", &fullThreshold);

            ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));

            if (ImGui::Button("Read Smooth Input", ImVec2(button_width, 0))) {
                inputFileName = igl::file_dialog_open();

                if( inputFileName.empty() == true )
                    return;

                myPuzzle_smooth.ReadSmoothPuzzleFile(inputFileName);
                myPuzzle_smooth.InitPuzzle_smooth(emptyThreshold, fullThreshold);

                myPuzzle.ClearPuzzle();

                vector<vector <int>> connectivityEdgeList;
                myPuzzle.InitPuzzle(myPuzzle_smooth.initVolumeSize, myPuzzle_smooth.initVoxelSize, myPuzzle_smooth.attachVoxelList, connectivityEdgeList);

                myPuzzle.CheckPuzzleState(true, isFixLastPiece);

                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);

            }

            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Attach Voxels", ImVec2(button_width, 0))) {
                vector<int> currPuzzleData = myPuzzle.ExtractPuzzleData();

                srand( seedNum );

                myPuzzle = *myPuzzle_smooth.AttachVoxel(currPuzzleData, myPuzzle.pieceList.size());

                myPuzzle.CheckPuzzleState(true, isFixLastPiece);

                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
            }

            ImGui::Dummy(ImVec2(0.0f, 3.0f));

            if (ImGui::Button("Read Smooth Shape", ImVec2(button_width, 0)))
            {
                string currFileName = igl::file_dialog_open();

                if( currFileName.empty() == true )
                    return;

                printf( "%s\n", currFileName.c_str());

                igl::readOBJ(currFileName, V_smooth, F_smooth);
            }

            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Save Smooth Puz", ImVec2(button_width, 0)))
            {
                string outputFolderPath = igl::file_dialog_save();
                if( outputFolderPath.empty() == true )
                    return;

                printf( "%s\n", outputFolderPath.c_str());

                if (V_smooth.rows() == 0 or F_smooth.rows() == 0)
                {
                    cout << "No Smooth Shape Loaded." << endl;
                    return;
                }

                MeshBoolean meshBoolean;

                size_t foundFolder = outputFolderPath.find_last_of('/'); // Note: this applies for Mac only
                outputFolderPath = outputFolderPath.substr(0, foundFolder);

                for (int i = 0; i < myPuzzle.pieceList.size(); ++i)
                {
                    string currVoxelizedPiecePath = outputFolderPath + "/piece" + to_string(i+1) + ".obj";

                    Eigen::MatrixXd V;
                    Eigen::MatrixXi F;

                    igl::readOBJ(currVoxelizedPiecePath, V, F);

                    Eigen::MatrixXd V_csg;
                    Eigen::MatrixXi F_csg;

                    meshBoolean.MeshIntersect(V, F, V_smooth, F_smooth, V_csg, F_csg);

                    string currSmoothPiecePath = outputFolderPath + "/smooth_piece" + to_string(i+1) + ".obj";

                    Mesh * currPieceMesh = new Mesh();
                    currPieceMesh->verM = V_csg;
                    currPieceMesh->triM = F_csg;

//                    currPieceMesh->ReverseNormal();

                    igl::writeOBJ(currSmoothPiecePath, currPieceMesh->verM, currPieceMesh->triM);
                }
            }

            ImGui::Dummy(ImVec2(0.0f, 3.0f));

            if (ImGui::Button("Read ProbVoxel", ImVec2(button_width, 0)))
            {
                string currFileName = igl::file_dialog_open();

                if( currFileName.empty() == true )
                    return;

                Eigen::MatrixXd V;
                Eigen::MatrixXi F;

                igl::readOBJ(currFileName, V, F);

//                cout << F << endl;

                double radius = 0.001;
                int radSamp = 20;

                for (int i = 0; i < F.rows(); i++)
                {
                    for (int j = 0; j < 4; j++ )
                    {
                        vector<int> faceVerticeIDList;
                        faceVerticeIDList.push_back(F(i,0));
                        faceVerticeIDList.push_back(F(i,1));
                        faceVerticeIDList.push_back(F(i,2));
                        faceVerticeIDList.push_back(F(i,3));

                        Vector3d v1;
                        Vector3d v2;

                        if (j == 0)
                        {
                            v1 = Vector3d(V(faceVerticeIDList[0], 0), V(faceVerticeIDList[0], 1), V(faceVerticeIDList[0], 2));
                            v2 = Vector3d(V(faceVerticeIDList[1], 0), V(faceVerticeIDList[1], 1), V(faceVerticeIDList[1], 2));
                        }

                        if (j == 1)
                        {
                            v1 = Vector3d(V(faceVerticeIDList[2], 0), V(faceVerticeIDList[2], 1), V(faceVerticeIDList[2], 2));
                            v2 = Vector3d(V(faceVerticeIDList[1], 0), V(faceVerticeIDList[1], 1), V(faceVerticeIDList[1], 2));
                        }

                        if (j == 2)
                        {
                            v1 = Vector3d(V(faceVerticeIDList[2], 0), V(faceVerticeIDList[2], 1), V(faceVerticeIDList[2], 2));
                            v2 = Vector3d(V(faceVerticeIDList[3], 0), V(faceVerticeIDList[3], 1), V(faceVerticeIDList[3], 2));
                        }

                        if (j == 3)
                        {
                            v1 = Vector3d(V(faceVerticeIDList[0], 0), V(faceVerticeIDList[0], 1), V(faceVerticeIDList[0], 2));
                            v2 = Vector3d(V(faceVerticeIDList[3], 0), V(faceVerticeIDList[3], 1), V(faceVerticeIDList[3], 2));
                        }

                        MeshCreator meshCreator;

                        Mesh * currMesh = meshCreator.CreateCylinder(v1, v2, radius, radSamp);

                        Eigen::MatrixXd tempV(V_prob.rows()+currMesh->verM.rows(), 3);
                        tempV << V_prob,
                                  currMesh->verM;

                        V_prob = tempV;

                        for (int k = 0; k < currMesh->triM.rows(); ++k)
                        {
                            currMesh->triM(k, 0) += V_prob.rows();
                            currMesh->triM(k, 1) += V_prob.rows();
                            currMesh->triM(k, 2) += V_prob.rows();
                        }

                        Eigen::MatrixXi tempF(F_prob.rows()+currMesh->triM.rows(), 3);
                        tempF << F_prob,
                                    currMesh->triM;

                        F_prob = tempF;

                    }
                }
            }

            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Save ProbVoxel", ImVec2(button_width, 0)))
            {
                string outputFolderPath = igl::file_dialog_save();
                if( outputFolderPath.empty() == true )
                    return;

                igl::writeOBJ(outputFolderPath + ".obj", V_prob, F_prob);
                cout << outputFolderPath << endl;
            }
        }


        ///////////////////////////////////////////////////////////////////////////
        //// High Level Puzzle Creator
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("High Level Puzzle Creator", ImGuiTreeNodeFlags_DefaultOpen))
        {
            //// gap between the button group and head
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            ////////////////////////////////////////////////////////////////////
            //// model&shell&parts related
            //// buttons for model/shell IO/generate

            if (ImGui::Button("Read", ImVec2(button_width, 0)))
            {
                inputFileName = igl::file_dialog_open();
                if( inputFileName.empty() == true )
                    return;

                myPuzzle.ReadPuzzleFile(inputFileName);

                myPuzzle.ReadSmoothPuzzleFile(inputFileName);

                myPuzzle.CheckPuzzleState(true, isFixLastPiece);

                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
            }
            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Create", ImVec2(button_width, 0)))
            {
                if (inputFileName.empty() == true)
                {
                    printf("Please import a puzzle volume first\n");
                    return;
                }

                srand( seedNum );

                PuzzleCreator myPuzzleCreator;
                myPuzzleCreator.InitPuzzleCreator( myPuzzle.volume );
                myPuzzle = *myPuzzleCreator.CreateBuildablePuzzle(pieceNum, firstLevel, myPuzzle_debug, isFixLastPiece, variance);
                printf("myPuzzle generationTime: %.3f\n", myPuzzle.generationTime);
                //myPuzzle = *myPuzzleCreator.CreateBuildablePuzzle(pieceNum, firstLevel);
                // myPuzzleCreator.CreateBuildablePuzzle_new(pieceNum, firstLevel);
                myPuzzle.CheckPuzzleState(true, isFixLastPiece);

                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
            }

            ImGui::Dummy(ImVec2(0.0f, 3.0f));

            if (ImGui::Button("Save Puz", ImVec2(button_width, 0)))
            {
                string outputFolderPath = igl::file_dialog_save();
                if( outputFolderPath.empty() == true )
                    return;

                printf( "%s\n", outputFolderPath.c_str());

                myPuzzle.SavePuzzleFiles(outputFolderPath, puzTolerance, isFixLastPiece);
            }

            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Check Puz", ImVec2(button_width, 0)))
            {
                if (myPuzzle.pieceList.size() != 0)
                    myPuzzle.CheckPuzzleState( true, isFixLastPiece );
            }

            ImGui::Dummy(ImVec2(0.0f, 3.0f));

            if (ImGui::Button("Display", ImVec2(button_width, 0)))
            {
                if (myPuzzle.pieceList.size() != 0)
                {
                    myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
                }
            }

            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Clear", ImVec2(button_width, 0)))
            {
                myRender.ClearViewer( viewer );
            }

            ImGui::Dummy(ImVec2(0.0f, 3.0f));

            if (ImGui::Button("Reset", ImVec2(button_width, 0)))
            {
                if (myPuzzle.pieceList.size() != 0)
                    myRender.RenderPuzzle(viewer, myPuzzle, 0);
            }

            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Update Graph", ImVec2(button_width, 0)))
            {
//                std::cout << inputFileName << std::endl;
                size_t foundFolder = inputFileName.find_last_of('/');
                string folderName = inputFileName.substr(0, foundFolder + 1);
                std::cout << folderName << std::endl;

                myPuzzle.UpdateKernelGraph(folderName);

//                PuzSolver puzSolver;
//                puzSolver.InitPuzSolver(myPuzzle.pieceList, myPuzzle.volume->GetVolumeSize(), 2);
//                puzSolver.DisassemblyPuzzzle_Graph(DISASS_FIX_LAST_PIECE, graphPuzConfigs, pathPuzConfigs, currLevel);
//                puzSolver.ComputeDisassemblyPlan(pathPuzConfigs, puzActions, isFixLastPiece);
            }

            ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));
        }

        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));

        ///////////////////////////////////////////////////////////////////////////
        //// High Level Puzzle Creator -- Iterative
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Iterative High Level Puzzle Creator", ImGuiTreeNodeFlags_DefaultOpen)) {
            //// gap between the button group and head
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            ////////////////////////////////////////////////////////////////////
            //// model&shell&parts related
            //// buttons for model/shell IO/generate

            ImGui::Text("First Level - Iter");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##First Level - Iter", &firstLevel_Iter);

            ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));

            if (ImGui::Button("Create_Iter", ImVec2(button_width, 0))) {
                if (inputFileName.empty() == true) {
                    printf("Please import a puzzle volume first\n");
                    return;
                }

                srand(seedNum);

                PuzCreator_Iter myPuzCreator_Iter;
                myPuzCreator_Iter.InitPuzzleCreator_Iter(&myPuzzle);
                myPuzzle = *myPuzCreator_Iter.CreateBuildablePuzzle_Iter(firstLevel_Iter, convergenceTime);

                myPuzzle.CheckPuzzleState(true, isFixLastPiece);

                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
            }


            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Save Puz - Iter", ImVec2(button_width, 0))) {
                string outputFolderPath = igl::file_dialog_save();
                if (outputFolderPath.empty() == true)
                    return;

                printf("%s\n", outputFolderPath.c_str());

                myPuzzle.SavePuzzleFiles(outputFolderPath, puzTolerance, isFixLastPiece);
            }

            ImGui::Dummy(ImVec2(0.0f, 3.0f));
        }

        ///////////////////////////////////////////////////////////////////////////
        //// High Level Puzzle Creator -- Combined
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Combined High Level Puzzle Creator", ImGuiTreeNodeFlags_DefaultOpen)) {
            //// gap between the button group and head
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            ////////////////////////////////////////////////////////////////////
            //// model&shell&parts related
            //// buttons for model/shell IO/generate

            ImGui::Text("k Value");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##k Value", &k_Value);

            ImGui::Text("Creator Time Limit");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragFloat("##Creator Time Limit", &timeCreator);

            ImGui::Text("Iterator Time Limit");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragFloat("##Iterator Time Limit", &timeIter);

            ImGui::Text("Convergence Time");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragFloat("##Convergence Time", &convergenceTime);

            if (ImGui::Button("Create_Combined", ImVec2(button_width, 0))) {
                if (inputFileName.empty() == true) {
                    printf("Please import a puzzle volume first\n");
                    return;
                }

                srand(seedNum);

                PuzzleCreator myCombinedPuzzleCreator;
                vector< vector<int> > puzzleCandidates;
                bool isNeedModification = true;
                vector<vector <int>> connectivityEdgeList;

                clock_t beginTime = clock();
                clock_t endTime;
                float elapsed;

                myCombinedPuzzleCreator.InitPuzzleCreator( myPuzzle.volume );
                puzzleCandidates = myCombinedPuzzleCreator.CreateBuildablePuzzle_creator(pieceNum, firstLevel, isFixLastPiece, variance, timeCreator, k_Value, isNeedModification);

                if (!isNeedModification)
                {
                    myPuzzle.InitPuzzle(myPuzzle.volume->volumeSize, myPuzzle.volume->voxelSize, puzzleCandidates[0], connectivityEdgeList);
                }

                else
                {
                    for (int i = 0; i < puzzleCandidates.size(); ++i)
                    {
                        Puzzle tempPuzzle;
                        tempPuzzle.InitPuzzle(myPuzzle.volume->volumeSize, myPuzzle.volume->voxelSize, puzzleCandidates[i], connectivityEdgeList);

                        PuzCreator_Iter myPuzCreator_Iter;
                        myPuzCreator_Iter.InitPuzzleCreator_Iter(&tempPuzzle);

                        tempPuzzle = *myPuzCreator_Iter.CreateBuildablePuzzle_Iter(firstLevel, convergenceTime, timeIter);

                        if (tempPuzzle.puzLevel > myPuzzle.puzLevel)
                        {
                            myPuzzle = tempPuzzle;
                        }

                        if (myPuzzle.puzLevel >= firstLevel)
                            break;
                    }
                }

                // Record the complete time
                endTime = clock();
                elapsed = ((float) (endTime - beginTime)) / (60.0f*CLOCKS_PER_SEC);

                myPuzzle.generationTime = elapsed;
                printf("\nThe time taken to create buildable puzzle is %.3f mins \n\n", elapsed);

                myPuzzle.CheckPuzzleState(false, true);
                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
            }

            ImGui::SameLine(0, button_horizontalGap);

            if (ImGui::Button("Save Puz - Combined", ImVec2(button_width, 0))) {
                string outputFolderPath = igl::file_dialog_save();
                if (outputFolderPath.empty() == true)
                    return;

                printf("%s\n", outputFolderPath.c_str());

                myPuzzle.SavePuzzleFiles(outputFolderPath, puzTolerance, isFixLastPiece);
            }

            ImGui::Dummy(ImVec2(0.0f, 3.0f));
        }

        ///////////////////////////////////////////////////////////////////////////
        //// Assembly Tree State Viewer
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Assembly Tree State Viewer", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            ImGui::Text("Node Index");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##Node Index", &disassStateID);

            ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));
        }

        if (ImGui::Button("Prev", ImVec2(button_width, 0)))
        {
            if (disassStateID > 0)
            {
                disassStateID --;
                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
            }
        }

        ImGui::SameLine(0, button_horizontalGap);

        if (ImGui::Button("Next", ImVec2(button_width, 0)))
        {
            if (disassStateID < myPuzzle.puzActionList.size())
            {
                disassStateID++;
                myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
            }
        }

        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));

        /////////////////////////////////////////////////////////////////////////////
        //// Construction Framework Viewer
        /////////////////////////////////////////////////////////////////////////////

//        if (ImGui::CollapsingHeader("Construction Framework Viewer", ImGuiTreeNodeFlags_DefaultOpen)) {
//            ImGui::Dummy(ImVec2(0.0f, 2.0f));
//
//            ImGui::Text("Piece Index");
//            ImGui::SameLine(half_width, p);
//            ImGui::SetNextItemWidth(half_width);
//            ImGui::DragInt("##Piece Index", &pieceID_debug);
//
//            ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));
//            ImGui::SetWindowFontScale(1);
//
//            ImGui::Text("Show Conta Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Conta Voxels", &showContaVoxels);
//
//            ImGui::Text("Show Seed Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Seed Voxels", &showSeedVoxels);
//
//            ImGui::Text("Show Seed Kept Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Seed Kept Voxels", &showSeedKeptVoxels);
//
//            ImGui::Text("Show Seed Path Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Seed Path Voxels", &showSeedPathVoxels);
//
//            ImGui::Text("Show Block Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Block Voxels", &showBlockVoxels);
//
//            ImGui::Text("Show Block Kept Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Block Kept Voxels", &showBlockKeptVoxels);
//
//            ImGui::Text("Show Block Path Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Block Path Voxels", &showBlockPathVoxels);
//
//            ImGui::Text("Show Extd Voxels");
//            ImGui::SameLine(half_width * 1.2, p);
//            ImGui::Checkbox("##Show Extd Voxels", &showExtdVoxels);
//
//            ImGui::Dummy(ImVec2(0.0f, 3.0f));
//
//            if (ImGui::Button("Display Debug Info", ImVec2(button_width, 0)))
//            {
//
//                if (myPuzzle.pieceList.size() != 0)
//                {
//                    if (myPuzzle_debug.piece_debug_List.size() == 0)
//                    {
//                        printf("No construction information stored.\n");
//                    }
//                    else if (pieceID_debug > myPuzzle_debug.piece_debug_List.size() - 1)
//                    {
//                        printf("Piece ID is out of range.\n");
//                    }
//                    else
//                    {
////                        RenderPuzzle_debug(viewer, myPuzzle_debug, pieceID_debug, myPuzzle);
//                        myRender.RenderPuzzle_debug(viewer, myPuzzle_debug, pieceID_debug, myPuzzle);
//                    }
//                }
//
//            }
//
//            ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));
//        }

        ///////////////////////////////////////////////////////////////////////////
        //// Render Control
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Render Control", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));
            float head_scale = 1.3f;
            float gap_between_renderGroups = 4.0f;
            float half_width = (w - p) / 2.f;
            float transparency;

            ImGui::Dummy(ImVec2(0.0f, gap_between_renderGroups));
            ImGui::SetWindowFontScale(1);

            ImGui::Text("Show Ground");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Ground", &showGround);

            ImGui::Text("Show Axes");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Axes", &showAxes);

            ImGui::Text("Show Puzzle");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Puzzle", &showPuzzle);

            ImGui::Text("Show Ball Skeleton");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Ball Skeleton", &showPuzSkel);

            ImGui::Text("Show Disconnected Edges");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Disconnected Edges", &showDisconnectedEdges);

            ImGui::Text("Show Smooth Puzzle");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Smooth Puzzle", &showSmoothPuzzle);

            ImGui::Dummy(ImVec2(0.0f, gap_between_renderGroups));

        }
        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));
    };

    viewer.plugins.push_back(&menu);
    viewer.data().face_based = true;
    viewer.core().background_color.setConstant(1.0f);
}




///=========================================================================================///
///                                     Computation Functions
///=========================================================================================///

void StatusBar()
{
    char *puzzleState;

    if (myPuzzle.puzLockState == PUZZLE_LOCK_UNKNOWN)           puzzleState = (char*)"Unknown";
    else if(myPuzzle.puzLockState == PUZZLE_GROUP_MOVE)         puzzleState = (char*)"Group Move";
    else if(myPuzzle.puzLockState == PUZZLE_PIECE_MOVE)         puzzleState = (char*)"Piece Move";
    else if(myPuzzle.puzLockState == PUZZLE_PIECE_MOVE)         puzzleState = (char*)"Piece Move";
    else if(myPuzzle.puzLockState == PUZZLE_DEAD_LOCK)          puzzleState = (char*)"Deadlocking";
    else if(myPuzzle.puzLockState == PUZZLE_INTER_LOCK)         puzzleState = (char*)"Interlocking";

    char *puzzleBuildState;

    if (myPuzzle.puzBuildState == PUZZLE_BUILD_UNKNOWN)         puzzleBuildState = (char*)"Unknown";
    else if(myPuzzle.puzBuildState == PUZZLE_NOT_BUILDABLE)     puzzleBuildState = (char*)"Puzzle Not Buildable";
    else if(myPuzzle.puzBuildState == PUZZLE_NOT_BUILD_GROUP)   puzzleBuildState = (char*)"Puzzle Not Build Group";
    else if(myPuzzle.puzBuildState == PUZZLE_NO_REMOVE_GROUP)   puzzleBuildState = (char*)"Puzzle No Remove Group";
    else if(myPuzzle.puzBuildState == PUZZLE_NORMAL_BUILDABLE)  puzzleBuildState = (char*)"Puzzle Normal Buildable";
    else if(myPuzzle.puzBuildState == PUZZLE_STRICT_BUILDABLE)  puzzleBuildState = (char*)"Puzzle Strict Buildable";

    char *disconnectivityState;
    if (myPuzzle.puzDisconnectivityState)               disconnectivityState = (char*)"Fulfilled";
    else                                                disconnectivityState = (char*)"Not Fulfilled";

    string fileName = inputFileName;

    for (int i = fileName.size() - 1; i > 0; --i)
    {
        if (fileName[i] == '/')
        {
            fileName.erase(fileName.begin(), fileName.begin() + i + 1);
            break;
        }
    }

    ImGui::Text("   File Name: %s", fileName.c_str());

    ImGui::Text("Puzzle State: %s", puzzleState);

    ImGui::Text(" Build State: %s", puzzleBuildState);

    ImGui::Text("Puzzle Level: %d", myPuzzle.puzLevel);

    ImGui::Text(" Total Moves: %lu", myPuzzle.puzActionList.size());

    ImGui::Text("DissComplexity: %d", myPuzzle.dissComplexity);

    ImGui::Text("Disconnectivity Status: %s", disconnectivityState);
}


static void HelpMarker(const char* desc)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
