#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge_sort(int left, int right) {
    // 如果左侧比右侧更右，或者相等，那么没有意义
    if (left >= right) {
        return;
    }

    // 计算中间位置
    int mid = (left + right) / 2;

    // 递归排序左侧半部分
    merge_sort(left, mid);

    // 递归排序右侧半部分
    merge_sort(mid + 1, right);


    int i = left; // 左侧半部分指针
    int i_end = mid; // 左侧半部分结束位置
    int j = mid + 1; // 右侧半部分指针
    int j_end = right; // 右侧半部分结束位置
    int k = left; // 临时数组指针

    // 按照循序合并左侧半部分和右侧半部分
    for(;i<=i_end && j<=j_end;k++){
        if(students[i].score > students[j].score){
            temp[k] = students[i];
            i++;
        }else{
            temp[k] = students[j];
            j++;
        }
    }

    // 合并剩余元素到临时数组中
    for(;i<=i_end;k++){
        temp[k] = students[i];
        i++;
    }
    for(;j<=j_end;k++){
        temp[k] = students[j];
        j++;
    }

    // 复制临时数组中的元素到原始数组中
    for(i = left; i <= right; i++){
        students[i] = temp[i];
    }

}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}