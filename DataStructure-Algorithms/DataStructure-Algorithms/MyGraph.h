#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <utility>
#include <vector>
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
