#include"users.h"
#include<fstream>

//Ĭ�Ϲ���
users::users() {

}

//�вι���
users::users(int id, string name, string pwd) {
	//��ʼ������
	this->m_studentId = id;
	this->m_name = name;
	this->m_pwd = pwd;

	//��ȡ������Ϣ
	this->getinfo();
}

//�˵�����
void users::operMenu() {
	cout << "\t\t--------��ӭ " << this->m_name << " �û���¼��--------" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����Һ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.ȡ��ҽԺԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע���˻���¼          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "---��ѡ�����Ĳ�����" << endl;
}

//��ȡ������Ϣ
void users::getinfo() {

	ifstream ifs;//��ȡ�ļ���Ϣ
	ifs.open(Computer_file, ios::in);

	computerRoom c;
	while (ifs >> c.m_id && ifs >> c.m_maxNum) {

		v_com.push_back(c);//����ȡ����Ϣ���뵽������
	}

	ifs.close();


}
//����ԤԼ
void users::applyOrder() {
	cout << "---/ҽԺ����ʱ��Ϊ��һ~����/---" << endl;
	cout << "/---��1����һ---/" << endl;
	cout << "/---��2���ܶ�---/" << endl;
	cout << "/---��3������---/" << endl;
	cout << "/---��4������---/" << endl;
	cout << "/---��5������---/" << endl;
	cout << "---����������ԤԼ��ʱ�䣺" << endl;

	int date = 0;//����
	int interval = 0;//ʱ��
	int room = 0;

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "---������������������---" << endl;
	}

	cout << "---����������ԤԼ��ʱ��Σ�" << endl;
	cout << "---��1������---" << endl;
	cout << "---��2������---" << endl;

	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "---������������������---" << endl;
	}
	cout << "---ҽԺ����������ͣ�---" << endl;
	cout << "1�ſ��ң������" << endl;
	cout << "2�ſ��ң������" << endl;
	cout << "3�ſ��ң����ۿ�" << endl;
	cout << endl;
	for (int i = 0; i < v_com.size(); i++) {

		cout <<"---"<<v_com[i].m_id<<"�ſ��ҿ�ԤԼ��Ա������-- - " << v_com[i].m_maxNum << endl;
	}

	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "---������������������---" << endl;
	}

	cout << "---ԤԼ�ɹ���Ŀǰ�����---" << endl;
	
	ofstream ofs;//����Ϣд���ļ�
	ofs.open(Order_file, ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_studentId << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");


}

//�鿴����ԤԼ
void users::showMyOrder()
{
	orderFile of;
	if (of.m_size == 0)
	{
		cout << "---��ԤԼ��¼��---" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		//��string��c++����.c_str() תΪc�����ַ���( const char *) 
		//������ atoi ( const char *) ת int
		if (this->m_studentId == atoi(of.m_orderData[i]["stuId"].c_str())) //�ҵ�����ԤԼ
		{
			cout << "---ԤԼ��Ϣ���£�---" << endl;
			cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
			cout << " ԤԼʱ��Σ� " << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			string  a;
			a = of.m_orderData[i]["roomId"];
			if (a == "1") {
				cout << "ԤԼ�Ʒ��������" << endl;
			}
			else if(a == "2") {
				cout << "ԤԼ�Ʒ��������" << endl;
			}
			else if (a == "3") {
				cout << "ԤԼ�Ʒ������ۿ�" << endl;
			}
			string status = "״̬�� ";
			// 1 �����  2 ��ԤԼ  -1 ԤԼʧ��  0 ȡ��ԤԼ
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "ԤԼ�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void users::showAllOrder() {
	orderFile of;
	if (of.m_size == 0)
	{
		cout << "---��ԤԼ��¼---" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++)
	{
		cout << "---ԤԼ��Ϣ���£�---" << endl;
		cout << i + 1 << "�� ";

		cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
		cout << " ԤԼʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ���߱�ţ�" << of.m_orderData[i]["stuId"];
		cout << " ����������" << of.m_orderData[i]["stuName"];
		cout << " ԤԼ�Ʒ���" << of.m_orderData[i]["roomId"];
		string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "ԤԼ�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "���δͨ����ԤԼʧ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

//ȡ��ԤԼ
void users::cancelOrder() {
	orderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;


	vector<int>v;//��ǰ��¼����λ��
	int index = 1;


	for (int i = 0; i < of.m_size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_studentId)//��stringת��Ϊint
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "�� ";
				cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
				cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " �Ʒ���" << of.m_orderData[i]["roomId"];
				string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;

			}
		}
	}

	cout << "---������ȡ���ļ�¼,����0��ȡ������---" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//	cout << "��ǰ��¼����λ�ã� " << v[select - 1] << endl;
				of.m_orderData[v[select - 1]]["status"] = "0";//v[select-1]�൱��v[i]  select�൱��index
				of.updateOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}