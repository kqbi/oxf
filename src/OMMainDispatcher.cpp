#include "OMMainDispatcher.h"
#include "OXFEventPoller.h"

OMMainDispatcher::OMMainDispatcher(boost::asio::io_context &ioc) : _ioc(ioc) {
}

OMMainDispatcher::~OMMainDispatcher() {
    printf("~OMMainDispatcher\n");
}

OMMainDispatcher* OMMainDispatcher::Instance() {
    static OMMainDispatcher dispatcher(OXFEventPollerPool::Instance()->_ioc);
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
