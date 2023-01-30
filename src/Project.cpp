#include "Project.hpp"

GUIPLUG::Project::Project(){};
GUIPLUG::Project::~Project(){};

bool GUIPLUG::Project::projectCreate(nlohmann::json &projectData)
{
      auto projectName = std::string{projectData["header"]["projectName"]};
      auto projectLocation = std::string{projectData["header"]["projectLocation"]};
      std::filesystem::path dir{projectLocation + projectName};

      if (fileManager.createDirectory(dir))
      {
            return save(projectLocation + projectName + "\\" + projectName + fileExtension, projectData);
      }
      return false;
}

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
      return false;
}

bool GUIPLUG::Project::save(const std::string &pathToSave, const nlohmann::json &projectStructure)
{
      return (fileManager.fileSave(pathToSave, projectStructure)) ? true : false;
}