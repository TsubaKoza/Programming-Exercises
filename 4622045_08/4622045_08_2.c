#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50

void mergesort(int *A, int left, int right);
void merge(int *A, int left, int mid, int right);

int main(void) {
    int Data[maxN]; /* 入力数値の配列 Data */
    int N; /* 数値の数 N */
    int i;
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */

    printf("input filename: "); /* ファイル名の入力を要求 */
    scanf("%s", fname); /* ファイル名を読み込む */

    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */

    fscanf(fp, "%d", &N); /* ファイルからデータを読み込む */
    if (N > maxN) {
        printf("Too many data, number of data must not exceed %d\n", maxN);
        printf("Sorting first %d values\n", maxN);
        N = maxN;
    }

    for (i = 0; i < N; i++) {
        fscanf(fp, "%d", &Data[i]);
    }
    fclose(fp); /* 開いたファイルを閉じる */

    printf("Before sorting:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", Data[i]);
    }
    printf("\n");

    mergesort(Data, 0, N - 1); /* mergesort を呼び出し */

    printf("After sorting:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", Data[i]);
    }
    printf("\n");

    return 0;
}

void mergesort(int *A, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergesort(A, left, mid);
        mergesort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

void merge(int *A, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}
