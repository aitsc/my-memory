// Cbianji.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "Cbianji.h"
#include "afxdialogex.h"
#include "Czengaixiangmu.h"
#include "Cɸѡ.h"
#include "C��Ƭʽ.h"
#include "C��Ŀ����.h"

#define һҳ���� 250 //����33��

// Cbianji �Ի���

IMPLEMENT_DYNAMIC(Cbianji, CDialogEx)

Cbianji::Cbianji(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cbianji::IDD, pParent)
	, shijianq(0)
	, shijianh(0)
	, fenlei(64)
	, zhuangtai(3)
	, sousuo(_T(""))
	, Ĭ�����ӷ���(0)
	, ��ǰҳ��(1)
	, ��ҳ��(1)
	, ��ҳ(0)
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
	DDX_Text(pDX, IDC_EDIT2, ��ǰҳ��);
	DDV_MinMaxInt(pDX, ��ǰҳ��, 0, 999);
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
	ON_BN_CLICKED(IDC_BUTTON6, &Cbianji::OnBnClicked_��һҳ)
	ON_BN_CLICKED(IDC_BUTTON7, &Cbianji::OnBnClicked_��һҳ)
	ON_WM_TIMER()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Cbianji ��Ϣ�������


BOOL Cbianji::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��ShowWindow(SW_HIDE);
	shijianh = gongju.xtsj;
	for (int i = 0; i < 32704; i++) listbiaoshi[i] = 0;//��ʼ���б��ʶ
	SetMenu((menu.LoadMenu(IDR_LIST), &menu));//��ʾ�˵���
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//ѡ������+������
	m_list.InsertColumn(0, L"���", LVCFMT_LEFT, 37);
	m_list.InsertColumn(1, L"����", LVCFMT_LEFT, 210);
	m_list.InsertColumn(2, L"��", LVCFMT_LEFT, 96);
	m_list.InsertColumn(3, L"�޸�ʱ��", LVCFMT_LEFT, 96);
	m_list.InsertColumn(4, L"״̬", LVCFMT_LEFT, 48);
	m_list.InsertColumn(5, L"������", LVCFMT_LEFT, 210);
	showlist();
	SetTimer(1, 50, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


// ˢ���б�
int Cbianji::showlist()
{
	m_list.DeleteAllItems();//����б��ֹ�ظ�
	int i = 0, j, ii = 0;
	gongju.pxlbyd = gongju.pxlb;
	UpdateData(TRUE);
	if (!��ҳ)
	{
		��ǰҳ�� = 1;
	}
	if (��ҳ�� < 1 || ��ǰҳ�� < 1 || ��ҳ�� < ��ǰҳ��)
	{
		��ҳ�� = 1;
		��ǰҳ�� = 1;
	}
	sousuo.TrimLeft();//ȥ����߻س��Ϳո�
	sousuo.TrimRight();//ȥ���ұ߻س��Ϳո�
	sousuo.MakeLower();//תΪСд
	UpdateData(false);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);//�ػ洰��
	CString sw, sd, s;
	int ss, sj, fl, zt;
	while (NULL != gongju.pxlbyd->next)
	{
		sw = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].wenti;
		sd = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].daan;
		sw.MakeLower();//�����ִ�Сд����
		sd.MakeLower();
		ss = sw.Find(sousuo) != -1 || sd.Find(sousuo) != -1;//�ж��Ƿ�����
			        //�ж�ʱ���Ƿ��ڷ�Χ��
		sj = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].zhxgsj >= shijianq && gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].zhxgsj <= shijianh;
		if (fenlei >= 64) fl = 1; //�жϷ����Ƿ�һ��
		else fl = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].fenlei == fenlei;
		j = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].jieduan;//״̬
		if (zhuangtai >= 3) zt = 1;//�ж�״̬�Ƿ�һ��
		else
		{
			if (j <= 0 && zhuangtai == 0) zt = 1;
			else if (j > 6 && zhuangtai == 1) zt = 1;
			else if (j > 0 && j < 7 && zhuangtai == 2) zt = 1;
			else zt = 0;
		}
		if (ss&&sj&&fl&&zt)
		{
			if (��ǰҳ��*һҳ����>ii && (��ǰҳ��-1)*һҳ����<=ii)
			{
				s.Format(L"%d", i + 1);
				m_list.InsertItem(i, s);
				m_list.SetItemText(i, 1, sw);//����
				m_list.SetItemText(i, 2, sd);//��
				m_list.SetItemText(i, 3, gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].riqi);//�޸�ʱ��
				j = gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].jieduan;//״̬
				if (j <= 0) m_list.SetItemText(i, 4, L"��ѧϰ");//0
				else if (j>6) m_list.SetItemText(i, 4, L"������");//1
				else m_list.SetItemText(i, 4, L"����ϰ");//2
				m_list.SetItemText(i, 5, gongju.flqk[gongju.xmsj[gongju.pxlbyd->next->biaoshi - 1].fenlei].name);
				listbiaoshi[i] = gongju.pxlbyd->next->biaoshi;
				i++;
			}
			ii++;
		}
		gongju.pxlbyd = gongju.pxlbyd->next;
	}
	if (ii > 0 && ii%һҳ���� == 0)
	{
		��ҳ�� = ii / һҳ����;
	}
	else
	{
		��ҳ�� = ii / һҳ���� + 1;
	}
	s.Format(L"/%d", ��ҳ��);
	GetDlgItem(IDC_STATIC2)->SetWindowText(L"      ");
	GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	s.Format(L"����ǰ����й�%d�����ݣ�", ii);
	GetMenu()->DeleteMenu(0, MF_BYPOSITION);
	GetMenu()->AppendMenu(MF_ENABLED, ID_qwe, s);
	DrawMenuBar();
	��ҳ = 0;
	return ii;
}


void Cbianji::OnBnClicked_Zenjia()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (gongju.zjyxm>=32704)
	{
		MessageBox(L"��Ŀ������������ӣ�");
		return;
	}
	Czengaixiangmu zengai;
	zengai.zengjia = 1;
	zengai.Ĭ�����ӷ��� = Ĭ�����ӷ���;
	if (11 == zengai.DoModal())
	{
		Ĭ�����ӷ��� = zengai.Ĭ�����ӷ���;
		showlist();
	}
	m_list.SetSelectionMark(-1);//����λ��
}


void Cbianji::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(11);
	//CDialogEx::OnClose();
}


void Cbianji::OnBnClicked_Shanchu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (15 == gongju.zjyxm)
	{
		MessageBox(L"��Ŀ������15�����£�");
		return;
	}
	int i = m_list.GetSelectionMark();//��ȡλ��
	if (-1 == i)
	{
		MessageBox(L"��ѡ���¼��");
		return;
	}
	int a = 0, b[32704];
	POSITION  pos = m_list.GetFirstSelectedItemPosition();//�ױ�ʶ��
	for (POSITION posTemp = pos; posTemp != NULL; a++)
	{
		b[a] = m_list.GetNextSelectedItem(posTemp);//�����ʶ
	}
	if (gongju.zjyxm - a<15 && gongju.zjyxm>15)
	{
		MessageBox(L"��Ŀ������15�����£�");
		return;
	}
	CString s;
	s.Format(L"��ȷ��Ҫɾ����%d����¼��", a);
	if (MessageBox(s, TEXT("ɾ��"), MB_YESNO) == IDNO)
	{
		m_list.SetSelectionMark(-1);//����λ��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Cɸѡ shaixuan;
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
	m_list.SetSelectionMark(-1);//����λ��
}


void Cbianji::OnBnClicked_Sousuo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	showlist();
}


void Cbianji::OnBnClicked_Xiugai()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = m_list.GetSelectionMark();//��ȡλ��
	int a = 0;//�ж�ѡ�˼���
	POSITION  pos = m_list.GetFirstSelectedItemPosition();
	for (POSITION posTemp = pos; posTemp != NULL;a++)
	{
		m_list.GetNextSelectedItem(posTemp);
	}
	if (-1 == i||1 < a)
	{
		m_list.SetSelectionMark(-1);
		MessageBox(L"��ѡ��һ����¼��");
		return;
	}
	Czengaixiangmu xiugai;
	xiugai.zengjia = 0;
	xiugai.biaozhi = listbiaoshi[i];
	if (11 == xiugai.DoModal()) showlist();
	else m_list.SetSelectionMark(-1);//����λ��
}



void Cbianji::OnBnClicked_Daoru()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString s;
	s =
	"����TXT�ı��ĸ�ʽ��\r\n\r\n"
	"fenlei:���˴���д����������Ҫ�ո�\r\n"
	"wenti:\r\n"
	"    ���˴���д���⣩\r\n"
	"daan:\r\n"
	"    ���˴���д�𰸣�\r\n\r\n"
	"fenlei:���˴���д����������Ҫ�ո�\r\n"
	"wenti:\r\n"
	"    ���˴���д���⣩\r\n"
	"daan:\r\n"
	"    ���˴���д�𰸣�\r\n\r\n"
	"......�����ѭ����\r\n\r\n"
	"ע�⣺\r\n"
	" 1��������������������в��������Ϊδ����\r\n"
	" 2����ûд������Ĭ�������������һ������\r\n"
	" 3������������ͬ��ʶͷ���ױ�ʶͷ����������\r\n"
	" 4������ǰ��Ŀո�س����Զ�ȥ��\r\n"
	" 5�������Ͽ��ظ����ݵĴ��ڣ�";
	MessageBox(s);
	m_list.SetSelectionMark(-1);//����λ��
	CFileDialog filedlg(true);
	filedlg.m_ofn.lpstrTitle = L"���ı��ĵ�";
	filedlg.m_ofn.lpstrFilter = L"�ı��ĵ�(*.txt)\0*.txt\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	�����ļ�(filedlg.GetPathName());
}


void Cbianji::�����ļ�(CString ��ַ)
{
	FILE *fp;
	if (0 != _wfopen_s(&fp, ��ַ, L"rb+"))
	{
		MessageBox(L"��ʧ�ܣ�");
		return;
	}
	fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
	int n = ftell(fp);//�ļ���С��ȡ
	if (n == -1 || n > 0x40000000)
	{
		fclose(fp);
		MessageBox(L"�ı����󣨲��ܳ���1GB����");
		return;
	}
	fseek(fp, 0, 0);
	short bm;
	fread(&bm, 2, 1, fp);
	if (0xFFFFFEFF != bm)
	{
		fclose(fp);
		MessageBox(L"��Unicode���룡�������ڼ��±������Ϊ���޸ı��롣");
		return;
	}
	if (n <= 2)
	{
		fclose(fp);
		MessageBox(L"�ı�Ϊ�գ�");
		return;
	}
	//�ж��ǲ���window�µ�Unicode����
	int hc = 0, hh = 0, j = 0;//�س����з�ͳ��
	fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
	n = (ftell(fp) - 2) / 2;//�ļ�������
	wchar_t* w�ļ� = new wchar_t[n + 2];
	CString c�ļ�;
	for (int i = 0; i < n + 1; i++)
	{
		w�ļ�[i] = 0;//��ʼ��
	}
	fseek(fp, 2, 0);
	fread(w�ļ�, 2, n, fp);
	c�ļ� = w�ļ�;
	j = c�ļ�.Find(L"\r", j) + 1;//ͳ�ƻس��ĸ���
	while (j != 0)
	{
		hc++;
		j = c�ļ�.Find(L"\r", j) + 1;
	}
	j = c�ļ�.Find(L"\n", j) + 1;//ͳ�ƻ��еĸ���
	while (j != 0)
	{
		hh++;
		j = c�ļ�.Find(L"\n", j) + 1;
	}
	if (hc != hh)
	{
		if (MessageBox(TEXT("��Windows���ı��ĵ���\r\n�Ƿ�ת����"), TEXT("�н��������淶"), MB_YESNO) == IDNO)
		{
			fclose(fp);
			delete(w�ļ�);
			return;
		}
		fclose(fp);
		if (0 != _wfopen_s(&fp, ��ַ, L"wb+"))
		{
			MessageBox(L"ת��ʧ�ܣ�");
			return;
		}
		wchar_t* ww = new wchar_t[2 * n + 1];
		for (int i = n; i >= 0; i--)//����
		{
			*(w�ļ� + i + 1) = *(w�ļ� + i);
		}
		*w�ļ� = 0;//����0
		int i2 = 0;
		for (int i1 = 1; i1 < n; i1++)
		{
			if (*(w�ļ� + i1) == '\r' && *(w�ļ� + i1 + 1) != '\n')//�س����治�ǻ���
			{
				*(ww + i2) = '\r';
				*(ww + i2 + 1) = '\n';
				i2 += 2;
			}
			else if (*(w�ļ� + i1) == '\n' && *(w�ļ� + i1 - 1) != '\r')//����ǰ���ǻس�
			{
				*(ww + i2) = '\r';
				*(ww + i2 + 1) = '\n';
				i2 += 2;
			}
			else
			{
				*(ww + i2) = *(w�ļ� + i1);
				i2++;
			}
		}
		if ((*(w�ļ� + n) == '\n' && *(w�ļ� + n - 1) != '\r') || *(w�ļ� + n) == '\r')
		{
			*(ww + i2) = '\r';
			*(ww + i2 + 1) = '\n';
			i2 += 2;
		}
		else
		{
			*(ww + i2) = *(w�ļ� + n);
			i2++;
		}
		fseek(fp, 0, 0);
		char b = 255, c = 254;
		fwrite(&b, 1, 1, fp);//Unicode��ʶ��FFFE
		fwrite(&c, 1, 1, fp);
		fwrite(ww, 2, i2, fp);
		fflush(fp);
		delete(ww);
	}
	delete(w�ļ�);
	if (��������(fp)) showlist();
	//�ͷ�
	fclose(fp);
	m_list.SetSelectionMark(-1);//����λ��
}


int Cbianji::��������(FILE* fp)//����Ϊ��ȷ���Ѵ򿪵��ı��ĵ���ָ��
{
	int n, ������� = 0, ������� = 0, �𰸸��� = 0, i = 0, ������� = 0, ���� = 0;
	fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
	n = (ftell(fp) - 2) / 2;//�ļ�������
	wchar_t* w�ļ� = new wchar_t[n + 2];
	CString c�ļ�, s, wt, da;
	for (int i = 0; i < n + 1; i++)
	{
		w�ļ�[i] = 0;//��ʼ��
	}
	fseek(fp, 2, 0);
	fread(w�ļ�, 2, n, fp);
	c�ļ� = w�ļ�;
	delete(w�ļ�);
	i = c�ļ�.Find(L"fenlei:", i) + 1;//ͳ�ơ�fenlei:���ĸ���
	while (i!=0)
	{
		�������++;
		i = c�ļ�.Find(L"fenlei:", i)+1;
	}
	i = c�ļ�.Find(L"wenti:", i) + 1;//ͳ�ơ�wenti:���ĸ���
	while (i != 0)
	{
		�������++;
		i = c�ļ�.Find(L"wenti:", i) + 1;
	}
	i = c�ļ�.Find(L"daan:", i) + 1;//ͳ�ơ�daan:���ĸ���
	while (i != 0)
	{
		�𰸸���++;
		i = c�ļ�.Find(L"daan:", i) + 1;
	}
	if (������� <= 0 || �𰸸��� <= 0)
	{
		MessageBox(L"δ��⵽�Ϸ���������Ŀ��");
		return 0;
	}
	int f = 0, w = 0, d = 0;
	c�ļ� = L"\r\n" + c�ļ�;
	f = c�ļ�.Find(L"\r\nfenlei:");
	w = c�ļ�.Find(L"\r\nwenti:\r\n");
	d = c�ļ�.Find(L"\r\ndaan:\r\n");
	if (w < 0 || d < 0 || w > d || (f > w && d > f))
	{
		MessageBox(L"�����ϸ�ʽҪ��");
		return 0;
	}
	if (f >= 0 && f < w)//��ȡ����
	{
		s = c�ļ�.Mid(f + 9, w - f - 9);
		s.Remove(L' ');
		s.Remove(L'\r');
		s.Remove(L'\n');
		���� = gongju.�������(s);
	}
	//д������ѭ�����
	int cuowu, dd = c�ļ�.GetLength();
	while (1)
	{
		//��ȡ����
		wt = c�ļ�.Mid(w + 10, d - w - 10);
		wt.TrimLeft();//ȥ����߻س��Ϳո�
		wt.TrimRight();//ȥ���ұ߻س��Ϳո�
		f = c�ļ�.Find(L"\r\nfenlei:", d + 1);
		w = c�ļ�.Find(L"\r\nwenti:\r\n", d + 1);
		//��ȡ��
		if ((w > 0 && f > 0 && f<w) || (f>0 && w < 0))
		{
			da = c�ļ�.Mid(d + 9, f - d - 9);
			da.TrimLeft();//ȥ����߻س��Ϳո�
			da.TrimRight();//ȥ���ұ߻س��Ϳո�
			dd = f;
		}
		else if ((w > 0 && f > 0 && w > f) || (f<0 && w>0))
		{
			da = c�ļ�.Mid(d + 9, w - d - 9);
			da.TrimLeft();//ȥ����߻س��Ϳո�
			da.TrimRight();//ȥ���ұ߻س��Ϳո�
			dd = w;
		}
		else //��ĩβ
		{
			da = c�ļ�.Mid(d + 9, c�ļ�.GetLength() - d - 9);
			da.TrimLeft();//ȥ����߻س��Ϳո�
			da.TrimRight();//ȥ���ұ߻س��Ϳո�
			dd = c�ļ�.GetLength();
			if (gongju.tianjiaXiangmu(wt, da, ����))
			{
				�������++;
				cuowu = 0;
				break;
			}
			else
			{
				cuowu = 1;//��������Ŀ����������
				break;
			}
		}
		//д������
		if (gongju.tianjiaXiangmu(wt, da, ����)) �������++;
		else
		{
			cuowu = 1;//��������Ŀ����������
			break;
		}
		d = c�ļ�.Find(L"\r\ndaan:\r\n", d + 1);
		if (w < 0 || d < 0 || w > d || (f > w && d > f))
		{
			cuowu = 2;//���ڲ����ϸ�ʽҪ��
			break;
		}
		//��ȡ����
		if (f > 0 && f < w)
		{
			s = c�ļ�.Mid(f + 9, w - f - 9);
			s.Remove(L' ');
			s.Remove(L'\r');
			s.Remove(L'\n');
			if (s.GetLength()>0) ���� = gongju.�������(s);
		}
	}
	s.Format(L"����⵽%d����fenlei:����%d����wenti:����%d����daan:��\r\n\r\n�ɹ�����%d����Ŀ��", �������,�������,�𰸸���,�������);
	//���β���Ƿ�ֻʣ��ʶ
	CString a=L"";
	int i1=0, i2=0, i3=0;
	a = c�ļ�.Mid(dd, c�ļ�.GetLength());
	a.Remove(L' ');
	a.Remove(L'\r');
	a.Remove(L'\n');
	i = a.Find(L"fenlei:", i) + 1;//ͳ��ʣ��fenlei:���ĸ���
	while (i != 0)
	{
		i1++;
		i = a.Find(L"fenlei:", i) + 1;
	}
	i = a.Find(L"wenti:", i) + 1;//ͳ��ʣ��wenti:���ĸ���
	while (i != 0)
	{
		i2++;
		i = a.Find(L"wenti:", i) + 1;
	}
	i = a.Find(L"daan:", i) + 1;//ͳ��ʣ��daan:���ĸ���
	while (i != 0)
	{
		i3++;
		i = a.Find(L"daan:", i) + 1;
	}
	if (i1 < 0) i1 = 0;
	if (i2 < 0) i2 = 0;
	if (i3 < 0) i3 = 0;
	int zhisheng = i1 * 7 + i2 * 6 + i3 * 5 == a.GetLength();

	if ((1 == cuowu) && !(wt == ""&&da == "")) s += "\r\n\r\n���ܳ���������������Ŀ������Ҫ��Ĵ���";
	if (!zhisheng) s += "\r\n\r\n���ܳ����˲����ϸ�ʽҪ��Ĵ���";
	MessageBox(s);
	return �������;
}


void Cbianji::OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int i = m_list.GetSelectionMark();//��ȡλ��
	if (-1 == i)
	{
		return;
	}
	C��Ŀ���� ����;
	����.wenti = gongju.xmsj[listbiaoshi[i] - 1].wenti;
	����.daan = gongju.xmsj[listbiaoshi[i] - 1].daan;
	����.duan = gongju.xmsj[listbiaoshi[i] - 1].jieduan;
	����.DoModal();
}


void Cbianji::OnBnClicked_Chongxue()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = m_list.GetSelectionMark();//��ȡλ��
	if (-1 == i)
	{
		MessageBox(L"��ѡ���¼��");
		return;
	}
	int a = 0, b[32704];
	POSITION  pos = m_list.GetFirstSelectedItemPosition();//�ױ�ʶ��
	for (POSITION posTemp = pos; posTemp != NULL; a++)
	{
		b[a] = m_list.GetNextSelectedItem(posTemp);//�����ʶ
		if (gongju.xmsj[listbiaoshi[b[a]] - 1].jieduan <= 0)
		{
			m_list.SetSelectionMark(-1);//����λ��
			MessageBox(L"����ѡ���ѧϰ��Ŀ��");
			return;
		}
	}
	CString s;
	s.Format(L"��ȷ��Ҫ��ѧ��%d����¼��", a);
	if (MessageBox(s, TEXT("��ѧ"), MB_YESNO) == IDNO)
	{
		m_list.SetSelectionMark(-1);//����λ��
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
	// TODO:  �ڴ����ר�ô����/����û���
	CString s;
	int a = 1;
	if (WM_KEYDOWN == pMsg->message && 13 == pMsg->wParam)
	{
		if (GetDlgItem(IDC_EDIT1) == GetFocus())
		{
			showlist();
			return FALSE;//��һ��������0ֵ
		}
		else if (GetDlgItem(IDC_EDIT2) == GetFocus())//�س���ҳ
		{
			GetDlgItem(IDC_EDIT2)->GetWindowText(s);
			a = _ttoi(s);
			a = a % ��ҳ��;
			if (a == 0)
			{
				a = ��ҳ��;
			}
			if (a != ��ǰҳ��)
			{
				��ǰҳ�� = a;
				s.Format(L"%d", ��ǰҳ��);
				GetDlgItem(IDC_EDIT2)->SetWindowText(s);
				��ҳ = 1;
				showlist();
			}
			else
			{
				s.Format(L"%d", ��ǰҳ��);
				GetDlgItem(IDC_EDIT2)->SetWindowText(s);
			}
			return FALSE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Cbianji::OnBnClicked_��һҳ()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString s;
	��ǰҳ��--;
	��ǰҳ�� = ��ǰҳ��%��ҳ��;
	if (��ǰҳ�� == 0)
	{
		��ǰҳ�� = ��ҳ��;
	}
	s.Format(L"%d", ��ǰҳ��);
	GetDlgItem(IDC_EDIT2)->SetWindowText(s);
	if (��ҳ�� != 1)
	{
		��ҳ = 1;
		showlist();
	}
}


void Cbianji::OnBnClicked_��һҳ()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString s;
	��ǰҳ��++;
	��ǰҳ�� = ��ǰҳ��%��ҳ��;
	if (��ǰҳ�� == 0)
	{
		��ǰҳ�� = ��ҳ��;
	}
	s.Format(L"%d", ��ǰҳ��);
	GetDlgItem(IDC_EDIT2)->SetWindowText(s);
	if (��ҳ�� != 1)
	{
		��ҳ = 1;
		showlist();
	}
}


void Cbianji::OnTimer(UINT_PTR nIDEvent) //�����뿪ʱ�ָ�ҳ��
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString s;
	if (GetDlgItem(IDC_EDIT2) != GetFocus() && nIDEvent == 1)
	{
		s.Format(L"%d", ��ǰҳ��);
		GetDlgItem(IDC_EDIT2)->SetWindowText(s);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void Cbianji::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	wchar_t filePath[5120];
	DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));//��ȡ��ק�ĵ�һ���ļ���·��
	CString s = filePath, s1;
	s1=s.Right(4);
	s1.MakeUpper();//ȫ���д
	if (s1 != ".TXT")
	{
		MessageBox(L"���ı��ĵ���");
	}
	else
	{
		if (MessageBox(L"��ȷ�����룿", TEXT("����"), MB_YESNO) == IDYES)
		{
			�����ļ�(s);
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
}
