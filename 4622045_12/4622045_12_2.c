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
        p[x] = find_set(p, p[x]); 
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
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            temp = ednum[i];
            ednum[i] = ednum[j];
            ednum[j] = temp;
        }
    }
    temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;
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

int main(void) {
    int N, M;
    struct edge_data edge[maxM];
    int W[maxM];
    int ednum[maxM];
    int u, v, w;
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
        fscanf(fp, "%d %d %d", &u, &v, &w);
        edge[i].end1 = u;
        edge[i].end2 = v;
        edge[i].weight = w;
    }
    fclose(fp);

    for (int i = 0; i < M; i++) {
        W[i] = edge[i].weight;
        ednum[i] = i;
    }

    quicksort(W, ednum, 0, M - 1);

    for (int i = 0; i < M; i++) {
        int k = ednum[i];
        printf("edge %2d: (%2d, %2d) weight = %d\n", k, edge[k].end1, edge[k].end2, edge[k].weight);
    }

    return 0;
}
