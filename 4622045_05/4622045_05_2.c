#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50

int parent(int i) {
    return (i - 1) / 2;
}

void heapify(int *H, int *A, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && A[l] > A[largest]) {
        largest = l;
    }

    if (r < n && A[r] > A[largest]) {
        largest = r;
    }

    if (largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        heapify(H, A, n, largest);
    }
}

void buildHeap(int *H, int *A, int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(H, A, n, i);
    }
}

void heapsort(int *H, int *A, int n) {
    buildHeap(H, A, n);
    int i;
    for (i = n - 1; i > 0; i--) {
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        heapify(H, A, i, 0);
    }
}

void increaseKey(int *H, int i, int a) {
    if (a < H[i]) {
        printf("New key is smaller than current key.\n");
        return;
    }
    H[i] = a;
    while (i > 0 && H[parent(i)] < H[i]) {
        int temp = H[i];
        H[i] = H[parent(i)];
        H[parent(i)] = temp;
        i = parent(i);
    }
}

int main(void) {
    int Data[maxN];
    int Heap[maxN];
    int N, i;
    char fname[100]; // ファイル名を格納する配列
    FILE *fp;

    printf("Input filename: ");
    fgets(fname, sizeof(fname), stdin);
    fname[strlen(fname) - 1] = '\0';
    fp = fopen(fname, "r");
    fflush(stdin);


    fscanf(fp, "%d", &N);
    if (N > maxN) {
        printf("N is too large, setting N = %d\n", maxN);
        N = maxN;
    }
    printf("aa");

    for (i = 0; i < N; i++) {
        fscanf(fp, "%d", &Data[i]);
    }
    fclose(fp);

    printf("Original data:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", Data[i]);
    }
    printf("\n");

    heapsort(Heap, Data, N);

    printf("Sorted data:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", Data[i]);
    }
    printf("\n");

    return 0;
}
