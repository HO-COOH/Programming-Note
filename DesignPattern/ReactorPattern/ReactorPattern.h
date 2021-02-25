// ReactorPattern.h : Include file for standard system include files,
// or project specific include files.

#pragma once

/*
 * Developing an effective server mechanism:
 *      1.Availability: The server must be available to handle incoming request even if it is waiting for other requests to arrive.
 *          A server must NOT block indefinitely handling any single source of events
 *      2.Efficiency: Minimize latency, maximize throughput, avoid utilizing CPU unnecessarily]
 *      3.Programming simplicity
 *      4.Adaptability: Integrating new / improved services should incur minimal modifications
 *      5.Portability: Porting -> a new OS should not require significant effort
 *  Structure:
 *      Handles: identify resources that are managed by an OS
 *      Synchronous event demultiplexer: select one handle that is ready in a non-blocking manner
 *      Event handler: specifies an interface consisting of a hook method that abstractly represents the dispatching operation for service-specific events
 *          Concrete event handler: implements the hook method
 *      Initiation dispatcher: defines an interface for registering, removing and dispatching Event handlers
 */

enum EventType
{
    Accept,
    Read,
    Write,
    Timeout,
    Signal,
    Close
};

#include <chrono>

class EventHandler;

class InitiationDispatcher
{
    static InitiationDispatcher& GetInstance()
    {
        static InitiationDispatcher dispatcher;
        return dispatcher;
    }
public:
    inline static InitiationDispatcher& instance = GetInstance();
    int registerHandler(EventHandler* handler, EventType type);
    int removeHandler(EventHandler* handler, EventType type);
    int handleEvents(std::chrono::seconds timeout = std::chrono::seconds{ 10 });
};

class Handle {};

class EventHandler
{
public:
    virtual void handleEvent() = 0;
    virtual Handle getHandle() const = 0;
    virtual ~EventHandler() = 0;
};


template<typename Socket>
class LoggingAcceptor:public EventHandler
{
    Socket acceptor;
public:
    LoggingAcceptor()
    {
        InitiationDispatcher::instance.register_handle(this, EventType::Accept);
    }
    /**
     * @brief Accept the connection and create a new LoggingHandler
     */
    void handleEvent() override
    {

    }
    Handle getHandle() const override;
    ~LoggingAcceptor() override;
};

/**
 * @brief Receive and process logging records sent by a client application
 */
template<typename SocketStream>
class LoggingHandler:public EventHandler
{
    SocketStream stream;
public:
    /**
     * @brief Initialize the client stream
     */
    LoggingHandler()
    {
        InitiationDispatcher::instance.register_handler(this);
    }
    
    /**
     * @brief Handles the reception of logging records from clients
     */
    void handleEvent() override
    {

    }

    /**
     * @brief Get the IO handle (called by the InitiationDispatcher when LoggingHandler is registered)
     */
    Handle getHandle() const override
    {

    }

    ~LoggingHandler() override;
};
