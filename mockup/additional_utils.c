#include "userfunc.h"

//�߰� ���� �����
void EraseSpace(char* ap_string)
{
	assert(ap_string != NULL && "ap_string is NULL");
	char* p_dest = ap_string;

	while (*ap_string != 0)
	{
		if (*ap_string != ' ')
		{
			*p_dest = *ap_string;
			p_dest++;
		}

		ap_string++;
	}
	*p_dest = 0;	//�� �������� null ����
}
// ���ڿ� ���� ���鹮�� ���� �Լ�
char* rtrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	if (des == NULL)
	{
		des = (char*)malloc(sizeof(char) * strlen(src));//fgets �ϸ� ���๮�ڵ� ���̵��ϴ�.
	}
	assert(des != NULL && "temp memory allocation is failed.");
	char* tdes = des;
	const char* tsrc = src;

	while (*tsrc != '\0')
	{
		*tdes++ = *tsrc++;
	}
	*tdes = '\0';
	while (*(tsrc - 1) == ' ')
	{
		tsrc--;
		tdes--;
	}
	*tdes = '\0';

	return des;
}
// ���ڿ� ���� ���鹮�� ���� �Լ�
char* ltrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	if (des == NULL)
	{
		des = (char*)malloc(sizeof(char) * strlen(src));//fgets �ϸ� ���๮�ڵ� ���̵��ϴ�.
	}
	assert(des != NULL && "temp memory allocation is failed.");
	int startFlags = 0;
	char* tdes = des;
	const char* tsrc = src;

	while (*tsrc != '\0')
	{
		if (*tsrc == ' ' && startFlags == 0)
		{
			tsrc++;
		}
		else
		{
			startFlags = 1;
			*tdes++ = *tsrc++;
		}
	}
	*tdes = '\0';

	return des;
}
// ���ڿ� �յ� ���� ��� ���� �Լ�
char* trim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	if (des == NULL)
	{
		des = (char*)malloc(sizeof(char) * strlen(src));//fgets �ϸ� ���๮�ڵ� ���̵��ϴ�.
	}
	assert(des != NULL && "temp memory allocation is failed.");
	int startFlags = 0;
	char* tdes = des;
	const char* tsrc = src;

	while (*tsrc != '\n')
	{
		if (*tsrc == ' ' && startFlags == 0)
		{
			tsrc++;
		}
		else
		{
			startFlags = 1;
			*tdes++ = *tsrc++;
		}
	}
	*tdes = '\0';
	if ((*(tsrc - 1) == ' '))
	{
		while (*tsrc != ' ')
		{
			tsrc--;
			tdes--;
		}
		*tdes = '\0';
	}
	return des;
}