#include "testS.h"
#include "oxf.h"
#include <signal.h>
#include <iostream>
#include <Poller/Timer.h>
#include "Poller/EventPoller.h"

static bool finished = false;

static void signalHandler(int signo) {
    std::cerr << "Shutting down" << std::endl;
    finished = true;
}

#if 0
int main(int argc, char *argv[]) {
    OXF::Instance().Initialize();
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
#endif

int main(int argc, char *argv[]) {
#if 0
    auto pool = oxf::EventPollerPool::Instance().getPoller();
    pool->async([]() {
        printf("111111111111111\n");
    });

    auto t = std::make_shared<oxf::Timer>(1, []() {
        printf("222222222222222222222\n");
        return true;
    }, nullptr);
#endif

    OXF::Instance().Initialize();
    std::shared_ptr <testS> test = std::make_shared<testS>();
    test->startBehavior();
    test->GEN(evPoll);

#ifdef WIN32
    Sleep(3000);
#else
    usleep(3 * 1000*1000);
#endif
    test->GEN(evEnd);

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
