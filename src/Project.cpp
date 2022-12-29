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
            return projectSave(projectLocation + projectName + "\\" + projectName + ".gpproj", projectData);
      }
      return false;
}

const std::string GUIPLUG::Project::currentDateTime()
{
      std::time_t t = std::time(nullptr);
      std::tm *now = std::localtime(&t);

      char buffer[128];
      strftime(buffer, sizeof(buffer), "%d/%m/%Y@%X", now);
      return buffer;
}

bool GUIPLUG::Project::projectSave(const std::string &filePathForSave, const nlohmann::json &projectStructure)
{
      return (fileManager.fileSave(filePathForSave, projectStructure)) ? true : false;
}