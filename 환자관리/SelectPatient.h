#pragma once
class SelectPatient
{
private:
	static SelectPatient* singleton;	
private:
	SelectPatient();
public:
	static SelectPatient* GetInstance();

private:
	CString pid;

public:
	CString GetPid();
	void SetPid(CString pid);

};

