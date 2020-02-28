
// qgevilDlg.cpp : ʵ���ļ�
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


// CqgevilDlg �Ի���




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


// CqgevilDlg ��Ϣ�������

BOOL CqgevilDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CFont* cfont=new CFont();
	cfont->CreateFont(20,0, 0, 0, FW_NORMAL,FALSE, FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, _T("����"));
	GetDlgItem(IDC_STANAME)->SetFont(cfont);
	GetDlgItem(IDC_STAAFT)->SetFont(cfont);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CqgevilDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CqgevilDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CqgevilDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szFileName[MAX_PATH]="";
	OPENFILENAME file={0};
	file.lStructSize=sizeof(file);
	file.lpstrFile=szFileName;
	file.nMaxFile=MAX_PATH;
	file.lpstrFilter="Text Files(*.txt)\0*.txt\0All Files\0*.*\0\0";
	file.nFilterIndex=1;
	file.lpstrTitle="����";
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
				::MessageBox(NULL,"�ļ�����ɹ�","qgevil",MB_ICONINFORMATION);
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
				::MessageBox(NULL,"�ļ�����ɹ�","qgevil",MB_ICONINFORMATION);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::MessageBox(NULL,"Author:MNTMDEV\r\n����ѧϰʹ�ã�δ�����������ֹ������ҵ��;","qgevil",MB_ICONINFORMATION);
}
