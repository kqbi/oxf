#ifndef OXF_H
#define OXF_H

#include <string>
#include <boost/asio.hpp>
class  OXF {
public :

    static OXF *getInstance();

    bool initialize(std::size_t eventPoll, std::size_t timeoutPoll);

    boost::asio::io_context &getIOContext();

};

#endif // OXF_H
