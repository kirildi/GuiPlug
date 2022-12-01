#ifndef PLATFORM_WINDOW_H
#define PLATFORM_WINDOW_H

#pragma once
#define SK_GL
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>

#include "Enums.h"

#include "ManagerWindow.h"
#include "MainWindow.h"

#include "SkData.h"
#include "SkImage.h"
#include "SkStream.h"
#include "SkCanvas.h"
#include "SkSurface.h"
#include "SkPaint.h"
#include "gl/GrGLInterface.h"
#include "gl/GrGLDefines.h"

#include "SkColorSpace.h"
#include "GrBackendSurface.h"
#include "GrDirectContext.h"

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

                  sk_sp<const GrGLInterface> gl_interface{};
                  sk_sp<GrDirectContext> context{GrDirectContext::MakeGL(gl_interface)};
                  SkASSERT(context);

                  // int fbo = 0, samples = 0, stencilBits = 0;
                  // GrGLFramebufferInfo fbinfo{};
                  // fbinfo.fFBOID = fbo;
                  // fbinfo.fFormat = GR_GL_RGBA8;

                  // GrBackendRenderTarget backendRT(width, height, samples, stencilBits, fbinfo);

                  // surface = SkSurface::MakeFromBackendRenderTarget(context.get(), backendRT,
                  //                                                  kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, nullptr, nullptr);

                  // SkImageInfo info{SkImageInfo::MakeN32Premul(width, height)};
                  // sk_sp<SkSurface> surface{
                  //     SkSurface::MakeRasterN32Premul(width, height)};
                  // if (!surface)
                  // {
                  //       SkDebugf("SkSurface::MakeRenderTarget returned null\n");
                  // }
                  // auto canvas{surface->getCanvas()};

                  // If PlatformWindow is closed loop is terminated and the program will continue
                  // depending on the which window is the last closed.
                  while (!glfwWindowShouldClose(thisWindow))
                  {
                        glfwPollEvents();

                        SkImageInfo info{SkImageInfo::MakeN32Premul(width, height)};
                        // sk_sp<SkSurface> surface{SkSurface::MakeRenderTarget(context.get(), SkBudgeted::kYes, info)};
                        sk_sp<SkSurface> surface{SkSurface::MakeRenderTarget(context.get(), SkBudgeted::kNo, info)};

                        auto canvas{surface->getCanvas()};
                        //   Clear background
                        canvas->clear(SK_ColorGREEN);

                        // SkPaint paint;
                        // paint.setStyle(SkPaint::kStroke_Style);
                        // paint.setStrokeWidth(8);
                        // paint.setColor(0xff4285F4);
                        // paint.setAntiAlias(true);
                        // paint.setStrokeCap(SkPaint::kRound_Cap);

                        // SkPath path;
                        // path.moveTo(10, 10);
                        // path.quadTo(256, 64, 128, 128);
                        // path.quadTo(10, 192, 250, 250);

                        // canvas->drawPath(path, paint);

                        sk_sp<SkImage> img{surface->makeImageSnapshot()};

                        ImGui_ImplOpenGL3_NewFrame();
                        ImGui_ImplGlfw_NewFrame();
                        ImGui::NewFrame();
                        if (windowId == "manager")
                        {
                              windowSelector = WindowSelector::MANAGER_WINDOW;
                              // managerWindow.placeContent(viewPort, *mainFont24px, *mainFont42px);
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

                        ImGui::Image(context.get(), ImVec2{width - 400, height - 300});
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
                  mainFont24px = io.Fonts->AddFontFromFileTTF("D:\\GuiPlug\\resources\\fonts\\Urbanist-SemiBold.ttf", 24.0F, NULL, io.Fonts->GetGlyphRangesDefault());

                  ImFontConfig config;
                  config.MergeMode = true;

                  static const ImWchar icon_ranges[] = {ICON_MIN_FK, ICON_MAX_FK, 0};
                  io.Fonts->AddFontFromFileTTF("D:\\GuiPlug\\resources\\fonts\\forkawesome-webfont.ttf", 28.0F, &config, icon_ranges);
                  mainFont42px = io.Fonts->AddFontFromFileTTF("D:\\GuiPlug\\resources\\fonts\\Urbanist-SemiBold.ttf", 42.0F, NULL, io.Fonts->GetGlyphRangesDefault());
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

            sk_sp<SkSurface> surface{};

            ImGuiViewport *viewPort{nullptr};

            ImVec4 backGroundColor{ImVec4{0.3f, 0.3f, 0.3f, 1.00f}};

            ManagerWindow managerWindow{};
            MainWindow mainWindow{};

            ImFont *mainFont24px{};
            ImFont *mainFont42px{};
      };
}
#endif // PLATFORM_WINDOW_H