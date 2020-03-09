#include "oxf.h"
#include "OMTimerManager.h"
#include "OMMainDispatcher.h"

OXF *OXF::getInstance() {
    static OXF oxf;
    return &oxf;
}

bool OXF::initialize(std::size_t eventPoll, std::size_t timeoutPoll) {
    //#[ operation initialize(OxfTimeUnit,Rhp_uint32_t,bool)
    bool status = false;

    // Create the main thread (actually its OXF wrapper)
    (void) OMMainDispatcher::getInstance();

    // create the timer
    (void) OMTimerManager::initInstance(OMMainDispatcher::getInstance()->_ioc);

    status = true;

    return status;
    //#]
}

boost::asio::io_context &OXF::getIOContext() {
    return OMMainDispatcher::getInstance()->_ioc;
}