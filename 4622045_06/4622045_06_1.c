#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 20 /* 文字列の最大長さ */
#define m 97 /* ハッシュ表のサイズ */
#define maxN 50 /* 扱う文字列の最大数 */

struct cell {
    char key[W+1];
    int next; /* 構造体 cell の定義 */
};

int allocate_object(struct cell *L, int *f); /* 関数 allocate_object の宣言 */
int chained_hash_search(int *A, struct cell *L, char *a); /* 関数 chained_hash_search の宣言 */
void chained_hash_insert(int *A, struct cell *L, char *a, int *f);
void chained_hash_delete(int *A, struct cell *L, char *a, int *f);
int hash_val(char *a); /* ハッシュ関数の宣言 */
void print_hash_table(int *A, struct cell *L);

int main(void) {
    struct cell List[maxN]; /* リストは cell の配列，数値数は n まで */
    int A[m]; /* ハッシュ表を表す配列 */
    int N; /* 数値の数は N */
    int freeL; /* 空きアドレスのリストの先頭 */
    int i, h;
    char word[W+1]; /* ファイルから読み込んだ文字列を格納する変数 */
    char fname[128]; /* 読み込むファイルの名前 */
    FILE *fp; /* 入力ファイル */

    for (i = 0; i < maxN - 1; i++) { /* allocate_object, free_object のための初期化 */
        List[i].next = i + 1;
    }
    List[maxN-1].next = -1;
    freeL = 0; /* 空きリストの初期化 */
    for (h = 0; h < m; h++) {
        A[h] = -1;
    } /* ハッシュ表の初期化 */

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
        int y = chained_hash_search(A, List, word); /* ハッシュ表の中で文字列 word を探索 */
        if (y == -1) {
            chained_hash_insert(A, List, word, &freeL); /* 挿入手続き */
        }
    }
    fclose(fp); /* 開いたファイルを一旦閉じる */

    /* ハッシュ表のアドレス h が指すリスト A[h] の長さを出力 */
    print_hash_table(A, List);

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
        chained_hash_delete(A, List, word, &freeL); /* データを削除する部分 */
    }
    fclose(fp); /* 開いたファイルを閉じる */

    /* ハッシュ表のアドレス h が指すリスト A[h] の長さを出力 */
    print_hash_table(A, List);

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

int allocate_object(struct cell *L, int *f) {
    if (*f == -1) {
        return -1;
    } else {
        int x = *f;
        *f = L[*f].next;
        return x;
    }
}

int chained_hash_search(int *A, struct cell *L, char *a) {
    int h = hash_val(a);
    int x = A[h];
    while (x != -1 && strcmp(L[x].key, a) != 0) {
        x = L[x].next;
    }
    return x;
}

void chained_hash_insert(int *A, struct cell *L, char *a, int *f) {
    int h = hash_val(a);
    int x = allocate_object(L, f);
    if (x != -1) {
        strcpy(L[x].key, a);
        L[x].next = A[h];
        A[h] = x;
    }
}

void chained_hash_delete(int *A, struct cell *L, char *a, int *f) {
    int h = hash_val(a);
    int x = A[h];
    int prev = -1;
    while (x != -1 && strcmp(L[x].key, a) != 0) {
        prev = x;
        x = L[x].next;
    }
    if (x != -1) {
        if (prev == -1) {
            A[h] = L[x].next;
        } else {
            L[prev].next = L[x].next;
        }
        L[x].next = *f;
        *f = x;
    }
}

void print_hash_table(int *A, struct cell *L) {
    for (int h = 0; h < m; h++) {
        int length = 0;
        int x = A[h];
        while (x != -1) {
            length++;
            x = L[x].next;
        }
        if (length > 0) {
            printf("Hash table[%d] length: %d\n", h, length);
        }
    }
}
