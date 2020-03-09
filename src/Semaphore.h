//
// Created by kqbi on 2019/12/22.
//

#ifndef UNTITLED_SEMAPHORE_H
#define UNTITLED_SEMAPHORE_H

#include <mutex>
class Semaphore {
public:
    explicit Semaphore(int count = 0) : count_(count) {
    }

    void Signal() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++count_;
        cv_.notify_one();
    }

    void Wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [=] { return count_ > 0; });
        --count_;
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
};


#endif //UNTITLED_SEMAPHORE_H
