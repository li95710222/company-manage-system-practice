#pragma once
#include "iostream"
#include "worker.h"
#include "fstream"
#define FILENAME "empFile.txt"

using namespace std;

class WorkerManager{
public:

    WorkerManager();

    void Show_Menu();

    void exitSystem();

    void Add_Emp();

    void save();

    int get_EmpNum();

    void init_Emp();

    void Show_Emp();

    void Del_Emp();

    int IsExist(int id);

    ~WorkerManager();

    int m_EmpNum;
    Worker ** m_EmpArray;
    bool m_FileIsEmpty;
};