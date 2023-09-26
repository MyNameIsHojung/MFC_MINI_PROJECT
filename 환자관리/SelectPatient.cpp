#include "pch.h"
#include "SelectPatient.h"

SelectPatient* SelectPatient::singleton = NULL;

SelectPatient::SelectPatient()
{
	pid = "";
}

SelectPatient* SelectPatient::GetInstance()
{
	if (singleton == NULL)
	{
		singleton = new SelectPatient();
	}
	return singleton;
}

CString SelectPatient::GetPid() { return pid; }
void SelectPatient::SetPid(CString pid) { this->pid = pid; }