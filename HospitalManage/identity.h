#pragma once
#include<iostream>
using namespace std;

//身份抽象基类
class identity {
public:
	//用户名
	string m_name;
	//密码
	string m_pwd;

	//操作菜单 纯虚函数
	virtual void operMenu() = 0;
};
