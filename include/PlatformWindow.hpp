#ifndef PLATFORM_WINDOW_HPP
#define PLATFORM_WINDOW_HPP

#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

#include "Enums.hpp"

#include "ManagerWindow.hpp"
#include "MainWindow.hpp"

#include <GL/gl.h>
#if defined(SK_BUILD_FOR_UNIX)
#include <GL/gl.h>
#elif defined(SK_BUILD_FOR_MAC)
#include <OpenGL/gl.h>
#elif defined(SK_BUILD_FOR_IOS)
#include <OpenGLES/ES2/gl.h>
#endif

namespace GUIPLUG
{
      class PlatformWindow
      {

      public:
            PlatformWindow(int width, int height, std::string title, std::string glsl_version,
                           GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);
            ~PlatformWindow();

            std::string glsl_version{};
            GUIPLUG::WindowSelector windowSelector = GUIPLUG::WindowSelector::MANAGER_WINDOW;

            inline void setWidth(int width) { this->width = width; }
            inline void setHeight(int height) { this->height = height; }
            inline void setTitle(std::string title) { this->title = title; }
            inline void setViewPort(ImGuiViewport *viewPort) { this->viewPort = viewPort; }

            GLFWwindow *create();

            bool showContent(std::string windowId);

            void setupFonts(ImGuiIO &io);
            void destroy();

      private:
            int width{};
            int height{};
            std::string title{};
            GLFWmonitor *monitor{}; // use glfwGetPrimaryMonitor() to get primary monitor;
            GLFWwindow *share{};
            GLFWwindow *thisWindow{};
            ImGuiViewport *viewPort{nullptr};

            bool isAppFullyClosed{false};

            // Format (Red, Green, Blue, Alpha)
            ImVec4 backGroundColor{ImVec4{0.3f, 0.3f, 0.3f, 1.00f}};

            ManagerWindow managerWindow{};
            MainWindow mainWindow{};

            ImFont *mainFont24px{};
            ImFont *mainFont42px{};

            void shutdownGUI();
      };
}
#endif // PLATFORM_WINDOW_HPP