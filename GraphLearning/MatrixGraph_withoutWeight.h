/*
	Date: 2021-11-23
	TODO: ���ڽӾ���ʵ������ͼ
*/

#pragma once

#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 10;		// ��󶥵���


// �ڽӾ���ʵ��ͼ
class MatrixGraph {
private:	// ˽�г�Ա
	char vertex[MaxSize];			// �����
	int Edges[MaxSize][MaxSize];	// �߱�
	int vertexNums, edgeNums;		// ������������
	bool visited[MaxSize];			// �������
	queue<int> que;					// ��������

private:	// ˽�з���
	void clearVisited();			// ��ʼ�����
	void Bfs_NotRecursion(int v);	// �ǵݹ��ȱ���
	void Bfs_Recursion(int v);		// �ݹ��ȱ���
	void Dfs_Recursion(int v);		// �ݹ���ȱ���

public:		// ��������
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

	// ��ʼ���ߵĹ�ϵ
	for (int i = 0; i < vertexNums; i++)
		for (int j = 0; j < vertexNums; j++)
			Edges[i][j] = 0;
}

// ��ʼ�����
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}

// ����ͼ
void MatrixGraph::createGraph() {
	cout << "������������Ķ�����Ϣ��һ��һ�ԣ�" << endl;

	int a = 0, b = 0;
	for (int i = 0; i < edgeNums; i++) {
		cin >> a >> b;
		Edges[a][b] = 1;
		Edges[b][a] = 1;
	}
}


// ��ȱ��� ���� �ݹ�
void MatrixGraph::Dfs_Recursion(int v) {
	// ����ڵ���Ϣ
	cout << this->vertex[v] << " ";

	// ��ȱ���
	for (int i = 0; i < vertexNums; i++) {
		if (Edges[v][i] != 0 && visited[i] == false) {
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
			if (Edges[v][i] != 0 && visited[i] == false) {
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
		if (Edges[v][i] != 0 && visited[i] == false) {
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
void testMatrixGraph_withoutWeight() {
	char arr[8] = { '0','1','2','3','4','5','6','7' };

	MatrixGraph graph(arr, 8, 7);
	graph.createGraph();

	// ��ȱ���
	graph.Bfs(0);

	cout << endl;

	// ��ȱ���
	graph.Dfs(0);
}


/*
������������Ķ�����Ϣ��һ��һ�ԣ�
0 1
1 2
1 3
2 4
2 5
3 6
3 7
*/