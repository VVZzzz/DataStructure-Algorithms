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

  void topsort();  //拓扑排序,Θ(|V|+|E|)
 private:
  //顶点类型
  struct Vertex {
    T data;  //顶点数据
    std::list<std::pair<Vertex *, int>>
        adjList;   //邻接表,first为结点,second为s到这个结点的距离
    int topNum;    //拓扑排序的编号
    int indegree;  //入度
    bool known;    //是否已被处理(求解最短路径时)

    /*无权最短路径所需成员*/
    int dist;      // s到该结点的距离
    Vertex *path;  //记录路径：path到该节点
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
   * 无权最短路径算法,BFS(广度搜索优先)
   * 借用队列或栈,原理类似于层序遍历
   * 不必使用bool known;
   */
  void unweighedShortestPath(Vertex *v);

  /**
   * 单源加权最短路径算法,Dijkstra算法
   * 只适用于路径长度不为负值
   * v,w结点的距离即v.adjList.second
   * 朴素算法，时间为O(|E|+|V|^2),适用于稠密图|E|=Θ(|V|^2)
   * 但对于稀疏图,在更新w结点的距离时,可采用优先队列P 262
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
  if (counter != vvector.size()) std::cout << "该图有环!" << std::endl;
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
