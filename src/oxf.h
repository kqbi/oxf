#ifndef OXF_H
#define OXF_H

#include <string>
#include <boost/asio.hpp>
class  OXF {
public :

    static OXF *getInstance();

    bool initialize();

};

#endif // OXF_H
