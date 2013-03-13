#ifndef _PROTOCOL_CONST_H_
#define _PROTOCOL_CONST_H_ 
enum{
    ERR_SESSIONID_EXPECTED, 
    ERR_METHOD_EXPECTED, 
    ERR_TYPE_EXPECTED, 
    ERR_PARAMS_EXPECTED, 
    ERR_INVALID_METHOD, 
    ERR_INVALID_PARAMS, 
    ERR_INVALID_TYPE, 
    ERR_OK, 
    ERR_NOT_IN_GROUP,
    ERR_NO_PRIVILEGE,
    ERR_WRONG_PASSWD
};

#define MSG_TYPE_GROUP_REQ  0
#define MSG_TYPE_P2P_MSG  1
#define MSG_TYPE_UNKNOWN 2
#define MSG_JOIN_GROUP_REQ  3
#define MSG_GROUP_REQ_GRANT  4

#define NOTIFY_GROUP_MSG  0
#define NOTIFY_P2P_MSG  1


#define PRIVILEGE_MASK_GROUPMG 0x1
#define PRIVILEGE_MASK_USERMG 0x2
#define PRIVILEGE_MASK_ROOT  0x4
#endif /* _PROTOCOL_CONST_H_ */
