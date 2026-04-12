#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN     50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;
int n;
Student students[MAX_STUDENTS];


int print_students(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %d,", students[i].name, students[i].score);
    }
    printf("\n");
}


void quick_sort(int left, int right) {

    // 如果左侧比右侧更右，或者相等，那么没有意义
    if(left >= right){
        return;
    }


    
    int x = students[(left+right)/2].score;
    int l = left-1;
    int r = right+1;
    // printf("-----------------\n");
    // printf("left=%d,right=%d\n",left,right);
    // printf("x=%d,l=%d,r=%d\n",x,l,r);

    while(l<r){

        // 找到第一个大于x的元素
        do l++;while(students[l].score>x);
        // 找到第一个小于x的元素
        do r--;while(students[r].score<x);
        

        
        // 交换元素
        if(l<r){
            // printf("swap l=%d,r=%d\n",l,r);
            
            Student temp = students[l];
            students[l] = students[r];
            students[r] = temp;
            // print_students(students, n);
            // l++;
            // r--;
        }
    }

    // 递归排序
    quick_sort(left,l);
    quick_sort(l+1,right);
}


int main(void) {
    FILE *file = fopen("03_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 03_students.txt\n");
        return 1;
    }


    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d（应为 1-%d）\n", n, MAX_STUDENTS);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    quick_sort(0, n - 1);

    // 输出结果
    printf("\n快速排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}