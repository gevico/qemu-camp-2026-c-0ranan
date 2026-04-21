#include <stdio.h>


//   题意：50 人围成圈，从队首开始报数，数到 5 的人出列并输出 淘汰: 编号；前 4 人「出队再入队」到队尾。重复至只剩 1
//   人，输出 最后剩下的人是: 编号。

//   实现要点（循环队列）：
//   • 用 head / tail / count 和模 MAX_PEOPLE 的数组做环形队列入队 1…50。
//   • 每轮：重复 4 次 pop 后 push 回到队尾，第 5 次 pop 为淘汰者并打印。
//   • 队列为空逻辑上不会只剩 0 人；最后 pop 一次得到幸存者（评测期望 19 号）
#define MAX_PEOPLE 50

typedef struct {
	int id;
} People;

typedef struct {
	People data[MAX_PEOPLE];
	int head;
	int tail;
	int count;
} Queue;

static void queue_init(Queue* q)
{
	q->head = 0;
	q->tail = 0;
	q->count = 0;
}

static void queue_push(Queue* q, int id)
{
	q->data[q->tail].id = id;
	q->tail = (q->tail + 1) % MAX_PEOPLE;
	q->count++;
}

static int queue_pop(Queue* q)
{
	int id = q->data[q->head].id;
	q->head = (q->head + 1) % MAX_PEOPLE;
	q->count--;
	return id;
}

int main(void)
{
	Queue q;
	int report_interval = 5;

	queue_init(&q);
	for (int i = 1; i <= MAX_PEOPLE; i++) {
		queue_push(&q, i);
	}

	while (q.count > 1) {
		for (int i = 0; i < report_interval - 1; i++) {
			int t = queue_pop(&q);
			queue_push(&q, t);
		}
		int eliminated = queue_pop(&q);
		printf("淘汰: %d\n", eliminated);
	}

	printf("最后剩下的人是: %d\n", queue_pop(&q));
	return 0;
}
