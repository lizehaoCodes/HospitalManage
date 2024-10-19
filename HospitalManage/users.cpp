#include"users.h"
#include<fstream>

//默认构造
users::users() {

}

//有参构造
users::users(int id, string name, string pwd) {
	//初始化属性
	this->m_studentId = id;
	this->m_name = name;
	this->m_pwd = pwd;

	//获取机房信息
	this->getinfo();
}

//菜单界面
void users::operMenu() {
	cout << "\t\t--------欢迎 " << this->m_name << " 用户登录！--------" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请挂号预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消医院预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销账户登录          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "---请选择您的操作：" << endl;
}

//获取机房信息
void users::getinfo() {

	ifstream ifs;//读取文件信息
	ifs.open(Computer_file, ios::in);

	computerRoom c;
	while (ifs >> c.m_id && ifs >> c.m_maxNum) {

		v_com.push_back(c);//将读取的信息放入到容器中
	}

	ifs.close();


}
//申请预约
void users::applyOrder() {
	cout << "---/医院工作时间为周一~周五/---" << endl;
	cout << "/---（1）周一---/" << endl;
	cout << "/---（2）周二---/" << endl;
	cout << "/---（3）周三---/" << endl;
	cout << "/---（4）周四---/" << endl;
	cout << "/---（5）周五---/" << endl;
	cout << "---请输入申请预约的时间：" << endl;

	int date = 0;//日期
	int interval = 0;//时间
	int room = 0;

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "---输入有误，请重新输入---" << endl;
	}

	cout << "---请输入申请预约的时间段：" << endl;
	cout << "---（1）上午---" << endl;
	cout << "---（2）下午---" << endl;

	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "---输入有误，请重新输入---" << endl;
	}
	cout << "---医院服务科室类型：---" << endl;
	cout << "1号科室：急诊科" << endl;
	cout << "2号科室：泌尿科" << endl;
	cout << "3号科室：骨折科" << endl;
	cout << endl;
	for (int i = 0; i < v_com.size(); i++) {

		cout <<"---"<<v_com[i].m_id<<"号科室可预约人员总数：-- - " << v_com[i].m_maxNum << endl;
	}

	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "---输入有误，请重新输入---" << endl;
	}

	cout << "---预约成功！目前审核中---" << endl;
	
	ofstream ofs;//将信息写入文件
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

//查看自身预约
void users::showMyOrder()
{
	orderFile of;
	if (of.m_size == 0)
	{
		cout << "---无预约记录！---" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		//将string（c++）用.c_str() 转为c语言字符串( const char *) 
		//再利用 atoi ( const char *) 转 int
		if (this->m_studentId == atoi(of.m_orderData[i]["stuId"].c_str())) //找到自身预约
		{
			cout << "---预约信息如下：---" << endl;
			cout << "预约日期： 周" << of.m_orderData[i]["date"];
			cout << " 预约时间段： " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			string  a;
			a = of.m_orderData[i]["roomId"];
			if (a == "1") {
				cout << "预约科房：急诊科" << endl;
			}
			else if(a == "2") {
				cout << "预约科房：泌尿科" << endl;
			}
			else if (a == "3") {
				cout << "预约科房：骨折科" << endl;
			}
			string status = "状态： ";
			// 1 审核中  2 已预约  -1 预约失败  0 取消预约
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "预约审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败，审核未通过";
			}
			else
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

//查看所有预约
void users::showAllOrder() {
	orderFile of;
	if (of.m_size == 0)
	{
		cout << "---无预约记录---" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++)
	{
		cout << "---预约信息如下：---" << endl;
		cout << i + 1 << "、 ";

		cout << "预约日期： 周" << of.m_orderData[i]["date"];
		cout << " 预约时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 患者编号：" << of.m_orderData[i]["stuId"];
		cout << " 患者姓名：" << of.m_orderData[i]["stuName"];
		cout << " 预约科房：" << of.m_orderData[i]["roomId"];
		string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "预约审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

//取消预约
void users::cancelOrder() {
	orderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;


	vector<int>v;//当前记录所在位置
	int index = 1;


	for (int i = 0; i < of.m_size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_studentId)//将string转化为int
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、 ";
				cout << "预约日期： 周" << of.m_orderData[i]["date"];
				cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 科房：" << of.m_orderData[i]["roomId"];
				string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;

			}
		}
	}

	cout << "---请输入取消的记录,输入0可取消操作---" << endl;
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
				//	cout << "当前记录所在位置： " << v[select - 1] << endl;
				of.m_orderData[v[select - 1]]["status"] = "0";//v[select-1]相当于v[i]  select相当于index
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}