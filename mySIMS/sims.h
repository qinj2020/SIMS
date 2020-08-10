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
	int user_limit;		//用户权限，1为管理员，0为普通用户
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

//从磁盘读取配置文件里的路径信息
void readConfigFile(char* argv, char* str1, char* str2);
//从磁盘读取学生信息加载到内存
void readStuFile(char* str1, pL_STU* linkStu);
//从磁盘读取用户信息加载到内存
void readUserFile(char* str2, pL_USER* linkUser);
//初始化系统，把磁盘数据读入内存
void systemInit(pL_STU* linkStu, pL_USER* linkUser, char* argv, char* str1, char* str2);
//创建链表头结点
pL_STU creatLink_stu(pL_STU* linkStu);
pL_USER creatLink_user(pL_USER** linkUser);
//尾插法建立单链表
pL_STU addLinkStu_tail(pL_STU linkStu, pLN_STU pnew);
pL_USER addLinkUser_tail(pL_USER linkUser, pLN_USER pnew);
//链表输出，测试使用
void linkPrint_stu(pL_STU linkStu);
void linkPrint_user(pL_USER linkUser);
void linkPrint_userAccount(pL_USER linkUser);
//退出系统
void systemExit();
//登陆界面菜单
void logon_menu();
void stu_menu();
void user_menu();
void search_menu();
void changeStuImf_menu();
void changeStuImf_menu2();
void admin_menu();
//检查输入的学号,账号，暂存密码用于下一步检查密码
int checkStuId(pL_STU linkStu, pSTU stu_now);
int checkUserName(pL_USER linkUser, pUSER user_now);
//检查输入的密码										错误代码，不能从所有信息对比密码
//int checkStuPassWd(pL_STU linkStu, char *passWd);
//int checkUserPassWd(pL_USER linkUser, char* passWd);
//获取输入的密码
char* getPassWd(char* passWd);
//登陆操作
int logon(pL_STU linkStu, pL_USER linkUser, pSTU stu_now, pUSER user_now);
//显示学生个人信息
void printStuImf(pSTU stu_now);
//更改密码
void changeStuPassWd(pL_STU linkStu, pSTU stu_now);
void changeUserPassWd(pL_USER linkUser, pUSER user_now);
//保存内存中的数据到磁盘
void save_stu(pL_STU linkStu, char *str1);
void save_user(pL_STU linkStu, char* str1, pL_USER linkUser, char* str2);
//查找学生学号、姓名
pSTU locatStuId(pL_STU linkStu, char* str);
pSTU locatStuName(pL_STU linkStu, char* str);
//修改学生信息
int changeStuImf(pL_STU linkStu, pSTU pstu);
//判断输入的学号是否已经存在，规定学号不能重复
int isExistStuId(pL_STU linkStu, char* str);
//单链表顺序插入
pL_STU addLinkStu_sort(pL_STU linkStu, pSTU pnew);
//删除学生
void delStu(pL_STU linkStu);
int delStuID(pL_STU linkStu, char* str);
void delStuAll(pL_STU linkStu);

pUSER locatUserName(pL_USER linkUser, const char* str);
void changeUser_menu();
void deleteUser(pL_USER linkUser);
int delUserName(pL_USER linkUser, char* name);
void delUserAll(pL_USER linkUser);