#include "Project.hpp"

GUIPLUG::Project::Project(){};
GUIPLUG::Project::~Project(){};

nlohmann::json GUIPLUG::Project::loadSaved(const std::string &pathOfSaved)
{
      return nlohmann::json();
}

nlohmann::json GUIPLUG::Project::fetchFromSaved(std::string &key)
{
      return nlohmann::json();
}

bool GUIPLUG::Project::save()
{
      nlohmann::json projectStructure{};
      // TODO what if the structures aren't empty?
      if (!projectHeader.empty())
            projectStructure.update(projectHeader, true);
      if (!projectWindow.empty())
            projectStructure.update(projectWindow, true);
      if (!projectPlugin.empty())
            projectStructure.update(projectPlugin, true);
      if (!projectMisc.empty())
            projectStructure.update(projectMisc, true);

      return (fileManager.fileSave(projectLocation + projectName + fileExtension, projectStructure)) ? true : false;
}

bool GUIPLUG::Project::save(const std::string &pathToSave, const nlohmann::json &projectStructure)
{
      return (fileManager.fileSave(pathToSave, projectStructure)) ? true : false;
}