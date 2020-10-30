#include "userfunc.h"


// 収切 焼艦檎 1鋼発, 因拷(?)戚檎 2 鋼発, 収切檎 0鋼発
int checkDigit(const char* ap_string)
{
	const char* p_dest = ap_string;
	while (*p_dest != '\0')
	{
		if (isdigit(*p_dest) == 0)
		{
			if (*p_dest == ' ' || *p_dest == '\t')
			{
				return 2;
			}
			return 1;
		}
		p_dest++;
	}
	return 0;
}
//収切 or 慎庚切 焼艦檎 1鋼発
int checkAlnum(const char* ap_string)
{
	const char* p_dest = ap_string;
	while (*p_dest != '\0')
	{
		if (isalnum(*p_dest) == 0)
		{
			return 1;
		}
		p_dest++;
	}
	return 0;
}
// 収切 + 慎庚切亜 焼艦檎 1鋼発
int checkID(const char* ap_string)
{
	const char* p_dest = ap_string;
	int IDcon[2] = { 0, };

	while (*p_dest != '\0')
	{
		if (isalnum(*p_dest) == 0)
		{
			return 1;
		}
		else if (isdigit(*p_dest) != 0)
		{
			IDcon[1] = 1;
		}
		else
		{
			IDcon[0] = 1;
		}
		p_dest++;
	}
	if (IDcon[0] && IDcon[1])
	{
		return 0;
	}
	return 1;
}
// 慎庚切 箸精 因拷戚 焼艦檎 1鋼発
int checkName(const char* ap_string)
{
	const char* p_dest = ap_string;

	while (*p_dest != '\0')
	{
		if (isalpha(*p_dest) == 0 && *p_dest != ' ')
		{
			return 1;
		}
		p_dest++;
	}
	return 0;
}
// 慎嬢, 収切, 働庚 馬蟹 梢 赤嬢醤敗. 戚雌廃暗 級嬢神暗蟹, 蒸生檎 1鋼発
int checkPW(const char* ap_string)
{
	const char* p_dest = ap_string;
	char SC[10] = { '!','@','#','$','%','^','&','*','(',')' };
	int PWcon[3] = { 0, };
	int i = 0;

	while (*p_dest != '\0')
	{
		if (isalpha(*p_dest) != 0)
		{
			PWcon[0] = 1;
		}
		else if (isdigit(*p_dest) != 0)
		{
			PWcon[1] = 1;
		}
		else
		{
			for (i = 0; i < 10; i++)
			{
				if (SC[i] == *p_dest)
				{
					PWcon[2] = 1;
					break;
				}
			}
		}
		p_dest++;
	}
	if (PWcon[0] && PWcon[1] && PWcon[2])
	{
		return 0;
	}
	return 1;
}
//掻娃 因拷 端滴馬奄
int checkSpace(const char* ap_string)
{
	const char* p_dest = ap_string;

	while (*p_dest != '\0')
	{
		if (*p_dest++ == ' ')
		{
			return 1;
		}
	}
	return 0;	//固 原走厳拭 null 煽舌
}
//掻娃 因拷 走酔奄
void EraseSpace(char* ap_string)
{
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
	*p_dest = 0;	//固 原走厳拭 null 煽舌
}
// 庚切伸 酔著 因拷庚切 肢薦 敗呪
char* rtrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	des = (char*)malloc(sizeof(char) * strlen(src));//fgets 馬檎 鯵楳庚切亀 旭戚級嬢逢艦陥.
	assert(des != NULL && "temp memory allocation is failed.");
	char* tdes = des;
	const char* tsrc = src;

	while (*tsrc != '\0')
	{
		*tdes++ = *tsrc++;
	}

	while (*tsrc == ' ')
	{
		tsrc--;
		tdes--;
	}
	*++tdes = '\0';

	return des;
}
// 庚切伸 疎著 因拷庚切 肢薦 敗呪
char* ltrim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	des = (char*)malloc(sizeof(char) * strlen(src));//fgets 馬檎 鯵楳庚切亀 旭戚級嬢逢艦陥.
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
// 庚切伸 蒋及 因拷 乞砧 肢薦 敗呪
char* trim_malloc(char* des, const char* src)
{
	assert(src != NULL && "src is NULL");
	des = (char*)malloc(sizeof(char) * strlen(src));//fgets 馬檎 鯵楳庚切亀 旭戚級嬢逢艦陥.
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
	while (*tsrc == ' ')
	{
		tsrc--;
		tdes--;
	}
	*--tdes = '\0';


	return des;
}
// 脊窒榎 域疎督析 鎧蝕 廃匝聖 IOinqury拭 鎧蝕 隔嬢掃艦陥. 失因馬檎 1 叔鳶馬檎 0 鋼発
int strToIOiq(const char* str, IOinqury_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	const char* piter = str;
	const char* pcounter;
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;
	int counter = 0;

	//域疎 鎧蝕 嗣奄
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_date, piter, counter);
	ioacc->IO_date[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_name, piter, counter);
	ioacc->IO_name[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_othernum, piter, counter);
	ioacc->IO_othernum[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_money, piter, counter);
	ioacc->IO_money[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
		if (counter > 2)
		{
			ioacc = NULL;
			return 0;
		}
	}
	strncpy(ioacc->IO_io, piter, 1);
	ioacc->IO_io[1] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		if (*pcounter == '\n')
		{
			ioacc = NULL;
			return 0;
		}
		counter++;
	}
	strncpy(ioacc->IO_balance, piter, counter);
	ioacc->IO_balance[counter] = '\0';
	return 1;
}
// 森旋榎 域疎督析 鎧蝕 廃匝聖 IOinqury拭 鎧蝕 隔嬢掃艦陥. 3腰属 昔切稽 隔嬢層 域疎腰硲幻 窒径. 失因馬檎 1 叔鳶馬檎 0鋼発 
int strToFSiq(const char* str, FSinqury_t* fsacc, const char* accNum)
{
	assert(str != NULL && fsacc != NULL && accNum != NULL && "str or fsacc or accNum is NULL");

	const char* piter = str;
	const char* pcounter;
	int counter = 0;
	int findflag = 0;

	//域疎 鎧蝕 嗣奄
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_date, piter, counter);
	fsacc->FS_date[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_name, piter, counter);
	fsacc->FS_name[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_mynum, piter, counter);
	fsacc->FS_mynum[counter] = '\0';

	fsacc->FS_type = getAccType(fsacc->FS_mynum);

	if (strncmp(accNum, fsacc->FS_mynum, 7) == 0)
	{
		findflag = 1;
	}

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_income, piter, counter);
	fsacc->FS_income[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(fsacc->FS_balance, piter, counter);
	fsacc->FS_balance[counter] = '\0';

	if (findflag == 1)
	{
		return 1;
	}
	return 0;
}
// 脊窒榎 域疎督析 紗失 廃匝聖 IOattributes_malloc_t拭 隔嬢 掃艦陥. 失因馬檎 1 叔鳶馬檎 0 鋼発
int strToIOatt_malloc(const char* str, IOattributes_malloc_t* ioacc)
{
	assert(str != NULL && ioacc != NULL && "str or ioacc is NULL");

	const char* piter = str;
	const char* pcounter;
	int counter = 0;
	int autonum = 0;

	//域疎 鎧蝕 嗣奄
	pcounter = piter;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_name, piter, counter);
	ioacc->IO_name[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_mynum, piter, counter);
	ioacc->IO_mynum[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_balance, piter, counter);
	ioacc->IO_balance[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		counter++;
	}
	strncpy(ioacc->IO_Passwords, piter, counter);
	ioacc->IO_Passwords[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		if (counter > 2)
		{
			return 0;
		}
		counter++;
	}
	strncpy(ioacc->IO_dateLimits, piter, counter);
	ioacc->IO_dateLimits[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		if (*pcounter == '\n')
		{
			return 0;
		}
		counter++;
	}
	strncpy(ioacc->IO_monthLimits, piter, counter);
	ioacc->IO_monthLimits[counter] = '\0';

	piter = pcounter;
	counter = 0;
	while (*pcounter++ != '|')
	{
		if (*pcounter == '\n')
		{
			ioacc->autoattributes = NULL;
			ioacc->autoNums = 0;
			return 1;
		}
	}
	pcounter = piter;
	while (*pcounter != '\n')
	{
		for (int i = 0; i < 4; i++)
		{
			while (*pcounter++ != '|');
		}
		autonum++;
	}
	pcounter = piter;
	ioacc->autoNums = autonum;
	ioacc->autoattributes = (char***)malloc(sizeof(char**) * autonum);
	for (int j = 0; j < autonum; j++)
	{
		ioacc->autoattributes[j] = (char**)malloc(sizeof(char*) * 4);
		ioacc->autoattributes[j][0] = (char*)malloc(sizeof(char) * 3);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][0], piter, counter);
		ioacc->autoattributes[j][0][counter] = '\0';
		ioacc->autoattributes[j][1] = (char*)malloc(sizeof(char) * 13);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][1], piter, counter);
		ioacc->autoattributes[j][1][counter] = '\0';
		ioacc->autoattributes[j][2] = (char*)malloc(sizeof(char) * 8);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][2], piter, counter);
		ioacc->autoattributes[j][2][counter] = '\0';
		ioacc->autoattributes[j][3] = (char*)malloc(sizeof(char) * 3);
		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(ioacc->autoattributes[j][3], piter, counter);
		ioacc->autoattributes[j][3][counter] = '\0';
	}

	return 1;
}
// 森旋榎 域疎督析 紗失 廃匝聖 FSattritubes_t拭 隔嬢掃艦陥. 3腰属 昔切稽 隔嬢層 域疎腰硲幻 窒径. 失因馬檎 獣拙是帖 舛呪, 叔鳶馬檎 -1 鋼発
int strToFSatt(const char* str, FSattributes_t* fsacc, const char* accNum)
{
	assert(str != NULL && fsacc != NULL && accNum != NULL && "str or ioacc or accNum is NULL");

	const char* piter = str;
	const char* returnValue;
	const char* pcounter;
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;
	int counter = 0;
	int flag = 1;
	int findflag = 0;


	//域疎 鎧蝕 嗣奄

	while (flag == 1 && *piter != '\n')
	{
		returnValue = piter;
		pcounter = piter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_name, piter, counter);
		fsacc->FS_name[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_mynum, piter, counter);
		fsacc->FS_mynum[counter] = '\0';

		if (strncmp(fsacc->FS_mynum, accNum, 7) == 0)
		{
			findflag = 1;
		}

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_money, piter, counter);
		fsacc->FS_money[counter] = '\0';


		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_Passwords, piter, counter);
		fsacc->FS_Passwords[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_remainService, piter, counter);
		fsacc->FS_remainService[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_interest, piter, counter);
		fsacc->FS_interest[counter] = '\0';

		piter = pcounter;
		counter = 0;
		while (*pcounter++ != '|')
		{
			counter++;
		}
		strncpy(fsacc->FS_balance, piter, counter);
		fsacc->FS_balance[counter] = '\0';

		if (findflag == 1)
		{
			return (int)(returnValue -str);
		}
		else
		{
			pcounter = piter;
			while (*pcounter != ' ')
			{
				pcounter++;
			}
			piter = ++pcounter;
		}
	}
	fprintf(stderr, "Eof with \\n\n");
	return -1;
}
// 陥彰 IOattributes_malloc_t 背薦
void freeIOattriutes(IOattributes_malloc_t* ioacc)
{
	if (ioacc != NULL)
	{
		for (int f1 = 0; f1 < ioacc->autoNums; f1++)
		{
			for (int f2 = 0; f2 < 4; f2++)
			{
				free(ioacc->autoattributes[f1][f2]);
				ioacc->autoattributes[f1][f2] = NULL;
			}
			free(ioacc->autoattributes[f1]);
			ioacc->autoattributes[f1] = NULL;
		}
		ioacc->autoattributes = NULL;
	}
}
// IOinqury_t 匂昔斗 閤焼辞 鎧蝕 窒径杯艦陥.
void printIOinquiry(const IOinqury_t* ioacc)
{
	assert(ioacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[6] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_date) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_date) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_date + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_name) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_name + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_othernum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_othernum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_othernum + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_money) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_money) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_money + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_io) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_io) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_io + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, ioacc->IO_balance + j, MB_CUR_MAX);
	}

	switch (*(ioacc->IO_io))
	{
	case 'i':
		wprintf(L"< %s >/ %16s: %s/ 榎衝: %s (脊榎)/ 接衝: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
		break;
	case 'o':
		wprintf(L"< %s >/ %16s: %s/ 榎衝: %s (窒榎)/ 接衝: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[5]);
		break;
	default:
		assert("Print Inquriy Error in \"printIOInquiry()\"");
	}

	for (int k = 0; k < 6; k++)
	{
		free(wtemps[k]);
		wtemps[k] = NULL;
	}
}
// FSinqury_t 匂昔斗 閤焼辞 鎧蝕 窒径杯艦陥.
int printFSinquiry(const FSinqury_t* fsacc)
{
	assert(fsacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[5] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_date) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocatFSn failed");
	for (int j = 0; j < strlen(fsacc->FS_date) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_date + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_name) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_name + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_mynum + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_income) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_income) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_income + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_balance + j, MB_CUR_MAX);
	}

	switch (fsacc->FS_type)
	{
	case T2:
		wprintf(L"< %s >/ %16s: %s/ 脊榎衝: %s / 薄仙 榎衝: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4]);
		break;
	case T3:
		wprintf(L"< %s >/ %16s: %s/ 脊榎衝: %s/ 薄仙 榎衝: %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[3], wtemps[4]);
		break;
	default:
		assert("Print Inquriy Error in \"printFSInquiry()\"");
	}

	for (int k = 0; k < 5; k++)
	{
		free(wtemps[k]);
		wtemps[k] = NULL;
	}
	return 1;
}
// IOattributes_malloc_t 匂昔斗 閤焼辞 鎧蝕 窒径杯艦陥.
void printIOatt(const IOattributes_malloc_t* ioacc)
{
	assert(ioacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[6] = { NULL, 0 };
	wchar_t*** wautotemps;
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_name) + 1; j++)
	{
		mbtowc(&wtemps[i][j], (ioacc->IO_name) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_mynum) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_balance) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_Passwords) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_Passwords) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_Passwords) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_dateLimits) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_dateLimits) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_dateLimits) + j, MB_CUR_MAX);
	}
	i++;
	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->IO_monthLimits) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(ioacc->IO_monthLimits) + 1; j++)
	{
		mbtowc(wtemps[i] + j, (ioacc->IO_monthLimits) + j, MB_CUR_MAX);
	}
	wprintf(L"< 脊窒榎 域疎 >/ %s: %s/ 接衝: %s 戚端廃亀 %s(析)/%s(杉)\n",
		wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5]);

	if (ioacc->autoNums > 0)
	{
		wautotemps = (wchar_t***)malloc(sizeof(wchar_t**) * ioacc->autoNums);
		for (int j = 0; j < ioacc->autoNums; j++)
		{
			wautotemps[j] = (wchar_t**)malloc(sizeof(wchar_t*) * 4);
			for (int u = 0; u < 4; u++)
			{
				wautotemps[j][u] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(ioacc->autoattributes[j][u]) + 1));
				for (int k = 0; k < strlen(ioacc->autoattributes[j][u]) + 1; k++)
				{
					mbtowc(wautotemps[j][u] + k, (ioacc->autoattributes[j][u]) + k, MB_CUR_MAX);
				}
			}
		}

		for (int k = 0; k < ioacc->autoNums; k++)
		{
			wprintf(L"%d)<切疑戚端>/ %.16s拭 %s 据梢, 古杉 %s析戚 鞠檎 左垣艦陥. 害精 奄娃 %s(杉)\n",
				k + 1, wautotemps[k][2], wautotemps[k][1], wautotemps[k][0], wautotemps[k][3]);
		}

		for (int f1 = 0; f1 < ioacc->autoNums; f1++)
		{
			for (int f2 = 0; f2 < 4; f2++)
			{
				free(wautotemps[f1][f2]);
				wautotemps[f1][f2] = NULL;
			}
			free(wautotemps[f1]);
			wautotemps[f1] = NULL;
		}
		free(wautotemps);
		wautotemps = NULL;
	}
	for (int h = 0; h < 6; h++)
	{
		free(wtemps[h]);
		wtemps[h] = NULL;
	}

	return;
}
// FSattributes_t 匂昔斗 閤焼辞 鎧蝕 窒径杯艦陥.
void printFSatt(const FSattributes_t* fsacc)
{
	assert(fsacc != NULL && "fascc is NULL pointer");
	wchar_t* wtemps[7] = { NULL, 0 };
	int i = 0;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_name) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_name) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_name + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_mynum) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_mynum) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_mynum + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_money) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_money) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_money + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_Passwords) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_Passwords) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_Passwords + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_remainService) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_remainService) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_remainService + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_interest) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_interest) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_interest + j, MB_CUR_MAX);
	}
	i++;

	wtemps[i] = (wchar_t*)malloc(sizeof(wchar_t) * (strlen(fsacc->FS_balance) + 1));
	assert(wtemps[i] != NULL && "wtemps[i] allocation failed");
	for (int j = 0; j < strlen(fsacc->FS_balance) + 1; j++)
	{
		mbtowc(wtemps[i] + j, fsacc->FS_balance + j, MB_CUR_MAX);
	}

	if (fsacc->type == T2)
	{
		wprintf(L"< 森榎 域疎 >/ %16s: %s/ 接衝: %s 害精 重短奄娃 %s(析) 戚切晴: %s 背走獣 榎衝 %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5], wtemps[6]);
	}
	else
	{
		wprintf(L"< 旋榎 域疎 >/ %16s: %s/ 接衝: %s 害精 重短奄娃 %s(析) 戚切晴: %s 背走獣 榎衝 %s\n",
			wtemps[0], wtemps[1], wtemps[2], wtemps[4], wtemps[5], wtemps[6]);
	}
	for (int f = 0; f < 7; f++)
	{
		free(wtemps[f]);
		wtemps[f] = NULL;
	}
}
// 厳幻窮 敗呪1
int setError()
{
	int tempnamelen = 0;
	eAccType type;
	FILE* f_setter;

	setAccListOfAll_malloc();

	for (int f = 0; f < g_allALANNums; f++) //欠覗宜檎辞
	{
		// 背雁 督析達焼亜奄
		wchar_t waccNums[8];
		for (int i = 0; i < 8; i++)
		{
			mbtowc(waccNums + i, g_allAccountsListAndName[0][f] + i, MB_CUR_MAX);
		}
		switch (getAccType(g_allAccountsListAndName[0][f])) // 展脊端滴
		{
		case T1: // 脊窒榎
			type = T1;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%s.txt", waccNums[1], waccNums);
			f_setter = _wfopen(g_wpath, L"r+");
			if (checkIO(f_setter) == 1)
			{
				fclose(f_setter);
				f_setter = NULL;
				wprintf(L"File: \"%s\" need to correction...\n terminate program...", g_wpath);
				goto NEEDTOCORRECTFILE;
			}
			fclose(f_setter);
			f_setter = NULL; 
			break;
		case T2: // 森榎
			type = T2;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", waccNums[1], waccNums[0], waccNums[1], waccNums[2]);
			f_setter = _wfopen(g_wpath, L"r+");
			if (checkFix(f_setter) == 1)
			{
				fclose(f_setter);
				f_setter = NULL;
				wprintf(L"File: \"%s\" need to correction...\n terminate program...", g_wpath);
				goto NEEDTOCORRECTFILE;
			}
			fclose(f_setter);
			f_setter = NULL;
			break;
		case T3: // 旋榎
			type = T3;
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", waccNums[1], waccNums[0], waccNums[1], waccNums[2]);
			f_setter = _wfopen(g_wpath, L"r+");
			if (checkSav(f_setter) == 1)
			{
				fclose(f_setter);
				f_setter = NULL;
				wprintf(L"File: \"%s\" need to correction...\n terminate program...", g_wpath);
				goto NEEDTOCORRECTFILE;
			}
			fclose(f_setter);
			f_setter = NULL;
			break;
		default:
			assert("Critical + fatal + horrendous error.... function: \"setInterset()\"" && 0);
		}
	}
	return 0;
NEEDTOCORRECTFILE:
	return 1;
}
// 厳幻窮 敗呪2
int checkIO(FILE* f_target) // 石生形壱...戚背馬形壱 獣亀馬走原室推 せせせせせせ
{
	assert(f_target != NULL && "I can't find file by account.txt..target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	size_t numOfBefore = 0;
	while (1)
	{
		fseek(f_target, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_target);
		if (feof(f_target))
		{
			break;
		}
		piter = g_buffer;
		pFileOffset = g_buffer;
		if (line == 0) //湛腰属匝
		{
			while ((*piter) != '|') // 域疎戚硯
			{
				if (isalnum(*piter) == 0)
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '\n') //蟹袴走 袷 収切
			{
				if (isdigit(*piter) == 0 && (*piter) != '|')
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
		}
		else//砧腰属 匝 ~ 
		{
			while ((*piter) != '|') // 劾促
			{
				if (isdigit(*piter) == 0 && *piter != '-')
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|') // 焼戚巨
			{
				if (isalnum(*piter) == 0)
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//域疎腰硲
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//儀
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if ((*piter) != 'o' && (*piter) != 'i') // i or o
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//接衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;

		}
		line++;
		CurrentFileOffset = ftell(f_target);
	}


	return 0;
}
// 厳幻窮 敗呪3
int checkFix(FILE* f_target)
{
	assert(f_target != NULL && "f_target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	size_t numOfBefore = 0;
	while (1)
	{
		fseek(f_target, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_target);
		if (feof(f_target))
		{
			break;
		}
		piter = g_buffer;
		pFileOffset = g_buffer;
		if (line == 0) //湛腰属匝
		{
		ANOTHER_ACCOUNT:
			while ((*piter) != '|') // 域疎戚硯
			{
				if (isalnum(*piter) == 0)
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//域疎腰硲
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.') //薄仙榎衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//搾腔腰硲
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)// 害精 奄娃
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 戚切晴
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 背走獣 榎衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			if (*piter++ == ' ')
			{
				goto ANOTHER_ACCOUNT;
			}
		}
		else //砧腰属 匝 ~ 
		{
			while ((*piter) != '|') // 劾促
			{
				if (isdigit(*piter) == 0 && *piter != '-')
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|') // 焼戚巨
			{
				if (isalnum(*piter) == 0)
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//域疎腰硲
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')//幻奄獣 背走 榎衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')//接衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;

		}
		line++;
		CurrentFileOffset = ftell(f_target);
	}
	return 0;
}
// 厳幻窮 敗呪4
int checkSav(FILE* f_target)
{
	assert(f_target != NULL && "f_target is NULL");

	long CurrentFileOffset = 0;
	int line = 0;
	int delNume = 6;
	char* piter = NULL;
	char* pFileOffset = NULL;
	size_t numOfBefore = 0;
	while (1)
	{
		fseek(f_target, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_target);
		if (feof(f_target))
		{
			break;
		}
		piter = g_buffer;
		pFileOffset = g_buffer;
	ANOTHER:
		if (line == 0) //湛腰属匝
		{

			while ((*piter) != '|') // 域疎戚硯
			{
				if (isalnum(*piter) == 0)
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//域疎腰硲
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.') //薄仙榎衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//搾腔腰硲
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)// 害精 奄娃
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 戚切晴
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')// 背走獣 榎衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			if (*piter++ == ' ')
			{
				goto ANOTHER;
			}
		}
		else //砧腰属 匝 ~ 
		{
			while ((*piter) != '|') // 劾促
			{
				if (isdigit(*piter) == 0 && *piter != '-')
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|') // 焼戚巨
			{
				if (isalnum(*piter) == 0)
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0)//域疎腰硲
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|')
			{
				if (isdigit(*piter) == 0 && (*piter) != '.')//幻奄獣 背走 榎衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
			while ((*piter) != '|' && (*piter) != '.')
			{
				if (isdigit(*piter) == 0)//接衝
				{
					fseek(f_target, CurrentFileOffset, SEEK_SET);
					while (*(pFileOffset++) != '\n')
					{
						CurrentFileOffset++;
						numOfBefore++;
					}
					fread(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fseek(f_target, CurrentFileOffset + 1, SEEK_SET);
					size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_target);
					f_target = _wfreopen(g_wpath, L"w+", f_target);
					fwrite(g_filebuff2, sizeof(char), numOfBefore, f_target);
					fwrite("<-- correct typos", sizeof(char), 18, f_target);
					fwrite(g_filebuff, sizeof(char), numOfWords, f_target);
					return 1;
				}
				piter++;
			}
			piter++;
		}
		line++;
		CurrentFileOffset = ftell(f_target);
	}
	return 0;
}
// 戚切 旋遂
void setInterest()
{
	FILE* f_checker;
	wchar_t waccNums[8];

	for (int f = 0; f < g_allALANNums; f++) //欠覗宜檎辞
	{
		// 背雁 督析達焼亜奄
		switch (getAccType(g_allAccountsListAndName[0][f])) // 展脊端滴
		{
		case T1: // 脊窒榎 鳶什
			break;
		case T2: // 森榎
		case T3: // 旋榎
			for (int i = 0; i < 8; i++)
			{
				mbtowc(waccNums + i, g_allAccountsListAndName[0][f] + i, MB_CUR_MAX);
			}
			swprintf(g_wpath, MAX_PATH, L"C:\\banksystemlog\\0%c\\%c%c%c.txt", waccNums[1], waccNums[0], waccNums[1], waccNums[2]);
			f_checker = _wfopen(g_wpath, L"r+");
			setFSInterest(f_checker, g_allAccountsListAndName[0][f]);
			fclose(f_checker);
			f_checker = NULL;
			break;
		default:
			assert("Critical + fatal + horrendous error.... function: \"setInterset()\"" && 0);
		}
	}
}
// 森旋榎 戚切 旋遂
int setFSInterest(FILE* f_accfile, const char* AccNum)
{
	long CurrentFileOffset = 0;
	long AttOffset = 0;
	long beforBal = 0;
	long afterBal = 0;
	int remainService = 0;
	int flag = 0;
	size_t numOfBefore = 0;

	double interestRatio = 0;

	int line = 0;
	int inputMonth = 0;
	int inputDay = 0;
	int inputYear = 0;

	char check = 0;

	char* pcp = NULL;
	char* pgb = NULL;
	char* temp =NULL;

	size_t templen = 0;
	size_t pcplen = 0;

	// 獄遁
	FSattributes_t* targetAT = (FSattributes_t*)malloc(sizeof(FSattributes_t)); 
	FSinqury_t* targetIQ = (FSinqury_t*)malloc(sizeof(FSinqury_t));
	assert(targetAT != NULL && targetIQ != NULL && "setSavInterest() allocation failed");

	pcplen = fread(g_tempbuff, sizeof(char), FILE_BUFF, f_accfile);
	fflush(f_accfile);
	g_tempbuff[pcplen] = '\0';
	pcp = g_tempbuff;
	pgb = g_buffer; 
	while (*pcp != '\0')
	{
		if (*pcp != '\n')
		{
			*pgb++ = *pcp++;
		}
		else
		{
			*pgb = '\0';
			//printf("%s\n", g_buffer);
			if (flag == 0)
			{
				AttOffset = strToFSatt(g_buffer, targetAT, AccNum);
				flag = 1;
			}
			else
			{
				strToFSiq(g_buffer, targetIQ, AccNum);
				inputYear = atoi(&(targetIQ->FS_date[0]));
				inputMonth = atoi(&(targetIQ->FS_date[5]));
				inputDay = atoi(&(targetIQ->FS_date[8]));
				if (inputYear == g_year && inputMonth == g_month && 
					inputDay == g_day && *(targetIQ->FS_income) == '0'&& 
					(strcmp(AccNum, targetIQ->FS_mynum) == 0))
				{ // 戚切 設 細嬢赤生檎 蟹亜奄
					free(targetAT);
					free(targetIQ);
					targetAT = NULL;
					targetIQ = NULL;

					fprintf(stdout, "%s good\n", AccNum);
					return 1; 
				}
			}
			pcp++;
			pgb = g_buffer;
			memset(g_buffer, '\0', BUFF_SIZE); // 焼艦檎 陥製牒.
		}
	} // 陥 達焼坐亀 蒸生檎
	remainService = atoi(targetAT->FS_remainService);
	if (remainService == 0) // 害精 奄娃 0戚檎 蒸蕉奄
	{
		free(targetAT);
		free(targetIQ);
		targetAT = NULL;
		targetIQ = NULL;

		fprintf(stdout, "%s no remain\n", AccNum);
		return 0;
	}//戚切 域至
	beforBal = atol(targetAT->FS_balance);
	interestRatio = atof(targetAT->FS_interest);
	afterBal = beforBal + (long)(beforBal * interestRatio / 100);
	
	
	
	if (temp != NULL)
	{
		free(temp);
		temp = NULL;
	}//紗失 床奄
	templen = sizeof(FSattributes_t) / sizeof(char) + 8;
	temp = (char*)malloc(sizeof(char) * templen);
	assert(temp != NULL && "setSavInterset allocation failed");

	sprintf(temp, "%s|%s|%s|%s|%d|%.1f|%ld|",
		targetAT->FS_name, targetAT->FS_mynum, targetAT->FS_money,
		targetAT->FS_Passwords, remainService - 1, interestRatio, afterBal);
	printf("%s\n", temp);

	//督析拭 床奄
	CurrentFileOffset = AttOffset;
	fseek(f_accfile, CurrentFileOffset, SEEK_SET);

	while (check != ' ' && check != '\n')
	{
		check = fgetc(f_accfile);
		CurrentFileOffset++;
	}
	CurrentFileOffset--;

	if (AttOffset > 0) // 掻娃拭 恩醤拝 凶
	{
		fseek(f_accfile, 0, SEEK_SET); //蒋拭依
		numOfBefore = fread(g_filebuff2, sizeof(char), AttOffset, f_accfile);
	}
	fseek(f_accfile, CurrentFileOffset, SEEK_SET);// 及拭依
	size_t numOfWords = fread(g_filebuff, sizeof(char), FILE_BUFF, f_accfile);
	//printf("g_filebuff:\n %s", g_filebuff);
	f_accfile = _wfreopen(g_wpath, L"w+", f_accfile);
	if (AttOffset > 0)
	{
		fwrite(g_filebuff2, sizeof(char), numOfBefore, f_accfile);
	}
	fwrite(temp, sizeof(char), strlen(temp), f_accfile);
	fflush(f_accfile);
	fwrite(g_filebuff, sizeof(char), numOfWords, f_accfile);
	fflush(f_accfile);

	free(temp);
	temp = NULL;

	//戚切 鎧蝕 床奄
	CurrentFileOffset = 0;
	fseek(f_accfile, CurrentFileOffset, SEEK_END);

	templen = sizeof(FSinqury_t) / sizeof(char) + 5;
	temp = (char*)malloc(sizeof(char) * templen);
	assert(temp != NULL && "setSavInterset allocation failed");

	sprintf(temp, "%d-%d-%d|%s|%s|0|%ld|\n",
		g_year, g_month, g_day, targetAT->FS_name, AccNum, afterBal);

	printf("%s\n", temp);

	fwrite(temp, sizeof(char), strlen(temp), f_accfile);
	fflush(f_accfile);

	free(temp);
	temp = NULL;
	
	fprintf(stdout, "%s bad\n", AccNum);
	return 0;
}
// 焼戚巨 掻差鞠澗走 溌昔杯艦陥.
int checkDupID(const char* ID)
{
	assert(ID != NULL && "ID is NULL");
	long CurrentFileOffset = 0;

	char* IDs = NULL;
	int i = 0;
	char* pbuf = NULL;
	char* pID = NULL;

	while (1)
	{
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_MemberFile);
		IDs = (char*)malloc(sizeof(char) * 17);
		assert(IDs != NULL && "IDs memory allocation is error");
		pbuf = g_buffer;
		pID = IDs;
		if (feof(f_MemberFile))
		{
			break;
		}
		while (*pbuf++ != '|');
		while (*pbuf != '|')
		{
			*pID++ = *pbuf++;
		}
		*pID = '\0';

		if (strcmp(ID, IDs) == 0)
		{
			free(IDs);
			IDs = NULL;
			return 1;
		}

		CurrentFileOffset = ftell(f_MemberFile);
	}
	if (IDs != NULL)
	{
		IDs = NULL;
		free(IDs);
	}
	return 0;
}
// 焼戚巨拭 背雁馬澗 搾腔腰硲亜 限澗走 溌昔杯艦陥.
int checkDupPW(const char* ID, const char* PW)
{
	assert(PW != NULL && "PW is NULL");
	long CurrentFileOffset = 0;

	char* PWs = NULL;
	int i = 0;
	char* pbuf = NULL;
	char* pPW = NULL;

	CurrentFileOffset = setBankByID(ID);
	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_MemberFile);

	PWs = (char*)malloc(sizeof(char) * 33);
	assert(PWs != NULL && "PWs memory allocation is error");
	pbuf = g_buffer;
	pPW = PWs;

	while (*pbuf++ != '|');
	while (*pbuf++ != '|');
	while (*pbuf != '|')
	{
		*pPW++ = *pbuf++;
	}
	*pPW = '\0';

	if (strcmp(PW, PWs) == 0)
	{
		free(PWs);
		PWs = NULL;
		return 1;
	}

	if (PWs != NULL)
	{
		free(PWs);
		PWs = NULL;
	}
	return 0;
}
// 焼戚巨稽 越稽忽 告滴 坪球 室特馬壱 益 匝 神覗実 鋼発 杯艦陥....蒸生檎 -1鋼発
int setBankByID(const char* ID)
{
	assert(ID != NULL && "ID is NULL");
	long CurrentFileOffset = 0;

	char* IDs = NULL;
	int IDNums = 0;
	int i = 0;
	char* pbuf = NULL;
	char* pID = NULL;
	int bankCode = 0;

	while (1)
	{
		fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_MemberFile);
		if (feof(f_MemberFile))
		{
			break;
		}
		IDs = (char*)malloc(sizeof(char) * 17);
		assert(IDs != NULL && "IDs memory allocation is error");
		pbuf = g_buffer;
		pID = IDs;

		while (*pbuf++ != '|');
		while (*pbuf != '|')
		{
			*pID++ = *pbuf++;
		}
		*pID = '\0';

		if (strcmp(ID, IDs) == 0)
		{
			while (*pbuf++ != '|');
			while (*pbuf++ != '|');
			bankCode = atoi(pbuf);
			assert((isdigit(bankCode) == 0 || bankCode == 0) && "get BankCode is failed");

			IDs = NULL;
			free(IDs);

			g_userBank = bankCode;
			return CurrentFileOffset;
		}
		CurrentFileOffset = ftell(f_MemberFile);
	}
	if (IDs != NULL)
	{
		IDs = NULL;
		free(IDs);
	}
	return -1;
}
// 域疎軒什闘 閲嬢紳 獄遁稽 紫遂切 社政 域疎戚硯 掻差昔走 溌昔 杯艦陥. 掻差戚檎 1鋼発 焼艦檎 0鋼発
int checkDupAN(const char* input)
{
	assert(input != NULL && "ID is NULL");

	long CurrentFileOffset = 0;
	int bDulpicate = 0;

	int ANlen = 0;
	char* pbuf = NULL;
	char* pbuftemp = NULL;

	for (int i = 0; i < g_allALANNums; i++)
	{
		for (int j = 0; j < g_userALNums; j++)
		{
			if (strcmp(g_allAccountsListAndName[0][i], g_userAccountsList[j]) == 0)
			{
				if (strcmp(g_allAccountsListAndName[1][i], input) == 0)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
// 焼戚巨稽 紫遂切 社政 域疎軒什闘 持失 域疎 鯵呪 鋼発
int setAccListByID_malloc(const char* ID)
{

	assert(ID != NULL && "ID is NULL");
	long CurrentFileOffset = 0;
	int bDulpicate = 0;

	char* IDs = NULL;
	int AccountsNums = 0;
	int i = 0;
	char* pbuf = NULL;
	char* pbuftemp = NULL;
	char* pID = NULL;

	CurrentFileOffset = setBankByID(ID);

	fseek(f_MemberFile, CurrentFileOffset, SEEK_SET);
	fgets(g_buffer, BUFF_SIZE, f_MemberFile);
	if (feof(f_MemberFile))
	{
		return 0;
	}
	pbuf = g_buffer;
	pID = IDs;
	for (int j = 0; j < 4; j++)
	{
		while (*pbuf++ != '|')
		{
			CurrentFileOffset++;
		}
	}
	pbuftemp = pbuf;
	while (*pbuf != '\0')
	{
		if (*pbuf++ == '|')
		{
			AccountsNums++;
		}
	}
	pbuf = pbuftemp;

	if (g_userAccountsList != NULL)
	{

		for (int h = 0; h < g_userALNums; h++)
		{
			free(g_userAccountsList[h]);
			g_userAccountsList[h] = NULL;
		}
		free(g_userAccountsList);
		g_userAccountsList = NULL;
	}
	g_userALNums = AccountsNums;

	if (g_userALNums != 0)
	{
		g_userAccountsList = (char**)malloc(sizeof(char*) * g_userALNums);
		assert(g_userAccountsList != NULL && "g_userAccountsList memory allocation is failed");
		for (int k = 0; k < g_userALNums; k++)
		{
			g_userAccountsList[k] = (char*)malloc(sizeof(char) * 8);
			assert(g_userAccountsList[k] != NULL && "g_userAccountsList[i] memory allocation is failed");
			for (int h = 0; h < 7; h++)
			{
				g_userAccountsList[k][h] = *pbuf++;
			}
			pbuf++;
			g_userAccountsList[k][7] = '\0';
			//printf("%s\n", g_userAccountsList[k]);
		}
		return g_userALNums;
	}
	return 0;
}
// 域疎軒什闘 督析 閲嬢辞 獄遁拭 隔奄. 域疎 鯵呪 鋼発
int setAccListOfAll_malloc()
{
	long CurrentFileOffset = 0;

	int i = 0;
	size_t tempnamelen = 0;
	int AccountNums = 0;
	char* piter = NULL;;
	char* pitertemp = NULL;

	while (1)// 域疎 鯵呪歯奄
	{
		fseek(f_AccountList, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_AccountList);
		//printf("%s", g_buffer);
		if (feof(f_AccountList))
		{
			break;
		}
		AccountNums++;
		CurrentFileOffset = ftell(f_AccountList);
	}

	if (g_allAccountsListAndName != NULL)
	{
		for (int k = 0; k < 2; k++)
		{
			for (int h = 0; h < g_allALANNums; h++)
			{
				free(g_allAccountsListAndName[k][h]);
				g_allAccountsListAndName[k][h] = NULL;
			}
			free(g_allAccountsListAndName[k]);
			g_allAccountsListAndName[k] = NULL;
		}
		free(g_allAccountsListAndName);
		g_allAccountsListAndName = NULL;
	}
	g_allALANNums = AccountNums;
	//printf("%d\n", g_allALANNums);

	g_allAccountsListAndName = (char***)malloc(sizeof(char**) * 2);
	assert(g_allAccountsListAndName != NULL && "g_allAcountsListAndName allocation failed");
	for (int j = 0; j < 2; j++)
	{
		g_allAccountsListAndName[j] = (char**)malloc(sizeof(char*) * g_allALANNums);
		assert(g_allAccountsListAndName[j] != NULL && "g_allAcountsListAndName allocation failed");
	}
	for (int k = 0; k < g_allALANNums; k++)
	{
		g_allAccountsListAndName[0][k] = (char*)malloc(sizeof(char) * 8);
		assert(g_allAccountsListAndName[1][k] != NULL && "g_allAcountsListAndName allocation failed");

	}
	CurrentFileOffset = 0;
	i = 0;
	while (i < g_allALANNums) // 域疎腰硲 獄遁拭 眼奄
	{
		tempnamelen = 0;
		fseek(f_AccountList, CurrentFileOffset, SEEK_SET);
		fgets(g_buffer, BUFF_SIZE, f_AccountList);
		if (feof(f_AccountList))
		{
			break;
		}
		piter = g_buffer;
		strncpy(g_allAccountsListAndName[0][i], g_buffer, 7);
		g_allAccountsListAndName[0][i][7] = '\0';
		//printf("%s\n", g_allAccountsListAndName[0][i]);

		while (*piter++ != '|');
		pitertemp = piter;
		while (*piter++ != '|')
		{
			tempnamelen++;
		}
		g_allAccountsListAndName[1][i] = (char*)malloc(sizeof(char) * (tempnamelen + 1));
		assert(g_allAccountsListAndName[1][i] != NULL && "g_allAcountsListAndName allocation failed");

		strncpy(g_allAccountsListAndName[1][i], pitertemp, tempnamelen);
		g_allAccountsListAndName[1][i][tempnamelen] = '\0';
		//printf("%s\n", g_allAccountsListAndName[1][i]);

		CurrentFileOffset = ftell(f_AccountList);
		i++;
	}
	return g_allALANNums;

}
// 域疎 展脊 鋼発
eAccType getAccType(const char* AccNum)
{
	switch (AccNum[2]) // 展脊端滴
	{
	case '1': // 脊窒榎精 域疎原陥
		return T1;
		break;
	case '2': // 森榎精 馬蟹
		return T2;
		break;
	case'3': // 旋榎亀 析舘 馬蟹
		return T3;
		break;
	default:
		return 4;
	}
}
