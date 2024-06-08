#include "workerManager.h"
#include "fstream"
#include "string"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "algorithm"

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
            while(this->IsExist(id)!=-1){
                cout<<"输入职工编号重复，请重新输入"<<endl;
                cin>>id;
            }


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

void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或记录为空"<<endl;

    }
    else{
        cout<<"请输入修改职工的编号："<<endl;
        int id;
        cin>>id;
        int ret= IsExist(id);
        if(ret!=-1){
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName ="";
            int dSelect=0;

            cout<<"查到"<<id<<"号职工，请输入新职工号："<<endl;
            cin>>newId;

            cout<<"请输入新姓名："<<endl;
            cin>>newName;

            cout<<"请输入新岗位"<<endl;
            cout<<"1.普通职工"<<endl;
            cout<<"2.经理"<<endl;
            cout<<"3.老板"<<endl;

            cin>>dSelect;

            Worker *worker= nullptr;
            switch (dSelect){
                case 1:
                    worker=new Employee(newId,newName,dSelect);
                    break;
                case 2:
                    worker=new Manager(newId,newName,dSelect);
                    break;
                case 3:
                    worker=new Boss(newId,newName,dSelect);
                    break;
                default:
                    break;

            }

            this->m_EmpArray[ret]=worker;

            cout<<"修改成功"<<this->m_EmpArray[ret]->m_DeptId<<endl;

            this->save();

        }
        else{
            cout<<"修改失败，查无此人"<<endl;

        }

    }

    std::system("pause");
    std::system("cls");
}

void WorkerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者记录为空！"<<endl;
    }
    else
    {
        cout<<"请输入查找的方式："<<endl;
        cout<<"1.按职工编号查找"<<endl;
        cout<<"2.按姓名查找"<<endl;
        int select=0;
        cin>>select;

        if(select==1){
            int id;
            cout<<"请输入查找的职工编号："<<endl;
            cin>>id;

            int ret = IsExist(id);
            if(ret!=-1){
                cout<<"查找成功！该职工信息如下："<<endl;
                this->m_EmpArray[ret]->showInfo();

            }
            else{
                cout<<"查无此人"<<endl;

            }

        }
        else if(select==2){

            string name;
            cout<<"请输入查找的姓名"<<endl;
            cin>>name;

            bool flag =false;
            for (int i = 0; i < m_EmpNum; ++i)
            {
                if(this->m_EmpArray[i]->m_Name==name){
                    cout<<"查找成功，职工编号为："<<m_EmpArray[i]->m_Id<<"信息如下："<<endl;
                    flag=true;
                    this->m_EmpArray[i]->showInfo();

                }
            }
            if (flag== false){
                cout<<"查无此人"<<endl;
            }


        }
        else{
            cout<<"输入选项有误"<<endl;
        }
    }

    std::system("pause");
    std::system("cls");

}

bool cmp_Emp_down(Worker *x,Worker *y){
    return x->m_Id>y->m_Id;

}

bool cmp_Emp_up(Worker *x,Worker *y){
    return x->m_Id<y->m_Id;

}

void WorkerManager::Sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者记录为空！"<<endl;
        std::system("pause");
        std::system("cls");
    }
    else
    {
        cout<<"请选择排序方式："<<endl;
        cout<<"1.升序"<<endl;
        cout<<"2.降序"<<endl;

        int select=0;
        cin>>select;

        if (select==1){
            sort(this->m_EmpArray,(this->m_EmpArray)+this->m_EmpNum, cmp_Emp_up);
        }
        else if(select==2){
            sort(this->m_EmpArray,(this->m_EmpArray)+this->m_EmpNum, cmp_Emp_down);

        }
        else{
            cout<<"方式输入错误，退出"<<endl;
            return;
        }

        cout<<"排序成功，排序后结果为："<<endl;
        this->save();
        this->Show_Emp();

    }
    return;
}

void WorkerManager::Clean_File()
{
    cout<<"确认清空？"<<endl;
    cout<<"1.确认"<<endl;
    cout<<"2.返回"<<endl;

    int select = 0;
    cin>>select;

    if(select==1)
    {
        ofstream ofs(FILENAME,ios::trunc);
        ofs.clear();

        if(this->m_EmpArray!= nullptr)
        {
            for(int i=0;i<this->m_EmpNum;i++)
            {
                if(this->m_EmpArray[i]!= nullptr)
                {
                    delete this->m_EmpArray[i];
                }

            }
            this->m_EmpNum=0;
            delete[] this->m_EmpArray;
            this->m_EmpArray= nullptr;
            this->m_FileIsEmpty=true;

        }
        cout<<"清空成功！"<<endl;
    }

    std::system("pause");
    std::system("cls");
}

WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray!= nullptr)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = nullptr;
    }
}