#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50
#define maxM 500

struct edge_data {
    int end1;
    int end2;
    int weight;
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

void quicksort(int *A, int *ednum, int p, int r);

int partition(int *A, int *ednum, int p, int r) {
    int x = A[r];
    int i = p - 1;
    int temp;

    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            // A[i]とA[j]を入れ替える
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            // ednum[i]とednum[j]を入れ替える
            temp = ednum[i];
            ednum[i] = ednum[j];
            ednum[j] = temp;
        }
    }
    // A[i+1]とA[r]を入れ替える
    temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;
    // ednum[i+1]とednum[r]を入れ替える
    temp = ednum[i + 1];
    ednum[i + 1] = ednum[r];
    ednum[r] = temp;

    return i + 1;
}

void quicksort(int *A, int *ednum, int p, int r) {
    if (p < r) {
        int q = partition(A, ednum, p, r);
        quicksort(A, ednum, p, q - 1);
        quicksort(A, ednum, q + 1, r);
    }
}

void kruskal(int n, int m, struct edge_data *edge, int *ednum, int *T) {
    int p[maxN], rank[maxN];
    // ユニオン・ファインド森の初期化
    for (int i = 0; i < n; i++) {
        make_set(p, rank, i);
    }

    int count = 0; // 最小木に含まれる辺の数
    for (int i = 0; i < m; i++) {
        int k = ednum[i];
        int u = edge[k].end1;
        int v = edge[k].end2;
        if (find_set(p, u) != find_set(p, v)) {
            T[k] = 1; // 辺 k を最小木に含める
            set_union(p, rank, u, v);
            count++;
            if (count == n - 1) // 最小木は頂点数-1本の辺を持つ
                break;
        }
    }
}

int main(void) {
    int N, M;
    struct edge_data edge[maxM];
    int W[maxM];
    int ednum[maxM];
    int *T; // 最小木を表す配列
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

    for (int i = 0; i < M; i++) {
        fscanf(fp, "%d %d %d", &edge[i].end1, &edge[i].end2, &edge[i].weight);
    }
    fclose(fp);

    // ソート用の配列の初期化
    for (int i = 0; i < M; i++) {
        W[i] = edge[i].weight;
        ednum[i] = i;
    }

    // クイックソートで重みを昇順にソート
    quicksort(W, ednum, 0, M - 1);

    // 最小木を表す配列 T のメモリ確保
    T = (int *)malloc(M * sizeof(int));
    if (T == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    memset(T, 0, M * sizeof(int)); // T を 0 で初期化

    // Kruskal法を適用して最小全域木を計算
    kruskal(N, M, edge, ednum, T);

    // 最小全域木に含まれる辺を出力
    for (int i = 0; i < M; i++) {
        if (T[i] == 1) {
            printf("edge (%2d, %2d) weight = %d\n", edge[i].end1, edge[i].end2, edge[i].weight);
        }
    }

    // 動的に確保したメモリを解放
    free(T);

    return 0;
}
