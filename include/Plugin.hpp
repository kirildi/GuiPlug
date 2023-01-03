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

      private:
            std::fstream fileManager{};
      };
}
#endif // PLUGIN_HPP