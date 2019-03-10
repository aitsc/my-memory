// Cbianji.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "Cbianji.h"
#include "afxdialogex.h"
#include "Czengaixiangmu.h"
#include "C筛选.h"
#include "C卡片式.h"
#include "C项目内容.h"

#define 一页条数 250 //最少33条

// Cbianji 对话框

IMPLEMENT_DYNAMIC(Cbianji, CDialogEx)

Cbianji::Cbianji(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cbianji::IDD, pParent)
	, shijianq(0)
	, shijianh(0)
	, fenlei(64)
	, zhuangtai(3)
	, sousuo(_T(""))
	, 默认增加分类(0)
	, 当前页码(1)
	, 总页码(1)
	, 换页(0)
{

}

Cbianji::~Cbianji()
{
}

void Cbianji::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, sousuo);
	DDV_MaxChars(pDX, sousuo, 900);
	DDX_Text(pDX, IDC_EDIT2, 当前页码);
	DDV_MinMaxInt(pDX, 当前页码, 0, 999);
}


BEGIN_MESSAGE_MAP(Cbianji, CDialogEx)
	ON_BN_CLICKED(IDCANCEL1, &Cbianji::OnBnClicked_Zenjia)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &Cbianji::OnBnClicked_Shanchu)
	ON_BN_CLICKED(IDOK, &Cbianji::OnBnClicked_Shaixuan)
	ON_BN_CLICKED(IDC_BUTTON5, &Cbianji::OnBnClicked_Sousuo)
	ON_BN_CLICKED(IDC_BUTTON1, &Cbianji::OnBnClicked_Xiugai)
	ON_BN_CLICKED(IDC_BUTTON3, &Cbianji::OnBnClicked_Daoru)
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST1, &Cbianji::OnNMRDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON4, &Cbianji::OnBnClicked_Chongxue)
	ON_BN_CLICKED(IDC_BUTTON6, &Cbianji::OnBnClicked_上一页)
	ON_BN_CLICKED(IDC_BUTTON7, &Cbianji::OnBnClicked_下一页)
	ON_WM_TIMER()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Cbianji 消息处理程序


BOOL Cbianji::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化ShowWindow(SW_HIDE);
	shijianh = gongju.xtsj;
	for (int i = 0; i < 32704; i++) listbiaoshi[i] = 0;//初始化列表标识
	SetMenu((menu.LoadMenu(IDR_LIST), &menu));//显示菜单栏
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//选择整行+网格线
	m_list.InsertColumn(0, L"序号", LVCFMT_LEFT, 37);
	m_list.InsertColumn(1, L"问题", LVCFMT_LEFT, 210);
	m_list.InsertColumn(2, L"答案", LVCFMT_LEFT, 96);
	m_list.InsertColumn(3, L"修改时间", LVCFMT_LEFT, 96);
	m_list.InsertColumn(4, L"状态", LVCFMT_LEFT, 48);
	m_list.InsertColumn(5, L"分类名", LVCFMT_LEFT, 210);
	showlist();
	SetTimer(1, 50, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


// 刷新列表
int Cbianji::showlist()
{
	m_list.DeleteAllItems();//清空列表防止重复
	int i = 0, j, ii = 0;
	gongju.pxlbyd = gongju.pxlb;
	UpdateData(TRUE);
	if (!换页)
	{
		当前页码 = 1;
	}
	if (总页码 < 1 || 当前页码 < 1 || 总页码 < 当前页码)
	{
		总页码 = 1;
		当前页码 = 1;
	}
	sousuo.TrimLeft();//去除左边回车和空格
	sousuo.TrimRight();//去除右边回车和空格
	sousuo.MakeLower();//转为小写
	UpdateData(false);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);//重绘窗口
	CString sw, sd, s;
	int ss, sj, fl, zt;
	while (NULL != gongju.pxlbyd->next)
	{
		sw = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].wenti;
		sd = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].daan;
		sw.MakeLower();//不区分大小写搜索
		sd.MakeLower();
		ss = sw.Find(sousuo) != -1 || sd.Find(sousuo) != -1;//判断是否搜索
			        //判断时间是否在范围内
		sj = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].zhxgsj >= shijianq && gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].zhxgsj <= shijianh;
		if (fenlei >= 64) fl = 1; //判断分类是否一致
		else fl = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].fenlei == fenlei;
		j = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].jieduan;//状态
		if (zhuangtai >= 3) zt = 1;//判断状态是否一致
		else
		{
			if (j <= 0 && zhuangtai == 0) zt = 1;
			else if (j > 6 && zhuangtai == 1) zt = 1;
			else if (j > 0 && j < 7 && zhuangtai == 2) zt = 1;
			else zt = 0;
		}
		if (ss&&sj&&fl&&zt)
		{
			if (当前页码*一页条数>ii && (当前页码-1)*一页条数<=ii)
			{
				s.Format(L"%d", i + 1);
				m_list.InsertItem(i, s);
				m_list.SetItemText(i, 1, sw);//问题
				m_list.SetItemText(i, 2, sd);//答案
				m_list.SetItemText(i, 3, gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].riqi);//修改时间
				j = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].jieduan;//状态
				if (j <= 0) m_list.SetItemText(i, 4, L"待学习");//0
				else if (j>6) m_list.SetItemText(i, 4, L"已掌握");//1
				else m_list.SetItemText(i, 4, L"备复习");//2
				m_list.SetItemText(i, 5, gongju.flqk[gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].fenlei].name);
				listbiaoshi[i] = gongju.pxlbyd->next->biaoshi;
				i++;
			}
			ii++;
		}
		gongju.pxlbyd = gongju.pxlbyd->next;
	}
	if (ii > 0 && ii%一页条数 == 0)
	{
		总页码 = ii / 一页条数;
	}
	else
	{
		总页码 = ii / 一页条数 + 1;
	}
	s.Format(L"/%d", 总页码);
	GetDlgItem(IDC_STATIC2)->SetWindowText(L"      ");
	GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	s.Format(L"（当前结果中共%d条数据）", ii);
	GetMenu()->DeleteMenu(0, MF_BYPOSITION);
	GetMenu()->AppendMenu(MF_ENABLED, ID_qwe, s);
	DrawMenuBar();
	换页 = 0;
	return ii;
}


void Cbianji::OnBnClicked_Zenjia()
{
	// TODO:  在此添加控件通知处理程序代码
	if (gongju.zjyxm>=32704)
	{
		MessageBox(L"项目已满，不能添加！");
		return;
	}
	Czengaixiangmu zengai;
	zengai.zengjia = 1;
	zengai.默认增加分类 = 默认增加分类;
	if (11 == zengai.DoModal())
	{
		默认增加分类 = zengai.默认增加分类;
		showlist();
	}
	m_list.SetSelectionMark(-1);//重置位置
}


void Cbianji::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	EndDialog(11);
	//CDialogEx::OnClose();
}


void Cbianji::OnBnClicked_Shanchu()
{
	// TODO:  在此添加控件通知处理程序代码
	if (15 == gongju.zjyxm)
	{
		MessageBox(L"项目不能在15个以下！");
		return;
	}
	int i = m_list.GetSelectionMark();//获取位置
	if (-1 == i)
	{
		MessageBox(L"请选择记录！");
		return;
	}
	int a = 0, b[32704];
	POSITION  pos = m_list.GetFirstSelectedItemPosition();//首标识处
	for (POSITION posTemp = pos; posTemp != NULL; a++)
	{
		b[a] = m_list.GetNextSelectedItem(posTemp);//储存标识
	}
	if (gongju.zjyxm - a<15 && gongju.zjyxm>15)
	{
		MessageBox(L"项目不能在15个以下！");
		return;
	}
	CString s;
	s.Format(L"您确定要删除这%d条记录？", a);
	if (MessageBox(s, TEXT("删除"), MB_YESNO) == IDNO)
	{
		m_list.SetSelectionMark(-1);//重置位置
		return;
	}
	for (int i = 0; i < a; i++)
	{
		gongju.shanchuXiangmu(listbiaoshi[b[i]]);
	}
	showlist();
}


void Cbianji::OnBnClicked_Shaixuan()
{
	// TODO:  在此添加控件通知处理程序代码
	C筛选 shaixuan;
	shaixuan.shijianq = shijianq;
	shaixuan.shijianh = shijianh;
	shaixuan.fenlei = fenlei;
	shaixuan.zhuangtai = zhuangtai;
	if (11 == shaixuan.DoModal())
	{
		shijianq = shaixuan.shijianq;
		shijianh = shaixuan.shijianh;
		fenlei = shaixuan.fenlei;
		zhuangtai = shaixuan.zhuangtai;
		showlist();
	}
	m_list.SetSelectionMark(-1);//重置位置
}


void Cbianji::OnBnClicked_Sousuo()
{
	// TODO:  在此添加控件通知处理程序代码
	showlist();
}


void Cbianji::OnBnClicked_Xiugai()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = m_list.GetSelectionMark();//获取位置
	int a = 0;//判断选了几条
	POSITION  pos = m_list.GetFirstSelectedItemPosition();
	for (POSITION posTemp = pos; posTemp != NULL;a++)
	{
		m_list.GetNextSelectedItem(posTemp);
	}
	if (-1 == i||1 < a)
	{
		m_list.SetSelectionMark(-1);
		MessageBox(L"请选择一条记录！");
		return;
	}
	Czengaixiangmu xiugai;
	xiugai.zengjia = 0;
	xiugai.biaozhi = listbiaoshi[i];
	if (11 == xiugai.DoModal()) showlist();
	else m_list.SetSelectionMark(-1);//重置位置
}



void Cbianji::OnBnClicked_Daoru()
{
	// TODO:  在此添加控件通知处理程序代码
	CString s;
	s =
	"导入TXT文本的格式：\r\n\r\n"
	"fenlei:（此处填写分类名，不要空格）\r\n"
	"wenti:\r\n"
	"    （此处填写问题）\r\n"
	"daan:\r\n"
	"    （此处填写答案）\r\n\r\n"
	"fenlei:（此处填写分类名，不要空格）\r\n"
	"wenti:\r\n"
	"    （此处填写问题）\r\n"
	"daan:\r\n"
	"    （此处填写答案）\r\n\r\n"
	"......（如此循环）\r\n\r\n"
	"注意：\r\n"
	" 1、若导入分类名在数据中不存在则归为未分类\r\n"
	" 2、若没写分类则默认是最近的上面一个分类\r\n"
	" 3、连续出现相同标识头，首标识头后都算内容中\r\n"
	" 4、数据前后的空格回车会自动去除\r\n"
	" 5、导入认可重复数据的存在！";
	MessageBox(s);
	m_list.SetSelectionMark(-1);//重置位置
	CFileDialog filedlg(true);
	filedlg.m_ofn.lpstrTitle = L"打开文本文档";
	filedlg.m_ofn.lpstrFilter = L"文本文档(*.txt)\0*.txt\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	导入文件(filedlg.GetPathName());
}


void Cbianji::导入文件(CString 地址)
{
	FILE *fp;
	if (0 != _wfopen_s(&fp, 地址, L"rb+"))
	{
		MessageBox(L"打开失败！");
		return;
	}
	fseek(fp, 0, SEEK_END);//文件指针移动到末尾
	int n = ftell(fp);//文件大小获取
	if (n == -1 || n > 0x40000000)
	{
		fclose(fp);
		MessageBox(L"文本过大（不能超过1GB）！");
		return;
	}
	fseek(fp, 0, 0);
	short bm;
	fread(&bm, 2, 1, fp);
	if (0xFFFFFEFF != bm)
	{
		fclose(fp);
		MessageBox(L"非Unicode编码！您可以在记事本的另存为中修改编码。");
		return;
	}
	if (n <= 2)
	{
		fclose(fp);
		MessageBox(L"文本为空！");
		return;
	}
	//判断是不是window下的Unicode编码
	int hc = 0, hh = 0, j = 0;//回车换行符统计
	fseek(fp, 0, SEEK_END);//文件指针移动到末尾
	n = (ftell(fp) - 2) / 2;//文件的字数
	wchar_t* w文件 = new wchar_t[n + 2];
	CString c文件;
	for (int i = 0; i < n + 1; i++)
	{
		w文件[i] = 0;//初始化
	}
	fseek(fp, 2, 0);
	fread(w文件, 2, n, fp);
	c文件 = w文件;
	j = c文件.Find(L"\r", j) + 1;//统计回车的个数
	while (j != 0)
	{
		hc++;
		j = c文件.Find(L"\r", j) + 1;
	}
	j = c文件.Find(L"\n", j) + 1;//统计换行的个数
	while (j != 0)
	{
		hh++;
		j = c文件.Find(L"\n", j) + 1;
	}
	if (hc != hh)
	{
		if (MessageBox(TEXT("非Windows的文本文档！\r\n是否转换？"), TEXT("行结束符不规范"), MB_YESNO) == IDNO)
		{
			fclose(fp);
			delete(w文件);
			return;
		}
		fclose(fp);
		if (0 != _wfopen_s(&fp, 地址, L"wb+"))
		{
			MessageBox(L"转换失败！");
			return;
		}
		wchar_t* ww = new wchar_t[2 * n + 1];
		for (int i = n; i >= 0; i--)//后移
		{
			*(w文件 + i + 1) = *(w文件 + i);
		}
		*w文件 = 0;//首置0
		int i2 = 0;
		for (int i1 = 1; i1 < n; i1++)
		{
			if (*(w文件 + i1) == '\r' && *(w文件 + i1 + 1) != '\n')//回车后面不是换行
			{
				*(ww + i2) = '\r';
				*(ww + i2 + 1) = '\n';
				i2 += 2;
			}
			else if (*(w文件 + i1) == '\n' && *(w文件 + i1 - 1) != '\r')//换行前不是回车
			{
				*(ww + i2) = '\r';
				*(ww + i2 + 1) = '\n';
				i2 += 2;
			}
			else
			{
				*(ww + i2) = *(w文件 + i1);
				i2++;
			}
		}
		if ((*(w文件 + n) == '\n' && *(w文件 + n - 1) != '\r') || *(w文件 + n) == '\r')
		{
			*(ww + i2) = '\r';
			*(ww + i2 + 1) = '\n';
			i2 += 2;
		}
		else
		{
			*(ww + i2) = *(w文件 + n);
			i2++;
		}
		fseek(fp, 0, 0);
		char b = 255, c = 254;
		fwrite(&b, 1, 1, fp);//Unicode标识符FFFE
		fwrite(&c, 1, 1, fp);
		fwrite(ww, 2, i2, fp);
		fflush(fp);
		delete(ww);
	}
	delete(w文件);
	if (导入数据(fp)) showlist();
	//释放
	fclose(fp);
	m_list.SetSelectionMark(-1);//重置位置
}


int Cbianji::导入数据(FILE* fp)//参数为正确的已打开的文本文档的指针
{
	int n, 分类个数 = 0, 问题个数 = 0, 答案个数 = 0, i = 0, 导入个数 = 0, 分类 = 0;
	fseek(fp, 0, SEEK_END);//文件指针移动到末尾
	n = (ftell(fp) - 2) / 2;//文件的字数
	wchar_t* w文件 = new wchar_t[n + 2];
	CString c文件, s, wt, da;
	for (int i = 0; i < n + 1; i++)
	{
		w文件[i] = 0;//初始化
	}
	fseek(fp, 2, 0);
	fread(w文件, 2, n, fp);
	c文件 = w文件;
	delete(w文件);
	i = c文件.Find(L"fenlei:", i) + 1;//统计“fenlei:”的个数
	while (i!=0)
	{
		分类个数++;
		i = c文件.Find(L"fenlei:", i)+1;
	}
	i = c文件.Find(L"wenti:", i) + 1;//统计“wenti:”的个数
	while (i != 0)
	{
		问题个数++;
		i = c文件.Find(L"wenti:", i) + 1;
	}
	i = c文件.Find(L"daan:", i) + 1;//统计“daan:”的个数
	while (i != 0)
	{
		答案个数++;
		i = c文件.Find(L"daan:", i) + 1;
	}
	if (问题个数 <= 0 || 答案个数 <= 0)
	{
		MessageBox(L"未检测到合符条件的项目！");
		return 0;
	}
	int f = 0, w = 0, d = 0;
	c文件 = L"\r\n" + c文件;
	f = c文件.Find(L"\r\nfenlei:");
	w = c文件.Find(L"\r\nwenti:\r\n");
	d = c文件.Find(L"\r\ndaan:\r\n");
	if (w < 0 || d < 0 || w > d || (f > w && d > f))
	{
		MessageBox(L"不符合格式要求！");
		return 0;
	}
	if (f >= 0 && f < w)//提取分类
	{
		s = c文件.Mid(f + 9, w - f - 9);
		s.Remove(L' ');
		s.Remove(L'\r');
		s.Remove(L'\n');
		分类 = gongju.分类存在(s);
	}
	//写入数据循环检测
	int cuowu, dd = c文件.GetLength();
	while (1)
	{
		//获取问题
		wt = c文件.Mid(w + 10, d - w - 10);
		wt.TrimLeft();//去除左边回车和空格
		wt.TrimRight();//去除右边回车和空格
		f = c文件.Find(L"\r\nfenlei:", d + 1);
		w = c文件.Find(L"\r\nwenti:\r\n", d + 1);
		//获取答案
		if ((w > 0 && f > 0 && f<w) || (f>0 && w < 0))
		{
			da = c文件.Mid(d + 9, f - d - 9);
			da.TrimLeft();//去除左边回车和空格
			da.TrimRight();//去除右边回车和空格
			dd = f;
		}
		else if ((w > 0 && f > 0 && w > f) || (f<0 && w>0))
		{
			da = c文件.Mid(d + 9, w - d - 9);
			da.TrimLeft();//去除左边回车和空格
			da.TrimRight();//去除右边回车和空格
			dd = w;
		}
		else //到末尾
		{
			da = c文件.Mid(d + 9, c文件.GetLength() - d - 9);
			da.TrimLeft();//去除左边回车和空格
			da.TrimRight();//去除右边回车和空格
			dd = c文件.GetLength();
			if (gongju.tianjiaXiangmu(wt, da, 分类))
			{
				导入个数++;
				cuowu = 0;
				break;
			}
			else
			{
				cuowu = 1;//字数或项目数超过限制
				break;
			}
		}
		//写入数据
		if (gongju.tianjiaXiangmu(wt, da, 分类)) 导入个数++;
		else
		{
			cuowu = 1;//字数或项目数超过限制
			break;
		}
		d = c文件.Find(L"\r\ndaan:\r\n", d + 1);
		if (w < 0 || d < 0 || w > d || (f > w && d > f))
		{
			cuowu = 2;//存在不符合格式要求！
			break;
		}
		//提取分类
		if (f > 0 && f < w)
		{
			s = c文件.Mid(f + 9, w - f - 9);
			s.Remove(L' ');
			s.Remove(L'\r');
			s.Remove(L'\n');
			if (s.GetLength()>0) 分类 = gongju.分类存在(s);
		}
	}
	s.Format(L"共检测到%d个“fenlei:”，%d个“wenti:”，%d个“daan:”\r\n\r\n成功导入%d个项目！", 分类个数,问题个数,答案个数,导入个数);
	//检测尾部是否只剩标识
	CString a=L"";
	int i1=0, i2=0, i3=0;
	a = c文件.Mid(dd, c文件.GetLength());
	a.Remove(L' ');
	a.Remove(L'\r');
	a.Remove(L'\n');
	i = a.Find(L"fenlei:", i) + 1;//统计剩“fenlei:”的个数
	while (i != 0)
	{
		i1++;
		i = a.Find(L"fenlei:", i) + 1;
	}
	i = a.Find(L"wenti:", i) + 1;//统计剩“wenti:”的个数
	while (i != 0)
	{
		i2++;
		i = a.Find(L"wenti:", i) + 1;
	}
	i = a.Find(L"daan:", i) + 1;//统计剩“daan:”的个数
	while (i != 0)
	{
		i3++;
		i = a.Find(L"daan:", i) + 1;
	}
	if (i1 < 0) i1 = 0;
	if (i2 < 0) i2 = 0;
	if (i3 < 0) i3 = 0;
	int zhisheng = i1 * 7 + i2 * 6 + i3 * 5 == a.GetLength();

	if ((1 == cuowu) && !(wt == ""&&da == "")) s += "\r\n\r\n可能出现了字数或总项目数不合要求的错误！";
	if (!zhisheng) s += "\r\n\r\n可能出现了不符合格式要求的错误！";
	MessageBox(s);
	return 导入个数;
}


void Cbianji::OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	int i = m_list.GetSelectionMark();//获取位置
	if (-1 == i)
	{
		return;
	}
	C项目内容 内容;
	内容.wenti = gongju.xmsj[listbiaoshi[i] - 1].wenti;
	内容.daan = gongju.xmsj[listbiaoshi[i] - 1].daan;
	内容.duan = gongju.xmsj[listbiaoshi[i] - 1].jieduan;
	内容.DoModal();
}


void Cbianji::OnBnClicked_Chongxue()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = m_list.GetSelectionMark();//获取位置
	if (-1 == i)
	{
		MessageBox(L"请选择记录！");
		return;
	}
	int a = 0, b[32704];
	POSITION  pos = m_list.GetFirstSelectedItemPosition();//首标识处
	for (POSITION posTemp = pos; posTemp != NULL; a++)
	{
		b[a] = m_list.GetNextSelectedItem(posTemp);//储存标识
		if (gongju.xmsj[listbiaoshi[b[a]] - 1].jieduan <= 0)
		{
			m_list.SetSelectionMark(-1);//重置位置
			MessageBox(L"不可选择待学习项目！");
			return;
		}
	}
	CString s;
	s.Format(L"您确定要重学这%d条记录？", a);
	if (MessageBox(s, TEXT("重学"), MB_YESNO) == IDNO)
	{
		m_list.SetSelectionMark(-1);//重置位置
		return;
	}
	for (int i = 0; i < a; i++)
	{
		gongju.xiugaiXiangmu(listbiaoshi[b[i]], 1, gongju.xmsj[listbiaoshi[b[i]] - 1].wenti, gongju.xmsj[listbiaoshi[b[i]] - 1].daan, gongju.xmsj[listbiaoshi[b[i]] - 1].fenlei);
	}
	showlist();
}


BOOL Cbianji::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	CString s;
	int a = 1;
	if (WM_KEYDOWN == pMsg->message && 13 == pMsg->wParam)
	{
		if (GetDlgItem(IDC_EDIT1) == GetFocus())
		{
			showlist();
			return FALSE;//进一步处理返回0值
		}
		else if (GetDlgItem(IDC_EDIT2) == GetFocus())//回车换页
		{
			GetDlgItem(IDC_EDIT2)->GetWindowText(s);
			a = _ttoi(s);
			a = a % 总页码;
			if (a == 0)
			{
				a = 总页码;
			}
			if (a != 当前页码)
			{
				当前页码 = a;
				s.Format(L"%d", 当前页码);
				GetDlgItem(IDC_EDIT2)->SetWindowText(s);
				换页 = 1;
				showlist();
			}
			else
			{
				s.Format(L"%d", 当前页码);
				GetDlgItem(IDC_EDIT2)->SetWindowText(s);
			}
			return FALSE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Cbianji::OnBnClicked_上一页()
{
	// TODO:  在此添加控件通知处理程序代码
	CString s;
	当前页码--;
	当前页码 = 当前页码%总页码;
	if (当前页码 == 0)
	{
		当前页码 = 总页码;
	}
	s.Format(L"%d", 当前页码);
	GetDlgItem(IDC_EDIT2)->SetWindowText(s);
	if (总页码 != 1)
	{
		换页 = 1;
		showlist();
	}
}


void Cbianji::OnBnClicked_下一页()
{
	// TODO:  在此添加控件通知处理程序代码
	CString s;
	当前页码++;
	当前页码 = 当前页码%总页码;
	if (当前页码 == 0)
	{
		当前页码 = 总页码;
	}
	s.Format(L"%d", 当前页码);
	GetDlgItem(IDC_EDIT2)->SetWindowText(s);
	if (总页码 != 1)
	{
		换页 = 1;
		showlist();
	}
}


void Cbianji::OnTimer(UINT_PTR nIDEvent) //焦点离开时恢复页码
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString s;
	if (GetDlgItem(IDC_EDIT2) != GetFocus() && nIDEvent == 1)
	{
		s.Format(L"%d", 当前页码);
		GetDlgItem(IDC_EDIT2)->SetWindowText(s);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void Cbianji::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	wchar_t filePath[5120];
	DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));//获取拖拽的第一个文件的路径
	CString s = filePath, s1;
	s1=s.Right(4);
	s1.MakeUpper();//全变大写
	if (s1 != ".TXT")
	{
		MessageBox(L"非文本文档！");
	}
	else
	{
		if (MessageBox(L"您确定导入？", TEXT("导入"), MB_YESNO) == IDYES)
		{
			导入文件(s);
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
}
