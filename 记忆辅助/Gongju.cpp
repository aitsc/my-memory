#include "stdafx.h"
#include "Gongju.h"
#define YEAR 2015 //除2015/2/22以外都是测试时间
#define MONTH 2
#define DAY 22

CGongju::CGongju()
: fp(NULL)
, lujing(_T(""))
{
	//用户名
	yhm[0] = 0;
	yhm[1] = 0;
	yhm[2] = 0;
	yhm[3] = 0;
	yhm[4] = 0;
	yhm[5] = 0;
	//段对应天数
	ddyts[0] = 1;
	ddyts[1] = 2;
	ddyts[2] = 4;
	ddyts[3] = 7;
	ddyts[4] = 15;
	ddyts[5] = 35;
	//连续答对次数所有的间隔
	jiange[0] = 5;
	jiange[1] = 7;
	jiange[2] = 14;
	jiange[3] = 14;
	//异常
	yc = 0;
	//项目数据
	for (int i=0; i < 32704;i++)
	{
		xmsj[i].qian[1] = 0;
		xmsj[i].hou[1] = 0;
		xmsj[i].wenti = L"";
		xmsj[i].daan = L"";
	}
	//分类情况
	for (int i = 0; i < 64; i++)
	{
		flqk[0].cunzai = 0; //初始化不存在处理
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
	//链表头指针初始化
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
	for (int i = 0; i < 32705; i++) 反向数组[i] = 0;
}


CGongju::~CGongju()
{
	//释放申请的空间
	while (fxlbt != NULL)//释放
	{
		fxlbw = fxlbt;
		fxlbt = fxlbt->next;
		delete(fxlbw);
	}
	while (pxlb->next != NULL)//释放
	{
		pxlb = pxlb->next;
		delete(pxlb->front);
	}
	delete(pxlb);
	struct jylb *jy;//释放
	while (jylb != NULL)
	{
		jy = jylb;
		jylb = jylb->next;
		delete(jy);
	}
}


int CGongju::riqizhuanhua(int year, int month, int day)
{
	if (year<YEAR) return -2; //时间在标准时间之后错误
	if (year == YEAR && month<MONTH) return -2;
	if (year == YEAR && month==MONTH && day < DAY) return -2;
	//保证月和日是正确的
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
	for (i = 0; !(year >= year1 && month >= month1 && day >= day1); i++)//计算间隔天数
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day <= 30) day++;//如果没到月底
			else   //如果到月底
			{
				if (month != 12)//如果到月底没到年底
				{
					day = 1;
					month++;
				}
				else  //如果到月底到年底
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
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) day++;//闰年
				else//不是闰年
				{
					day = 1;
					month++;
				}
			}
			else //2月29号时
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
			if (day <= 30) day++;//如果没到月底
			else   //如果到月底
			{
				if (month != 12)//如果到月底没到年底
				{
					day = 1;
					month++;
				}
				else  //如果到月底到年底
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
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) day++;//闰年
				else//不是闰年
				{
					day = 1;
					month++;
				}
			}
			else //2月29号时
			{
				day = 1;
				month++;
			}
		}
	}
	CString s;
	s.Format(L"%d年%d月%d日", year,month,day);
	return s;
}


void CGongju::chushihua()
{
	if (YEAR != 2015 || MONTH != 2 || DAY != 22)
	{
		AfxMessageBox(L"测试版本！（不想进入关闭后台）");
	}
	CTime t = CTime::GetCurrentTime();
	xtsj = riqizhuanhua(t.GetYear(), t.GetMonth(), t.GetDay());
	if (0 >= xtsj)
	{
		yc = -1;//系统时间错误！
		return;
	}
	if (32767 < xtsj)
	{
		yc = -2;//系统时间溢出！
		return;
	}
	fflush(fp);//写后读前要刷新
	fseek(fp, 2, 0);
	fread(yhm, 2, 5, fp);
	fseek(fp, 16, 0);
	fread(&fsj, 2, 1, fp);
	fread(&lsj, 2, 1, fp);
	if (!(xtsj >= lsj&&lsj >= fsj))
	{
		yc = -3;//时间不匹配！
		return;
	}
	if (lsj > 0 && xtsj - lsj > 9)
	{
		if (IDNO == AfxMessageBox(L"注意！您确定系统时间正确？", MB_YESNO))
		{
			yc = -4;
			return;
		}
		else yc = 1;
	}
	fread(&dlyxs, 1, 1, fp);
	int jj = 0;
	for (int i = 0; i < 15; i++)   //记忆队列读取
	{
		fread(&jydl[i].biaoshi, 2, 1, fp);
		fread(&jydl[i].shangshengyan, 1, 1, fp);
		fread(&jydl[i].lianxucishu, 1, 1, fp);
		fread(&jydl[i].xiajiangyan, 1, 1, fp);
		if (0 < jydl[i].biaoshi) jj++;
	}
	if (dlyxs > jj)
	{
		yc = 21;//数据出现错误
		dlyxs = jj;
	}
	//时间太长平沿清零
	if (lsj > 0 && xtsj - lsj > 2)
	{
		for (int i = 0; i < 15; i++)
		{
			jydl[i].shangshengyan = 0;
			jydl[i].lianxucishu = 0;
			jydl[i].xiajiangyan = 0;
		}
		写入记忆队列();
	}
	//项目数据读取
	int weizhi,a,q=0;
	short b;
	int cc1, cc2;
	wchar_t c[61]; c[60] = 0;
	for (int i = 0; i < 32704; i++)
	{
		fread(&b, 2, 1, fp);//标识
		if (b <= 0) //无数据
		{
			fseek(fp, 14, 1);
			xmsj[i].jieduan = -128;
			continue;
		}
		if (b >127) yc = 22;//数据可能存在损坏！
		fread(&xmsj[i].jieduan, 1, 1, fp);//阶段
		fread(&xmsj[i].scsdsj, 2, 1, fp);//首次升段时间
		fread(&xmsj[i].zhxgsj, 2, 1, fp);//最后修改时间
		fread(&xmsj[i].fenlei, 1, 1, fp);//分类
		fread(&xmsj[i].qian[0], 4, 1, fp);//前驱问题
		fread(&xmsj[i].hou[0], 1, 4, fp);//后驱答案
		xmsj[i].riqi = riqizhuanhua(xmsj[i].zhxgsj);//最后修改时间字符串格式
		tianjiaFxlb(i + 1, b);
		weizhi = ftell(fp);
		if (xmsj[i].qian[0]<525430 || xmsj[i].hou[0]<525430)
		{
			yc = 23;//数据可能存在损坏！
			continue;
		}
		fseek(fp, xmsj[i].qian[0], 0);//准备读取问题
		cc1 = i + 1;
		a = xmsj[i].qian[0];
		q=0;
		do
		{
			q++;
			if (q <= 15) ; //限制900字
			else
			{
				yc = 24;//数据可能存在损坏！
				break;
			}
			fread(&cc2, 4, 1, fp);
			if (cc1 == cc2) cc1 = a;
			else
			{
				yc = 28;//前驱错误！
			}
			fread(c, 2, 60, fp);//读取内容
			xmsj[i].wenti += c;//内容赋值
			fread(&a, 4, 1, fp);//判断是否结束的标记
			xmsj[i].qian[1]++;//数据单元个数
			fseek(fp, a, 0);//下一个块的开头
		} while (525430 <= a);
		if (16 == q) xmsj[i].qian[1] = 0;
		fseek(fp, xmsj[i].hou[0], 0);//准备读取答案
		cc1 = -(i + 1);
		a = xmsj[i].hou[0];
		q = 0;
		do
		{
			q++;
			if (q <= 15) ; //限制900字
			else
			{
				yc = 24;//数据可能存在损坏！
				break;
			}
			fread(&cc2, 4, 1, fp);
			if (cc1 == cc2) cc1 = a;
			else
			{
				yc = 28;//前驱错误！
			}
			fread(c, 2, 60, fp);//读取内容
			xmsj[i].daan += c;//内容赋值
			fread(&a, 4, 1, fp);//判断是否结束的标记
			xmsj[i].hou[1]++;//数据单元个数
			fseek(fp, a, 0);//下一个块的开头
		} while (525430 <= a);
		if (16 == q) xmsj[i].hou[1] = 0;
		fseek(fp, weizhi, 0);
	}
	//分类情况读取
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
	lstrcpyW(flqk[0].name, L"未分类");
	fread(fxjz, 2, 4, fp);  //读取复习基准
	if (!(xtsj >= fxjz[2] && fxjz[2] >= fxjz[0]))
	{
		yc = -3;//时间不匹配！
		return;
	}
	fread(&dfxxm, 2, 1, fp);  //读取待复习项目
	fread(&wdwdz, 4, 1, fp);  //读取尾地址
	//设定与外存不直接相关的变量
	for (int i = 0; i < 32704; i++)
	{
		if (-128 == xmsj[i].jieduan) continue;
		zjyxm++;//总记忆项目
		tianjiaPxlb(i+1);
		if (xmsj[i].jieduan == -1) //检测学习队列是否存在
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
				xiugaiJieduan(i + 1, 0);//不在的时候
			}
		}
		if (xmsj[i].jieduan > 1 && xmsj[i].jieduan < 7) dwfl[0][xmsj[i].fenlei]++;//段位分类
		else dwfl[1][xmsj[i].fenlei]++;//段位分类
		if (xmsj[i].jieduan <= 0) dxxxm++;//待学习项目
		if (xmsj[i].jieduan > 6) yzwxm++;//已掌握项目
		tianjiaJylb(i+1);
	}
	//段位分类总数确定
	for (int j = 0; j<64; j++)
	{
		dwfl[0][64] += dwfl[0][j];
	}
	for (int j = 0; j<64; j++)
	{
		dwfl[1][64] += dwfl[1][j];
	}
	 //复习个数确定
	if (fxjz[2] < xtsj)//是当天则不需要
	{
		if (xtsj - fxjz[2] > 7)//全超过7天了
		{
			fxjz[0] = xtsj;
			fxjz[1] = 0;
		}
		else
		{
			if (xtsj - fxjz[0] > 7)//只有前者超过7天
			{
				fxjz[0] = fxjz[2];
				fxjz[1] = fxjz[3];
			}
			else
			{
				if (fxjz[1] <= fxjz[3])//加等于保证天数最新的
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
			fxjz[1] = 0;//意外的破坏时
		}
		if (dfxxm < 0)
		{
			yc = 26;
			dfxxm = 0;//意外的破坏时
		}
		if (fxjz[1] * 7 / 3 > 25) dfxxm += fxjz[1] * 7 / 3 + 5;
		else dfxxm += 25;
		if (dfxxm>fxlbt->biaoshi) dfxxm = fxlbt->biaoshi;//复习个数的上限
		fseek(fp, 525416, 0);//写入修改的数据的位置
		fwrite(fxjz, 2, 4, fp);
		fwrite(&dfxxm, 2, 1, fp);
		fflush(fp);
	}
	fseek(fp, 0, SEEK_END);//文件指针移动到末尾
	int n = ftell(fp);//文件大小获取
	if (wdwdz<525430 || wdwdz>n) yc = 27;//尾单位出错
	重新整理();
	//超过5天记忆队列重置0
	if (lsj > 0 && xtsj - lsj >= 5)
	{
		for (int i = 0; i < 15; i++)  
		{
			jydl[i].shangshengyan = 0;
			jydl[i].lianxucishu = 0;
			jydl[i].xiajiangyan = 0;
		}
		dlyxs = 0;
		写入记忆队列();
	}
	//复习队列最后一个移到最前，降低关闭打开对平沿大于0的全部靠前的影响
	if (fxlbt->biaoshi>1)
	{
		struct fxlb *ff;
		for (ff = fxlbt; ff->next != fxlbw; ff = ff->next);
		fxlbw->next = fxlbt->next;
		fxlbt->next = fxlbw;
		fxlbw = ff;
		fxlbw->next = NULL;
	}
	//随机数种子
	srand(time(0)*time(0));
}


// 排序链表插入一个新的项目,降序排序
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

//修改内存和外存的项目的阶段
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
	fflush(fp);//刷新，立即写入
	return 1;
}


// 记忆链表，增加一个结点
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


// 复习链表
int CGongju::tianjiaFxlb(int biaoshi, int b)
{
	if (yc < 0)
	{
		return 0;
	}
	if (0 >= xmsj[biaoshi - 1].jieduan || 7 <= xmsj[biaoshi - 1].jieduan)
	{
		return 0;//1到6段之外不行
	}
	if (xmsj[biaoshi - 1].scsdsj + ddyts[xmsj[biaoshi - 1].jieduan-1] > xtsj)
	{
		return 0;
	}
	struct fxlb *zzz = new struct fxlb;
	zzz->biaoshi = biaoshi;//标识
	if (b > 0 && b <= 128)
		zzz->pingyancishu = b - 1;//平沿次数
	else
		zzz->pingyancishu = 0;
	if (1 == xmsj[biaoshi - 1].jieduan || zzz->pingyancishu > 0)//一段和平沿大于0的在前面
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
	fxlbt->biaoshi++;//复习的个数
	return 1;
}


// 修改用户名
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
	if (YHM.Find(L" ") != -1)//不能有空格
	{
		return 0;
	}
	lstrcpy(yhm,YHM);
	fseek(fp, 2, 0);
	fwrite(yhm, 2, 5, fp);
	fflush(fp);//刷新，立即写入
	return 1;
}


int CGongju::tianjiaXiangmu(CString wen, CString da, char fenlei)//返回标识
{
	if (yc < 0 || wen.GetLength() > 900 || da.GetLength() > 900 || fenlei > 63 || fenlei < 0)
	{
		return 0;
	}
	if (wen.GetLength() < 1 || da.GetLength() < 1 || 32703 < zjyxm || !flqk[fenlei].cunzai) return 0;
	dxxxm++;
	zjyxm++;
	int j;
	short i = 0;//标识-1
	for (i = 0; i < 32704; i++)
	{
		if (xmsj[i].jieduan == -128) break;
	}
	if (i == 32704)
	{
		return -1;//项目已添加满
	}
	wchar_t *wenti = new wchar_t[wen.GetLength()+61];//加61防止写入时内存读取出错
	for (int k=0; k < wen.GetLength() + 1;k++) wenti[k] = 0;
	lstrcpy(wenti, wen);//将CString转换为wchar_t
	wchar_t *daan = new wchar_t[da.GetLength() + 61];//加61防止写入时内存读取出错
	for (int k=0; k < da.GetLength() + 1; k++) daan[k] = 0;
	lstrcpy(daan, da);//将CString转换为wchar_t
	//项目数据内存修改
	xmsj[i].jieduan = 0;
	xmsj[i].scsdsj = xtsj;
	xmsj[i].zhxgsj = xtsj;
	xmsj[i].fenlei = fenlei;
	xmsj[i].qian[0] = wdwdz;
	xmsj[i].qian[1] = (wen.GetLength() - 1) / 60 + 1;//自动下取整变得只有一种情况
	xmsj[i].hou[0] = wdwdz + xmsj[i].qian[1] * 128;
	xmsj[i].hou[1] = (da.GetLength() - 1) / 60 + 1;
	xmsj[i].wenti = wen;
	xmsj[i].daan = da;
	xmsj[i].riqi = riqizhuanhua(xtsj);
	//项目数据外存修改
		//添加
	fseek(fp, 96 + i * 16, 0);
	short ii = 1;
	fwrite(&ii, 2, 1, fp);
	fwrite(&xmsj[i].jieduan, 1, 1, fp);
	fwrite(&xmsj[i].scsdsj, 2, 1, fp);
	fwrite(&xmsj[i].zhxgsj, 2, 1, fp);
	fwrite(&xmsj[i].fenlei, 1, 1, fp);
	fwrite(&xmsj[i].qian[0], 4, 1, fp);
	fwrite(&xmsj[i].hou[0], 4, 1, fp);
	fseek(fp, wdwdz, 0);//从尾部开始添加数据
	for (int k = 0; k < xmsj[i].qian[1]; k++)//尾部添加问题
	{
		if (0 == k) j = i + 1;//问题是正数
		else j = xmsj[i].qian[0] + (k - 1) * 128;
		fwrite(&j, 4, 1, fp);
		//fseek(fp, 120, 1);
		fwrite(wenti + k * 60, 2, 60, fp);//写入问题
		if (k + 1 == xmsj[i].qian[1]) j = 0;
		else j = xmsj[i].qian[0] + (k + 1) * 128;
		fwrite(&j, 4, 1, fp);
	}
	for (int k = 0; k < xmsj[i].hou[1]; k++)//尾部添加答案
	{
		if (0 == k) j = -(i + 1);//答案是负数
		else j = xmsj[i].hou[0] + (k - 1) * 128;
		fwrite(&j, 4, 1, fp);
		//fseek(fp, 120, 1);
		fwrite(daan + k * 60, 2, 60, fp);//写入答案
		if (k + 1 == xmsj[i].hou[1]) j = 0;
		else j = xmsj[i].hou[0] + (k + 1) * 128;
		fwrite(&j, 4, 1, fp);
	}
	wdwdz += (xmsj[i].qian[1] + xmsj[i].hou[1]) * 128;//写入尾单位地址
	fseek(fp, 525426, 0);
	fwrite(&wdwdz, 4, 1, fp);
	fflush(fp);
	//其他内存修改
	tianjiaJylb(i + 1);//链表
	tianjiaPxlb(i + 1);
	dwfl[1][fenlei]++;
	dwfl[1][64]++;
	//最后释放空间
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
			if (day <= 30) day++;//如果没到月底
			else   //如果到月底
			{
				if (month != 12)//如果到月底没到年底
				{
					day = 1;
					month++;
				}
				else  //如果到月底到年底
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
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) day++;//闰年
				else//不是闰年
				{
					day = 1;
					month++;
				}
			}
			else //2月29号时
			{
				day = 1;
				month++;
			}
		}
	}
	CTime t(year, month, day, 0, 0, 0);//六项齐全才有效
	return t;
}


int CGongju::Qiandao()
{
	if (yc < 0 || lsj == xtsj)//错误或已签到
	{
		return 0;
	}
	if (0 >= fsj || xtsj - lsj>1)//从未签到或断签了
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


// 删除该标识对应的第一个块
int CGongju::shanchuKuai(short biaoshi,int wenti)
{
	if (yc < 0 || biaoshi < 1 || xmsj[biaoshi - 1].jieduan == -128)
	{
		return 0;
	}
	if ((wenti&& xmsj[biaoshi - 1].qian[1] < 1) || (!wenti&& xmsj[biaoshi - 1].hou[1] < 1))//没有块
	{
		return 0;
	}
	int a,b,d;//开始删除
	char c[128];
	if (wenti)
	{
		b = xmsj[biaoshi - 1].qian[0];//要删除块的标识
		if (xmsj[biaoshi - 1].qian[1] > 1)
		{
			fseek(fp, b + 124, 0);
			fread(&a, 4, 1, fp);//读取删除块后块的位置
			fseek(fp, a, 0);//移动到该块
			d = biaoshi;
			fwrite(&d, 4, 1, fp);
			fflush(fp);//防止删除的块是最后一个块逻辑前块
			xmsj[biaoshi - 1].qian[0] = a;//赋值
			fseek(fp, 96 + (biaoshi - 1) * 16 + 8, 0);//移动到该项目前驱
			fwrite(&a, 4, 1, fp);
		}
		else
		{
			a = 0;
			xmsj[biaoshi - 1].qian[0] = a;//赋值
			fseek(fp, 96 + (biaoshi - 1) * 16 + 8, 0);//移动到该项目前驱
			fwrite(&a, 4, 1, fp);
		}
		xmsj[biaoshi - 1].qian[1]--;
		if (b != wdwdz - 128)//删除的不是最后一个块
		{
			fflush(fp);//写后读前要刷新
			fseek(fp, wdwdz - 128, 0);//移动到填补块
			fread(c, 1, 128, fp);
			fseek(fp, b, 0);//移动到删除块
			fwrite(c, 1, 128, fp);//覆盖
			fflush(fp);//写后读前要刷新
			fseek(fp, wdwdz - 128, 0);//移动到填补块
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a + 124 , 0);//移动到填补块的前驱的后驱
				fwrite(&b, 4, 1, fp);
			}
			else
			{
				if (0 < a)
				{
					xmsj[a - 1].qian[0] = b;
					fseek(fp, 96 + (a - 1) * 16 + 8, 0);//移动到该项目前驱
					fwrite(&b, 4, 1, fp);
				}
				else if (0 > a)
				{
					xmsj[-a - 1].hou[0] = b;
					fseek(fp, 96 + (-a - 1) * 16 + 12, 0);//移动到该项目前驱
					fwrite(&b, 4, 1, fp);
				}
				else yc = 3;//未知块
			}
			fflush(fp);//写后读前要刷新
			fseek(fp, wdwdz - 4, 0);//移动到填补块后驱
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a, 0);//移动到填补块的后驱的前驱
				fwrite(&b, 4, 1, fp);
			}
		}
	}
	else
	{
		b = xmsj[biaoshi - 1].hou[0];//要删除块的标识
		if (xmsj[biaoshi - 1].hou[1] > 1)
		{
			fflush(fp);//写后读前要刷新
			fseek(fp, b + 124, 0);
			fread(&a, 4, 1, fp);//读取删除块后块的位置
			fseek(fp, a, 0);//移动到该块
			d = biaoshi;
			fwrite(&d, 4, 1, fp);
			fflush(fp);//防止删除的块是最后一个块逻辑前块
			xmsj[biaoshi - 1].hou[0] = a;//赋值
			fseek(fp, 96 + (biaoshi - 1) * 16 + 12, 0);//移动到该项目前驱
			fwrite(&a, 4, 1, fp);
		}
		else
		{
			a = 0;
			xmsj[biaoshi - 1].hou[0] = a;//赋值
			fseek(fp, 96 + (biaoshi - 1) * 16 + 12, 0);//移动到该项目前驱
			fwrite(&a, 4, 1, fp);
		}
		xmsj[biaoshi - 1].hou[1]--;
		if (b != wdwdz - 128)//删除的不是最后一个块
		{
			fflush(fp);//写后读前要刷新
			fseek(fp, wdwdz - 128, 0);//移动到填补块
			fread(c, 1, 128, fp);
			fseek(fp, b, 0);//移动到删除块
			fwrite(c, 1, 128, fp);//覆盖
			fflush(fp);//写后读前要刷新
			fseek(fp, wdwdz - 128, 0);//移动到填补块
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a + 124, 0);//移动到填补块的前驱的后驱
				fwrite(&b, 4, 1, fp);
			}
			else
			{
				if (0 < a)
				{
					xmsj[a - 1].qian[0] = b;
					fseek(fp, 96 + (a - 1) * 16 + 8, 0);//移动到该项目前驱
					fwrite(&b, 4, 1, fp);
				}
				else if (0 > a)
				{
					xmsj[-a - 1].hou[0] = b;
					fseek(fp, 96 + (-a - 1) * 16 + 12, 0);//移动到该项目前驱
					fwrite(&b, 4, 1, fp);
				}
				else yc = 3;//未知块
			}
			fflush(fp);//写后读前要刷新
			fseek(fp, wdwdz - 4, 0);//移动到填补块后驱
			fread(&a, 4, 1, fp);
			if (a >= 525430)
			{
				fseek(fp, a, 0);//移动到填补块的后驱的前驱
				fwrite(&b, 4, 1, fp);
			}
		}
	}
	wdwdz -= 128;
	fseek(fp, 525426, 0);
	fwrite(&wdwdz, 4, 1, fp);//写入尾单位地址
	fflush(fp);
	return 1;
}


// 为该标识添加一个块
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
		fflush(fp);//写后读前要刷新
		for (int i = xmsj[biaoshi - 1].qian[1]; i>1; i--)//移到最后块的后驱的位置
		{
			fread(&b, 4, 1, fp);
			a = b + 124;
			fseek(fp, a, 0);
		}
		fseek(fp, a, 0);
		if (xmsj[biaoshi - 1].qian[1] > 0)
		{
			fwrite(&wdwdz, 4, 1, fp);
			a -= 124;//最后块的位置
		}
		else
		{
			xmsj[biaoshi - 1].qian[0] = wdwdz;//赋值
			fseek(fp, 96 + (biaoshi - 1) * 16 + 8, 0);//移动到该项目前驱
			fwrite(&wdwdz, 4, 1, fp);
			a = biaoshi;
		}
		fseek(fp, wdwdz, 0);//从尾部开始添加数据
		fwrite(&a, 4, 1, fp);
		fwrite(c, 1, 120, fp);
		b = 0;
		fwrite(&b, 4, 1, fp);
		xmsj[biaoshi - 1].qian[1]++;
	}
	else
	{
		a = xmsj[biaoshi - 1].hou[0] + 124;
		fflush(fp);//写后读前要刷新
		for (int i = xmsj[biaoshi - 1].hou[1]; i>1; i--)//移到最后块的后驱的位置
		{
			fread(&b, 4, 1, fp);
			a = b + 124;
			fseek(fp, a, 0);
		}
		fseek(fp, a, 0);
		if (xmsj[biaoshi - 1].hou[1] > 0)
		{
			fwrite(&wdwdz, 4, 1, fp);
			a -= 124;//最后块的位置
		}
		else
		{
			xmsj[biaoshi - 1].hou[0] = wdwdz;//赋值
			fseek(fp, 96 + (biaoshi - 1) * 16 + 12, 0);//移动到该项目前驱
			fwrite(&wdwdz, 4, 1, fp);
			a = -biaoshi;
		}
		fseek(fp, wdwdz, 0);//从尾部开始添加数据
		fwrite(&a, 4, 1, fp);
		fwrite(c, 1, 120, fp);
		a = 0;
		fwrite(&a, 4, 1, fp);
		xmsj[biaoshi - 1].hou[1]++;
	}
	wdwdz += 128;
	fseek(fp, 525426, 0);
	fwrite(&wdwdz, 4, 1, fp);//写入尾单位地址
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
	if (chongxue)//重新学习的修改就是删除再添加
	{
		shanchuXiangmu(biaoshi);
		tianjiaXiangmu(wen, da, fenlei);
		return 1;
	}
	wchar_t *wenti = new wchar_t[wen.GetLength() + 1];
	for (int k = 0; k < wen.GetLength() + 1; k++) wenti[k] = 0;
	lstrcpy(wenti, wen);//将CString转换为wchar_t
	wchar_t *daan = new wchar_t[da.GetLength() + 1];
	for (int k = 0; k < da.GetLength() + 1; k++) daan[k] = 0;
	lstrcpy(daan, da);//将CString转换为wchar_t
	int qian1, hou1;
	qian1 = (wen.GetLength() - 1) / 60 + 1;//自动下取整变得只有一种情况
	hou1 = (da.GetLength() - 1) / 60 + 1;//自动下取整变得只有一种情况
	while (1)//删减问题单元个数
	{
		if (qian1>xmsj[biaoshi - 1].qian[1]) tianjiaKuai(biaoshi, 1);
		else if (qian1<xmsj[biaoshi - 1].qian[1]) shanchuKuai(biaoshi, 1);
		else break;
	}
	while (1)//删减答案单元个数
	{
		if (hou1>xmsj[biaoshi - 1].hou[1]) tianjiaKuai(biaoshi, 0);
		else if (hou1<xmsj[biaoshi - 1].hou[1]) shanchuKuai(biaoshi, 0);
		else break;
	}
	//段位分类内存修改
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
	//项目数据内存修改
	xmsj[biaoshi - 1].zhxgsj = xtsj;
	xmsj[biaoshi - 1].fenlei = fenlei;
	xmsj[biaoshi - 1].wenti = wen;
	xmsj[biaoshi - 1].daan = da;
	xmsj[biaoshi - 1].riqi = riqizhuanhua(xtsj);
	//项目数据外存修改
	fseek(fp, 96 + (biaoshi - 1) * 16 + 5 , 0);
	fwrite(&xmsj[biaoshi - 1].zhxgsj, 2, 1, fp);
	fwrite(&xmsj[biaoshi - 1].fenlei, 1, 1, fp);
	int i;
	fseek(fp, xmsj[biaoshi - 1].qian[0], 0);//从头开始添加数据
	for (int k = 0; k < xmsj[biaoshi - 1].qian[1]; k++)//覆盖原问题
	{
		fseek(fp, 4, 1);//头部跳过
		fwrite(wenti + k * 60, 2, 60, fp);//写入问题
		fflush(fp);//写后读前要刷新
		fread(&i, 4, 1, fp);//读取下一个单位地址
		fseek(fp, i, 0);
	}
	fseek(fp, xmsj[biaoshi - 1].hou[0], 0);//从头开始添加数据
	for (int k = 0; k < xmsj[biaoshi - 1].hou[1]; k++)//覆盖原答案
	{
		fseek(fp, 4, 1);//头部跳过
		fwrite(daan + k * 60, 2, 60, fp);//写入答案
		fflush(fp);//写后读前要刷新
		fread(&i, 4, 1, fp);//读取下一个单位地址
		fseek(fp, i, 0);
	}
	fflush(fp);
	//链表内存修改
	shanchuPxlb(biaoshi);//排序链表
	tianjiaPxlb(biaoshi);
	//最后释放空间
	delete(wenti);
	delete(daan);
	return 1;
}

//不减少今天已学项目数
int CGongju::shanchuXiangmu(short biaoshi)
{
	if (yc < 0 || biaoshi < 1 || xmsj[biaoshi - 1].jieduan == -128)
	{
		return 0;
	}
	//内存修改
	zjyxm--;
	shanchuPxlb(biaoshi);
	if (-1 == xmsj[biaoshi - 1].jieduan)
	{
		if (dlyxs>0) dlyxs--;
		for (int i = 0; i < 15; i++)//记忆队列去一个
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
		//记忆队列填补若有则去
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
	else yc = 4;//段位在-127到-1之间
	 //段位分类内存修改
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
	while (shanchuKuai(biaoshi, 1));//删除问题数据
	while (shanchuKuai(biaoshi, 0));//删除答案数据
	//项目数据内存修改
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
	//外存修改
	fseek(fp, 20, 0);
	fwrite(&dlyxs, 1, 1, fp);
	for (int i = 0; i < 15; i++)   //记忆队列写入
	{
		fwrite(&jydl[i].biaoshi, 2, 1, fp);
		fwrite(&jydl[i].shangshengyan, 1, 1, fp);
		fwrite(&jydl[i].lianxucishu, 1, 1, fp);
		fwrite(&jydl[i].xiajiangyan, 1, 1, fp);
	}
	fseek(fp, 96 + (biaoshi - 1) * 16, 0);//移动到该项目
	int ii = 0;
	fwrite(&ii, 4, 1, fp);//项目数据写入
	fwrite(&ii, 4, 1, fp);
	fwrite(&ii, 4, 1, fp);
	fwrite(&ii, 4, 1, fp);
	fseek(fp, 525424, 0);
	fwrite(&dfxxm, 2, 1, fp);//待复习项目写入
	return 1;
}


// 删除排序链表中的一个结点
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
	while (zz->next != NULL)//找到该位置
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


// 删除记忆链表中的一个结点
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
	while (zz->next != NULL)//找到该位置
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


// 删除复习链表中的一个结点
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
	while (zz->next != NULL)//找到该位置
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


// 参数为保存位置
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
	fwrite(&bom, 2, 1, fbc);//写入Unicode标识
	if (fenlei<0 || fenlei>63)//全部处理
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
	else//分分类处理
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


// 若异常等于0则可以备份新
int CGongju::BEI_FEN()
{
	if (yc < 0)
	{
		return 0;
	}
	CString s(L"C:\\Users\\Public\\记忆辅助的备份文件.ysj");
	if (yc>0)
	{
		s = L"C:\\Users\\Public\\记忆辅助异常前的备份文件.ysj";
		FILE *f,*ff;
		if (0 != _wfopen_s(&ff, L"C:\\Users\\Public\\记忆辅助的备份文件.ysj", L"rb+"))
		{
			return 0;
		}
		if (0 != _wfopen_s(&f, s, L"wb+"))
		{
			return 0;
		}
		fseek(ff, 0, SEEK_END);//文件指针移动到末尾
		int n = ftell(ff);//文件大小获取
		char *bf = new char[n];
		fseek(ff, 0, 0);
		fread(bf, 1, n, ff);
		fseek(f, 0, 0);//开始写入
		fwrite(bf, 1, n, f);
		fclose(f);
		delete(bf);
		return 1;
	}
	else
	{
		fseek(fp, 0, SEEK_END);//文件指针移动到末尾
		int n = ftell(fp);//文件大小获取
		char *bf = new char[n];
		fseek(fp, 0, 0);
		fread(bf, 1, n, fp);
		FILE *f;
		if (0 != _wfopen_s(&f, s, L"wb+"))
		{
			return 0;
		}
		fseek(f, 0, 0);//开始写入
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
	if (mingzi.Find(L" ") != -1)//不能有空格
	{
		return 0;
	}
	if (mingzi=="未分类")//不能是默认
	{
		return 0;
	}
	lstrcpy(flqk[fenlei].name, mingzi);
	fseek(fp, 523368 + fenlei * 32 , 0);
	fwrite(flqk[fenlei].name, 2, 16, fp);//写入分类名称
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
	fwrite(a, 1, 8, fp);//写入分类标记
	fflush(fp);//刷新，立即写入
	return 1;
}


int CGongju::tianjiaFenlei(CString name)
{
	if (yc < 0 || name.GetLength()>16 || name.GetLength() == 0)
	{
		return 0;
	}
	if (name.Find(L" ") != -1)//不能有空格
	{
		return 0;
	}
	if (name == "未分类")//不能是默认
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


// 删除一个分类
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
	fwrite(b, 1, 32, fp);//写入空
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
	fwrite(a, 1, 8, fp);//写入分类标记
	fflush(fp);//刷新，立即写入
	return 1;
}


// 将记忆队列中的空白处填补起来
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
			suiji = rand() % jylb->biaoshi;//随机数
			jylbyd = jylb;
			for (int j = 0; j < suiji; j++)
			{
				jylbyd = jylbyd->next;
			}
			biaoshi = jylbyd->next->biaoshi;
			shanchuJylb(biaoshi);//删除该结点
			jydl[i].biaoshi = biaoshi;
			jydl[i].lianxucishu = 0;
			jydl[i].shangshengyan = 0;
			jydl[i].xiajiangyan = 0;
			xmsj[biaoshi - 1].jieduan = -1;
			fseek(fp, 96 + (biaoshi - 1) * 16, 0);
			short iii = 1;
			fwrite(&iii, 2, 1, fp);
			fwrite(&xmsj[biaoshi - 1].jieduan, 1, 1, fp);//写入阶段
		}
		int cf;//重复
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
	if (t) //学完一组重计队列有效数
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
	写入记忆队列();
	return 1;
}


int CGongju::写入记忆队列()
{
	fseek(fp, 20, 0);
	fwrite(&dlyxs, 1, 1, fp);
	for (int i = 0; i < 15; i++)   //记忆队列写入
	{
		fwrite(&jydl[i].biaoshi, 2, 1, fp);
		fwrite(&jydl[i].shangshengyan, 1, 1, fp);
		fwrite(&jydl[i].lianxucishu, 1, 1, fp);
		fwrite(&jydl[i].xiajiangyan, 1, 1, fp);
	}
	fflush(fp);
	return 1;
}


int CGongju::学习一个(int 成功)
{
	if (yc < 0 || zjyxm < 15 || dlyxs < 1)
	{
		return 0;
	}
	int biaoshi, ii=0;
	char lianxucishu, shangshengyan, xiajiangyan;
	lianxucishu = jydl[0].lianxucishu;//想保留数据
	shangshengyan = jydl[0].shangshengyan;
	xiajiangyan = jydl[0].xiajiangyan;
	if (!成功&&jydl[0].biaoshi < 0)
	{
		biaoshi = jydl[0].biaoshi;
		for (int i = 0; i < 14; i++)//全部前移
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
		写入记忆队列();
		return 1;
	}
	if (成功&&jydl[0].biaoshi < 0)
	{
		for (int i = 0; i < 14; i++)//全部前移
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
	if (成功&&jydl[0].lianxucishu>=3)
	{
		dxxxm--;
		fxjz[3]++;
		fseek(fp, 525416 + 6, 0);//今日已背项目的位置
		fwrite(&fxjz[3], 2, 1, fp);
		biaoshi = jydl[0].biaoshi;
		if (1 == jydl[0].shangshengyan)
		{
			xmsj[biaoshi - 1].jieduan = 2;//段位置2
			dwfl[1][xmsj[biaoshi - 1].fenlei]--;
			dwfl[1][64]--;
			dwfl[0][xmsj[biaoshi - 1].fenlei]++;
			dwfl[0][64]++;
		}
		else xmsj[biaoshi - 1].jieduan = 1;//段位置1
		xmsj[biaoshi - 1].scsdsj = xtsj;//首次升段时间
		fseek(fp, 96 + (biaoshi - 1) * 16, 0);//项目的位置
		short iii = 1;
		fwrite(&iii, 2, 1, fp);
		fwrite(&xmsj[biaoshi - 1].jieduan, 1, 1, fp);
		fwrite(&xtsj, 2, 1, fp);
		fflush(fp);//刷新写入
		if (rand() % 2 + rand() % 2)//一定概率不前移
		{
			for (int i = 0; i < 14; i++)//全部前移
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
		写入记忆队列();
		return 1;
	}
	if (成功)//但还未完全记住
	{
		biaoshi = jydl[0].biaoshi;
		lianxucishu++;
		if (1 == lianxucishu && 127 != shangshengyan)
		{
			shangshengyan++;
			if (xiajiangyan > 0) xiajiangyan--;
		}
		else xiajiangyan = 0;
		for (ii = 0; ii < jiange[lianxucishu-1]; ii++)//移适当位数
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
		写入记忆队列();
		return 1;
	}
	//未记住的时候
	biaoshi = jydl[0].biaoshi;
	if (lianxucishu > 1) xiajiangyan = 0;
	else if (lianxucishu == 0 && xiajiangyan < jiange[0] - 1) xiajiangyan++;//下降沿越大，移位越少
	lianxucishu = 0;
	for (ii = 0; ii < jiange[0] - xiajiangyan; ii++)//移位，适当缩短位数
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
	写入记忆队列();
	return 1;
}


int CGongju::复习一个(int 成功)
{
	if (yc < 0 || zjyxm < 15 || dfxxm < 1)
	{
		return 0;
	}
	struct fxlb *zz = fxlbt, *zzz = fxlbt;
	int shibaicharu = 12;//复习失败插入位置,相隔shibaicharu-1个
	if (!成功)//复习失败
	{
		if (126>fxlbt->next->pingyancishu) fxlbt->next->pingyancishu++;
		fseek(fp, 96 + (fxlbt->next->biaoshi - 1) * 16, 0);
		char iii = fxlbt->next->pingyancishu + 1;
		fwrite(&iii, 1, 1, fp);//写入平沿次数加一
		fflush(fp);
		for (int i = 0; i < shibaicharu; i++)//找到位置
		{
			if (zz->next != NULL) zz = zz->next;
			else break;
		}
		if (zz->next == NULL)//插入
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
	//复习成功
	dfxxm--;
	int biaoshi = fxlbt->next->biaoshi, duan = 1;
	int i = xtsj - xmsj[biaoshi - 1].scsdsj;
	if (i / ddyts[5] >= 1) duan = 6;//计算相对段位
	else if (i / ddyts[4] >= 1) duan = 5;
	else if (i / ddyts[3] >= 1) duan = 4;
	else if (i / ddyts[2] >= 1) duan = 3;
	else if (i / ddyts[1] >= 1) duan = 2;
	else duan = 1;
	duan = duan - fxlbt->next->pingyancishu + 1;
	if (duan < 1) duan = 1;//得到最终段位
	//段位分类修改
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
	if (duan > 6) yzwxm++;//已掌握项目
	xmsj[biaoshi - 1].jieduan = duan;
	if (duan == 1) xmsj[biaoshi - 1].scsdsj = xtsj;
	else xmsj[biaoshi - 1].scsdsj = xtsj - ddyts[duan - 2];
	shanchuFxlb(biaoshi);
	fseek(fp, 96 + (biaoshi - 1) * 16, 0);//项目的位置
	short iii = 1;
	fwrite(&iii, 2, 1, fp);
	fwrite(&xmsj[biaoshi - 1].jieduan, 1, 1, fp);
	fwrite(&xmsj[biaoshi - 1].scsdsj, 2, 1, fp);
	fseek(fp, 525416 + 8, 0);
	fwrite(&dfxxm, 2, 1, fp);//待复习项目
	fflush(fp);
	if (dfxxm <= 0 || 1 >= fxlbt->biaoshi || xmsj[fxlbt->next->biaoshi - 1].jieduan <= 1) return 2;
	if (获取平沿加一(fxlbt->next->biaoshi) > 1) return 3;//背过的再来，不需要调换
	int suiji = rand() % fxlbt->biaoshi;//段位大于1的存在是随机的，防止后面的总复习不到
	if (suiji == 0) return 4;//第一个结点本来就是第一，不用换
	for (int i = 0; i <= suiji; i++)//找到位置
	{
		if (zz->next != NULL)
		{
			zzz = zz;
			zz = zz->next;
		}
		else break;
	}
	if (suiji <= shibaicharu && 0 < zz->pingyancishu) return 5;//没背出而故意延后的不调
	if (zz->next == NULL)//提到最前面
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
	if (zz->next == zzz) return 6; //相邻不需要调换
	//把zz->next调到zzz后面，实现交换
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


int CGongju::反向初始化(char fenlei)
{
	if (yc < 0 || zjyxm < 15 || dwfl[0][64] < 1)
	{
		return 0;
	}
	if (fenlei<0 || fenlei>63)//全部
	{
		for (int i = 0; i < 32704; i++)
		{
			if (1 < xmsj[i].jieduan && 7 > xmsj[i].jieduan)
			{
				反向数组[反向数组[32704]++] = i + 1;
			}
		}
	}
	else //某个分类进行反向
	{
		for (int i = 0; i < 32704; i++)
		{
			if (1 < xmsj[i].jieduan && 7 > xmsj[i].jieduan && xmsj[i].fenlei == fenlei)
			{
				反向数组[反向数组[32704]++] = i + 1;
			}
		}
	}
	获取反向();
	return 1;
}


int CGongju::反向一个(int 成功)
{
	if (yc < 0 || zjyxm < 15 || 反向数组[32704] < 1)
	{
		return 0;
	}
	short ls;
	int i = rand() % 反向数组[32704];
	if (成功)
	{
		反向数组[32704]--;
		反向数组[0] = 反向数组[反向数组[32704]];
	}
	else
	{
		ls = 反向数组[0];
		反向数组[0] = 反向数组[i];
		反向数组[i] = ls;
	}
	return 1;
}


short CGongju::获取反向()//用于打乱顺序
{
	if (yc < 0 || zjyxm < 15 || 反向数组[32704] < 1)
	{
		return 0;
	}
	short luanxu[32704];
	int i, j;
	for (i = 反向数组[32704]; i>0; i--)
	{
		j = rand() % i;
		luanxu[i - 1] = 反向数组[j];
		while (j < i - 1)
		{
			反向数组[j] = 反向数组[j + 1];
			j++;
		}
	}
	for (i = 0; i < 反向数组[32704]; i++)
	{
		反向数组[i] = luanxu[i];
	}
	return 反向数组[0];
}


char CGongju::获取平沿加一(short biaoshi)
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
	while (zz->next != NULL)//找到该位置
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


char CGongju::分类存在(CString fenlei)//返回分类编号
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


// 把项目从fenlei1移动到fenlei2，返回移动个数
int CGongju::移动分类(char fenlei1, char fenlei2)
{
	if (yc < 0 || fenlei1 < 0 || fenlei2 < 0 || fenlei1 > 63 || fenlei2 > 63 || fenlei1 == fenlei2)
	{
		return 0;
	}
	if (flqk[fenlei1].cunzai == 0 || flqk[fenlei2].cunzai == 0) return 0;
	int ci = 0;//移动次数
	for (int i = 0; i < 32704; i++)
	{
		if (-128 != xmsj[i].jieduan&&xmsj[i].fenlei == fenlei1)
		{
			if (xmsj[i].jieduan > 1 && xmsj[i].jieduan < 7)//段位分类修改
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


void CGongju::重新整理()
{
	fseek(fp, 0, SEEK_END);//文件指针移动到末尾
	int n = ftell(fp);//文件大小获取
	if (wdwdz*1.3 < n)//文件过大时重新整理
	{
		char *cc = new char[wdwdz];
		fseek(fp, 0, 0);//移到开头
		fread(cc, 1, wdwdz, fp);
		fclose(fp);
		if (0 != _wfopen_s(&fp, lujing, L"wb+"))
		{
			yc = -4;//意外错误！
			return;
		}
		fwrite(cc, 1, wdwdz, fp);
		fflush(fp);
		delete(cc);
	}
}
