#include<iostream>
using namespace std;

#include"globalFile.h"
#include<fstream>

#include"identity.h"
#include"users.h"
#include"doctor.h"
#include"manager.h"

//���˵�
void menu() {
	cout << "======================  ��ӭ����ҽԺԤԼϵͳ  ======================"
		<< endl;
	cout << endl << "�������������:" << endl;
	cout << "\t\t ------------------------------------\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (1)-->�Һ��û�           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (2)-->����ҽ��           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (3)-->�� �� Ա           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (0)-->��    ��           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t ------------------------------------\n";
	cout << "---������ѡ��: ---";
}

//�û��˵�
void studentMenu(identity*& person) {
	while (true) {

		person->operMenu();//ѧ���˵�

		users* stu = (users*)person;

		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1://����ԤԼ
			stu->applyOrder();
			break;
		case 2://�鿴����ԤԼ
			stu->showMyOrder();
			break;
		case 3://�鿴����ԤԼ
			stu->showAllOrder();
			break;
		case 4://ȡ��ԤԼ
			stu->cancelOrder();
			break;
		case 0://ע���˺�
			delete person;
			cout << "---�û��˺ţ�ע���ɹ�---" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "---�밴����ʾ��������---��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//ҽ���˵�
void teacherMenu(identity *&person) {
	while (true) {
		//��ʦ�˵�
		person->operMenu();

		doctor* tea = (doctor*)person;
		int select = 0;

		cin >> select;

		switch (select)
		{
		case 1:
			//�鿴����ԤԼ
			tea->showAllOrder();
			break;
		case 2:
			//���ԤԼ
			tea->validOrder();
			break;
		case 0:
			//ע���˺�
			delete person;
			cout << "---ҽ���˺ţ�ע���ɹ�---" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "---�����������������---" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
}
//����Ա�Ӳ˵�
void managerMenu(identity * &person) {
		while (true) {
			//������д�����еĴ��麯��
			person->operMenu();//�˵�

			manager* man = (manager*)person;//ǿת����������������ӿ�

			int select = 0;
			cin >> select;
			switch (select)
			{
			case 1:
				cout << "---����˺�---" << endl;
				man->addPerson();
				break;
			case 2:
				cout << "---�鿴�˺�---" << endl;
				man->showPerson();
				break;
			case 3:
				cout << "---ɾ���˺�---" << endl;
				man->deletePerson();
				break;
			case 4:
				cout << "---��ӻ���---" << endl;
				man->addComputer();
				break;
			case 5:
				cout << "---�鿴����---" << endl;
				man->showComputer();
				break;
			case 6:
				cout << "---�޸Ļ���---" << endl;
				man->modifyComputer();
				break;
			case 7:
				cout << "---���ԤԼ---" << endl;
				man->cleanFile();
				break;
			case 0:

				delete person;//��Ҫ�ͷ�ָ������

				cout << "---����Ա�˺ţ�ע���ɹ�---" << endl;
				system("pause");
				system("cls");
				return;
			default:
				cout << "---�밴����ʾ��������---��" << endl;
				system("pause");
				system("cls");
				break;
			}
		}

	}

//��¼����
void logIn(string fileName, int type) {
		identity* person = NULL;

		ifstream ifs;
		ifs.open(fileName, ios::in);

		//�ļ������ڵ����
		if (!ifs.is_open()) {
			cout << "�ļ�������" << endl;
			ifs.close();
			return;
		}

		//�û��������Ϣ
		int id = 0;
		string name;
		string pwd;

		if (type == 1) {//�û���¼
			cout << "----�����뻼�߱�ţ�----" << endl;
			cin >> id;
		}
		else if (type == 2) {//ҽ����¼
			cout << "----������ҽ����ţ�----" << endl;
			cin >> id;
		}
		cout << "----�������û�����----" << endl;
		cin >> name;
		cout << "-----���������룺-----" << endl;
		cin >> pwd;

		if (type == 1) {//�û���¼��֤

			//���ļ��ж�ȡ����Ϣ
			int f_id;
			string f_name;
			string f_pwd;

			while (ifs >> f_id && ifs >> f_name && ifs >> f_pwd) {//���ж�ȡ

				if (id == f_id && name == f_name && pwd == f_pwd) {
					cout << "----�û���Ϣ��֤�ɹ����ѵ�¼----" << endl;
					system("pause");
					system("cls");

					person = new users(id, name, pwd);//����ָ��ָ���������
					
					studentMenu(person);//�����û����Ӳ˵�

					return;
				}
			}
		}
		else if (type == 2) {//ҽ����¼��֤

			//���ļ��ж�ȡ����Ϣ
			int f_id;
			string f_name;
			string f_pwd;

			while (ifs >> f_id && ifs >> f_name && ifs >> f_pwd) {//���ո�ָ��ȡ��Ϣ�����ڲ��ṹ�йأ�

				if (id == f_id && name == f_name && pwd == f_pwd) {
					cout << "----ҽ����Ϣ��֤�ɹ����ѵ�¼----" << endl;
					system("pause");
					system("cls");

					person = new doctor(id, name, pwd);//����ָ��ָ���������
					
					teacherMenu(person);//����ҽ�����Ӳ˵�

					return;
				}
			}
		}
		else if (type == 3) {//����Ա��¼��֤

			//���ļ��ж�ȡ����Ϣ
			string f_name;
			string f_pwd;

			while (ifs >> f_name && ifs >> f_pwd) {//���ж�ȡ

				if (name == f_name && pwd == f_pwd) {
					cout << "----����Ա��Ϣ��֤�ɹ����ѵ�¼----" << endl;
					system("pause");
					system("cls");

					person = new manager(name, pwd);//����ָ��ָ���������
					//�������Ա���Ӳ˵�
					managerMenu(person);

					return;
				}
			}
		}

		cout << "----��֤��¼ʧ��----" << endl;

		system("pause");
		system("cls");
		return;
	}

int main() {
		while (true) {
			menu();
			int select = 0;//�û���ѡ��
			cin >> select;
			switch (select)
			{
			case 1://�û����
				logIn(Student_file, 1);
				break;
			case 2://ҽ�����
				logIn(Teacher_file, 2);
				break;
			case 3://����Ա���
				logIn(Admin_file, 3);
				break;
			case 0://�˳�ϵͳ
				cout << "----��ӭ�´�ʹ��----" << endl;
				system("pause");
				system("cls");
				return 0;
				break;
			default:
				cout << "----�����������������룺----" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		system("pause");
		return 0;
	}