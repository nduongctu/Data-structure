﻿#include <stdio.h>
#include <stdlib.h>

struct Node {
    int Key;
    struct Node* Left, * Right;
    int Height;
};
typedef struct Node* Tree;

int deleteMax(Tree* pT) {
    if ((*pT)->Right == NULL) {
        int key = (*pT)->Key;
        *pT = (*pT)->Left;
        return key;
    }
    return deleteMax(&((*pT)->Right));
}
void deleteNode(int x, Tree* pT) {
    if (*pT == NULL)
        return;
    if ((*pT)->Key != x) {
        if ((*pT)->Key > x)
            return deleteNode(x, &((*pT)->Left));
        return deleteNode(x, &((*pT)->Right));
    }
    if ((*pT)->Left == NULL || (*pT)->Right == NULL) {
        *pT = NULL;
        return;
    }
    if ((*pT)->Left == NULL) {
        *pT = (*pT)->Right;
        return;
    }
    if ((*pT)->Left == NULL) {
        *pT = (*pT)->Left;
        return;
    }
    (*pT)->Key = deleteMax(&((*pT)->Left));
}

//Hàm trả về con trỏ của nút đứng trước nút có khóa x cho trước trong phép duyệt trung tự (giả sử x chắc chắn có trong cây T)
Tree leftest(Tree root){
    if (root == NULL)
        return NULL;
    if (root->Left == NULL)
        return root;
    return leftest(root->Left);
}
Tree rightest(Tree root){
    if (root == NULL)
        return NULL;

    if (root->Right == NULL)
        return root;
    return rightest(root->Right);
}
Tree getPrevious(int x, Tree root){
    if (root == NULL)
        return NULL;
    if (root->Key == x)
        if (root->Left != NULL)
            return rightest(root->Left);
    Tree lrest = leftest(root->Right);
    if (lrest != NULL)
        if (lrest->Key == x)
            return root;
    if (x < root->Key)
        return getPrevious(x, root->Left);
    return getPrevious(x, root->Right);
}

//Hàm tính chiều cao của nút có khóa x trong cây T
int getHeight(Tree T){
    if (T == NULL)
        return -1;
    int lh = getHeight(T->Left);
    int rh = getHeight(T->Right);

    return 1 + (lh > rh ? lh : rh);
}
int hNode(int x, Tree root){
    if (root == NULL)
        return getHeight(root);
    if (root->Key == x)
        return getHeight(root);
    if (x < root->Key)
        return hNode(x, root->Left);
    return hNode(x, root->Right);
}

Tree searchNode(int x, Tree root){
    if (root == NULL)
        return NULL;
    if (x < root->Key)
        return searchNode(x, root->Left);
    if (x > root->Key)
        return searchNode(x, root->Right);
    return root;
}

void insertNode(int x, Tree* pRoot){
    if (*pRoot == NULL){
        (*pRoot) = (Tree)malloc(sizeof(struct Node));
        (*pRoot)->Left = NULL;
        (*pRoot)->Right = NULL;
        (*pRoot)->Key = x;
        return;
    }
    if (x == (*pRoot)->Key)
        return;
    if (x < (*pRoot)->Key)
        return insertNode(x, &((*pRoot)->Left));
    return insertNode(x, &((*pRoot)->Right));
}
//Hàm tìm kiếm nút cha của nút có khóa x trong cây tìm kiếm nhị phân
Tree getParent(int x, Tree root){
    if (root == NULL)
        return NULL;
    if (x < root->Key){
        if (root->Left == NULL)
            return NULL;
        if (root->Left->Key == x)
            return root;
        return getParent(x, root->Left);
    }
    if (root->Right == NULL)
        return NULL;
    if (root->Right->Key == x)
        return root;
    return getParent(x, root->Right);
}
//Hàm liệt kê (in) các giá trị khóa trên đường đi của việc tìm kiếm một khóa x trong cây tìm kiếm nhị phân
void printPath(int x, Tree root){
    if (root == NULL){
        printf("-> Khong thay");
        return;
    }
    printf("%d ", root->Key);
    if (root->Key == x){
        printf("-> Tim thay");
        return;
    }
    if (x < root->Key)
        return printPath(x, root->Left);
    return printPath(x, root->Right);
}
//Tìm kiếm nút anh em ruột phải của nút có khóa x trong cây tìm kiếm nhị phân
Tree rightSibling(int x, Tree root){
    if (root == NULL || root->Left == NULL)
        return NULL;
    if (root->Left->Key == x)
        return root->Right;
    if (x < root->Key)
        return rightSibling(x, root->Left);
    return rightSibling(x, root->Right);
}