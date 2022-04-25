#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <string>
#include <math.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <utility>
using namespace std;

const string EMP_FILE = "Emp.csv";
const string DEPT_FILE = "Dept.csv";

/*
Employee Class
*/
class emp {
  public:
    int id;
    string name;
    int age;
    double salary;
};

/*
Department Class
*/
class dept {
  public:
    int id;
    string name;
    string bud; //made into a string instead of double because of printing issue
    int man_id;
};

/*
Get the length of the file
*/
void lengthEMP(int &EMP_LEN) {
    ifstream data; 
    string lines;
    data.open(EMP_FILE); 
    if(!data) { cout << "Error: could not open file [make sure your Emp.csv file exist] (please check README.csv)" << endl; exit(1); }
    else { while(getline(data, lines)) { EMP_LEN++; } }
    data.close();
}

/*
reads data and saves it to a vector. 
vector only grabs it's allocated memory allowed
which in this case is 6 blocks at a time.
*/
void readEMP(vector<emp> &emp_data, int &EMP_LEN, int &GET_AMOUNT_EMP, int &START_INDEX_EMP) {
    ifstream data;
    data.open(EMP_FILE);
    string lines;
    char* ch;
    int p = 0;

    //check if we have gone over the limit
    if(EMP_LEN < GET_AMOUNT_EMP+START_INDEX_EMP) {
        GET_AMOUNT_EMP = EMP_LEN - START_INDEX_EMP;
    }

    //ignore lines we already met
    while (START_INDEX_EMP != p) { getline(data, lines); p++; }

    //get the lines
    for (size_t i = 0; i < GET_AMOUNT_EMP; i++)
    {
        getline(data, lines);
        emp emp_content;
        char raw_arr[lines.size()+1];
        strcpy(raw_arr, lines.c_str());
        ch = strtok(raw_arr, ",");
        int id = atoi(ch);
        ch = strtok(NULL, ",");
        string name = ch;
        ch = strtok(NULL, ",");
        int age = atoi(ch);
        ch = strtok(NULL, ",");
        double salary = stod(ch);
        emp_content.id = id;
        emp_content.name = name;
        emp_content.age = age;
        emp_content.salary = salary;
        emp_data.push_back(emp_content);
    }
    START_INDEX_EMP += GET_AMOUNT_EMP;
}

/*
sort the data and save it to a temporary file
*/
void sortSaveEMP(vector<emp> &emp_data, int &EMP_LEN_FILES, vector<int> &emp_length) {
    sort(emp_data.begin(), emp_data.end(), [](const emp& lhs, const emp& rhs){ return lhs.id < rhs.id; });

    ofstream file;
    file.open("EMP_" + to_string(EMP_LEN_FILES) + ".csv");
    for (size_t i = 0; i < emp_data.size(); i++)
    {
        file << emp_data[i].id << "," << emp_data[i].name << "," << emp_data[i].age << "," << emp_data[i].salary << endl;
    }
    EMP_LEN_FILES++;
    file.close();
    emp_length.push_back(emp_data.size());
    emp_data.clear();
}

/*
Get the length of the file
*/
void lengthDEPT(int &DEPT_LEN) {
    ifstream data; 
    string lines;
    data.open(DEPT_FILE); 
    if(!data) { cout << "Error: could not open file [make sure your Dept.csv file exist] (please check README.csv)" << endl; exit(1); }
    else { while(getline(data, lines)) { DEPT_LEN++; } }
    data.close();
}

/*
reads data and saves it to a vector. 
vector only grabs it's allocated memory allowed
which in this case is 6 blocks at a time.
*/
void readDEPT(vector<dept> &dept_data, int &DEPT_LEN, int &GET_AMOUNT_DEPT, int &START_INDEX_DEPT) {
    ifstream data;
    data.open(DEPT_FILE);
    string lines;
    char* ch;
    int p = 0;

    //check if we have gone over the limit
    if(DEPT_LEN < GET_AMOUNT_DEPT+START_INDEX_DEPT) {
        GET_AMOUNT_DEPT = DEPT_LEN - START_INDEX_DEPT;
    }

    //ignore lines we already met
    while (START_INDEX_DEPT != p) { getline(data, lines); p++; }

    //get the lines
    for (size_t i = 0; i < GET_AMOUNT_DEPT; i++)
    {
        getline(data, lines);
        dept dept_content;
        char raw_arr[lines.size()+1];
        strcpy(raw_arr, lines.c_str());
        ch = strtok(raw_arr, ",");
        int id = atoi(ch);
        ch = strtok(NULL, ",");
        string name = ch;
        ch = strtok(NULL, ",");
        string bud = ch;
        ch = strtok(NULL, ",");
        int man_id = atoi(ch);
        dept_content.id = id;
        dept_content.name = name;
        dept_content.bud = bud;
        dept_content.man_id = man_id;
        dept_data.push_back(dept_content);
    }
    START_INDEX_DEPT += GET_AMOUNT_DEPT;
}

/*
sort the data and save it to a temporary file
*/
void sortSaveDEPT(vector<dept> &dept_data, int &DEPT_LEN_FILES, vector<int> &dept_length) {
    sort(dept_data.begin(), dept_data.end(), [](const dept& lhs, const dept& rhs){ return lhs.man_id < rhs.man_id; });

    ofstream file;
    file.open("DEPT_" + to_string(DEPT_LEN_FILES) + ".csv");
    for (size_t i = 0; i < dept_data.size(); i++)
    {
        file << dept_data[i].id << "," << dept_data[i].name << "," << dept_data[i].bud << "," << dept_data[i].man_id << endl;
    }
    DEPT_LEN_FILES++;
    file.close();
    dept_length.push_back(dept_data.size());
    dept_data.clear();
}

/*
finds the file that has the lowest block index
*/
void findEmpSuccessor(int &EMP_LEN_FILES, int &emp_smallest, int &index_choosen, vector<int> &FILE_EMP_CNT, vector<int> &emp_length) {
    string lines;
    for (size_t i = 0; i < EMP_LEN_FILES; i++)
    {
        // cout << "FILE: " << i << endl;
        ifstream data;
        char* ch;
        data.open("EMP_" + to_string(i) + ".csv");
        int p = 0;

        if(FILE_EMP_CNT[i] == emp_length[i]) {
        }
        else {
            while (FILE_EMP_CNT[i] != p) { getline(data, lines); p++; }

            getline(data,lines);
            emp emp_content;
            char raw_arr[lines.size()+1];
            strcpy(raw_arr, lines.c_str());
            ch = strtok(raw_arr, ",");
            int id = atoi(ch);

            if(emp_smallest == -1) {
                emp_smallest = id;
                index_choosen = i;
            }
            else {
                data.close();
                data.open("EMP_" + to_string(i) + ".csv");
                int o = 0;
                while (FILE_EMP_CNT[i] != o) { getline(data, lines); o++; }

                getline(data, lines);
                emp emp_content;
                char raw_arr[lines.size()+1];
                strcpy(raw_arr, lines.c_str());
                ch = strtok(raw_arr, ",");
                int id2 = atoi(ch);
                if(emp_smallest >= id2) {
                    emp_smallest = id2;
                    index_choosen = i;
                }
            }
        }
        data.close();
    }
    FILE_EMP_CNT[index_choosen] += 1;
}

/*
saves the block that we will be using
*/
void saveEmpSuccessor(vector<emp> &emp_data, int &index_choosen, vector<int> &FILE_EMP_CNT) {
    string lines;
    ifstream data;
    char* ch;
    data.open("EMP_" + to_string(index_choosen) + ".csv");
    int p = 0;

    while (FILE_EMP_CNT[index_choosen] != p) { getline(data, lines); p++; }

    emp emp_content;
    char raw_arr[lines.size()+1];
    strcpy(raw_arr, lines.c_str());
    ch = strtok(raw_arr, ",");
    int id = atoi(ch);
    ch = strtok(NULL, ",");
    string name = ch;
    ch = strtok(NULL, ",");
    int age = atoi(ch);
    ch = strtok(NULL, ",");
    double salary = stod(ch);
    emp_content.id = id;
    emp_content.name = name;
    emp_content.age = age;
    emp_content.salary = salary;
    emp_data.push_back(emp_content);
    data.close();
}

/*
finds the file that has the lowest block index
*/
void findDeptSuccessor(int &DEPT_LEN_FILES, int &dept_smallest, int &dept_index_choosen, vector<int> &FILE_DEPT_CNT, vector<int> &dept_length) {
    string lines;
    for (size_t i = 0; i < DEPT_LEN_FILES; i++)
    {
        ifstream data;
        char* ch;
        data.open("DEPT_" + to_string(0) + ".csv");
        int p = 0;

        if(FILE_DEPT_CNT[i] == dept_length[i]) {
            // cout << "LIMIT REACHED :(" << endl;
        }
        else {
            // cout << "limit good :)" << endl;
            while (FILE_DEPT_CNT[i] != p) { getline(data, lines); p++; }

            getline(data, lines);
            char raw_arr[lines.size()+1];
            strcpy(raw_arr, lines.c_str());
            ch = strtok(raw_arr, ",");
            ch = strtok(NULL, ",");
            ch = strtok(NULL, ",");
            ch = strtok(NULL, ",");
            int id = atoi(ch);

            if(dept_smallest == -1) {
                // cout << dept_smallest << endl;
                dept_smallest = id;
                dept_index_choosen = i;
            }
            else {
                data.close();
                data.open("DEPT_" + to_string(i) + ".csv");
                int o = 0;
                while (FILE_DEPT_CNT[i] != o) { getline(data, lines); o++; }

                getline(data, lines);
                char raw_arr[lines.size()+1];
                strcpy(raw_arr, lines.c_str());
                ch = strtok(raw_arr, ",");
                ch = strtok(NULL, ",");
                ch = strtok(NULL, ",");
                ch = strtok(NULL, ",");
                int id2 = atoi(ch); //wanna grab the man_id
                if(dept_smallest >= id2) {
                    // cout << "successor found: " << dept_smallest << " >= " << id2 << endl;
                    dept_smallest = id2;
                    dept_index_choosen = i;
                }
            }
        }
        data.close();
    }
}

/*
saves the block that we will be using
*/
void saveDeptSuccessor(vector<dept> &dept_data) {
    string lines;
    ifstream data;
    char* ch;
    data.open("DEPT_" + to_string(0) + ".csv");

    while(getline(data, lines)) {
        dept dept_content;
        char raw_arr[lines.size()+1];
        strcpy(raw_arr, lines.c_str());
        ch = strtok(raw_arr, ",");
        int id = atoi(ch);
        ch = strtok(NULL, ",");
        string name = ch;
        ch = strtok(NULL, ",");
        string bud = ch;
        ch = strtok(NULL, ",");
        int man_id = atoi(ch);
        dept_content.id = id;
        dept_content.name = name;
        dept_content.bud = bud;
        dept_content.man_id = man_id;
        dept_data.push_back(dept_content);
    }

    data.close();
}

/*
main calls all the functions above and inside main we preform the optimized merge sort
*/
int main(int argc, char *argv[]) {
    vector<emp> emp_data; vector<dept> dept_data;
    vector<pair<emp, dept>> result;
    int mark_pos = -1; bool mark_bool = false;
    int r = 0; int s = 0;

    vector<int> emp_length;
    vector<int> dept_length;

    int EMP_LEN = 0;
    int EMP_LEN_FILES = 0;
    lengthEMP(EMP_LEN);
    int GET_AMOUNT_EMP = 6;
    int START_INDEX_EMP = 0;

    //phase 1
    while(EMP_LEN != START_INDEX_EMP && EMP_LEN > START_INDEX_EMP) {
        readEMP(emp_data, EMP_LEN, GET_AMOUNT_EMP, START_INDEX_EMP);
        sortSaveEMP(emp_data, EMP_LEN_FILES, emp_length);
    }

    int DEPT_LEN = 0;
    int DEPT_LEN_FILES = 0;
    lengthDEPT(DEPT_LEN);
    int GET_AMOUNT_DEPT = 15;
    int START_INDEX_DEPT = 0;

    //phase 1
    while(DEPT_LEN != START_INDEX_DEPT && DEPT_LEN > START_INDEX_DEPT) {
        readDEPT(dept_data, DEPT_LEN, GET_AMOUNT_DEPT, START_INDEX_DEPT);
        sortSaveDEPT(dept_data, DEPT_LEN_FILES, dept_length);
    }

    //below we will preform phase 2

    int emp_smallest = -1;
    int emp_index_choosen = -1;

    vector<int> FILE_EMP_CNT;
    for(int i = 0; i < EMP_LEN_FILES; i++) { FILE_EMP_CNT.push_back(0); }

    emp_smallest = -1; emp_index_choosen = -1;
    findEmpSuccessor(EMP_LEN_FILES, emp_smallest, emp_index_choosen, FILE_EMP_CNT, emp_length);
    saveEmpSuccessor(emp_data, emp_index_choosen, FILE_EMP_CNT);

    saveDeptSuccessor(dept_data);


    //optimized merge sort
    while(dept_data.size() != s && emp_index_choosen != -1)
    {
        if(r == 6) {
            for (size_t i = 0; i < 6; i++)
            {
                emp_data.erase(emp_data.begin());
                r--;
            }
        }
        if (!mark_bool) {
            while (dept_data[s].man_id > emp_data[r].id) { 
                emp_smallest = -1; emp_index_choosen = -1;
                findEmpSuccessor(EMP_LEN_FILES, emp_smallest, emp_index_choosen, FILE_EMP_CNT, emp_length);
                saveEmpSuccessor(emp_data, emp_index_choosen, FILE_EMP_CNT);
                r++;
            }
            while(dept_data[s].man_id < emp_data[r].id) { s++; }
            mark_pos = s; mark_bool = true;
        }
        if(emp_data[r].id == dept_data[s].man_id) {
            result.push_back(make_pair(emp_data[r], dept_data[s]));
            s++;
        }
        else {
            s = mark_pos;
            emp_smallest = -1; emp_index_choosen = -1;
            findEmpSuccessor(EMP_LEN_FILES, emp_smallest, emp_index_choosen, FILE_EMP_CNT, emp_length);
            saveEmpSuccessor(emp_data, emp_index_choosen, FILE_EMP_CNT);
            r++;
            mark_pos = -1; mark_bool = false;
        }
    }

    //write our solution to the final csv file
    ofstream MyFile("join.csv");
    for (size_t i = 0; i < result.size(); i++)
    {
        MyFile << result[i].first.id << "," << result[i].first.name << "," << result[i].first.age << "," << result[i].first.salary << "," << result[i].second.id << "," << result[i].second.name << "," << (double)atoi(result[i].second.bud.c_str()) << endl;
    }

    return 0;
}