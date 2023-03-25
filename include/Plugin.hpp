#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "json.hpp"

namespace GUIPLUG
{
      class Plugin
      {

      public:
            Plugin();
            ~Plugin();

            std::string pluginRenderer{};
            std::string pluginName{};
            std::string pluginCreator{};

      private:
            std::fstream fileManager{};
      };
}
#endif // PLUGIN_HPP