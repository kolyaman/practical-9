#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
int pos;
int step_len;
int step_count;
struct QueueNode* next;
} QueueNode;

QueueNode* createQueueNode(int pos, int step_len, int step_count) {
QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
newNode->pos = pos;
newNode->step_len = step_len;
newNode->step_count = step_count;
newNode->next = NULL;
return newNode;
}

void enqueue(QueueNode** front, QueueNode** rear, int pos, int step_len, int step_count) {
QueueNode* newNode = createQueueNode(pos, step_len, step_count);
if (*rear == NULL) {
    *front = *rear = newNode;
} else {
    (*rear)->next = newNode;
    *rear = newNode;
}
}

QueueNode* dequeue(QueueNode** front) {
if (*front == NULL) return NULL;
QueueNode* temp = *front;
*front = (*front)->next;
return temp;
}

int calculateMinSteps(int start, int target) {
if (start == target) return 0;

QueueNode* front = NULL;
QueueNode* rear = NULL;
enqueue(&front, &rear, start, 1, 1);

while (front != NULL) {
    QueueNode* current = dequeue(&front);

    int pos = current->pos;
    int step_len = current->step_len;
    int step_count = current->step_count;
    free(current);

    if (pos + step_len == target || pos + step_len + 1 == target) {
        return step_count + 1;
    }

    if (pos + step_len - 1 >= start) {
        enqueue(&rear, &rear, pos + step_len - 1, step_len - 1, step_count + 1);
    }
    enqueue(&rear, &rear, pos + step_len, step_len, step_count + 1);
    enqueue(&rear, &rear, pos + step_len + 1, step_len + 1, step_count + 1);
}

return -1;
}

int main() {
int start, target;
scanf("%d %d", &start, &target);
printf("%d\n", calculateMinSteps(start, target));
return 0;
}
