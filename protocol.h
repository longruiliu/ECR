#ifndef __PROTOCOL_H
#define __PROTOCOL_H
#include <vector>
enum {
    INVALID_REQUEST
};
const int ERROR = -1;
int requestHandler(std::string &request, std::string &responese);
#endif
