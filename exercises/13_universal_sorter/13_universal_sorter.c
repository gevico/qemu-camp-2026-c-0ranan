#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*CompareFunc)(const void *, const void *);

int compareInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareFloat(const void *a, const void *b) {
    float diff = (*(float*)a - *(float*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

int compareString(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

void sort(void *array, size_t n, size_t size, CompareFunc compare) {
    qsort(array, n, size, compare);
}

void processFile(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        printf("错误: 无法打开文件 %s\n", filename);
        return;
    }
    // choice: 1-整数排序, 2-浮点数排序
    // n: 元素数量, 最多支持20个元素
    int choice, n;
    if (fscanf(fin, "%d", &choice) != 1 || fscanf(fin, "%d", &n) != 1) {
        printf("错误: 文件 %s 格式不正确\n", filename);
        fclose(fin);
        return;
    }

    if (n > 20) n = 20;  // 最多支持20个元素

    printf("=== 处理数据来自: %s ===\n", filename);

    switch (choice) {
        // TODO: 在这里添加你的代码
        
        case 1 :
            // 整数排序
            

            int *is = malloc(sizeof(int)*n);

            // 读取数据
            for(int i=0;i<n;i++){
                fscanf(fin,"%d",&is[i]);
            }
            // 排序
            sort(is,n,sizeof(int),compareInt);
            // 输出结果
            for(int i=0;i<n;i++){
                if(i!=0){
                    printf(" ");
                }
                printf("%d",is[i]);
            }
            printf("\n");
            // 释放内存
            free(is);
            break ; 
        case 2 :
            // 浮点数排序
            float *fs = malloc(sizeof(float)*n);

            // 读取数据
            for(int i=0;i<n;i++){
                fscanf(fin,"%f",&fs[i]);
            }
            // 排序
            sort(fs,n,sizeof(float),compareFloat);
            // 输出结果
            for(int i=0;i<n;i++){
                if(i!=0){
                    printf(" ");
                }
                printf("%.2f",fs[i]);
            }
            printf("\n");
            // 释放内存
            free(fs);
            break ; 
    }

    fclose(fin);
}

int main() {
    processFile("int_sort.txt");
    processFile("float_sort.txt");

    return 0;
}