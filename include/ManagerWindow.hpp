#ifndef MANAGER_WINDOW_HPP
#define MANAGER_WINDOW_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "IconsForkAwesome.hpp"

#include "WizardWindow.hpp"

namespace GUIPLUG
{
      class ManagerWindow
      {
      public:
            ManagerWindow();

            ~ManagerWindow();

            void placeContent(ImGuiViewport *viewPort, ImFont &mainFont24px, ImFont &mainFont42px);

            std::string openExistingPath{""};
            bool openNewProj{false};
            bool isNewProject{false}; // To detect if project is opened from file or is newly created.

      private:
            ImVec2 winPosition{0.0F, 0.0F};
            ImVec2 winSize{0.0F, 0.0F};
            std::string popUpName{""};

            WizardWindow WizardWindow{};
      };

} // GUIPLUG

#endif // MANAGER_WINDOW_H