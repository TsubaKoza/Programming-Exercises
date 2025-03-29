#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */

#define maxN 50 /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */

int Adj[maxN][maxN]; /* 隣接行列を表す変数 */
int N, M; /* 頂点数，辺数 */
int d[maxN], f[maxN], p[maxN], color[maxN]; /* 配列変数 d, f, p, color */
int time; /* 時刻を表す変数 */

void traverse(int u) {
    color[u] = 1; /* 灰色 (発見した) */
    time++;
    d[u] = time;
    for (int v = 0; v < N; v++) {
        if (Adj[u][v] && color[v] == 0) {
            p[v] = u;
            traverse(v);
        }
    }
    color[u] = 2; /* 黒色 (完了した) */
    time++;
    f[u] = time;
}

int main(void) {
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */
    int u, v;

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
        fscanf(fp, "%d %d", &u, &v); /* 順番に辺の両端 u, v を読み込む */
        Adj[u][v] = 1; /* 無向グラフの場合は Adj[v][u] = 1 も追加 */
    }

    fclose(fp);

    for (u = 0; u < N; u++) { /* 配列の初期化 */
        color[u] = 0; /* 白色 (未発見) */
        p[u] = -1; /* 親を未定義に */
    }

    time = 0;

    for (u = 0; u < N; u++) {
        if (color[u] == 0) {
            traverse(u);
        }
    }

    printf("Depth-First Search Results:\n");
    for (u = 0; u < N; u++) {
        printf("vertex %d: d[%d] = %d, f[%d] = %d, p[%d] = %d\n", u, u, d[u], u, f[u], u, p[u]);
    }

    return 0;
}
