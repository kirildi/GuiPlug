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

            Project(nlohmann::json &projectData) : projectLocation{projectData["projectRootDir"]},
                                                   projectDateCreated{currentDateTime()},
                                                   projectPlatform{projectData["projectPlatform"]},
                                                   projectOwner{projectData["projectOwner"]},
                                                   projectName{projectData["projectName"]}
            {
                  projectStructure["header"]["projectOwner"] = projectOwner;
                  projectStructure["header"]["projectPlatform"] = projectPlatform;
                  projectStructure["header"]["projectLocation"] = projectLocation;
                  projectStructure["header"]["projectDateCreated"] = projectDateCreated;
                  projectStructure["header"]["projectName"] = projectName;

                  projectSave(projectStructure);
            };
            ~Project(){};

            std::string projectLocation{};
            std::string projectDateCreated{};
            std::string projectPlatform{};
            std::string projectOwner{};
            std::string projectName{};

            nlohmann::json projectStructure{};

      private:
            std::string sectionKeyWord{"header"};

            bool projectSave(nlohmann::json &projectStructure)
            {
                  FileManager projectFile;

                  projectFile.fileSave(projectLocation + projectName + "\\" + projectName + ".gpproj", projectStructure);
                  return true;
            }

            std::string currentDateTime()
            {
                  std::time_t t = std::time(nullptr);
                  std::tm *now = std::localtime(&t);

                  char buffer[128];
                  strftime(buffer, sizeof(buffer), "%d/%m/%Y@%X", now);
                  return buffer;
            }
      };
}

#endif // PROJECT_H