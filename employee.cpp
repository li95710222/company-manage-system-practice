#include "iostream"
#include "string"
#include "employee.h"

using namespace std;

Employee::Employee(int id, std::string name, int dId)
{
    this->m_Id=id;
    this->m_Name=name;
    this->m_DeptId=dId;
}

void Employee::showInfo()
{
    cout<<"职工编号："<<this->m_Id;
    cout<<"\t职工姓名："<<this->m_Name;
    cout<<"\t岗位："<<this->getDeptName();
    cout<<"\t岗位职责：完成经理交给的任务"<<endl;
    return;
}

string Employee::getDeptName()
{
    return string("员工");
}
