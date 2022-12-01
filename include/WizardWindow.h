#ifndef WIZARD_WINDOW_H
#define WIZARD_WINDOW_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
#include "Project.h"

#include "portable-file-dialogs.h"

namespace GUIPLUG
{

      class WizardWindow
      {
      public:
            WizardWindow()
            {
            }

            ~WizardWindow()
            {
            }

            bool showWizard(const std::string &wizardWindowId)
            {
                  // Centers modal window
                  viewPort = ImGui::GetMainViewport();
                  popUpStartPos.x = viewPort->Size.x * 0.111F;
                  popUpStartPos.y = viewPort->Size.y * 0.111F;
                  popUpSize.x = viewPort->Size.x - (viewPort->Size.x * 0.111F * 2.0F);
                  popUpSize.y = viewPort->Size.y - (viewPort->Size.y * 0.111F * 2.0F);

                  ImGui::SetNextWindowPos(popUpStartPos, ImGuiCond_Appearing);
                  ImGui::SetNextWindowSize(popUpSize);

                  ImGui::SetNextWindowBgAlpha(1.0F);

                  if (wizardWindowId != "wzProject")
                        wizardPlugin();

                  wizardResult = wizardProject();

                  return wizardResult;
            }

            /* loads New Project form/fields inside modal */
            bool wizardProject()
            {
                  // Heading
                  ImGui::Dummy(ImVec2{0.0F, 3.0F});
                  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{5.0F, 5.0F});
                  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.0F, 12.0F});
                  ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2{0.0F, 14.0F});
                  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{6.0F, 5.0F});
                  ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2{0.5f, 0.5f});

                  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.25F, 0.25F, 0.25F, 1.0F));

                  ImGui::BeginGroup();
                  ImGui::PushItemWidth(240.0F);
                  // Name
                  ImGui::LabelText("##project_name_label", "Name");
                  ImGui::SameLine(0.0F, 52.0F);
                  ImGui::LabelText("##project_platform_label", "Platform/OS");

                  ImGui::InputText("##project_name: ", projectName, sizeof(projectName));
                  ImGui::SameLine(0.0F, 52.0F);

                  const char *items[] = {"Windows", "Linux", "OSX"};
                  static const char *item_current = items[0];
                  if (ImGui::BeginCombo("##project_platform_select", item_current)) // The second parameter is the label previewed.
                  {
                        // TODO Size of popup is not the same as field
                        projectPlatform = "";
                        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                        {
                              bool is_selected = (item_current == items[n]);
                              if (ImGui::Selectable(items[n], is_selected))
                                    item_current = items[n];
                              if (is_selected)
                                    ImGui::SetItemDefaultFocus(); // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                        }
                        projectPlatform = item_current;
                        ImGui::EndCombo();
                  }

                  // Creator name
                  ImGui::LabelText("##first_name", "First Name");
                  ImGui::SameLine(0.0F, 52.0F);
                  ImGui::LabelText("##last_name", "Last/Second Name");

                  ImGui::InputText("##first_name_input ", firstName, sizeof(firstName));
                  ImGui::SameLine(0.0F, 52.0F);
                  ImGui::InputText("##last_name_input ", lastName, sizeof(lastName));

                  ImGui::PopItemWidth();
                  ImGui::EndGroup();

                  ImGui::BeginGroup();
                  // Location
                  ImGui::LabelText("##project_dir", "Location");
                  ImGui::PushItemWidth(400.0F);
                  ImGui::InputText("##project_dir_input", &projectRootDir);

                  ImGui::SameLine(0.0F, 30.0F);
                  if (ImGui::Button("Browse...", ImVec2{90.0F, 32.0F}))
                  {
                        auto dir = pfd::select_folder("Select a directory").result();
                        projectRootDir = dir.c_str();
                  }
                  ImGui::PopItemWidth();

                  // IPLUG dir
                  ImGui::LabelText("##framework_dir", "IPLUG Location");
                  ImGui::PushItemWidth(400.0F);
                  ImGui::InputText("##framework_dir_input", &iplugDir);

                  ImGui::SameLine(0.0F, 30.0F);
                  if (ImGui::Button("Browse...", ImVec2{90.0F, 32.0F}))
                  {
                        auto dir = pfd::select_folder("Select IPLUG directory").result();
                        iplugDir = dir.c_str();
                  }
                  ImGui::PopItemWidth();
                  ImGui::EndGroup(); // TODO

                  ImGui::PopStyleColor();
                  ImGui::PopStyleVar(5);

                  ImGui::Dummy(ImVec2{0.0F, 12.0F});
                  // Buttons bottom
                  wizardButtons();

                  if (isDone)
                  {
                        std::string projectInRootDir = std::string{projectName} + "\\" + std::string{projectName} + ".gpproj";

                        isProjectExist = fileManger.fileExist(projectRootDir + projectInRootDir);
                        if (!isProjectExist)
                        {
                              collectPopUpData(); // stores input data before create
                              projectCreate(projectData);
                              projectData.clear();
                        }
                        else
                        {
                              ImGui::OpenPopup("Project Exist", ImGuiPopupFlags_AnyPopupLevel);
                        }
                        return isDone;
                  }

                  // Confirmation modal if project exist in provided path
                  if (ImGui::BeginPopupModal("Project Exist", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
                  {
                        ImGui::Dummy(ImVec2{0.0f, 12.0f});

                        ImGui::LabelText("##project_exist_label", "Project already exist.");
                        ImGui::LabelText("##project_exist_label2", "Do you want to open it?");

                        ImGui::SetCursorPos(ImVec2{popUpSize.x * 0.3F, popUpSize.y * 0.5F});
                        ImGui::BeginGroup();
                        if (ImGui::Button("OK", ImVec2{120.0F, 32.0F}))
                        {
                              isDone = true;
                              ImGui::CloseCurrentPopup();
                        }
                        ImGui::SameLine(0, 12.0F);
                        if (ImGui::Button("Cancel", ImVec2{120.0F, 32.0F}))
                        {
                              isDone = false;
                              ImGui::CloseCurrentPopup();
                        }
                        ImGui::EndGroup();

                        ImGui::EndPopup();
                  }

                  return false;
            };

            /* Loads New Plugin form/fields inside modal */
            bool wizardPlugin()
            {
                  // Always center this window when appearing
                  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
                  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2{0.5f, 0.5f});

                  if (ImGui::BeginPopupModal("##new_plugin_modal", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                  {

                        /* Heading */
                        ImGui::LabelText("##big_heading_text", "New Plugin Setup");

                        ImGui::Dummy(ImVec2{0.0f, 14.0f});

                        /* Wizard TabBar */
                        ImGui::BeginTabBar("##wizard_tabbar");

                        if (ImGui::BeginTabItem("Render"))
                        {
                              // Render platform selection
                              ImGui::BeginGroup();
                              ImGui::LabelText("", "Rendering platform: ");
                              const char *items[] = {"IPLUG_default(nanoSVG)", "SKIA", "OpenGL3", "Cairo_graphics"};
                              static const char *item_current = items[0];
                              if (ImGui::BeginCombo("##render_select", item_current)) // The second parameter is the label previewed.
                              {
                                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                                    {
                                          bool is_selected = (item_current == items[n]);
                                          if (ImGui::Selectable(items[n], is_selected))
                                                item_current = items[n];
                                          if (is_selected)
                                                ImGui::SetItemDefaultFocus(); // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                                    }
                                    ImGui::EndCombo();
                              }
                              ImGui::EndGroup();

                              ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Plugin"))
                        {
                              // Plugin platform selection
                              ImGui::BeginGroup();
                              ImGui::LabelText("##plugin_section", "Plugin: ");

                              static char plugin_name[128] = "";
                              ImGui::InputTextWithHint("##plugin_name", "Plugin name...", plugin_name, IM_ARRAYSIZE(plugin_name));
                              static char creator_name[128] = "";
                              ImGui::InputTextWithHint("##creator_name", "Creator name...", creator_name, IM_ARRAYSIZE(creator_name));

                              static int e = 0;
                              ImGui::RadioButton("VST3", &e, 0);
                              ImGui::SameLine();
                              ImGui::RadioButton("AU", &e, 1);
                              ImGui::SameLine();
                              ImGui::RadioButton("LV2", &e, 2);

                              // TODO: Iplug Directorie path field

                              // static bool check = true;
                              // ImGui::Checkbox("checkbox", &check);
                              // ImGui::Checkbox("checkbx", &check);

                              ImGui::EndGroup();
                              ImGui::EndTabItem();
                        }

                        ImGui::EndTabBar();
                        ImGui::EndPopup();
                  }
                  return false;
            };

            bool wizardResult{false};
            bool isProjectExist{false};

      private:
            char projectName[100] = {};
            char firstName[100] = {};
            char lastName[100] = {};
            std::string projectPlatform{};

            bool isDone{false};
            // Default location
            std::string projectRootDir{std::filesystem::current_path().string() + "\\Projects\\"};
            std::string iplugDir{""};

            // Stores the data from input fields until project created
            nlohmann::json projectData{};

            ImGuiViewport *viewPort{nullptr};
            ImVec2 popUpStartPos{0.0F, 0.0F};
            ImVec2 popUpSize{0.0F, 0.0F};

            FileManager fileManger;

            void wizardButtons()
            {
                  ImGui::Dummy(ImVec2{0.0F, 12.0F});
                  ImGui::SetCursorPos(ImVec2{popUpSize.x * 0.46F, popUpSize.y - 21.0F});

                  ImGui::BeginGroup(); // wizardButtons
                  if (ImGui::Button("Done", ImVec2{100.0F, 32.0F}))
                        isDone = true;

                  ImGui::SameLine(0, 12.0F);

                  if (ImGui::Button("Cancel", ImVec2{120.0F, 32.0F}))
                        ImGui::CloseCurrentPopup();

                  ImGui::EndGroup();
            }

            void collectPopUpData()
            {
                  // projectData["projectLocation"] =
                  projectData["projectName"] = projectName;
                  projectData["projectPlatform"] = projectPlatform;
                  projectData["projectOwner"] = std::string{firstName} + std::string{lastName};
                  projectData["projectRootDir"] = projectRootDir;
            }

            Project projectCreate(nlohmann::json &projectData)
            {
                  std::filesystem::path dir{std::string{projectData["projectRootDir"]} + std::string{projectName}};
                  if (fileManger.createDirectory(dir))
                        return Project{projectData};

                  return Project{};
            }
      };

} // GUIPLUG
#endif // WIZARD_WINDOW_H