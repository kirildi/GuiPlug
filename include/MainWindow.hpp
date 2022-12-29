#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "FileManager.hpp"
#include "SkiaHandler.hpp"
#include "json.hpp"

namespace GUIPLUG
{
      class MainWindow
      {
      public:
            MainWindow();

            ~MainWindow();

            std::string openProjectPath{""};

            void placeContent(ImGuiViewport *viewPort, ImFont &mainFont24px);

            bool isNewProject{false}; // To detect if project is opened from file or is newly created.
      private:
            ImVec2 winPosition{0.0F, 0.0F};
            ImVec2 winSize{0.0F, 0.0F};

            FileManager fileManager{};

            // SkiaHandler skiaHandler{};

            nlohmann::json projectProperties{};

            void placeHeader();
            void placePanel();
            void placeEditor(ImGuiViewport *viewPort);
            void placeItemSettings(ImGuiViewport *viewPort);

            void placeFooter();
      };

} // GUIPLUG
#endif // MAIN_WINDOW_HPP