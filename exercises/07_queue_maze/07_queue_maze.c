#include <stdio.h>
#include <stdlib.h>
#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};


// 坐标
struct coord {
	int col;// 列
	int row;// 行
};

// 路径地图
struct coord* path_map[MAX_ROW][MAX_COL] = {0};




struct QueueNode{
	struct coord* c;
	struct QueueNode* next;
};


struct QueueNode* queue_head = NULL;
struct QueueNode* queue_tail = NULL;
// 队列是否为空
int queue_empty(void){
	return queue_head == NULL;
}
// 入队
void queue_push(int col, int row){
	// 创建一个新的节点
	struct QueueNode* new_node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	new_node->c = (struct coord*)malloc(sizeof(struct coord));
	// 初始化节点的坐标
	new_node->c->col = col;
	new_node->c->row = row;
	// 初始化节点的下一个节点
	new_node->next = NULL;
	if(queue_head == NULL){
		// 如果队列为空，直接将新节点赋值给队头头尾
		queue_head = new_node;
		queue_tail = new_node;
	}else{
		// 否则，将新节点加入队尾
		queue_tail->next = new_node;
		queue_tail = new_node;
	}
}
// 出队
struct coord* queue_pop(void){
	// 从队头中取出一个节点
	struct coord* ret = queue_head->c;
	// 将队头指针指向下一个节点
	struct QueueNode* next_head = queue_head->next;
	// 释放队头节点
	free(queue_head);
	// 更新队头指针
	queue_head = next_head;
	if (next_head == NULL){
		// 如果队列只有一个节点，将队尾也针指向 NULL
		queue_tail = NULL;
	}

	// 返回取出的节点
	return ret;
}
// 队列大小
int queue_size(void){
	return queue_tail - queue_head + 1;
}



// 四个方向的偏移量
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

// 当前所在的行，列
int now_col = 0;
int now_row = 0;

int bfs(){
	queue_push(0, 0);
	while((!queue_empty()) && path_map[MAX_ROW - 1][MAX_COL - 1] == NULL){
		// 从队列中取出一个节点
		struct coord* now = queue_pop();
		now_col = now->col;
		now_row = now->row;
		free(now);
		now = 0;
		// 遍历当前位置的四个方向所有能够走的节点
		// 当遍历所有方向后，就从队列寻找下一个可以遍历方向的节点
		for(int i = 0; i < 4; i++)
		{
			int next_col = now_col + dx[i];
			int next_row = now_row + dy[i];
			// 如果如果能够通行，1. 记录路径 2. 加入队列

			// flag 是用来判断能否通行的标志位
			int flag = 1 ;
			// 检查是否在地图范围内
			flag = flag && next_col >= 0 && next_col < MAX_COL && next_row >= 0 && next_row < MAX_ROW;
			// 检查是否是墙
			flag = flag && (maze[next_row][next_col] == 0);
			// 检查是否已经访问过
			flag = flag && (path_map[next_row][next_col] == NULL);
			// 不为0,0	节点
			flag = flag && (next_col != 0 || next_row != 0);

			// printf("next_col: %d, next_row: %d, flag: %d\n", next_col, next_row, flag);

			if(flag){
				// 记录路径
				path_map[next_row][next_col] = (struct coord*)malloc(sizeof(struct coord));
				path_map[next_row][next_col]->col = now_col;
				path_map[next_row][next_col]->row = now_row;
				// 加入队列
				queue_push(next_col, next_row);
			}
		}
	}
}

int printPathMap(void){
	for(int i = 0; i < MAX_ROW; i++){
		for(int j = 0; j < MAX_COL; j++){
			if(path_map[i][j] != NULL){
				struct coord* now = path_map[i][j];
				printf("(%d,%d)", now->col, now->row);
			}else{
				printf("( , )");
			}
		}
		printf("\n");
	}
}

struct coord* path[MAX_COL*MAX_ROW] = {0};
int main(void)
{
	bfs();

	// 打印路径地图
	// printPathMap();

	// 打印路径
	struct coord* now = path_map[MAX_ROW - 1][MAX_COL - 1];

	int path_len = 0;

	printf("(4,4)\n");
		
	while(now != NULL){
		// path[path_len++] = now;
		printf("(%d, %d)\n", now->row, now->col);
		now = path_map[now->row][now->col];
	}

	// for(int i = path_len - 1; i >= 0; i--){
	// 	printf("(%d, %d)\n", path[i]->col, path[i]->row);
	// }


	return 0;
}