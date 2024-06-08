#include "workerManager.h"
#include "fstream"
#include "string"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

WorkerManager::WorkerManager()
{

    ifstream ifs;
    ifs.open(FILENAME,ios::in);



    if(!ifs.is_open()){
        cout<<"文件不存在"<<endl;
        this->m_EmpNum=0;
        this->m_EmpArray= nullptr;
        this->m_FileIsEmpty=true;
        return;
    }

    char ch;
    ifs>>ch;
    if(ifs.eof()){
        cout<<"文件为空"<<endl;
        this->m_EmpNum=0;
        this->m_EmpArray= nullptr;
        this->m_FileIsEmpty=true;
        ifs.close();
        return;



    }

    this->m_FileIsEmpty= false;
    int num=this->get_EmpNum();
    cout<<"职工个数为："<<num<<endl;
    this->m_EmpNum=num;

    this->m_EmpArray=new Worker * [this->m_EmpNum];
    init_Emp();
    for (int i = 0; i < this->m_EmpNum; ++i)
    {
        cout<<" 职工编号："<<this->m_EmpArray[i]->m_Id
        <<" 职工名称："<<this->m_EmpArray[i]->m_Name
        <<" 部门编号："<<this->m_EmpArray[i]->m_DeptId<<endl;
    }


}

void WorkerManager::Show_Menu()
{
    ifstream show;
    string buff;
    show.open("title.txt",ios::in);
    if(!show.is_open())
    {
        std::cout << "open title error" << endl;
        return;
    }
    while (getline(show,buff)){

        std::cout<<buff<<endl;
    }
    show.close();
    return;

}

void WorkerManager::exitSystem()
{
    cout<<"欢迎下次使用"<<endl;
    std::system("pause");
    exit(0);

}

void WorkerManager::Add_Emp()
{
    cout<<"请输入增加职工数量："<<endl;
    int addNum =0;
    cin>>addNum;
    if(addNum>0)
    {
        int newSize=this->m_EmpNum+addNum;
        Worker ** newSpace=new Worker * [newSize];
        if(this->m_EmpArray!= nullptr)
        {
            for (int i = 0; i < this->m_EmpNum; ++i)
            {
                newSpace[i]=this->m_EmpArray[i];
            }

        }

        for (int i = 0; i < addNum; ++i)
        {
            int id;
            string name;
            int dSelect;

            cout<<"请输入第"<<i+1<<"个新职工编号"<<endl;
            cin>>id;

            cout<<"请输入第"<<i+1<<"个新职工名字"<<endl;
            cin>>name;

            cout<<"请选择该员工的职位"<<endl;
            cout<<"1.普通员工"<<endl;
            cout<<"2.经理"<<endl;
            cout<<"3.老板"<<endl;
            cin>>dSelect;

            Worker *worker=nullptr;
            switch (dSelect){
                case 1:
                    worker=new Employee(id,name,1);
                    break;
                case 2:
                    worker=new Manager(id,name,2);
                    break;
                case 3:
                    worker=new Boss(id,name,3);
                    break;
                default:
                    break;

            }

            newSpace[this->m_EmpNum+i]=worker;

        }

        delete[] this->m_EmpArray;

        this->m_EmpArray=newSpace;

        this->m_EmpNum=newSize;

        cout<<"成功添加"<<addNum<<"名新职工"<<endl;
    }
    else{
        cout<<"数量输入有误"<<endl;
    }

    this->save();
    this->m_FileIsEmpty = false;
    std::system("pause");
    std::system("cls");
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME,ios::out);

    for (int i = 0; i < this->m_EmpNum; ++i)
    {
        ofs<<this->m_EmpArray[i]->m_Id<<" "
        <<this->m_EmpArray[i]->m_Name<<" "
        <<this->m_EmpArray[i]->m_DeptId<<endl;
    }

    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;
    int num=0;
    while (ifs>>id&&ifs>>name&&ifs>>dId){
        num++;

    }
    ifs.close();
    return num;

}

void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;
    int index=0;
    while (ifs>>id&&ifs>>name&&ifs>>dId){
        Worker *worker= nullptr;

        switch (dId)
        {
            case 1:
                worker=new Employee(id,name,dId);
                break;
            case 2:
                worker=new Manager(id,name,dId);
                break;
            case 3:
                worker=new Boss(id,name,dId);
                break;
            default:
                break;
        }
        this->m_EmpArray[index]=worker;
        index++;



    }
    ifs.close();
}

void WorkerManager::Show_Emp()
{
    if(this->m_EmpArray== nullptr||this->m_FileIsEmpty){
        cout<<"文件不存在或记录为空"<<endl;
    }
    else{
        for (int i = 0; i < this->m_EmpNum; ++i)
        {
            this->m_EmpArray[i]->showInfo();
        }

    }

    std::system("pause");
    std::system("cls");
}

void WorkerManager::Del_Emp()
{
    if(this->m_FileIsEmpty)
        cout<<"文件不存在或记录为空"<<endl;
    else{

        cout<<"请输入须删除的员工编号"<<endl;
        int id=0;
        cin>>id;
        int index = this->IsExist(id);
        if (index!=-1&&index!=m_EmpNum-1){
            for (int i = index; i < this->m_EmpNum-1; ++i)
            {
                this->m_EmpArray[i]=this->m_EmpArray[i+1];

            }
            this->m_EmpNum--;
            this->save();
            cout<<"删除成功！"<<endl;
        }
        else if(index==m_EmpNum-1){
            this->m_EmpNum--;
            this->save();
            if(m_EmpNum==0)
                this->m_FileIsEmpty= true;
            cout<<"删除成功！"<<endl;
        }
        else
        {
            cout << "删除失败，未找到该员工" << endl;

        }
    }
    std::system("pause");
    std::system("cls");

}

int WorkerManager::IsExist(int id)
{
    for (int i = 0; i < this->m_EmpNum; ++i)
    {
        if(m_EmpArray[i]->m_Id==id)
            return i;
    }
    return -1;

}


WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray!= nullptr)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = nullptr;
    }
}