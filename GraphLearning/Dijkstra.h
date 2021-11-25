/*
	Date: 2021-11-23 14:30
	TODO: Dijkstra�㷨
*/

#pragma once

#include <iostream>
#include <queue>

using namespace std;

const int MaxSize = 10;				// ��󶥵���
const int MAX_INT = 0x3f3f3f3f;		// ���������


// �ڽӾ���ʵ��ͼ
class MatrixGraph {
// ˽�б���
private:
	char vertex[MaxSize];			// �����
	int Edges[MaxSize][MaxSize];	// �߱�
	int vertexNums, edgeNums;		// ������������
	bool visited[MaxSize];			// �������
	queue<int> que;					// Bfs��������

	int dist[MaxSize];				// ��¼Դ�㵽����������·������
	string path[MaxSize];			// �洢�Ѿ������Դ�����·���Ķ���


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

	// ͼ�㷨
	void Dfs(int v);				// ��ȱ���
	void Bfs(int v);				// ��ȱ���

	void Dijkstra(int v);			// Dijkstra	�㷨
	void Dijkstra2(int v);			// ���Ը����鱾���㷨������ʧ���ˡ�����

	// ���߷���
	void edgeShow(int Edges[MaxSize][MaxSize]);		// չʾ�߱�
	void edgeInit(int Edges[MaxSize][MaxSize]);		// ��ʼ���߱�

	// �����ṩ��ȡ˽�б����Ľӿ�
	auto& getPath() { return this->path; }
	auto& getDist() { return this->dist; }
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
		//Edges[b][a] = w;
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


// Dijkstra	�ǵݹ��㷨
/*
	dist���飺��¼Դ�㵽����������·������
	path���飺�洢�Ѿ������Դ�����·���Ķ���
*/
void MatrixGraph::Dijkstra(int v) {
	// ��dist�����ʼ��Ϊ���ֵ����������Сֵ
	for (int i = 0; i < vertexNums; i++) {
		dist[i] = MAX_INT;
	}

	// ������С�ߵ�ֵ���±꣬���´�ѭ��ʹ��
	int nextVex = v, nextEdge = 0;

	// Dijkstra �㷨
	/*
		��һ��ѭ��Ϊ����ѭ��
	*/
	for (int i = 0; i < vertexNums; i++) {
		/*
			nowVex����ǰ�ڵ���±�
			nowEdge��Դ�㵽��nowVex�ľ���
		*/
		int nowVex = nextVex, nowEdge = nextEdge;

		// �ָ����ֵ���Ա�Ѱ����Сֵ��ע�⣺����ָ�nextVex
		nextEdge = MAX_INT;

		// �������ڵ�
		for (int j = 0; j < vertexNums; j++) {
			/*
				��Դ�㵽j�����·��
				���������һ��·����Դ��-->nowVex-->j���ĳ��ȱ�ֱ�� Դ��-->j ����
				�����dist��path����
			*/
			if (Edges[nowVex][j] != MAX_INT &&
				dist[j] > Edges[nowVex][j] + nowEdge) 
			{
				// ����dist����
				dist[j] = Edges[nowVex][j] + nowEdge;
				/*
					����path����
					תcharΪstring
					�ɷ�����
						char ch[2] = { vertex[j], 0 }; 
						string sch = ch;
						path[j] = path[nowVex] + sch;
					�·���������string�Ĺ��캯������charתstring��string(size_t n, char c)
				*/
				path[j] = path[nowVex] + string(1, vertex[j]);
			}

			// Ѱ����С�ߵ�ֵ���±�
			if (dist[j] < nextEdge && dist[j] != 0) {
				nextEdge = dist[j];
				nextVex = j;
			}
		}

		// ��dist�е���С�ߵ�ֵ��0��˵���Ѿ���ͼ
		dist[nextVex] = 0;
	}
}

// �޷���ԭ�ķ��˼·��������
void MatrixGraph::Dijkstra2(int v) {
	// ��Ǻ���
	int flag[MaxSize];

	for (int i = 0; i < vertexNums; i++) {
		flag[i] = 0;
		dist[i] = Edges[v][i];
	}

	// �������
	dist[v] = 0;
	flag[v] = 1;

	int minVex = 0;
	for (int i = 0; i < vertexNums; i++) {
		int minDist = MAX_INT;
		// �ҵ�������Ȩֵ��С�Ķ��㣬��Ϊ������ȷ�������·���Ķ���
		for (int j = 0; j < vertexNums; j++) {
			if (flag[j] == 0 && dist[j] < minDist) {
				minVex = j;
				minDist = dist[j];
			}
		}

		// ���ҵ��Ķ�����
		flag[minVex] = 1;
		path[i] += vertex[minVex];

		// Ѱ�� Դ�� --> minVex --> k �����·��
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

	// ��ȡ˽�б���
	auto path = graph.getPath();
	auto dist = graph.getDist();

	// ���
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