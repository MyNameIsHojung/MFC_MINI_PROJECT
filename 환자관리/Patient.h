#pragma once
class Patient
{
	const int no;   //NO
	CString name;   //�̸�
	CString phone;  //��ȭ��ȣ
	CString birth;  //�������
	CString addr;   //�ּ�
	CString id;     //�ֹε�Ϲ�ȣ
	COleDateTime date;   //�湮��¥
	CString sick;   //����
	CString image;  //����
	CString content;//����(�ڼ��� ���� �� ó��)
	CString content_ex;//���
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

