#include "Controller.h"

// 输入选项
const string options[38] = {
	"龙溪",		// 0
	"菊树",		// 1
	"西塱",		// 2
	"坑口",		// 3
	"花地湾",	// 4
	"芳村",		// 5
	"黄沙",		// 6
	"陈家祠",	// 7
	"长寿路",	// 8
	"西门口",	// 9
	"公园前",	// 10
	"农讲所",	// 11
	"烈士陵园",	// 12
	"东山口",	// 13
	"杨箕",		// 14
	"体育西路",	// 15
	"石牌桥",	// 16
	"岗顶",		// 17
	"华师",		// 18
	"五山",		// 19
	"天河客运站",	// 20
	"机场",		// 21
	"高增",		// 22
	"嘉禾望岗",	// 23
	"白云公园",	// 24
	"广州火车站", // 25
	"海珠公园",	// 26
	"昌岗",		// 27
	"南州",		// 28
	"广州南站",	// 29
	"广州东站",	// 30
	"林和西",	// 31
	"珠江新城",	// 32
	"广州塔",	// 33
	"客村",		// 34
	"沥滘",		// 35
	"汉溪长隆",	// 36
	"番禺广场"	// 37
};


// 欢迎页面
void WelCome() {
	cout << "---------------------------------------------" << endl;
	cout << "|          欢迎使用广州地铁线路导航程序      |" << endl;
	cout << "|              Author: 赵汝权                |" << endl;
	cout << "|              ID: 20202005005               |" << endl;
	cout << "|              Date: 2021-12-05              |" << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl << endl;
}

// 地铁线路图设计
void GraphDisplay() {
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                        机场(21)                                                                                                              |" << endl;
	cout << "                                          |                                                                                                                   |" << endl;
	cout << "                                        高增(22)                                                                                                              |" << endl;
	cout << "                                          |                                                                                                                   |" << endl;
	cout << "                                       嘉禾望岗(23)                                                                                                           |" << endl;
	cout << "                                      /        \\                                                                                                             |" << endl;
	cout << "                                     /          \\                                                                                                            |" << endl;
	cout << "                              白云公园(24)     广州东站(30)                                                                                                   |" << endl;
	cout << "                                 |                    |                                                                                                       |" << endl;
	cout << "                             广州火车站(25)           |------------林和西(31)-----------\\                                                                    |" << endl;
	cout << "                                 |                                                       |                                                                    |" << endl;
	cout << "陈家祠(7)-长寿路(8)--西门口(9)-公园前(10)-农讲所(11)--烈士陵园(12)-东山口(13)-杨箕(14)-体育西路(15)--石牌桥(16)--岗顶(17)--华师(18)--五山(19)--天河客运站(20) |" << endl;
	cout << "  |                              |                                                       |                                                                    |" << endl;
	cout << " 黄沙(6)                         |                                                       |                                                                    |" << endl;
	cout << "  |                          海珠公园(26)                                             珠江新城(32)                                                            |" << endl;
	cout << " 芳村(5)                         |                                                       |                                                                    |" << endl;
	cout << "  |                              |                                                     广州塔(33)                                                             |" << endl;
	cout << "花地湾(4)                     昌岗(27)                                                   |                                                                    |" << endl;
	cout << "  |                              |                                                     客村(34)                                                               |" << endl;
	cout << " 坑口(3)                         |                                                       |                                                                    |" << endl;
	cout << "  |                           南洲(28)                                                 沥滘(35)                                                               |" << endl;
	cout << " 西塱(2)                         |                                                       |                                                                    |" << endl;
	cout << "  |                              |                                                    汉溪长隆(36)                                                            |" << endl;
	cout << " 菊树(1)                     广州南站(29)                                                |                                                                    |" << endl;
	cout << "  |                                                                                   番禺广场(37)                                                            |" << endl;
	cout << " 龙溪(0)                                                                                                                                                      |" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
}

// 输入选择框
void ShowOptions() {
	cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "0.龙溪     1.菊树       2.西塱       3.坑口       4.花地湾       5.芳村       6.黄沙   7.陈家祠  8.长寿路     9.西门口      10.公园前   |" << endl;
	cout << "11.农讲所  12.烈士陵园  13.东山口    14.杨箕      15.体育西路    16.石牌桥    17.岗顶  18.华师   19.五山      20.天河客运站             |" << endl;
	cout << "21.机场    22.高增      23.嘉禾望岗  24.白云公园  25.广州火车站  26.海珠公园  27.昌岗  28.南州   29.广州南站  30.广州东站               |" << endl;
	cout << "31.林和西  32.珠江新城  33.广州塔    34.客村      35.沥滘        36.汉溪长隆  37.番禺广场                                               |" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

// 运行主程序
void StartProject() {
	MatrixGraph graph;

	// 获取相关变量
	auto dict = graph.getDict();
	auto paths = graph.getPath();
	auto minPath = graph.getDijMinPathLength();

	
	// 执行查询操作
	cout << "请根据菜单选择起始点：（输入序号）" << endl;
	int startPoints = -1;
	cin >> startPoints;
	while (startPoints < 0 || startPoints > 37) {
		cout << "输入有误！重新输入！" << endl;
		cin >> startPoints;
	}
	cout << "起始地：" << options[startPoints] << endl << endl;


	cout << "请根据菜单选择目的地：（输入序号）" << endl;
	int distation = -1;
	cin >> distation;
	while (distation < 0 || distation > 37) {
		cout << "输入有误！重新输入！" << endl;
		cin >> distation;
	}
	cout << "目的地：" << options[distation] << endl;

	int dictIndex = dict[options[distation]];

	// 执行算法
	graph.Dijkstra(dict[options[startPoints]]);

	// 输出从startPoints到distation的路径及距离
	cout << endl;
	cout << "从" << options[startPoints] << "到" << options[distation] << "的最短路径为: " << endl;
	cout << paths[dictIndex] << endl;
	cout << "距离长度为：" << minPath[dictIndex] << endl;
	cout << endl;

}

// 主控制函数
void GuidanceController() {
	int flag = 1;

	while (true) {
		// 欢迎页面
		WelCome();

		// 展示地图
		GraphDisplay();

		// 展示选项
		ShowOptions();
		
		// 运行程序
		StartProject();

		cout << "是否再次查询？（1.是 2.否）" << endl;
		cin >> flag;

		if (flag == 2) break;

		// 清除控制台
		system("cls");
	}
	cout << endl << "欢迎下次使用！！" << endl;

	system("pause");
}