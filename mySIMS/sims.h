#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define STU_ID_LEN 10
#define NAME_LEN 20
#define PASSWD_LEN 20
#define PATH_LEN 256

typedef struct student
{
	char stu_id[STU_ID_LEN];
	char stu_name[NAME_LEN];
	char stu_sex;
	int stu_age;
	char stu_passwd[PASSWD_LEN];
	double stu_score1, stu_score2, stu_score3;
}STU,*pSTU;

typedef struct user
{
	char user_name[NAME_LEN];
	char user_passwd[PASSWD_LEN];
	int user_limit;		//�û�Ȩ�ޣ�1Ϊ����Ա��0Ϊ��ͨ�û�
}USER,*pUSER;

typedef struct linkNode_stu
{
	pSTU date;
	struct linkNode_stu* next;
}LN_STU,*pLN_STU;

typedef struct link_stu
{
	int num_stu;
	pLN_STU head;
	pLN_STU tail;
}L_STU,*pL_STU;

typedef struct linkNode_user
{
	pUSER date;
	struct linkNode_user* next;
}LN_USER,*pLN_USER;

typedef struct link_user
{
	int num_user;
	pLN_USER head;
	pLN_USER tail;
}L_USER,*pL_USER;

//�Ӵ��̶�ȡ�����ļ����·����Ϣ
void readConfigFile(char* argv, char* str1, char* str2);
//�Ӵ��̶�ȡѧ����Ϣ���ص��ڴ�
void readStuFile(char* str1, pL_STU* linkStu);
//�Ӵ��̶�ȡ�û���Ϣ���ص��ڴ�
void readUserFile(char* str2, pL_USER* linkUser);
//��ʼ��ϵͳ���Ѵ������ݶ����ڴ�
void systemInit(pL_STU* linkStu, pL_USER* linkUser, char* argv, char* str1, char* str2);
//��������ͷ���
pL_STU creatLink_stu(pL_STU* linkStu);
pL_USER creatLink_user(pL_USER** linkUser);
//β�巨����������
pL_STU addLinkStu_tail(pL_STU linkStu, pLN_STU pnew);
pL_USER addLinkUser_tail(pL_USER linkUser, pLN_USER pnew);
//�������������ʹ��
void linkPrint_stu(pL_STU linkStu);
void linkPrint_user(pL_USER linkUser);
void linkPrint_userAccount(pL_USER linkUser);
//�˳�ϵͳ
void systemExit();
//��½����˵�
void logon_menu();
void stu_menu();
void user_menu();
void search_menu();
void changeStuImf_menu();
void changeStuImf_menu2();
void admin_menu();
//��������ѧ��,�˺ţ��ݴ�����������һ���������
int checkStuId(pL_STU linkStu, pSTU stu_now);
int checkUserName(pL_USER linkUser, pUSER user_now);
//������������										������룬���ܴ�������Ϣ�Ա�����
//int checkStuPassWd(pL_STU linkStu, char *passWd);
//int checkUserPassWd(pL_USER linkUser, char* passWd);
//��ȡ���������
char* getPassWd(char* passWd);
//��½����
int logon(pL_STU linkStu, pL_USER linkUser, pSTU stu_now, pUSER user_now);
//��ʾѧ��������Ϣ
void printStuImf(pSTU stu_now);
//��������
void changeStuPassWd(pL_STU linkStu, pSTU stu_now);
void changeUserPassWd(pL_USER linkUser, pUSER user_now);
//�����ڴ��е����ݵ�����
void save_stu(pL_STU linkStu, char *str1);
void save_user(pL_STU linkStu, char* str1, pL_USER linkUser, char* str2);
//����ѧ��ѧ�š�����
pSTU locatStuId(pL_STU linkStu, char* str);
pSTU locatStuName(pL_STU linkStu, char* str);
//�޸�ѧ����Ϣ
int changeStuImf(pL_STU linkStu, pSTU pstu);
//�ж������ѧ���Ƿ��Ѿ����ڣ��涨ѧ�Ų����ظ�
int isExistStuId(pL_STU linkStu, char* str);
//������˳�����
pL_STU addLinkStu_sort(pL_STU linkStu, pSTU pnew);
//ɾ��ѧ��
void delStu(pL_STU linkStu);
int delStuID(pL_STU linkStu, char* str);
void delStuAll(pL_STU linkStu);

pUSER locatUserName(pL_USER linkUser, const char* str);
void changeUser_menu();
void deleteUser(pL_USER linkUser);
int delUserName(pL_USER linkUser, char* name);
void delUserAll(pL_USER linkUser);