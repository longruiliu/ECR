#ifndef __PROTOCOL_H
#define __PROTOCOL_H
/* OP table */
#include <vector>
#include <string>

enum {
    ADDGROUP, DELGROUP, ADDUSER, DELUSER,
    JOINREQ, QUITREQ, USERLIST, REDMSG,
    LOGIN, LOGOUT, SENDMSG, USERINFO, STATUS;
};

struct Request {
    int sessionID, op;
    std::string payload;
};

struct Response {
    int token;
    std::string payload;
};
#endif
