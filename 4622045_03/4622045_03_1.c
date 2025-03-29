#include <stdio.h>
#include <stdlib.h>

void selectionSort(int data[], int N) {
    int i, j, min_idx;

    for (i = 0; i < N - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < N; j++) {
            if (data[j] < data[min_idx]) {
                min_idx = j;
            }
        }
        // Swap data[i] and data[min_idx]
        int temp = data[i];
        data[i] = data[min_idx];
        data[min_idx] = temp;
    }
}

int main() {
    FILE *fp;
    int N, i;
    int *data;

    // ファイルを読み込みモードでオープン
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("ファイルが開けませんでした。\n");
        return 1;
    }

    // Nを読み込む
    fscanf(fp, "%d", &N);

    // 配列を動的に確保
    data = (int *)malloc(N * sizeof(int));

    // 整数値を読み込み配列に格納
    for (i = 0; i < N; i++) {
        fscanf(fp, "%d", &data[i]);
    }

    // ファイルをクローズ
    fclose(fp);

    // 選択ソートを実行
    selectionSort(data, N);

    // ソートされた配列を出力
    for (i = 0; i < N; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // メモリを解放
    free(data);

    return 0;
}
