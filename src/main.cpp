#include <exception>

#include "Application.h"
#include "logging.h"

int main(int argc, char* argv[])
{
    try
    {
        Application application;
        application.initialize();
        application.run();
    }
    catch (const std::exception& exception)
    {
        log_error(exception.what());
        return 1;
    }
    catch (...)
    {
        log_error("Unknown exception");
        return 1;
    }

    return 0;
}
