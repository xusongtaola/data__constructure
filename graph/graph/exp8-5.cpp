/*-------------采用普里姆算法求最小生成树---------------*/
#include "graph.h"
#include <stdlib.h>
void Prim(MatGraph g, int v) {
	int lowcost[MAXV], min, n = g.n;			//lowcost表示U-V中每一个点的最小权重边
	int closest[MAXV], i, j, k;					//closest表示U-V中每个点对应的最小边的另一点
	for (i = 0; i < n; i++) {					//给lowcost和closest赋初值，最初他们的目标只有一个点
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	for (i = 1; i < n; i++) {					//表示遍历n-1遍，将所有的点全部纳入U中
		min = INF;
		for(j=0;j<n;j++)
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];				//比较最小值
				k = j;							//k记录最终比较所有U-V中顶点对应边最小的编号
			}
		printf(" 边(%d,%d)权为：%d\n", closest[k], k, min);		//closest[k]在后面的循环中已经修订好了，每个点对应的U中最小点已经确定，这采取的是逐级（逐点）比较的思想。
		lowcost[k] = 0;							//标记k已经加入U中
		for(j=0;j<n;j++)						//对于U-V中的结点再次比较修改，将每一个点到U中的最小值进行修改，看看k加入U中后，最小值是否发生变化，变化了就把其最小边改到k点去。
			if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j]) {		//每次都进行一次比较，每次只是比较最新加入的一个点，这样实际上每次U-V中每个点都一直能得到更新。
				lowcost[j] = g.edges[k][j];
				closest[j] = k;
			}
	}
}
int main() {
	int v = 3;
	MatGraph g;
	int A[MAXV][MAXV] = {
		{0,5,8,7,INF,3},{5,0,4,INF,INF,INF},{8,4,0,5,INF,9},
		{7,INF,5,0,5,6},{INF,INF,INF,5,0,1},{3,INF,9,6,1,0}
	};
	int n = 6, e = 10;
	CreateMat(g, A, n, e);
	printf("图G的邻接矩阵：\n"); DispMat(g);
	printf("普里姆算法求解结果：\n");
	Prim(g, 0);
	system("pause");
	return 1;
}