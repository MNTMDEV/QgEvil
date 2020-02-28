
// qgevilDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "qgevil.h"
#include "qgevilDlg.h"
#include "afxdialogex.h"
#include <fstream>
using namespace std; 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CqgevilDlg 对话框




CqgevilDlg::CqgevilDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CqgevilDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CqgevilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CqgevilDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE, &CqgevilDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_COP, &CqgevilDlg::OnBnClickedCop)
END_MESSAGE_MAP()


// CqgevilDlg 消息处理程序

BOOL CqgevilDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CFont* cfont=new CFont();
	cfont->CreateFont(20,0, 0, 0, FW_NORMAL,FALSE, FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, _T("宋体"));
	GetDlgItem(IDC_STANAME)->SetFont(cfont);
	GetDlgItem(IDC_STAAFT)->SetFont(cfont);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CqgevilDlg::OnPaint()
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
HCURSOR CqgevilDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CqgevilDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFileName[MAX_PATH]="";
	OPENFILENAME file={0};
	file.lStructSize=sizeof(file);
	file.lpstrFile=szFileName;
	file.nMaxFile=MAX_PATH;
	file.lpstrFilter="Text Files(*.txt)\0*.txt\0All Files\0*.*\0\0";
	file.nFilterIndex=1;
	file.lpstrTitle="保存";
	WCHAR* UName,*UAft;
	CString Name;
	CString Aft;
	GetDlgItem(IDC_NAME)->GetWindowText(Name);
	GetDlgItem(IDC_AFT)->GetWindowText(Aft);
	int nName=MultiByteToWideChar(CP_ACP,0,Name,-1,NULL,0);
	int nAft=MultiByteToWideChar(CP_ACP,0,Aft,-1,NULL,0);
	UName=new WCHAR[nName];
	UAft=new WCHAR[nAft];
	MultiByteToWideChar(CP_ACP,0,Name,-1,UName,nName);
	MultiByteToWideChar(CP_ACP,0,Aft,-1,UAft,nAft);
	WCHAR* UAftA=new WCHAR[nAft];
	for(int i=0;i<nAft-1;i++)
	{
		UAftA[i]=UAft[nAft-i-2];
	}
	UAft[nAft-1]=0x0000;
	ofstream out;
	if(::GetSaveFileName(&file))
	{
		int curindex=file.nFilterIndex;
		CString strPath=szFileName;
		if(curindex==1)
		{
			try
			{
				int ind=strPath.ReverseFind('.');
				if(ind!=-1)
				{
					CString bot=strPath.Right(strPath.GetLength()-ind);
					if(bot!=".txt")
					{
						strPath+=".txt";
					}
				}
				else
				{
					strPath+=".txt";
				}
				out.open(strPath,std::ofstream::binary);
				char start[2]={0xFF,0xFE};
				char RLO[2]={0x2E,0x20};
				char LRO[2]={0x2D,0x20};
				out.write(start,sizeof(char[2]));
				out.write((const char*)UName,2*nName-2);
				out.write(RLO,sizeof(char[2]));
				out.write((const char*)UAftA,2*nAft-2);
				out.write(LRO,sizeof(char[2]));
				::MessageBox(NULL,"文件保存成功","qgevil",MB_ICONINFORMATION);
			}
			catch(...)
			{
				::MessageBox(NULL,"failed","",MB_ICONHAND);
				out.close();
				return;
			}
		}
		else
		{
			try
			{
				out.open(szFileName,std::ofstream::binary);
				char start[2]={0xFF,0xFE};
				char RLO[2]={0x2E,0x20};
				char LRO[2]={0x2D,0x20};
				out.write(start,sizeof(char[2]));
				out.write((const char*)UName,2*nName-2);
				out.write(RLO,sizeof(char[2]));
				out.write((const char*)UAftA,2*nAft-2);
				out.write(LRO,sizeof(char[2]));
				::MessageBox(NULL,"文件保存成功","qgevil",MB_ICONINFORMATION);
			}
			catch(...)
			{
				::MessageBox(NULL,"failed","",MB_ICONHAND);
				out.close();
				return;
			}
		}
		out.close();
	}
}


void CqgevilDlg::OnBnClickedCop()
{
	// TODO: 在此添加控件通知处理程序代码
	::MessageBox(NULL,"Author:MNTMDEV\r\n仅供学习使用，未经作者允许禁止用于商业用途","qgevil",MB_ICONINFORMATION);
}
