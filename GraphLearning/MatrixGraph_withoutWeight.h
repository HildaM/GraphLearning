/*
	Date: 2021-11-23
	TODO: 用邻接矩阵实现无向图
*/

#pragma once

#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 10;		// 最大顶点数


// 邻接矩阵实现图
class MatrixGraph {
private:	// 私有成员
	char vertex[MaxSize];			// 顶点表
	int Edges[MaxSize][MaxSize];	// 边表
	int vertexNums, edgeNums;		// 顶点数、边数
	bool visited[MaxSize];			// 标记数组
	queue<int> que;					// 辅助队列

private:	// 私有方法
	void clearVisited();			// 初始化标记
	void Bfs_NotRecursion(int v);	// 非递归广度遍历
	void Bfs_Recursion(int v);		// 递归广度遍历
	void Dfs_Recursion(int v);		// 递归深度遍历

public:		// 公共方法
	MatrixGraph(char points[], int nodeNums, int edgeNums);	// 构造函数
	void createGraph();				// 构建图
	void Dfs(int v);				// 深度遍历
	void Bfs(int v);				// 广度遍历
};


// 构造函数
MatrixGraph::MatrixGraph(char points[], int nodeNums, int edgeNums) {
	// 初始化数据
	this->vertexNums = nodeNums;
	this->edgeNums = edgeNums;
	clearVisited();

	// 初始化节点
	for (int i = 0; i < vertexNums; i++) {
		vertex[i] = points[i];
	}

	// 初始化边的关系
	for (int i = 0; i < vertexNums; i++)
		for (int j = 0; j < vertexNums; j++)
			Edges[i][j] = 0;
}

// 初始化标记
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}

// 构建图
void MatrixGraph::createGraph() {
	cout << "请输入相关联的顶点信息：一行一对：" << endl;

	int a = 0, b = 0;
	for (int i = 0; i < edgeNums; i++) {
		cin >> a >> b;
		Edges[a][b] = 1;
		Edges[b][a] = 1;
	}
}


// 深度遍历 —— 递归
void MatrixGraph::Dfs_Recursion(int v) {
	// 输出节点信息
	cout << this->vertex[v] << " ";

	// 深度遍历
	for (int i = 0; i < vertexNums; i++) {
		if (Edges[v][i] != 0 && visited[i] == false) {
			visited[i] = true;
			Dfs_Recursion(i);
		}
	}
}


// 广度遍历 —— 非递归
void MatrixGraph::Bfs_NotRecursion(int v) {
	// 广度遍历
	while (!que.empty()) {
		int node = que.front();
		que.pop();

		cout << vertex[node] << " ";

		for (int i = 0; i < vertexNums; i++) {
			if (Edges[v][i] != 0 && visited[i] == false) {
				que.push(i);
				visited[i] = true;
			}
		}
	}
}


// 广度遍历 —— 递归
void MatrixGraph::Bfs_Recursion(int v) {
	cout << vertex[v] << " ";
	que.pop();

	for (int i = 0; i < vertexNums; i++) {
		if (Edges[v][i] != 0 && visited[i] == false) {
			visited[i] = true;
			que.push(i);
		}
	}
	
	// 递归
	if (!que.empty()) Bfs_Recursion(que.front());
}


// 深度遍历方法接口
void MatrixGraph::Dfs(int v) {
	cout << "深度遍历" << endl;

	// 初始化标记数组
	clearVisited();
	// 处理头节点
	visited[v] = true;
	// 调用私有方法
	Dfs_Recursion(v);	// 递归方法
}


// 广度遍历接口
void MatrixGraph::Bfs(int v) {
	// 初始化标记数组
	clearVisited();
	// 处理头节点
	visited[v] = true;
	que.push(v);
	// 调用私有方法
	cout << "广度遍历 —— 非递归" << endl;
	Bfs_NotRecursion(v);	// 非递归方法


	cout << endl << "广度遍历 —— 递归" << endl;
	clearVisited();
	visited[v] = true;
	que.push(v);
	Bfs_Recursion(v);		// 递归方法
}

// 测试代码
void testMatrixGraph_withoutWeight() {
	char arr[8] = { '0','1','2','3','4','5','6','7' };

	MatrixGraph graph(arr, 8, 7);
	graph.createGraph();

	// 广度遍历
	graph.Bfs(0);

	cout << endl;

	// 深度遍历
	graph.Dfs(0);
}


/*
请输入相关联的顶点信息：一行一对：
0 1
1 2
1 3
2 4
2 5
3 6
3 7
*/