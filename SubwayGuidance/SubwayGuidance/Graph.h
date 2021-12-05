/*
	Date: 2021-12-5
	Author: Zhaoruquan
	Email: 20202005005@m.scnu.edu.cn
	Description: ���ݵ���������Ŀ
*/

#pragma once


#include <iostream>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

const int MaxSize = 40;				// ��󶥵���
const int MAX_INT = 0x3f3f3f3f;		// ���������


// �ڽӾ���ʵ��ͼ
class MatrixGraph {
// ˽�б���
private:
	string vertex[MaxSize];			// �����
	int Edges[MaxSize][MaxSize];	// �߱�
	int vertexNums, edgeNums;		// ������������
	bool visited[MaxSize];			// �������
	queue<int> que;					// Bfs��������
	map<string, int> dict;			// �ַ�ӳ���ֵ�

	int dist[MaxSize];				// ��¼Դ�㵽����������·������
	string path[MaxSize];			// �洢�Ѿ������Դ�����·���Ķ���
	int DijMinPathLength[MaxSize];	// �洢��������·������


// ˽�з���
private:
	void InitBasicData();			// ��ʼ����������
	void edgeInit(int Edges[MaxSize][MaxSize]);		// ��ʼ���߱�
	void clearVisited();			// ��ʼ�����
	void createGraph();				// ����ͼ
	void Bfs_NotRecursion(int v);	// �ǵݹ��ȱ���
	void Bfs_Recursion(int v);		// �ݹ��ȱ���
	void Dfs_Recursion(int v);		// �ݹ���ȱ���


// ��������
public:
	// ���캯��
	MatrixGraph();

	// ͼ�㷨�ӿ�
	void Dfs(int v);				// ��ȱ���
	void Bfs(int v);				// ��ȱ���
	void Dijkstra(int v);			// Dijkstra	�㷨

	// ���߷���
	void edgeShow(int Edges[MaxSize][MaxSize]);		// չʾ�߱�

	// �����ṩ��ȡ˽�б����Ľӿ�
	auto& getPath() { return this->path; }
	auto& getDist() { return this->dist; }
	auto& getDict() { return this->dict; }
	auto& getDijMinPathLength() { return this->DijMinPathLength; }
};