#include "WizardWindow.hpp"

GUIPLUG::WizardWindow::WizardWindow(){};
GUIPLUG::WizardWindow::~WizardWindow(){};

bool GUIPLUG::WizardWindow::showWizard(const std::string &wizardWindowId)
{
      // Centers modal window
      viewPort = ImGui::GetMainViewport();
      wizardStartPos.x = viewPort->Size.x * 0.111F;
      wizardStartPos.y = viewPort->Size.y * 0.111F;
      wizardDimensions.x = viewPort->Size.x - (viewPort->Size.x * 0.111F * 2.0F);
      wizardDimensions.y = viewPort->Size.y - (viewPort->Size.y * 0.111F * 2.0F);

      ImGui::SetNextWindowPos(wizardStartPos, ImGuiCond_Appearing);
      ImGui::SetNextWindowSize(wizardDimensions);
      ImGui::SetNextWindowBgAlpha(1.0F);

      if (wizardWindowId != "wzProject")
            wizardPlugin();

      wizardResult = wizardProject();

      return wizardResult;
}

bool GUIPLUG::WizardWindow::wizardProject()
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

      ImGui::InputText("##project_name: ", &project.projectName);
      ImGui::SameLine(0.0F, 52.0F);

      const char *platformList[] = {"Windows", "Linux", "OSX"};
      static const char *current_platform = platformList[0];
      if (ImGui::BeginCombo("##project_platform_select", current_platform)) // The second parameter is the label previewed.
      {
            // TODO Width of popup is not the same as field width

            for (int n = 0; n < IM_ARRAYSIZE(platformList); n++)
            {
                  bool is_selected = (current_platform == platformList[n]);
                  if (ImGui::Selectable(platformList[n], is_selected))
                        current_platform = platformList[n];
                  if (is_selected)
                        ImGui::SetItemDefaultFocus(); // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
            }
            ImGui::EndCombo();
      }

      // Creator name
      ImGui::LabelText("##first_name", "First Name");
      ImGui::SameLine(0.0F, 52.0F);
      ImGui::LabelText("##last_name", "Last/Second Name");

      ImGui::InputText("##first_name_input ", &project.firstName);
      ImGui::SameLine(0.0F, 52.0F);
      ImGui::InputText("##last_name_input ", &project.lastName);

      ImGui::PopItemWidth();
      ImGui::EndGroup();

      // Project Location
      ImGui::BeginGroup();
      ImGui::LabelText("##project_dir", "Location");
      ImGui::PushItemWidth(400.0F);
      ImGui::InputText("##project_dir_input", &projectRootDir);

      ImGui::SameLine(0.0F, 30.0F);
      if (ImGui::Button("Browse...", ImVec2{90.0F, 32.0F}))
      {
            projectRootDir = pfd::select_folder("Select a directory").result();
      }
      ImGui::PopItemWidth();
      ImGui::EndGroup();

      ImGui::PopStyleColor();
      ImGui::PopStyleVar(5);

      // Place confirmation buttons
      ImGui::Dummy(ImVec2{0.0F, 12.0F});
      wizardButtons();

      if (isDoneClicked)
      {
            project.projectPlatform = current_platform;
            project.projectLocation = projectRootDir + project.projectName + "\\";

            isProjectExist = fileManager.fileExist(project.projectLocation + project.projectName + project.fileExtension);
            if (!isProjectExist)
            {
                  fillForNewProject(); // stores input data before create
                  std::filesystem::path dir{project.projectLocation};

                  if (fileManager.createDirectory(dir))
                  {
                        project.save();
                  }
            }
            else
            {
                  ImGui::OpenPopup("Project Exist", ImGuiPopupFlags_AnyPopupLevel);
            }
            return isDoneClicked;
      }

      // Confirmation modal if project exist in provided path
      if (ImGui::BeginPopupModal("Project Exist", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
      {
            ImGui::Dummy(ImVec2{0.0f, 12.0f});

            ImGui::LabelText("##project_exist_label", "Project already exist.");
            ImGui::LabelText("##project_exist_label2", "Do you want to open it?");

            ImGui::SetCursorPos(ImVec2{wizardDimensions.x * 0.3F, wizardDimensions.y * 0.5F});
            ImGui::BeginGroup();
            if (ImGui::Button("OK", ImVec2{120.0F, 32.0F}))
            {
                  isDoneClicked = true;
                  ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine(0, 12.0F);
            if (ImGui::Button("Cancel", ImVec2{120.0F, 32.0F}))
            {
                  isDoneClicked = false;
                  ImGui::CloseCurrentPopup();
            }
            ImGui::EndGroup();

            ImGui::EndPopup();
      }

      return false;
};

bool GUIPLUG::WizardWindow::wizardPlugin()
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
                  const char *items[] = {"SKIA", "OpenGL3", "Cairo_graphics"};
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

                  ImGui::EndGroup();
                  ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
            ImGui::EndPopup();
      }
      return false;
};

void GUIPLUG::WizardWindow::fillForNewProject()
{
      project.projectHeader["header"]["projectLocation"] = project.projectLocation;
      project.projectHeader["header"]["projectPlatform"] = project.projectPlatform;
      project.projectHeader["header"]["projectOwner"] = project.firstName.append(project.lastName);
      project.projectHeader["header"]["projectName"] = project.projectName;
      project.projectHeader["header"]["projectDateCreated"] = currentDateTime();
};

void GUIPLUG::WizardWindow::wizardButtons()
{
      ImGui::Dummy(ImVec2{0.0F, 12.0F});
      ImGui::SetCursorPos(ImVec2{wizardDimensions.x * 0.46F, wizardDimensions.y - 21.0F});

      ImGui::BeginGroup();
      if (ImGui::Button("Done", ImVec2{100.0F, 32.0F}))
            isDoneClicked = true;

      ImGui::SameLine(0, 12.0F);

      if (ImGui::Button("Cancel", ImVec2{120.0F, 32.0F}))
            ImGui::CloseCurrentPopup();

      ImGui::EndGroup();
};