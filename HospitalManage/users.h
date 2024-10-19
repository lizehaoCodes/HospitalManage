#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include"globalFile.h"
#include<vector>
#include"computerRoom.h"
#include"orderFile.h"
#include<string>
//学生类
class users :public identity {
public:
	
	int m_studentId;//学生学号

	//默认构造
	users();

	//有参构造
	users(int id, string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//申请预约
	void applyOrder();
	vector<computerRoom>v_com;//机房容器
	void getinfo();//获取机房信息

	//查看我的预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

};