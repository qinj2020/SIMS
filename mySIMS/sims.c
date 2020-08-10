#include "sims.h"

void readConfigFile(char *argv, char* str1, char* str2)
{
	FILE* fp_configure = fopen(argv, "r");	//打开配置文件
	if (fp_configure == NULL)
	{
		perror("fopen_configure");
		systemExit();
	}
	fgets(str1, PATH_LEN, fp_configure);
	str1[strlen(str1) - 1] = 0;				//去掉读到的\n
	//fseek(fp_configure, 0, SEEK_CUR);
	fgets(str2, PATH_LEN, fp_configure);
	fclose(fp_configure);
}

void readStuFile(char* str1, pL_STU* linkStu)
{
	FILE *fp_stu = fopen(str1, "r");			//打开学生文件加载数据
	if (fp_stu == NULL)
	{
		perror("fopen_stu");
		systemExit();
	}
	pLN_STU LN_pnew = (pLN_STU)calloc(1, sizeof(LN_STU));	//申请新链表结点空间
	if (LN_pnew == NULL)
	{
		perror("LN_pnew_stu calloc");
		systemExit();
	}
	pSTU STU_pnew = (pSTU)calloc(1, sizeof(STU));		//申请stu结构体空间
	if (STU_pnew == NULL)
	{
		perror("STU_pnew calloc");
		systemExit();
	}
	LN_pnew->date = STU_pnew;
	while (fscanf(fp_stu, "%s%s %c%d%lf%lf%lf%s", STU_pnew->stu_id, STU_pnew->stu_name, &(STU_pnew->stu_sex), &(STU_pnew->stu_age), &(STU_pnew->stu_score1), &(STU_pnew->stu_score2), &(STU_pnew->stu_score3), STU_pnew->stu_passwd) != EOF)
	{
		addLinkStu_tail(*linkStu, LN_pnew);
		LN_pnew = (pLN_STU)calloc(1, sizeof(LN_STU));	//申请新结点空间
		if (LN_pnew == NULL)
		{
			perror("LN_pnew_stu calloc");
			systemExit();
		}
		STU_pnew = (pSTU)calloc(1, sizeof(STU));
		if (STU_pnew == NULL)
		{
			perror("STU_pnew calloc");
			systemExit();
		}
		LN_pnew->date = STU_pnew;
	}
	free(LN_pnew);		//释放没读入数据申请的空间
	free(STU_pnew);
	fclose(fp_stu);
	//linkPrint_stu(*linkStu);
}

void readUserFile(char* str2, pL_USER* linkUser)
{
	FILE *fp_user = fopen(str2, "r");
	if (fp_user == NULL)
	{
		perror("fopen_user");
		systemExit();
	}
	pLN_USER LN_pnew_user = (pLN_USER)calloc(1, sizeof(LN_USER));	//申请新链表结点空间
	if (LN_pnew_user == NULL)
	{
		perror("LN_pnew_user calloc");
		systemExit();
	}
	pUSER USER_pnew = (pUSER)calloc(1, sizeof(USER));			//申请user结构体空间
	if (USER_pnew == NULL)
	{
		perror("USER_pnew calloc");
		systemExit();
	}
	LN_pnew_user->date = USER_pnew;
	while (fscanf(fp_user, "%s%s%d", USER_pnew->user_name, USER_pnew->user_passwd, &(USER_pnew->user_limit)) != EOF)
	{
		addLinkUser_tail(*linkUser, LN_pnew_user);
		LN_pnew_user = (pLN_USER)calloc(1, sizeof(LN_USER));	//申请新结点空间
		if (LN_pnew_user == NULL)
		{
			perror("LN_pnew_user calloc");
			systemExit();
		}
		USER_pnew = (pUSER)calloc(1, sizeof(USER));
		if (USER_pnew == NULL)
		{
			perror("USER_pnew calloc");
			systemExit();
		}
		LN_pnew_user->date = USER_pnew;
	}
	free(LN_pnew_user);		//释放没读入数据申请的空间
	free(USER_pnew);
	fclose(fp_user);
	//linkPrint_user(*linkUser);
}

void systemInit(pL_STU* linkStu, pL_USER* linkUser, char* argv, char* str1, char* str2)
{
	printf("系统正在初始化......\n");
	readConfigFile(argv, str1, str2);
	*linkStu = creatLink_stu(linkStu);		//传入的是systemInit函数里linkStu的值，无法在creatLink函数中改变其内容，接收返回值
	creatLink_user(&linkUser);				//传入地址，可以改变其内容
	readStuFile(str1, linkStu);
	readUserFile(str2, linkUser);
	printf("系统初始化成功\n");
}

pL_STU creatLink_stu(pL_STU* linkStu)
{
	*linkStu = (pL_STU)calloc(1, sizeof(L_STU));	//创建链表指针
	if (*linkStu == NULL)
	{
		perror("linkStu calloc");
		systemExit();
	}
	pLN_STU headNode = (pLN_STU)calloc(1, sizeof(LN_STU));	//创建头结点
	if (headNode == NULL)
	{
		perror("stu headNode calloc");
		systemExit();
	}
	(*linkStu)->head = headNode;
	(*linkStu)->tail = headNode;
	return *linkStu;
}

pL_USER creatLink_user(pL_USER** linkUser)
{
	**linkUser = (pL_USER)calloc(1, sizeof(L_USER));	//创建链表指针
	if (**linkUser == NULL)
	{
		perror("linkUser calloc");
		systemExit();
	}
	pLN_USER headNode = (pLN_USER)calloc(1, sizeof(LN_USER));	//创建头结点
	if (headNode == NULL)
	{
		perror("user headNode calloc");
		systemExit();
	}
	(**linkUser)->head = headNode;
	(**linkUser)->tail = headNode;
	return **linkUser;
}

pL_STU addLinkStu_tail(pL_STU linkStu, pLN_STU pnew)
{
	if (linkStu->head->next == NULL)
	{
		linkStu->head->next = pnew;
	}
	linkStu->tail->next = pnew;
	linkStu->tail = pnew;
	linkStu->num_stu++;
	return linkStu;
}

void linkPrint_stu(pL_STU linkStu)
{
	char sex[5] = { 0 };
	pLN_STU p = linkStu->head->next;
	system("cls");
	for (int i = 0; i < linkStu->num_stu; i++)
	{
		memset(sex, 0, sizeof(sex));
		if (p->date->stu_sex == 'f')
		{
			strcpy(sex, "女");
		}
		else
		{
			strcpy(sex, "男");
		}
		printf("%s\t%-12s\t%s\t%d\t%5.2lf\t%5.2lf\t%5.2lf\n", p->date->stu_id, p->date->stu_name, sex, p->date->stu_age, p->date->stu_score1, p->date->stu_score2, p->date->stu_score3);
		p = p->next;
	}
}

void linkPrint_user(pL_USER linkUser)
{
	pLN_USER p = linkUser->head->next;
	for (int i = 0; i < linkUser->num_user; i++)
	{
		printf("%s\t%s\t%d\n", p->date->user_name, p->date->user_passwd, p->date->user_limit);
		p = p->next;
	}
}
void linkPrint_userAccount(pL_USER linkUser)
{
	char str[20] = { 0 };
	pLN_USER p = linkUser->head->next;
	printf("用户名\t权限\n");
	for (int i = 0; i < linkUser->num_user; i++)
	{
		memset(str, 0, sizeof(str));
		if (p->date->user_limit == 1)
		{
			strcpy(str, "管理员");
		}
		else
		{
			strcpy(str, "普通用户");
		}
		printf("%s\t%s\n", p->date->user_name, str);
		p = p->next;
	}
}
pL_USER addLinkUser_tail(pL_USER linkUser, pLN_USER pnew)
{
	if (linkUser->head->next == NULL)
	{
		linkUser->head->next = pnew;
	}
	linkUser->tail->next = pnew;
	linkUser->tail = pnew;
	linkUser->num_user++;
	return linkUser;
}

void systemExit()
{
	system("cls");
	printf("感谢使用学生信息管理系统\n");
	exit(0);
}

void logon_menu()
{
	system("cls");
	printf("--------------------------------------------------------------\n");
	printf("******************欢迎使用学生信息管理系统********************\n");
	printf("--------------------------------------------------------------\n");
	printf("请选择登陆方式：\n");
	printf("[1]->学生登陆\n");
	printf("[2]->教师登陆\n");
	printf("[0]->退出系统\n");
}

int checkStuId(pL_STU linkStu, pSTU stu_now)
{
	char str[STU_ID_LEN] = { 0 };
	printf("请输入学号：");
	scanf("%s", str);
	pLN_STU p = linkStu->head->next;
	for (int i = 0; i < linkStu->num_stu; i++)
	{
		if (strcmp(str, p->date->stu_id) == 0)
		{
			strcpy(stu_now->stu_passwd, p->date->stu_passwd);
			stu_now->stu_age = p->date->stu_age;
			strcpy(stu_now->stu_id, p->date->stu_id);
			strcpy(stu_now->stu_name, p->date->stu_name);
			stu_now->stu_sex = p->date->stu_sex;
			stu_now->stu_score1 = p->date->stu_score1;
			stu_now->stu_score2 = p->date->stu_score2;
			stu_now->stu_score3 = p->date->stu_score3;
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//int checkStuPassWd(pL_STU linkStu, char* passWd)
//{
//	pLN_STU p = linkStu->head->next;
//	for (int i = 0; i < linkStu->num_stu; i++)
//	{
//		if (strcmp(passWd, p->date->stu_passwd) == 0)
//		{
//			return 1;
//		}
//		p = p->next;
//	}
//	return 0;
//}

char* getPassWd(char* passWd)
{
	int i = 0;
	char c;
	printf("请输入密码：");
	while ((c = getch()) != '\r')		//读到的\n变成\r了
	{
		if (c == '\b')
		{
			printf("\b \b");
			i--;
			passWd[i] = 0;
			continue;
		}
		else
		{
			passWd[i] = c;
			printf("*");
		}
		i++;
	}
}

int checkUserName(pL_USER linkUser, pUSER user_now)
{
	char str[NAME_LEN] = { 0 };
	printf("请输入用户名：");
	scanf("%s", str);
	pLN_USER p = linkUser->head->next;
	for (int i = 0; i < linkUser->num_user; i++)
	{
		if (strcmp(str, p->date->user_name) == 0)
		{
			strcpy(user_now->user_passwd, p->date->user_passwd);
			user_now->user_limit = p->date->user_limit;
			strcpy(user_now->user_name, p->date->user_name);
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//int checkUserPassWd(pL_USER linkUser, char* passWd)
//{
//	pLN_USER p = linkUser->head->next;
//	for (int i = 0; i < linkUser->num_user; i++)
//	{
//		if (strcmp(passWd, p->date->user_passwd) == 0)
//		{
//			return 1;
//		}
//		p = p->next;
//	}
//	return 0;
//}

int logon(pL_STU linkStu, pL_USER linkUser, pSTU stu_now, pUSER user_now)
{
	int n;
	int ret;
	char tmp[PASSWD_LEN] = { 0 };
	printf("请输入一个数字：");
	while (scanf("%d", &n) != EOF)
	{
		if (n == 1)
		{
			system("cls");
			while ((ret = checkStuId(linkStu, stu_now))==0)
			{	
				printf("账号不存在，请重新输入\n");
			}
			getPassWd(tmp);
			while (strcmp(tmp,stu_now->stu_passwd) != 0)
			{
				printf("\n密码错误！请重新输入\n");
				fflush(stdin);
				memset(tmp, 0, sizeof(tmp));
				getPassWd(tmp);
			}
			printf("\n登陆成功\n");
			return 1;
		}
		else if (n == 2)
		{
			system("cls");
			while ((ret = checkUserName(linkUser, user_now)) == 0)
			{
				printf("账号不存在，请重新输入\n");
				fflush(stdin);
			}
			getPassWd(tmp);
			while (strcmp(tmp, user_now->user_passwd) != 0)
			{
				printf("\n密码错误！请重新输入\n");
				fflush(stdin);
				memset(tmp, 0, sizeof(tmp));
				getPassWd(tmp);
			}
			printf("\n登陆成功\n");
			if (user_now->user_limit == 0)
			{
				return 2;
			}
			else if (user_now->user_limit == 1)
			{
				return 3;
			}
		}
		else if (n == 0)
		{
			systemExit();
		}
		else
		{
			printf("没有这个选项，请重新输入\n");
			fflush(stdin);
		}
	}
}

void head_menu()
{
	system("cls");
	printf("--------------------------------------------------------------\n");
	printf("******************欢迎使用学生信息管理系统********************\n");
	printf("--------------------------------------------------------------\n");
}
void stu_menu()
{
	head_menu();
	printf("[1]->查询信息\n");
	printf("[2]->修改密码\n");
	printf("[0]->退出系统\n");
}
void user_menu()
{
	head_menu();
	printf("[1]->查询学生信息\n");
	printf("[2]->修改学生信息\n");
	printf("[3]->增加学生用户\n");
	printf("[4]->删除学生用户\n");
	printf("[5]->修改密码\n");
	printf("[0]->退出系统\n");
}
void search_menu()
{
	head_menu();
	printf("[1]->通过学号查找\n");
	printf("[2]->通过姓名查找\n");
	printf("[3]->显示全部\n");
	printf("[0]->返回上一层\n");
}
void changeStuImf_menu()
{
	head_menu();
	printf("[1]->通过学号查找修改\n");
	printf("[2]->通过姓名查找修改\n");
	printf("[0]->返回上一层\n");
}
void changeStuImf_menu2()
{
	system("cls");
	printf("请选择要修改的内容：\n");
	printf("[1]->学号\n");
	printf("[2]->姓名\n");
	printf("[3]->性别(男->输入'm',女->输入'f')\n");
	printf("[4]->年龄\n");
	printf("[5]->成绩1\n");
	printf("[6]->成绩2\n");
	printf("[7]->成绩3\n");
	printf("[8]->密码\n");
	printf("[0]->返回上一层\n");
}
void admin_menu()
{
	head_menu();
	printf("[1]->查询学生信息\n");
	printf("[2]->修改学生信息\n");
	printf("[3]->增加学生用户\n");
	printf("[4]->删除学生用户\n");
	printf("[5]->查询用户信息\n");
	printf("[6]->修改用户信息\n");
	printf("[7]->增加普通用户\n");
	printf("[8]->删除普通用户\n");
	printf("[0]->退出系统\n");
}

void printStuImf(pSTU stu_now)
{
	char sex[5] = { 0 };
	system("cls");
	if (stu_now == 'f')
	{
		strcpy(sex, "女");
	}
	else
	{
		strcpy(sex, "男");
	}
	printf("学号\t姓名\t性别\t年龄\t成绩1\t成绩2\t成绩3\n");
	printf("%s\t%-s\t%s\t%d\t%5.2lf\t%5.2lf\t%5.2lf\n", stu_now->stu_id, stu_now->stu_name, sex, stu_now->stu_age, stu_now->stu_score1, stu_now->stu_score2, stu_now->stu_score3);
}

void changeStuPassWd(pL_STU linkStu, pSTU stu_now)
{
	char str1[PASSWD_LEN] = { 0 };
	char str2[PASSWD_LEN] = { 0 };
	system("cls");
	while (1)
	{
		printf("新密码：\n");
		getPassWd(str1);
		printf("\n重复一次确认！\n");
		getPassWd(str2);
		if (strcmp(str1, str2) == 0)
		{
			pLN_STU p = linkStu->head->next;
			for (int i = 0; i < linkStu->num_stu; i++)
			{
				if (strcmp(p->date->stu_id, stu_now->stu_id) == 0)
				{
					strcpy(p->date->stu_passwd, str1);
					strcpy(stu_now->stu_passwd, str1);
				}
				p = p->next;
			}
			printf("\n修改成功！\n");
			system("pause");
			break;
		}
		else
		{
			printf("\n前后不一致！请重新输入\n");
			fflush(stdin);
			memset(str1, 0, sizeof(str1));
			memset(str2, 0, sizeof(str2));
		}
	}
}

void save_stu(pL_STU linkStu, char* str1)
{
	FILE* fp_stu = fopen(str1, "w+");
	if (fp_stu == NULL)
	{
		perror("fp_stu fopen");
		return;
	}
	pLN_STU p = linkStu->head->next;
	for (int i = 0; i < linkStu->num_stu; i++)
	{
		fprintf(fp_stu, "%s\t%s\t%c\t%d\t%5.2lf\t%5.2lf\t%5.2lf\t%s\n", p->date->stu_id, p->date->stu_name, p->date->stu_sex, p->date->stu_age, p->date->stu_score1, p->date->stu_score2, p->date->stu_score3, p->date->stu_passwd);
		p = p->next;
	}
	fclose(fp_stu);
}

void save_user(pL_STU linkStu, char* str1, pL_USER linkUser, char* str2)
{
	save_stu(linkStu, str1);
	FILE* fp_user = fopen(str2, "w+");
	if (fp_user == NULL)
	{
		perror("fp_user fopen");
		return;
	}
	pLN_USER p = linkUser->head->next;
	for (int i = 0; i < linkUser->num_user; i++)
	{
		fprintf(fp_user, "%s\t%s\t%d\n", p->date->user_name, p->date->user_passwd, p->date->user_limit);
		p = p->next;
	}
	fclose(fp_user);
}

pSTU locatStuId(pL_STU linkStu, char* str)
{
	system("cls");
	printf("请输入学号：");
	scanf("%s", str);
	pLN_STU p = linkStu->head->next;
	for (int i = 0; i < linkStu->num_stu; i++)
	{
		if (strcmp(p->date->stu_id, str) == 0)
		{
			//printStuImf(p->date);
			return p->date;
		}
		p = p->next;
	}
	printf("输入的学号不存在\n");
	return NULL;
}
pSTU locatStuName(pL_STU linkStu, char* str)
{
	system("cls");
	printf("请输入姓名：");
	scanf("%s", str);
	pLN_STU p = linkStu->head->next;
	for (int i = 0; i < linkStu->num_stu; i++)
	{
		if (strcmp(p->date->stu_name, str) == 0)
		{
			//printStuImf(p->date);
			return p->date;
		}
		p = p->next;
	}
	printf("查无此人\n");
	return	NULL;
}
int changeStuImf(pL_STU linkStu,pSTU pstu)
{
	int n;
	char str[PASSWD_LEN] = { 0 };
	while (1)
	{
		changeStuImf_menu2();
		printf("请请输入一个数字：");
		while (scanf("%d", &n) != EOF)
		{
			if (n == 1)
			{
				system("cls");
				printf("请输入新学号：");
				while (scanf("%s", str) != EOF)
				{
					if (isExistStuId(linkStu, str)==0)
					{
						break;
					}
					else
					{
						printf("学号已存在，请重新输入\n");
						fflush(stdin);
					}
				}
				strcpy(pstu->stu_id, str);
				printf("修改成功\n");
				system("pause");
				break;
			}
			else if (n == 2)
			{
				system("cls");
				printf("请输入新姓名：");
				scanf("%s", str);
				strcpy(pstu->stu_name, str);
				printf("修改成功\n");
				system("pause");
				break;
			}
			else if (n == 3)
			{
				char c;
				system("cls");
				printf("请输入修改后的性别(男->输入m; 女->输入f)：");
				scanf(" %c", &c);
				pstu->stu_sex = c;
				printf("修改成功\n");
				system("pause");
				break;
			}
			else if (n == 4)
			{
				int age;
				system("cls");
				printf("请输入修改后的年龄：");
				scanf("%d", &age);
				pstu->stu_age = age;
				printf("修改成功\n");
				system("pause");
				break;
			}
			else if (n == 5)
			{
				double n;
				system("cls");
				printf("请输入修改后的成绩1：");
				scanf("%lf", &n);
				pstu->stu_score1 = n;
				printf("修改成功\n");
				system("pause");
				break;
			}
			else if (n == 6)
			{
				double n;
				system("cls");
				printf("请输入修改后的成绩2：");
				scanf("%lf", &n);
				pstu->stu_score2 = n;
				printf("修改成功\n");
				system("pause");
				break;
			}
			else if (n == 7)
			{
				double n;
				system("cls");
				printf("请输入修改后的成绩3：");
				scanf("%lf", &n);
				pstu->stu_score3 = n;
				printf("修改成功\n");
				system("pause");
				break;
			}
			else if (n == 8)
			{
				char str1[PASSWD_LEN] = { 0 };
				char str2[PASSWD_LEN] = { 0 };
				system("cls");
				while (1)
				{
					printf("新密码：\n");
					getPassWd(str1);
					printf("\n重复一次确认！\n");
					getPassWd(str2);
					if (strcmp(str1, str2) == 0)
					{
						strcpy(pstu->stu_passwd, str1);
						printf("\n修改成功！\n");
						system("pause");
						break;
					}
					else
					{
						printf("\n前后不一致！请重新输入\n");
						fflush(stdin);
						memset(str1, 0, sizeof(str1));
						memset(str2, 0, sizeof(str2));
					}
				}
				break;
			}
			else if (n == 0)
			{
				break;
			}
			else
			{
				printf("没有这个选项，请重新输入\n");
				fflush(stdin);
			}
		}
		if (n == 0)
		{
			break;
		}
	}
}

int isExistStuId(pL_STU linkStu, char* str)
{
	pLN_STU p = linkStu->head->next;
	for (int i = 0; i < linkStu->num_stu; i++)
	{
		if (strcmp(p->date->stu_id, str) == 0)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

pL_STU addLinkStu_sort(pL_STU linkStu, pSTU pnew)
{
	pLN_STU p = linkStu->head->next, per = linkStu->head;
	pLN_STU newNode = (pLN_STU)calloc(1, sizeof(LN_STU));
	pSTU newStu = (pSTU)calloc(1, sizeof(STU));
	if (newNode == NULL)
	{
		printf("newNode calloc error\n");
		return NULL;
	}
	if (newStu == NULL)
	{
		printf("newNStu calloc error\n");
		return NULL;
	}
	newNode->date = newStu;
	*(newNode->date) = *pnew;
	while (p)
	{
		if (strcmp(p->date->stu_id, newNode->date->stu_id) > 0)
		{
			per->next = newNode;
			newNode->next = p;
		}
		per = p;
		p = p->next;
	}
	if (p == NULL)
	{
		addLinkStu_tail(linkStu, newNode);
	}
}

void delStu(pL_STU linkStu)
{
	system("cls");
	printf("[1]->按学号删除\n");
	printf("[2]->删除全部\n");
	printf("[0]->返回上一层\n");
	int n;
	printf("请选择一个数字：");
	while (1)
	{
		scanf("%d", &n);
		if (n == 1)
		{
			char str[STU_ID_LEN];
			system("cls");
			printf("请输入要删除学生的学号：");
			scanf("%s", str);
			if (delStuID(linkStu, str))
			{
				printf("删除成功...\n");
				system("pause");
			}
			else
			{
				printf("学号不存在，删除失败...\n");
				system("pause");
			}
			break;
		}
		else if(n==2)
		{
			char c;
			system("cls");
			printf("是否确认删除全部学生信息!!!(确定输入y,其他任意键：否)\n");
			fflush(stdin);
			scanf(" %c", &c);
			if (c == 'y')
			{
				delStuAll(linkStu);
				printf("删除成功...\n");
				system("pause");
			}
			break;
		}
		else if(n==0)
		{
			break;
		}
		else
		{
			printf("没有这个选项，请重新输入\n");
			fflush(stdin);
		}
	}
}

int delStuID(pL_STU linkStu, char* str)
{
	pLN_STU per = linkStu->head, pcur = linkStu->head->next;
	while (pcur)
	{
		if (strcmp(pcur->date->stu_id, str) == 0)
		{
			per->next = pcur->next;
			linkStu->num_stu--;
			break;
		}
		per = pcur;
		pcur = pcur->next;
	}
	if (pcur == NULL)
	{
		return 0;
	}
	else
	{
		free(pcur->date);	//释放结构体空间
		free(pcur);			//释放链表节点空间
		return 1;
	}
}

void delStuAll(pL_STU linkStu)
{
	pLN_STU pcur = linkStu->head->next, ptmp;
	while (pcur)
	{
		ptmp = pcur;
		pcur = pcur->next;
		free(ptmp->date);	//释放结构体空间
		free(ptmp);			//释放链表节点空间
		linkStu->num_stu--;
	}
}
void changeUserPassWd(pL_USER linkUser, pUSER user_now)
{
	char str1[PASSWD_LEN] = { 0 };
	char str2[PASSWD_LEN] = { 0 };
	system("cls");
	while (1)
	{
		printf("新密码：\n");
		getPassWd(str1);
		printf("\n重复一次确认！\n");
		getPassWd(str2);
		if (strcmp(str1, str2) == 0)
		{
			pLN_USER p = linkUser->head->next;
			for (int i = 0; i < linkUser->num_user; i++)
			{
				if (strcmp(p->date->user_name, user_now->user_name) == 0)
				{
					strcpy(p->date->user_passwd, str1);
					strcpy(user_now->user_passwd, str1);
				}
				p = p->next;
			}
			printf("\n修改成功！\n");
			system("pause");
			break;
		}
		else
		{
			printf("\n前后不一致！请重新输入\n");
			fflush(stdin);
			memset(str1, 0, sizeof(str1));
			memset(str2, 0, sizeof(str2));
		}
	}
}

pUSER locatUserName(pL_USER linkUser, const char* str)
{
	pLN_USER p = linkUser->head->next;
	for (int i = 0; i < linkUser->num_user; i++)
	{
		if (strcmp(p->date->user_name, str) == 0)
		{
			return p->date;
		}
		p = p->next;
	}
	return NULL;
}
void changeUser_menu()
{
	printf("[1]->修改用户姓名\n");
	printf("[2]->修改用户密码\n");
	printf("[0]->返回上一层\n");
}
void changeUserName(pUSER pUser)
{
	char strName[NAME_LEN] = { 0 };
	printf("请输入新用户名：\n");
	scanf("%s", strName);
	memset(pUser->user_name, 0, sizeof(pUser->user_name));
	strcpy(pUser->user_name, strName);
}
void deleteUser(pL_USER linkUser)
{
	int n = 0;
	char name[NAME_LEN] = { 0 };
	while (1)
	{
		system("cls");
		printf("[1]->按姓名删除用户\n");
		printf("[2]->删除全部用户\n");
		printf("[0]->返回上一层\n");
		printf("请输入一个数字\n");
		while (scanf("%d", &n))
		{
			if (n == 1)
			{
				system("cls");
				printf("请输入要删除的用户姓名：\n");
				scanf("%s", name);
				if (delUserName(linkUser, name))
				{
					printf("删除成功...\n");
				}
				else
				{
					printf("查无此人，删除失败...\n");
				}
				system("pause");
				break;
			}
			else if (n == 2)
			{
				char c;
				system("cls");
				printf("是否确认删除全部用户!!!(确定输入y,其他任意键：否)\n");
				fflush(stdin);
				scanf(" %c", &c);
				if (c == 'y')
				{
					delUserAll(linkUser);
					printf("删除成功...\n");
					system("pause");
				}
				break;
			}
			else if (n == 0)
			{
				break;
			}
			else
			{
				printf("没有这个选项，请重新输入\n");
				fflush(stdin);
			}
		}
		if (n == 0)
		{
			break;
		}
	}
}
int delUserName(pL_USER linkUser, char *name)
{
	pLN_USER p = linkUser->head->next, pre = linkUser->head;
	for (int i = 0; i < linkUser->num_user; i++)
	{
		if (strcmp(p->date->user_name, name) == 0)
		{
			pre->next = p->next;
			free(p->date);
			free(p);
			linkUser->num_user--;
			return 1;
		}
		pre = p;
		p = p->next;
	}
	return 0;
}
void delUserAll(pL_USER linkUser)
{
	pLN_USER pcur = linkUser->head->next, ptmp;
	while (pcur)
	{
		ptmp = pcur;
		pcur = pcur->next;
		free(ptmp->date);	//释放结构体空间
		free(ptmp);			//释放链表节点空间
		linkUser->num_user--;
	}
}