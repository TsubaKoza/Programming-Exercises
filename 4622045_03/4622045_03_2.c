#include <stdio.h>
#include <stdlib.h>

// セルの構造体の定義
struct Node {
    int data;
    struct Node *next;
};

// セルの作成
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("メモリの割り当てエラー\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// リストの先頭に要素を挿入
void insertFront(struct Node **head, int value) {
    struct Node *newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

// リストの先頭から最小値のセルを見つけて削除し、その値を返す
int deleteMin(struct Node **head) {
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *minNode = *head;
    struct Node *prevMinNode = NULL;

    while (current != NULL) {
        if (current->data < minNode->data) {
            minNode = current;
            prevMinNode = prev;
        }
        prev = current;
        current = current->next;
    }

    if (prevMinNode != NULL) {
        prevMinNode->next = minNode->next;
    } else {
        *head = minNode->next;
    }

    int minValue = minNode->data;
    free(minNode);
    return minValue;
}

// 選択ソートの実装
void selectionSort(struct Node **head, int N) {
    struct Node *sortedList = NULL;
    int i;

    for (i = 0; i < N; i++) {
        int minValue = deleteMin(head);
        insertFront(&sortedList, minValue);
    }

    *head = sortedList;
}

// リストの内容を表示
void displayList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    FILE *fp;
    int N, value, i;
    struct Node *head = NULL;

    // ファイルを読み込みモードでオープン
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("ファイルが開けませんでした。\n");
        return 1;
    }

    // Nを読み込む
    fscanf(fp, "%d", &N);

    // 整数値を読み込みリストに挿入
    for (i = 0; i < N; i++) {
        fscanf(fp, "%d", &value);
        insertFront(&head, value);
    }

    // ファイルをクローズ
    fclose(fp);

    // 選択ソートを実行
    selectionSort(&head, N);

    // ソートされたリストを表示
    printf("Sorted list: ");
    displayList(head);

    // メモリを解放
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
