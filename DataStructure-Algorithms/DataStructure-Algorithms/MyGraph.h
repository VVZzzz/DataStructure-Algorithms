#pragma once
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <utility>
#include <vector>
#include "MyDisjSets.h"
using namespace std;
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
    int lowNum;    //后序编号(寻找割点时需要)

    /*无权最短路径所需成员*/
    int dist;      // s到该结点的距离
    Vertex *path;  //记录路径：path到该节点

    /*有权负值路径所需成员*/
    bool isInqueue;  //是否进入了队列

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

  // kruskal算法需要的并查集成员(注意并查集类的底层类型是int)
  MyDisjSets disjsets;

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
    int tempdis = INT_MAX;
    for (auto &c : vvector) {
      if (!c.known) {
        if (c.dist <= tempdis) {
          vp = &c;
          tempdis = c.dist;
        }
      }
    }
    return vp;
  }

  /**
   * 单源加权负值路径算法(Dijkstra算法不适用)
   * 适用于路径为负值
   * O(|E|*|V|)
   */
  void weightedNegative(Vertex *v);

  /**
   * 最小生成树:Prim算法 Kruskal算法
   */

  /**
   * Prim算法:
   * 和Dijkstra算法极为相似
   * 不同在于:更新dw时,不再比较dw和dv+c(v.w)而是直接比较dv dw
   */
  void primMinSpanTree(Vertex *v);

  /**
   * Kruskal算法:
   * 主要用到并查集,优先队列
   * 每次通过优先队列找最小权值的边,将边的两个结点放入并查集
   * 直到所有结点都联通
   */
  void kruskalMinSpanTree();

  /**
   * 重要
   * DFS:深度优先搜索模板
   * 递归
   */
  void dfs(Vertex *v);

  /**
   * DFS的应用: 寻找割点(双连通性)
   * 步骤1 2 3
   * 1.前序遍历得到谦虚编号 assignNum(v) 即topNum (DFS遍历)
   * 2.后序遍历得到后序编号 assignLow(v) 即lowNum
   * 3.通过Num(v)和Low(v)判断v是否为割点(在assignLow()中)
   *
   * Low(v)可能是:
   * 1.Num(v)
   * 2.所有后向边(v,w)中的最低Num(w)
   * 3.树的所有边(v,w)中的最低Low(w)
   *
   * 割点为:前向边(v,w),若w.lowNum>=v.topNum,则v是割点
   */
  void assignNum(Vertex *v);
  void assignLow(Vertex *v);

  //结合assignNum和assignLow的算法:
  void findArtPoint(Vertex *v);
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
    vp->known = true;
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

template <typename T>
void MyGraphList<T>::primMinSpanTree(Vertex *v) {
  for (auto &c : vvector) {
    c.known = false;
    c.dist = INT_MAX;
  }
  v->known = true;
  v->dist = 0;
  while (true) {
    Vertex *vp = findSmallestUnknownVertex();
    if (vp == nullptr) break;
    vp->known = true;
    for (auto &c : vp->adjList) {
      if (!((c.first)->known)) {
        if (c.second < c.first->dist) {  //
          c.first->dist = c.second;  //注意这两句和Dijkstra算法的区别
          c.first->path = vp;
        }
      }
    }
  }
}

template <typename T>
void MyGraphList<T>::kruskalMinSpanTree() {
  int edgesAccepted = 0;
  std::priority_queue<int> pq;
  /*
  将边长push进优先队列，建队。
  for(auto e:dist)
    pq.push(e);
  */
  while (edgesAccepted < vvector.size()) {
    int e = pq.top();  // e为pq.top(),即最短的边。其两个结点为u v.
    int u, v;
    int uset = disjsets.find_pathcompress(u);
    int vset = disjsets.find_pathcompress(v);
    if (uset != vset) {
      edgesAccepted++;
      disjsets.unionSets_height(uset, vset);  // union这个边的两个的结点
    }
  }
}

template <typename T>
void MyGraphList<T>::dfs(Vertex *v) {
  v->known = true;
  for (auto &c : v->adjList) {
    if (!(c.first->known)) {
      dfs(c.first);
    }
  }
}

template <typename T>
void MyGraphList<T>::assignNum(Vertex *v) {
  static int counter(1);
  v->topNum = counter++;
  v->known = true;
  for (auto &c : v->adjList) {
    if (!(c.first->known)) {
      c.first->path = v;
      assignNum(c.first);
    }
  }
}

template <typename T>
void MyGraphList<T>::assignLow(Vertex *v) {
  v->lowNum = v->topNum;  //规则1
  for (auto &w : v->adjList) {
    if (w.first->topNum > v->topNum) {  //若(v,w)是前向边
      assignLow(w.first);               // DFS遍历
      if (w.first->lowNum >= v->topNum)
        std::cout << v->data << " is an articulation point. " << std::endl;
      v->lowNum = std::min(v->lowNum, w.first->lowNum);  //规则3
    } else {  //若(v,w)是后向边,则规则2
      if (v->path != w.first) v->lowNum = std::min(v->lowNum, w.first->lowNum);
    }
  }
}

template <typename T>
void MyGraphList<T>::findArtPoint(Vertex *v) {
  static int counter(1);
  v->known = true;
  v->lowNum = v->topNum = counter++;  //规则1
  for (auto &w : v->adjList) {
    if (!(w.first->known)) {
      w.first->path = v;
      findArtPoint(w.first);  // DFS遍历
      if (w.first->lowNum >= v->topNum)
        std::cout << v->data << " is an articulation point. " << std::endl;
      v->lowNum = std::min(v->lowNum, w.first->lowNum);  //规则3
    } else {  //若(v,w)是后向边,则规则2
      if (v->path != w.first) v->lowNum = std::min(v->lowNum, w.first->lowNum);
    }
  }
}

/**
 * 所有顶点对的最短路径问题
 * 无权最短路径:字梯问题
 * 目标:得到所有单词的最短路径
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
