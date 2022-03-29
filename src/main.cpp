///////////////////////////////////////////////////////////////
//
// main.cpp
//
//   A program for computational design of disassembly puzzles
//
// by Rulin Chen and Peng Song
//
// 29/May/2021
//
//
///////////////////////////////////////////////////////////////


#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include "Utility/HelpTypedef.h"
#include "Render/libigl_Render.h"
#include "Render/libigl_UI.h"
#include "Mesh/Mesh.h"


///////////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////////

// the viewer
iglViewer viewer;

// a menu plugin
igl::opengl::glfw::imgui::ImGuiMenu menu;

int winWidth;
int winHeight;
static bool isFirstCall;

bool showAxes;
bool showGround;
bool showPuzzle;
bool showPuzSkel;
bool showSmoothPuzzle;

float camPosX = 10;
float camPosY = 10;
float camPosZ = 10;


libigl_Render myRender;

///////////////////////////////////////////////////////////////
// Function Declarations
///////////////////////////////////////////////////////////////

void InitSetting();
void InitViewer();


///=========================================================================================///
///                                       Initialization
///=========================================================================================///

void InitSetting()
{
    winWidth          =  1600;
    winHeight         =  1000;

    isFirstCall       =  true;

    showAxes          =  false;
    showGround        =  false;
    showPuzzle        =  true;
    showPuzSkel       =  true;
    showSmoothPuzzle  =  true;
}

void InitViewer()
{
    ///set animation
    viewer.core().animation_max_fps = 45.;
    viewer.core().is_animating = true;
    viewer.core().background_color = RowVector4f (1,1,1,0);
    viewer.core().set_rotation_type(igl::opengl::ViewerCore::ROTATION_TYPE_TRACKBALL); // For Trackball rotation setting
}




///=========================================================================================///
///                                       Interaction
///=========================================================================================///

bool key_down(iglViewer &Viewer, unsigned char key, int modifier)
{
    if (key == ' ')
    {
        Viewer.core().is_animating = !Viewer.core().is_animating;
    }

    if (key == '+')
    {
        float sensitivity = 1;
        camPosX += sensitivity;
        camPosY += sensitivity;
        camPosZ += sensitivity;
    }


    return false;
}




///=========================================================================================///
///                                       Main Function
///=========================================================================================///

int main(int argc, char *argv[])
{

    setViewerUI(viewer);

    InitViewer();

    InitSetting();

    myRender.RenderScene( viewer);

    viewer.callback_pre_draw =
            [&](igl::opengl::glfw::Viewer &)
            {
                myRender.ShowGround( viewer, showGround );
                myRender.ShowAxes(viewer, showAxes );
                myRender.ShowPuzzle(viewer, showPuzzle);
                myRender.ShowPuzzleSkeleton(viewer, showPuzSkel);
                myRender.ShowSmoothPuzzle(viewer, showSmoothPuzzle);

                if(isFirstCall)
                {
                    myRender.SetCamera( viewer, 0.1, Vector3f (10, 10, 10) );
                    isFirstCall = false;
                }

                return 0;
            };

    viewer.callback_key_down = &key_down;

    viewer.launch(true,false,"High-LevelPuzzle", winWidth, winHeight);

    return 1;
}

