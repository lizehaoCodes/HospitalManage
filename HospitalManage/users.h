#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include"globalFile.h"
#include<vector>
#include"computerRoom.h"
#include"orderFile.h"
#include<string>
//ѧ����
class users :public identity {
public:
	
	int m_studentId;//ѧ��ѧ��

	//Ĭ�Ϲ���
	users();

	//�вι���
	users(int id, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();
	vector<computerRoom>v_com;//��������
	void getinfo();//��ȡ������Ϣ

	//�鿴�ҵ�ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

};