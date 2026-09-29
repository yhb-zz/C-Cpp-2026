#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
    struct Node *last;
};

struct Node *generate(int length, int *array) {
    struct Node * p, * last;
    p = (struct Node *)malloc(sizeof(struct Node));
    if (p == NULL) {
        perror("malloc");
    }
    struct Node * head = p;

    for (int i = 0; i < length; i++) {
        (*p).value = array[i];

        if (i != 0){
            (*p).last = last;
        } else {
            (*p).last = NULL;
            last = NULL;
        }

        if (i != length - 1){
            (*p).next = (struct Node *)malloc(sizeof(struct Node));
            if ((*p).next == NULL) {
                perror("malloc");
            }
        } else {
            (*p).next = NULL;
        }
        
        last = p;
        p = (*p).next;
    }

    return head;
}

int check(int value, int num_of_times, struct Node *head) {
    struct Node *p = head;
    int number = 1;
    int times = 0;
    while (p != NULL) {
        if (p->value == value) {
            times++;
            if (times == num_of_times) {
                return number;
            }
        }
        p = p->next;
        number++;
    }
    return -1;
}

struct Node * reverse(struct Node * head) {
    struct Node *p = head;
    struct Node *t, *new_head;
    while (p != NULL) {
        new_head = p;
        t = p->next;
        p->next = p->last;
        p->last = t;
        t = NULL;
        p = p->last;
    }
    return new_head;
}

int main() {

    // 创建一个单向链表
    int arr[16] = {12, 5, 3, 34, 2, 4, 54, 5, 6, 4, 3, 2, 4, 5, 6, 7};
    struct Node *head = generate(16, arr);

    // 遍历该链表，依次现实各节点的 value
    struct Node *p = head;
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
    p = NULL;

    // 将该链表所有节点反序
    head = reverse(head);
    p = head;
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
    p = NULL;

    // 在该链表中查找第一个值为 5 的节点, 如果找到则返回该节点的序号, 否则返回-1
    printf("查询值为 5 的节点的结果: %d\n", check(5, 1, head));

    // 查找其他值为 5 的节点，返回值同上
    printf("查询第二个值为 5 的节点的结果: %d\n", check(5, 2, head));
    printf("查询第二个值为 5 的节点的结果: %d\n", check(5, 3, head));
    printf("查询第二个值为 5 的节点的结果: %d\n", check(5, 4, head));
}
