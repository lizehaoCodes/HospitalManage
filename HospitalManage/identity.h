#pragma once
#include<iostream>
using namespace std;

//��ݳ������
class identity {
public:
	//�û���
	string m_name;
	//����
	string m_pwd;

	//�����˵� ���麯��
	virtual void operMenu() = 0;
};
