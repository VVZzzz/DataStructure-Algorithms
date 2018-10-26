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