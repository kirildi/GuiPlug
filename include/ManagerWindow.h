#ifndef MANAGER_WINDOW_H
#define MANAGER_WINDOW_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "IconsForkAwesome.h"

#include "WizardWindow.h"

namespace GUIPLUG
{
      class ManagerWindow
      {
      public:
            ManagerWindow()
            {
            }

            ~ManagerWindow()
            {
            }

            void placeContent(ImGuiViewport *viewPort, ImFont &mainFont24px, ImFont &mainFont42px)
            {
                  winSize.x = viewPort->Size.x;
                  winSize.y = viewPort->Size.y;
                  ImGui::SetNextWindowPos(winPosition); // set initial position (windows are placed inside platform window)
                  ImGui::SetNextWindowSize(winSize);

                  /* Manager Window */
                  ImGui::Begin("project_manager", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);

                  /* Heading */
                  ImGui::PushFont(&mainFont42px);
                  ImGui::LabelText("##big_heading_text", "GUIPLUG");
                  ImGui::PopFont();

                  ImGui::Dummy(ImVec2{0.0F, 21.0F});

                  /* Content */
                  ImGui::PushFont(&mainFont24px);

                  ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2{0.12F, 0.5F});
                  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.16F, 0.16F, 0.16F, 1.0F}); // All buttons in following table
                  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.25F, 0.25F, 0.25F, 1.0F});

                  ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, ImVec4{0.25F, 0.25F, 0.25F, 0.0F});
                  // Table "Projects"
                  ImGui::BeginTable("table_projects", 2);
                  ImGui::TableSetupColumn("Projects", ImGuiTableColumnFlags_WidthFixed, winSize.x * 0.5F);
                  ImGui::TableSetupColumn("Open Recent", ImGuiTableColumnFlags_WidthFixed, winSize.x * 0.5F);
                  ImGui::TableHeadersRow();

                  // "Projects" column
                  ImGui::TableNextRow();
                  ImGui::TableNextColumn();
                  ImGui::Dummy(ImVec2{0.0f, 12.0f});

                  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{28.0F, 28.0F});
                  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{160.0F, 12.0F});
                  ImGui::BeginGroup(); // "Projects" column content group

                  // Open Existing
                  if (ImGui::Button(ICON_FK_FILE_TEXT_O " Open Existing", ImVec2{210.0F, 48.0F}))
                  {
                        auto openExisting = pfd::open_file("Open existing project...").result();
                        if (!openExisting.empty())
                        {
                              auto result = openExisting[0].find("gpproj");
                              if (result == std::string::npos)
                              {
                                    pfd::message("Wrong file selected", "File should be in \".gpproj\" format.", pfd::choice::ok);
                              }
                              else
                              {
                                    openExistingPath = openExisting[0];
                                    openNewProj = true;
                                    isNewProject = false;
                              }
                        }
                        openExisting.clear();
                  }

                  // New Project
                  if (ImGui::Button(ICON_FK_FILE_O " New Project", ImVec2{210.0F, 48.0F}))
                  {
                        popUpName = "New Project";
                        ImGui::OpenPopup(popUpName.c_str(), ImGuiPopupFlags_None);
                  }

                  // Modal content for the "new project". Cannot be combined with OpenPopUp() on same scope (implemented by library)
                  if (ImGui::BeginPopupModal(popUpName.c_str(), NULL,
                                             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
                  {
                        ImGui::SetNextWindowBgAlpha(1.0F);
                        WizardWindow.showWizard("wzProject");
                        if (WizardWindow.wizardResult)
                        {
                              openNewProj = true;
                              isNewProject = true;
                        }
                        ImGui::EndPopup();
                  };
                  ImGui::EndGroup(); // End of "Projects" column content group

                  // "Open recent" column
                  ImGui::TableNextColumn();
                  ImGui::Dummy(ImVec2{0.0F, 12.0F});
                  // TODO - styling and make it to work as intended
                  ImGui::BeginGroup(); // "Open recent" column content group"
                  for (int i = 0; i < 6; i++)
                  {
                        std::string tempFileName{{ICON_FK_FILE_TEXT_O " fileName "}};
                        tempFileName += std::to_string(i);
                        if (ImGui::Button(tempFileName.c_str(), ImVec2(210.0F, 48.0F)))
                        {
                              // TODO logic when recent proj open
                        };
                        tempFileName.clear();
                  }
                  ImGui::EndGroup(); // End of "Open recent" column content group
                  ImGui::EndTable(); // table_projects end

                  ImGui::PopStyleColor(3);
                  ImGui::PopStyleVar(3);

                  ImGui::PopFont();

                  ImGui::End(); // End ManagerWindow
            }

            std::string openExistingPath{""};
            bool openNewProj{false};
            bool isNewProject{false}; // To detect if project is opened from file or is newly created.

      private:
            ImVec2 winPosition{0.0F, 0.0F};
            ImVec2 winSize{0.0F, 0.0F};
            WizardWindow WizardWindow{};

            std::string popUpName{""};
      };

} // GUIPLUG

#endif // MANAGER_WINDOW_H