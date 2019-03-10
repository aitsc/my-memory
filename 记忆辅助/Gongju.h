#pragma once
class CGongju
{
public:
	CGongju();
	~CGongju();
public:
	short 反向数组[32705];
	char dlyxs;//队列有效数
	int wdwdz;//尾单位地址
	short ddyts[6];//段对应天数
	short jiange[4];//连续答对次数所有的间隔
	short fxjz[4]; //复习基准，时间、个数、时间、今日记忆个数
	struct jydl //记忆队列
	{
		short biaoshi;
		char shangshengyan;
		char lianxucishu;
		char xiajiangyan;
	}jydl[15];
	struct xmsj //项目数据
	{
		char jieduan;//阶段，-1为入队，-128表示标志为空
		short scsdsj;//上次升段时间
		short zhxgsj;//最后修改时间
		char fenlei;//分类
		int qian[2];//前驱,第二个表示数据单元个数
		int hou[2];//后驱,第二个表示数据单元个数
		CString wenti;//问题
		CString daan;//答案
		CString riqi;//日期
	}xmsj[32704];
	struct flqk//分类情况
	{
		char cunzai;
		wchar_t name[17];
	}flqk[64];
	struct fxlb//复习链表
	{
		short biaoshi;
		char pingyancishu;//平沿次数
		fxlb *next;
	}*fxlbt,*fxlbw;
	struct pxlb//排序链表
	{
		short biaoshi;
		pxlb *front;
		pxlb *next;
	}*pxlb,*pxlbyd;
	struct jylb //记忆链表
	{
		short biaoshi;
		jylb *next;
	}*jylb,*jylbyd;
public:
	static int riqizhuanhua(int year, int month, int day);
	static CString riqizhuanhua(short xiangge);
	FILE* fp;
	void chushihua();
	char yc;//异常
	wchar_t yhm[6];//用户名
	int xtsj;//系统时间
	short dxxxm;//待学习项目
	short zjyxm;//总记忆项目
	short yzwxm;//已掌握项目
	short dfxxm;//待复习项目
	short fsj;//首次签到时间
	short lsj;//上次签到时间
	short dwfl[2][65];//段位分类,大于一段，小于7段的

	// 排序链表插入一个新的项目
	int tianjiaPxlb(int biaoshi);
	int xiugaiJieduan(int biaoshi, char jieduan);
	// 记忆链表，内外存修改
	int tianjiaJylb(int biaoshi);
	// 复习链表
	int tianjiaFxlb(int biaoshi, int b);
	// 修改用户名
	int xiugaiYhm(CString YHM);
	CString lujing;
	int tianjiaXiangmu(CString wen, CString da, char fenlei);
	static CTime riqizhuanhua(short xiangge, CTime time);
	int Qiandao();
	// 删除该标识对应的一个块
	int shanchuKuai(short biaoshi, int wenti);
	// 为该标识添加一个块
	int tianjiaKuai(short biaoshi, int wenti);
	int xiugaiXiangmu(short biaoshi, int chongxue, CString wen, CString da, char fenlei);
	int shanchuXiangmu(short biaoshi);
	// 删除排序链表中的一个结点
	int shanchuPxlb(short biaoshi);
	// 删除记忆链表中的一个结点
	int shanchuJylb(short biaoshi);
	// 删除复习链表中的一个结点
	int shanchuFxlb(short biaoshi);
	// 若异常等于0则可以备份
	int BEI_FEN();
	int xiugaiFenleiming(char fenlei, CString mingzi);
	int tianjiaFenlei(CString name);
	// 删除一个分类
	int shanchufenlei(char fenlei);
	// 将记忆队列中的空白出填补起来
	int buchongJydl();
	int 写入记忆队列();
	int 学习一个(int 成功);
	int 复习一个(int 成功);
	int 反向初始化(char fenlei);
	int 反向一个(int 成功);
	short 获取反向();
	char 获取平沿加一(short biaoshi);
	char 分类存在(CString fenlei);
	// 参数为保存位置
	int daochu(CString dizhi, char fenlei);
	// 把项目从fenlei1移动到fenlei2
	int 移动分类(char fenlei1, char fenlei2);
	void 重新整理();
};

