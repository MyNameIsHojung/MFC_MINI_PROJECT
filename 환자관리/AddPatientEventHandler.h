#pragma once
class Patient;
class AddPatientEventHandler
{
public:
	virtual void AddedPatient(Patient* patient) = 0;
};
//class UpdatePatientEventHandler
//{
//public:
//	virtual void UpdatePatient(Patient* patient) = 0;
//};
//
//class RemovePatientEventHandler
//{
//public:
//	virtual void RemovedPatient(int pno) = 0;
//};







