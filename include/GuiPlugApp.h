#ifndef GUI_PLUG_APP_H
#define GUI_PLUG_APP_H

#pragma once

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

#include "Enums.h"
#include "PlatformWindow.h"

namespace GUIPLUG
{
      class GuiPlugApp
      {
      public:
            GuiPlugApp();
            ~GuiPlugApp();

            const char *glsl_version{};

            // The main window which contains the different App windows
            PlatformWindow platformWindow{0, 0, "", glsl_version};

            void appRun();

      private:
            bool isPlatformWindowClosed{false};
            std::string contentIndex{""};

            GUIPLUG::WindowSelector windowSelector{GUIPLUG::WindowSelector::MANAGER_WINDOW};
      };
}
#endif