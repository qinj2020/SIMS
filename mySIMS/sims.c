#include "sims.h"

void readConfigFile(char *argv, char* str1, char* str2)
{
	FILE* fp_configure = fopen(argv, "r");	//�������ļ�
	if (fp_configure == NULL)
	{
		perror("fopen_configure");
		systemExit();
	}
	fgets(str1, PATH_LEN, fp_configure);
	str1[strlen(str1) - 1] = 0;				//ȥ��������\n
	//fseek(fp_configure, 0, SEEK_CUR);
	fgets(str2, PATH_LEN, fp_configure);
	fclose(fp_configure);
}

void readStuFile(char* str1, pL_STU* linkStu)
{
	FILE *fp_stu = fopen(str1, "r");			//��ѧ���ļ���������
	if (fp_stu == NULL)
	{
		perror("fopen_stu");
		systemExit();
	}
	pLN_STU LN_pnew = (pLN_STU)calloc(1, sizeof(LN_STU));	//������������ռ�
	if (LN_pnew == NULL)
	{
		perror("LN_pnew_stu calloc");
		systemExit();
	}
	pSTU STU_pnew = (pSTU)calloc(1, sizeof(STU));		//����stu�ṹ��ռ�
	if (STU_pnew == NULL)
	{
		perror("STU_pnew calloc");
		systemExit();
	}
	LN_pnew->date = STU_pnew;
	while (fscanf(fp_stu, "%s%s %c%d%lf%lf%lf%s", STU_pnew->stu_id, STU_pnew->stu_name, &(STU_pnew->stu_sex), &(STU_pnew->stu_age), &(STU_pnew->stu_score1), &(STU_pnew->stu_score2), &(STU_pnew->stu_score3), STU_pnew->stu_passwd) != EOF)
	{
		addLinkStu_tail(*linkStu, LN_pnew);
		LN_pnew = (pLN_STU)calloc(1, sizeof(LN_STU));	//�����½��ռ�
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
	free(LN_pnew);		//�ͷ�û������������Ŀռ�
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
	pLN_USER LN_pnew_user = (pLN_USER)calloc(1, sizeof(LN_USER));	//������������ռ�
	if (LN_pnew_user == NULL)
	{
		perror("LN_pnew_user calloc");
		systemExit();
	}
	pUSER USER_pnew = (pUSER)calloc(1, sizeof(USER));			//����user�ṹ��ռ�
	if (USER_pnew == NULL)
	{
		perror("USER_pnew calloc");
		systemExit();
	}
	LN_pnew_user->date = USER_pnew;
	while (fscanf(fp_user, "%s%s%d", USER_pnew->user_name, USER_pnew->user_passwd, &(USER_pnew->user_limit)) != EOF)
	{
		addLinkUser_tail(*linkUser, LN_pnew_user);
		LN_pnew_user = (pLN_USER)calloc(1, sizeof(LN_USER));	//�����½��ռ�
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
	free(LN_pnew_user);		//�ͷ�û������������Ŀռ�
	free(USER_pnew);
	fclose(fp_user);
	//linkPrint_user(*linkUser);
}

void systemInit(pL_STU* linkStu, pL_USER* linkUser, char* argv, char* str1, char* str2)
{
	printf("ϵͳ���ڳ�ʼ��......\n");
	readConfigFile(argv, str1, str2);
	*linkStu = creatLink_stu(linkStu);		//�������systemInit������linkStu��ֵ���޷���creatLink�����иı������ݣ����շ���ֵ
	creatLink_user(&linkUser);				//�����ַ�����Ըı�������
	readStuFile(str1, linkStu);
	readUserFile(str2, linkUser);
	printf("ϵͳ��ʼ���ɹ�\n");
}

pL_STU creatLink_stu(pL_STU* linkStu)
{
	*linkStu = (pL_STU)calloc(1, sizeof(L_STU));	//��������ָ��
	if (*linkStu == NULL)
	{
		perror("linkStu calloc");
		systemExit();
	}
	pLN_STU headNode = (pLN_STU)calloc(1, sizeof(LN_STU));	//����ͷ���
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
	**linkUser = (pL_USER)calloc(1, sizeof(L_USER));	//��������ָ��
	if (**linkUser == NULL)
	{
		perror("linkUser calloc");
		systemExit();
	}
	pLN_USER headNode = (pLN_USER)calloc(1, sizeof(LN_USER));	//����ͷ���
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
			strcpy(sex, "Ů");
		}
		else
		{
			strcpy(sex, "��");
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
	printf("�û���\tȨ��\n");
	for (int i = 0; i < linkUser->num_user; i++)
	{
		memset(str, 0, sizeof(str));
		if (p->date->user_limit == 1)
		{
			strcpy(str, "����Ա");
		}
		else
		{
			strcpy(str, "��ͨ�û�");
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
	printf("��лʹ��ѧ����Ϣ����ϵͳ\n");
	exit(0);
}

void logon_menu()
{
	system("cls");
	printf("--------------------------------------------------------------\n");
	printf("******************��ӭʹ��ѧ����Ϣ����ϵͳ********************\n");
	printf("--------------------------------------------------------------\n");
	printf("��ѡ���½��ʽ��\n");
	printf("[1]->ѧ����½\n");
	printf("[2]->��ʦ��½\n");
	printf("[0]->�˳�ϵͳ\n");
}

int checkStuId(pL_STU linkStu, pSTU stu_now)
{
	char str[STU_ID_LEN] = { 0 };
	printf("������ѧ�ţ�");
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
	printf("���������룺");
	while ((c = getch()) != '\r')		//������\n���\r��
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
	printf("�������û�����");
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
	printf("������һ�����֣�");
	while (scanf("%d", &n) != EOF)
	{
		if (n == 1)
		{
			system("cls");
			while ((ret = checkStuId(linkStu, stu_now))==0)
			{	
				printf("�˺Ų����ڣ�����������\n");
			}
			getPassWd(tmp);
			while (strcmp(tmp,stu_now->stu_passwd) != 0)
			{
				printf("\n�����������������\n");
				fflush(stdin);
				memset(tmp, 0, sizeof(tmp));
				getPassWd(tmp);
			}
			printf("\n��½�ɹ�\n");
			return 1;
		}
		else if (n == 2)
		{
			system("cls");
			while ((ret = checkUserName(linkUser, user_now)) == 0)
			{
				printf("�˺Ų����ڣ�����������\n");
				fflush(stdin);
			}
			getPassWd(tmp);
			while (strcmp(tmp, user_now->user_passwd) != 0)
			{
				printf("\n�����������������\n");
				fflush(stdin);
				memset(tmp, 0, sizeof(tmp));
				getPassWd(tmp);
			}
			printf("\n��½�ɹ�\n");
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
			printf("û�����ѡ�����������\n");
			fflush(stdin);
		}
	}
}

void head_menu()
{
	system("cls");
	printf("--------------------------------------------------------------\n");
	printf("******************��ӭʹ��ѧ����Ϣ����ϵͳ********************\n");
	printf("--------------------------------------------------------------\n");
}
void stu_menu()
{
	head_menu();
	printf("[1]->��ѯ��Ϣ\n");
	printf("[2]->�޸�����\n");
	printf("[0]->�˳�ϵͳ\n");
}
void user_menu()
{
	head_menu();
	printf("[1]->��ѯѧ����Ϣ\n");
	printf("[2]->�޸�ѧ����Ϣ\n");
	printf("[3]->����ѧ���û�\n");
	printf("[4]->ɾ��ѧ���û�\n");
	printf("[5]->�޸�����\n");
	printf("[0]->�˳�ϵͳ\n");
}
void search_menu()
{
	head_menu();
	printf("[1]->ͨ��ѧ�Ų���\n");
	printf("[2]->ͨ����������\n");
	printf("[3]->��ʾȫ��\n");
	printf("[0]->������һ��\n");
}
void changeStuImf_menu()
{
	head_menu();
	printf("[1]->ͨ��ѧ�Ų����޸�\n");
	printf("[2]->ͨ�����������޸�\n");
	printf("[0]->������һ��\n");
}
void changeStuImf_menu2()
{
	system("cls");
	printf("��ѡ��Ҫ�޸ĵ����ݣ�\n");
	printf("[1]->ѧ��\n");
	printf("[2]->����\n");
	printf("[3]->�Ա�(��->����'m',Ů->����'f')\n");
	printf("[4]->����\n");
	printf("[5]->�ɼ�1\n");
	printf("[6]->�ɼ�2\n");
	printf("[7]->�ɼ�3\n");
	printf("[8]->����\n");
	printf("[0]->������һ��\n");
}
void admin_menu()
{
	head_menu();
	printf("[1]->��ѯѧ����Ϣ\n");
	printf("[2]->�޸�ѧ����Ϣ\n");
	printf("[3]->����ѧ���û�\n");
	printf("[4]->ɾ��ѧ���û�\n");
	printf("[5]->��ѯ�û���Ϣ\n");
	printf("[6]->�޸��û���Ϣ\n");
	printf("[7]->������ͨ�û�\n");
	printf("[8]->ɾ����ͨ�û�\n");
	printf("[0]->�˳�ϵͳ\n");
}

void printStuImf(pSTU stu_now)
{
	char sex[5] = { 0 };
	system("cls");
	if (stu_now == 'f')
	{
		strcpy(sex, "Ů");
	}
	else
	{
		strcpy(sex, "��");
	}
	printf("ѧ��\t����\t�Ա�\t����\t�ɼ�1\t�ɼ�2\t�ɼ�3\n");
	printf("%s\t%-s\t%s\t%d\t%5.2lf\t%5.2lf\t%5.2lf\n", stu_now->stu_id, stu_now->stu_name, sex, stu_now->stu_age, stu_now->stu_score1, stu_now->stu_score2, stu_now->stu_score3);
}

void changeStuPassWd(pL_STU linkStu, pSTU stu_now)
{
	char str1[PASSWD_LEN] = { 0 };
	char str2[PASSWD_LEN] = { 0 };
	system("cls");
	while (1)
	{
		printf("�����룺\n");
		getPassWd(str1);
		printf("\n�ظ�һ��ȷ�ϣ�\n");
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
			printf("\n�޸ĳɹ���\n");
			system("pause");
			break;
		}
		else
		{
			printf("\nǰ��һ�£�����������\n");
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
	printf("������ѧ�ţ�");
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
	printf("�����ѧ�Ų�����\n");
	return NULL;
}
pSTU locatStuName(pL_STU linkStu, char* str)
{
	system("cls");
	printf("������������");
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
	printf("���޴���\n");
	return	NULL;
}
int changeStuImf(pL_STU linkStu,pSTU pstu)
{
	int n;
	char str[PASSWD_LEN] = { 0 };
	while (1)
	{
		changeStuImf_menu2();
		printf("��������һ�����֣�");
		while (scanf("%d", &n) != EOF)
		{
			if (n == 1)
			{
				system("cls");
				printf("��������ѧ�ţ�");
				while (scanf("%s", str) != EOF)
				{
					if (isExistStuId(linkStu, str)==0)
					{
						break;
					}
					else
					{
						printf("ѧ���Ѵ��ڣ�����������\n");
						fflush(stdin);
					}
				}
				strcpy(pstu->stu_id, str);
				printf("�޸ĳɹ�\n");
				system("pause");
				break;
			}
			else if (n == 2)
			{
				system("cls");
				printf("��������������");
				scanf("%s", str);
				strcpy(pstu->stu_name, str);
				printf("�޸ĳɹ�\n");
				system("pause");
				break;
			}
			else if (n == 3)
			{
				char c;
				system("cls");
				printf("�������޸ĺ���Ա�(��->����m; Ů->����f)��");
				scanf(" %c", &c);
				pstu->stu_sex = c;
				printf("�޸ĳɹ�\n");
				system("pause");
				break;
			}
			else if (n == 4)
			{
				int age;
				system("cls");
				printf("�������޸ĺ�����䣺");
				scanf("%d", &age);
				pstu->stu_age = age;
				printf("�޸ĳɹ�\n");
				system("pause");
				break;
			}
			else if (n == 5)
			{
				double n;
				system("cls");
				printf("�������޸ĺ�ĳɼ�1��");
				scanf("%lf", &n);
				pstu->stu_score1 = n;
				printf("�޸ĳɹ�\n");
				system("pause");
				break;
			}
			else if (n == 6)
			{
				double n;
				system("cls");
				printf("�������޸ĺ�ĳɼ�2��");
				scanf("%lf", &n);
				pstu->stu_score2 = n;
				printf("�޸ĳɹ�\n");
				system("pause");
				break;
			}
			else if (n == 7)
			{
				double n;
				system("cls");
				printf("�������޸ĺ�ĳɼ�3��");
				scanf("%lf", &n);
				pstu->stu_score3 = n;
				printf("�޸ĳɹ�\n");
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
					printf("�����룺\n");
					getPassWd(str1);
					printf("\n�ظ�һ��ȷ�ϣ�\n");
					getPassWd(str2);
					if (strcmp(str1, str2) == 0)
					{
						strcpy(pstu->stu_passwd, str1);
						printf("\n�޸ĳɹ���\n");
						system("pause");
						break;
					}
					else
					{
						printf("\nǰ��һ�£�����������\n");
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
				printf("û�����ѡ�����������\n");
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
	printf("[1]->��ѧ��ɾ��\n");
	printf("[2]->ɾ��ȫ��\n");
	printf("[0]->������һ��\n");
	int n;
	printf("��ѡ��һ�����֣�");
	while (1)
	{
		scanf("%d", &n);
		if (n == 1)
		{
			char str[STU_ID_LEN];
			system("cls");
			printf("������Ҫɾ��ѧ����ѧ�ţ�");
			scanf("%s", str);
			if (delStuID(linkStu, str))
			{
				printf("ɾ���ɹ�...\n");
				system("pause");
			}
			else
			{
				printf("ѧ�Ų����ڣ�ɾ��ʧ��...\n");
				system("pause");
			}
			break;
		}
		else if(n==2)
		{
			char c;
			system("cls");
			printf("�Ƿ�ȷ��ɾ��ȫ��ѧ����Ϣ!!!(ȷ������y,�������������)\n");
			fflush(stdin);
			scanf(" %c", &c);
			if (c == 'y')
			{
				delStuAll(linkStu);
				printf("ɾ���ɹ�...\n");
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
			printf("û�����ѡ�����������\n");
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
		free(pcur->date);	//�ͷŽṹ��ռ�
		free(pcur);			//�ͷ�����ڵ�ռ�
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
		free(ptmp->date);	//�ͷŽṹ��ռ�
		free(ptmp);			//�ͷ�����ڵ�ռ�
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
		printf("�����룺\n");
		getPassWd(str1);
		printf("\n�ظ�һ��ȷ�ϣ�\n");
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
			printf("\n�޸ĳɹ���\n");
			system("pause");
			break;
		}
		else
		{
			printf("\nǰ��һ�£�����������\n");
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
	printf("[1]->�޸��û�����\n");
	printf("[2]->�޸��û�����\n");
	printf("[0]->������һ��\n");
}
void changeUserName(pUSER pUser)
{
	char strName[NAME_LEN] = { 0 };
	printf("���������û�����\n");
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
		printf("[1]->������ɾ���û�\n");
		printf("[2]->ɾ��ȫ���û�\n");
		printf("[0]->������һ��\n");
		printf("������һ������\n");
		while (scanf("%d", &n))
		{
			if (n == 1)
			{
				system("cls");
				printf("������Ҫɾ�����û�������\n");
				scanf("%s", name);
				if (delUserName(linkUser, name))
				{
					printf("ɾ���ɹ�...\n");
				}
				else
				{
					printf("���޴��ˣ�ɾ��ʧ��...\n");
				}
				system("pause");
				break;
			}
			else if (n == 2)
			{
				char c;
				system("cls");
				printf("�Ƿ�ȷ��ɾ��ȫ���û�!!!(ȷ������y,�������������)\n");
				fflush(stdin);
				scanf(" %c", &c);
				if (c == 'y')
				{
					delUserAll(linkUser);
					printf("ɾ���ɹ�...\n");
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
				printf("û�����ѡ�����������\n");
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
		free(ptmp->date);	//�ͷŽṹ��ռ�
		free(ptmp);			//�ͷ�����ڵ�ռ�
		linkUser->num_user--;
	}
}