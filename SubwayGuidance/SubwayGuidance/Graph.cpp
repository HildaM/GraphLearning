/*
	Date: 2021-12-5
	Author: Zhaoruquan
	Email: 20202005005@m.scnu.edu.cn
	Description: 广州地铁导航项目
*/

#include "Graph.h"

// 初始化标记
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}


// 初始化基本数据
void MatrixGraph::InitBasicData() {
	// 初始化边表
	edgeInit(Edges);

	// 初始化visited数组
	this->clearVisited();
}


// 构建图
void MatrixGraph::createGraph() {
	string a, b;
	int w = 0;
	int nums = 0;
	int edgeNums = 0;

	// 打开文件，读取地图信息
	ifstream ifs;
	ifs.open("myGraphData.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	// 读取文件信息并构建图
	while (ifs >> a >> b >> w) {
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
		Edges[index_b][index_a] = w;

		// 一行数据表示一条边
		edgeNums++;
	}

	// 初始化顶点数和边数
	this->vertexNums = nums;
	this->edgeNums = edgeNums;

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