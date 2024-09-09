
// kesheMFCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "kesheMFC.h"
#include "kesheMFCDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <ctime>
#include <Windows.h>
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


static int NHour = 7;
static int NMinute = 0;

//飞机类
class Plane {

public:
    char PName[100];   //航班号
    int PQHtime;       //起飞时间（小时）
    int PQMtime;       //起飞时间（分钟）
    int PAHtime;       //降落时间（小时）
    int PAMtime;       //降落时间（分钟）
    int PFuel;         //油量

public:
    Plane()
    {
    }
    Plane(char PName[100],int PQHtime, int PQMtime, int PAHtime, int PAMtime, int PFuel) {
        for (int i = 0; i < 100; i++) {
            this->PName[i] = PName[i];
        }
        this->PQHtime = PQHtime;
        this->PQMtime = PQMtime;
        this->PAHtime = PAHtime;
        this->PAMtime = PAMtime;
        this->PFuel = PFuel;

    }
    virtual ~Plane() {

    }
public:

    bool everyTime() {
        PFuel = PFuel - 5;
        return true;
    }
};



class Road {
public:
    int Rflag;
    Road() {//初始化跑道 0为空
        Rflag = 0;
    }
    bool ISOCCUPY() {
        Rflag = 1;
        return true;
    }
    bool NOTOCCUPY() {
        Rflag = 0;
        return true;
    }
};


class Queue {
public:
    bool getFront(Plane& item);
    bool clear();
    bool deQueue(Plane& item);
    bool enQueue(const Plane& item);
    bool isEmpty();
    bool isFull();
    bool deleteitem(int n);
};

class PQueue :public Queue {
public:
    int mSize, front, rear;
    Plane* p;

    PQueue() {
    }
    PQueue(int size) {
        mSize = size + 1;
        p = new Plane[mSize];
        front = rear = 0;
    }
    ~PQueue() {
        delete[] p;
    }

    bool getFront(Plane& item) {
        if (front == rear) {
            cout << "队空" << endl;
            return false;
        }
        item = p[front];
        return true;
    }

    void clear() {
        front = rear;
    }

    bool enQueue(const Plane item)
    {
        if (((rear + 1) % mSize) == front) {
            cout << "队满" << endl;
            return false;
        }
        p[rear] = item;
        rear = (rear + 1) % mSize;
        return true;
    }
    bool deQueue(Plane& item) {
        if (front == rear) {
            cout << "队空" << endl;
            return false;
        }
        item = p[front];
        front = (front + 1) % mSize;
        return true;
    }


    bool isEmpty() {
        if (front == rear)
            return true;
        else
            return false;
    }

    void deleteitem(int n) {//从队列中移除某元素
        for (int i = n; i < rear - 1; i = (i + 1) % mSize) {
            p[i] = p[i + 1];
        }
        rear = (rear - 1) % mSize;
    }
};



// CkesheMFCDlg 对话框




CkesheMFCDlg::CkesheMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KESHEMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkesheMFCDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON1, m_begin);
    DDX_Control(pDX, IDC_BUTTON2, m_stop);
    DDX_Control(pDX, IDC_BUTTON3, m_exit);
    DDX_Control(pDX, IDC_EDIT1, m_edit1);
    // DDX_Control(pDX, IDC_PIC_STATIC, m_cPicture);
    DDX_Control(pDX, IDC_WAY1_STATIC, m_bmp1);
    // DDX_Control(pDX, IDC_WAY2_STATIC, m_bmp2);
    // DDX_Control(pDX, IDC_WAY3_STATIC, m_bmp3);
    // DDX_Control(pDX, IDC_WAY4_STATIC, m_bmp4);
    DDX_Control(pDX, IDC_EDIT4, m_edit4);
    DDX_Control(pDX, IDC_EDIT2, m_edit2);
    DDX_Control(pDX, IDC_EDIT3, m_edit3);
    DDX_Control(pDX, IDC_EDIT5, m_edit5);
    DDX_Control(pDX, IDC_EDIT6, m_edit6);
}

BEGIN_MESSAGE_MAP(CkesheMFCDlg, CDialogEx)
	ON_WM_PAINT()
    ON_WM_CLOSE()
    //  ON_BN_CLICKED(IDC_BUTTON3, &CkesheMFCDlg::OnBnClickedButtonExit)
    ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CkesheMFCDlg::OnBnClickedButton1)
   // ON_EN_CHANGE(IDC_EDIT3, &CkesheMFCDlg::OnEnChangeEdit3)
    ON_BN_CLICKED(IDC_BUTTON3, &CkesheMFCDlg::OnBnClickedButton3)
   // ON_STN_CLICKED(IDC_WAY4_STATIC, &CkesheMFCDlg::OnStnClickedWay4Static)
END_MESSAGE_MAP()


// CkesheMFCDlg 消息处理程序

BOOL CkesheMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_bmp1.ModifyStyle(0, SS_BITMAP); 
    HBITMAP hBmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6));
    m_bmp1.SetBitmap(hBmp);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CkesheMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CkesheMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//按下开始按钮
void CkesheMFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

    int QPNum = 0;
    int APNum = 0;
    int ALLNum = 0;
    char a, b;
    char sum[4000];
    char op[4000]=" ";
    char FPName[100];
    int PQHtime, PQMtime, PAHtime, PAMtime;
    char info[4000] = " ";
    char QFinfo[4000] = " ";
    ifstream file("C:\\Users\\23854\\Desktop\\test3.txt");
    if (!file.is_open())  //统计起飞降落飞机数量
    {
        cout << "can not open this file" << endl;
       // return 0;
    }
    while (!file.eof()) {

        //  file >> f >> g >> Fnum >> c >>PQHtime >> a >>PQMtime >> d >>PAHtime >> b >> PAMtime >> e;
        //  cout<< f << g << Fnum << c << PQHtime << a << PQMtime << d << PAHtime << b << PAMtime <<endl;
        file >> FPName >> PQHtime >> a >> PQMtime >> PAHtime >> b >> PAMtime;
        cout << FPName << " " << PQHtime << a << PQMtime << " " << PAHtime << b << PAMtime << endl;
        sprintf(sum, "%s %d%c%d %d%c%d ",FPName, PQHtime, a, PQMtime,PAHtime,b,PAMtime);
       // SetDlgItemText(IDC_EDIT1, CA2CT(str));
       // bool SetWindowText(m_edit1, sum);
       // oss << PName << " " << a << " " << b << endl;
       // cout << oss.str() << endl;
      //  temp = PName;
        sprintf(op, "%s\r\n%s", op, sum);
        m_edit1.SetSel(0, -1);
        m_edit1.ReplaceSel(op);
       
     //   cwnd->SetWindowText(_T("asdfg"));
        if (PAHtime == 0 && PAMtime == 0) {
            // cout << "file was opened" << endl;
            QPNum++;
            // cout << "111" << endl;
        }
        else if (PQHtime == 0 && PQMtime == 0) {
            //    cout << "file was opened" << endl;
            APNum++;
            // cout << "222" << endl;
        }
    }
    file.close();
    ALLNum = QPNum + APNum;
    PQueue QF(QPNum);
    PQueue JL(APNum);
    PQueue Jinji(ALLNum);
    Road way[4];
    int FLAG = 0;
    //cout << "*********" << endl;
    cout << "航班信息显示完毕" << endl;
    int i;
  //  int  PQHtime, PQMtime, PAHtime, PAMtime;
    int PFuel;
   // string PName;
    int QFcnt = 0, JLcnt = 0;//起飞计数 降落计数
    int ALLcnt = 0;//全部飞机计数
    int fuel;//随机生成油量
    int JLF;//JL队列的Front
    JLF = JL.front;
    char qfdl[4000]=" ";
    char jldl[4000]=" ";
    int jlnum = 0;
   // char a, b;
     srand((int)time(0));
   // while (1) {
        while (ALLNum > 0) {
            sprintf(info, "%s\r\n%d:%d:\r\n", info, NHour, NMinute);
            m_edit3.SetSel(0, -1);
            m_edit3.ReplaceSel(info);
            sprintf(QFinfo, "%s\r\n%d:%d:\r\n", QFinfo, NHour, NMinute);
            m_edit2.SetSel(0, -1);
            m_edit2.ReplaceSel(QFinfo);
            sprintf(jldl, "%s\r\n%d:%d:\r\n", jldl, NHour, NMinute);
            m_edit6.SetSel(0, -1);
            m_edit6.ReplaceSel(jldl);
            sprintf(qfdl, "%s\r\n%d:%d:\r\n", qfdl, NHour, NMinute);
            m_edit5.SetSel(0, -1);
            m_edit5.ReplaceSel(qfdl);
            for (int i = 0; i < 4; i++) {
                way[i].NOTOCCUPY();//清空跑道
            }
            QFcnt = 0;
            JLcnt = 0;
            cout << "kkkkkkkkkk" << ALLNum << "kkkkkkkkkk" << endl;
            ifstream file("C:\\Users\\23854\\Desktop\\test3.txt");
 
            if (!file.is_open())
            {
                cout << "can not open file !" << endl;
            }
            while (!file.eof()) {
                file >> FPName >> PQHtime >> a >> PQMtime >> PAHtime >> b >> PAMtime;
                cout << "  " << NHour << ":" << NMinute << endl;
                if ((PAHtime == 0 && PAMtime == 0) && (PQHtime == NHour && PQMtime >= NMinute && PQMtime < NMinute + 15)) {
                    Plane fj(FPName, PQHtime, PQMtime, PAHtime, PAMtime, 100);
                    // cout << "qifei mSize" << QF.mSize << endl;
                    if (QFcnt <= 40) {
                        QF.enQueue(fj);
                        cout << fj.PName << "进入起飞队列" << endl;
                        QFcnt = QFcnt + 1;
                        cout << "起飞队列中有：" << endl;
                        sprintf(qfdl, "%s\r\n 起飞队列中有%s ", qfdl, fj.PName);
                        m_edit5.SetSel(0, -1);
                        m_edit5.ReplaceSel(qfdl);
                    }
                    else
                        break;
                }
                else if ((PQHtime == 0 && PQMtime == 0) && (PAHtime == NHour && PAMtime >= NMinute && PAMtime < NMinute + 15)) {
                    fuel = rand() % 100 + 1;

                    Plane fj(FPName, PQHtime, PQMtime, PAHtime, PAMtime, fuel);
                    if (jlnum <= 40) {
                        JL.enQueue(fj);
                        cout << fj.PName << "进入降落队列" << endl;
                        jlnum = jlnum + 1;
                        cout << "降落队列中有：" << endl;
                        sprintf(jldl, "%s\r\n 降落队列中有%s,油量为：%d ", jldl, fj.PName ,fj.PFuel);
                        m_edit6.SetSel(0, -1);
                        m_edit6.ReplaceSel(jldl);

                    }
                    else
                        break;
                }
            }
            file.close();
            int t;
            int c = JL.front;
            int v = JL.rear;
            ALLcnt = 0;

            if (JL.rear >= JL.front) {
                t = JL.rear - JL.front;
            }
            else {
                t = JL.rear - JL.front + JL.mSize;
            }

            while (ALLcnt != t) {
                for (JLF = JL.front; JLF < JL.rear; JLF = (JLF + 1) % JL.mSize) {
                    if (JL.p[JLF].PFuel < 10) {
                        Plane fj;
                        fj = JL.p[JLF];
                        JL.deleteitem(JLF);
                        jlnum--;
                        cout << fj.PName << "进入紧急队列" << endl;
                        sprintf(jldl, "%s\r\n 紧急队列中有%s ", jldl, fj.PName);
                        m_edit6.SetSel(0, -1);
                        m_edit6.ReplaceSel(jldl);
                        Jinji.enQueue(fj);
                        JLF = JL.front;
                        ALLcnt = 0;
                        break;

                    }
                    else {
                        ALLcnt = ALLcnt + 1;
                    }
                }
                break;
            }

            if (!QF.isEmpty() || !JL.isEmpty() || !Jinji.isEmpty()) {
                //有紧急
                if (!Jinji.isEmpty()) {
                    //按油量排序
                    for (int m = Jinji.front; m < Jinji.rear - 1; m = (m + 1) % Jinji.mSize) {
                        for (int n = m; n < Jinji.rear; n = (n + 1) % Jinji.mSize) {
                            if (Jinji.p[m].PFuel > Jinji.p[n].PFuel) {
                                Plane tmp;
                                tmp = Jinji.p[m];
                                Jinji.p[m] = Jinji.p[n];
                                Jinji.p[n] = tmp;
                            }
                        }
                    }
                    int jinjinum = 0;
                    for (int i = Jinji.front; i < Jinji.rear; i = (i + 1) % Jinji.mSize) {
                        jinjinum = jinjinum + 1;
                    }
                    //只有一架紧急飞机时
                    if (jinjinum == 1) {
                        way[3].ISOCCUPY();//占用紧急跑道
                        Plane fj;
                        Jinji.deQueue(fj);
                        cout << fj.PName << "降落在紧急跑道" << endl;
                        
                        sprintf(info, " %s\r\n%s 降落在紧急跑道,油量为%d",info,fj.PName,fj.PFuel);
                        m_edit3.SetSel(0, -1);
                        m_edit3.ReplaceSel(info);

                        cout << "油量为" << fj.PFuel << endl;
                        ALLNum = ALLNum - 1;
                    }
                    //不止一架紧急
                    else {
                        way[3].ISOCCUPY();
                        Plane fj;
                        Jinji.deQueue(fj);
                        cout << fj.PName << "降落在紧急跑道" << endl;
                        cout << "油量为" << fj.PFuel << endl;
                        sprintf(info, " %s\r\n%s降落在紧急跑道,油量为%d", info, fj.PName, fj.PFuel);
                        m_edit3.SetSel(0, -1);
                        m_edit3.ReplaceSel(info);

                        ALLNum = ALLNum - 1;
                        jinjinum = jinjinum - 1;
                        int waynum = 2;
                        while (jinjinum != 0) {
                            if (waynum != 0) {
                                way[waynum].ISOCCUPY();
                                Plane temp;
                                Jinji.deQueue(temp);
                                cout << temp.PName << "在第" << waynum + 1 << "道降落" << endl;
                                cout << "油量为" << temp.PFuel << endl;
                                sprintf(info, " %s\r\n%s降落在第%d道,油量为%d", info, fj.PName,waynum+1, fj.PFuel);
                                m_edit3.SetSel(0, -1);
                                m_edit3.ReplaceSel(info);
                                ALLNum--;
                                jlnum--;
                                jinjinum--;
                                waynum--;
                            }
                        }
                    }


                  //  int jlnum = 0;
                 //   for (int i = JL.front; i < JL.rear; i = (i + 1) % JL.mSize) {
                 //       jlnum = jlnum + 1;
                 //   }

                    //选时间最早的飞机
                    while (1) {



                        Plane qft;
                        Plane jlt;
                        //有起飞 无降落
                        if (!QF.isEmpty() && JL.isEmpty()) {
                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 3; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag == 1) {
                                Plane fj;
                                QF.deQueue(fj);
                                ALLNum--;
                                cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;

                                sprintf(QFinfo, " %s\r\n%s在第%d道上起飞", QFinfo, fj.PName,n+1);
                                m_edit2.SetSel(0, -1);
                                m_edit2.ReplaceSel(QFinfo);
                            }
                            else
                                break;
                        }
                        //无起飞 有降落
                        else if (QF.isEmpty() && !JL.isEmpty()) {
                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 2; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }

                            }
                            if (flag == 1) {
                                Plane fj;
                                JL.deQueue(fj);
                                ALLNum--;
                                jlnum--;
                                cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                cout << "油量为" << fj.PFuel << endl;
                                sprintf(info, " %s\r\n%s降落在第%d道,油量为%d", info, fj.PName, n + 1, fj.PFuel);
                                m_edit3.SetSel(0, -1);
                                m_edit3.ReplaceSel(info);
                            }
                            else
                                break;

                        }
                        //有起飞 有降落
                        else if (!QF.isEmpty() && !JL.isEmpty()) {
                            //降落的飞机数量大于设定值时降落优先
                            if (jlnum > 5) {
                                for (int m = JL.front; m < JL.rear - 1; m = (m + 1) % JL.mSize) {
                                    for (int n = m; n < JL.rear; n = (n + 1) % JL.mSize) {
                                        if (JL.p[m].PFuel > JL.p[n].PFuel) {
                                            Plane tmp;
                                            tmp = JL.p[m];
                                            JL.p[m] = JL.p[n];
                                            JL.p[n] = tmp;
                                        }
                                    }
                                }
                                //油少的飞机优先降落
                                if (!JL.isEmpty()) {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        jlnum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                        sprintf(info, " %s\r\n%s降落在第%d道,油量为%d", info, fj.PName,n + 1, fj.PFuel);
                                        m_edit3.SetSel(0, -1);
                                        m_edit3.ReplaceSel(info);
                                    }
                                    else
                                        break;
                                }
                                //降落飞机降落后开始起飞
                                else if (!QF.isEmpty()) {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                        sprintf(QFinfo, " %s\r\n%s在第%d道上起飞", QFinfo, fj.PName, n + 1);
                                        m_edit2.SetSel(0, -1);
                                        m_edit2.ReplaceSel(QFinfo);
                                    }
                                    else
                                        break;
                                }

                            }
                            //降落的飞机数没有达到设定值时    按时间进行
                            else {
                                Plane qft, jlt;
                                QF.getFront(qft);
                                JL.getFront(jlt);
                                //比较起飞时间和降落时间

                                if ((qft.PQHtime < jlt.PAHtime) || ((qft.PQHtime = jlt.PAHtime) && (qft.PQMtime < jlt.PAMtime)))
                                {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                        sprintf(QFinfo, " %s\r\n%s在第%d道上起飞", QFinfo, fj.PName, n + 1);
                                        m_edit2.SetSel(0, -1);
                                        m_edit2.ReplaceSel(QFinfo);
                                    }
                                    else
                                        break;
                                }
                                //按时间顺序无起飞飞机
                                else {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        jlnum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                        sprintf(info, " %s\r\n%s降落在第%d道上，油量为：%d", info, fj.PName, n + 1,fj.PFuel);
                                        m_edit3.SetSel(0, -1);
                                        m_edit3.ReplaceSel(info);
                                    }
                                    else
                                        break;
                                }
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
                //无紧急
                else {
              //  int jlnum = 0;
              //  for (int i = JL.front; i < JL.rear; i = (i + 1) % JL.mSize) {
              //      jlnum = jlnum + 1;
             //   }
                    while (1) {
                        Plane qft;
                        Plane jlt;
                        //有起飞 无降落
                        if (!QF.isEmpty() && JL.isEmpty()) {
                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 3; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag == 1) {
                                Plane fj;
                                QF.deQueue(fj);
                                ALLNum--;
                                cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                sprintf(QFinfo, " %s\r\n%s在第%d道上起飞", QFinfo, fj.PName, n + 1);
                                m_edit2.SetSel(0, -1);
                                m_edit2.ReplaceSel(QFinfo);
                            }
                            else
                                break;
                        }
                        //无起飞 有降落
                        else if (QF.isEmpty() && !JL.isEmpty()) {

                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 2; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }

                            }
                            if (flag == 1) {
                                Plane fj;
                                JL.deQueue(fj);
                                ALLNum--;
                                jlnum--;
                                cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                cout << "油量为" << fj.PFuel << endl;
                                sprintf(info, " %s\r\n%s降落在第%d道上，油量为：%d", info, fj.PName, n + 1, fj.PFuel);
                                m_edit3.SetSel(0, -1);
                                m_edit3.ReplaceSel(info);
                            }
                            else
                                break;

                        }
                        else if (!QF.isEmpty() && !JL.isEmpty()) {//有起飞 有降落
                           // int jlnum = 0;

                            if (jlnum > 5) {
                                for (int m = JL.front; m < JL.rear - 1; m = (m + 1) % JL.mSize) {
                                    for (int n = m; n < JL.rear; n = (n + 1) % JL.mSize) {
                                        if (JL.p[m].PFuel > JL.p[n].PFuel) {
                                            Plane tmp;
                                            tmp = JL.p[m];
                                            JL.p[m] = JL.p[n];
                                            JL.p[n] = tmp;
                                        }
                                    }
                                }

                                if (!JL.isEmpty()) {//优先降落
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        jlnum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                        sprintf(info, " %s\r\n%s降落在第%d道上，油量为：%d", info, fj.PName, n + 1, fj.PFuel);
                                        m_edit3.SetSel(0, -1);
                                        m_edit3.ReplaceSel(info);
                                    }
                                    else
                                        break;
                                }
                                else if (!QF.isEmpty()) {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                        sprintf(QFinfo, " %s\r\n%s在第%d道上起飞", QFinfo, fj.PName, n + 1);
                                        m_edit2.SetSel(0, -1);
                                        m_edit2.ReplaceSel(QFinfo);
                                    }
                                    else
                                        break;
                                }

                            }
                            else {
                                Plane qft, jlt;
                                QF.getFront(qft);
                                JL.getFront(jlt);
                                if ((qft.PQHtime < jlt.PAHtime) || ((qft.PQHtime = jlt.PAHtime) && (qft.PQMtime < jlt.PAMtime)))
                                {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                        sprintf(QFinfo, " %s\r\n%s在第%d道上起飞", QFinfo, fj.PName, n + 1);
                                        m_edit2.SetSel(0, -1);
                                        m_edit2.ReplaceSel(QFinfo);
                                    }
                                    else
                                        break;
                                }
                                else {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        jlnum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                        sprintf(info, " %s\r\n%s降落在第%d道上，油量为：%d", info, fj.PName, n + 1,fj.PFuel );
                                        m_edit3.SetSel(0, -1);
                                        m_edit3.ReplaceSel(info);
                                    }
                                    else
                                        break;
                                }
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
                NMinute = NMinute + 15;
                if (NMinute == 60) {
                    NHour++;
                    NMinute = 0;
                    if (NHour == 24) {
                        NHour = 0;
                    }
                }
                char op[400];
                 sprintf(op, " %d:%d",NHour,NMinute );
                 m_edit4.SetSel(0, -1);
                 m_edit4.ReplaceSel(op);
                 Sleep(1000);
                  int k = JL.front;
                  int w = JL.rear;
                  for (int n = JL.front; n < JL.rear; n++) {
                      JL.p[n].everyTime();
                  }
                  continue;
              }
              NMinute = NMinute + 15;
              if (NMinute == 60) {
                  NHour++;
                  NMinute = 0;
                  if (NHour == 24) {
                      NHour = 0;
                  }
              }
              char op[400];
              sprintf(op, " %d:%d", NHour, NMinute);
              m_edit4.SetSel(0, -1);
              m_edit4.ReplaceSel(op);
              // srand((unsigned)time(NULL));
              Sleep(1000);
              for (int n = JL.front; n < JL.rear; n = (n + 1) % JL.mSize) {
                  JL.p[n].everyTime();
              }  
              if (NHour == 12) {
              break;
              }
          }
        
         
      }









void CkesheMFCDlg::OnBnClickedButton3()
 {
          // TODO: 在此添加控件通知处理程序代码
    exit(0);
 }

