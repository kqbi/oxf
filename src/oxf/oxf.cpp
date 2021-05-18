#include "oxf.h"
#include "OMTimerManager.h"
#include "OMMainDispatcher.h"

OXF &OXF::Instance() {
    static OXF oxf;
    return oxf;
}

bool OXF::Initialize() {
    //#[ operation initialize(OxfTimeUnit,Rhp_uint32_t,bool)
    bool status = false;

    // Create the main thread (actually its OXF wrapper)
    (void) OMMainDispatcher::Instance();

    // create the timer
    (void) OMTimerManager::Instance();

    status = true;

    return status;
    //#]
}