#ifndef __PROTOCOL_H
#define __PROTOCOL_H
#include <vector>
#include <string>
enum {
    INVALID_REQUEST
};
const int ERROR = -1;
int requestHandler(std::string &request);
#endif
