#include <string>
#include <exception>
#include <vector>
#include <limits>

#include "common/functional.hpp"
#include "common/logging.hpp"

using namespace logging;
std::shared_ptr<Logging> Logging::This;
std::shared_ptr<AsyncLogging> AsyncLogging::This;

void viewer_2d_example();
void viewer_3d_example();

int main(int argc, char* argv[])
{
  try
  {
    std::vector<std::string> params = {argv, argv + argc};

    auto level = LogLevel::DIAGNOSTIC;
    level = LogLevel::NORMAL;

    Log->LogInfo(std::string("opengl tmp toc"));

    if(params.size() == 1)
    {
      // set the default
      params.push_back("-2dplot");
    }

    if(func::contains(params, "-2dplot"))
    {
      viewer_2d_example();
    }
    else if(func::contains(params, "-3dplot"))
    {
      viewer_3d_example();
    }
  }
  catch(const std::exception& e)
  {
    std::cout << "Exception caught in main():" << std::endl;
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch(...)
  {
    std::cout << "Unknown exception caught in main()!\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
