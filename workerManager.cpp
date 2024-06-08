#include "workerManager.h"
#include "fstream"
#include "string"

WorkerManager::WorkerManager()
{


}

void WorkerManager::Show_Menu()
{
    ifstream show;
    string buff;
    show.open("../title.txt",ios::in);
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


WorkerManager::~WorkerManager()
{


}