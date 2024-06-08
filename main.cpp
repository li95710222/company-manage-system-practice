#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

void test();

using namespace std;

int main()
{
    WorkerManager wm;
    int choice;
    test();
//    while (true){
//        wm.Show_Menu();
//        cout<<"请输入你的选择"<<endl;
//        cin>>choice;
//        switch (choice)
//        {
//            case 0:   //退出
//                wm.exitSystem();
//                break;
//            case 1:   //退出
//                break;
//            case 2:   //退出
//                break;
//            case 3:   //退出
//                break;
//            case 4:   //退出
//                break;
//            case 5:   //退出
//                break;
//            case 6:   //退出
//                break;
//            case 7:   //退出
//                break;
//            default:
//                system("cls");
//                break;
//
//        }
//
//
//
//
//
//    }
    return 0;
}



void test(){

    Worker *worker = nullptr;
    worker = new Employee(1,"张三",1);
    worker->showInfo();
    delete worker;

    worker = new Manager(2,"李四",2);
    worker->showInfo();
    delete worker;

    worker = new Boss(3,"王五",3);
    worker->showInfo();
    delete worker;


}