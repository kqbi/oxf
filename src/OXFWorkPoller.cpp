//
// Created by kqbi on 2020/4/21.
//

#include "OXFWorkPoller.h"

int OXFWorkPollerPool::_pool_size = 0;

OXFWorkPollerPool::OXFWorkPollerPool() : _work(boost::asio::make_work_guard(_ioc)) {
    auto size = _pool_size ? _pool_size : 2 * boost::thread::hardware_concurrency();
    for (int i = 0; i < size; ++i) {
        _threads.create_thread(boost::bind(&boost::asio::io_context::run, &_ioc));
    }
}

OXFWorkPollerPool::~OXFWorkPollerPool() {
    _ioc.stop();
    _threads.join_all();
}

void OXFWorkPollerPool::SetPoolSize(int size) {
    _pool_size = size;
}

OXFWorkPollerPool &OXFWorkPollerPool::Instance() {
    static OXFWorkPollerPool pollerPool;
    return pollerPool;
}