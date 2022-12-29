#ifndef GUIPLUGAPP_HPP
#define GUIPLUGAPP_HPP

#pragma once

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

#include "Enums.hpp"
#include "PlatformWindow.hpp"

namespace GUIPLUG
{
      class GuiPlugApp
      {
      public:
            GuiPlugApp();
            ~GuiPlugApp();

            std::string glsl_version{};

            // The main window which contains the different windows
            PlatformWindow platformWindow{0, 0, "", glsl_version};

            void appRun();

      private:
            bool isAppFullyClosed{false};
            std::string contentIndex{""};

            GUIPLUG::WindowSelector windowSelector{GUIPLUG::WindowSelector::MANAGER_WINDOW};
      };
}
#endif // GUIPLUGAPP_HPP