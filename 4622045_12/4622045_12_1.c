#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50
#define maxM 500

struct edge_data {
    int end1;
    int end2;
};

void make_set(int *p, int *rank, int x) {
    p[x] = x;
    rank[x] = 0;
}

int find_set(int *p, int x) {
    if (x != p[x]) {
        p[x] = find_set(p, p[x]); // パス圧縮
    }
    return p[x];
}

void link(int *p, int *rank, int x, int y) {
    if (rank[x] > rank[y]) {
        p[y] = x;
    } else {
        p[x] = y;
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}

void set_union(int *p, int *rank, int x, int y) {
    link(p, rank, find_set(p, x), find_set(p, y));
}

int main(void) {
    int N, M; /* 頂点数，辺数 */
    struct edge_data edge[maxM];/* 辺データを表す変数 */
    int p[maxN], rank[maxN]; /* p[x], rank[x]を格納する変数 */
    int component[maxN]; /* 連結成分番号 component[u] を格納する変数 */
    int number_comp; /* 連結成分数を表す変数 */
    int u, v;/* 頂点番号を表す変数 */
    int i;
    char fname[128];
    FILE *fp;

    printf("input filename: ");
    scanf("%s", fname);
    fp = fopen(fname, "r");

    fscanf(fp, "%d %d", &N, &M);
    if (N > maxN || M > maxM) {
        printf("N or M is too large, redefine maxN, maxM\n");
        return 1;
    }

    for (i = 0; i < M; i++) {
        fscanf(fp, "%d %d", &u, &v);
        edge[i].end1 = u;
        edge[i].end2 = v;
        //printf("edge[i].end1 = %d, v = %d\n", u, v);
    }
    fclose(fp);

    for (u = 0; u < N; u++) {
        make_set(p, rank, u);
    }

    for (i = 0; i < M; i++) {
        set_union(p, rank, edge[i].end1, edge[i].end2);
        //printf("p[%d] = %d, rank[%d] = %d\n", i, p[i], i, rank[i]);
    }

    number_comp = 0;
    for (u = 0; u < N; u++) {
        component[u] = find_set(p, u);
        /*if (component[u] == u) {
            number_comp++;
        }*/
    }

    int component_id[maxN];
    memset(component_id, -1, sizeof(component_id));
    int current_id = 1;
    for (u = 0; u < N; u++) {
        int root = find_set(p, u);
        if (component_id[root] == -1) {
            component_id[root] = current_id++;
        }
        component[u] = component_id[root];
    }
    number_comp = current_id - 1;

    printf("Number of connected components: %d\n", number_comp);
    for (u = 0; u < N; u++) {
        printf("Vertex %d: component = %d, parent = %d, rank = %d\n", u, component[u], p[u], rank[u]);
    }

    return 0;
}
