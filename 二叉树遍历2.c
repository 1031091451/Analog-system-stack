/*************************************************************************
	> File Name: 二叉树遍历２.c
	> Author: 史桢港 
	> Mail: 1031091451@qq.com
	> Created Time: 2018年02月28日 星期三 11时37分26秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "any_stack2.h"

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int data) {
    Node *p = (Node *)malloc(sizeof(Node) * 1);
    p->data = data;
    p->lchild = p->rchild=  NULL;
    return p;
}

Node *init_binary_tree() {
    Node *root = getNewNode(1);
    root->lchild = getNewNode(3);
    root->rchild = getNewNode(6);
    root->lchild->rchild = getNewNode(9);
    root->rchild->rchild = getNewNode(11);
    root->rchild->lchild = getNewNode(14);
    root->lchild->rchild->lchild = getNewNode(17);
    return root;
}

void __pre_order(Node *root) {
    // status = 0
    if (root == NULL) return ; // status = 100
    printf("%d\n", root->data); // status = 1
    __pre_order(root->lchild); // status = 2
    __pre_order(root->rchild); // status = 3
    return ; // status = 100
}

typedef struct PreOrderArgs {
    Node *root;
    int status;
} PreOrderArgs;

PreOrderArgs *getNewArgs(Node *root) {
    PreOrderArgs *p = (PreOrderArgs *)malloc(sizeof(PreOrderArgs) * 1);
    p->root = root;
    p->status = 0;
    return p;
}

void pre_order(Node *root) {
    Stack *s = init_stack(100, PreOrderArgs);
    PreOrderArgs *temp_args = getNewArgs(root), *p_args;
    push_stack(s, temp_args);
    while (!empty_stack(s)) {
        p_args = top_stack(s, PreOrderArgs);
        switch (p_args->status) {
            case 0: {
                if (p_args->root == NULL) {
                    p_args->status = 100;
                } else {
                    p_args->status = 1;
                }
            } break;
            case 1: {
                printf("%d\n", p_args->root->data);
                p_args->status = 2;
            } break;
            case 2: {
                temp_args->root = p_args->root->lchild;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 3;
            } break;
            case 3: {
                temp_args->root = p_args->root->rchild;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 100;
            } break;
            case 100: {
                pop_stack(s);
            } break;
        }
    }
    free(temp_args);
    clear_stack(s);
    return ;
}

void in_order(Node *root) {
    //status = 0;
    if (root == NULL) return ; //status = 100
    in_order(root->lchild); //status = 1
    printf("%d\n", root->data); //status = 2
    in_order(root->rchild); //status = 3
    return ;
}

void __in_order(Node *root) {
    Stack *s = init_stack(100, PreOrderArgs);
    PreOrderArgs *temp_args = getNewArgs(root), *p_args;
    push_stack(s, temp_args);
    while (!empty_stack(s)) {
        p_args = top_stack(s, PreOrderArgs);
        switch(p_args->status) {
            case 0: {
                if (p_args->root == NULL) {
                    p_args->status = 100;
                } else {
                    p_args->status = 1;
                }
            } break;
            case 1: {
                temp_args->root = p_args->root->lchild;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 2;
            } break;
            case 2: {
                printf("%d\n", p_args->root->data);
                p_args->status = 3;
            } break;
            case 3: {
                temp_args->root = p_args->root->rchild;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 100;
            } break;
            case 100 : {
                pop_stack(s);
            } break;

        }
    }
    free(temp_args);
    clear_stack(s);
    return ;
}

void out_order(Node *root) {
    //status = 0;
    if (root == NULL) return ; //status = 100;
    out_order(root->lchild); //status = 1;
    out_order(root->rchild); //status = 2;
    printf("%d\n", root->data); // status = 3;
    return ; //status = 100;
}

void __out_order(Node *root) {
    Stack *s = init_stack(100, PreOrderArgs);
    PreOrderArgs *temp_args = getNewArgs(root), *p_args;
    push_stack(s, temp_args);
    while (!empty_stack(s)) {
        p_args = top_stack(s, PreOrderArgs);
        switch (p_args->status) {
            case 0: {
                if (p_args->root == NULL) {
                    p_args->status = 100;
                } else {
                    p_args->status = 1;
                }
            } break;
            case 1: {
                temp_args->root = p_args->root->lchild;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 2;
            } break;
            case 2: {
                temp_args->root = p_args->root->rchild;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 3;
            } break;
            case 3: {
                printf("%d\n", p_args->root->data);
                p_args->status = 100;
            } break;
            case 100: {
                pop_stack(s);
            } break;
        }
    }
    free(temp_args);
    clear_stack(s);
    return ;
}

int main() {
    Node *root = init_binary_tree();
    pre_order(root);
    printf("\n");
    __pre_order(root);
    printf("\n");
    in_order(root);
    printf("\n");
    __in_order(root);
    printf("\n");

    out_order(root);
    printf("\n");
    __out_order(root);

    return 0;
}
