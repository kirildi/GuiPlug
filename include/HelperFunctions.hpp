#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include <ctime>
#include <string>

namespace GUIPLUG
{
      // get current date/time
      const std::string currentDateTime()
      {
            std::time_t t = std::time(nullptr);
            std::tm *now = std::localtime(&t);

            char buffer[128];
            strftime(buffer, sizeof(buffer), "%d/%m/%Y@%X", now);
            return buffer;
      }
}
#endif // HELPER_FUNCTIONS_HPP