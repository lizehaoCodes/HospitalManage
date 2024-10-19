#include"orderFile.h"
#include<fstream>
#include"globalFile.h"
#include<string>
#include<map>
orderFile::orderFile() {
	ifstream ifs;
	ifs.open(Order_file, ios::in);
	string date;      //日期
	string interval;  //时间段
	string stuId;     //学生编号
	string stuName;   //学生姓名
	string roomId;    //机房编号
	string status;    //预约状态


	this->m_size = 0;//记录条数

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//测试代码
		/*
		cout << date << endl;     //date:1
		cout << interval << endl; //interval:1
		cout << stuId << endl;    //stuId:1
		cout << stuName << endl;  //stuName:张三
		cout << roomId << endl;   //roomId:3
		cout << status << endl;   //status:1
		*/


		string key;
		string value;
		map<string, string> m;//记录单条数据的容器


		//date:1
		int pos = date.find(":");//4
		if (pos != -1)
		{
			key = date.substr(0, pos);//date
			value = date.substr(pos + 1, date.size() - pos - 1);//1
			m.insert(make_pair(key, value));
		}

		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}


		this->m_orderData.insert(make_pair(this->m_size, m));//插入到大容器中
		this->m_size++;
	}

	//测试代码
	//for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end();it++)
	//{
	//	cout << "key = " << it->first << " value = " << endl;
	//	for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << mit->first << " " << mit->second << " ";
	//	}
	//	cout << endl;
	//}

	ifs.close();
}
void orderFile::updateOrder() {
	if (this->m_size ==0 ) {
		return;
	}
	
	ofstream ofs(Order_file, ios::out | ios::trunc);
	for (int i = 0; i < this->m_size; i++) {
		ofs << "date:" << this->m_orderData[i]["date"] << " ";//通过键来访问值
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
	ofs.close();
	}