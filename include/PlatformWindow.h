#ifndef PLATFORM_WINDOW_H
#define PLATFORM_WINDOW_H

#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

#include "Enums.h"

#include "ManagerWindow.h"
#include "MainWindow.h"

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
                           GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr) : glsl_version{glsl_version},
                                                                                          width{width},
                                                                                          height{height},
                                                                                          title{title},
                                                                                          monitor{monitor},
                                                                                          share{share},
                                                                                          thisWindow{nullptr} {};
            ~PlatformWindow()
            {
                  destroy();
            };

            inline void setWidth(int width) { this->width = width; }
            inline void setHeight(int height) { this->height = height; }
            inline void setTitle(std::string title) { this->title = title; }

            GLFWwindow *create()
            {
                  (thisWindow == nullptr || thisWindow == NULL)
                      ? thisWindow = glfwCreateWindow(width, height, title.c_str(), monitor, share)
                      : thisWindow = nullptr;
                  glfwMakeContextCurrent(thisWindow);
                  glfwSwapInterval(1); // Enable vsync

                  return thisWindow;
            }

            bool showContent(std::string windowId)
            {
                  ImGui::CreateContext();
                  ImGuiIO &io = ImGui::GetIO();

                  // Setting up the fonts used in the App
                  setupFonts(io);

                  ImGui_ImplGlfw_InitForOpenGL(thisWindow, true);
                  ImGui_ImplOpenGL3_Init(glsl_version.c_str());

                  // Setting the PlatformWindow as main ViewPort to host "Dear ImGui" windows
                  setViewPort(ImGui::GetMainViewport());
                  /*-------------------------------------------------------*/

                  // sk_sp<const GrGLInterface> gl_interface{};
                  // sk_sp<GrDirectContext> context{GrDirectContext::MakeGL(gl_interface)};
                  // SkASSERT(context);

                  // If PlatformWindow is closed loop is terminated and the program will continue
                  // depending on the which window is the last closed.
                  while (!glfwWindowShouldClose(thisWindow))
                  {
                        glfwPollEvents();
                        ImGui_ImplOpenGL3_NewFrame();
                        ImGui_ImplGlfw_NewFrame();
                        // Start the Dear ImGui frame
                        ImGui::NewFrame();

                        if (windowId == "manager")
                        {
                              windowSelector = WindowSelector::MANAGER_WINDOW;
                              managerWindow.placeContent(viewPort, *mainFont24px, *mainFont42px);

                              if (managerWindow.openNewProj)
                              {
                                    windowSelector = WindowSelector::MAIN_WINDOW;
                                    glfwDestroyWindow(thisWindow);
                                    thisWindow = nullptr;
                                    managerWindow.openNewProj = false;
                                    ImGui::DestroyContext();
                                    return false;
                              }
                        }

                        if (windowId == "main")
                        {
                              windowSelector = WindowSelector::MAIN_WINDOW;
                              mainWindow.openProjectPath = managerWindow.openExistingPath;
                              mainWindow.isNewProject = managerWindow.isNewProject;
                              mainWindow.placeContent(viewPort, *mainFont24px);
                        }
                        // Rendering
                        ImGui::Render();

                        glfwGetFramebufferSize(thisWindow, &width, &height);
                        glClearColor(backGroundColor.x * backGroundColor.w, backGroundColor.y * backGroundColor.w, backGroundColor.z * backGroundColor.w, backGroundColor.w);
                        glViewport(0, 0, width, height);
                        glClear(GL_COLOR_BUFFER_BIT);

                        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                        glfwSwapBuffers(thisWindow);
                  }

                  if (windowSelector == WindowSelector::MAIN_WINDOW)
                  {
                        windowSelector = WindowSelector::MANAGER_WINDOW;
                        glfwDestroyWindow(thisWindow);
                        thisWindow = nullptr;
                        ImGui::DestroyContext();
                        return false;
                  }

                  ImGui_ImplOpenGL3_Shutdown();
                  ImGui_ImplGlfw_Shutdown();
                  ImGui::DestroyContext();
                  return true;
            }

            void setViewPort(ImGuiViewport *viewPort) { this->viewPort = viewPort; }

            void setupFonts(ImGuiIO &io)
            {
                  // TODO can font be loaded by setting a value, or path?
                  // Fonts are currently loaded by FULL PATH provided
                  mainFont24px = io.Fonts->AddFontFromFileTTF("D:\\GitHub\\GuiPlug\\resources\\fonts\\Urbanist-SemiBold.ttf",
                                                              24.0F, NULL, io.Fonts->GetGlyphRangesDefault());

                  ImFontConfig config;
                  config.MergeMode = true;

                  static const ImWchar icon_ranges[] = {ICON_MIN_FK, ICON_MAX_FK, 0};
                  // load icons for button with icon
                  io.Fonts->AddFontFromFileTTF("D:\\GitHub\\GuiPlug\\resources\\fonts\\forkawesome-webfont.ttf",
                                               28.0F, &config, icon_ranges);
                  // Main font, but bigger
                  mainFont42px = io.Fonts->AddFontFromFileTTF("D:\\GitHub\\GuiPlug\\resources\\fonts\\Urbanist-SemiBold.ttf",
                                                              42.0F, NULL, io.Fonts->GetGlyphRangesDefault());
                  io.Fonts->Build();
            }
            void destroy()
            {
                  printf("Destroy Called");
                  if (thisWindow != nullptr)
                  {
                        glfwDestroyWindow(thisWindow);
                        thisWindow = nullptr;
                  }
                  glfwTerminate();
            }

            GUIPLUG::WindowSelector windowSelector = GUIPLUG::WindowSelector::MANAGER_WINDOW;

            std::string glsl_version{};

      private:
            // default window sizes
            int width{};
            int height{};
            std::string title{};
            GLFWmonitor *monitor{}; // use glfwGetPrimaryMonitor() to get primary monitor;
            GLFWwindow *share{};
            GLFWwindow *thisWindow{};

            ImGuiViewport *viewPort{nullptr};

            ImVec4 backGroundColor{ImVec4{0.3f, 0.3f, 0.3f, 1.00f}};

            ManagerWindow managerWindow{};
            MainWindow mainWindow{};

            ImFont *mainFont24px{};
            ImFont *mainFont42px{};
      };
}
#endif // PLATFORM_WINDOW_H