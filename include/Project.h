#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "FileManager.h"

/* Default Project Structure
{
      "header": {},
      "plugin": {},
      "window": {},
      "misc": {}
}
*/

namespace GUIPLUG
{
      class Project
      {
      public:
            Project(){};
            ~Project(){};
            bool projectCreate(nlohmann::json &projectData)
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

            const std::string currentDateTime()
            {
                  std::time_t t = std::time(nullptr);
                  std::tm *now = std::localtime(&t);

                  char buffer[128];
                  strftime(buffer, sizeof(buffer), "%d/%m/%Y@%X", now);
                  return buffer;
            }

      private:
            bool projectSave(const std::string &filePathForSave, const nlohmann::json &projectStructure)
            {
                  return (fileManager.fileSave(filePathForSave, projectStructure)) ? true : false;
            }
            FileManager fileManager{};
      };
}

#endif // PROJECT_H