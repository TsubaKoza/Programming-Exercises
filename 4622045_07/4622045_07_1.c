#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50 /* 扱えるデータ数の最大値 */
#define maxM 20 /* 使えるバケット数の最大値 */

struct cell {
    int key;
    int next;
};

void bucket_sort(int *A, int n, int l, int u, int m); /* 関数 bucket_sort の宣言 */

int main(void) {
    int Data[maxN]; /* 入力数値の配列，数値数は maxN まで */
    int N, l, u, m; /* 数値の数 N，値の下界 l, 上界 u, バケット数 m */
    int i, j;
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */

    printf("input filename: "); /* ファイル名の入力を要求 */
    scanf("%s", fname);
    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */

    fscanf(fp, "%d %d %d %d", &N, &l, &u, &m); /* N, l, u, m をファイルから読み込む */

    if (N > maxN) {
        printf("N is too large, setting N = %d\n", maxN);
        N = maxN;
    }

    int validN = 0;
    for (i = 0; i < N; i++) { /* 整数をファイルから読み込む */
        int temp;
        fscanf(fp, "%d", &temp);
        if (temp >= l && temp <= u) {
            Data[validN++] = temp;
        } else {
            printf("Value %d is out of range [%d, %d] and will be ignored.\n", temp, l, u);
        }
    }
    fclose(fp); /* 開いたファイルを閉じる */
    
    if (m > maxM) {
        printf("number of buckets m is too large, setting m = %d\n", maxM);
        m = maxM;
    }

    printf("Original data:\n");
    for (i = 0; i < validN; i++) {
        printf("%d ", Data[i]);
    }
    printf("\n");

    bucket_sort(Data, validN, l, u, m); /* bucket_sort を呼び出し */

    printf("Sorted data:\n");
    for (i = 0; i < validN; i++) {
        printf("%d ", Data[i]);
    }
    printf("\n");

    return 0;
}

void bucket_sort(int *A, int n, int l, int u, int m) {
    struct cell List[maxN]; /* リストを格納する配列 */
    int B[maxM]; /* バケットを表す配列 */
    int i, j;

    for (i = 0; i < n; i++) { /* あらかじめ n 個の数値をリストに格納 */
        List[i].key = A[i]; /* next の値を初期化 */
        List[i].next = -1;
    }

    for (j = 0; j < m; j++) { /* バケットを初期化 */
        B[j] = -1;
    }

    /* 主要部分 */
    for (i = 0; i < n; i++) {
        int index = (List[i].key - l) * m / (u - l + 1);
        if (B[index] == -1) {
            B[index] = i;
        } else {
            int k = B[index];
            while (List[k].next != -1) {
                k = List[k].next;
            }
            List[k].next = i;
        }
    }

    /* ソートしたデータを A に格納 */
    int idx = 0;
    for (j = 0; j < m; j++) {
        if (B[j] != -1) {
            int k = B[j];
            while (k != -1) {
                A[idx++] = List[k].key;
                k = List[k].next;
            }
        }
    }
}
