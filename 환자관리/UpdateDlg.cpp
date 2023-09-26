// UpdateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "환자관리.h"
#include "afxdialogex.h"
#include "UpdateDlg.h"
#include "DBControl.h"
#include "SelectPatient.h"

// UpdateDlg 대화 상자

IMPLEMENT_DYNAMIC(UpdateDlg, CDialogEx)
enum MY_W_MSG
{
    MWM_ENDED_REG = WM_APP + 1,
    MWM_READ_P,
    MWM_IMG_LOAD,
    MWM_UPDATE_CONTENT
};
UpdateDlg::UpdateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE, pParent)
	, update_edit_name_val(_T(""))
	, update_edit_phone_val(_T(""))
	, update_edit_birth_val(_T(""))
	, update_edit_addr_val(_T(""))
	, update_edit_id_val(_T(""))
	, update_edit_dp_val(COleDateTime::GetCurrentTime())
	, update_edit_content_val(_T(""))
	, update_edit_content_ex_val(_T(""))
    , update_mc_val(COleDateTime::GetCurrentTime())
{

}

UpdateDlg::~UpdateDlg()
{
}

void UpdateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_NAME, update_edit_name_con);
    DDX_Control(pDX, IDC_EDIT_PHONE, update_edit_phone_con);
    DDX_Control(pDX, IDC_EDIT_BIRTH, update_edit_birth_con);
    DDX_Control(pDX, IDC_EDIT_ID, update_edit_id_con);
    DDX_Control(pDX, IDC_DATETIMEPICKER1, update_edit_dp_con);
    DDX_Text(pDX, IDC_EDIT_NAME, update_edit_name_val);
    DDX_Text(pDX, IDC_EDIT_PHONE, update_edit_phone_val);
    DDX_Text(pDX, IDC_EDIT_BIRTH, update_edit_birth_val);
    DDX_Control(pDX, IDC_EDIT_ADDR, update_edit_addr_con);
    DDX_Text(pDX, IDC_EDIT_ADDR, update_edit_addr_val);
    DDX_Text(pDX, IDC_EDIT_ID, update_edit_id_val);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, update_edit_dp_val);
    DDX_Control(pDX, IDC_STATIC_IMG, update_img_con);
    DDX_Control(pDX, IDC_EDIT_CONTENT, update_edit_content_con);
    DDX_Text(pDX, IDC_EDIT_CONTENT, update_edit_content_val);
    DDX_Text(pDX, IDC_EDIT_CONTENT_EX, update_edit_content_ex_val);
    DDX_Control(pDX, IDC_EDIT_CONTENT_EX, update_edit_content_ex_con);
    DDX_Control(pDX, IDC_MONTHCALENDAR1, update_mc_con);
    DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, update_mc_val);
}


BEGIN_MESSAGE_MAP(UpdateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &UpdateDlg::OnBnClickedButtonUpdate)
    ON_MESSAGE(MWM_UPDATE_CONTENT,&UpdateDlg::ReadDB)
    ON_STN_DBLCLK(IDC_STATIC_IMG, &UpdateDlg::OnStnDblclickStaticImg)
    ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &UpdateDlg::OnMcnSelchangeMonthcalendar1)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &UpdateDlg::OnDtnDatetimechangeDatetimepicker1)
    ON_STN_CLICKED(IDC_STATIC_IMG, &UpdateDlg::OnStnClickedStaticImg)
    ON_BN_CLICKED(IDC_BUTTON1, &UpdateDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON_CANCEL, &UpdateDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// UpdateDlg 메시지 처리기


BOOL UpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
    PostMessage(MWM_UPDATE_CONTENT, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void UpdateDlg::OnBnClickedButtonUpdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    DBControl* dbc = DBControl::GetInstance();
    SelectPatient* spt = SelectPatient::GetInstance();
    CString pid = spt->GetPid();
    if (image == "")
    {
        image = temp_image;
    }
    wchar_t query_str_update_path[256] = TEXT("");
    wsprintf(query_str_update_path, TEXT("update img_path set[path] = '%s' where img_path.pid = '%s'"), image, pid);
    dbc->ExecuteQuery(query_str_update_path);
    CString _name;
    CString _phone;
    CString _addr;
    CString _id;
    CString _visit;
    CString _disease;

    GetDlgItemText(IDC_EDIT_NAME, _name);
    GetDlgItemText(IDC_EDIT_PHONE, _phone);
    GetDlgItemText(IDC_EDIT_ADDR, _addr);
    GetDlgItemText(IDC_EDIT_ID, _id);
    GetDlgItemText(IDC_DATETIMEPICKER1, _visit);
    GetDlgItemText(IDC_EDIT_CONTENT, _disease);

    wchar_t query_str_update_data[256] = TEXT("");
    wsprintf(query_str_update_data, TEXT("update patient set pname = '%s',phone = '%s', addr='%s', id = '%s', visit = '%s', disease = '%s' where patient.pid = '%s'"), _name, _phone,_addr, _id, _visit, _disease,pid);
    dbc->ExecuteQuery(query_str_update_data);

    OnCancel();
}


LRESULT UpdateDlg::ReadDB(WPARAM, LPARAM)
{
    SelectPatient* spt = SelectPatient::GetInstance();
    CString pid = spt->GetPid();

    CString _name;
    CString _phone;
    CString _birth;
    CString _addr;
    CString _id;
    CString _visit;
    CString _disease;
    CString _symptom;
    CString _path;

    wchar_t query_str[512] = TEXT("");
    try
    {
        DBControl* dbc = DBControl::GetInstance();
        CRecordset* rs = dbc->Select();

        wsprintf(query_str, TEXT("select patient.pname, patient.phone, patient.birth, patient.addr, patient.id, patient.visit, patient.disease, disease.symptom,img_path.path  from patient, disease,img_path where patient.pid='%s' and img_path.pid='%s' and  patient.disease =  disease.disease"), pid, pid);
        rs->Open(CRecordset::forwardOnly, query_str);

        rs->GetFieldValue((short)0, _name);
        rs->GetFieldValue((short)1, _phone);
        rs->GetFieldValue((short)2, _birth);
        rs->GetFieldValue((short)3, _addr);
        rs->GetFieldValue((short)4, _id);
        rs->GetFieldValue((short)5, _visit);
        rs->GetFieldValue((short)6, _disease);
        rs->GetFieldValue((short)7, _symptom);
        rs->GetFieldValue((short)8, _path);

        SetDlgItemText(IDC_EDIT_NAME, _name);
        SetDlgItemText(IDC_EDIT_PHONE, _phone);
        SetDlgItemText(IDC_EDIT_BIRTH, _birth);
        SetDlgItemText(IDC_EDIT_ADDR, _addr);
        SetDlgItemText(IDC_EDIT_ID, _id);
        SetDlgItemText(IDC_DATETIMEPICKER1, _visit);
        COleDateTime dtDate;
        dtDate.ParseDateTime(_visit);
        update_edit_dp_con.SetTime(dtDate);
        SetDlgItemText(IDC_EDIT_CONTENT, _disease);
        SetDlgItemText(IDC_EDIT_CONTENT_EX, _symptom);

        CImage cimg;
        cimg.Load(_path);
        CDC* cdc = update_img_con.GetDC();
        RECT rt;
        update_img_con.GetClientRect(&rt);
        cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
        UpdateData();
        update_mc_con.SetCurSel(update_edit_dp_val);
        temp_image = _path;
        temp_name = _name;
        temp_phone = _phone;
        temp_birth = _birth;
        temp_addr = _addr;
        temp_id = _id;
        temp_visit = _visit;
        temp_disease = _disease;
        temp_symptom = _symptom;
        temp_path = _path;
}
    catch (...)
    {
        DBControl* dbc = DBControl::GetInstance();
        CRecordset* rs = dbc->Select();

        wsprintf(query_str, TEXT("select patient.pname, patient.phone, patient.birth, patient.addr, patient.id, patient.visit, patient.disease, disease.symptom from patient, disease where patient.pid='%s' and  patient.disease =  disease.disease"), pid);
        rs->Open(CRecordset::forwardOnly, query_str);

        rs->GetFieldValue((short)0, _name);
        rs->GetFieldValue((short)1, _phone);
        rs->GetFieldValue((short)2, _birth);
        rs->GetFieldValue((short)3, _addr);
        rs->GetFieldValue((short)4, _id);
        rs->GetFieldValue((short)5, _visit);
        rs->GetFieldValue((short)6, _disease);
        rs->GetFieldValue((short)7, _symptom);

        SetDlgItemText(IDC_EDIT_NAME, _name);
        SetDlgItemText(IDC_EDIT_PHONE, _phone);
        SetDlgItemText(IDC_EDIT_BIRTH, _birth);
        SetDlgItemText(IDC_EDIT_ADDR, _addr);
        SetDlgItemText(IDC_EDIT_ID, _id);
        SetDlgItemText(IDC_DATETIMEPICKER1, _visit);
        COleDateTime dtDate;
        dtDate.ParseDateTime(_visit);
        update_edit_dp_con.SetTime(dtDate);
        SetDlgItemText(IDC_EDIT_CONTENT, _disease);
        SetDlgItemText(IDC_EDIT_CONTENT_EX, _symptom);

        CImage cimg;
        CString path = TEXT("./noimg2.png");

        cimg.Load(path);
        CDC* cdc = update_img_con.GetDC();
        RECT rt;
        update_img_con.GetClientRect(&rt);
        cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
        UpdateData();
        update_mc_con.SetCurSel(update_edit_dp_val);
        temp_image = path;
        temp_name = _name;
        temp_phone = _phone;
        temp_birth = _birth;
        temp_addr = _addr;
        temp_id = _id;
        temp_visit = _visit;
        temp_disease = _disease;
        temp_symptom = _symptom;
        temp_path = _path;
    }
    return 0;
}

void UpdateDlg::OnStnDblclickStaticImg()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString image;
    CFileDialog* fod = new CFileDialog(TRUE, 0);
    int re = fod->DoModal();
    if (re != IDOK)
    {
        return;
    }
    image = fod->GetPathName();
    CImage cimg;
    cimg.Load(image);

    CDC* cdc = update_img_con.GetDC();
    RECT rt;
    update_img_con.GetClientRect(&rt);
    cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}


void UpdateDlg::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
    UpdateData();
    update_edit_dp_con.SetTime(update_mc_val);
    
}


void UpdateDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    *pResult = 0;
    UpdateData();    
    update_mc_con.SetCurSel(update_edit_dp_val);
}


void UpdateDlg::OnStnClickedStaticImg()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString image;
    CFileDialog* fod = new CFileDialog(TRUE, 0);
    int re = fod->DoModal();
    if (re != IDOK)
    {
        return;
    }
    image = fod->GetPathName();
    CImage cimg;
    cimg.Load(image);

    CDC* cdc = update_img_con.GetDC();
    RECT rt;
    update_img_con.GetClientRect(&rt);
    cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}


void UpdateDlg::OnBnClickedButton1()
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
    CDC* cdc = update_img_con.GetDC();
    RECT rt;
    update_img_con.GetClientRect(&rt);
    cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}

void UpdateDlg::AddEndedEventHandler(EndDialogEventHandler* eeh)
{
    this->eeh = eeh;
}

void UpdateDlg::OnCancel()
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    if (eeh)
    {
        eeh->EndedDialog();//나 죽음을 통보한다.
    }

    temp_image = TEXT("");
    temp_name = TEXT("");
    temp_phone = TEXT("");
    temp_birth = TEXT("");
    temp_addr = TEXT("");
    temp_id = TEXT("");
    temp_visit = TEXT("");
    temp_disease = TEXT("");
    temp_symptom = TEXT("");
    temp_path = TEXT("");

    CDialogEx::OnCancel();
}


void UpdateDlg::OnBnClickedButtonCancel()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    SetDlgItemText(IDC_EDIT_NAME, temp_name);
    SetDlgItemText(IDC_EDIT_PHONE, temp_phone);
    SetDlgItemText(IDC_EDIT_BIRTH, temp_birth);
    SetDlgItemText(IDC_EDIT_ADDR, temp_addr);
    SetDlgItemText(IDC_EDIT_ID, temp_id);
    SetDlgItemText(IDC_DATETIMEPICKER1, temp_visit);
    COleDateTime dtDate;
    dtDate.ParseDateTime(temp_visit);
    update_edit_dp_con.SetTime(dtDate);
    SetDlgItemText(IDC_EDIT_CONTENT, temp_disease);
    SetDlgItemText(IDC_EDIT_CONTENT_EX, temp_symptom);
    UpdateData();
    update_edit_dp_con.SetTime(update_mc_val);

}
