/*
	Date: 2021-11-23:10:33
	TODO: Prim算法
	Notes: 用无向图实现
*/

#pragma once

#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 10;				// 最大顶点数
const int MAX_INT = 0x3f3f3f3f;		// 定义无穷大


// 邻接矩阵实现图
class MatrixGraph {
// 私有成员
private:	
	char vertex[MaxSize];			// 顶点表
	int Edges[MaxSize][MaxSize];	// 边表
	int vertexNums, edgeNums;		// 顶点数、边数
	bool visited[MaxSize];			// 标记数组
	queue<int> que;					// 辅助队列

	int adjvex[MaxSize];			// adjvex：候选最短边的邻接点
	int lowcost[MaxSize];			// lowcost：到达该点的最小权值
	int newEdges[MaxSize][MaxSize];	// 最小生成树图


// 私有方法
private:	
	void clearVisited();			// 初始化标记
	void Bfs_NotRecursion(int v);	// 非递归广度遍历
	void Bfs_Recursion(int v);		// 递归广度遍历
	void Dfs_Recursion(int v);		// 递归深度遍历


// 公共方法
public:		
	MatrixGraph(char points[], int nodeNums, int edgeNums);	// 构造函数
	void createGraph();				// 构建图
	void Dfs(int v);				// 深度遍历
	void Bfs(int v);				// 广度遍历

	void Prim(int v);				// Prim最小生成树算法

	// 工具方法
	void edgeShow(int Edges[MaxSize][MaxSize]);		// 展示边表
	void edgeInit(int Edges[MaxSize][MaxSize]);		// 初始化边表

	// 向外提供接口访问私有成员
	auto& getEdges() { return this->Edges; }
	auto& getNewEdges() { return this->newEdges; }

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
	edgeInit(Edges);
	edgeInit(newEdges);

	// 创建图
	createGraph();
}


// 初始化边表
void MatrixGraph::edgeInit(int Edges[MaxSize][MaxSize]) {
	for (int i = 0; i < vertexNums; i++) {
		for (int j = 0; j < vertexNums; j++) {
			Edges[i][j] = MAX_INT;
		}
		Edges[i][i] = 0;
	}
}


// 展示边表
void MatrixGraph::edgeShow(int Edges[MaxSize][MaxSize]) {
	for (int i = 0; i < vertexNums; i++) {
		for (int j = 0; j < vertexNums; j++) {
			if (Edges[i][j] != MAX_INT)
				cout << Edges[i][j] << " ";
			else
				cout << "INF" << " ";
		}
		cout << endl;
	}
}


// 初始化标记
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}

// 构建图
void MatrixGraph::createGraph() {
	cout << "请输入相关联的顶点信息：一行一对：" << endl;

	int a = 0, b = 0, w = 0;
	for (int i = 0; i < edgeNums; i++) {
		cin >> a >> b >> w;
		Edges[a][b] = w;
		Edges[b][a] = w;
	}
}



// 深度遍历 —— 递归
void MatrixGraph::Dfs_Recursion(int v) {
	// 输出节点信息
	cout << this->vertex[v] << " ";

	// 深度遍历
	for (int i = 0; i < vertexNums; i++) {
		if (Edges[v][i] != MAX_INT && Edges[v][i] != 0 && visited[i] == false) {
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
			if (Edges[v][i] != MAX_INT && Edges[v][i] != 0 && visited[i] == false) {
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
		if (Edges[v][i] != MAX_INT && Edges[v][i] != 0 && visited[i] == false) {
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


/*
	Prim最小生成树算法
	非递归。起始编号为v
*/
void MatrixGraph::Prim(int v) {
	// 初始化候选邻接表和最小权值表
	for (int i = 0; i < vertexNums; i++) {
		adjvex[i] = v;
		lowcost[i] = Edges[v][i];
	}

	// Prim算法
	/*
		第一层循环：计数循环，遍历除v节点外的所有节点
	*/
	for (int i = 1; i < vertexNums; i++) {
		int fromVex = -1, nextVex = -1, minEdge = MAX_INT;

		// 寻找最小权值和边
		for (int j = 0; j < vertexNums; j++) {
			// 找权值最小的边
			if (lowcost[j] > Edges[v][j]) {
				adjvex[j] = v;				// 关联j和v节点
				lowcost[j] = Edges[v][j];	// 更新到达j节点，最小权值的边
			}
			// 更新最小的权值和对应的节点
			// lowcost[j] != 0：排除自己到自己的可能
			if (lowcost[j] != 0 && lowcost[j] < minEdge) {
				minEdge = lowcost[j];
				fromVex = adjvex[j];
				nextVex = j;
			}
		}

		newEdges[fromVex][nextVex] = minEdge;
		newEdges[nextVex][fromVex] = minEdge;
		v = nextVex;
	}
}



// 测试代码
void testPrim_undirected() {
	char arr[5] = { 'A','B','C','D','E' };
	
	// 创建和初始化无向图
	MatrixGraph graph(arr, 5, 7);

	// 广度遍历
	graph.Bfs(0);
	cout << endl;

	// 深度遍历
	graph.Dfs(0);
	cout << endl;

	// 展示图的边
	graph.edgeShow(graph.getEdges());
	cout << endl;

	// Prim
	graph.Prim(0);
	
	// 展示最小生成树图的边
	graph.edgeShow(graph.getNewEdges());
	cout << endl;


	// 从不同起点开始，探究最小生成树的唯一性
	for (int i = 0; i < 5; i++) {
		cout << "Start from " << i << endl;
		graph.edgeInit(graph.getNewEdges());
		graph.Prim(i);
		graph.edgeShow(graph.getNewEdges());
		cout << "======== End =========" << endl << endl;
	}

}


