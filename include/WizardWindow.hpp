#ifndef WIZARD_WINDOW_H
#define WIZARD_WINDOW_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
#include "Project.hpp"
#include "Plugin.hpp"

#include "portable-file-dialogs.h"

namespace GUIPLUG
{
      class WizardWindow
      {
      public:
            WizardWindow();
            ~WizardWindow();

            bool showWizard(const std::string &wizardWindowId);

            /* loads New Project form/fields inside modal */
            bool wizardProject();

            /* Loads New Plugin form/fields inside modal */
            bool wizardPlugin();

            bool wizardResult{false};
            bool isProjectExist{false};
            std::string openProjectPath{};

      private:
            bool isDoneClicked{false};

            // Default location related to executable directory
            std::string projectRootDir{std::filesystem::current_path().string() + "\\Projects\\"};

            Project project{};
            Plugin plugin{};
            FileManager fileManager{};

            ImGuiViewport *viewPort{nullptr};
            ImVec2 wizardStartPos{0.0F, 0.0F};
            ImVec2 wizardDimensions{0.0F, 0.0F};

            void fillForNewProject();
            void fillForNewPlugin();

            void wizardButtons();
      };
} // GUIPLUG
#endif // WIZARD_WINDOW_H