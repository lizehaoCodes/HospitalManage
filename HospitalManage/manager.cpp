#include"manager.h"
#include"computerRoom.h"
#include<fstream>
#include"globalFile.h"

#include<algorithm>
//默认构造
manager::manager() {

}

//有参构造
manager::manager(string name, string pwd) {
	this->m_name = name;
	this->m_pwd = pwd;

	this->initvector();//初始化容器

	this->initCom();//初始化机房信息
}

//选择菜单
void manager::operMenu() { 
	cout << "\t\t|---欢迎医院管理员：" << this->m_name << " 登录---|" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号(患者/医生）|\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号(患者/医生）|\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.删除账号(患者/医生）|\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.添加科室            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          7.清空挂号记录        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.退出登录        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "---请选择您的操作：" << endl;
}

//添加账号
void manager::addPerson()
{
	string fileName; //操作文件名
	string tip;  //提示id号
	string errorTip; //重复错误提示

	ofstream ofs;//文件操作对象

	int select = 0;
	while (true) {
		cout << "---请输入添加账号类型---" << endl;
		cout << "---（1）添加学生---" << endl;
		cout << "---（2）添加老师---" << endl;
		cin >> select; //接受用户的选项

		if (select == 1)
		{
			//添加的是学生
			fileName = Student_file;
			tip = "---请输入学号：";
			errorTip = "---学号重复，请重新输入---";
			break;
		}
		else if (select == 2)
		{
			fileName = Teacher_file;
			tip = "---请输入职工编号：";
			errorTip = "---职工号重复，请重新输入---";
			break;
		}
		else
		{
			cout << "---输入无效，请重新输入---" << endl;
		}
	}

	//利用追加的方式 写文件
	ofs.open(fileName, ios::out | ios::app);

	int id; //学号 /职工号
	string name; //姓名
	string pwd; //密码

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) //有重复
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}

	}


	cout << "---请输入姓名：--- " << endl;
	cin >> name;

	cout << "---请输入密码：--- " << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "---添加成功---" << endl;

	system("pause");
	system("cls");

	ofs.close();

	//调用初始化容器接口，从新获取文件中的数据
	this->initvector();
}

//初始化容器
void manager::initvector() {
	v_stu.clear();
	v_tea.clear();

	//读取学生文件中的信息
	ifstream ifs;
	ifs.open(Student_file, ios::in);
	if (!ifs.is_open()) {
		cout << "---文件读取失败---" << endl;
		return;
	}
	users s;
	while (ifs >> s.m_studentId && ifs >> s.m_name && ifs >> s.m_pwd) {
		v_stu.push_back(s);
	}
	cout << "---当前患者的数量为：" << v_stu.size()<<" ---" << endl;
	ifs.close();

	//读取老师文件中的信息
	ifs.open(Teacher_file, ios::in);

	doctor t;
	while (ifs >> t.m_teacherId && ifs >> t.m_name && ifs >> t.m_pwd) {
		v_tea.push_back(t);
	}
	cout << "---当前医生的数量为：" << v_tea.size() <<" ---" << endl;
	ifs.close();
}

//去重函数封装
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

//必须为全局函数
void printstudent(users& s) {
	cout << "患者编号：" << s.m_studentId << "\t姓名：" << s.m_name << "\t密码：" << s.m_pwd << endl;
}
void printteacher(doctor& t) {
	cout << "医生编号：" << t.m_teacherId << "\t医生：" << t.m_name << "\t密码：" << t.m_pwd << endl;
}

//查看账号
void manager::showPerson() {
		
		//不显示可初始化容器强制显示   this->initvector
		
		cout << "---请选择查看的内容：---" << endl;
		cout << "(1)----->查看所有用户" << endl;
		cout << "(2)----->查看所有医生" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) {
			cout << "---所有用户信息如下：---" << endl;
			for_each(v_stu.begin(), v_stu.end(), printstudent);
		}
		else if (select == 2) {
			cout << "---所有医生的信息如下：---" << endl;
			for_each(v_tea.begin(), v_tea.end(), printteacher);
		}
		else {
			cout << "---请按照提示重新输入---" << endl;
		}
		system("pause");
		system("cls");

}
// 删除账号
void manager::deletePerson() {

	//不显示可初始化容器强制显示   this->initvector

	string fileName; // 操作文件名
	string tip;  // 提示id号

	int select = 0;
	while (true) {
		cout << "---请输入删除账号类型---" << endl;
		cout << "---（1）删除用户---" << endl;
		cout << "---（2）删除医生---" << endl;
		cin >> select; // 接受用户的选项

		if (select == 1) {
			// 删除的是学生
			fileName = Student_file;
			tip = "---请输入用户编号：";
			break;
		}
		else if (select == 2) {
			fileName = Teacher_file;
			tip = "---请输入医生编号：";
			break;
		}
		else {
			cout << "---输入无效，请重新输入---" << endl;
		}
	}

	int id; // 学号 /职工号
	cout << tip << endl;
	cin >> id;

	if (select == 1) {
		// 删除学生
		for (vector<users>::iterator it = v_stu.begin(); it != v_stu.end(); it++) {
			if (id == it->m_studentId) {
				v_stu.erase(it);
				break;
			}
		}
	}
	else {
		// 删除老师
		for (vector<doctor>::iterator it = v_tea.begin(); it != v_tea.end(); it++) {
			if (id == it->m_teacherId) {
				v_tea.erase(it);
				break;
			}
		}
	}

	// 更新文件
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

	cout << "---删除成功---" << endl;
	system("pause");
	system("cls");
}
//初始化机房信息
void manager::initCom() {

	ifstream ifs;//获取机房信息

	ifs.open(Computer_file, ios::in);

	computerRoom c;
	while (ifs >> c.m_id && ifs >> c.m_maxNum) {
		v_com.push_back(c);
	}
	cout << "---当前科室的数量为：" << v_com.size()<<" ---" << endl;
}
//添加机房信息
void manager::addComputer() {
	cout << "---请输入科室编号：" << endl;
	int roomId;
	cin >> roomId;

	cout << "---请输入科室最大容量：" << endl;
	int maxNum;
	cin >> maxNum;

	//检查是否已存在相同编号的机房
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		if (it->m_id == roomId) {
			cout << "---科室编号已存在，请重新添加---" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	//创建新的机房对象并添加到容器中
	computerRoom newRoom;
	newRoom.m_id = roomId;
	newRoom.m_maxNum = maxNum;
	v_com.push_back(newRoom);

	//将新的机房信息写回到机房文件中
	ofstream ofs(Computer_file, ios::out | ios::app);
	ofs << roomId << " " << maxNum << endl;
	ofs.close();

	cout << "---科室信息添加成功---" << endl;
	system("pause");
	system("cls");
}
//查看机房信息
void manager::showComputer() {
	cout << "---科室信息如下：---" << endl;
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		cout << "科室编号：" << it->m_id << "\t科室最大容量：" << it->m_maxNum << endl;
	}
	system("pause");
	system("cls");
}

//修改机房信息
void manager::modifyComputer() {
	cout << "---当前科室信息如下：" << endl;
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		cout << "科室编号：" << it->m_id << "\t科室最大容量：" << it->m_maxNum << endl;
	}

	cout << "---请选择要修改的科室编号：" << endl;
	int roomId;
	cin >> roomId;

	cout << "---请输入新的科室最大容量：" << endl;
	int newMaxNum;
	cin >> newMaxNum;

	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		if (it->m_id == roomId) {
			it->m_maxNum = newMaxNum;
			break;
		}
	}

	//将更新后的机房信息写回到机房文件中
	ofstream ofs(Computer_file, ios::out | ios::trunc);
	for (vector<computerRoom>::iterator it = v_com.begin(); it != v_com.end(); it++) {
		ofs << it->m_id << " " << it->m_maxNum << endl;
	}
	ofs.close();

	cout << "---科室信息修改成功---" << endl;
	system("pause");
	system("cls");
}
//清空预约记录
void manager::cleanFile() {
	ofstream ofs(Order_file, ios::trunc);
	ofs.close();

	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}
