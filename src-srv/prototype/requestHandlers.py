from group import *
from user import *

requestHandlers = {
    "regular": {
        "add": {"func": addUser, "args": [int]},
        "del": {"func": delUser, "args": [int]},
        }
    "group": {
        "add": {"func": addGroup, "args": [str, int]},
        "del": {"func": delGroup, "args": [int]},
        }
    }
