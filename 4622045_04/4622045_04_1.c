#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxN 50

struct node {
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
};

void inorder_tree_walk(struct node *x);
struct node *tree_search(struct node *T, int a);
struct node *tree_minimum(struct node *x);
struct node *tree_maximum(struct node *x);
struct node *tree_insert(struct node *T, struct node *x);
struct node *tree_delete(struct node *T, struct node *z);

int main(void) {
    struct node *Tree = NULL;
    struct node *x, *y, *z;
    int N;
    int Data[maxN];
    char fname[128];
    FILE *fp;

    printf("Enter filename: ");
    scanf("%s", fname);
    
    fp = fopen(fname, "r");

    fscanf(fp, "%d", &N);
    if (N > maxN) {
        printf("N is too large, setting N = %d\n", maxN);
        N = maxN;
    }

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%d", &Data[i]);
    }
    fclose(fp);

    for (int i = 0; i < N; i++) {
        x = (struct node *)malloc(sizeof(struct node));
        x->key = Data[i];
        x->parent = x->left = x->right = NULL;
        Tree = tree_insert(Tree, x);
        printf("After inserting %d:\n", Data[i]);
        inorder_tree_walk(Tree);
        printf("\n");
        printf("Minimum key: %d\n", tree_minimum(Tree)->key);
        printf("Maximum key: %d\n", tree_maximum(Tree)->key);
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        z = tree_search(Tree, Data[i]);
        if (z != NULL) {
            printf("Deleting %d:\n", Data[i]);
            Tree = tree_delete(Tree, z);
            inorder_tree_walk(Tree);
            printf("\n");
            printf("Minimum key: %d\n", tree_minimum(Tree)->key);
            printf("Maximum key: %d\n", tree_maximum(Tree)->key);
            printf("\n");
        }
    }

    return 0;
}

void inorder_tree_walk(struct node *x) {
    if (x != NULL) {
        inorder_tree_walk(x->left);
        printf("%d ", x->key);
        inorder_tree_walk(x->right);
    }
}

struct node *tree_search(struct node *T, int a) {
    while (T != NULL && a != T->key) {
        if (a < T->key) {
            T = T->left;
        } else {
            T = T->right;
        }
    }
    return T;
}

struct node *tree_minimum(struct node *x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

struct node *tree_maximum(struct node *x) {
    while (x->right != NULL) {
        x = x->right;
    }
    return x;
}

struct node *tree_insert(struct node *T, struct node *x) {
    struct node *r, *y, *z;
    r = T;
    y = NULL;
    z = r;

    while (z != NULL) {
        y = z;
        if (x->key < z->key) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    x->parent = y;
    if (y == NULL) {
        r = x; 
    } else if (x->key < y->key) {
        y->left = x;
    } else {
        y->right = x;
    }

    return r;
}

struct node *tree_delete(struct node *T, struct node *z) {
    return NULL;
}
