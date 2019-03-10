#include "stdafx.h"
#include "Gongju.h"
#define YEAR 2015 //��2015/2/22���ⶼ�ǲ���ʱ��
#define MONTH 2
#define DAY 22

CGongju::CGongju()
: fp(NULL)
, lujing(_T(""))
{
	//�û���
	yhm[0] = 0;
	yhm[1] = 0;
	yhm[2] = 0;
	yhm[3] = 0;
	yhm[4] = 0;
	yhm[5] = 0;
	//�ζ�Ӧ����
	ddyts[0] = 1;
	ddyts[1] = 2;
	ddyts[2] = 4;
	ddyts[3] = 7;
	ddyts[4] = 15;
	ddyts[5] = 35;
	//������Դ������еļ��
	jiange[0] = 5;
	jiange[1] = 7;
	jiange[2] = 14;
	jiange[3] = 14;
	//�쳣
	yc = 0;
	//��Ŀ����
	for (int i=0; i < 32704;i++)
	{
		xmsj[i].qian[1] = 0;
		xmsj[i].hou[1] = 0;
		xmsj[i].wenti = L"";
		xmsj[i].daan = L"";
	}
	//�������
	for (int i = 0; i < 64; i++)
	{
		flqk[0].cunzai = 0; //��ʼ�������ڴ���
		for (int j = 0; j < 17; j++)
		{
			flqk[i].name[j] = 0;
		}
	}
	for (int i = 0; i < 65; i++)
	{
		dwfl[0][i] = 0;
	}
	for (int i = 0; i < 65; i++)
	{
		dwfl[1][i] = 0;
	}
	yzwxm = 0;
	dxxxm = 0;
	zjyxm = 0;
	//����ͷָ���ʼ��
	fxlbt = new struct fxlb;
	fxlbt->biaoshi = 0;
	fxlbt->next = NULL;
	fxlbw = fxlbt;
	pxlb = new struct pxlb;
	pxlb->biaoshi = 0;
	pxlb->front = NULL;
	pxlb->next = NULL;
	jylb = new struct jylb;
	jylb->biaoshi = 0;
	jylb->next = NULL;
	dxxxm = 0;
	for (int i = 0; i < 32705; i++) ��������[i] = 0;
}


CGongju::~CGongju()
{
	//�ͷ�����Ŀռ�
	while (fxlbt != NULL)//�ͷ�
	{
		fxlbw = fxlbt;
		fxlbt = fxlbt->next;
		delete(fxlbw);
	}
	while (pxlb->next != NULL)//�ͷ�
	{
		pxlb = pxlb->next;
		delete(pxlb->front);
	}
	delete(pxlb);
	struct jylb *jy;//�ͷ�
	while (jylb != NULL)
	{
		jy = jylb;
		jylb = jylb->next;
		delete(jy);
	}
}


int CGongju::riqizhuanhua(int year, int month, int day)
{
	if (year<YEAR) return -2; //ʱ���ڱ�׼ʱ��֮�����
	if (year == YEAR && month<MONTH) return -2;
	if (year == YEAR && month==MONTH && day < DAY) return -2;
	//��֤�º�������ȷ��
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day<1 || day>31) return -1;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day<1 || day>30) return -1;
	}
	else if (month == 2)
	{
		if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day<1 || day>29)) return -1;
		if (!((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (day<1 || day>28)) return -1;
	}
	else return -1;
	int i,year1=year,month1=month,day1=day;
	year = YEAR; 
	month = MONTH; 
	day = DAY;
	for (i = 0; !(year >= year1 && month >= month1 && day >= day1); i++)//����������
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day <= 30) day++;//���û���µ�
			else   //������µ�
			{
				if (month != 12)//������µ�û�����
				{
					day = 1;
					month++;
				}
				else  //������µ׵����
				{
					day = 1; 
					month = 1;
					year++;
				}
			}
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day<=29) day++;
			else
			{
				day = 1;
				month++;
			}
		}
		else
		{
			if (day <= 27) day++;
			else if (day == 28)
			{
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) day++;//����
				else//��������
				{
					day = 1;
					month++;
				}
			}
			else //2��29��ʱ
			{
				day = 1;
				month++;
			}
		}
	}
	return i;
}


CString CGongju::riqizhuanhua(short xiangge)
{
	int year = YEAR, month = MONTH, day = DAY;
	for (; xiangge > 0; xiangge--)
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day <= 30) day++;//���û���µ�
			else   //������µ�
			{
				if (month != 12)//������µ�û�����
				{
					day = 1;
					month++;
				}
				else  //������µ׵����
				{
					day = 1;
					month = 1;
					year++;
				}
			}
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day <= 29) day++;
			else
			{
				day = 1;
				month++;
			}
		}
		else
		{
			if (day <= 27) day++;
			else if (day == 28)
			{
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) day++;//����
				else//��������
				{
					day = 1;
					month++;
				}
			}
			else //2��29��ʱ
			{
				day = 1;
				month++;
			}
		}
	}
	CString s;
	s.Format(L"%d��%d��%d��", year,month,day);
	return s;
}


void CGongju::chushihua()
{
	if (YEAR != 2015 || MONTH != 2 || DAY != 22)
	{
		AfxMessageBox(L"���԰汾�����������رպ�̨��");
	}
	CTime t = CTime::GetCurrentTime();
	xtsj = riqizhuanhua(t.GetYear(), t.GetMonth(), t.GetDay());
	if (0 >= xtsj)
	{
		yc = -1;//ϵͳʱ�����
		return;
	}
	if (32767 < xtsj)
	{
		yc = -2;//ϵͳʱ�������
		return;
	}
	fflush(fp);//д���ǰҪˢ��
	fseek(fp, 2, 0);
	fread(yhm, 2, 5, fp);
	fseek(fp, 16, 0);
	fread(&fsj, 2, 1, fp);
	fread(&lsj, 2, 1, fp);
	if (!(xtsj >= lsj&&lsj >= fsj))
	{
		yc = -3;//ʱ�䲻ƥ�䣡
		return;
	}
	if (lsj > 0 && xtsj - lsj > 9)
	{
		if (IDNO == AfxMessageBox(L"ע�⣡��ȷ��ϵͳʱ����ȷ��", MB_YESNO))
		{
			yc = -4;
			return;
		}
		else yc = 1;
	}
	fread(&dlyxs, 1, 1, fp);
	int jj = 0;
	for (int i = 0; i < 15; i++)   //������ж�ȡ
	{
		fread(&jydl[i].biaoshi, 2, 1, fp);
		fread(&jydl[i].shangshengyan, 1, 1, fp);
		fread(&jydl[i].lianxucishu, 1, 1, fp);
		fread(&jydl[i].xiajiangyan, 1, 1, fp);
		if (0 < jydl[i].biaoshi) jj++;
	}
	if (dlyxs > jj)
	{
		yc = 21;//���ݳ��ִ���
		dlyxs = jj;
	}
	//ʱ��̫��ƽ������
	if (lsj > 0 && xtsj - lsj > 2)
	{
		for (int i = 0; i < 15; i++)
		{
			jydl[i].shangshengyan = 0;
			jydl[i].lianxucishu = 0;
			jydl[i].xiajiangyan = 0;
		}
		д��������();
	}
	//��Ŀ���ݶ�ȡ
	int weizhi,a,q=0;
	short b;
	int cc1, cc2;
	wchar_t c[61]; c[60] = 0;
	for (int i = 0; i < 32704; i++)
	{
		fread(&b, 2, 1, fp);//��ʶ
		if (b <= 0) //������
		{
			fseek(fp, 14, 1);
			xmsj[i].jieduan = -128;
			continue;
		}
		if (b >127) yc = 22;//���ݿ��ܴ����𻵣�
		fread(&xmsj[i].jieduan, 1, 1, fp);//�׶�
		fread(&xmsj[i].scsdsj, 2, 1, fp);//�״�����ʱ��
		fread(&xmsj[i].zhxgsj, 2, 1, fp);//����޸�ʱ��
		fread(&xmsj[i].fenlei, 1, 1, fp);//����
		fread(&xmsj[i].qian[0], 4, 1, fp);//ǰ������
		fread(&xmsj[i].hou[0], 1, 4, fp);//������
		xmsj[i].riqi = riqizhuanhua(xmsj[i].zhxgsj);//����޸�ʱ���ַ�����ʽ
		tianjiaFxlb(i + 1, b);
		weizhi = ftell(fp);
		if (xmsj[i].qian[0]<525430 || xmsj[i].hou[0]<525430)
		{
			yc = 23;//���ݿ��ܴ����𻵣�
			continue;
		}
		fseek(fp, xmsj[i].qian[0], 0);//׼����ȡ����
		cc1 = i + 1;
		a = xmsj[i].qian[0];
		q=0;
		do
		{
			q++;
			if (q <= 15) ; //����900��
			else
			{
				yc = 24;//���ݿ��ܴ����𻵣�
				break;
			}
			fread(&cc2, 4, 1, fp);
			if (cc1 == cc2) cc1 = a;
			else
			{
				yc = 28;//ǰ������
			}
			fread(c, 2, 60, fp);//��ȡ����
			xmsj[i].wenti += c;//���ݸ�ֵ
			fread(&a, 4, 1, fp);//�ж��Ƿ�����ı��
			xmsj[i].qian[1]++;//���ݵ�Ԫ����
			fseek(fp, a, 0);//��һ����Ŀ�ͷ
		} while (525430 <= a);
		if (16 == q) xmsj[i].qian[1] = 0;
		fseek(fp, xmsj[i].hou[0], 0);//׼����ȡ��
		cc1 = -(i + 1);
		a = xmsj[i].hou[0];
		q = 0;
		do
		{
			q++;
			if (q <= 15) ; //����900��
			else
			{
				yc = 24;//���ݿ��ܴ����𻵣�
				break;
			}
			fread(&cc2, 4, 1, fp);
			if (cc1 == cc2) cc1 = a;
			else
			{
				yc = 28;//ǰ������
			}
			fread(c, 2, 60, fp);//��ȡ����
			xmsj[i].daan += c;//���ݸ�ֵ
			fread(&a, 4, 1, fp);//�ж��Ƿ�����ı��
			xmsj[i].hou[1]++;//���ݵ�Ԫ����
			fseek(fp, a, 0);//��һ����Ŀ�ͷ
		} while (525430 <= a);
		if (16 == q) xmsj[i].hou[1] = 0;
		fseek(fp, weizhi, 0);
	}
	//���������ȡ
	unsigned char cc;
	for (int i = 0; i < 8; i++)
	{
		fread(&cc, 1, 1, fp);
		if ((cc & 0x80) == 0x80) flqk[i * 8 + 0].cunzai = 1;
		if ((cc & 0x40) == 0x40) flqk[i * 8 + 1].cunzai = 1;
		if ((cc & 0x20) == 0x20) flqk[i * 8 + 2].cunzai = 1;
		if ((cc & 0x10) == 0x10) flqk[i * 8 + 3].cunzai = 1;
		if ((cc & 0x08) == 0x08) flqk[i * 8 + 4].cunzai = 1;
		if ((cc & 0x04) == 0x04) flqk[i * 8 + 5].cunzai = 1;
		if ((cc & 0x02) == 0x02) flqk[i * 8 + 6].cunzai = 1;
		if ((cc & 0x01) == 0x01) flqk[i * 8 + 7].cunzai = 1;
	}
	for (int i = 0; i < 64; i++)
	{
		if (1 == flqk[i].cunzai) fread(flqk[i].name, 2, 16, fp);
		else fseek(fp, 32, 1);
	}
	flqk[0].cunzai = 1;
	lstrcpyW(flqk[0].name, L"δ����");
	fread(fxjz, 2, 4, fp);  //��ȡ��ϰ��׼
	if (!(xtsj >= fxjz[2] && fxjz[2] >= fxjz[0]))
	{
		yc = -3;//ʱ�䲻ƥ�䣡
		return;
	}
	fread(&dfxxm, 2, 1, fp);  //��ȡ����ϰ��Ŀ
	fread(&wdwdz, 4, 1, fp);  //��ȡβ��ַ
	//�趨����治ֱ����صı���
	for (int i = 0; i < 32704; i++)
	{
		if (-128 == xmsj[i].jieduan) continue;
		zjyxm++;//�ܼ�����Ŀ
		tianjiaPxlb(i+1);
		if (xmsj[i].jieduan == -1) //���ѧϰ�����Ƿ����
		{
			int csxx = 0;
			for (int i1 = 0; i1 < 15; i1++)
			{
				if (jydl[i1].biaoshi == i + 1)
				{
					csxx = 1;
					break;
				}
			}
			if (csxx != 1)
			{
				yc = 25;
				xiugaiJieduan(i + 1, 0);//���ڵ�ʱ��
			}
		}
		if (xmsj[i].jieduan > 1 && xmsj[i].jieduan < 7) dwfl[0][xmsj[i].fenlei]++;//��λ����
		else dwfl[1][xmsj[i].fenlei]++;//��λ����
		if (xmsj[i].jieduan <= 0) dxxxm++;//��ѧϰ��Ŀ
		if (xmsj[i].jieduan > 6) yzwxm++;//��������Ŀ
		tianjiaJylb(i+1);
	}
	//��λ��������ȷ��
	for (int j = 0; j<64; j++)
	{
		dwfl[0][64] += dwfl[0][j];
	}
	for (int j = 0; j<64; j++)
	{
		dwfl[1][64] += dwfl[1][j];
	}
	 //��ϰ����ȷ��
	if (fxjz[2] < xtsj)//�ǵ�������Ҫ
	{
		if (xtsj - fxjz[2] > 7)//ȫ����7����
		{
			fxjz[0] = xtsj;
			fxjz[1] = 0;
		}
		else
		{
			if (xtsj - fxjz[0] > 7)//ֻ��ǰ�߳���7��
			{
				fxjz[0] = fxjz[2];
				fxjz[1] = fxjz[3];
			}
			else
			{
				if (fxjz[1] <= fxjz[3])//�ӵ��ڱ�֤�������µ�
				{
					fxjz[0] = fxjz[2];
					fxjz[1] = fxjz[3];
				}
			}
		}
		fxjz[2] = xtsj;
		fxjz[3] = 0;
		if (fxjz[1] < 0)
		{
			yc = 26;
			fxjz[1] = 0;//������ƻ�ʱ
		}
		if (dfxxm < 0)
		{
			yc = 26;
			dfxxm = 0;//������ƻ�ʱ
		}
		if (fxjz[1] * 7 / 3 > 25) dfxxm += fxjz[1] * 7 / 3 + 5;
		else dfxxm += 25;
		if (dfxxm>fxlbt->biaoshi) dfxxm = fxlbt->biaoshi;//��ϰ����������
		fseek(fp, 525416, 0);//д���޸ĵ����ݵ�λ��
		fwrite(fxjz, 2, 4, fp);
		fwrite(&dfxxm, 2, 1, fp);
		fflush(fp);
	}
	fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
	int n = ftell(fp);//�ļ���С��ȡ
	if (wdwdz<525430 || wdwdz>n) yc = 27;//β��λ����
	��������();
	//����5������������0
	if (lsj > 0 && xtsj - lsj >= 5)
	{
		for (int i = 0; i < 15; i++)  
		{
			jydl[i].shangshengyan = 0;
			jydl[i].lianxucishu = 0;
			jydl[i].xiajiangyan = 0;
		}
		dlyxs = 0;
		д��������();
	}
	//��ϰ�������һ���Ƶ���ǰ�����͹رմ򿪶�ƽ�ش���0��ȫ����ǰ��Ӱ��
	if (fxlbt->biaoshi>1)
	{
		struct fxlb *ff;
		for (ff = fxlbt; ff->next != fxlbw; ff = ff->next);
		fxlbw->next = fxlbt->next;
		fxlbt->next = fxlbw;
		fxlbw = ff;
		fxlbw->next = NULL;
	}
	//���������
	srand(time(0)*time(0));
}


// �����������һ���µ���Ŀ,��������
int CGongju::tianjiaPxlb(int biaoshi)
{
	if (yc < 0)
	{
		return 0;
	}
	if (-128 == xmsj[biaoshi-1].jieduan)
	{
		return 0;
	}
	struct pxlb *zz = pxlb;
	struct pxlb *zzz = new struct pxlb;
	zzz->biaoshi = biaoshi;
	zzz->next = NULL;
	while (zz->next != NULL)
	{
		if (xmsj[biaoshi-1].zhxgsj < xmsj[zz->next->biaoshi - 1].zhxgsj) zz = zz->next;
		else
		{
			zzz->next = zz->next;
			zzz->front = zz;
			zz->next->front = zzz;
			zz->next = zzz;
			break;
		}
	}
	if (zz->next == NULL)
	{
		zz->next = zzz;
		zzz->front = zz;
	}
	pxlb->biaoshi++;
	return 1;
}

//�޸��ڴ��������Ŀ�Ľ׶�
int CGongju::xiugaiJieduan(int biaoshi, char jieduan)
{
	if (yc < 0)
	{
		return 0;
	}
	short i = 1;
	xmsj[biaoshi-1].jieduan = jieduan;
	fseek(fp, 96 + (biaoshi - 1) * 16, 0);
	fwrite(&i, 2, 1, fp);
	fwrite(&jieduan, 1, 1, fp);
	fflush(fp);//ˢ�£�����д��
	return 1;
}


// ������������һ�����
int CGongju::tianjiaJylb(int biaoshi)
{
	if (yc < 0)
	{
		return 0;
	}
	if (0 != xmsj[biaoshi - 1].jieduan)
	{
		return 0;
	}
	struct jylb *zzz = new struct jylb;
	zzz->biaoshi = biaoshi;
	zzz->next = jylb->next;
	jylb->next = zzz;
	jylb->biaoshi++;
	return 1;
}


// ��ϰ����
int CGongju::tianjiaFxlb(int biaoshi, int b)
{
	if (yc < 0)
	{
		return 0;
	}
	if (0 >= xmsj[biaoshi - 1].jieduan || 7 <= xmsj[biaoshi - 1].jieduan)
	{
		return 0;//1��6��֮�ⲻ��
	}
	if (xmsj[biaoshi - 1].scsdsj + ddyts[xmsj[biaoshi - 1].jieduan-1] > xtsj)
	{
		return 0;
	}
	struct fxlb *zzz = new struct fxlb;
	zzz->biaoshi = biaoshi;//��ʶ
	if (b > 0 && b <= 128)
		zzz->pingyancishu = b - 1;//ƽ�ش���
	else
		zzz->pingyancishu = 0;
	if (1 == xmsj[biaoshi - 1].jieduan || zzz->pingyancishu > 0)//һ�κ�ƽ�ش���0����ǰ��
	{
		zzz->next = fxlbt->next;
		fxlbt->next = zzz;
		if (fxlbt == fxlbw) fxlbw = zzz;
	}
	else
	{
		fxlbw->next = zzz;
		zzz->next = NULL;
		fxlbw = fxlbw->next;
	}
	fxlbt->biaoshi++;//��ϰ�ĸ���
	return 1;
}


// �޸��û���
int CGongju::xiugaiYhm(CString YHM)
{
	if (yc < 0)
	{
		return 0;
	}
	if (YHM.GetLength() > 5||YHM.GetLength()==0)
	{
		return 0;
	}
	if (YHM.Find(L" ") != -1)//�����пո�
	{
		return 0;
	}
	lstrcpy(yhm,YHM);
	fseek(fp, 2, 0);
	fwrite(yhm, 2, 5, fp);
	fflush(fp);//ˢ�£�����д��
	return 1;
}


int CGongju::tianjiaXiangmu(CString wen, CString da, char fenlei)//���ر�ʶ
{
	if (yc < 0 || wen.GetLength() > 900 || da.GetLength() > 900 || fenlei > 63 || fenlei < 0)
	{
		return 0;
	}
	if (wen.GetLength() < 1 || da.GetLength() < 1 || 32703 < zjyxm || !flqk[fenlei].cunzai) return 0;
	dxxxm++;
	zjyxm++;
	int j;
	short i = 0;//��ʶ-1
	for (i = 0; i < 32704; i++)
	{
		if (xmsj[i].jieduan == -128) break;
	}
	if (i == 32704)
	{
		return -1;//��Ŀ�������
	}
	wchar_t *wenti = new wchar_t[wen.GetLength()+61];//��61��ֹд��ʱ�ڴ��ȡ����
	for (int k=0; k < wen.GetLength() + 1;k++) wenti[k] = 0;
	lstrcpy(wenti, wen);//��CStringת��Ϊwchar_t
	wchar_t *daan = new wchar_t[da.GetLength() + 61];//��61��ֹд��ʱ�ڴ��ȡ����
	for (int k=0; k < da.GetLength() + 1; k++) daan[k] = 0;
	lstrcpy(daan, da);//��CStringת��Ϊwchar_t
	//��Ŀ�����ڴ��޸�
	xmsj[i].jieduan = 0;
	xmsj[i].scsdsj = xtsj;
	xmsj[i].zhxgsj = xtsj;
	xmsj[i].fenlei = fenlei;
	xmsj[i].qian[0] = wdwdz;
	xmsj[i].qian[1] = (wen.GetLength() - 1) / 60 + 1;//�Զ���ȡ�����ֻ��һ�����
	xmsj[i].hou[0] = wdwdz + xmsj[i].qian[1] * 128;
	xmsj[i].hou[1] = (da.GetLength() - 1) / 60 + 1;
	xmsj[i].wenti = wen;
	xmsj[i].daan = da;
	xmsj[i].riqi = riqizhuanhua(xtsj);
	//��Ŀ��������޸�
		//���
	fseek(fp, 96 + i * 16, 0);
	short ii = 1;
	fwrite(&ii, 2, 1, fp);
	fwrite(&xmsj[i].jieduan, 1, 1, fp);
	fwrite(&xmsj[i].scsdsj, 2, 1, fp);
	fwrite(&xmsj[i].zhxgsj, 2, 1, fp);
	fwrite(&xmsj[i].fenlei, 1, 1, fp);
	fwrite(&xmsj[i].qian[0], 4, 1, fp);
	fwrite(&xmsj[i].hou[0], 4, 1, fp);
	fseek(fp, wdwdz, 0);//��β����ʼ�������
	for (int k = 0; k < xmsj[i].qian[1]; k++)//β���������
	{
		if (0 == k) j = i + 1;//����������
		else j = xmsj[i].qian[0] + (k - 1) * 128;
		fwrite(&j, 4, 1, fp);
		//fseek(fp, 120, 1);
		fwrite(wenti + k * 60, 2, 60, fp);//д������
		if (k + 1 == xmsj[i].qian[1]) j = 0;
		else j = xmsj[i].qian[0] + (k + 1) * 128;
		fwrite(&j, 4, 1, fp);
	}
	for (int k = 0; k < xmsj[i].hou[1]; k++)//β����Ӵ�
	{
		if (0 == k) j = -(i + 1);//���Ǹ���
		else j = xmsj[i].hou[0] + (k - 1) * 128;
		fwrite(&j, 4, 1, fp);
		//fseek(fp, 120, 1);
		fwrite(daan + k * 60, 2, 60, fp);//д���
		if (k + 1 == xmsj[i].hou[1]) j = 0;
		else j = xmsj[i].hou[0] + (k + 1) * 128;
		fwrite(&j, 4, 1, fp);
	}
	wdwdz += (xmsj[i].qian[1] + xmsj[i].hou[1]) * 128;//д��β��λ��ַ
	fseek(fp, 525426, 0);
	fwrite(&wdwdz, 4, 1, fp);
	fflush(fp);
	//�����ڴ��޸�
	tianjiaJylb(i + 1);//����
	tianjiaPxlb(i + 1);
	dwfl[1][fenlei]++;
	dwfl[1][64]++;
	//����ͷſռ�
	delete(wenti);
	delete(daan);
	return i+1;
}


CTime CGongju::riqizhuanhua(short xiangge, CTime time)
{
	int year = YEAR, month = MONTH, day = DAY;
	for (; xiangge > 0; xiangge--)
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day <= 30) day++;//���û���µ�
			else   //������µ�
			{
				if (month != 12)//������µ�û�����
				{
					day = 1;
					month++;
				}
				else  //������µ׵����
				{
					day = 1;
					month = 1;
					year++;
				}
			}
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day <= 29) day++;
			else
			{
				day = 1;
				month++;
			}
		}
		else
		{
			if (day <= 27) day++;
			else if (day == 28)
			{
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) day++;//����
				else//��������
				{
					day = 1;
					month++;
				}
			}
			else //2��29��ʱ
			{
				day = 1;
				month++;
			}
		}
	}
	CTime t(year, month, day, 0, 0, 0);//������ȫ����Ч
	return t;
}


int CGongju::Qiandao()
{
	if (yc < 0 || lsj == xtsj)//�������ǩ��
	{
		return 0;
	}
	if (0 >= fsj || xtsj - lsj>1)//��δǩ�����ǩ��
	{
		lsj = xtsj;
		fsj = lsj;
	}
	else
	{
		lsj = xtsj;
	}
	fseek(fp, 16, 0);
	fwrite(&fsj, 2, 1, fp);
	fwrite(&lsj, 2, 1, fp);
	return 1;
}


// ɾ���ñ�ʶ��Ӧ�ĵ�һ����
int CGongju::shanchuKuai(short biaoshi,int wenti)
{
	if (yc < 0 || biaoshi < 1 || xmsj[biaoshi - 1].jieduan == -128)
	{
		return 0;
	}
	if ((wenti&& xmsj[biaoshi - 1].qian[1] < 1) || (!wenti&& xmsj[biaoshi - 1].hou[1] < 1))//û�п�
	{
		return 0;
	}
	int a,b,d;//��ʼɾ��
	char c[128];
	if (wenti)
	{
		b = xmsj[biaoshi - 1].qian[0];//Ҫɾ����ı�ʶ
		if (xmsj[biaoshi - 1].qian[1] > 1)
		{
			fseek(fp, b + 124, 0);
			fread(&a, 4, 1, fp);//��ȡɾ�������λ��
			fseek(fp, a, 0);//�ƶ����ÿ�
			d = biaoshi;
			fwrite(&d, 4, 1, fp);
			fflush(fp);//��ֹɾ���Ŀ������һ�����߼�ǰ��
			xmsj[biaoshi - 1].qian[0] = a;//��ֵ
			fseek(fp, 96 + (biaoshi - 1) * 16 + 8, 0);//�ƶ�������Ŀǰ��
			fwrite(&a, 4, 1, fp);
		}
		else
		{
			a = 0;
			xmsj[biaoshi - 1].qian[0] = a;//��ֵ
			fseek(fp, 96 + (biaoshi - 1) * 16 + 8, 0);//�ƶ�������Ŀǰ��
			fwrite(&a, 4, 1, fp);
		}
		xmsj[biaoshi - 1].qian[1]--;
		if (b != wdwdz - 128)//ɾ���Ĳ������һ����
		{
			fflush(fp);//д���ǰҪˢ��
			fseek(fp, wdwdz - 128, 0);//�ƶ������
			fread(c, 1, 128, fp);
			fseek(fp, b, 0);//�ƶ���ɾ����
			fwrite(c, 1, 128, fp);//����
			fflush(fp);//д���ǰҪˢ��
			fseek(fp, wdwdz - 128, 0);//�ƶ������
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a + 124 , 0);//�ƶ�������ǰ���ĺ���
				fwrite(&b, 4, 1, fp);
			}
			else
			{
				if (0 < a)
				{
					xmsj[a - 1].qian[0] = b;
					fseek(fp, 96 + (a - 1) * 16 + 8, 0);//�ƶ�������Ŀǰ��
					fwrite(&b, 4, 1, fp);
				}
				else if (0 > a)
				{
					xmsj[-a - 1].hou[0] = b;
					fseek(fp, 96 + (-a - 1) * 16 + 12, 0);//�ƶ�������Ŀǰ��
					fwrite(&b, 4, 1, fp);
				}
				else yc = 3;//δ֪��
			}
			fflush(fp);//д���ǰҪˢ��
			fseek(fp, wdwdz - 4, 0);//�ƶ���������
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a, 0);//�ƶ������ĺ�����ǰ��
				fwrite(&b, 4, 1, fp);
			}
		}
	}
	else
	{
		b = xmsj[biaoshi - 1].hou[0];//Ҫɾ����ı�ʶ
		if (xmsj[biaoshi - 1].hou[1] > 1)
		{
			fflush(fp);//д���ǰҪˢ��
			fseek(fp, b + 124, 0);
			fread(&a, 4, 1, fp);//��ȡɾ�������λ��
			fseek(fp, a, 0);//�ƶ����ÿ�
			d = biaoshi;
			fwrite(&d, 4, 1, fp);
			fflush(fp);//��ֹɾ���Ŀ������һ�����߼�ǰ��
			xmsj[biaoshi - 1].hou[0] = a;//��ֵ
			fseek(fp, 96 + (biaoshi - 1) * 16 + 12, 0);//�ƶ�������Ŀǰ��
			fwrite(&a, 4, 1, fp);
		}
		else
		{
			a = 0;
			xmsj[biaoshi - 1].hou[0] = a;//��ֵ
			fseek(fp, 96 + (biaoshi - 1) * 16 + 12, 0);//�ƶ�������Ŀǰ��
			fwrite(&a, 4, 1, fp);
		}
		xmsj[biaoshi - 1].hou[1]--;
		if (b != wdwdz - 128)//ɾ���Ĳ������һ����
		{
			fflush(fp);//д���ǰҪˢ��
			fseek(fp, wdwdz - 128, 0);//�ƶ������
			fread(c, 1, 128, fp);
			fseek(fp, b, 0);//�ƶ���ɾ����
			fwrite(c, 1, 128, fp);//����
			fflush(fp);//д���ǰҪˢ��
			fseek(fp, wdwdz - 128, 0);//�ƶ������
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a + 124, 0);//�ƶ�������ǰ���ĺ���
				fwrite(&b, 4, 1, fp);
			}
			else
			{
				if (0 < a)
				{
					xmsj[a - 1].qian[0] = b;
					fseek(fp, 96 + (a - 1) * 16 + 8, 0);//�ƶ�������Ŀǰ��
					fwrite(&b, 4, 1, fp);
				}
				else if (0 > a)
				{
					xmsj[-a - 1].hou[0] = b;
					fseek(fp, 96 + (-a - 1) * 16 + 12, 0);//�ƶ�������Ŀǰ��
					fwrite(&b, 4, 1, fp);
				}
				else yc = 3;//δ֪��
			}
			fflush(fp);//д���ǰҪˢ��
			fseek(fp, wdwdz - 4, 0);//�ƶ���������
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a, 0);//�ƶ������ĺ�����ǰ��
				fwrite(&b, 4, 1, fp);
			}
		}
	}
	wdwdz -= 128;
	fseek(fp, 525426, 0);
	fwrite(&wdwdz, 4, 1, fp);//д��β��λ��ַ
	fflush(fp);
	return 1;
}


// Ϊ�ñ�ʶ���һ����
int CGongju::tianjiaKuai(short biaoshi, int wenti)
{
	if (yc < 0 || biaoshi < 1 || xmsj[biaoshi - 1].jieduan == -128)
	{
		return 0;
	}
	int a,b;
	char c[120] = { 0 };
	if (wenti)
	{
		a = xmsj[biaoshi - 1].qian[0] + 124;
		fflush(fp);//д���ǰҪˢ��
		for (int i = xmsj[biaoshi - 1].qian[1]; i>1; i--)//�Ƶ�����ĺ�����λ��
		{
			fread(&b, 4, 1, fp);
			a = b + 124;
			fseek(fp, a, 0);
		}
		fseek(fp, a, 0);
		if (xmsj[biaoshi - 1].qian[1] > 0)
		{
			fwrite(&wdwdz, 4, 1, fp);
			a -= 124;//�����λ��
		}
		else
		{
			xmsj[biaoshi - 1].qian[0] = wdwdz;//��ֵ
			fseek(fp, 96 + (biaoshi - 1) * 16 + 8, 0);//�ƶ�������Ŀǰ��
			fwrite(&wdwdz, 4, 1, fp);
			a = biaoshi;
		}
		fseek(fp, wdwdz, 0);//��β����ʼ�������
		fwrite(&a, 4, 1, fp);
		fwrite(c, 1, 120, fp);
		b = 0;
		fwrite(&b, 4, 1, fp);
		xmsj[biaoshi - 1].qian[1]++;
	}
	else
	{
		a = xmsj[biaoshi - 1].hou[0] + 124;
		fflush(fp);//д���ǰҪˢ��
		for (int i = xmsj[biaoshi - 1].hou[1]; i>1; i--)//�Ƶ�����ĺ�����λ��
		{
			fread(&b, 4, 1, fp);
			a = b + 124;
			fseek(fp, a, 0);
		}
		fseek(fp, a, 0);
		if (xmsj[biaoshi - 1].hou[1] > 0)
		{
			fwrite(&wdwdz, 4, 1, fp);
			a -= 124;//�����λ��
		}
		else
		{
			xmsj[biaoshi - 1].hou[0] = wdwdz;//��ֵ
			fseek(fp, 96 + (biaoshi - 1) * 16 + 12, 0);//�ƶ�������Ŀǰ��
			fwrite(&wdwdz, 4, 1, fp);
			a = -biaoshi;
		}
		fseek(fp, wdwdz, 0);//��β����ʼ�������
		fwrite(&a, 4, 1, fp);
		fwrite(c, 1, 120, fp);
		a = 0;
		fwrite(&a, 4, 1, fp);
		xmsj[biaoshi - 1].hou[1]++;
	}
	wdwdz += 128;
	fseek(fp, 525426, 0);
	fwrite(&wdwdz, 4, 1, fp);//д��β��λ��ַ
	fflush(fp);
	return 0;
}


int CGongju::xiugaiXiangmu(short biaoshi, int chongxue, CString wen, CString da, char fenlei)
{
	if (yc < 0 || wen.GetLength() > 900 || da.GetLength() > 900 || fenlei > 63 || fenlei < 0)
	{
		return 0;
	}
	if (wen.GetLength() < 1 || da.GetLength() < 1) return 0;
	if (biaoshi < 1 || xmsj[biaoshi - 1].jieduan == -128)
	{
		return 0;
	}
	if (chongxue)//����ѧϰ���޸ľ���ɾ�������
	{
		shanchuXiangmu(biaoshi);
		tianjiaXiangmu(wen, da, fenlei);
		return 1;
	}
	wchar_t *wenti = new wchar_t[wen.GetLength() + 1];
	for (int k = 0; k < wen.GetLength() + 1; k++) wenti[k] = 0;
	lstrcpy(wenti, wen);//��CStringת��Ϊwchar_t
	wchar_t *daan = new wchar_t[da.GetLength() + 1];
	for (int k = 0; k < da.GetLength() + 1; k++) daan[k] = 0;
	lstrcpy(daan, da);//��CStringת��Ϊwchar_t
	int qian1, hou1;
	qian1 = (wen.GetLength() - 1) / 60 + 1;//�Զ���ȡ�����ֻ��һ�����
	hou1 = (da.GetLength() - 1) / 60 + 1;//�Զ���ȡ�����ֻ��һ�����
	while (1)//ɾ�����ⵥԪ����
	{
		if (qian1>xmsj[biaoshi - 1].qian[1]) tianjiaKuai(biaoshi, 1);
		else if (qian1<xmsj[biaoshi - 1].qian[1]) shanchuKuai(biaoshi, 1);
		else break;
	}
	while (1)//ɾ���𰸵�Ԫ����
	{
		if (hou1>xmsj[biaoshi - 1].hou[1]) tianjiaKuai(biaoshi, 0);
		else if (hou1<xmsj[biaoshi - 1].hou[1]) shanchuKuai(biaoshi, 0);
		else break;
	}
	//��λ�����ڴ��޸�
	if (xmsj[biaoshi - 1].jieduan > 1 && xmsj[biaoshi - 1].jieduan < 7)
	{
		dwfl[0][fenlei]++;
		dwfl[0][xmsj[biaoshi - 1].fenlei]--;
	}
	else
	{
		dwfl[1][fenlei]++;
		dwfl[1][xmsj[biaoshi - 1].fenlei]--;
	}
	//��Ŀ�����ڴ��޸�
	xmsj[biaoshi - 1].zhxgsj = xtsj;
	xmsj[biaoshi - 1].fenlei = fenlei;
	xmsj[biaoshi - 1].wenti = wen;
	xmsj[biaoshi - 1].daan = da;
	xmsj[biaoshi - 1].riqi = riqizhuanhua(xtsj);
	//��Ŀ��������޸�
	fseek(fp, 96 + (biaoshi - 1) * 16 + 5 , 0);
	fwrite(&xmsj[biaoshi - 1].zhxgsj, 2, 1, fp);
	fwrite(&xmsj[biaoshi - 1].fenlei, 1, 1, fp);
	int i;
	fseek(fp, xmsj[biaoshi - 1].qian[0], 0);//��ͷ��ʼ�������
	for (int k = 0; k < xmsj[biaoshi - 1].qian[1]; k++)//����ԭ����
	{
		fseek(fp, 4, 1);//ͷ������
		fwrite(wenti + k * 60, 2, 60, fp);//д������
		fflush(fp);//д���ǰҪˢ��
		fread(&i, 4, 1, fp);//��ȡ��һ����λ��ַ
		fseek(fp, i, 0);
	}
	fseek(fp, xmsj[biaoshi - 1].hou[0], 0);//��ͷ��ʼ�������
	for (int k = 0; k < xmsj[biaoshi - 1].hou[1]; k++)//����ԭ��
	{
		fseek(fp, 4, 1);//ͷ������
		fwrite(daan + k * 60, 2, 60, fp);//д���
		fflush(fp);//д���ǰҪˢ��
		fread(&i, 4, 1, fp);//��ȡ��һ����λ��ַ
		fseek(fp, i, 0);
	}
	fflush(fp);
	//�����ڴ��޸�
	shanchuPxlb(biaoshi);//��������
	tianjiaPxlb(biaoshi);
	//����ͷſռ�
	delete(wenti);
	delete(daan);
	return 1;
}

//�����ٽ�����ѧ��Ŀ��
int CGongju::shanchuXiangmu(short biaoshi)
{
	if (yc < 0 || biaoshi < 1 || xmsj[biaoshi - 1].jieduan == -128)
	{
		return 0;
	}
	//�ڴ��޸�
	zjyxm--;
	shanchuPxlb(biaoshi);
	if (-1 == xmsj[biaoshi - 1].jieduan)
	{
		if (dlyxs>0) dlyxs--;
		for (int i = 0; i < 15; i++)//�������ȥһ��
		{
			if (biaoshi == jydl[i].biaoshi)
			{
				jydl[i].biaoshi = 0;
				jydl[i].lianxucishu = 0;
				jydl[i].shangshengyan = 0;
				jydl[i].xiajiangyan = 0;
				break;
			}
		}
		dxxxm--;
	}
	else if (0 == xmsj[biaoshi - 1].jieduan)
	{
		shanchuJylb(biaoshi);
		dxxxm--;
	}
	else if (0 < xmsj[biaoshi - 1].jieduan)
	{
		//��������������ȥ
		for (int i = 0; i < 15; i++)
		{
			if (-biaoshi == jydl[i].biaoshi)
			{
				jydl[i].biaoshi = 0;
				jydl[i].lianxucishu = 0;
				jydl[i].shangshengyan = 0;
				jydl[i].xiajiangyan = 0;
			}
		}
		if ((shanchuFxlb(biaoshi) && (dfxxm>70)) || fxlbt->biaoshi < dfxxm)
		{
			dfxxm--;
		}
		if (6<xmsj[biaoshi - 1].jieduan) yzwxm--;
	}
	else yc = 4;//��λ��-127��-1֮��
	 //��λ�����ڴ��޸�
	if (xmsj[biaoshi - 1].jieduan > 1 && xmsj[biaoshi - 1].jieduan < 7)
	{
		dwfl[0][xmsj[biaoshi - 1].fenlei]--;
		dwfl[0][64]--;
	}
	else
	{
		dwfl[1][xmsj[biaoshi - 1].fenlei]--;
		dwfl[1][64]--;
	}
	while (shanchuKuai(biaoshi, 1));//ɾ����������
	while (shanchuKuai(biaoshi, 0));//ɾ��������
	//��Ŀ�����ڴ��޸�
	xmsj[biaoshi - 1].jieduan = -128;
	xmsj[biaoshi - 1].scsdsj = 0;
	xmsj[biaoshi - 1].zhxgsj = 0;
	xmsj[biaoshi - 1].fenlei = 0;
	xmsj[biaoshi - 1].qian[0] = 0;
	xmsj[biaoshi - 1].hou[0] = 0;
	xmsj[biaoshi - 1].qian[1] = 0;
	xmsj[biaoshi - 1].hou[1] = 0;
	xmsj[biaoshi - 1].wenti = L"";
	xmsj[biaoshi - 1].daan = L"";
	xmsj[biaoshi - 1].riqi = L"";
	//����޸�
	fseek(fp, 20, 0);
	fwrite(&dlyxs, 1, 1, fp);
	for (int i = 0; i < 15; i++)   //�������д��
	{
		fwrite(&jydl[i].biaoshi, 2, 1, fp);
		fwrite(&jydl[i].shangshengyan, 1, 1, fp);
		fwrite(&jydl[i].lianxucishu, 1, 1, fp);
		fwrite(&jydl[i].xiajiangyan, 1, 1, fp);
	}
	fseek(fp, 96 + (biaoshi - 1) * 16, 0);//�ƶ�������Ŀ
	int ii = 0;
	fwrite(&ii, 4, 1, fp);//��Ŀ����д��
	fwrite(&ii, 4, 1, fp);
	fwrite(&ii, 4, 1, fp);
	fwrite(&ii, 4, 1, fp);
	fseek(fp, 525424, 0);
	fwrite(&dfxxm, 2, 1, fp);//����ϰ��Ŀд��
	return 1;
}


// ɾ�����������е�һ�����
int CGongju::shanchuPxlb(short biaoshi)
{
	if (yc < 0)
	{
		return 0;
	}
	if (-128 == xmsj[biaoshi - 1].jieduan)
	{
		return 0;
	}
	struct pxlb *zz = pxlb,*zzz;
	while (zz->next != NULL)//�ҵ���λ��
	{
		if (zz->next->biaoshi != biaoshi) zz = zz->next;
		else break;
	}
	if (zz->next != NULL)
	{
		if (zz->next->next != NULL)
		{
			zzz = zz->next;
			zz->next->next->front = zz;
			zz->next = zz->next->next;
			delete(zzz);
		}
		else
		{
			zzz = zz->next;
			zz->next = NULL;
			delete(zzz);
		}
	}
	else return 0;
	pxlb->biaoshi--;
	return 1;
}


// ɾ�����������е�һ�����
int CGongju::shanchuJylb(short biaoshi)
{
	if (yc < 0)
	{
		return 0;
	}
	if (0 != xmsj[biaoshi - 1].jieduan)
	{
		return 0;
	}
	struct jylb *zz = jylb, *zzz;
	while (zz->next != NULL)//�ҵ���λ��
	{
		if (zz->next->biaoshi != biaoshi) zz = zz->next;
		else break;
	}
	if (zz->next != NULL)
	{
		if (zz->next->next != NULL)
		{
			zzz = zz->next;
			zz->next = zz->next->next;
			delete(zzz);
		}
		else
		{
			zzz = zz->next;
			zz->next = NULL;
			delete(zzz);
		}
	}
	else return 0;
	jylb->biaoshi--;
	return 1;
}


// ɾ����ϰ�����е�һ�����
int CGongju::shanchuFxlb(short biaoshi)
{
	if (yc < 0)
	{
		return 0;
	}
	if (-128 == xmsj[biaoshi - 1].jieduan)
	{
		return 0;
	}
	struct fxlb *zz = fxlbt, *zzz;
	while (zz->next != NULL)//�ҵ���λ��
	{
		if (zz->next->biaoshi != biaoshi) zz = zz->next;
		else break;
	}
	if (zz->next != NULL)
	{
		if (zz->next->next != NULL)
		{
			zzz = zz->next;
			zz->next = zz->next->next;
			delete(zzz);
		}
		else
		{
			zzz = zz->next;
			zz->next = NULL;
			fxlbw = zz;
			delete(zzz);
		}
	}
	else return 0;
	fxlbt->biaoshi--;
	return 1;
}


// ����Ϊ����λ��
int CGongju::daochu(CString dizhi, char fenlei)
{
	if (yc < 0)
	{
		return 0;
	}
	FILE* fbc;
	if (0 != _wfopen_s(&fbc, dizhi, L"wb+"))
	{
		return 0;
	}
	wchar_t bom = 0xFEFF;
	fwrite(&bom, 2, 1, fbc);//д��Unicode��ʶ
	if (fenlei<0 || fenlei>63)//ȫ������
	{
		for (int i = 0; i < 32704; i++)
		{
			if (xmsj[i].jieduan != -128 && xmsj[i].wenti != ""&&xmsj[i].daan != "")
			{
				fwprintf(fbc, L"fenlei:%s\r\n", flqk[xmsj[i].fenlei].name);
				fwprintf(fbc, L"wenti:\r\n%s\r\n", xmsj[i].wenti);
				fwprintf(fbc, L"daan:\r\n%s\r\n\r\n", xmsj[i].daan);
			}
		}
	}
	else//�ַ��ദ��
	{
		fwprintf(fbc, L"fenlei:%s\r\n", flqk[fenlei].name);
		for (int i = 0; i < 32704; i++)
		{
			if (xmsj[i].jieduan != -128 && xmsj[i].fenlei==fenlei && xmsj[i].wenti != ""&&xmsj[i].daan != "")
			{
				fwprintf(fbc, L"wenti:\r\n%s\r\n", xmsj[i].wenti);
				fwprintf(fbc, L"daan:\r\n%s\r\n\r\n", xmsj[i].daan);
			}
		}
	}
	fclose(fbc);
	return 1;
}


// ���쳣����0����Ա�����
int CGongju::BEI_FEN()
{
	if (yc < 0)
	{
		return 0;
	}
	CString s(L"C:\\Users\\Public\\���丨���ı����ļ�.ysj");
	if (yc>0)
	{
		s = L"C:\\Users\\Public\\���丨���쳣ǰ�ı����ļ�.ysj";
		FILE *f,*ff;
		if (0 != _wfopen_s(&ff, L"C:\\Users\\Public\\���丨���ı����ļ�.ysj", L"rb+"))
		{
			return 0;
		}
		if (0 != _wfopen_s(&f, s, L"wb+"))
		{
			return 0;
		}
		fseek(ff, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
		int n = ftell(ff);//�ļ���С��ȡ
		char *bf = new char[n];
		fseek(ff, 0, 0);
		fread(bf, 1, n, ff);
		fseek(f, 0, 0);//��ʼд��
		fwrite(bf, 1, n, f);
		fclose(f);
		delete(bf);
		return 1;
	}
	else
	{
		fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
		int n = ftell(fp);//�ļ���С��ȡ
		char *bf = new char[n];
		fseek(fp, 0, 0);
		fread(bf, 1, n, fp);
		FILE *f;
		if (0 != _wfopen_s(&f, s, L"wb+"))
		{
			return 0;
		}
		fseek(f, 0, 0);//��ʼд��
		fwrite(bf, 1, n, f);
		fclose(f);
		delete(bf);
		return 2;
	}
	return 3;
}


int CGongju::xiugaiFenleiming(char fenlei, CString mingzi)
{
	if (yc < 0 || fenlei > 63 || fenlei < 1 || mingzi.GetLength() == 0)
	{
		return 0;
	}
	if (mingzi.GetLength()>16 || 0 == flqk[fenlei].cunzai)
	{
		return 0;
	}
	if (mingzi.Find(L" ") != -1)//�����пո�
	{
		return 0;
	}
	if (mingzi=="δ����")//������Ĭ��
	{
		return 0;
	}
	lstrcpy(flqk[fenlei].name, mingzi);
	fseek(fp, 523368 + fenlei * 32 , 0);
	fwrite(flqk[fenlei].name, 2, 16, fp);//д���������
	unsigned char a[8] = { 0 };
	for (int i = 0,j=0; i < 8; i++)
	{
		if (flqk[j++].cunzai) a[i] = a[i] | 0x80;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x40;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x20;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x10;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x08;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x04;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x02;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x01;
	}
	fseek(fp, 523360, 0);
	fwrite(a, 1, 8, fp);//д�������
	fflush(fp);//ˢ�£�����д��
	return 1;
}


int CGongju::tianjiaFenlei(CString name)
{
	if (yc < 0 || name.GetLength()>16 || name.GetLength() == 0)
	{
		return 0;
	}
	if (name.Find(L" ") != -1)//�����пո�
	{
		return 0;
	}
	if (name == "δ����")//������Ĭ��
	{
		return 0;
	}
	int i;
	for (i = 0; i < 64; i++)
	{
		if (!flqk[i].cunzai) break;
	}
	if (64 == i) return -1;
	flqk[i].cunzai = 1;
	if (!xiugaiFenleiming(i,name)) return -2;
	return 1;
}


// ɾ��һ������
int CGongju::shanchufenlei(char fenlei)
{
	if (yc < 0 || fenlei > 63 || fenlei < 1 || !flqk[fenlei].cunzai)
	{
		return 0;
	}
	for (int i = 0; i < 32704; i++)
	{
		if (xmsj[i].jieduan == -128) continue;
		if (fenlei == xmsj[i].fenlei) shanchuXiangmu(i + 1);
	}
	flqk[fenlei].cunzai = 0;
	char b[32] = { 0 };
	fseek(fp, 523368 + fenlei * 32, 0);
	fwrite(b, 1, 32, fp);//д���
	unsigned char a[8] = { 0 };
	for (int i = 0, j = 0; i < 8; i++)
	{
		if (flqk[j++].cunzai) a[i] = a[i] | 0x80;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x40;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x20;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x10;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x08;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x04;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x02;
		if (flqk[j++].cunzai) a[i] = a[i] | 0x01;
	}
	fseek(fp, 523360, 0);
	fwrite(a, 1, 8, fp);//д�������
	fflush(fp);//ˢ�£�����д��
	return 1;
}


// ����������еĿհ״������
int CGongju::buchongJydl()
{
	if (yc < 0 || zjyxm < 15 || dxxxm < 0)
	{
		return 0;
	}
	int suiji,biaoshi,t;
	if (0 >= dlyxs) t = 1;
	else t = 0;
	for (int i = 0; i < 15; i++)
	{
		if (0 >= jydl[i].biaoshi && 0<jylb->biaoshi)
		{
			suiji = rand() % jylb->biaoshi;//�����
			jylbyd = jylb;
			for (int j = 0; j < suiji; j++)
			{
				jylbyd = jylbyd->next;
			}
			biaoshi = jylbyd->next->biaoshi;
			shanchuJylb(biaoshi);//ɾ���ý��
			jydl[i].biaoshi = biaoshi;
			jydl[i].lianxucishu = 0;
			jydl[i].shangshengyan = 0;
			jydl[i].xiajiangyan = 0;
			xmsj[biaoshi - 1].jieduan = -1;
			fseek(fp, 96 + (biaoshi - 1) * 16, 0);
			short iii = 1;
			fwrite(&iii, 2, 1, fp);
			fwrite(&xmsj[biaoshi - 1].jieduan, 1, 1, fp);//д��׶�
		}
		int cf;//�ظ�
		if (0 == jydl[i].biaoshi && 0 == jylb->biaoshi)
		{
			suiji = rand() % 32704;
			for (int j = 0; j < 32704; j++)
			{
				if (xmsj[suiji % 32704].jieduan>0)
				{
					cf = 0;
					for (int k = 0; k < 15; k++)
					{
						if ((suiji % 32704) + 1 == abs(jydl[k].biaoshi))
						{
							cf = 1;
							break;
						}
					}
					if (cf) suiji++;
					else break;
				}
				else suiji++;
			}
			biaoshi = suiji % 32704 + 1;
			jydl[i].biaoshi = -biaoshi;
			jydl[i].lianxucishu = 0;
			jydl[i].shangshengyan = 0;
			jydl[i].xiajiangyan = 0;
		}
	}
	if (t) //ѧ��һ���ؼƶ�����Ч��
	{
		dlyxs = 0;
		for (int i = 0; i < 15; i++)
		{
			if (0 < jydl[i].biaoshi)
			{
				dlyxs++;
			}
		}
	}
	д��������();
	return 1;
}


int CGongju::д��������()
{
	fseek(fp, 20, 0);
	fwrite(&dlyxs, 1, 1, fp);
	for (int i = 0; i < 15; i++)   //�������д��
	{
		fwrite(&jydl[i].biaoshi, 2, 1, fp);
		fwrite(&jydl[i].shangshengyan, 1, 1, fp);
		fwrite(&jydl[i].lianxucishu, 1, 1, fp);
		fwrite(&jydl[i].xiajiangyan, 1, 1, fp);
	}
	fflush(fp);
	return 1;
}


int CGongju::ѧϰһ��(int �ɹ�)
{
	if (yc < 0 || zjyxm < 15 || dlyxs < 1)
	{
		return 0;
	}
	int biaoshi, ii=0;
	char lianxucishu, shangshengyan, xiajiangyan;
	lianxucishu = jydl[0].lianxucishu;//�뱣������
	shangshengyan = jydl[0].shangshengyan;
	xiajiangyan = jydl[0].xiajiangyan;
	if (!�ɹ�&&jydl[0].biaoshi < 0)
	{
		biaoshi = jydl[0].biaoshi;
		for (int i = 0; i < 14; i++)//ȫ��ǰ��
		{
			jydl[i].biaoshi = jydl[i + 1].biaoshi;
			jydl[i].lianxucishu = jydl[i + 1].lianxucishu;
			jydl[i].shangshengyan = jydl[i + 1].shangshengyan;
			jydl[i].xiajiangyan = jydl[i + 1].xiajiangyan;
		}
		jydl[14].biaoshi = biaoshi;
		jydl[14].lianxucishu = 0;
		jydl[14].shangshengyan = 0;
		jydl[14].xiajiangyan = 0;
		д��������();
		return 1;
	}
	if (�ɹ�&&jydl[0].biaoshi < 0)
	{
		for (int i = 0; i < 14; i++)//ȫ��ǰ��
		{
			jydl[i].biaoshi = jydl[i + 1].biaoshi;
			jydl[i].lianxucishu = jydl[i + 1].lianxucishu;
			jydl[i].shangshengyan = jydl[i + 1].shangshengyan;
			jydl[i].xiajiangyan = jydl[i + 1].xiajiangyan;
		}
		jydl[14].biaoshi = 0;
		jydl[14].lianxucishu = 0;
		jydl[14].shangshengyan = 0;
		jydl[14].xiajiangyan = 0;
		buchongJydl();
		return 1;
	}
	if (�ɹ�&&jydl[0].lianxucishu>=3)
	{
		dxxxm--;
		fxjz[3]++;
		fseek(fp, 525416 + 6, 0);//�����ѱ���Ŀ��λ��
		fwrite(&fxjz[3], 2, 1, fp);
		biaoshi = jydl[0].biaoshi;
		if (1 == jydl[0].shangshengyan)
		{
			xmsj[biaoshi - 1].jieduan = 2;//��λ��2
			dwfl[1][xmsj[biaoshi - 1].fenlei]--;
			dwfl[1][64]--;
			dwfl[0][xmsj[biaoshi - 1].fenlei]++;
			dwfl[0][64]++;
		}
		else xmsj[biaoshi - 1].jieduan = 1;//��λ��1
		xmsj[biaoshi - 1].scsdsj = xtsj;//�״�����ʱ��
		fseek(fp, 96 + (biaoshi - 1) * 16, 0);//��Ŀ��λ��
		short iii = 1;
		fwrite(&iii, 2, 1, fp);
		fwrite(&xmsj[biaoshi - 1].jieduan, 1, 1, fp);
		fwrite(&xtsj, 2, 1, fp);
		fflush(fp);//ˢ��д��
		if (rand() % 2 + rand() % 2)//һ�����ʲ�ǰ��
		{
			for (int i = 0; i < 14; i++)//ȫ��ǰ��
			{
				jydl[i].biaoshi = jydl[i + 1].biaoshi;
				jydl[i].lianxucishu = jydl[i + 1].lianxucishu;
				jydl[i].shangshengyan = jydl[i + 1].shangshengyan;
				jydl[i].xiajiangyan = jydl[i + 1].xiajiangyan;
			}
			jydl[14].biaoshi = 0;
			jydl[14].lianxucishu = 0;
			jydl[14].shangshengyan = 0;
			jydl[14].xiajiangyan = 0;
		}
		else
		{
			jydl[0].biaoshi = 0;
			jydl[0].lianxucishu = 0;
			jydl[0].shangshengyan = 0;
			jydl[0].xiajiangyan = 0;
		}
		buchongJydl();
		dlyxs--;
		д��������();
		return 1;
	}
	if (�ɹ�)//����δ��ȫ��ס
	{
		biaoshi = jydl[0].biaoshi;
		lianxucishu++;
		if (1 == lianxucishu && 127 != shangshengyan)
		{
			shangshengyan++;
			if (xiajiangyan > 0) xiajiangyan--;
		}
		else xiajiangyan = 0;
		for (ii = 0; ii < jiange[lianxucishu-1]; ii++)//���ʵ�λ��
		{
			jydl[ii].biaoshi = jydl[ii + 1].biaoshi;
			jydl[ii].lianxucishu = jydl[ii + 1].lianxucishu;
			jydl[ii].shangshengyan = jydl[ii + 1].shangshengyan;
			jydl[ii].xiajiangyan = jydl[ii + 1].xiajiangyan;
		}
		jydl[ii].biaoshi = biaoshi;
		jydl[ii].lianxucishu = lianxucishu;
		jydl[ii].shangshengyan = shangshengyan;
		jydl[ii].xiajiangyan = xiajiangyan;
		д��������();
		return 1;
	}
	//δ��ס��ʱ��
	biaoshi = jydl[0].biaoshi;
	if (lianxucishu > 1) xiajiangyan = 0;
	else if (lianxucishu == 0 && xiajiangyan < jiange[0] - 1) xiajiangyan++;//�½���Խ����λԽ��
	lianxucishu = 0;
	for (ii = 0; ii < jiange[0] - xiajiangyan; ii++)//��λ���ʵ�����λ��
	{
		jydl[ii].biaoshi = jydl[ii + 1].biaoshi;
		jydl[ii].lianxucishu = jydl[ii + 1].lianxucishu;
		jydl[ii].shangshengyan = jydl[ii + 1].shangshengyan;
		jydl[ii].xiajiangyan = jydl[ii + 1].xiajiangyan;
	}
	jydl[ii].biaoshi = biaoshi;
	jydl[ii].lianxucishu = lianxucishu;
	jydl[ii].shangshengyan = shangshengyan;
	jydl[ii].xiajiangyan = xiajiangyan;
	д��������();
	return 1;
}


int CGongju::��ϰһ��(int �ɹ�)
{
	if (yc < 0 || zjyxm < 15 || dfxxm < 1)
	{
		return 0;
	}
	struct fxlb *zz = fxlbt, *zzz = fxlbt;
	int shibaicharu = 12;//��ϰʧ�ܲ���λ��,���shibaicharu-1��
	if (!�ɹ�)//��ϰʧ��
	{
		if (126>fxlbt->next->pingyancishu) fxlbt->next->pingyancishu++;
		fseek(fp, 96 + (fxlbt->next->biaoshi - 1) * 16, 0);
		char iii = fxlbt->next->pingyancishu + 1;
		fwrite(&iii, 1, 1, fp);//д��ƽ�ش�����һ
		fflush(fp);
		for (int i = 0; i < shibaicharu; i++)//�ҵ�λ��
		{
			if (zz->next != NULL) zz = zz->next;
			else break;
		}
		if (zz->next == NULL)//����
		{
			zz->next = fxlbt->next;
			fxlbt->next = fxlbt->next->next;
			fxlbw = zz->next;
			fxlbw->next = NULL;
		}
		else
		{
			zzz = fxlbt->next;
			fxlbt->next = fxlbt->next->next;
			zzz->next = zz->next;
			zz->next = zzz;
		}
		return 1;
	}
	//��ϰ�ɹ�
	dfxxm--;
	int biaoshi = fxlbt->next->biaoshi, duan = 1;
	int i = xtsj - xmsj[biaoshi - 1].scsdsj;
	if (i / ddyts[5] >= 1) duan = 6;//������Զ�λ
	else if (i / ddyts[4] >= 1) duan = 5;
	else if (i / ddyts[3] >= 1) duan = 4;
	else if (i / ddyts[2] >= 1) duan = 3;
	else if (i / ddyts[1] >= 1) duan = 2;
	else duan = 1;
	duan = duan - fxlbt->next->pingyancishu + 1;
	if (duan < 1) duan = 1;//�õ����ն�λ
	//��λ�����޸�
	if ((1 == duan || 7 == duan) && (xmsj[biaoshi - 1].jieduan>1 && xmsj[biaoshi - 1].jieduan < 7))
	{
		dwfl[1][xmsj[biaoshi - 1].fenlei]++;
		dwfl[1][64]++;
		dwfl[0][xmsj[biaoshi - 1].fenlei]--;
		dwfl[0][64]--;
	}
	else if ((1 < duan && 7 > duan) && (xmsj[biaoshi - 1].jieduan == 1 || xmsj[biaoshi - 1].jieduan == 7))
	{
		dwfl[1][xmsj[biaoshi - 1].fenlei]--;
		dwfl[1][64]--;
		dwfl[0][xmsj[biaoshi - 1].fenlei]++;
		dwfl[0][64]++;
	}
	if (duan > 6) yzwxm++;//��������Ŀ
	xmsj[biaoshi - 1].jieduan = duan;
	if (duan == 1) xmsj[biaoshi - 1].scsdsj = xtsj;
	else xmsj[biaoshi - 1].scsdsj = xtsj - ddyts[duan - 2];
	shanchuFxlb(biaoshi);
	fseek(fp, 96 + (biaoshi - 1) * 16, 0);//��Ŀ��λ��
	short iii = 1;
	fwrite(&iii, 2, 1, fp);
	fwrite(&xmsj[biaoshi - 1].jieduan, 1, 1, fp);
	fwrite(&xmsj[biaoshi - 1].scsdsj, 2, 1, fp);
	fseek(fp, 525416 + 8, 0);
	fwrite(&dfxxm, 2, 1, fp);//����ϰ��Ŀ
	fflush(fp);
	if (dfxxm <= 0 || 1 >= fxlbt->biaoshi || xmsj[fxlbt->next->biaoshi - 1].jieduan <= 1) return 2;
	if (��ȡƽ�ؼ�һ(fxlbt->next->biaoshi) > 1) return 3;//����������������Ҫ����
	int suiji = rand() % fxlbt->biaoshi;//��λ����1�Ĵ���������ģ���ֹ������ܸ�ϰ����
	if (suiji == 0) return 4;//��һ����㱾�����ǵ�һ�����û�
	for (int i = 0; i <= suiji; i++)//�ҵ�λ��
	{
		if (zz->next != NULL)
		{
			zzz = zz;
			zz = zz->next;
		}
		else break;
	}
	if (suiji <= shibaicharu && 0 < zz->pingyancishu) return 5;//û�����������Ӻ�Ĳ���
	if (zz->next == NULL)//�ᵽ��ǰ��
	{
		zz->next = fxlbt->next;
		fxlbt->next = zz;
		fxlbw = zzz;
		fxlbw->next = NULL;
	}
	else
	{
		zzz->next = zz->next;
		zz->next = fxlbt->next;
		fxlbt->next = zz;
	}
	if (zz->next == zzz) return 6; //���ڲ���Ҫ����
	//��zz->next����zzz���棬ʵ�ֽ���
	if (zzz->next == NULL)
	{
		zzz->next = zz->next;
		zz->next = zz->next->next;
		fxlbw = zzz->next;
		fxlbw->next = NULL;
	}
	else
	{
		zz = zz->next;
		fxlbt->next->next = fxlbt->next->next->next;
		zz->next = zzz->next;
		zzz->next = zz;
	}
	return 1;
}


int CGongju::�����ʼ��(char fenlei)
{
	if (yc < 0 || zjyxm < 15 || dwfl[0][64] < 1)
	{
		return 0;
	}
	if (fenlei<0 || fenlei>63)//ȫ��
	{
		for (int i = 0; i < 32704; i++)
		{
			if (1 < xmsj[i].jieduan && 7 > xmsj[i].jieduan)
			{
				��������[��������[32704]++] = i + 1;
			}
		}
	}
	else //ĳ��������з���
	{
		for (int i = 0; i < 32704; i++)
		{
			if (1 < xmsj[i].jieduan && 7 > xmsj[i].jieduan && xmsj[i].fenlei == fenlei)
			{
				��������[��������[32704]++] = i + 1;
			}
		}
	}
	��ȡ����();
	return 1;
}


int CGongju::����һ��(int �ɹ�)
{
	if (yc < 0 || zjyxm < 15 || ��������[32704] < 1)
	{
		return 0;
	}
	short ls;
	int i = rand() % ��������[32704];
	if (�ɹ�)
	{
		��������[32704]--;
		��������[0] = ��������[��������[32704]];
	}
	else
	{
		ls = ��������[0];
		��������[0] = ��������[i];
		��������[i] = ls;
	}
	return 1;
}


short CGongju::��ȡ����()//���ڴ���˳��
{
	if (yc < 0 || zjyxm < 15 || ��������[32704] < 1)
	{
		return 0;
	}
	short luanxu[32704];
	int i, j;
	for (i = ��������[32704]; i>0; i--)
	{
		j = rand() % i;
		luanxu[i - 1] = ��������[j];
		while (j < i - 1)
		{
			��������[j] = ��������[j + 1];
			j++;
		}
	}
	for (i = 0; i < ��������[32704]; i++)
	{
		��������[i] = luanxu[i];
	}
	return ��������[0];
}


char CGongju::��ȡƽ�ؼ�һ(short biaoshi)
{
	if (yc < 0 || 0 > xmsj[biaoshi - 1].jieduan)
	{
		return 0;
	}
	if (1 > xmsj[biaoshi - 1].jieduan)
	{
		return 1;
	}
	char a = 1;
	struct fxlb *zz = fxlbt;
	while (zz->next != NULL)//�ҵ���λ��
	{
		if (zz->next->biaoshi != biaoshi) zz = zz->next;
		else break;
	}
	if (zz->next != NULL)
	{
		a = zz->next->pingyancishu + 1;
	}
	else
	{
		a = 1;
	}
	return a;
}


char CGongju::�������(CString fenlei)//���ط�����
{
	if (yc < 0 || fenlei.GetLength() <= 0)
	{
		return 0;
	}
	char cunzai = 0;
	for (int i = 0; i < 64; i++)
	{
		if (flqk[i].cunzai && fenlei == flqk[i].name)
		{
			cunzai = i;
			break;
		}
	}
	return cunzai;
}


// ����Ŀ��fenlei1�ƶ���fenlei2�������ƶ�����
int CGongju::�ƶ�����(char fenlei1, char fenlei2)
{
	if (yc < 0 || fenlei1 < 0 || fenlei2 < 0 || fenlei1 > 63 || fenlei2 > 63 || fenlei1 == fenlei2)
	{
		return 0;
	}
	if (flqk[fenlei1].cunzai == 0 || flqk[fenlei2].cunzai == 0) return 0;
	int ci = 0;//�ƶ�����
	for (int i = 0; i < 32704; i++)
	{
		if (-128 != xmsj[i].jieduan&&xmsj[i].fenlei == fenlei1)
		{
			if (xmsj[i].jieduan > 1 && xmsj[i].jieduan < 7)//��λ�����޸�
			{
				dwfl[0][fenlei1]--;
				dwfl[0][fenlei2]++;
			}
			else
			{
				dwfl[1][fenlei1]--;
				dwfl[1][fenlei2]++;
			}
			xmsj[i].fenlei = fenlei2;
			fseek(fp, 96 + i * 16 + 7, 0);
			fwrite(&fenlei2, 1, 1, fp);
			ci++;
		}
	}
	fflush(fp);
	return ci;
}


void CGongju::��������()
{
	fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
	int n = ftell(fp);//�ļ���С��ȡ
	if (wdwdz*1.3 < n)//�ļ�����ʱ��������
	{
		char *cc = new char[wdwdz];
		fseek(fp, 0, 0);//�Ƶ���ͷ
		fread(cc, 1, wdwdz, fp);
		fclose(fp);
		if (0 != _wfopen_s(&fp, lujing, L"wb+"))
		{
			yc = -4;//�������
			return;
		}
		fwrite(cc, 1, wdwdz, fp);
		fflush(fp);
		delete(cc);
	}
}
