#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50 /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */

int main(void) {
    int N, M; /* 頂点数，辺数 */
    int Lmat[maxN+1][maxN+1]; /* 重み行列を表す変数 */
    int d[maxN+1][maxN+1][maxN+1]; /* 配列 d の宣言 */
    int u, v, len, i, j, k; /* 必要な変数を宣言 */
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */
    
    printf("input filename: "); /* ファイル名の入力を要求 */
    scanf("%s", fname); /* ファイル名を読み込む */
    
    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */
    
    fscanf(fp, "%d %d", &N, &M); /* ファイルから N, M を読み込む */
    if (N > maxN) { /* N > maxN のとき */
        printf("N > maxN, redefine maxN\n"); /* maxN の値を補正する必要の警告 */
        return 1;
    }
    
    for (u = 1; u <= N; u++) { /* 重み行列の初期化 */
        for (v = 1; v <= N; v++) {
            if (u == v) {
                Lmat[u][v] = 0;
            } else {
                Lmat[u][v] = inf;
            }
        }
    }
    
    for (i = 0; i < M; i++) {
        fscanf(fp, "%d %d %d", &u, &v, &len); /* 順番に辺の両端 u, vと長さを読み込む */
        Lmat[u][v] = len;
    }
    
    fclose(fp);
    
    for (u = 1; u <= N; u++) { /* d[0][u][v] の計算 */
        for (v = 1; v <= N; v++) {
            d[0][u][v] = Lmat[u][v];
        }
    }
    
    printf("k = 0:\n"); /* d[0][u][v] の出力 */
    for (u = 1; u <= N; u++) {
        printf(" %2d:", u);
        if (u > 1) {
            for (v = 1; v < u; v++) {
                printf(" "); /* 見やすいように必要な空白を出力する */
            }
        }
        for (v = u; v <= N; v++) {
            if (d[0][u][v] != inf) {
                printf(" %2d", d[0][u][v]);
            } else {
                printf(" --");
            }
        }
        printf("\n");
    }
    
    for (k = 1; k <= N; k++) { /* 主要部分 */
        for (u = 1; u <= N; u++) {
            for (v = 1; v <= N; v++) {
                d[k][u][v] = (d[k-1][u][v] < d[k-1][u][k] + d[k-1][k][v]) ? d[k-1][u][v] : d[k-1][u][k] + d[k-1][k][v];
            }
        }
        
        printf("k = %d:\n", k); /* 各ステップの結果を出力 */
        for (u = 1; u <= N; u++) {
            printf(" %2d:", u);
            if (u > 1) {
                for (v = 1; v < u; v++) {
                    printf(" ");
                }
            }
            for (v = u; v <= N; v++) {
                if (d[k][u][v] != inf) {
                    printf(" %2d", d[k][u][v]);
                } else {
                    printf(" --");
                }
            }
            printf("\n");
        }
    }
    
    return 0;
}
