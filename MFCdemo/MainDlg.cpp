
// MainDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "MFCdemo.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)						//Карта сообщений, позволяет связать функции с элементами управления
END_MESSAGE_MAP()


// диалоговое окно CMainDlg



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

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)								//Карта сообщений, позволяет связать функции с элементами управления
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_GETFILEIN, &CMainDlg::OnGetfilein)
	ON_BN_CLICKED(IDC_BUTTON_PUTFILEOUT, &CMainDlg::OnPutfileout)
	//ON_EN_CHANGE(IDC_EDIT_FILEOUT, &CMainDlg::OnEnChangeEditFileout)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &CMainDlg::OnProcess)
END_MESSAGE_MAP()


// обработчики сообщений CMainDlg

BOOL CMainDlg::OnInitDialog() //Функция инициализации диалога. Вызывается после создания диалога, но до его отображения на экране
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	ms_filein = "input.txt";
	ms_fileout = "output.txt";
	UpdateData(FALSE);						//необходимо для обновления переменных в окне управления

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
void CMainDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);				//из всех элементов управления данные обновляются в связанных переменных

	CString sMsg;
	sMsg = "Пользователь ввел =";
	sMsg =sMsg + ms_filein;

	MessageBox(sMsg, L"Message", MB_YESNO | MB_ICONQUESTION);
}
*/

void CMainDlg::OnGetfilein()
{
	CFileDialog dlg(TRUE);				//TRUE-диалог открытия файла, FALSE-диалог сохранения файла
	if (dlg.DoModal() == IDOK)			//dlg.DoModal();  отображение диалога в модальном режиме
	{
		ms_filein = dlg.m_ofn.lpstrFile;
		UpdateData(FALSE);
	}

}


void CMainDlg::OnPutfileout()
{
	CFileDialog dlg(FALSE);				//TRUE-диалог открытия файла, FALSE-диалог сохранения файла
	if (dlg.DoModal() == IDOK)			//dlg.DoModal();  отображение диалога в модальном режиме
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
		MessageBox(L"Обработка завершилась с ошибкой", L"Ошибка", MB_OK | MB_ICONERROR);
	}
	else 
	{
		MessageBox(L"Файлы обработаны успешно", L"Информация", MB_OK | MB_ICONINFORMATION);
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
