// ReactorPattern.cpp : Defines the entry point for the application.
//

#include "ReactorPattern.h"
#include <iostream>

using namespace std;

/**
 * @brief Implements a single-threaded, concurrent logging server that waits in the InititationDispatcher.handle_event() loop
 */
int main()
{
    //Logging server port number

    LoggingAcceptor<int> acceptor;

    //Main event loop that handles client connection requests and logging request
    while (true)
    {
        InitiationDispatcher::instance.handleEvents();
    }
}
