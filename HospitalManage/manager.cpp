#include"manager.h"
#include"computerRoom.h"
#include<fstream>
#include"globalFile.h"

#include<algorithm>
//Ĭ�Ϲ���
manager::manager() {

}

//�вι���
manager::manager(string name, string pwd) {
	this->m_name = name;
	this->m_pwd = pwd;

	this->initvector();//��ʼ������

	this->initCom();//��ʼ��������Ϣ
}

//ѡ��˵�
void manager::operMenu() { 
	cout << "\t\t|---��ӭҽԺ����Ա��" << this->m_name << " ��¼---|" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�(����/ҽ����|\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�(����/ҽ����|\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.ɾ���˺�(����/ҽ����|\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.��ӿ���            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          7.��չҺż�¼        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.�˳���¼        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "---��ѡ�����Ĳ�����" << endl;
}

//����˺�
void manager::addPerson()
{
	string fileName; //�����ļ���
	string tip;  //��ʾid��
	string errorTip; //�ظ�������ʾ

	ofstream ofs;//�ļ���������

	int select = 0;
	while (true) {
		cout << "---����������˺�����---" << endl;
		cout << "---��1�����ѧ��---" << endl;
		cout << "---��2�������ʦ---" << endl;
		cin >> select; //�����û���ѡ��

		if (select == 1)
		{
			//��ӵ���ѧ��
			fileName = Student_file;
			tip = "---������ѧ�ţ�";
			errorTip = "---ѧ���ظ�������������---";
			break;
		}
		else if (select == 2)
		{
			fileName = Teacher_file;
			tip = "---������ְ����ţ�";
			errorTip = "---ְ�����ظ�������������---";
			break;
		}
		else
		{
			cout << "---������Ч������������---" << endl;
		}
	}

	//����׷�ӵķ�ʽ д�ļ�
	ofs.open(fileName, ios::out | ios::app);

	int id; //ѧ�� /ְ����
	string name; //����
	string pwd; //����

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) //���ظ�
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}

	}


	cout << "---������������--- " << endl;
	cin >> name;

	cout << "---���������룺--- " << endl;
	cin >> pwd;

	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "---��ӳɹ�---" << endl;

	system("pause");
	system("cls");

	ofs.close();

	//���ó�ʼ�������ӿڣ����»�ȡ�ļ��е�����
	this->initvector();
}

//��ʼ������
void manager::initvector() {
	v_stu.clear();
	v_tea.clear();

	//��ȡѧ���ļ��е���Ϣ
	ifstream ifs;
	ifs.open(Student_file, ios::in);
	if (!ifs.is_open()) {
		cout << "---�ļ���ȡʧ��---" << endl;
		return;
	}
	users s;
	while (ifs >> s.m_studentId && ifs >> s.m_name && ifs >> s.m_pwd) {
		v_stu.push_back(s);
	}
	cout << "---��ǰ���ߵ�����Ϊ��" << v_stu.size()<<" ---" << endl;
	ifs.close();

	//��ȡ��ʦ�ļ��е���Ϣ
	ifs.open(Teacher_file, ios::in);

	doctor t;
	while (ifs >> t.m_teacherId && ifs >> t.m_name && ifs >> t.m_pwd) {
		v_tea.push_back(t);
	}
	cout << "---��ǰҽ��������Ϊ��" << v_tea.size() <<" ---" << endl;
	ifs.close();
}

//ȥ�غ�����װ
bool manager::checkRepeat(int id, int type) {
	if (type == 1) {
		for (vector<users>::iterator it = v_stu.begin(); it != v_stu.end(); it++) {
			if (id == it->m_studentId) {
				return true;
			}
		}
	}
	else {
		for (vector<doctor>::iterator it = v_tea.begin(); it != v_tea.end(); it++) {
			if (id == it->m_teacherId) {
				return true;
			}
		}
	}
	return false;
}

//����Ϊȫ�ֺ���
void printstudent(users& s) {
	cout << "���߱�ţ�" << s.m_studentId << "\t������" << s.m_name << "\t���룺" << s.m_pwd << endl;
}
void printteacher(doctor& t) {
	cout << "ҽ����ţ�" << t.m_teacherId << "\tҽ����" << t.m_name << "\t���룺" << t.m_pwd << endl;
}

//�鿴�˺�
void manager::showPerson() {
		
		//����ʾ�ɳ�ʼ������ǿ����ʾ   this->initvector
		
		cout << "---��ѡ��鿴�����ݣ�---" << endl;
		cout << "(1)----->�鿴�����û�" << endl;
		cout << "(2)----->�鿴����ҽ��" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) {
			cout << "---�����û���Ϣ���£�---" << endl;
			for_each(v_stu.begin(), v_stu.end(), printstudent);
		}
		else if (select == 2) {
			cout << "---����ҽ������Ϣ���£�---" << endl;
			for_each(v_tea.begin(), v_tea.end(), printteacher);
		}
		else {
			cout << "---�밴����ʾ��������---" << endl;
		}
		system("pause");
		system("cls");

}
// ɾ���˺�
void manager::deletePerson() {

	//����ʾ�ɳ�ʼ������ǿ����ʾ   this->initvector

	string fileName; // �����ļ���
	string tip;  // ��ʾid��

	int select = 0;
	while (true) {
		cout << "---������ɾ���˺�����---" << endl;
		cout << "---��1��ɾ���û�---" << endl;
		cout << "---��2��ɾ��ҽ��---" << endl;
		cin >> select; // �����û���ѡ��

		if (select == 1) {
			// ɾ������ѧ��
			fileName = Student_file;
			tip = "---�������û���ţ�";
			break;
		}
		else if (select == 2) {
			fileName = Teacher_file;
			tip = "---������ҽ����ţ�";
			break;
		}
		else {
			cout << "---������Ч������������---" << endl;
		}
	}

	int id; // ѧ�� /ְ����
	cout << tip << endl;
	cin >> id;

	if (select == 1) {
		// ɾ��ѧ��
		for (vector<users>::iterator it = v_stu.begin(); it != v_stu.end(); it++) {
			if (id == it->m_studentId) {
				v_stu.erase(it);
				break;
			}
		}
	}
	else {
		// ɾ����ʦ
		for (vector<doctor>::iterator it = v_tea.begin(); it != v_tea.end(); it++) {
			if (id == it->m_teacherId) {
				v_tea.erase(it);
				break;
			}
		}
	}

	// �����ļ�
	ofstream ofs(fileName, ios::out | ios::trunc);
	if (select == 1) {
		for (vector<users>::iterator it = v_stu.begin(); it != v_stu.end(); it++) {
			ofs << it->m_studentId << " " << it->m_name << " " << it->m_pwd << endl;
		}
	}
	else {
		for (vector<doctor>::iterator it = v_tea.begin(); it != v_tea.end(); it++) {
			ofs << it->m_teacherId << " " << it->m_name << " " << it->m_pwd << endl;
		}
	}

	ofs.close();

	cout << "---ɾ���ɹ�---" << endl;
	system("pause");
	system("cls");
}
//��ʼ��������Ϣ
void manager::initCom() {

	ifstream ifs;//��ȡ������Ϣ

	ifs.open(Computer_file, ios::in);

	computerRoom c;
	while (ifs >> c.m_id && ifs >> c.m_maxNum) {
		v_com.push_back(c);
	}
	cout << "---��ǰ���ҵ�����Ϊ��" << v_com.size()<<" ---" << endl;
}
//��ӻ�����Ϣ
void manager::addComputer() {
	cout << "---��������ұ�ţ�" << endl;
	int roomId;
	cin >> roomId;

	cout << "---������������������" << endl;
	int maxNum;
	cin >> maxNum;

	//����Ƿ��Ѵ�����ͬ��ŵĻ���
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		if (it->m_id == roomId) {
			cout << "---���ұ���Ѵ��ڣ����������---" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	//�����µĻ���������ӵ�������
	computerRoom newRoom;
	newRoom.m_id = roomId;
	newRoom.m_maxNum = maxNum;
	v_com.push_back(newRoom);

	//���µĻ�����Ϣд�ص������ļ���
	ofstream ofs(Computer_file, ios::out | ios::app);
	ofs << roomId << " " << maxNum << endl;
	ofs.close();

	cout << "---������Ϣ��ӳɹ�---" << endl;
	system("pause");
	system("cls");
}
//�鿴������Ϣ
void manager::showComputer() {
	cout << "---������Ϣ���£�---" << endl;
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		cout << "���ұ�ţ�" << it->m_id << "\t�������������" << it->m_maxNum << endl;
	}
	system("pause");
	system("cls");
}

//�޸Ļ�����Ϣ
void manager::modifyComputer() {
	cout << "---��ǰ������Ϣ���£�" << endl;
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		cout << "���ұ�ţ�" << it->m_id << "\t�������������" << it->m_maxNum << endl;
	}

	cout << "---��ѡ��Ҫ�޸ĵĿ��ұ�ţ�" << endl;
	int roomId;
	cin >> roomId;

	cout << "---�������µĿ������������" << endl;
	int newMaxNum;
	cin >> newMaxNum;

	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		if (it->m_id == roomId) {
			it->m_maxNum = newMaxNum;
			break;
		}
	}

	//�����º�Ļ�����Ϣд�ص������ļ���
	ofstream ofs(Computer_file, ios::out | ios::trunc);
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		ofs << it->m_id << " " << it->m_maxNum << endl;
	}
	ofs.close();

	cout << "---������Ϣ�޸ĳɹ�---" << endl;
	system("pause");
	system("cls");
}
//���ԤԼ��¼
void manager::cleanFile() {
	ofstream ofs(Order_file, ios::trunc);
	ofs.close();

	cout << "��ճɹ�" << endl;
	system("pause");
	system("cls");
}
