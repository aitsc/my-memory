#pragma once
class CGongju
{
public:
	CGongju();
	~CGongju();
public:
	short ��������[32705];
	char dlyxs;//������Ч��
	int wdwdz;//β��λ��ַ
	short ddyts[6];//�ζ�Ӧ����
	short jiange[4];//������Դ������еļ��
	short fxjz[4]; //��ϰ��׼��ʱ�䡢������ʱ�䡢���ռ������
	struct jydl //�������
	{
		short biaoshi;
		char shangshengyan;
		char lianxucishu;
		char xiajiangyan;
	}jydl[15];
	struct xmsj //��Ŀ����
	{
		char jieduan;//�׶Σ�-1Ϊ��ӣ�-128��ʾ��־Ϊ��
		short scsdsj;//�ϴ�����ʱ��
		short zhxgsj;//����޸�ʱ��
		char fenlei;//����
		int qian[2];//ǰ��,�ڶ�����ʾ���ݵ�Ԫ����
		int hou[2];//����,�ڶ�����ʾ���ݵ�Ԫ����
		CString wenti;//����
		CString daan;//��
		CString riqi;//����
	}xmsj[32704];
	struct flqk//�������
	{
		char cunzai;
		wchar_t name[17];
	}flqk[64];
	struct fxlb//��ϰ����
	{
		short biaoshi;
		char pingyancishu;//ƽ�ش���
		fxlb *next;
	}*fxlbt,*fxlbw;
	struct pxlb//��������
	{
		short biaoshi;
		pxlb *front;
		pxlb *next;
	}*pxlb,*pxlbyd;
	struct jylb //��������
	{
		short biaoshi;
		jylb *next;
	}*jylb,*jylbyd;
public:
	static int riqizhuanhua(int year, int month, int day);
	static CString riqizhuanhua(short xiangge);
	FILE* fp;
	void chushihua();
	char yc;//�쳣
	wchar_t yhm[6];//�û���
	int xtsj;//ϵͳʱ��
	short dxxxm;//��ѧϰ��Ŀ
	short zjyxm;//�ܼ�����Ŀ
	short yzwxm;//��������Ŀ
	short dfxxm;//����ϰ��Ŀ
	short fsj;//�״�ǩ��ʱ��
	short lsj;//�ϴ�ǩ��ʱ��
	short dwfl[2][65];//��λ����,����һ�Σ�С��7�ε�

	// �����������һ���µ���Ŀ
	int tianjiaPxlb(int biaoshi);
	int xiugaiJieduan(int biaoshi, char jieduan);
	// ��������������޸�
	int tianjiaJylb(int biaoshi);
	// ��ϰ����
	int tianjiaFxlb(int biaoshi, int b);
	// �޸��û���
	int xiugaiYhm(CString YHM);
	CString lujing;
	int tianjiaXiangmu(CString wen, CString da, char fenlei);
	static CTime riqizhuanhua(short xiangge, CTime time);
	int Qiandao();
	// ɾ���ñ�ʶ��Ӧ��һ����
	int shanchuKuai(short biaoshi, int wenti);
	// Ϊ�ñ�ʶ���һ����
	int tianjiaKuai(short biaoshi, int wenti);
	int xiugaiXiangmu(short biaoshi, int chongxue, CString wen, CString da, char fenlei);
	int shanchuXiangmu(short biaoshi);
	// ɾ�����������е�һ�����
	int shanchuPxlb(short biaoshi);
	// ɾ�����������е�һ�����
	int shanchuJylb(short biaoshi);
	// ɾ����ϰ�����е�һ�����
	int shanchuFxlb(short biaoshi);
	// ���쳣����0����Ա���
	int BEI_FEN();
	int xiugaiFenleiming(char fenlei, CString mingzi);
	int tianjiaFenlei(CString name);
	// ɾ��һ������
	int shanchufenlei(char fenlei);
	// ����������еĿհ׳������
	int buchongJydl();
	int д��������();
	int ѧϰһ��(int �ɹ�);
	int ��ϰһ��(int �ɹ�);
	int �����ʼ��(char fenlei);
	int ����һ��(int �ɹ�);
	short ��ȡ����();
	char ��ȡƽ�ؼ�һ(short biaoshi);
	char �������(CString fenlei);
	// ����Ϊ����λ��
	int daochu(CString dizhi, char fenlei);
	// ����Ŀ��fenlei1�ƶ���fenlei2
	int �ƶ�����(char fenlei1, char fenlei2);
	void ��������();
};

