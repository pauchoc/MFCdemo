
// MainDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "MFCdemo.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)						//����� ���������, ��������� ������� ������� � ���������� ����������
END_MESSAGE_MAP()


// ���������� ���� CMainDlg



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCDEMO_DIALOG, pParent)
	, ms_filein(_T(""))
	, ms_fileout(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEIN, ms_filein);
	DDX_Text(pDX, IDC_EDIT_FILEOUT, ms_fileout);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)								//����� ���������, ��������� ������� ������� � ���������� ����������
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_GETFILEIN, &CMainDlg::OnGetfilein)
	ON_BN_CLICKED(IDC_BUTTON_PUTFILEOUT, &CMainDlg::OnPutfileout)
	//ON_EN_CHANGE(IDC_EDIT_FILEOUT, &CMainDlg::OnEnChangeEditFileout)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &CMainDlg::OnProcess)
END_MESSAGE_MAP()


// ����������� ��������� CMainDlg

BOOL CMainDlg::OnInitDialog() //������� ������������� �������. ���������� ����� �������� �������, �� �� ��� ����������� �� ������
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	ms_filein = "input.txt";
	ms_fileout = "output.txt";
	UpdateData(FALSE);						//���������� ��� ���������� ���������� � ���� ����������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
void CMainDlg::OnBnClickedButton1()
{
	// TODO: �������� ���� ��� ����������� �����������
	UpdateData(TRUE);				//�� ���� ��������� ���������� ������ ����������� � ��������� ����������

	CString sMsg;
	sMsg = "������������ ���� =";
	sMsg =sMsg + ms_filein;

	MessageBox(sMsg, L"Message", MB_YESNO | MB_ICONQUESTION);
}
*/

void CMainDlg::OnGetfilein()
{
	CFileDialog dlg(TRUE);				//TRUE-������ �������� �����, FALSE-������ ���������� �����
	if (dlg.DoModal() == IDOK)			//dlg.DoModal();  ����������� ������� � ��������� ������
	{
		ms_filein = dlg.m_ofn.lpstrFile;
		UpdateData(FALSE);
	}

}


void CMainDlg::OnPutfileout()
{
	CFileDialog dlg(FALSE);				//TRUE-������ �������� �����, FALSE-������ ���������� �����
	if (dlg.DoModal() == IDOK)			//dlg.DoModal();  ����������� ������� � ��������� ������
	{
		ms_fileout = dlg.m_ofn.lpstrFile;
		UpdateData(FALSE);
	}
	
}

void CMainDlg::OnProcess()
{
	UpdateData(FALSE);
	if (ProcessFiles(ms_filein,ms_fileout)!=TRUE)
	{
		MessageBox(L"��������� ����������� � �������", L"������", MB_OK | MB_ICONERROR);
	}
	else 
	{
		MessageBox(L"����� ���������� �������", L"����������", MB_OK | MB_ICONINFORMATION);
	}
}


BOOL CMainDlg::ProcessFiles(CString sFileIn, CString sFileOut)
{
	CFile FileIn;
	if (!FileIn.Open(sFileIn,CFile::modeRead))
	{
		CString sMsg;
		sMsg.Format(L"Can't open file %s", sFileIn);
		MessageBox(sMsg,L"Error",MB_OK|MB_ICONERROR);
		return FALSE;
	}

	CFile FileOut;
	if (!FileOut.Open(sFileOut, CFile::modeWrite|CFile::modeCreate))
	{
		CString sMsg;
		sMsg.Format(L"Can't open file %s", sFileOut);
		MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	int a;
	FileIn.Read(&a, sizeof(int));
	FileOut.Write(&a, sizeof(int));
	return TRUE	;
}
