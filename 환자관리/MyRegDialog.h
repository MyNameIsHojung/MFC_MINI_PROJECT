#pragma once
#include "afxdialogex.h"
#include "EndDialogEventHandler.h"


// MyRegDialog 대화 상자

class MyRegDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyRegDialog)
	EndDialogEventHandler* eeh;


public:
	MyRegDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MyRegDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif
public:
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	CString name;
	CString phone;
	CString birth;
	CString addr;
	CString p_id;
	CString content;
	CString image;
	COleDateTime date1;
	COleDateTime date2;
	CMonthCalCtrl mc;
	CDateTimeCtrl dtp;
	CString content_ex;
	CStatic pic_img;
	afx_msg void OnStnDblclickStaticImg();
	virtual BOOL OnInitDialog();
	
private:
	void InitControls();
public:
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	void AddEndedEventHandler(EndDialogEventHandler* eeh);

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonCancel();
};
