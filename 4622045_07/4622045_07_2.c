#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define maxN 50 /* 扱えるデータ数の最大値 */
#define maxM 20 /* 使えるバケット数の最大値 */

struct cell {
    int key;
    int next;
};

void bucket_sort(int *A, int n, int l, int u, int m); /* 関数 bucket_sort の宣言 */
void radix_sort_bucket(int *A, int n, int k, int d);  /* 関数 radix_sort_bucket の宣言 */

int main(void) {
    int Data[maxN]; /* 入力数値の配列，数値数は maxN まで */
    int N, l, u, m, k, d; /* 数値の数 N，値の下界 l, 上界 u, バケット数 m, k 進数, 桁数 d */
    int i, j, option;
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */

    printf("Choose option (1: bucket sort, 2: radix sort): ");
    scanf("%d", &option);

    printf("input filename: "); /* ファイル名の入力を要求 */
    scanf("%s", fname);
    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */

    if (option == 1) {
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
    } else if (option == 2) {
        fscanf(fp, "%d %d %d", &N, &k, &d); /* N, k, d をファイルから読み込む */

        if (N > maxN) {
            printf("N is too large, setting N = %d\n", maxN);
            N = maxN;
        }

        int validN = 0;
        for (i = 0; i < N; i++) { /* 整数をファイルから読み込む */
            int temp;
            fscanf(fp, "%d", &temp);
            if (temp < pow(k, d)) {
                Data[validN++] = temp;
            } else {
                printf("Value %d exceeds the maximum value for %d-digit base-%d numbers and will be ignored.\n", temp, d, k);
            }
        }
        fclose(fp); /* 開いたファイルを閉じる */
        
        printf("Original data:\n");
        for (i = 0; i < validN; i++) {
            printf("%d ", Data[i]);
        }
        printf("\n");

        radix_sort_bucket(Data, validN, k, d); /* radix_sort を呼び出し */

        printf("Sorted data:\n");
        for (i = 0; i < validN; i++) {
            printf("%d ", Data[i]);
        }
        printf("\n");
    } else {
        printf("Invalid option.\n");
        fclose(fp);
        return 1;
    }

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

void radix_sort_bucket(int *A, int n, int k, int d) {
    int B[maxM][maxN]; /* バケットを表す2次元配列 */
    int count[maxM];   /* バケット内の要素数を記録 */
    int i, j, p, index, divisor = 1;

    for (p = 0; p < d; p++) {
        for (i = 0; i < k; i++) { /* バケットを初期化 */
            count[i] = 0;
        }

        for (i = 0; i < n; i++) {
            index = (A[i] / divisor) % k;
            B[index][count[index]++] = A[i];
        }

        int idx = 0;
        for (i = 0; i < k; i++) {
            for (j = 0; j < count[i]; j++) {
                A[idx++] = B[i][j];
            }
        }

        divisor *= k; /* 次の桁に移動 */
    }
}
