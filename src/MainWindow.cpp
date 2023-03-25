#include "MainWindow.hpp"

GUIPLUG::MainWindow::MainWindow()
{
}

GUIPLUG::MainWindow::~MainWindow()
{
}

void GUIPLUG::MainWindow::placeContent(ImGuiViewport *viewPort, ImFont &mainFont24px)
{
      mainFont24px.FontSize = 22.0F;
      ImGui::PushFont(&mainFont24px);
      placeHeader();
      placeEditor(viewPort);
      //  placePanel(); //TODO: Rethink this feature, is it needed?
      placeItemSettings(viewPort);

      placeFooter();
      ImGui::PopFont();
}

void GUIPLUG::MainWindow::placeHeader()
{
      // Menu Bar
      if (ImGui::BeginMainMenuBar())
      {
            if (ImGui::BeginMenu("File"))
            {
                  if (ImGui::MenuItem("New"))
                  {
                  }
                  if (ImGui::MenuItem("Open", "Ctrl+O"))
                  {
                  }
                  if (ImGui::BeginMenu("Open Recent"))
                  {
                        // TODO implement logic for recently opened projects
                        ImGui::MenuItem("plug1.gpproj");
                        ImGui::MenuItem("plug2.gpproj");
                        ImGui::MenuItem("plug3.gpproj");
                        ImGui::EndMenu();
                  }
                  if (ImGui::MenuItem("Save", "Ctrl+S"))
                  {
                  }
                  if (ImGui::MenuItem("Save As.."))
                  {
                  }

                  ImGui::Separator();
                  // if (ImGui::BeginMenu("Options"))
                  // {
                  //       static bool enabled = true;
                  //       ImGui::MenuItem("Enabled", "", &enabled);
                  //       ImGui::BeginChild("child", ImVec2(0, 60), true);
                  //       for (int i = 0; i < 10; i++)
                  //             ImGui::Text("Scrolling Text %d", i);
                  //       ImGui::EndChild();
                  //       static float f = 0.5f;
                  //       static int n = 0;
                  //       ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
                  //       ImGui::InputFloat("Input", &f, 0.1f);
                  //       ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                  //       ImGui::EndMenu();
                  // }
                  if (ImGui::MenuItem("Exit"))
                  {
                  }
                  ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                  if (ImGui::MenuItem("Undo", "CTRL+Z"))
                  {
                  }
                  if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
                  {
                  } // Disabled item
                  ImGui::Separator();
                  if (ImGui::MenuItem("Cut", "CTRL+X"))
                  {
                  }
                  if (ImGui::MenuItem("Copy", "CTRL+C"))
                  {
                  }
                  if (ImGui::MenuItem("Paste", "CTRL+V"))
                  {
                  }
                  ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Build/Test"))
            {
                  if (ImGui::MenuItem("Build Standalone"))
                  {
                  }
                  if (ImGui::MenuItem("Build VST3"))
                  {
                  }
                  if (ImGui::MenuItem("Build AU (Audio Unit)"))
                  {
                  }
                  if (ImGui::MenuItem("Build LV2 (LADSPA Version 2)"))
                  {
                  }
                  if (ImGui::MenuItem("Build CLAP"))
                  {
                  }
                  ImGui::EndMenu();
            }

            ImGui::BeginGroup();
            ImGui::PushItemWidth(ImGui::GetFontSize() * 32);
            ImGui::Button("Reaper");
            ImGui::PopItemWidth();
            ImGui::EndGroup();

            ImGui::EndMainMenuBar();
      }
}

void GUIPLUG::MainWindow::placePanel()
{
      ImGui::BeginMenuBar();
      ImGui::BeginGroup();
      if (ImGui::Button("Add"))
      {
            /* code */
      }

      ImGui::EndGroup();
      ImGui::EndMenuBar();
}

void GUIPLUG::MainWindow::placeEditor(ImGuiViewport *viewPort)
{
      mainWinPosition.x = 0.0F;
      mainWinPosition.y = 27.0F;
      mainWinSize.x = viewPort->Size.x * 0.80F;
      mainWinSize.y = viewPort->Size.y - 20.0F;

      ImGui::SetNextWindowPos(mainWinPosition);
      ImGui::SetNextWindowSize(mainWinSize);

      ImGui::Begin("Editor", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
      ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2{0.12F, 0.5F});
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.16F, 0.16F, 0.16F, 1.0F}); // All buttons in following table
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.25F, 0.25F, 0.25F, 1.0F});
      std::string popUpTitle = "New Plugin";

      if (isNewProject)
      {
            ImGui::SetCursorPos(ImVec2{mainWinSize.x * 0.5F, mainWinSize.y * 0.5F});
            if (ImGui::Button("Create New Plugin", ImVec2{200.0F, 49.0F}))
            {
                  ImGui::OpenPopup(popUpTitle.c_str(), ImGuiPopupFlags_None);
            }

            // Modal content for the "new plugin". Cannot be combined with OpenPopUp() on same scope (implemented by library)
            if (ImGui::BeginPopupModal(popUpTitle.c_str(), NULL,
                                       ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
            {
                  ImGui::SetNextWindowBgAlpha(1.0F);
                  wizardWindow.openProjectPath = openProjectPath;
                  wizardWindow.showWizard("wzPlugin");
                  if (wizardWindow.wizardResult)
                  {
                        // project.loadSaved();
                        isNewProject = false;
                  }
                  ImGui::EndPopup();
            };
      }
      ImGui::PopStyleColor(2);
      ImGui::PopStyleVar();
      ImGui::End();
}

void GUIPLUG::MainWindow::placeItemSettings(ImGuiViewport *viewPort)
{
      mainWinPosition.x = viewPort->Size.x * 0.80F;
      mainWinPosition.y = 27.0F;
      mainWinSize.x = viewPort->Size.x * 0.20F;
      mainWinSize.y = viewPort->Size.y;

      ImGui::SetNextWindowPos(mainWinPosition);
      ImGui::SetNextWindowSize(mainWinSize);

      ImGui::Begin("ItemSettings", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
      if (ImGui::CollapsingHeader("Positioning", ImGuiTreeNodeFlags_Selected))
      {
            static float f0 = 0.001f;
            ImGui::Text("Position X: ");
            ImGui::SameLine();
            ImGui::DragFloat(" ", &f0, 0.5f);

            ImGui::Text("Position Y: ");
            ImGui::SameLine();
            static float f1 = 0.001f;
            ImGui::DragFloat(" ", &f1, 0.5f);
      }
      ImGui::End();
}

void GUIPLUG::MainWindow::placeFooter() {}