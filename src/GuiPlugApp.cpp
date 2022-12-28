#include "GuiPlugApp.h"

GUIPLUG::GuiPlugApp::GuiPlugApp() : glsl_version{"#version 130"}
{
      // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
      // GL ES 2.0 + GLSL 100
      glsl_version = "#version 100";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
      // GL 3.2 + GLSL 150
      glsl_version = "#version 150";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
      // GL 3.0 + GLSL 130
      glsl_version = "#version 130";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
      // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
}
void GUIPLUG::GuiPlugApp::appRun()
{
      platformWindow.glsl_version = glsl_version;

      while (!isAppFullyClosed)
      {
            windowSelector = platformWindow.windowSelector; // windows management state

            if (windowSelector == WindowSelector::MANAGER_WINDOW)
            {
                  platformWindow.setWidth(900);
                  platformWindow.setHeight(660);
                  platformWindow.setTitle("GUIPlug: Project Manager");
                  contentIndex = "manager";
            }
            if (windowSelector == WindowSelector::MAIN_WINDOW)
            {
                  platformWindow.setWidth(1660);
                  platformWindow.setHeight(900);
                  platformWindow.setTitle("GUIPlug: Plugin development platform");
                  contentIndex = "main";
            }

            auto isCreated = platformWindow.create();
            if (isCreated != nullptr)
            {
                  isAppFullyClosed = platformWindow.showContent(contentIndex);
            }
      }
}

GUIPLUG::GuiPlugApp::~GuiPlugApp()
{
}