/*
	Date: 2021-11-23 17:50 + 2021-11-24
	TODO: 优化整个数据结构
		1. 可以输入中文节点名称。并可以将中文节点映射到对应的数字下标上
		2. 实现自动添加陌生节点。
		3. 支持导出最短路径长度
*/

#pragma once


#include <iostream>
#include <queue>
#include <map>

using namespace std;

const int MaxSize = 40;				// 最大顶点数
const int MAX_INT = 0x3f3f3f3f;		// 定义无穷大


// 邻接矩阵实现图
class MatrixGraph {
// 私有变量
private:
	string vertex[MaxSize];			// 顶点表
	int Edges[MaxSize][MaxSize];	// 边表
	int vertexNums, edgeNums;		// 顶点数、边数
	bool visited[MaxSize];			// 标记数组
	queue<int> que;					// Bfs辅助队列
	map<string, int> dict;			// 字符映射字典

	int dist[MaxSize];				// 记录源点到各顶点的最短路径长度
	string path[MaxSize];			// 存储已经求出到源点最短路径的顶点
	int DijMinPathLength[MaxSize];	// 存储求出的最短路径长度


// 私有方法
private:
	void InitBasicData();			// 初始化基本数据
	void edgeInit(int Edges[MaxSize][MaxSize]);		// 初始化边表
	void NumsInit();				// 顶点数、边数初始化
	void clearVisited();			// 初始化标记
	void createGraph();				// 构建图
	void Bfs_NotRecursion(int v);	// 非递归广度遍历
	void Bfs_Recursion(int v);		// 递归广度遍历
	void Dfs_Recursion(int v);		// 递归深度遍历


// 公共方法
public:
	// 构造函数
	MatrixGraph();
	
	// 图算法接口
	void Dfs(int v);				// 深度遍历
	void Bfs(int v);				// 广度遍历
	void Dijkstra(int v);			// Dijkstra	算法
	void Dijkstra2(int v);			// 尝试复现书本的算法，但是失败了。。。

	// 工具方法
	void edgeShow(int Edges[MaxSize][MaxSize]);		// 展示边表

	// 向外提供获取私有变量的接口
	auto& getPath() { return this->path; }
	auto& getDist() { return this->dist; }
	auto& getDict() { return this->dict; }
	auto& getVertexNums() { return this->vertexNums; }
	auto& getDijMinPathLength() { return this->DijMinPathLength; }
};



// 顶点数、边数初始化
void MatrixGraph::NumsInit() {
	cout << "请输入边个数：" << endl;
	int vertexNums = 0, edgeNums = 0;
	cin >> edgeNums;

	// 初始化数据
	this->vertexNums = vertexNums;
	this->edgeNums = edgeNums;
}


// 初始化标记
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}


// 初始化基本数据
void MatrixGraph::InitBasicData() {
	// 初始化顶点数、边数
	NumsInit();

	// 初始化边表
	edgeInit(Edges);
	
	// 初始化visited数组
	this->clearVisited();
}


// 构建图
void MatrixGraph::createGraph() {
	cout << "请输入相关联的顶点信息：一行一对：" << endl;

	string a, b;
	int w = 0;
	int nums = 0;
	for (int i = 0; i < edgeNums; i++) {
		cin >> a >> b >> w;
		
		/*
			以下代码实现动态生成图的功能
			当且仅当a或b不存在时，才添加到vertex和dict中！
		*/
		if (!dict.count(a)) {	// 当数量为0时，不存在
			vertex[nums] = a;
			dict[a] = nums;
			nums++;
		}
		if (!dict.count(b)) {
			vertex[nums] = b;
			dict[b] = nums;
			nums++;
		}

		// 构建边的关系
		int index_a = dict[a], index_b = dict[b];
		Edges[index_a][index_b] = w;
	}

	// 由于在这里nums的作用是充当vertexNums，而vertexNums只有在所有边都输入完成后，才可确定。
	this->vertexNums = nums;
}


// 构造函数
MatrixGraph::MatrixGraph() {
	// 初始化基本数据
	InitBasicData();

	// 创建图
	createGraph();
}


// 初始化边表
void MatrixGraph::edgeInit(int Edges[MaxSize][MaxSize]) {
	for (int i = 0; i < MaxSize; i++) {
		for (int j = 0; j < MaxSize; j++) {
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
	// 初始化最短路径存储数组
	for (int i = 0; i < vertexNums; i++) {
		dist[i] = MAX_INT;
		DijMinPathLength[i] = 0;
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
				DijMinPathLength[j] = dist[j];
				/*
					更新path数组
					转char为string
					旧方法：
						char ch[2] = { vertex[j], 0 };
						string sch = ch;
						path[j] = path[nowVex] + sch;
					新方法：利用string的构造函数，将char转string。string(size_t n, char c)
				*/
				path[j] = path[nowVex] + "->" + vertex[j];

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


// 测试代码
void test_DijkstraPro() {
	MatrixGraph graph;

	auto dict = graph.getDict();
	auto vertexNums = graph.getVertexNums();
	auto path = graph.getPath();
	auto minPath = graph.getDijMinPathLength();

	graph.Dijkstra(dict["西塱"]);

	for (int i = 0; i < vertexNums; i++) {
		cout << path[i] << "  ";
		cout << minPath[i] << endl;
	}

}