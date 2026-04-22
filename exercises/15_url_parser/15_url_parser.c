#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int parseKv(const char* url,char* key,char* value);

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // TODO: 在这里添加你的代码




    // 1. 解析出包含查询参数的字符串
    char* query_params = strstr(url, "?");
    if (query_params == NULL) {
        printf("URL中没有查询参数\n");
        return 1;
    }
    query_params++;

    // 2. 解析出所有的key-value键值对
    char* kvstr[100] = {0};
    while (strlen(query_params) > 0) {
        // printf("query_params = %s\n", query_params);
        // printf("len = %d\n", strlen(query_params));
        // printf("d = %d\n", *query_params);


        // 查询下一个key-value对的索引
        char* index = strchr(query_params, '&');
        // 处理最后一个key-value对
        if (index == NULL) {
            index = query_params + strlen(query_params);
        }
        strncpy(kvstr, query_params, index - query_params );
        // printf("-----------kvstr = %s\n", kvstr);
        
        // 3. 解析key-value键值对
        char key[256] = {0};
        char value[256] = {0};
        parseKv(kvstr, key, value);
        printf("key = %s, value = %s\n", key, value);
        
        query_params = index ;
        query_params+=*query_params !='\0';
    }


    return 0 ;
    
    


exit:
    return err;
}

int parseKv(const char* url,char* key,char* value){
    // printf("kv = %s\n", url);


    char* equal_sign = strchr(url, '=');
    if (equal_sign == NULL) {
        printf("key-value对中没有等号\n");
        return 1;
    }
    equal_sign++;
    strncpy(key, url, equal_sign - url - 1);
    strncpy(value, equal_sign,strlen(equal_sign) );
    return 0;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}