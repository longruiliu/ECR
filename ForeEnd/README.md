chatroom.h chatroom.cpp :定义了聊天对话框类chatRoom
chatRoom：
QString sendText; //发送消息
QString receiveText;//接收到的消息



chatroompanel.h chatroompanel.cpp：定义了登陆后的主界面对话框类 ChatRoomPanel



fadeinout.h fadeinout.cpp：实现了对话框淡入淡出效果的对话框类FadeInOut
FadeInOut：
timerRate：timerRate个毫秒发生一次渐变
changeValue：每发生一次渐变改变的渐变值



friendlist.h friendlist.cpp：定义了主界面上存放好友列表的对话框类FriendList
FriendList：可以在该类中维护好友列表和所有打开的聊天窗口



grouplist.h grouplist.cpp：定义了主界面上存放群组列表的对话框类GroupList




groupchatdialog.h groupchatdialog.cpp：定义了群组聊天的对话框类GroupChatDialog
GroupChatDialog：
QString sendText ：发送的消息
QString receiveText：接收到的消息




loginconfig.h loginconfig.cpp：定义了服务器配置的对话框类：LoginConfig
LoginConfig：
QString serverIP：服务器IP地址
QString serverPort：服务器端口号




logindialog.h logindialog.cpp：定义了登陆窗口类：LoginDialog
LoginDialog:
QString userName：用户登陆名
QString userPassword：用户登陆密码




registerdialog.h registerdialog.cpp：定义了注册窗口类 RegisterDialog
RegisterDialog：
QString userName：用户名
QString userPassword1:登陆密码
QString userPassword2：确认登陆密码
QString userNickName：用户昵称




shakewindow.h shakewindow.cpp：定义了抖动窗口的类：shakeWindow
shakeWindow：
enum {MaxLimitTimes = 20}：抖动次数
enum {MaxLimitSpace = 8}：抖动幅度
enum {ShakeSpeed = 30}：ShakeSpeed毫秒发送一次抖动
