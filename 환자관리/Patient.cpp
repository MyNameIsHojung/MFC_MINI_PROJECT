#include "pch.h"
#include "Patient.h"
/*Patient::Patient(int no, CString name, CString phone, CString birth, CString addr
	, CString id, COleDateTime date, CString sick, CString image, CString content
	, CString content_ex) : no(no)
{
	this->name = name;
	this->phone = phone;
	this->birth = birth;
	this->addr = addr;
	this->id = id;
	this->date = date;
	this->sick = sick;
	this->image = image;
	this->content = content;
	this->content_ex = content_ex;

}
*/
Patient::Patient(int no,CString name, CString phone, CString birth, CString addr, CString id, COleDateTime date, CString content):no(no)
{
	this->name = name;
	this->phone = phone;
	this->birth = birth;
	this->addr = addr;
	this->id = id;
	this->date = date;
	this->content = content;
}
Patient::Patient(int no,CString name, CString phone, CString birth, CString addr, CString id, COleDateTime date, CString content, CString content_ex):no(no)
{
	this->name = name;
	this->phone = phone;
	this->birth = birth;
	this->addr = addr;
	this->id = id;
	this->date = date;
	this->content = content;
	this->content_ex = content_ex;
}
int Patient::GetNO()
{
	return no;
}
CString Patient::GetName()
{
	return name;
}
CString Patient::GetPhone()
{
	return phone;
}
CString Patient::GetBirth()
{
	return birth;
}
CString Patient::GetAddr()
{
	return addr;
}
CString Patient::GetId()
{
	return id;
}
COleDateTime Patient::GetDate()
{
	return date;
}
CString Patient::GetSick()
{
	return sick;
}
CString Patient::GetImage()
{
	return image;
}
CString Patient::GetContent()
{
	return content;
}
CString Patient::GetContent_Ex()
{
	return content_ex;
}

void Patient::SetName(CString name)
{
	this->name = name;
}
void Patient::SetPhone(CString phone)
{
	this->phone = phone;
}
void Patient::SetBirth(CString birth)
{
	this->birth = birth;
}
void Patient::SetAddr(CString addr)
{
	this->addr = addr;
}
void Patient::SetId(CString id)
{
	this->id = id;
}
void Patient::SetDate(COleDateTime date)
{
	this->date = date;
}
void Patient::SetSick(CString sick)
{
	this->sick = sick;
}
void Patient::SetImage(CString image)
{
	this->image = image;
}
void Patient::SetContent(CString content)
{
	this->content = content;
}
void Patient::SetContent_Ex(CString content_ex)
{
	this->content_ex = content_ex;
}