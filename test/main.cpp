#include "testS.h"
#include "oxf.h"
#include <signal.h>
#include <iostream>

static bool finished = false;

static void signalHandler(int signo) {
    std::cerr << "Shutting down" << std::endl;
    finished = true;
}

int main(int argc, char *argv[]) {
    OXF::getInstance()->initialize(0, 0);
    std::shared_ptr <testS> test = std::make_shared<testS>();
    test->startBehavior();
    test->GEN(evPoll);
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        std::cerr << "Couldn't install signal handler for SIGINT" << std::endl;
        exit(-1);
    }

    if (signal(SIGTERM, signalHandler) == SIG_ERR) {
        std::cerr << "Couldn't install signal handler for SIGTERM" << std::endl;
        exit(-1);
    }

    while (!finished) {
        printf("qqqqqqqqqqqqq\n");
#ifdef WIN32
        Sleep(1000);
#else
        usleep(1000*1000);
#endif
    }
printf("ddddddddddddddddd\n");
    return 0;
}
