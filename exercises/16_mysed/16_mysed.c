#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }
    char *p1,*p2,*p3;
    p1 = strchr(cmd,'/');
    p2 = strchr(p1+1,'/');
    p3 = strchr(p2+1,'/');

    // 构造字符串新内存空间（带\0或者/）
    int old_str_len = p2-p1; 
    *old_str=malloc(sizeof(char)*old_str_len);
    int new_str_len = p3-p2 ;
    *new_str=malloc(sizeof(char)*new_str_len);
    // return 0;
    // printf("old_str = %s ",*old_str);
    // printf("new_str = %s ",*new_str);

    // 复制字符串
    strncpy(*old_str,p1+1,old_str_len-1);
    (*old_str)[old_str_len] = '\0';

    strncpy(*new_str,p2+1,new_str_len-1);
    (*new_str)[new_str_len] = '\0';


    // 验证结果
    // printf("old_str %s\n",*old_str);
    // printf("new_str %s\n",*new_str);

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {

    // printf("0-str %s \n",str);
    char new_str[MAX_LINE_LENGTH] = {0};
    // int new_str_map[MAX_LINE_LENGTH] ={0}

    int old_len = strlen(old) ;
    int new_len = strlen(new) ;
    int str_len = strlen(str) ;
    
    // printf("str = %s , old = -%s- ,new = -%s-\n",str,old,new);
    

    char *pold = NULL , *pnew = NULL;

    pold = strstr(str,old);
    pnew = new_str+(pold-str);
    // 复制替换前
    strncpy(new_str,str,pold-str);

    
    // printf("1-str %s \n",str);
    // printf("1-new_str %s \n",new_str);


    // 复制需要替换的串
    strncpy(pnew,new,new_len) ; 

    
    // printf("2-str %s \n",str);
    // 复制剩下的串
    pnew += new_len ; 
    pold +=old_len;
    strcpy(pnew,pold) ; 

    // printf("new_str %s \n",new_str);
    // printf("str %s \n",str);
    
    strcpy(str,new_str);

}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line1[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;

    //解析指令
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    // 替换指令
    replace_first_occurrence(line1, old_str, new_str);
    fputs(line1, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
