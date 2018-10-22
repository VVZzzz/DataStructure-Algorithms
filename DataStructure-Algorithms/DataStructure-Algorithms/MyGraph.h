#pragma once
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
template <typename T>

class MyGraphList {
 public:
  MyGraphList() = default;

  void topsort();  //��������,��(|V|+|E|)
 private:
  //��������
  struct Vertex {
    T data;  //��������
    std::list<std::pair<Vertex *, int>>
        adjList;   //�ڽӱ�,firstΪ���,secondΪs��������ľ���
    int topNum;    //��������ı��
    int indegree;  //���
    bool known;    //�Ƿ��ѱ�����(������·��ʱ)

    /*��Ȩ���·�������Ա*/
    int dist;      // s���ý��ľ���
    Vertex *path;  //��¼·����path���ýڵ�

    /*��Ȩ��ֵ·�������Ա*/
    bool isInqueue;  //�Ƿ�����˶���

    Vertex(const T &d, const list<std::pair<Vertex *, int>> &adj, int t, int id,
           bool k)
        : data(d), adjList(adj), topNum(t), indegree(id), known(k) {}
    Vertex()
        : data(T()),
          adjList(std::list<std::pair<Vertex *, int>>()),
          topNum(-1),
          indegree(0),
          dist(INT_MAX),
          path(this),
          known(false) {}
  };
  std::vector<Vertex> vvector;

  /**
   * ��Ȩ���·���㷨,BFS(�����������)
   * ���ö��л�ջ,ԭ�������ڲ������
   * ����ʹ��bool known;
   */
  void unweighedShortestPath(Vertex *v);

  /**
   * ��Դ��Ȩ���·���㷨,Dijkstra�㷨
   * ֻ������·�����Ȳ�Ϊ��ֵ
   * v,w���ľ��뼴v.adjList.second
   * �����㷨��ʱ��ΪO(|E|+|V|^2),�����ڳ���ͼ|E|=��(|V|^2)
   * ������ϡ��ͼ,�ڸ���w���ľ���ʱ,�ɲ������ȶ���P 262
   */
  void dijkstraWeighedPath(Vertex *v);

  Vertex *findSmallestUnknownVertex() {
    Vertex *vp = nullptr;
    T tempdis = INT_MAX;
    for (auto &c : vvector) {
      if (!c.known) {
        if (c.data <= tempdis) vp = &c;
      }
    }
    return vp;
  }

  /**
   * ��Դ��Ȩ��ֵ·���㷨(Dijkstra�㷨������)
   * ������·��Ϊ��ֵ
   * O(|E|*|V|)
   */
  void weightedNegative(Vertex *v);
};

template <typename T>
void MyGraphList<T>::topsort() {
  std::queue<Vertex *> q;
  std::vector<int> temp_indegree(vvector.size());
  for (int i = 0; i < vvector.size(); i++) {
    temp_indegree[i] = vvector[i].indegree;
  }
  int counter = 0;
  for (auto &c : vvector)
    if (c.indegree == 0) q.push(&c);
  while (!q.empty()) {
    Vertex *vp = q.front();
    q.pop();
    vp->topNum = ++counter;
    std::list<std::pair<Vertex *, int>> &l = vp->adjList;
    for (auto itr = l.begin(); itr != l.end(); itr++)
      if (--((*itr).first->indegree) == 0) q.push(*itr.first);
  }
  for (int i = 0; i < vvector.size(); i++) {
    vvector[i].indegree = temp_indegree[i];
  }
  if (counter != vvector.size()) std::cout << "��ͼ�л�!" << std::endl;
}

template <typename T>
void MyGraphList<T>::unweighedShortestPath(Vertex *v) {
  std::queue<Vertex *> q;
  for (auto &c : vvector) c.dist = INT_MAX;
  v->dist = 0;
  v->path = v;
  q.push(v);
  while (!q.empty()) {
    Vertex *temp = q.front();
    q.pop();
    for (auto &c : temp->adjList) {
      if (c.first->dist == INT_MAX) {
        c.first->dist = temp->dist + 1;
        c.first->path = temp;
        q.push(c.first);
      }
    }
  }
}

template <typename T>
void MyGraphList<T>::dijkstraWeighedPath(Vertex *v) {
  for (auto &c : vvector) {
    c.known = false;
    c.dist = INT_MAX;
  }
  v->known = true;
  v->dist = 0;
  while (true) {
    Vertex *vp = findSmallestUnknownVertex();
    if (vp == nullptr) break;
    for (auto &c : vp->adjList) {
      if (!((c.first)->known)) {
        if (vp->dist + c.second < c.first->dist) {
          c.first->dist = vp->dist + c.second;
          c.first->path = vp;
        }
      }
    }
  }
}

template <typename T>
void MyGraphList<T>::weightedNegative(Vertex *v) {
  std::queue<Vertex *> q;
  for (auto &c : vvector) {
    c.dist = INT_MAX;
    c.isInqueue = false;
  }
  v->dist = INT_MAX;
  v->path = v;
  v->isInqueue = true;
  while (!q.empty()) {
    Vertex *vp = q.front();
    q.pop();
    for (auto itr = vp->adjList.begin(); itr != vp->adjList.end(); itr++) {
      if (vp->dist + *itr.second < *itr.first->dist) {
        *itr.first->dist = vp->dist + *itr.second;
        *itr.first->path = vp;
        if (!(*itr.first->isInqueue)) q.push(*itr.first);
      }
    }
  }
}

/**
 * ���ж���Ե����·������
 * ��Ȩ���·��:��������
 * Ŀ��:�õ����е��ʵ����·��
 */
map<string, string> findChain(const map<string, vector<string>> &adjacentWords,
                              const string &first) {
  map<string, string> previousWord;
  queue<string> q;
  q.push(first);
  while (!q.empty()) {
    string current = q.front();
    q.pop();
    auto itr = adjacentWords.find(current);
    const vector<string> &adj = itr->second;
    for (int i = 0; i < adj.size(); i++) {
      if (previousWord[adj[i]] == "") {
        previousWord[adj[i]] = current;
      }
    }
  }
}
