cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


#PUGIXML
find_package(PUGIXML REQUIRED)

#LIBIGL
find_package(LIBIGL REQUIRED QUIET)
if(LIBIGL_FOUND)
    add_definitions(-DLIBIGL_FOUND=1)
endif()

set(ext_include
        ${PUGIXML_INCLUDE_DIR}
        ${LIBIGL_INCLUDE_DIR}
        PARENT_SCOPE)

set(ext_lib pugixml
        igl::core
        igl::cgal
        igl::opengl_glfw
        igl::opengl_glfw_imgui
        PARENT_SCOPE)