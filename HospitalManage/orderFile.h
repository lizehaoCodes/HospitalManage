#pragma once
#include<iostream>
using namespace std;
#include<map>
#include"globalFile.h"

class orderFile {
public:
	//���캯��
	orderFile();

	//����ԤԼ��¼
	void updateOrder();

	//��¼���� key:��¼������ value:-��¼��������Ϣ
	map<int, map<string, string>>m_orderData;
	//ԤԼ��¼������
	int m_size;
};