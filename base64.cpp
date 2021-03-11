#include "base64.h"  

void Base64::base64_encode(unsigned char str[])
{
	long len;
	long str_len;
	unsigned char *res;
	int i, j;

	//���㾭��base64�������ַ�������  
	str_len = strlen((char*)str);
	if (str_len % 3 == 0)
		len = str_len / 3 * 4;
	else
		len = (str_len / 3 + 1) * 4;

	this->dst_length = len;

	this->dst = (unsigned char*)malloc(sizeof(unsigned char)*len + 1);
	this->dst[len] = '\0';

	//��3��8λ�ַ�Ϊһ����б���  
	for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
	{
		this->dst[i] = this->base64_table[str[j] >> 2];															//ȡ����һ���ַ���ǰ6λ���ҳ���Ӧ�Ľ���ַ�  
		this->dst[i + 1] = this->base64_table[(str[j] & 0x3) << 4 | (str[j + 1] >> 4)];			//����һ���ַ��ĺ�λ��ڶ����ַ���ǰ4λ������ϲ��ҵ���Ӧ�Ľ���ַ�  
		this->dst[i + 2] = this->base64_table[(str[j + 1] & 0xf) << 2 | (str[j + 2] >> 6)];		//���ڶ����ַ��ĺ�4λ��������ַ���ǰ2λ��ϲ��ҳ���Ӧ�Ľ���ַ�  
		this->dst[i + 3] = this->base64_table[str[j + 2] & 0x3f];											//ȡ���������ַ��ĺ�6λ���ҳ�����ַ�  
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

	//����������ַ�������  
	len = strlen((char*)code);
	//�жϱ������ַ������Ƿ���=  
	if (strstr((char*)code, "=="))
		str_len = len / 4 * 3 - 2;
	else if (strstr((char*)code, "="))
		str_len = len / 4 * 3 - 1;
	else
		str_len = len / 4 * 3;
	
	this->src_length = str_len;

	this->src = (unsigned char*)malloc(sizeof(unsigned char)*str_len + 1);
	this->src[str_len] = '\0';

	//��4���ַ�Ϊһλ���н���  
	for (i = 0, j = 0; i < len - 2; j += 3, i += 4)
	{
		this->src[j] = ((unsigned char)this->table[code[i]]) << 2 | (((unsigned char)this->table[code[i + 1]]) >> 4);						//ȡ����һ���ַ���Ӧbase64���ʮ��������ǰ6λ��ڶ����ַ���Ӧbase64���ʮ�������ĺ�2λ�������  
		this->src[j + 1] = (((unsigned char)this->table[code[i + 1]]) << 4) | (((unsigned char)this->table[code[i + 2]]) >> 2);		//ȡ���ڶ����ַ���Ӧbase64���ʮ�������ĺ�4λ��������ַ���Ӧbas464���ʮ�������ĺ�4λ�������  
		this->src[j + 2] = (((unsigned char)this->table[code[i + 2]]) << 6) | ((unsigned char)this->table[code[i + 3]]);					//ȡ���������ַ���Ӧbase64���ʮ�������ĺ�2λ���4���ַ��������  
	}
}