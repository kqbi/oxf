//
// Created by kqbi on 2020/4/21.
//

#include "OXFEventPoller.h"

int OXFEventPollerPool::_pool_size = 0;

OXFEventPollerPool::OXFEventPollerPool() : _work(boost::asio::make_work_guard(_ioc)) {
    auto size = _pool_size ? _pool_size : 2 * boost::thread::hardware_concurrency();
    for (int i = 0; i < size; ++i) {
        _threads.create_thread(boost::bind(&boost::asio::io_context::run, &_ioc));
    }
}

OXFEventPollerPool::~OXFEventPollerPool() {
    printf("~OXFEventPollerPool\n");
    _ioc.stop();
    _threads.join_all();
}

void OXFEventPollerPool::SetPoolSize(int size) {
    _pool_size = size;
}

OXFEventPollerPool *OXFEventPollerPool::Instance() {
    static OXFEventPollerPool pollerPool;
    return &pollerPool;
}