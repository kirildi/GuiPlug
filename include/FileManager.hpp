#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "json.hpp"

namespace GUIPLUG
{
      class FileManager
      {

      public:
            FileManager();
            ~FileManager();

            bool fileOpen(const std::string &filePath, bool createNew = false);
            bool fileClose();
            bool fileSave(const std::string &filePathForSave, const nlohmann::json &data);
            bool fileExist(const std::filesystem::path &filePath);
            bool fileExist(const std::string &fullFileName);
            // TODO GetDirAsList?

            bool createDirectory(const std::filesystem::path &dir);

            std::filesystem::path workingDirectory{};

      private:
            std::fstream fileManager{};
      };
}
#endif // FILE_MANAGER_HPP