/*-------------��������ķ�㷨����С������---------------*/
#include "graph.h"
#include <stdlib.h>
void Prim(MatGraph g, int v) {
	int lowcost[MAXV], min, n = g.n;			//lowcost��ʾU-V��ÿһ�������СȨ�ر�
	int closest[MAXV], i, j, k;					//closest��ʾU-V��ÿ�����Ӧ����С�ߵ���һ��
	for (i = 0; i < n; i++) {					//��lowcost��closest����ֵ��������ǵ�Ŀ��ֻ��һ����
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	for (i = 1; i < n; i++) {					//��ʾ����n-1�飬�����еĵ�ȫ������U��
		min = INF;
		for(j=0;j<n;j++)
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];				//�Ƚ���Сֵ
				k = j;							//k��¼���ձȽ�����U-V�ж����Ӧ����С�ı��
			}
		printf(" ��(%d,%d)ȨΪ��%d\n", closest[k], k, min);		//closest[k]�ں����ѭ�����Ѿ��޶����ˣ�ÿ�����Ӧ��U����С���Ѿ�ȷ�������ȡ�����𼶣���㣩�Ƚϵ�˼�롣
		lowcost[k] = 0;							//���k�Ѿ�����U��
		for(j=0;j<n;j++)						//����U-V�еĽ���ٴαȽ��޸ģ���ÿһ���㵽U�е���Сֵ�����޸ģ�����k����U�к���Сֵ�Ƿ����仯���仯�˾Ͱ�����С�߸ĵ�k��ȥ��
			if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j]) {		//ÿ�ζ�����һ�αȽϣ�ÿ��ֻ�ǱȽ����¼����һ���㣬����ʵ����ÿ��U-V��ÿ���㶼һֱ�ܵõ����¡�
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
	printf("ͼG���ڽӾ���\n"); DispMat(g);
	printf("����ķ�㷨�������\n");
	Prim(g, 0);
	system("pause");
	return 1;
}