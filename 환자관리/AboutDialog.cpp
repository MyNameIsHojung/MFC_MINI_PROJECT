// AboutDialog.cpp: 구현 파일
//

#include "pch.h"
#include "환자관리.h"
#include "afxdialogex.h"
#include "AboutDialog.h"
#include "DBControl.h"
#include "SelectPatient.h"


enum MY_W_MSG
{
    MWM_ENDED_REG = WM_APP + 1,
    MWM_READ_P,
    MWM_IMG_LOAD
};

// AboutDialog 대화 상자

IMPLEMENT_DYNAMIC(AboutDialog, CDialogEx)

AboutDialog::AboutDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_ABOUT, pParent)
    , name(_T(""))
    , phone(_T(""))
    , birth(_T(""))
    , addr(_T(""))
    , p_id(_T(""))
    , date(COleDateTime::GetCurrentTime())
    , content(_T(""))
{

}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_IMG, pbox_img);
    DDX_Text(pDX, IDC_EDIT_NAME, name);
    DDX_Text(pDX, IDC_EDIT_PHONE, phone);
    DDX_Text(pDX, IDC_EDIT_BIRTH, birth);
    DDX_Text(pDX, IDC_EDIT_ADDR, addr);
    DDX_Text(pDX, IDC_EDIT_ID, p_id);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, date);
    DDX_LBString(pDX, IDC_LIST_CONTENT, content);
    DDX_Control(pDX, IDC_LIST_CONTENT, A_list_con);
    DDX_Control(pDX, IDC_DATETIMEPICKER1, date_con);
}


BEGIN_MESSAGE_MAP(AboutDialog, CDialogEx)
    ON_MESSAGE(MWM_IMG_LOAD, &AboutDialog::ReadDB)
END_MESSAGE_MAP()

BOOL AboutDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.
    PostMessage(MWM_IMG_LOAD, 0, 0);
    

    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

LRESULT AboutDialog::ReadDB(WPARAM, LPARAM)
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

    wchar_t query_str[256] = TEXT("");
    wchar_t birth_id[256] = TEXT("");
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

        wsprintf(birth_id, TEXT("%s-%s"), _birth, _id);
        SetDlgItemText(IDC_EDIT_NAME, _name);
        SetDlgItemText(IDC_EDIT_PHONE, _phone);
        SetDlgItemText(IDC_EDIT_BIRTH, _birth);
        SetDlgItemText(IDC_EDIT_ADDR, _addr);
        SetDlgItemText(IDC_EDIT_ID, birth_id);
        SetDlgItemText(IDC_DATETIMEPICKER1, _visit);
        COleDateTime dtDate;
        dtDate.ParseDateTime(_visit);
        date_con.SetTime(dtDate);
        A_list_con.InsertString(0, _disease);
        A_list_con.InsertString(-1, _symptom);

        CImage cimg;
        cimg.Load(_path);
        CDC* cdc = pbox_img.GetDC();
        RECT rt;
        pbox_img.GetClientRect(&rt);
        cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
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

        wsprintf(birth_id, TEXT("%s-%s"), _birth, _id);
        SetDlgItemText(IDC_EDIT_NAME, _name);
        SetDlgItemText(IDC_EDIT_PHONE, _phone);
        SetDlgItemText(IDC_EDIT_BIRTH, _birth);
        SetDlgItemText(IDC_EDIT_ADDR, _addr);
        SetDlgItemText(IDC_EDIT_ID, birth_id);
        SetDlgItemText(IDC_DATETIMEPICKER1, _visit);
        COleDateTime dtDate;
        dtDate.ParseDateTime(_visit);
        date_con.SetTime(dtDate);
        A_list_con.InsertString(0, _disease);
        A_list_con.InsertString(-1, _symptom);

        CImage cimg;
        CString path = TEXT("./noimg2.png");

        cimg.Load(path);
        CDC* cdc = pbox_img.GetDC();
        RECT rt;
        pbox_img.GetClientRect(&rt);
        cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
    }
    return 0;
}
