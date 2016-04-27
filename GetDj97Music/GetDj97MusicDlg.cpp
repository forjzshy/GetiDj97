
// GetDj97MusicDlg.cpp : ʵ���ļ�
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


// CGetDj97MusicDlg �Ի���



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


// CGetDj97MusicDlg ��Ϣ�������

BOOL CGetDj97MusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGetDj97MusicDlg::OnPaint()
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
HCURSOR CGetDj97MusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGetDj97MusicDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CHttp * pHttp = new CHttp;
	int nLast = 0;
	int nRight = 0;
	CString strMusicListenAddr = _T("");
	GetDlgItemText(IDC_EDIT_LISTEN, strMusicListenAddr);

	//��ȡ��ҳԴ����
	CString strRead = pHttp->GetHTML(strMusicListenAddr, "", "");

	//��ȡ��¼���ĸ�ר��
	int nFindResult = strRead.Find(_T("��¼��"));
	CString strMusicAlbum = strRead.Mid(nFindResult + 6, 8);
	
	//��ȡ��������
	nLast = strRead.Find(_T("name: '"));
	nRight = strRead.Find(_T("', file"));
	CString strMusicName = strRead.Mid(nLast + 7, nRight - nLast - 7);
	SetDlgItemText(IDC_STATIC_MUSICNAME, strMusicName);

	//��ȡ�����ϴ�ʱ��
	nLast = strRead.Find(_T("myxc/"));
	nRight = strRead.Find(_T("/"), nLast + 5);
	CString strMusicUploadTime = strRead.Mid(nLast + 5, nRight - nLast - 5);

	//��ȡ��������
	nLast = strRead.Find(_T("MP3���ʣ�"));
	nRight = strRead.Find(_T("������ʱ��Ϊ"), nLast);
	CString strMusicRate = strRead.Mid(nLast + 9, nRight - nLast - 9);
	SetDlgItemText(IDC_STATIC_MUSICRATE, strMusicRate);

	//��ȡ���ִ�С
	nLast = strRead.Find(_T("��СΪ"));
	nRight = strRead.Find(_T("M��M"), nLast);
	CString strMusicSize = strRead.Mid(nLast + 6, nRight - nLast - 5);
	SetDlgItemText(IDC_STATIC_MUSICSIZE, strMusicSize);

	//���ɸ���������
	CString strMusicMp3Addr = _T("http://downmp3.oscaches.com/");
	strMusicMp3Addr += strMusicAlbum + _T("/") + strMusicUploadTime + _T("/") + strMusicName + _T(".mp3");

	SetDlgItemText(IDC_EDIT_LISTEN_DOWNLOADADDR, strMusicMp3Addr);

	delete pHttp;
	pHttp = NULL;
}
