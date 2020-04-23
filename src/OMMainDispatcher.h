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

    OMMainDispatcher(boost::asio::io_context &ioc);

    ~OMMainDispatcher();

    static OMMainDispatcher* Instance();

    void execute(IOxfEvent::Ptr& ev);

    IOxfReactive::TakeEventStatus dispatch(IOxfEvent::Ptr& ev);

    boost::asio::io_context &_ioc;
};

#endif // OMMAINDISPATCHER_H
