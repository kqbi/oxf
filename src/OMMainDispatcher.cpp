#include "OMMainDispatcher.h"

OMMainDispatcher::OMMainDispatcher() : _work(boost::asio::make_work_guard(_ioc)) {
    _threads.create_thread(boost::bind(&boost::asio::io_context::run, &_ioc));
}

OMMainDispatcher::~OMMainDispatcher() {
    _ioc.stop();
    _threads.join_all();
}

OMMainDispatcher* OMMainDispatcher::getInstance() {
    static  OMMainDispatcher dispatcher;
    return &dispatcher;
}

void OMMainDispatcher::execute(IOxfEvent::Ptr& ev) {
    if (ev) {
        IOxfReactive::TakeEventStatus result = IOxfReactive::eventConsumed;
        std::weak_ptr<IOxfReactive> dest = ev->getDestination();
        result = dispatch(ev);

        if (result == IOxfReactive::instanceReachTerminate) {
            auto reative = dest.lock();
            if (reative)	{
                reative.reset();
            }
        }
    }
}

IOxfReactive::TakeEventStatus OMMainDispatcher::dispatch(IOxfEvent::Ptr& ev) {
    IOxfReactive::TakeEventStatus result = IOxfReactive::eventNotConsumed;
    std::weak_ptr<IOxfReactive> dest = ev->getDestination();
    auto reactive = dest.lock();
    if (reactive) {
        result = reactive->handleEvent(ev);
    }
    return result;
}
