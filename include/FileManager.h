#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

namespace GUIPLUG
{
      class FileManager
      {

      public:
            FileManager(){};
            ~FileManager(){};

            bool fileOpen(const std::string filePath, bool createNew = false)
            {
                  if (createNew)
                  {
                        fileManager.open(filePath, std::ios::out);
                        fileClose();
                  }
                  fileManager.open(filePath, std::ios::out | std::ios::app);
                  if (fileManager.is_open())
                        return true;
                  return false;
            };

            bool fileClose()
            {
                  fileManager.close();
                  return true;
            };

            bool fileSave(const std::string &filePathForSave, const nlohmann::json &data)
            {
                  if (fileOpen(filePathForSave, true))
                  {
                        std::string dataAsString = data.dump(4);
                        fileManager.write(dataAsString.c_str(), dataAsString.size());
                        fileClose();
                  }
                  else
                        return false;

                  return true;
            }
            bool fileExist(const std::filesystem::path filePath)
            {

                  return std::filesystem::exists(filePath);
            }

            bool fileExist(const std::string &fullFileName)
            {
                  bool isOpen{false};
                  fileManager.open(workingDirectory += "/" + fullFileName, std::ios::in);
                  if (fileManager.is_open())
                        isOpen = true;

                  fileClose();
                  return isOpen;
            }
            // TODO GetDirAsList

            bool createDirectory(const std::filesystem::path &dir)
            {
                  if (!std::filesystem::exists(dir))
                  {
                        std::filesystem::create_directories(dir);
                        return true;
                  }

                  return false;
            }

            std::filesystem::path workingDirectory{};

      private:
            std::fstream fileManager{};
      };
}
#endif