#include "codeChange.h"

QString s2q(const std::string &str){
	QString qstr =QString::fromStdString(str);
	return qstr;
}   


std::string q2s(const QString &qstr){
	std::string str = s.toStdString();
	return str;

}
