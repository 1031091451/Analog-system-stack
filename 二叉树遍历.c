/*************************************************************************
	> File Name: 二叉树遍历.c
	> Author: 史桢港 
	> Mail: 1031091451@qq.com
	> Created Time: 2018年02月28日 星期三 10时25分53秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "any_stack.h"

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

Node *get_new_node(int data) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *init_tree() {
    Node *root = get_new_node(1);
    root->lchild = get_new_node(3);
    root->rchild = get_new_node(6);
    root->lchild->rchild = get_new_node(9);
    root->rchild->rchild = get_new_node(11);
    root->rchild->lchild = get_new_node(14);
    root->lchild->rchild->lchild = get_new_node(17);
    return root;
}

void pre_order(Node *root) {
    //status 0;
    if (root == NULL) return ; //status 100
    printf("%d\n", root->data); // status 1
    pre_order(root->lchild); //status 2
    pre_order(root->rchild); //status 3 
    return ;//status 100
}

typedef struct PreOrderArgs {
    Node *root;
    int status;
} PreOrderArgs;

PreOrderArgs *get_new_args (Node *root) {
    PreOrderArgs *p = (PreOrderArgs *)malloc(sizeof(PreOrderArgs));
    p->root  = root;
    p->status = 0;
    return p;
}

void preOrder(Node *root) {
    Stack *s = init_stack(100, PreOrderArgs);
    PreOrderArgs *temp_args = get_new_args(root), *p_args;
    push_stack(s, temp_args);
    push_stack(s, get_new_args(root));
    while (!empty_stack(s)) {
        p_args = top_stack(s, PreOrderArgs);
        switch (top_stack(s, PreOrderArgs)->status) {
            case 0: {
                if (p_args == NULL) {
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
            } break; //　模拟函数压栈
            case 3: {
                temp_args->root = p_args->root->rchild;
                temp_args->status = 0;
                push_stack(s, temp_args);
                p_args->status = 100;

            }
            case 100: {
                pop_stack(s);
            }
        }
    }
    free(temp_args);
    clear(s);

}

void inOrder(Node *root) {
    if (root == NULL) return ;
    inOrder(root->lchild);
    printf("%d\n", root->data);
    inOrder(root->rchild);
}

void outOrder(Node *root) {
    if (root == NULL) return ;
    outOrder(root->lchild);
    outOrder(root->rchild);
    printf("%d\n", root->data);
}



int main() {
    Node *root = init_tree();
    pre_order(root);
    printf("\n");
    preOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
    outOrder(root);
    
    return 0;
}
