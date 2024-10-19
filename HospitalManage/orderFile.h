#pragma once
#include<iostream>
using namespace std;
#include<map>
#include"globalFile.h"

class orderFile {
public:
	//构造函数
	orderFile();

	//更新预约记录
	void updateOrder();

	//记录容器 key:记录的条数 value:-记录单条的信息
	map<int, map<string, string>>m_orderData;
	//预约记录的条数
	int m_size;
};