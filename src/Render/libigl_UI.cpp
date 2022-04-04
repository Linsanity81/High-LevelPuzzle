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
#include "Puzzle/PuzAction.h"
#include "libigl_UI.h"
#include "libigl_Render.h"
#include "Puzzle/Piece.h"



///////////////////////////////////////////////////////////////
// Puzzle Related Variables
///////////////////////////////////////////////////////////////

// Puzzle
int pieceNum = 4;
int firstLevel = 4;
int seedNum = 50;
int firstLevel_Iter = 12;
float puzTolerance = 0;
int disassStateID = 0;
float variance = 0;

// Input volume or puzzle file name (.vol or .puz)
string inputFileName;

// Piece Remove Mode
bool isFixLastPiece = false;

Puzzle myPuzzle;
Puzzle myPuzzle_Iter;

extern iglViewer viewer;
extern igl::opengl::glfw::imgui::ImGuiMenu menu;
extern libigl_Render myRender;

extern bool showAxes;
extern bool showPuzzle;
extern bool showPuzSkel;
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

            ImGui::Text("Level of Difficulty");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##Level of Difficulty", &firstLevel);

            ImGui::Text("Seed Number");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##Seed Number", &seedNum);

            ImGui::Text("Puzzle Tolerance");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragFloat("##Puzzle Tolerance", &puzTolerance);
        }

        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));

        ///////////////////////////////////////////////////////////////////////////
        //// High Level Puzzle Creator
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("High Level Puzzle Constructor", ImGuiTreeNodeFlags_DefaultOpen))
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

            if (ImGui::Button("Construct", ImVec2(button_width, 0)))
            {
                if (inputFileName.empty() == true)
                {
                    printf("Please import a puzzle volume first\n");
                    return;
                }

                srand( seedNum );

                PuzzleCreator myPuzzleCreator;
                myPuzzleCreator.InitPuzzleCreator( myPuzzle.volume );
                myPuzzle = *myPuzzleCreator.CreateBuildablePuzzle(pieceNum, firstLevel, isFixLastPiece, variance);
                printf("myPuzzle generationTime: %.3f\n", myPuzzle.generationTime);
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

            if (ImGui::Button("Reset", ImVec2(button_width, 0)))
            {
                if (myPuzzle.pieceList.size() != 0)
                    myRender.RenderPuzzle(viewer, myPuzzle, 0);
            }
        }

        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));

        ///////////////////////////////////////////////////////////////////////////
        //// High Level Puzzle Creator -- Iterative
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Modify High Level Puzzle", ImGuiTreeNodeFlags_OpenOnArrow)) {
            //// gap between the button group and head
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            ////////////////////////////////////////////////////////////////////
            //// model&shell&parts related
            //// buttons for model/shell IO/generate

            ImGui::Text("Target Level (Modify)");
            ImGui::SameLine(half_width * 1.2, p);
            ImGui::SetNextItemWidth(half_width * 0.8);
            ImGui::DragInt("##Target Level (Modify)", &firstLevel_Iter);

            ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));

//            ImGui::SameLine(half_width * 0.5, p);

            if (ImGui::Button("Modify", ImVec2(button_width, 0))) {
                if (inputFileName.empty() == true) {
                    printf("Please import a puzzle volume first\n");
                    myRender.RenderPuzzle(viewer, myPuzzle, disassStateID);
                }

                ImGui::Dummy(ImVec2(0.0f, 3.0f));
                ImGui::Dummy(ImVec2(0.0f, gap_between_paraGroups));
            }
        }

        ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));

        ///////////////////////////////////////////////////////////////////////////
        //// Assembly Tree State Viewer
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Assembly State Viewer", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));

            ImGui::Text("Disassembly Step");
            ImGui::SameLine(half_width, p);
            ImGui::SetNextItemWidth(half_width);
            ImGui::DragInt("##Disassembly Step", &disassStateID);

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

        ///////////////////////////////////////////////////////////////////////////
        //// Render Control
        ///////////////////////////////////////////////////////////////////////////

        if (ImGui::CollapsingHeader("Render Control", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));
            float gap_between_renderGroups = 4.0f;
            float half_width = (w - p) / 2.f;

            ImGui::Dummy(ImVec2(0.0f, gap_between_renderGroups));
            ImGui::SetWindowFontScale(1);

            ImGui::Text("Show Axes");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Axes", &showAxes);

            ImGui::Text("Show Puzzle");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Puzzle", &showPuzzle);

            ImGui::Text("Show Ball Skeleton");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Ball Skeleton", &showPuzSkel);

            ImGui::Text("Show Smooth Puzzle");
            ImGui::SameLine(half_width * 1.5, p);
            ImGui::Checkbox("##Show Smooth Puzzle", &showSmoothPuzzle);

            ImGui::Dummy(ImVec2(0.0f, gap_between_renderGroups));

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
    else if(myPuzzle.puzLockState == PUZZLE_DEAD_LOCK)          puzzleState = (char*)"Deadlocking";
    else if(myPuzzle.puzLockState == PUZZLE_INTER_LOCK)         puzzleState = (char*)"Interlocking";

    ImGui::Text("Puzzle State: %s", puzzleState);

    ImGui::Text("Level of Difficulty: %d", myPuzzle.puzLevel);
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
