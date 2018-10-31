#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
const int INFINTY = 99999;
struct Vertex {
  vector<int> adj;  //邻接表
  vector<int> weight;  //自身到其邻接点的距离，即c(v,w)
  bool known;
  int dist;  //s到该点的距离
  string name;
  int path;  //父路径
};

void printPath(int vIndex, vector<Vertex> &v) {
  if (vIndex >= 0 && v[vIndex].path > -1) {
    printPath(v[vIndex].path, v);
    cout << " to " << endl;
  }
  cout << v[vIndex].name << endl;
}

void dijkstraString(int sIndex, int tIndex, vector<Vertex> &Vertices) {
  int smallestDist;
  int smallestVertex;
  Vertex v, s, t;
  int n = Vertices.size();
  Vertices[sIndex].dist = 0;
  for (;;) {
    smallestDist = INFINTY;
    smallestVertex = -1;
    //找到未标记的最小距离的结点
    for (int i = 0; i < n; i++) {
      if (!Vertices[i].known && Vertices[i].dist < smallestDist) {
        smallestDist = Vertices[i].dist;
        smallestDist = i;
      }
    }
    if (smallestVertex < 0 || smallestVertex == tIndex) break;
    Vertices[smallestVertex].known = true;
    v = Vertices[smallestVertex];
    for (int j = 0; j < v.adj.size(); j++) {
      if (!Vertices[v.adj[j]].known) {
        if (v.dist + v.weight[j] < Vertices[v.adj[j]].dist) {
          Vertices[v.adj[j]].dist = v.dist + v.weight[j];
          Vertices[v.adj[j]].path = smallestVertex;
        }
      }
    }

  }
}

vector<Vertex> readWords(istream &in) {
  string oneLine;
  vector<Vertex> v;
  Vertex w;
  while (in >> oneLine) {
    w.name = oneLine;
    w.known = false;
    w.path = -1;
    w.dist = INFINTY;
    v.push_back(w);
  }
  return v;
}

//word1和word2的距离
int oneCharOff(const string & word1, const string &word2, int p) {
  string big, small, shrink;
  int cost;
  //comparing...
  int diff = word1.size() - word2.size();
  if (diff < -1 || diff>1) return 0;
  else if (word1.size() == word2.size()) {
    int diffs = 0;
    for (int i = 0; i < word1.size(); i++)
      if (word1[i] != word2[i])
        if (++diffs > 1)
          return 0;
    if (diffs == 1) return 1;
  }
  if (word2.size() > word1.size()) {
    big = word2;
    small = word1;
  }
  else
  {
    big = word1;
    small = word2;
  }
  //如果big是small在某个位置上插入了一个字符,则返回p.否则返回0.
  for (int i = 0; i < big.size() - 1; i++) {
    shrink = big.substr(0, i) + big.substr(i + 1, big.size() - i - 1);
    if (shrink == small) return p;
  }
  if (big.substr(0, big.size() - 1) == small) return p;
  else return 0;
}

void fillAdjacencies(vector<Vertex> & words, int p) {
  int cost;
  for (int i = 0; i < words.size(); i++) {
    for (int j = i + 1; j < words.size(); j++) {
      cost = oneCharOff(words[i].name, words[j].name, p);
      if (cost > 0) {
        words[i].adj.push_back(j);
        words[i].weight.push_back(cost);
        words[j].adj.push_back(i);
        words[j].weight.push_back(cost);
      }
    }
  }
}

void WORD_TEST() {
  //dict.txt存放词典
  string file = "dict.txt";
  int p;
  ifstream fin(file);
  string w1, w2;
  int w1Index, w2Index;
  cout << "what is the cost of single char deletions: ";
  cin >> p;
  vector<Vertex> words = readWords(fin);
  do {
    cout << "Enter two words in the dictionary: ";
    cin >> w1 >> w2;
    // Find their indices (here is where a map would be superior
    // However all other access are now in O(1) time
    for (w1Index = 0; w1Index < words.size()
      && words[w1Index].name != w1; w1Index++);
    for (w2Index = 0; w2Index < words.size()
      && words[w2Index].name != w2; w2Index++);
  } while (w1Index >= words.size() || w2Index >= words.size());
  fillAdjacencies(words, p); // 创建邻接表
  dijkstraString(w1Index, w2Index, words); // dijkstra算法找有源最短路径
  cout << endl;
  printPath(w2Index, words); // print the result
}
