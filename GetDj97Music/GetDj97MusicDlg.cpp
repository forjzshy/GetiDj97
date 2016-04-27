
// GetDj97MusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GetDj97Music.h"
#include "GetDj97MusicDlg.h"
#include "afxdialogex.h"
#include "Http.h"
#include "deelx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGetDj97MusicDlg 对话框



CGetDj97MusicDlg::CGetDj97MusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GETDJ97MUSIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetDj97MusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGetDj97MusicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGetDj97MusicDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetDj97MusicDlg 消息处理程序

BOOL CGetDj97MusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetDj97MusicDlg::OnPaint()
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
HCURSOR CGetDj97MusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGetDj97MusicDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CHttp * pHttp = new CHttp;
	int nLast = 0;
	int nRight = 0;
	CString strMusicListenAddr = _T("");
	GetDlgItemText(IDC_EDIT_LISTEN, strMusicListenAddr);

	//获取网页源代码
	CString strRead = pHttp->GetHTML(strMusicListenAddr, "", "");

	//获取收录于哪个专辑
	int nFindResult = strRead.Find(_T("收录于"));
	CString strMusicAlbum = strRead.Mid(nFindResult + 6, 8);
	
	//获取音乐名称
	nLast = strRead.Find(_T("name: '"));
	nRight = strRead.Find(_T("', file"));
	CString strMusicName = strRead.Mid(nLast + 7, nRight - nLast - 7);
	SetDlgItemText(IDC_STATIC_MUSICNAME, strMusicName);

	//获取音乐上传时间
	nLast = strRead.Find(_T("myxc/"));
	nRight = strRead.Find(_T("/"), nLast + 5);
	CString strMusicUploadTime = strRead.Mid(nLast + 5, nRight - nLast - 5);

	//获取音乐码率
	nLast = strRead.Find(_T("MP3音质："));
	nRight = strRead.Find(_T("，舞曲时长为"), nLast);
	CString strMusicRate = strRead.Mid(nLast + 9, nRight - nLast - 9);
	SetDlgItemText(IDC_STATIC_MUSICRATE, strMusicRate);

	//获取音乐大小
	nLast = strRead.Find(_T("大小为"));
	nRight = strRead.Find(_T("M，M"), nLast);
	CString strMusicSize = strRead.Mid(nLast + 6, nRight - nLast - 5);
	SetDlgItemText(IDC_STATIC_MUSICSIZE, strMusicSize);

	//生成高音质链接
	CString strMusicMp3Addr = _T("http://downmp3.oscaches.com/");
	strMusicMp3Addr += strMusicAlbum + _T("/") + strMusicUploadTime + _T("/") + strMusicName + _T(".mp3");

	SetDlgItemText(IDC_EDIT_LISTEN_DOWNLOADADDR, strMusicMp3Addr);

	delete pHttp;
	pHttp = NULL;
}
