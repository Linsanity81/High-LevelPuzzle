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


#ifndef _LIBIGL_UI_H
#define _LIBIGL_UI_H

//#include <igl/opengl/glfw/Viewer.h>

namespace igl
{namespace opengl
    {namespace glfw {
            class Viewer;
        }}}

//// manage all UI here
void setViewerUI(igl::opengl::glfw::Viewer &viewer);

/// to show tips hovering on the UI items
static void HelpMarker(const char* desc);
void StatusBar();

#endif // _LIBIGL_UI_H