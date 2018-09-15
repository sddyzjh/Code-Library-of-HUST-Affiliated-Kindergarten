/*
	调用maxflow()返回最大流
	S,T为源汇
	addedge(u,v,f,F)F为反向流量
	多组数据时调用Ginit()
*/
struct E{
	int v, f, F, n;
}G[M];
int point[N], D[N], cnt, S, T;
void Ginit(){
	cnt = 1;
	fill(point,0,T+1);
}
void addedge(int u, int v, int f, int F){
	G[++cnt] = (E){v, 0, f, point[u]}, point[u] = cnt;
	G[++cnt] = (E){u, 0, F, point[v]}, point[v] = cnt;
}
int BFS(){
	queue<int> q;
	fill(D,0,T+1);
	q.push(S);
	D[S] = 1;
	while (!q.empty()){
		int u = q.front();q.pop();
		for_each_edge(u)
			if (G[i].F > G[i].f){
				int v = G[i].v;
				if (!D[v]){
					D[v] = D[u] + 1;
					if(v==T)return D[T];
					q.push(v);
				}
			}
	}
	return D[T];
}
int Dinic(int u, int F){
	if (u == T)	return F;
	int f = 0;
	for_each_edge(u){
		if(F<=f)break;
		int v = G[i].v;
		if (G[i].F > G[i].f && D[v] == D[u] + 1){
			int temp = Dinic(v, min(F - f, G[i].F-G[i].f));
			if (temp == 0)
				D[v] = 0;
			else{
				f += temp;
				G[i].f += temp;
				G[i^1].f -= temp;
			}
		}
	}
	if(!f)D[u]=0;
	return f;
}
int maxflow(){
	int f = 0;
	while (BFS())
		f += Dinic(S, infi);
	return f;
}
/*
最大权闭合子图
	在一个有向无环图中,每个点都有一个权值。
	现在需要选择一个子图，满足若一个点被选，其后继所有点也会被选。最大化选出的点权和。
	建图方法：源向所有正权点连容量为权的边，所有负权点向汇点连容量为权的绝对值的边。若原图中存在有向边<u,v>，则从u向v连容量为正无穷的边。答案为所有正权点和 – 最大流
最大权密度子图
	在一个带点权带边权无向图中，选出一个子图，使得该子图的点权和与边权和的比值最大。
	二分答案k，问题转为最大化|V|-k|E|
	确定二元关系：如果一条边连接的两个点都被选择，则将获得该边的权值(可能需要处理负权)
二分图最小点权覆盖集
	点覆盖集：在无向图G=(V,E)中，选出一个点集V′，使得对于任意<u,v>属于E，都有u属于V'或v属于V′，则称V′是无向图G的一个点覆盖集。
	最小点覆盖集：在无向图中，包含点数最少的点覆盖集被称为最小点覆盖集。
	这是一个NPC问题，但在二分图中可以用最大匹配模型快速解决。

	最小点权覆盖集：在最小点覆盖集的基础上每个点均被赋上一个点权。
	建模方法：对二分图进行黑白染色，源点向白点连容量为该点点权的边，黑点向汇点连容量为该点点权的边，对于无向边<u,v>，设u为白点，则从u向v连容量为正无穷的边。最小割即为答案。
二分图最大点权独立集
	点独立集：在无向图G=(V,E)中，选出一个点集V′，使得对于任意u,v属于V',<u,v>不属于E'，则称V′是无向图G的一个点独立集。
	最大点独立集：在无向图中，包含点数最多的点独立集被称为最大点独立集。
	|最大独立集| = |V|-|最大匹配数|
	这是一个NPC问题，但在二分图中可以用最大匹配模型快速解决。
	最大点权独立集：在最大点独立集的基础上每个点均被赋上一个点权。
	建模方法：对二分图进行黑白染色，源点向白点连容量为该点点权的边，黑点向汇点连容量为该点点权的边，对于无向边<u,v>，设u为白点，则从u向v连容量为正无穷的边。所有点权-最小割即为答案。
最小路径覆盖
	在一个DAG中，用尽量少的不相交的简单路径覆盖所有的节点。
	最小路径覆盖数=点数-路径中的边数
	建立一个二分图，把原图中的所有节点分成两份（X集合为i，Y集合为i‘），如果原来图中有i->j的有向边，则在二分图中建立i->j’的有向边。最终|最小路径覆盖|=|V|-|最大匹配数|

无源汇可行流
	建图方法:
	首先建立附加源点ss和附加汇点tt,对于原图中的边x->y，若限制为[b,c]，那么连边x->y，流量为c-b,对于原图中的某一个点i，记d(i)为流入这个点的所有边的下界和减去流出这个点的所有边的下界和 
	若d(i)>0，那么连边ss->i，流量为d(i),若d(i)<0，那么连边i->tt，流量为-d(i)
	求解方法:
		在新图上跑ss到tt的最大流,若新图满流，那么一定存在一种可行流,此时，原图中每一条边的流量应为新图中对应的边的流量+这条边的流量下界
有源汇可行流
	建图方法:在原图中添加一条边t->s，流量限制为[0,inf],即让源点和汇点也满足流量平衡条件,这样就改造成了无源汇的网络流图,其余方法同上
	求解方法:同 无源汇可行流
有源汇最大流
	建图方法:同有源汇可行流
	求解方法:在新图上跑ss到tt的最大流,若新图满流，那么一定存在一种可行流,记此时sigma f(s,i)=sum1,将t->s这条边拆掉，在新图上跑s到t的最大流,记此时sigma f(s,i)=sum2,最终答案即为sum1+sum2
有源汇最小流
	建图方法:同 无源汇可行流
	求解方法:求ss->tt最大流,连边t->s,inf,求ss->tt最大流,答案即为边t->s,inf的实际流量
有源汇费用流
	建图方法:首先建立附加源点ss和附加汇点tt,对于原图中的边x->y，若限制为[b,c]，费用为cost，那么连边x->y，流量为c-b，费用为cost,对于原图中的某一个点i，记d(i)为流入这个点的所有边的下界和减去流出这个点的所有边的下界和,若d(i)>0，那么连边ss->i，流量为d(i)，费用为0,若d(i)<0，那么连边i->tt，流量为-d(i)，费用为0,连边t->s，流量为inf，费用为0
	求解方法:跑ss->tt的最小费用最大流,答案即为（求出的费用+原图中边的下界*边的费用）
	注意:有上下界的费用流指的是在满足流量限制条件和流量平衡条件的情况下的最小费用流,而不是在满足流量限制条件和流量平衡条件并且满足最大流的情况下的最小费用流,也就是说，有上下界的费用流只需要满足网络流的条件就可以了，而普通的费用流是满足一般条件并且满足是最大流的基础上的最小费用*/