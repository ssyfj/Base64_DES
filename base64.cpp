#include "base64.h"  

void Base64::base64_encode(unsigned char str[])
{
	long len;
	long str_len;
	unsigned char *res;
	int i, j;

	//计算经过base64编码后的字符串长度  
	str_len = strlen((char*)str);
	if (str_len % 3 == 0)
		len = str_len / 3 * 4;
	else
		len = (str_len / 3 + 1) * 4;

	this->dst_length = len;

	this->dst = (unsigned char*)malloc(sizeof(unsigned char)*len + 1);
	this->dst[len] = '\0';

	//以3个8位字符为一组进行编码  
	for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
	{
		this->dst[i] = this->base64_table[str[j] >> 2];															//取出第一个字符的前6位并找出对应的结果字符  
		this->dst[i + 1] = this->base64_table[(str[j] & 0x3) << 4 | (str[j + 1] >> 4)];			//将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符  
		this->dst[i + 2] = this->base64_table[(str[j + 1] & 0xf) << 2 | (str[j + 2] >> 6)];		//将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符  
		this->dst[i + 3] = this->base64_table[str[j + 2] & 0x3f];											//取出第三个字符的后6位并找出结果字符  
	}

	switch (str_len % 3)
	{
	case 1:
		this->dst[i - 2] = '=';
		this->dst[i - 1] = '=';
		break;
	case 2:
		this->dst[i - 1] = '=';
		break;
	}
}

void Base64::bae64_decode(unsigned char code[])
{

	long len;
	long str_len;
	unsigned char *res;
	int i, j;

	//计算解码后的字符串长度  
	len = strlen((char*)code);
	//判断编码后的字符串后是否有=  
	if (strstr((char*)code, "=="))
		str_len = len / 4 * 3 - 2;
	else if (strstr((char*)code, "="))
		str_len = len / 4 * 3 - 1;
	else
		str_len = len / 4 * 3;
	
	this->src_length = str_len;

	this->src = (unsigned char*)malloc(sizeof(unsigned char)*str_len + 1);
	this->src[str_len] = '\0';

	//以4个字符为一位进行解码  
	for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
	{
		this->src[j] = ((unsigned char)this->table[code[i]]) << 2 | (((unsigned char)this->table[code[i + 1]]) >> 4);						//取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合  
		this->src[j + 1] = (((unsigned char)this->table[code[i + 1]]) << 4) | (((unsigned char)this->table[code[i + 2]]) >> 2);		//取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合  
		this->src[j + 2] = (((unsigned char)this->table[code[i + 2]]) << 6) | ((unsigned char)this->table[code[i + 3]]);					//取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合  
	}
}