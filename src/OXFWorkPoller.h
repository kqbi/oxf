//
// Created by kqbi on 2020/4/21.
//

#ifndef OXF_WORKPOLLER_H
#define OXF_WORKPOLLER_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class OXFWorkPollerPool {
public:
    typedef boost::asio::executor_work_guard<boost::asio::io_context::executor_type> io_context_work;

    OXFWorkPollerPool();

    ~OXFWorkPollerPool();

    //单例创建前有效
    static void SetPoolSize(int size = 0);

    static OXFWorkPollerPool &Instance();

    boost::asio::io_context _ioc;
    boost::thread_group _threads;
    static int _pool_size;
    io_context_work _work;
};


#endif //OXF_EVENTPOLLER_H
