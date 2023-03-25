#include "PlatformWindow.hpp"

GUIPLUG::PlatformWindow::PlatformWindow(int width, int height, std::string title, std::string glsl_version,
                                        GLFWmonitor *monitor, GLFWwindow *share) : glsl_version{glsl_version},
                                                                                   width{width},
                                                                                   height{height},
                                                                                   title{title},
                                                                                   monitor{monitor},
                                                                                   share{share},
                                                                                   thisWindow{nullptr} {};

GUIPLUG::PlatformWindow::~PlatformWindow()
{
      destroy();
};

void GUIPLUG::PlatformWindow::shutdownGUI()
{
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
};

GLFWwindow *GUIPLUG::PlatformWindow::create()
{
      (thisWindow == nullptr || thisWindow == NULL)
          ? thisWindow = glfwCreateWindow(width, height, title.c_str(), monitor, share)
          : thisWindow = nullptr;
      glfwMakeContextCurrent(thisWindow);
      glfwSwapInterval(1); // Enable vsync

      return thisWindow;
}

bool GUIPLUG::PlatformWindow::showContent(std::string windowId)
{
      ImGui::CreateContext();
      ImGuiIO &io = ImGui::GetIO();

      // Setting up the fonts used in the App
      setupFonts(io);

      ImGui_ImplGlfw_InitForOpenGL(thisWindow, true);
      ImGui_ImplOpenGL3_Init(glsl_version.c_str());

      // Setting the PlatformWindow as main ViewPort to host "Dear ImGui" windows
      setViewPort(ImGui::GetMainViewport());

      // If PlatformWindow is closed, loop is terminated and the program will continue
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
                        shutdownGUI();
                        isAppFullyClosed = false;
                        return isAppFullyClosed;
                  }
            }

            if (windowId == "main")
            {
                  windowSelector = WindowSelector::MAIN_WINDOW;
                  mainWindow.openProjectPath = managerWindow.openProjectPath;
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

      // After platform window closed.
      if (windowSelector != WindowSelector::MANAGER_WINDOW)
      {
            windowSelector = WindowSelector::MANAGER_WINDOW;
            glfwDestroyWindow(thisWindow);
            thisWindow = nullptr;
            managerWindow.openNewProj = false;
            isAppFullyClosed = false;
      }
      else
      {
            isAppFullyClosed = true;
      }

      shutdownGUI();
      return isAppFullyClosed;
}

void GUIPLUG::PlatformWindow::setupFonts(ImGuiIO &io)
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

void GUIPLUG::PlatformWindow::destroy()
{
      printf("Destroy Called");
      if (thisWindow != nullptr)
      {
            glfwDestroyWindow(thisWindow);
            thisWindow = nullptr;
      }
      glfwTerminate();
}