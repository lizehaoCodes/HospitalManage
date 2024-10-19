#pragma once
#include"identity.h"
#include<vector>
#include"users.h"
#include"doctor.h"
#include"computerRoom.h"

//管理员类
class manager :public identity {
public:
	
	//默认构造
	manager();

	//有参构造
	manager(string name, string pwd);

	//选择菜单
	virtual void operMenu();


	//添加账号
	void addPerson();
	//去重操作  
	void initvector();//初始化容器
	vector<users>v_stu;//学生容器
	vector<doctor>v_tea;//教师容器
	bool checkRepeat(int id, int type); //去重函数

	//查看账号
	void showPerson();	

	//删除账号
	void deletePerson();

	//添加机房信息
	void addComputer();
	vector<computerRoom>v_com;//机房容器
	void initCom();//初始化机房信息

	//查看机房信息
	void showComputer();

	//修改机房信息
	void modifyComputer();


	//清空预约记录
	void cleanFile();


};
