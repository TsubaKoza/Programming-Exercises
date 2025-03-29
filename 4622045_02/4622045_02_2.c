#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N; 
    printf("生成する整数の個数を入力してください: ");
    scanf("%d", &N);

    srand(time(NULL));

    // ファイルの準備
    FILE *file = fopen("random_integers.txt", "w");
    if (file == NULL) {
        printf("ファイルを閉じられませんでした。\n");
        return 1;
    }

    fprintf(file, "%d\n", N); // 整数の個数をファイルに書き込む
    for (int i = 0; i < N; i++) {
        int random_integer = rand() % 100 + 1; // 1以上100以下の整数の生成
        fprintf(file, "%d ", random_integer); // ファイルに書き込む
    }

    // ファイルを閉じる
    fclose(file);

    printf("ファイルに整数を出力しました。\n");

    return 0;
}
