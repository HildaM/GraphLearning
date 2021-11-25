// GraphLearning.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include <fstream>

using namespace std;

#include "GraphLearning.h"
//#include "MatrixGraph_withoutWeight.h"
//#include "MatrixGraph_withWeight.h"
//#include "Prim_undirected.h"
//#include "Prim_directed.h"
//#include "Dijkstra.h"
//#include "Dijkstra_Pro.h"
#include "MetroProject_v1.0.h"


// 文件读写测试
void FileTest() {
	ifstream ifs;
	ifs.open("E:\\Program Practics\\GraphLearning\\GraphLearning\\myGraphData_1.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	string a, b;
	int w;
	while (ifs >> a >> b >> w) {
		cout << a << " " << b << " " << w << endl;
	}
}


int main()
{
	// 无向图
	//testMatrixGraph_withoutWeight();

	// 有向图
	//testMatrixGraph_withWeight();

	// Prim
	//testPrim_undirected();
	//testPrim_directed();

	// Dijkstra
	//testDijkstra();
	//test_DijkstraPro();

	test_Project();

	return 0;
}
