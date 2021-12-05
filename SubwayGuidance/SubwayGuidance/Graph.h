/*
	Date: 2021-12-5
	Author: Zhaoruquan
	Email: 20202005005@m.scnu.edu.cn
	Description: 广州地铁导航项目
*/

#pragma once


#include <iostream>
#include <fstream>
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

	// 工具方法
	void edgeShow(int Edges[MaxSize][MaxSize]);		// 展示边表

	// 向外提供获取私有变量的接口
	auto& getPath() { return this->path; }
	auto& getDist() { return this->dist; }
	auto& getDict() { return this->dict; }
	auto& getDijMinPathLength() { return this->DijMinPathLength; }
};