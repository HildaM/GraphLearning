/*
	Date: 2021-11-23 14:30
	TODO: Dijkstra算法
*/

#pragma once

#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 10;				// 最大顶点数
const int MAX_INT = 0x3f3f3f3f;		// 定义无穷大


// 邻接矩阵实现图
class MatrixGraph {
// 私有变量
private:
	char vertex[MaxSize];			// 顶点表
	int Edges[MaxSize][MaxSize];	// 边表
	int vertexNums, edgeNums;		// 顶点数、边数
	bool visited[MaxSize];			// 标记数组
	queue<int> que;					// Bfs辅助队列

	int dist[MaxSize];				// 记录源点到各顶点的最短路径长度
	string path[MaxSize];			// 存储已经求出到源点最短路径的顶点


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

	// 图算法
	void Dfs(int v);				// 深度遍历
	void Bfs(int v);				// 广度遍历

	void Dijkstra(int v);			// Dijkstra	算法
	void Dijkstra2(int v);			// 尝试复现书本的算法，但是失败了。。。

	// 工具方法
	void edgeShow(int Edges[MaxSize][MaxSize]);		// 展示边表
	void edgeInit(int Edges[MaxSize][MaxSize]);		// 初始化边表

	// 向外提供获取私有变量的接口
	auto& getPath() { return this->path; }
	auto& getDist() { return this->dist; }
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
		//Edges[b][a] = w;
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


// Dijkstra	非递归算法
/*
	dist数组：记录源点到各顶点的最短路径长度
	path数组：存储已经求出到源点最短路径的顶点
*/
void MatrixGraph::Dijkstra(int v) {
	// 将dist数组初始化为最大值，方便找最小值
	for (int i = 0; i < vertexNums; i++) {
		dist[i] = MAX_INT;
	}

	// 传递最小边的值与下标，供下次循环使用
	int nextVex = v, nextEdge = 0;

	// Dijkstra 算法
	/*
		第一层循环为计数循环
	*/
	for (int i = 0; i < vertexNums; i++) {
		/*
			nowVex：当前节点的下标
			nowEdge：源点到达nowVex的距离
		*/
		int nowVex = nextVex, nowEdge = nextEdge;

		// 恢复最大值，以便寻找最小值。注意：无需恢复nextVex
		nextEdge = MAX_INT;

		// 遍历各节点
		for (int j = 0; j < vertexNums; j++) {
			/*
				求源点到j的最短路径
				假如存在着一条路径：源点-->nowVex-->j，的长度比直接 源点-->j 更短
				则更新dist和path数组
			*/
			if (Edges[nowVex][j] != MAX_INT &&
				dist[j] > Edges[nowVex][j] + nowEdge) 
			{
				// 更新dist数组
				dist[j] = Edges[nowVex][j] + nowEdge;
				/*
					更新path数组
					转char为string
					旧方法：
						char ch[2] = { vertex[j], 0 }; 
						string sch = ch;
						path[j] = path[nowVex] + sch;
					新方法：利用string的构造函数，将char转string。string(size_t n, char c)
				*/
				path[j] = path[nowVex] + string(1, vertex[j]);
			}

			// 寻找最小边的值与下标
			if (dist[j] < nextEdge && dist[j] != 0) {
				nextEdge = dist[j];
				nextVex = j;
			}
		}

		// 将dist中的最小边的值归0，说明已经入图
		dist[nextVex] = 0;
	}
}

// 无法还原文峰的思路？？？？
void MatrixGraph::Dijkstra2(int v) {
	// 标记函数
	int flag[MaxSize];

	for (int i = 0; i < vertexNums; i++) {
		flag[i] = 0;
		dist[i] = Edges[v][i];
	}

	// 处理起点
	dist[v] = 0;
	flag[v] = 1;

	int minVex = 0;
	for (int i = 0; i < vertexNums; i++) {
		int minDist = MAX_INT;
		// 找到各顶点权值最小的顶点，即为本次能确定的最短路径的顶点
		for (int j = 0; j < vertexNums; j++) {
			if (flag[j] == 0 && dist[j] < minDist) {
				minVex = j;
				minDist = dist[j];
			}
		}

		// 将找到的顶点标记
		flag[minVex] = 1;
		path[i] += vertex[minVex];

		// 寻找 源点 --> minVex --> k 的最短路径
		for (int k = 0; k < vertexNums; k++) {
			if (flag[k] == 0 && (minDist + Edges[minVex][k] < dist[k])) {
				dist[k] = minDist + Edges[minVex][k];
				path[i] += path[minVex] + string(1, vertex[k]);
			}
		}
	}
}



void testDijkstra() {
	char arr[5] = { '0','1','2','3','4' };

	MatrixGraph graph(arr, 5, 7);
	
	graph.Dijkstra(1);

	// 获取私有变量
	auto path = graph.getPath();
	auto dist = graph.getDist();

	// 输出
	for (int i = 0; i < 5; i++) {
		cout << path[i] << endl;
	}

	for (int i = 0; i < 5; i++) {
		if (dist[i] != MAX_INT)
			cout << dist[i] << " ";
		else
			cout << "INF" << " ";
	}
	cout << endl;
}