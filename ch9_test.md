## Ch9 
------------------------------------
1. 图的后序遍历即将前序遍历得到的编号反过来
2. 查找强连通分支的时候，后序编号不唯一（因为后序遍历有可能多种情况）   

### 9.1  
使用队列: s, G, D, H, A, B, E, I, F, C, t  
### 9.2  
使用栈: s, G, H, D, A, E, I, F, B, C, t  

### 9.3（重要） 
见```MyGraph.h```

### 9.4（没看懂题意...）（和5.12练习类似）


### 9.5
a.加权最短路径(Dijkstra算法(广度优先))  

			   d  path  
			A  0   A
			B  5   A
			C  3   A
			D  9   E  
			E  7   G
			F  8   E  
			G  6   B   
代码如下：

	void Dijkstra(Vertex *v)
	{
	  //所有结点dist为∞
	  v->dist=0;
	  v->path=v;
	  v->known=true;
		while(true)
		{
		  v=SmallestDistUnknownVertex();
		  if(v==nullptr) break;
			  for each w of v->adjList
			    {
			      if(dv+c(v,w)<dw)
			        w->dist=dv+c(v,w);
			        w->path=v;
			    }
		}
	}   

b.无权最短路径  

			   d  path  
			A  0   A
			B  5   A
			C  3   A
			D  9   C  
			E  7   B
			F  8   E  
			G  6   B   
代码如下：

	void Dijkstra(Vertex *v)
	{
      queue<Vertex*> q;
	  //所有结点dist为∞
	  v->dist=0;
	  v->path=v;
	  q.push(v);
		while(!q.empty())
		{
		  v=q.front();
          v.pop();
		  for each w of v->adjList
		    {
		      if(dw==INITFY)
		        w->dist=dv+1;
		        w->path=v;
		    }
		}
	}   


### 9.6（重要）
如果在Dijkstra算法中使用d堆，需要|E|次的decreaseKey操作，进行路径的更新。还需要|V|次的deleteMin操作。而对于d堆，decreaseKey操作为O(log(d)N),deleteMin操作为O(d * log(d)N).  
故需要O(|E|log(d)N+|V|*d*log(d)N),实践证明使用d堆不能提高效率。   

### 9.7 
Dijkstra算法无法应用于边值为负数的情况。   

### 9.8（和9.19相同）

### 9.9
见```MyGraph.h```   

### 9.10 (重要)  
a.首先用一个数组count[]保存各个顶点的最短路径数。初始都为0
如果```if(dv+c(v,w)<dw)```更新count[w]=count[v],因为之前的路径不是最短路径。故全部更新。    
如果```if(dv+c(v,w)==dw)```则count[w]+=count[v].之前已有的路径数目，在加上v的最短路径数即可。
伪代码如下: 

	void Dijkstra(Vertex *v)
	{
	  //所有结点dist为∞
	  v->dist=0;
	  v->path=v;
	  v->known=true;
      count[v]=1;
		while(true)
		{
		  v=SmallestDistUnknownVertex();
		  if(v==nullptr) break;
			  for each w of v->adjList
			    {
			      if(dv+c(v,w)<dw)
                  {
					w->dist=dv+c(v,w);
			        w->path=v;
					count[w]=count[v];
				  }
				  if(dv+c(v,w)==dw)
                    count[w]+=count[v];			        
			    }
		}
	}

b.和a类似，用numEdge[]数组保存各个顶点的最短路径的边数。初始都为0.    
```if(dv+c(v,w)<dw)```更新numEdge[w]=numEdge[v]+1;
```if(dv+c(v,w)==dw)```除非numEdge[v]+1更小，更新path和numEdge[w].    
伪代码如下：

	void Dijkstra(Vertex *v)
	{
	  //所有结点dist为∞
	  v->dist=0;
	  v->path=v;
	  v->known=true;
      numEdge[v]=0;
		while(true)
		{
		  v=SmallestDistUnknownVertex();
		  if(v==nullptr) break;
			  for each w of v->adjList
			    {
			      if(dv+c(v,w)<dw)
                  {
					w->dist=dv+c(v,w);
			        w->path=v;
					numEdge[w]=numEdge[v]+1;
				  }
				  if(dv+c(v,w)==dw)
                    {
					  if(numEdge[w]<numEdge[v]+1)
						{ 
							numEdge[w]=numEdge[v]+1;
							w->path=v;
						}
					}			        
			    }
		}
	} 

### 9.11（求网络最大流）（重要）

### 9.12（树的最大流）（重要）
T为树根，incomingCap是T的最大输入流。   
采取递归策略(DFS),得到总的最大流。  
伪代码如下：

	FlowType findMaxFlow( Tree T, FlowType incomingCap)
	{
	  int totalFlow=0,childFlow=0;
	  if(T.hasNoSubtrees())
		return incomingCap;
	  else
	  {
		for(each T_i of T's SubTrees)
	    {
		  childFlow+=findMaxFlow(T_i,min(T_i's incomingCap,incomingCap);
		  totalFlow+=childFlow;
		  incomingCap-=childFlow;
		}
		return totalFlow;
	  }
	}   

### 9.13 （二分图）（二分匹配）（重要）
a.  二分图指边的两个顶点分别在不同的两个集合中。   
如何判断是否是二分图：   
1. 任意取一个顶点标为red    
2. 从该顶点出发进行DFS，如果出发点是red，则将其邻接点设为blue，反之设为red.   
3. 重复1 2 
4. 在DFS的过程中，如果有出发点是red，其邻接点也是red。或者同为blue,说明它不是一个二分图。否则是！  

b. c. d. e.  
没看懂   

### 9.14 （重要）（允许最大流的增长路径） 
注意和9.11练习的区别。9.11是求最大流，9.14是求允许最大流通过的增长路径。   
实际上只需修改Dijkstra算法即可。  
1. 设f(s)为s的容许通过的最大流，初始时，源点s的f(s)为无穷大,剩下的都为0.  
2. 每次都选择未知的顶点中f最大的顶点v  
3. 对于v的所有邻接点w,若此时min(f(v),c(v,w))大于f(w).则更新f(w)和p(w).   
伪代码如下：  

	void Dijkstra(Vertex *v)
	{
	  //所有结点flow为0
	  v->flow=INF;
	  v->path=v;
	  v->known=true;
		while(true)
		{
		  v=LargestDistUnknownVertex();
		  if(v==nullptr) break;
			  for each w of v->adjList
			    {
			      if(min(fv,c(v,w))>fw)
			        w->flow=min(fv,c(v,w);
			        w->path=v;
			    }
		}
	}      


### 9.15 （重要）
1.Prim算法最小生成树：
	   
		   d  Path  
		A  3  D
		B  3  A  
		C  1  G  
		D  0  D  
		E  2  B  
		F  3  B  
		G  2  F  
		H  2  E
		I  1  E  
		J  7  I

伪代码如下：
  
		void Prim(Vertex *v)
		{
		  v->dist=0;
		  v->known=true;
		  v->path=v;
		  while(true) 
		  {
		    v=findSmallestDistUnknownVertex();
		    if(v==nullptr) break;
		  	for each w of v's unknown adjVertex
		    {
		   	  if(c(v,w)<dw) 
		      {
				w->dist=c(v,w);
				w->path=v;
			  }
		    }
		  }
		}

2.Kruskal算法：
 结果同上，伪代码：
   
		void Kruskal(Vertex *v)
		{
		  Disjsets disjsets(NUM_VERTEICES);
		  prioity_queue<Edge> pq(edges);
		  int acceptedEdges=0;
		  while(acceptedEdges<NUM_VERTEICES-1)
		  {
			u,v=pq.front().Vertex();
		    auto uset=disjsets.find(u);
		    auto vset=disjsets.find(v);
			if(uset != vset)
			{
			  disjsets.union(uset,vset);
			  acceptedEdges++;
			}
		  }
		}  


### 9.17 （证明略）
### 9.18 （Kruskal伪代码如上）  
### 9.19 
主要花费在并查集的find/union操作上。

### 9.25（重要）（有向图边(v,w)的类别）
1. Num[v]!=Num[w]可以明显得到v w不是同一个顶点，而是一条边。
2. Num[v]>Num[w]&&low[v]>low[w] 得到(v,w)是一个交叉边，即v w不在同一条边上。 Num[v]>Num[w]保证v不是w的后代，low[v]>low[w]保证w不是v的后代。故是交叉边。
3. 其余的情况，假设Num[v]>Num[w],通过进行DFS时将边push进栈可以判断(v,w)是前向边还是后向边。  

### 9.26 （非常重要）（找强连通分支）
首先从A顶点进行后序遍历，并为所有顶点给出后序编号。       
将原图的所有边进行反向，得到图Gr。      
其次，对Gr进行前序遍历，每次都选区编号最大的顶点进行前序遍历。得到强连通分支。  

### 9.29 （重要）（查找双联通分支）（没搞懂）
将边(V,w)push入堆栈，如果此时v被确定为割点，low[w]≥num[v]，则弹出堆栈直到去除（v，w）：弹出边缘的集合是双连通分量。 如果边（w，v）已经作为后向边处理，则边（v，w）不会放置在堆叠上。   

### 9.30 
证明略

### 9.31 
这与欧拉回路不同，只是在不同方向通过一次即可。用DFS，前序遍历之后的递归返回是另一个方向。两个方向各有一次。  

### 9.32  9.33 （欧拉回路）
（待做）

### 9.34
都不行，对于下图：
![](https://i.imgur.com/pn26nX7.png)  
从A点出发，总是要回到A点。

### 9.35
证明略

### 9.36 
所有算法都可以在多重图下运行。  

### 9.37（重要）（联通无向图转为强连通有向图）
1. 首先图G必须是联通的，否则无法转换。
2. 若图G中存在一条边断开后，不再是连通图。则无法转换
3. 否则，对G进行DFS，设从A(根）开始，则将所有的后向边都指向根直到遍历完所有结点。   

### 9.38
将每个木棍用一个顶点表示，如果Si高于Sj,则表示为Si->Sj.  
最终求图的拓扑排序即可确定拿取木棍的顺序。（若图中有环则无法完成。）

### 9.39 
深度优先搜索即可。

### 9.40
贪心策略

### 9.41
找到入度大于0的顶点，从该处出发，DFS直到遍历两遍这个顶点。找到环。

### 9.42
对于矩阵A[s,t]，A[s,t]=0则没有s到t的边，t有可能是汇点。若A[s,t]不为0，则s必不是汇点。  
首先检查一遍|v|可得到一些候选者，对这些候选者进行排查即可。  

### 9.43 
进行DFS后序遍历，并标号，标号大小大于N/2的第一个顶点，即为所求。

### 9.44
即关键路径，对于这题可以用DFS即可。

### 9.45 
DFS就完事了。

### 9.46 
破解迷宫即为：单源无权最短路径问题。用BFS广度优先搜索即可。

### 9.47
即变为加权最短路径，无墙成本为1，有墙成本为P。Dijkstra算法完事。

### 9.48 （很有意思的迷宫解题）
a.     
思想仍是Dijkstra算法，用一个双端队列进行操作。    
1. 从A开始BFS，将A的邻接非墙方块```push_front```，将A的邻接墙块进行```push_back```.   
2. 之后将队列中的前半部分（非墙结点）出队，并同样的1规则进行下去。直到到达出口。   
3. 如果其中一个出队的结点的邻接点有边界，则边界不入队。  
4. 如果最后一个非墙结点出队之后仍到达不了出口，**说明此迷宫是无解的需要拆墙。**则将队列的墙部分进行pop_back,从队末出队，并继续同1的规则进行push它的邻接结点。    
5. 出队的序列即为最短拆墙最少路径。  

### 9.49 
即练习9.47  

### 9.50
即图的一边，如果X可以到Y则可以说明X强于Y。

### 9.51
每一个货币都是一个顶点，比如例子中的X Y。X到Y的距离为X到Y的汇率的**对数**，即log2，换成对数的原因是因为对数可以将“+”变成“*”.   
之后找到最短路径和最长路径即可得到利润.  

### 9.52 
每门课都是一个顶点,找到最长路径即可学期数最少.

### 9.53 
略

### 9.54 55 56
略