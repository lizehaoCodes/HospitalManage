#pragma once
#include"identity.h"
#include"orderFile.h"
#include<vector>
//��ʦ��
class doctor :public identity {
public:

	int m_teacherId;//ְ�����

	//Ĭ�Ϲ���
	doctor();

	//�вι���
	doctor(int id, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();


};