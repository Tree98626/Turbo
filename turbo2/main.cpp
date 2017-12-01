#include<iostream>
#include<vector>
#include <stdlib.h>
#include <stdio.h>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
struct Vertex {
	string label;
	int seq;
	int color;
	Vertex() {
		label = "";
		seq = -1;
		color = -1;
	}
	bool operator<(const Vertex& b)const {
		return seq < b.seq;
	}
};
struct AdjacentList {
	string str;
	vector<int> list;
	AdjacentList(string s, int i) {
		str = s;
		list.push_back(i);
	}
};

Vertex quaryVetex[100];//quary tree vertices
Vertex quaryNEC[100];//NEC points 可能没用
int num1,num2;//num1 is the total of quary graph, num2 is the total of data graph
vector<vector<int> > NECs(110);//eg. u1's NECs is u2,u3,同类结点
Vertex dataVetex[100];
int CR[110][110][110];

vector<vector<Vertex*>> getQuaryG() {
	vector<vector<Vertex*> > quaryGraph(110);
	cout << "the sum of vertices: ";
	cin >> num1;
	for (int i = 1;i <= num1;i++) {
		cin >> quaryVetex[i].label;
		quaryVetex[i].seq = i;
	}
	int s, e;
	cout << "edges: "<<endl;
	while (cin >> s >> e && s!=0 && e !=0)
		quaryGraph[s].push_back(&quaryVetex[e]);
	return quaryGraph;
}
vector<vector<Vertex*>> getDataG() {
	vector<vector<Vertex*> > dataGraph(110);
	cout << "the sum of vertices: ";
	cin >> num2;
	for (int i = 1;i <= num2;i++) {
		cin >> dataVetex[i].label;
		dataVetex[i].seq = i;
	}
	int s, e;
	cout << "edges: " << endl;
	while (cin >> s >> e && s != 0 && e != 0)
		dataGraph[s].push_back(&dataVetex[e]);
	return dataGraph;
}
int FindNEC(vector<vector<Vertex*>> &qt){
	int c = 1;
	for (int i = 1;i <= num1;i++) {
		if (quaryVetex[i].color != -1)
			continue;
		int flag = 0;
		for (int j = i+1;j <= num1;j++) {
			if (quaryVetex[j].color != -1)
				continue;
			if (quaryVetex[i].label == quaryVetex[j].label && qt[i].size()==qt[j].size()) {
				sort(qt[i].begin(), qt[i].end());
				sort(qt[j].begin(), qt[j].end());
				int k;
				for (k = 0;k < qt[i].size();k++) {
					if (qt[i][k]->label!=qt[j][k]->label)
						break;
				}
				if (k == qt[i].size()) {
					if (flag == 0) {
						quaryVetex[i].color = c;
						NECs[c].push_back(i);
						flag = 1;
					}
					quaryVetex[j].color = c;
					NECs[c].push_back(j);
				}
			}
		}
		if (quaryVetex[i].color == -1) {
			quaryVetex[i].color = c;
			NECs[c].push_back(i);
		}	
		c++;
	}
	return c-1;
}

vector<vector<Vertex*> > BFSgetNECTree(vector<vector<Vertex*> > &qt, int groups) {
	int visited[100];
	queue<Vertex> que;
	vector<vector<Vertex*> > NECTree(110);
	memset(visited, 0, sizeof(visited));
	visited[1] = 1;
	que.push(quaryVetex[1]);
	NECTree[0].push_back(&quaryVetex[1]);
	while (!que.empty()) {
		Vertex s = que.front();
		for (int i = 0;i < qt[s.seq].size();i++) {
			Vertex *temp = qt[s.seq][i];
			if (!visited[temp->color]) {
				int seq2 = temp->seq;
				NECTree[s.color].push_back(&quaryVetex[seq2]);
				que.push(quaryVetex[seq2]);
				visited[temp->color] = 1;
			}
		}
		que.pop();
	}
	return NECTree;
}
vector<vector<AdjacentList>> adj(vector<vector<Vertex*> > &dataGraph) {
	vector<vector<AdjacentList> > adjlist(110);
	for (int i = 1;i <= num2;i++) {
		int visited[110];
		memset(visited, 0, sizeof(visited));
		for (int j = 0;j < dataGraph[i].size();j++) {
			if (visited[dataGraph[i][j]->seq])
				continue;
			adjlist[i].push_back(AdjacentList(dataGraph[i][j]->label, dataGraph[i][j]->seq));
			int tail = adjlist[i].size() - 1;
			for (int k = j + 1;k < dataGraph[i].size();k++) {
				if (!visited[dataGraph[i][k]->seq]) {
					if (dataGraph[i][j]->label == dataGraph[i][k]->label) {
						adjlist[i][tail].list.push_back(dataGraph[i][k]->seq);
						visited[dataGraph[i][k]->seq] = 1;
					}
				}
			}
		}
	}
	return adjlist;
}
int visited[110];//DFS所用visited
bool NLF(int u, int v, vector<vector<AdjacentList>> &adju, vector<vector<AdjacentList>> &adjv) {
	for (int i = 0;i < adju[u].size();i++) {
		for (int j = 0;j < adjv[v].size();j++) {
			if (adju[u][i].str == adjv[v][j].str && adju[u][i].list.size() > adjv[v][j].list.size())
				return false;
		}
	}
	return true;
}
void clearCR(int u1, int v) {
	int i = 0;
	while (CR[u1][v][i] != 0) {
		CR[u1][v][i] = 0;
		i++;
	}
}
bool ExploreCR(int u1, vector<vector<Vertex*> > &NECtree, vector<vector<Vertex*> > &dataG, vector<vector<AdjacentList>> &adj, 
	vector<vector<AdjacentList>> &adju,Vertex VM[],int size,int v) {
	for (int i = 1;i <= size;i++) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		if (NECtree[NECs[u1][0]].size() > dataG[VM[i].seq].size() || visited[VM[i].seq] || NLF(NECs[u1][0], VM[i].seq,adju,adj)==false)
			continue;
		visited[VM[i].seq] = 1;
		bool matched = true;
		for (int j = 0;j < NECtree[u1].size();j++) {
			Vertex vadj[110];
			int p;
			for (p = 0;p < adj[VM[i].seq].size();p++) {
				if (NECtree[u1][j]->label == adj[VM[i].seq][p].str)
					break;
			}
			int m;

			for (m = 1;m <= adj[VM[i].seq][p].list.size();m++)
				vadj[m] = dataVetex[adj[VM[i].seq][p].list[m-1]];
			if (ExploreCR(NECtree[u1][j]->seq, NECtree, dataG, adj, adju, vadj, m-1, VM[i].seq) == false) {
				for (int k = 0;k < NECtree[u1].size();k++) {
					if (NECtree[u1][k]->seq != NECtree[u1][j]->seq)
						clearCR(NECtree[u1][k]->seq, VM[i].seq); 
				}
				matched = false;
				break;
			}
		}
		visited[VM[i].seq] = 0;
		if (matched == false)
			continue;
		for (int p = 0;p < 110;p++) {
			if (CR[u1][v] == 0) {
				CR[u1][v][p] = VM[i].seq;
				break;
			}		
		}
	}
	int sizeofCR = 0;
	while (CR[u1][v][sizeofCR] != 0) 
		sizeofCR++;
	if (sizeofCR < NECs[u1].size()) {
		clearCR(u1, v);
		return false;
	}
	return true;
}


int main() {
	vector<vector<Vertex*> > quaryGraph = getQuaryG();
	int group = FindNEC(quaryGraph);
	vector<vector<Vertex*> > NECtree = BFSgetNECTree(quaryGraph,group);//NEC树，标明子节点状况
	vector<vector<Vertex*> > dataGraph = getDataG(); 
	vector<vector<AdjacentList> > adjlist = adj(dataGraph);//子树中有标签相同的归为一类
	vector<vector<AdjacentList> > adju = adj(quaryGraph);
	memset(visited, 0, sizeof(visited));
	memset(CR, 0, sizeof(CR));
	if (ExploreCR(1,NECtree,dataGraph,adjlist,adju,dataVetex,num2,0) == true)
		cout << "exist" << endl;
	else
		cout << "no" << endl;
	return 0;
}