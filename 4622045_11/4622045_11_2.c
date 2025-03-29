#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50 /* 扱う行列数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */

int main(void) {
    int N; /* 行列数 */
    int p[maxN+1]; /* 行列のサイズを表す変数 */
    int m[maxN+1][maxN+1], s[maxN+1][maxN+1]; /* m[i,j], s[i,j] を格納する変数 */
    int i, j, k, l, q; /* 必要な変数を宣言 */
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */
    
    printf("input filename: "); /* ファイル名の入力を要求 */
    scanf("%s", fname); /* ファイル名を読み込む */
    
    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */
    
    fscanf(fp, "%d", &N); /* ファイルから N を読み込む */
    if (N > maxN) { /* N > maxN のとき */
        printf("N > maxN, redefine maxN\n"); /* maxN の値を補正する必要の警告 */
        return 1;
    }
    
    for (i = 0; i <= N; i++) {
        fscanf(fp, "%d", &p[i]); /* 順番に p[i] の値を読み込む */
    }
    
    fclose(fp);
    
    for (i = 1; i <= N; i++) { /* 行列サイズの出力 */
        printf("matrix %2d:(%d, %d)\n", i, p[i-1], p[i]);
    } /* なくてもよいが，あると結果が見やすい */
    
    for (i = 1; i <= N; i++) {
        m[i][i] = 0; /* 対角要素は 0 */
    }
    
    for (l = 2; l <= N; l++) { /* l はチェーンの長さ */
        for (i = 1; i <= N - l + 1; i++) {
            j = i + l - 1;
            m[i][j] = inf;
            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    
    printf("m-values:\n"); /* m[i,j] の出力 */
    for (i = 1; i <= N; i++) {
        printf(" %2d", i);
        if (i > 1) { /* 見やすいように必要な空白を出力する */
            for (j = 1; j < i; j++) {
                printf(" ");
            }
        }
        for (j = i; j <= N; j++) {
            printf(" %5d", m[i][j]);
        }
        printf("\n");
    } /* 見やすいように桁数を指定する */
    
    printf("s-values:\n"); /* s[i,j] の出力 */
    for (i = 1; i <= N - 1; i++) {
        printf(" %2d", i);
        for (j = 1; j <= i; j++) {
            printf(" ");
        }
        for (j = i + 1; j <= N; j++) {
            printf(" %2d", s[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
