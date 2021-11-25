/*
	Date: 2021-11-25 15:36
	TODO: ���ݵ�����Ŀ v1.0
*/

#pragma once


#include <iostream>
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
	void Dijkstra2(int v);			// ���Ը����鱾���㷨������ʧ���ˡ�����

	// ���߷���
	void edgeShow(int Edges[MaxSize][MaxSize]);		// չʾ�߱�

	// �����ṩ��ȡ˽�б����Ľӿ�
	auto& getPath() { return this->path; }
	auto& getDist() { return this->dist; }
	auto& getDict() { return this->dict; }
	auto& getVertexNums() { return this->vertexNums; }
	auto& getDijMinPathLength() { return this->DijMinPathLength; }
};


// ��ʼ�����
void MatrixGraph::clearVisited() {
	for (int i = 0; i < MaxSize; i++)
		visited[i] = false;
}


// ��ʼ����������
void MatrixGraph::InitBasicData() {
	// ��ʼ���߱�
	edgeInit(Edges);

	// ��ʼ��visited����
	this->clearVisited();
}


// ����ͼ
void MatrixGraph::createGraph() {
	string a, b;
	int w = 0;
	int nums = 0;
	int edgeNums = 0;

	// ���ļ�����ȡ��ͼ��Ϣ
	ifstream ifs;
	ifs.open("E:\\Program Practics\\GraphLearning\\GraphLearning\\myGraphData.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	// ��ȡ�ļ���Ϣ������ͼ
	while (ifs >> a >> b >> w) {
		/*
			���´���ʵ�ֶ�̬����ͼ�Ĺ���
			���ҽ���a��b������ʱ������ӵ�vertex��dict�У�
		*/
		if (!dict.count(a)) {	// ������Ϊ0ʱ��������
			vertex[nums] = a;
			dict[a] = nums;
			nums++;
		}
		if (!dict.count(b)) {
			vertex[nums] = b;
			dict[b] = nums;
			nums++;
		}

		// �����ߵĹ�ϵ
		int index_a = dict[a], index_b = dict[b];
		Edges[index_a][index_b] = w;
		Edges[index_b][index_a] = w;

		// һ�����ݱ�ʾһ����
		edgeNums++;
	}

	// ��ʼ���������ͱ���
	this->vertexNums = nums;
	this->edgeNums = edgeNums;

}


// ���캯��
MatrixGraph::MatrixGraph() {
	// ��ʼ����������
	InitBasicData();

	// ����ͼ
	createGraph();
}


// ��ʼ���߱�
void MatrixGraph::edgeInit(int Edges[MaxSize][MaxSize]) {
	for (int i = 0; i < MaxSize; i++) {
		for (int j = 0; j < MaxSize; j++) {
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
	// ��ʼ�����·���洢����
	for (int i = 0; i < vertexNums; i++) {
		dist[i] = MAX_INT;
		DijMinPathLength[i] = 0;
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
				DijMinPathLength[j] = dist[j];
				/*
					����path����
					תcharΪstring
					�ɷ�����
						char ch[2] = { vertex[j], 0 };
						string sch = ch;
						path[j] = path[nowVex] + sch;
					�·���������string�Ĺ��캯������charתstring��string(size_t n, char c)
				*/
				path[j] = path[nowVex] + "/" + vertex[j];

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


// ���Դ���
void test_Project() {
	MatrixGraph graph;

	auto dict = graph.getDict();
	auto vertexNums = graph.getVertexNums();
	auto paths = graph.getPath();
	auto minPath = graph.getDijMinPathLength();

	cout << "��������ʼ�㣺" << endl;
	string startPoints = "";
	cin >> startPoints;

	cout << "������Ŀ�ĵ�" << endl;
	string distation = "";
	cin >> distation;
	int dictIndex = dict[distation];

	// ִ���㷨
	graph.Dijkstra(dict[startPoints]);

	// �����startPoints��distation��·��������
	cout << paths[dictIndex] << " " << minPath[dictIndex] << endl;

	// ���ȫ��·��
	cout << endl;
	for (int i = 0; i < vertexNums; i++) {
		cout << paths[i] << "  " << minPath[i] << endl;
	}
}