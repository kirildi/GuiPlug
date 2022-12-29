#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "FileManager.hpp"

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
            Project();
            ~Project();

            bool projectCreate(nlohmann::json &projectData);

            const std::string currentDateTime(); // get current date/time on project create

      private:
            FileManager fileManager{};
            bool projectSave(const std::string &filePathForSave, const nlohmann::json &projectStructure);
      };
}

#endif // PROJECT_H