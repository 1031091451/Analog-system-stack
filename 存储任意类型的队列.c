/*************************************************************************
	> File Name: Queue.c
	> Author: 史桢港 
	> Mail: 1031091451@qq.com
	> Created Time: 2018年01月16日 星期二 14时26分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0

//#define DEFAULTARG(n, x) ((#n[0] ? n + 0: x)) // 返回默认参数
#define init(T)  (__init(sizeof(T), 10))
#define push(q,val) (__push(q, &val))
#define front(q, T) (*((T *)(__front(q))))

typedef struct Queue {
    void *data;
    int data_size;
    int length, tail, head;
} Queue;

Queue *__init(int, int);
int __push(Queue *, void *);
int pop(Queue *);
int empty(Queue *);
int expand(Queue *);
void clear(Queue *);
//void output(Queue *);
void *__front(Queue *);


int main() {
    Queue *q = init(int);
    int op, val;
    while(~scanf("%d", &op)) {
        switch (op) {
            case 1:
                scanf("%d", &val);
                push(q, val);
                break;
            case 2:
                pop(q);
                break;
            case 3:
                printf("front :%d\n",front(q, int));
                break;
            default :
                fprintf(stderr, "operator error\n");
                break;
        }
    //output(q);
    }
    clear(q);

    return 0;
}


Queue *__init(int data_size, int n) {
    Queue *p = (Queue *)malloc(sizeof(Queue) * 1);
    p->data = malloc(sizeof(int) * n);
    p->length = n;
    p->head = p->tail = 0;
    p->data_size = data_size;
    return p;
}

int __push(Queue *q, void *val_p) {
    if (q->tail == q->length) {
        if (expand(q) == 0)
            return ERROR;
    }
    char *data = (char *)(q->data);
    memcpy(data + q->tail * q->data_size, val_p, q->data_size); //第一个参数为目的地址，第二个为源地址，第三个为拷贝的大小
    q->tail++;
    return OK;
}
int expand(Queue *q) {
    void *temp_data = (int *)realloc(q->data, q->data_size * q->length * 2);
    if (temp_data == NULL) return ERROR;
    q->data = temp_data;
    q->length *= 2;
    return OK;
}

int empty(Queue *q) {
    return q->head == q->tail;
}

int pop(Queue *q) {
    if (empty(q)) return ERROR;
    q->head++;
    return OK;

}

void clear(Queue *q) {
    if (q == NULL) return  ;
    free(q->data);
    free(q);
    return ;
}

void *__front(Queue *q) {
    if (empty(q)) return NULL;
    return (char *)(q->data) + q->data_size * q->head;
}

/*void output(Queue *q) {
    printf("Queue is :");
    for (int i = q->head; i < q->tail; ++i) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
    return ;
}*/
