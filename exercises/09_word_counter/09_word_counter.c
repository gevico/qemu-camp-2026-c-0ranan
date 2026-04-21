#include <stdio.h>


//   第 09 题在考什么

//   功能：对程序里给定的英文句子，统计「单词个数」并输出
//   单词数量: <整数>（测评用 sscanf 按 “单词数量: %d” 解析，格式要对）。

//   分词规则（和测试一致）：

//   • 以 空格 和 换行 作为分隔，其它字符（含 ,、.、' 等）只要旁边没有空格，就和相邻字母同属一个词。
//   • 因此 you, 算 1 个词、country. 算 1 个题；Don't 里带撇号也整体算 1 个词。

//   算法：用布尔状态 in_word 表示「当前是否在某个词内部」；从词外第一次碰到非空白时 wordCount++
//   并进入词内；遇到空白再退出词外。这样多空格、首尾空格在逻辑上也会自然数对（测试里用同样思路验证了边界，见
//   test_09_word_counter.c）。

//   本题固定句拆成 18 段，例如：
//   Don't … you, … but … country. 等，与评测期望 18 一致。

/* 以空格/换行分词，标点若无空格分隔则随相邻字母同一词。 */
int main(void)
{
	char str[] = "Don't ask what your country can do for you, but ask what you can do for your country.";
	int wordCount = 0;
	int in_word = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ' && str[i] != '\n' && !in_word) {
			in_word = 1;
			wordCount++;
		} else if (str[i] == ' ' || str[i] == '\n') {
			in_word = 0;
		}
	}

	printf("单词数量: %d\n", wordCount);
	return 0;
}
