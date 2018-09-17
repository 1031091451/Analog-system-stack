/*************************************************************************
	> File Name: 快排转非递归.c
	> Author: 史桢港 
	> Mail: 1031091451@qq.com
	> Created Time: 2018年02月28日 星期三 13时40分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "any_stack2.h"

#define swap(a, b) {\
    __typeof(a)__temp = (a);\
    (a) = (b);\
    (b) = __temp;\
}

void quick_sort(int *num, int l, int r) {
    //status = 0
    if (r <= l) return ; //status = 100
    int x = l, y = r, z = num[(l + r) >> 1];//status = 1
    do {
        while (num[x] < z) ++x;
        while (num[x] > z) --y;
        if (x <= y) {
            swap(num[x], num[y]);
            ++x, --y;
        }
    } while(x <= y);
    quick_sort(num, l, y); //status = 2
    quick_sort(num, x, r); //status = 3
    return ; //status = 100
}

typedef struct quickArgs {
    int *data;
    int left, right, x, status, y;
} quickArgs;

quickArgs *getNewArgs(int *num, int l, int r) {
    quickArgs *p = (quickArgs *)malloc(sizeof(quickArgs));
    p->data = num;
    p->left = l;
    p->right = r;
    p->x = 0;
    p->y = 0;
    p->status = 0;
    return p;
}

void __quick_sort(int *num, int l, int r) {
    Stack *s = init_stack(100, quickArgs);
    quickArgs *temp_arg = getNewArgs(num, l, r), *p_arg;
    push_stack(s, temp_arg);
    while (!empty_stack(s)) {
        p_arg = top_stack(s, quickArgs);
        switch (p_arg->status) {
            case 0: {
                if (p_arg->right <= p_arg->left) {
                    p_arg->status = 100;
                } else {
                    p_arg->status = 1;
                }
            } break;
            case 1: {
                int x = p_arg->left, y = p_arg->right, z = p_arg->data[(x + y) >> 1];
                do {
                    while (p_arg->data[x] < z) ++x;
                    while (p_arg->data[y] > z) --y;
                    if (x <= y) {
                        swap(p_arg->data[x], p_arg->data[y]);
                        ++x, --y;
                    }
                } while (x <= y);
                p_arg->x = y;
                p_arg->y = x;
                p_arg->status = 2;
            } break;
            case 2: {
                temp_arg = getNewArgs(num, p_arg->left, p_arg->x);
                push_stack(s, temp_arg);
                free(temp_arg);
                p_arg->status = 3;
            } break;
            case 3: {
                temp_arg = getNewArgs(num, p_arg->y, p_arg->right);
                push_stack(s, temp_arg);
                free(temp_arg);
                p_arg->status = 100;
            } break;
            case 100 :{
                pop_stack(s);
            } break;
        }
    }
    clear_stack(s);
}

int main() {
    int n;
    scanf("%d", &n);
    int *num = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < 100; ++i) {
        scanf("%d", &num[i]);
    }
    __quick_sort(num, 0, 99);
    for (int i = 0; i < 100; ++i) {
        printf("%d\n", num[i]);
    }
    return 0;
}
