/*
	Date: 2021-12-5
	Author: Zhaoruquan
	Email: 20202005005@m.scnu.edu.cn
	Description: ���ݵ���������Ŀ
*/

#include "Graph.h"

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
	ifs.open("myGraphData.txt", ios::in);

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
				path[j] = path[nowVex] + "->" + vertex[j];

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