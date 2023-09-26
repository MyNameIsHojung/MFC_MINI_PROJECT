#pragma once
class Patient
{
	const int no;   //NO
	CString name;   //이름
	CString phone;  //전화번호
	CString birth;  //생년월일
	CString addr;   //주소
	CString id;     //주민등록번호
	COleDateTime date;   //방문날짜
	CString sick;   //병명
	CString image;  //사진
	CString content;//증상(자세한 증상 및 처방)
	CString content_ex;//비고
	//CString content_summary;

public:
	/*
	Patient(int no, CString name, CString phone, CString birth, CString addr
		, CString id, COleDateTime date, CString sick, CString image, CString content
		, CString content_ex);
	*/
	Patient(int no, CString name, CString phone, CString birth, CString addr, CString id, COleDateTime date,CString content);
	Patient(int no, CString name, CString phone, CString birth, CString addr, CString id, COleDateTime date, CString content, CString content_ex);
	int GetNO();
	CString GetName();
	CString GetPhone();
	CString GetBirth();
	CString GetAddr();
	CString GetId();
	COleDateTime GetDate();
	CString GetSick();
	CString GetImage();
	CString GetContent();
	CString GetContent_Ex();

	void SetName(CString name);
	void SetPhone(CString phone);
	void SetBirth(CString birth);
	void SetAddr(CString addr);
	void SetId(CString id);
	void SetDate(COleDateTime date);
	void SetSick(CString sick);
	void SetImage(CString image);
	void SetContent(CString content);
	void SetContent_Ex(CString content_ex);

};

