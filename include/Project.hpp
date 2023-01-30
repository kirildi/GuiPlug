#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "HelperFunctions.hpp"
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

            bool isSaved{false};
            bool projectCreate(nlohmann::json &projectData);
            nlohmann::json projectHeader{};
            nlohmann::json projectPlugin{};
            nlohmann::json projectWindow{};
            nlohmann::json projectMisc{};

            nlohmann::json loadSaved(const std::string &pathOfSaved);
            nlohmann::json fetchFromSaved(std::string &key);

            bool save();
            bool save(const std::string &pathToSave, const nlohmann::json &projectStructure);

      private:
            FileManager fileManager{};
            const std::string fileExtension{".gpproj"};
      };
}

#endif // PROJECT_H