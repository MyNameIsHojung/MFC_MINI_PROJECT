#pragma once
#include "afxdialogex.h"

#include "Patient.h"
// AboutDialog 대화 상자

class AboutDialog : public CDialogEx
{
	DECLARE_DYNAMIC(AboutDialog)

public:
	AboutDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AboutDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ABOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// void AddedPatient(Patient* p);
	// void AddedPatient(Patient* p);
	CStatic pbox_img;
	CString name;
	CString phone;
	CString birth;
	CString addr;
	CString p_id;
	COleDateTime date;
	CString content;
	virtual BOOL OnInitDialog();
	CListBox A_list_con;
	CDateTimeCtrl date_con;
	afx_msg LRESULT ReadDB(WPARAM, LPARAM);

};