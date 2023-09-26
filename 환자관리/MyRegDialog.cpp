// MyRegDialog.cpp: 구현 파일
//

#include "pch.h"
#include "환자관리.h"
#include "afxdialogex.h"
#include "MyRegDialog.h"
#include "DBControl.h"


// MyRegDialog 대화 상자

IMPLEMENT_DYNAMIC(MyRegDialog, CDialogEx)

MyRegDialog::MyRegDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, name(_T(""))
	, phone(_T(""))
	, birth(_T(""))
	, addr(_T(""))
	, p_id(_T(""))
	, content(_T(""))
	, content_ex(_T(""))
	, date1(COleDateTime::GetCurrentTime())
	, date2(COleDateTime::GetCurrentTime())
{
}

MyRegDialog::~MyRegDialog()
{
}

void MyRegDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, name);
	DDX_Text(pDX, IDC_EDIT_PHONE, phone);
	DDX_Text(pDX, IDC_EDIT_BIRTH, birth);
	DDX_Text(pDX, IDC_EDIT_ADDR, addr);
	DDX_Text(pDX, IDC_EDIT_ID, p_id);
	DDX_Text(pDX, IDC_EDIT_CONTENT, content);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, date1);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, date2);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, dtp);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, mc);
	DDX_Text(pDX, IDC_EDIT_CONTENT_EX, content_ex);
	DDX_Control(pDX, IDC_STATIC_IMG, pic_img);
}


BEGIN_MESSAGE_MAP(MyRegDialog, CDialogEx)
	ON_STN_DBLCLK(IDC_STATIC_IMG, &MyRegDialog::OnStnDblclickStaticImg)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &MyRegDialog::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &MyRegDialog::OnMcnSelchangeMonthcalendar1)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &MyRegDialog::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &MyRegDialog::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// MyRegDialog 메시지 처리기
void MyRegDialog::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (eeh)
	{
		eeh->EndedDialog_add();//나 죽음을 통보한다.
	}
	CDialogEx::OnCancel();
}


void MyRegDialog::OnStnDblclickStaticImg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* fod = new CFileDialog(TRUE, 0);
	int re = fod->DoModal();
	if (re != IDOK)
	{
		return;
	}
	image = fod->GetPathName();
	CImage cimg;
	cimg.Load(image);

	CDC* cdc = pic_img.GetDC();
	RECT rt;
	pic_img.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}

void MyRegDialog::InitControls()
{
	name = TEXT("");
	phone = TEXT("");
	birth = TEXT("");
	addr = TEXT("");
	p_id = TEXT("");
	content = TEXT("");
	content_ex = TEXT("");
	image = TEXT("");
	UpdateData(FALSE);
	
}

BOOL MyRegDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MyRegDialog::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	*pResult = 0;
	UpdateData();
	mc.SetCurSel(date1);	
}


void MyRegDialog::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData();
	dtp.SetTime(date2);
}

void MyRegDialog::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	try
	{
		DBControl* dbc = DBControl::GetInstance();
		wchar_t query_add[512];
		CString _name;
		CString _phone;
		CString _birth;
		CString _addr;
		CString _id;
		CString _visit;
		CString _disease;
		
		GetDlgItemText(IDC_EDIT_NAME, _name);
		GetDlgItemText(IDC_EDIT_PHONE, _phone);
		GetDlgItemText(IDC_EDIT_BIRTH, _birth);
		GetDlgItemText(IDC_EDIT_ADDR, _addr);
		GetDlgItemText(IDC_EDIT_ID, _id);
		GetDlgItemText(IDC_DATETIMEPICKER1, _visit);
		GetDlgItemText(IDC_EDIT_CONTENT, _disease);
		if (_name == TEXT("")||_phone == TEXT("")||birth == TEXT("")||_addr == TEXT("") || _id == TEXT("") || _visit == TEXT("") || _disease == TEXT(""))
		{			
			throw MessageBox(TEXT("입력된 정보 확인"), TEXT("경고"));
		}
		wchar_t query_str_add[256];
		wsprintf(query_str_add, TEXT("insert into patient(pname,phone,birth,addr,id,visit,disease) values('%s','%s','%s','%s','%s','%s','%s')"), _name, _phone, _birth, _addr, _id, _visit, _disease);
		dbc->ExecuteQuery(query_str_add);
		wchar_t query_str_add_path[256];
		wsprintf(query_str_add_path, TEXT("insert into img_path(pid,[path]) values((select patient.pid from patient where patient.id = '%s'),'%s')"), _id, image);
		dbc->ExecuteQuery(query_str_add_path);

		InitControls();
		OnCancel();
	}
	catch (int exception)
	{
		MessageBox(TEXT("확인 후 재입력 바람"), TEXT("경고"));
	}	
}

void MyRegDialog::AddEndedEventHandler(EndDialogEventHandler* eeh)
{
	this->eeh = eeh;
}

void MyRegDialog::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InitControls();
}
