chatroom.h chatroom.cpp :����������Ի�����chatRoom
chatRoom��
QString sendText; //������Ϣ
QString receiveText;//���յ�����Ϣ



chatroompanel.h chatroompanel.cpp�������˵�½���������Ի����� ChatRoomPanel



fadeinout.h fadeinout.cpp��ʵ���˶Ի����뵭��Ч���ĶԻ�����FadeInOut
FadeInOut��
timerRate��timerRate�����뷢��һ�ν���
changeValue��ÿ����һ�ν���ı�Ľ���ֵ



friendlist.h friendlist.cpp���������������ϴ�ź����б�ĶԻ�����FriendList
FriendList�������ڸ�����ά�������б�����д򿪵����촰��



grouplist.h grouplist.cpp���������������ϴ��Ⱥ���б�ĶԻ�����GroupList




groupchatdialog.h groupchatdialog.cpp��������Ⱥ������ĶԻ�����GroupChatDialog
GroupChatDialog��
QString sendText �����͵���Ϣ
QString receiveText�����յ�����Ϣ




loginconfig.h loginconfig.cpp�������˷��������õĶԻ����ࣺLoginConfig
LoginConfig��
QString serverIP��������IP��ַ
QString serverPort���������˿ں�




logindialog.h logindialog.cpp�������˵�½�����ࣺLoginDialog
LoginDialog:
QString userName���û���½��
QString userPassword���û���½����




registerdialog.h registerdialog.cpp��������ע�ᴰ���� RegisterDialog
RegisterDialog��
QString userName���û���
QString userPassword1:��½����
QString userPassword2��ȷ�ϵ�½����
QString userNickName���û��ǳ�




shakewindow.h shakewindow.cpp�������˶������ڵ��ࣺshakeWindow
shakeWindow��
enum {MaxLimitTimes = 20}����������
enum {MaxLimitSpace = 8}����������
enum {ShakeSpeed = 30}��ShakeSpeed���뷢��һ�ζ���
