#ifndef __PROTOCOL_H
#define __PROTOCOL_H
#include <vector>
#include <string>
enum {
    ERR_INVALID_REQUEST
};
const int ERROR = -1;
int requestHandler(std::string &request);
#endif
