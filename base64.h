#ifndef _BASE64_H  
#define _BASE64_H  

#include "common.h"
#include <string.h>
#include <stdio.h>

class Base64
{
private:
	//定义base64编码表  
	unsigned char base64_table[100];
	//根据base64表，以字符找到对应的十进制数据  
	int table[255];
public:
	//获取数据结构
	unsigned char* src;
	unsigned char* dst;
	int src_length;
	int dst_length;
public:
	Base64()
	{
		int temp[255] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0,
			63, 52, 53, 54, 55, 56, 57, 58,
			59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
			13, 14, 15, 16, 17, 18, 19, 20, 21,
			22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26,
			27, 28, 29, 30, 31, 32, 33, 34, 35,
			36, 37, 38, 39, 40, 41, 42, 43, 44,
			45, 46, 47, 48, 49, 50, 51
		};
		memcpy(this->base64_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",100);
		memcpy(this->table, temp, sizeof(temp));
	}
	void base64_encode(unsigned char *str);
	void bae64_decode(unsigned char *code);
};

#endif

