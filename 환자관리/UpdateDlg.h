#pragma once
#include "afxdialogex.h"
#include "EndDialogEventHandler.h"


// UpdateDlg 대화 상자

class UpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateDlg)
	EndDialogEventHandler* eeh;

public:
	UpdateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UpdateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit update_edit_name_con;
	CEdit update_edit_phone_con;
	CEdit update_edit_birth_con;
	CEdit update_edit_id_con;
	CDateTimeCtrl update_edit_dp_con;
	CString update_edit_name_val;
	CString update_edit_phone_val;
	CString update_edit_birth_val;
	CEdit update_edit_addr_con;
	CString update_edit_addr_val;
	CString update_edit_id_val;
	COleDateTime update_edit_dp_val;
	CStatic update_img_con;
	CEdit update_edit_content_con;
	CString update_edit_content_val;
	CString update_edit_content_ex_val;
	CEdit update_edit_content_ex_con;
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg LRESULT ReadDB(WPARAM, LPARAM);
	CMonthCalCtrl update_mc_con;
	afx_msg void OnStnDblclickStaticImg();
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	COleDateTime update_mc_val;
	afx_msg void OnStnClickedStaticImg();
	afx_msg void OnBnClickedButton1();
	CStatic img_con;
	CString image;
	CString temp_image;
	CString temp_name;
	CString temp_phone;
	CString temp_birth;
	CString temp_addr;
	CString temp_id2;
	CString temp_id;
	CString temp_visit;
	CString temp_disease;
	CString temp_symptom;
	CString temp_path;

	virtual void OnCancel();
	afx_msg void OnBnClickedButtonCancel();
	void AddEndedEventHandler(EndDialogEventHandler* eeh);

};
