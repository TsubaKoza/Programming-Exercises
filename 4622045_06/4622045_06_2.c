#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 20 /* 文字列の最大長さ */
#define m 97 /* ハッシュ表のサイズ */
#define maxN 50 /* 扱う文字列の最大数 */

struct cell {
    char key[W+1];
    unsigned int state : 2; /* 0: 空, 1: 使用中, 2: 削除済み */
};

int hash_val(char *a); /* ハッシュ関数の宣言 */
int hash_search(struct cell *A, char *a); /* 関数 hash_search の宣言 */
void hash_insert(struct cell *A, char *a); /* 関数 hash_insert の宣言 */
void hash_delete(struct cell *A, char *a); /* 関数 hash_delete の宣言 */
void print_hash_table(struct cell *A); /* 関数 print_hash_table の宣言 */

int main(void) {
    struct cell A[m]; /* ハッシュ表を表す配列 */
    int N; /* 数値の数は N */
    int i;
    char word[W+1]; /* ファイルから読み込んだ文字列を格納する変数 */
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */

    for (i = 0; i < m; i++) { /* ハッシュ表の初期化 */
        A[i].state = 0;
    }

    printf("input filename: "); /* ファイル名の入力を要求 */
    scanf("%s", fname);

    fp = fopen(fname, "r"); /* ファイルを読み込みモードで開く */
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &N); /* N をファイルから読み込む */
    if (N > maxN) {
        printf("N is too large, setting N = %d\n", maxN);
        N = maxN;
    }

    for (i = 0; i < N; i++) {
        fscanf(fp, "%s", word); /* 文字列をファイルから読み込み，wordに格納 */
        hash_insert(A, word); /* 挿入手続き */
    }
    fclose(fp); /* 開いたファイルを一旦閉じる */

    printf("After insertion:\n");
    print_hash_table(A);

    fp = fopen(fname, "r"); /* ファイルを再度読み込みモードで開く */
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &N); /* N をファイルから読み込む */
    if (N > maxN) {
        N = maxN;
    }

    for (i = 0; i < N; i++) {
        fscanf(fp, "%s", word); /* 文字列をファイルから読み込み，wordに格納 */
        hash_delete(A, word); /* データを削除する部分 */
    }
    fclose(fp); /* 開いたファイルを閉じる */

    printf("After deletion:\n");
    print_hash_table(A);

    return 0;
}

int hash_val(char *a) { /* 文字列はポインタ渡し */
    int h = 0, i = 0;
    while (a[i] != 0 && i < W) { /* 文字の整数コードの和を計算 */
        h = h + (int)a[i];
        i++;
    }
    h = h % m; /* m で割った余りを取る */
    return h;
}

int hash_search(struct cell *A, char *a) {
    int h = hash_val(a);
    int i = h;
    do {
        if (A[i].state == 0) {
            return -1;
        } else if (A[i].state == 1 && strcmp(A[i].key, a) == 0) {
            return i;
        }
        i = (i + 1) % m;
    } while (i != h);
    return -1;
}

void hash_insert(struct cell *A, char *a) {
    int h = hash_val(a);
    int i = h;
    do {
        if (A[i].state != 1) {
            strcpy(A[i].key, a);
            A[i].state = 1;
            return;
        }
        i = (i + 1) % m;
    } while (i != h);
}

void hash_delete(struct cell *A, char *a) {
    int x = hash_search(A, a);
    if (x != -1) {
        A[x].state = 2;
    }
}

void print_hash_table(struct cell *A) {
    for (int i = 0; i < m; i++) {
        if (A[i].state == 1) {
            printf("A[%d]: %s\n", i, A[i].key);
        }
    }
}
