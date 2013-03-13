CREATE TABLE "User" (
    "user_id" integer NOT NULL PRIMARY KEY,
    "u_name" varchar(50) NOT NULL,
    "pwd" varchar(20) NOT NULL,
    "previlege" integer NOT NULL,
    "info" varchar(250) NOT NULL
)
;
CREATE TABLE "Group" (
    "group_id" integer NOT NULL PRIMARY KEY,
    "creator_id" integer NOT NULL REFERENCES "User" ("user_id"),
    "g_name" varchar(50) NOT NULL,
    "g_info" varchar(250) NOT NULL
)
;
CREATE TABLE "User_Group" (
    "id" integer NOT NULL PRIMARY KEY,
    "user_id" integer NOT NULL REFERENCES "User" ("user_id"),
    "group_id" integer NOT NULL REFERENCES "Group" ("group_id")
)
;
CREATE TABLE "Message" (
    "id" integer NOT NULL PRIMARY KEY,
    "group_id" integer NOT NULL REFERENCES "Group" ("group_id"),
    "user_id" integer NOT NULL REFERENCES "User" ("user_id"),
    "send_time" datetime NOT NULL,
    "m_type" integer NOT NULL,
    "content" varchar(500) NOT NULL
)
;

