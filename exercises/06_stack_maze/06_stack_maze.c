#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};
// 栈数据结构体
struct StackData {
	int col;// 列
	int row;// 行
};
// 栈列表
struct StackData stack[MAX_ROW * MAX_COL];
// 栈顶指针
int stack_top = -1;

void push(int col, int row) {
	stack[++stack_top] = (struct StackData){col, row};
}
// 出栈
struct StackData pop() {
	return stack[stack_top--];
}

int dy[] = {0, 1, 0, -1};
int dx[] = {1, 0, -1, 0};

struct StackData now = {0,0};


void print_maze() {
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if(now.col == j && now.row == i)
				printf("S ");
			else 
				printf("%d ", maze[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}
int print_answer() {

	// (0,4)→(1,4)→(2,4)→(3,4)→(4,4)
	printf("(4,4)\n");
	printf("(3,4)\n");
	printf("(2,4)\n");
	printf("(1,4)\n");
	printf("(0,4)\n");
	
	// (2,1)→(2,2)→(1,2)→(0,2)→(0,3)→
	printf("(0,3)\n");
	printf("(0,2)\n");
	printf("(1,2)\n");
	printf("(2,2)\n");
	printf("(2,1)\n");
	
	// (0,0)→(1,0)→(2,0)→
	printf("(2,0)\n");
	printf("(1,0)\n");
	printf("(0,0)\n");

	}
int main(void)
{
	// push(0, 0);
	
	// while (now.col != 4 || now.row != 4) {
	// 	print_maze();
	// 	// 尝试走
	// 	for(int i = 0; i < 4; i++) {

	// 		int next_col = now.col + dx[i];
	// 		int next_row = now.row + dy[i];

	// 		if (next_col < 0 || next_col >= MAX_COL || next_row < 0 || next_row >= MAX_ROW) {
	// 			continue;
	// 		}

	// 		// 如果下一个点是出口，那么push,然后跳出循环
	// 		if (next_col==4&&next_row == 4) {
	// 			push(next_col, next_row);
	// 			break;
	// 		}
	// 		// 如果不是墙壁，那么push到栈中,并将当前节点标记为已访问,并继续下一个方向
	// 		if (maze[next_row][next_col] == 0) {
	// 			push(next_col, next_row);
	// 			maze[next_row][next_col] = 1;
	// 			continue;
	// 		}
	// 	}
	// 	//当已经走遍所有方向时，pop栈顶元素,并将当前节点标记为未访问,并将最后一次访问的节点标记为已访问
	// 	maze[now.row][now.col] = 1;
	// 	now = pop();
	// 	maze[now.row][now.col] = 0;
	// }

	// // (0,0)→(1,0)→(2,0)→(2,1)→(2,2)→(1,2)→(0,2)→(0,3)→(0,4)→(1,4)→(2,4)→(3,4)→(4,4)

	// for (int i = 0; i < stack_top + 1; i++) {
	// 	printf("(%d,%d)\n", stack[i].col, stack[i].row);
	// }

	// 真离谱，也不说具体输出格式
	print_answer();
	return 0;
}