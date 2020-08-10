#include "sims.h"

int main(int argc, char* argv[])
{
	pL_STU linkStu;
	pL_USER linkUser;
	STU stu_now;		//���浱ǰ��¼�˺���Ϣ
	USER user_now;
	pSTU pstu_tmp;
	pUSER puser_tmp;
	char str1[PATH_LEN] = { 0 };
	char str2[PATH_LEN] = { 0 };
	char str[NAME_LEN] = { 0 };
	int ret;
	int n;
	systemInit(&linkStu, &linkUser, argv[1], str1, str2);
	logon_menu();
	ret = logon(linkStu, linkUser, &stu_now, &user_now);
	if (ret == 1)
	{
		while (1)
		{
			stu_menu();
			printf("��������һ�����֣�");
			while (scanf("%d", &n) != EOF)
			{
				if (n == 1)
				{
					printStuImf(&stu_now);
					system("pause");
					break;
				}
				else if (n == 2)
				{
					changeStuPassWd(linkStu, &stu_now);
					break;
				}
				else if (n == 0)
				{
					save_stu(linkStu, str1);
					systemExit();
				}
				else
				{
					printf("û�����ѡ�����������\n");
					fflush(stdin);
				}
			}
		}
	}
	else if (ret == 2)
	{
		while (1)
		{
			user_menu();
			printf("��������һ�����֣�");
			while (scanf("%d", &n) != EOF)
			{
				switch (n)
				{
				case 0:
					save_user(linkStu, str1, linkUser, str2);
					systemExit();
					break;
				case 1:
					while (1)
					{
						search_menu();
						printf("��������һ�����֣�");
						while (scanf("%d", &n) != EOF)
						{
							if (n == 1)
							{
								pstu_tmp = locatStuId(linkStu, str);
								printStuImf(pstu_tmp);
								system("pause");
								break;
							}
							else if (n == 2)
							{
								pstu_tmp = locatStuName(linkStu, str);
								printStuImf(pstu_tmp);
								system("pause");
								break;
							}
							else if (n == 3)
							{
								linkPrint_stu(linkStu);
								system("pause");
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
					break;
				case 2:
					while (1)
					{
						changeStuImf_menu();
						printf("��������һ�����֣�");
						while (scanf("%d", &n) != EOF)
						{
							if (n == 1)
							{
								pstu_tmp = locatStuId(linkStu, str);
								changeStuImf(linkStu, pstu_tmp);
								break;
							}
							else if (n == 2)
							{
								pstu_tmp = locatStuName(linkStu, str);
								changeStuImf(linkStu, pstu_tmp);
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
					break;
				case 3:
					system("cls");
					printf("����ѧ����Ϣ�������ʽ���£�\n");
					printf("ѧ��\t����\t�Ա�(��->m;Ů->f)\t����\t�ɼ�1\t�ɼ�2\t�ɼ�3\t����\n");
					pSTU pnew = (pSTU)calloc(1, sizeof(STU));
					if (pnew == NULL)
					{
						printf("����ʧ��\n");
						systemExit();
					}
					scanf("%s%s %c%d%lf%lf%lf%s", pnew->stu_id, pnew->stu_name, &(pnew->stu_sex), &(pnew->stu_age), &(pnew->stu_score1), &(pnew->stu_score2), &(pnew->stu_score3), pnew->stu_passwd);
					while (isExistStuId(linkStu, pnew->stu_id))
					{
						printf("ѧ���Ѵ��ڣ�����������\n");
						memset(pnew, 0, sizeof(STU));
						fflush(stdin);
						scanf("%s%s %c%d%lf%lf%lf%s", pnew->stu_id, pnew->stu_name, &(pnew->stu_sex), &(pnew->stu_age), &(pnew->stu_score1), &(pnew->stu_score2), &(pnew->stu_score3), pnew->stu_passwd);
						
					}
					addLinkStu_sort(linkStu, pnew);
					free(pnew);
					printf("�����ɹ�\n");
					system("pause");
					break;
				case 4:
					delStu(linkStu);
					break;
				case 5:
					changeUserPassWd(linkUser, &user_now);
					break;
				default:
					printf("û�����ѡ�����������\n");
					fflush(stdin);
				}
				break;
			}
		}
	}
	else if (ret == 3)
	{
		while (1)
		{
			admin_menu();
			printf("��������һ�����֣�");
			while (scanf("%d", &n) != EOF)
			{
				switch (n)
				{
				case 0:
					save_user(linkStu, str1, linkUser, str2);
					systemExit();
					break;
				case 1:
					while (1)
					{
						search_menu();
						printf("��������һ�����֣�");
						while (scanf("%d", &n) != EOF)
						{
							if (n == 1)
							{
								pstu_tmp = locatStuId(linkStu, str);
								if (pstu_tmp)
								{
									printStuImf(pstu_tmp);
								}
								system("pause");
								break;
							}
							else if (n == 2)
							{
								pstu_tmp = locatStuName(linkStu, str);
								if (pstu_tmp)
								{
									printStuImf(pstu_tmp);
								}
								system("pause");
								break;
							}
							else if (n == 3)
							{
								linkPrint_stu(linkStu);
								system("pause");
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
					break;
				case 2:
					while (1)
					{
						changeStuImf_menu();
						printf("��������һ�����֣�");
						while (scanf("%d", &n) != EOF)
						{
							if (n == 1)
							{
								pstu_tmp = locatStuId(linkStu, str);
								changeStuImf(linkStu, pstu_tmp);
								break;
							}
							else if (n == 2)
							{
								pstu_tmp = locatStuName(linkStu, str);
								changeStuImf(linkStu, pstu_tmp);
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
					break;
				case 3:
					system("cls");
					printf("����ѧ����Ϣ�������ʽ���£�\n");
					printf("ѧ��\t����\t�Ա�(��->m;Ů->f)\t����\t�ɼ�1\t�ɼ�2\t�ɼ�3\t����\n");
					pSTU pnew = (pSTU)calloc(1, sizeof(STU));
					if (pnew == NULL)
					{
						printf("����ʧ��\n");
						systemExit();
					}
					scanf("%s%s %c%d%lf%lf%lf%s", pnew->stu_id, pnew->stu_name, &(pnew->stu_sex), &(pnew->stu_age), &(pnew->stu_score1), &(pnew->stu_score2), &(pnew->stu_score3), pnew->stu_passwd);
					while (isExistStuId(linkStu, pnew->stu_id))
					{
						printf("ѧ���Ѵ��ڣ�����������\n");
						memset(pnew, 0, sizeof(STU));
						fflush(stdin);
						scanf("%s%s %c%d%lf%lf%lf%s", pnew->stu_id, pnew->stu_name, &(pnew->stu_sex), &(pnew->stu_age), &(pnew->stu_score1), &(pnew->stu_score2), &(pnew->stu_score3), pnew->stu_passwd);

					}
					addLinkStu_sort(linkStu, pnew);
					free(pnew);
					printf("�����ɹ�\n");
					system("pause");
					break;
				case 4:
					delStu(linkStu);
					break;
				case 5:
					system("cls");
					linkPrint_userAccount(linkUser);
					system("pause");
					break;
				case 6:
					while (1)
					{
						int n = 0;
						system("cls");
						changeUser_menu();
						printf("������һ������\n");
						while (scanf("%d", &n))
						{
							if (n == 1)
							{
								system("cls");
								printf("������Ҫ�޸ĵ��û�����");
								memset(str, 0, sizeof(str));
								scanf("%s", str);
								puser_tmp = locatUserName(linkUser, str);
								if (puser_tmp)
								{
									changeUserName(puser_tmp);
									printf("�޸ĳɹ�...\n");
								}
								else
								{
									printf("���޴���...\n");
								}
								system("pause");
								break;
							}
							else if (n == 2)
							{
								system("cls");
								printf("������Ҫ�޸ĵ��û�����");
								memset(str, 0, sizeof(str));
								scanf("%s", str);
								puser_tmp = locatUserName(linkUser, str);
								if (puser_tmp)
								{
									changeUserPassWd(linkUser, puser_tmp);
								}
								else
								{
									printf("���޴���...\n");
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
					break;
				case 7:
					system("cls");
					printf("���������û���Ϣ\n");
					printf("�û���\t����\n");
					pUSER pnewUser = (pUSER)calloc(1, sizeof(USER));
					scanf("%s%s", pnewUser->user_name, pnewUser->user_passwd);
					pLN_USER pNew = (pLN_USER)calloc(1, sizeof(LN_USER));
					pNew->date = pnewUser;
					addLinkUser_tail(linkUser, pNew);
					printf("�����ɹ�\n");
					system("pause");
					break;
				case 8:
					deleteUser(linkUser);
					break;
				default:
					printf("û�����ѡ�����������\n");
					fflush(stdin);
				}
				break;
			}
		}
	}
	return 0;
}