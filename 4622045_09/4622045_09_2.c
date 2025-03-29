#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50 /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */

int main(void) {
    int N, M; /* 頂点数，辺数 */
    int Adj[maxN][maxN]; /* 隣接行列を表す変数 */
    int d[maxN], p[maxN], color[maxN]; /* 配列変数 d, p, color */
    int v0; /* 始点の変数 */
    int Q[maxN]; /* キューを表す変数 */
    int head, tail; /* キューの先頭と末尾 */
    int u, v;
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */

    printf("input filename: "); /* ファイル名の入力を要求 */
    scanf("%s", fname); /* ファイル名の入力を受け取る */

    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */

    fscanf(fp, "%d %d", &N, &M); /* ファイルから N, M を読み込む */

    for (u = 0; u < N; u++) { /* 隣接行列の初期化 */
        for (v = 0; v < N; v++) {
            Adj[u][v] = 0;
        }
    }

    for (int i = 0; i < M; i++) {
        fscanf(fp, " %d %d", &u, &v); /* 順番に辺の両端 u, v を読み込む */
        Adj[u][v] = 1;
        Adj[v][u] = 1; /* 無向グラフの場合 */
    }

    fscanf(fp, " %d", &v0); /* 始点 v0 を読み込む */
    fclose(fp);

    /* 幅優先探索の初期化 */
    for (u = 0; u < N; u++) {
        d[u] = inf;
        p[u] = -1;
        color[u] = 0; /* 白色 */
    }
    d[v0] = 0;
    color[v0] = 1; /* 灰色 */

    head = tail = 0;
    Q[tail++] = v0;

    while (head != tail) {
        u = Q[head++];
        for (v = 0; v < N; v++) {
            if (Adj[u][v] && color[v] == 0) { /* 隣接していて未訪問の頂点を探索 */
                d[v] = d[u] + 1;
                p[v] = u;
                color[v] = 1; /* 灰色 */
                Q[tail++] = v;
            }
        }
        color[u] = 2; /* 黒色 */
    }

    /* 結果の出力 */
    for (u = 0; u < N; u++) {
        printf("vertex %d: d[%d] = %d, p[%d] = %d\n", u, u, d[u], u, p[u]);
    }

    return 0;
}
