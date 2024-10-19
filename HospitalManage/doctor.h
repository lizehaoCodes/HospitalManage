#pragma once
#include"identity.h"
#include"orderFile.h"
#include<vector>
//老师类
class doctor :public identity {
public:

	int m_teacherId;//职工编号

	//默认构造
	doctor();

	//有参构造
	doctor(int id, string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();


};