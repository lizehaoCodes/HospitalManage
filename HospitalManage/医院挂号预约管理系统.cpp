#include<iostream>
using namespace std;

#include"globalFile.h"
#include<fstream>

#include"identity.h"
#include"users.h"
#include"doctor.h"
#include"manager.h"

//主菜单
void menu() {
	cout << "======================  欢迎来到医院预约系统  ======================"
		<< endl;
	cout << endl << "请输入您的身份:" << endl;
	cout << "\t\t ------------------------------------\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (1)-->挂号用户           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (2)-->科室医生           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (3)-->管 理 员           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t|          (0)-->退    出           |\n";
	cout << "\t\t|                                   |\n";
	cout << "\t\t ------------------------------------\n";
	cout << "---请输入选项: ---";
}

//用户菜单
void studentMenu(identity*& person) {
	while (true) {

		person->operMenu();//学生菜单

		users* stu = (users*)person;

		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1://申请预约
			stu->applyOrder();
			break;
		case 2://查看自身预约
			stu->showMyOrder();
			break;
		case 3://查看所有预约
			stu->showAllOrder();
			break;
		case 4://取消预约
			stu->cancelOrder();
			break;
		case 0://注销账号
			delete person;
			cout << "---用户账号，注销成功---" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "---请按照提示重新输入---：" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//医生菜单
void teacherMenu(identity *&person) {
	while (true) {
		//教师菜单
		person->operMenu();

		doctor* tea = (doctor*)person;
		int select = 0;

		cin >> select;

		switch (select)
		{
		case 1:
			//查看所有预约
			tea->showAllOrder();
			break;
		case 2:
			//审核预约
			tea->validOrder();
			break;
		case 0:
			//注销账号
			delete person;
			cout << "---医生账号，注销成功---" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "---输入错误，请重新输入---" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
}
//管理员子菜单
void managerMenu(identity * &person) {
		while (true) {
			//子类重写父类中的纯虚函数
			person->operMenu();//菜单

			manager* man = (manager*)person;//强转成子类对象调用子类接口

			int select = 0;
			cin >> select;
			switch (select)
			{
			case 1:
				cout << "---添加账号---" << endl;
				man->addPerson();
				break;
			case 2:
				cout << "---查看账号---" << endl;
				man->showPerson();
				break;
			case 3:
				cout << "---删除账号---" << endl;
				man->deletePerson();
				break;
			case 4:
				cout << "---添加机房---" << endl;
				man->addComputer();
				break;
			case 5:
				cout << "---查看机房---" << endl;
				man->showComputer();
				break;
			case 6:
				cout << "---修改机房---" << endl;
				man->modifyComputer();
				break;
			case 7:
				cout << "---清空预约---" << endl;
				man->cleanFile();
				break;
			case 0:

				delete person;//需要释放指针引用

				cout << "---管理员账号，注销成功---" << endl;
				system("pause");
				system("cls");
				return;
			default:
				cout << "---请按照提示重新输入---：" << endl;
				system("pause");
				system("cls");
				break;
			}
		}

	}

//登录功能
void logIn(string fileName, int type) {
		identity* person = NULL;

		ifstream ifs;
		ifs.open(fileName, ios::in);

		//文件不存在的情况
		if (!ifs.is_open()) {
			cout << "文件不存在" << endl;
			ifs.close();
			return;
		}

		//用户输入的信息
		int id = 0;
		string name;
		string pwd;

		if (type == 1) {//用户登录
			cout << "----请输入患者编号：----" << endl;
			cin >> id;
		}
		else if (type == 2) {//医生登录
			cout << "----请输入医生编号：----" << endl;
			cin >> id;
		}
		cout << "----请输入用户名：----" << endl;
		cin >> name;
		cout << "-----请输入密码：-----" << endl;
		cin >> pwd;

		if (type == 1) {//用户登录验证

			//从文件中读取的信息
			int f_id;
			string f_name;
			string f_pwd;

			while (ifs >> f_id && ifs >> f_name && ifs >> f_pwd) {//按行读取

				if (id == f_id && name == f_name && pwd == f_pwd) {
					cout << "----用户信息验证成功，已登录----" << endl;
					system("pause");
					system("cls");

					person = new users(id, name, pwd);//父类指针指向子类对象
					
					studentMenu(person);//进入用户的子菜单

					return;
				}
			}
		}
		else if (type == 2) {//医生登录验证

			//从文件中读取的信息
			int f_id;
			string f_name;
			string f_pwd;

			while (ifs >> f_id && ifs >> f_name && ifs >> f_pwd) {//按空格分割读取信息（与内部结构有关）

				if (id == f_id && name == f_name && pwd == f_pwd) {
					cout << "----医生信息验证成功，已登录----" << endl;
					system("pause");
					system("cls");

					person = new doctor(id, name, pwd);//父类指针指向子类对象
					
					teacherMenu(person);//进入医生的子菜单

					return;
				}
			}
		}
		else if (type == 3) {//管理员登录验证

			//从文件中读取的信息
			string f_name;
			string f_pwd;

			while (ifs >> f_name && ifs >> f_pwd) {//按行读取

				if (name == f_name && pwd == f_pwd) {
					cout << "----管理员信息验证成功，已登录----" << endl;
					system("pause");
					system("cls");

					person = new manager(name, pwd);//父类指针指向子类对象
					//进入管理员的子菜单
					managerMenu(person);

					return;
				}
			}
		}

		cout << "----验证登录失败----" << endl;

		system("pause");
		system("cls");
		return;
	}

int main() {
		while (true) {
			menu();
			int select = 0;//用户的选择
			cin >> select;
			switch (select)
			{
			case 1://用户身份
				logIn(Student_file, 1);
				break;
			case 2://医生身份
				logIn(Teacher_file, 2);
				break;
			case 3://管理员身份
				logIn(Admin_file, 3);
				break;
			case 0://退出系统
				cout << "----欢迎下次使用----" << endl;
				system("pause");
				system("cls");
				return 0;
				break;
			default:
				cout << "----输入有误，请重新输入：----" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		system("pause");
		return 0;
	}