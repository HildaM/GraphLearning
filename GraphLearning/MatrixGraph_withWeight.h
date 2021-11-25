/*
	Date: 2021-11-23:10:04
	TODO: ���ڽӾ���ʵ������ͼ
	Notes:
		����ͼ������ͼ��ʵ�֣�ֻ���ڳ�ʼ�����в�ͬ��
		ֻҪ�������ڽӾ���ʵ�֣������㷨�ϲ�����̫�����
*/

#pragma once

#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 10;				// ��󶥵���
const int MAX_INT = 0x3f3f3f3f;		// ���������


// �ڽӾ���ʵ��ͼ
class MatrixGraph {
private:
	char vertex[MaxSize];			// �����
	int Edges[MaxSize][MaxSize];	// �߱�
	int vertexNums, edgeNums;		// ������������
	bool visited[MaxSize];			// �������
	queue<int> que;					// ��������

	void clearVisited();			// ��ʼ�����
	void Bfs_NotRecursion(int v);	// �ǵݹ��ȱ���
	void Bfs_Recursion(int v);		// �ݹ��ȱ���
	void Dfs_Recursion(int v);		// �ݹ���ȱ���

public:
	MatrixGraph(char points[], int nodeNums, int edgeNums);	// ���캯��
	void createGraph();				// ����ͼ
	void Dfs(int v);				// ��ȱ���
	void Bfs(int v);				// ��ȱ���
};


// ���캯��
MatrixGraph::MatrixGraph(char points[], int nodeNums, int edgeNums) {
	// ��ʼ������
	this->vertexNums = nodeNums;
	this->edgeNums = edgeNums;
	clearVisited();

	// ��ʼ���ڵ�
	for (int i = 0; i < vertexNums; i++) {
		vertex[i] = points[i];
	}

	// ��ʼ���ߵĹ�ϵ ���� ������ͼ��ͬ
	for (int i = 0; i < vertexNums; i++) {
		for (int j = 0; j < vertexNums; j++) {
			Edges[i][j] = MAX_INT;
		}		
		Edges[i][i] = 0;
	}
		
}

// ��ʼ�����
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}

// ����ͼ
void MatrixGraph::createGraph() {
	cout << "������������Ķ�����Ϣ��һ��һ�ԣ�" << endl;

	// �˴�������ͼ�Ĵ���ͬ
	int a = 0, b = 0, w = 0;
	for (int i = 0; i < edgeNums; i++) {
		cin >> a >> b >> w;
		Edges[a][b] = w;
	}
}


// ��ȱ��� ���� �ݹ�
void MatrixGraph::Dfs_Recursion(int v) {
	// ����ڵ���Ϣ
	cout << this->vertex[v] << " ";

	// ��ȱ���
	for (int i = 0; i < vertexNums; i++) {
		if (Edges[v][i] != MAX_INT && visited[i] == false) {
			visited[i] = true;
			Dfs_Recursion(i);
		}
	}
}


// ��ȱ��� ���� �ǵݹ�
void MatrixGraph::Bfs_NotRecursion(int v) {
	// ��ȱ���
	while (!que.empty()) {
		int node = que.front();
		que.pop();

		cout << vertex[node] << " ";

		for (int i = 0; i < vertexNums; i++) {
			if (Edges[v][i] != MAX_INT && visited[i] == false) {
				que.push(i);
				visited[i] = true;
			}
		}
	}
}


// ��ȱ��� ���� �ݹ�
void MatrixGraph::Bfs_Recursion(int v) {
	cout << vertex[v] << " ";
	que.pop();

	for (int i = 0; i < vertexNums; i++) {
		if (Edges[v][i] != MAX_INT && visited[i] == false) {
			visited[i] = true;
			que.push(i);
		}
	}

	// �ݹ�
	if (!que.empty()) Bfs_Recursion(que.front());
}


// ��ȱ��������ӿ�
void MatrixGraph::Dfs(int v) {
	cout << "��ȱ���" << endl;

	// ��ʼ���������
	clearVisited();
	// ����ͷ�ڵ�
	visited[v] = true;
	// ����˽�з���
	Dfs_Recursion(v);	// �ݹ鷽��
}


// ��ȱ����ӿ�
void MatrixGraph::Bfs(int v) {
	// ��ʼ���������
	clearVisited();
	// ����ͷ�ڵ�
	visited[v] = true;
	que.push(v);
	// ����˽�з���
	cout << "��ȱ��� ���� �ǵݹ�" << endl;
	Bfs_NotRecursion(v);	// �ǵݹ鷽��


	cout << endl << "��ȱ��� ���� �ݹ�" << endl;
	clearVisited();
	visited[v] = true;
	que.push(v);
	Bfs_Recursion(v);		// �ݹ鷽��
}

// ���Դ���
void testMatrixGraph_withWeight() {
	char arr[5] = { 'A','B','C','D','E' };

	MatrixGraph graph(arr, 5, 10);
	graph.createGraph();

	// ��ȱ���
	graph.Bfs(0);

	cout << endl;

	// ��ȱ���
	graph.Dfs(0);
}


/*
������������Ķ�����Ϣ��һ��һ�ԣ�
0 1 13
0 3 4
1 0 13
1 2 15
1 4 5
2 3 12
3 0 4
3 2 12
4 2 6
4 3 3
*/