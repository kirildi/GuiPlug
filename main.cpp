// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#define GLFW_DLL
#define SK_GL

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <stdio.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "GuiPlugApp.h"

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char **)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) // initialize GLFW
        return 1;

    GUIPLUG::GuiPlugApp GUIPlugApp;

    GUIPlugApp.appRun(); // start main window

    return 0;
}
