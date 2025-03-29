#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50 /* 扱う頂点数の最大値，ここでは 50 に設定 */

int main(void) {
    int N, M; /* 頂点数，辺数 */
    int Adj[maxN][maxN]; /* 隣接行列を表す変数 */
    int u, v; /* 辺の両端 */
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
    fclose(fp);

    printf("Adjacency matrix\n"); /* 隣接行列出力 */
    for (u = 0; u < N; u++) {
        for (v = 0; v < N; v++) {
            printf("%d ", Adj[u][v]);
        }
        printf("\n");
    }

    return 0;
}
