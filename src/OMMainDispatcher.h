#ifndef OMMAINDISPATCHER_H
#define OMMAINDISPATCHER_H

#include "IOxfEvent.h"
#include <queue>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "IOxfActive.h"
#include "OMEventQueue.h"

class OMMainDispatcher : public IOxfActive
{
public:
    typedef boost::asio::executor_work_guard<boost::asio::io_context::executor_type> io_context_work;

    OMMainDispatcher();

    ~OMMainDispatcher();

    static OMMainDispatcher* getInstance();

    void execute(IOxfEvent::Ptr& ev);

    IOxfReactive::TakeEventStatus dispatch(IOxfEvent::Ptr& ev);

    boost::thread_group _threads;

    boost::asio::io_context _ioc;

    io_context_work _work;
};

#endif // OMMAINDISPATCHER_H
