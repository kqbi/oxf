#ifndef OMMAINDISPATCHER_H
#define OMMAINDISPATCHER_H

#include "IOxfEvent.h"
#include <queue>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "IOxfActive.h"
#include "OMEventQueue.h"

class OMMainDispatcher : public IOxfActive {
public:

    OMMainDispatcher();

    ~OMMainDispatcher();

    static OMMainDispatcher &Instance();

    void execute(IOxfEvent::Ptr &ev);

    IOxfReactive::TakeEventStatus dispatch(IOxfEvent::Ptr &ev);

};

#endif // OMMAINDISPATCHER_H
