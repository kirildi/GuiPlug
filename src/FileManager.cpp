#include "FileManager.hpp"

GUIPLUG::FileManager::FileManager(){};
GUIPLUG::FileManager::~FileManager(){};

bool GUIPLUG::FileManager::fileOpen(const std::string &filePath, bool createNew)
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

bool GUIPLUG::FileManager::fileClose()
{
      fileManager.close();
      return true;
};

bool GUIPLUG::FileManager::fileSave(const std::string &filePathForSave, const nlohmann::json &data)
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

bool GUIPLUG::FileManager::fileExist(const std::filesystem::path &filePath)
{
      return std::filesystem::exists(filePath);
}

bool GUIPLUG::FileManager::fileExist(const std::string &fullFileName)
{
      bool isOpen{false};
      fileManager.open(workingDirectory += "/" + fullFileName, std::ios::in);
      if (fileManager.is_open())
            isOpen = true;

      fileClose();
      return isOpen;
}

bool GUIPLUG::FileManager::createDirectory(const std::filesystem::path &dir)
{
      if (!std::filesystem::exists(dir))
      {
            std::filesystem::create_directories(dir);
            return true;
      }

      return false;
}
