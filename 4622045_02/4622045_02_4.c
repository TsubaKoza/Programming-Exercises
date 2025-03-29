#include <stdio.h>
#include <stdlib.h>

int main () {
    int n;
    printf("受験者の人数を入力してください: ");
    scanf("%d", &n);

    // 点数を保存するための動的配列の確保
    int *scores = (int *)malloc(n * sizeof(int));
    if (scores == NULL) {
        printf("メモリの国保に失敗しました。\n");
        return 1;
    }

    printf("各受験者の点数を入力してください:\n");
    for (int i = 0; i < n; i++)
    {
        printf("受験者%dの点数:", i + 1);
        scanf("%d", &scores[i]);
    }
    
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += scores[i];
    }
    
    double average = (double)sum / n;

    printf("\n受験者の点数一覧:\n");
    for (int i = 0; i < n; i++)
    {
        printf("受験者%dの点数: %d\n", i+1, scores[i]);
    }
    
    printf("\n受験者の平均点: %d\n", average);

    // 度的配列の解放
    free(scores);

    return 0;
}