#include <iostream>
#include "workerManager.h"
using namespace std;

int main()
{
    WorkerManager wm;
    int choice;
    while (true){
        wm.Show_Menu();
        cout<<"请输入你的选择"<<endl;
        cin>>choice;
        switch (choice)
        {
            case 0:   //退出
                wm.exitSystem();
                break;
            case 1:   //退出
                break;
            case 2:   //退出
                break;
            case 3:   //退出
                break;
            case 4:   //退出
                break;
            case 5:   //退出
                break;
            case 6:   //退出
                break;
            case 7:   //退出
                break;
            default:
                system("cls");
                break;

        }





    }
    return 0;
}
