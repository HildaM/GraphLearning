/*
	Date: 2021-11-23:10:33
	TODO: Prim�㷨
	Notes: ������ͼʵ��
*/

#pragma once

#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 10;				// ��󶥵���
const int MAX_INT = 0x3f3f3f3f;		// ���������


// �ڽӾ���ʵ��ͼ
class MatrixGraph {
// ˽�г�Ա
private:	
	char vertex[MaxSize];			// �����
	int Edges[MaxSize][MaxSize];	// �߱�
	int vertexNums, edgeNums;		// ������������
	bool visited[MaxSize];			// �������
	queue<int> que;					// ��������

	int adjvex[MaxSize];			// adjvex����ѡ��̱ߵ��ڽӵ�
	int lowcost[MaxSize];			// lowcost������õ����СȨֵ
	int newEdges[MaxSize][MaxSize];	// ��С������ͼ


// ˽�з���
private:	
	void clearVisited();			// ��ʼ�����
	void Bfs_NotRecursion(int v);	// �ǵݹ��ȱ���
	void Bfs_Recursion(int v);		// �ݹ��ȱ���
	void Dfs_Recursion(int v);		// �ݹ���ȱ���


// ��������
public:		
	MatrixGraph(char points[], int nodeNums, int edgeNums);	// ���캯��
	void createGraph();				// ����ͼ
	void Dfs(int v);				// ��ȱ���
	void Bfs(int v);				// ��ȱ���

	void Prim(int v);				// Prim��С�������㷨

	// ���߷���
	void edgeShow(int Edges[MaxSize][MaxSize]);		// չʾ�߱�
	void edgeInit(int Edges[MaxSize][MaxSize]);		// ��ʼ���߱�

	// �����ṩ�ӿڷ���˽�г�Ա
	auto& getEdges() { return this->Edges; }
	auto& getNewEdges() { return this->newEdges; }

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
	edgeInit(Edges);
	edgeInit(newEdges);

	// ����ͼ
	createGraph();
}


// ��ʼ���߱�
void MatrixGraph::edgeInit(int Edges[MaxSize][MaxSize]) {
	for (int i = 0; i < vertexNums; i++) {
		for (int j = 0; j < vertexNums; j++) {
			Edges[i][j] = MAX_INT;
		}
		Edges[i][i] = 0;
	}
}


// չʾ�߱�
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


// ��ʼ�����
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}

// ����ͼ
void MatrixGraph::createGraph() {
	cout << "������������Ķ�����Ϣ��һ��һ�ԣ�" << endl;

	int a = 0, b = 0, w = 0;
	for (int i = 0; i < edgeNums; i++) {
		cin >> a >> b >> w;
		Edges[a][b] = w;
		Edges[b][a] = w;
	}
}



// ��ȱ��� ���� �ݹ�
void MatrixGraph::Dfs_Recursion(int v) {
	// ����ڵ���Ϣ
	cout << this->vertex[v] << " ";

	// ��ȱ���
	for (int i = 0; i < vertexNums; i++) {
		if (Edges[v][i] != MAX_INT && Edges[v][i] != 0 && visited[i] == false) {
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
			if (Edges[v][i] != MAX_INT && Edges[v][i] != 0 && visited[i] == false) {
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
		if (Edges[v][i] != MAX_INT && Edges[v][i] != 0 && visited[i] == false) {
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


/*
	Prim��С�������㷨
	�ǵݹ顣��ʼ���Ϊv
*/
void MatrixGraph::Prim(int v) {
	// ��ʼ����ѡ�ڽӱ����СȨֵ��
	for (int i = 0; i < vertexNums; i++) {
		adjvex[i] = v;
		lowcost[i] = Edges[v][i];
	}

	// Prim�㷨
	/*
		��һ��ѭ��������ѭ����������v�ڵ�������нڵ�
	*/
	for (int i = 1; i < vertexNums; i++) {
		int fromVex = -1, nextVex = -1, minEdge = MAX_INT;

		// Ѱ����СȨֵ�ͱ�
		for (int j = 0; j < vertexNums; j++) {
			// ��Ȩֵ��С�ı�
			if (lowcost[j] > Edges[v][j]) {
				adjvex[j] = v;				// ����j��v�ڵ�
				lowcost[j] = Edges[v][j];	// ���µ���j�ڵ㣬��СȨֵ�ı�
			}
			// ������С��Ȩֵ�Ͷ�Ӧ�Ľڵ�
			// lowcost[j] != 0���ų��Լ����Լ��Ŀ���
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



// ���Դ���
void testPrim_undirected() {
	char arr[5] = { 'A','B','C','D','E' };
	
	// �����ͳ�ʼ������ͼ
	MatrixGraph graph(arr, 5, 7);

	// ��ȱ���
	graph.Bfs(0);
	cout << endl;

	// ��ȱ���
	graph.Dfs(0);
	cout << endl;

	// չʾͼ�ı�
	graph.edgeShow(graph.getEdges());
	cout << endl;

	// Prim
	graph.Prim(0);
	
	// չʾ��С������ͼ�ı�
	graph.edgeShow(graph.getNewEdges());
	cout << endl;


	// �Ӳ�ͬ��㿪ʼ��̽����С��������Ψһ��
	for (int i = 0; i < 5; i++) {
		cout << "Start from " << i << endl;
		graph.edgeInit(graph.getNewEdges());
		graph.Prim(i);
		graph.edgeShow(graph.getNewEdges());
		cout << "======== End =========" << endl << endl;
	}

}


