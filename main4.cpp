#include <iostream>
#include <fstream>
#include <vector>
//#include <algorithm>
#include <sstream>
#include <cstring>
#include <stdio.h>
//#include "employee.h"
using namespace std;

class Employee{
private:
    int id, age;
    string name;
    double salary;

public:
    Employee(int id, string name, int age, double salary);

    void setEmployee(int id, string name, int age, double salary);

    int getId() {return id;}
    string getName() {return name;}
    int getAge() {return age;}
    double getSalary() {return salary;}
};

// Setting an employee class object
Employee::Employee(int cur_id, string cur_name, int cur_age, double cur_salary) {
    id = cur_id;
    name = cur_name;
    age = cur_age;
    salary = cur_salary;
}

// Create employee class object from a string of employee data
Employee getEmployee(string tuple){
    int tuple_count = 0, cur_id = 0, cur_age = 0;
    string cur_name, tuple_entry;
    double cur_salary;
    stringstream s_stream(tuple);
    while(s_stream.good()){
        getline(s_stream, tuple_entry, ',');
        if(tuple_count == 0){
            stringstream geek(tuple_entry);
            geek >> cur_id;
        }
        else if(tuple_count == 1)
            cur_name = tuple_entry;
        else if(tuple_count == 2){
            stringstream geek(tuple_entry);
            geek >> cur_age;
        }
        else{
            cur_salary = atof(tuple_entry.c_str());
        }
        tuple_count ++;
    }
    Employee emp = Employee(cur_id, cur_name, cur_age, cur_salary);
    return emp;
}

// Save employee data on its own file
void saveOnDisk(vector<Employee> emps, ofstream &sortedFile){
    //ofstream sortedFile("sortedFile.txt");
    if(sortedFile.is_open()){
        for(int i = 0; i < emps.size(); i ++)
            sortedFile << emps[i].getId() << ", " << emps[i].getName() << ", " << emps[i].getAge() << ", " << emps[i].getSalary() << "\n";
    }
}

// Run through the first pass and set clumps size M employees and save to the disk
int pass1(int num_blocks){
    string tuple, str_file_name, str_num_file, start_file = "sortedFile", end_file = ".txt";
    int count = 0, pos = 0, num_chunks = 0, num_file = 0;
    bool sorted = false;
    vector<Employee> emps;

    //ofstream sortedFile("sortedFile.txt");
    ifstream emp_file ("Emp.csv");
    if(emp_file.is_open()){
        while(getline(emp_file, tuple)){
            if(count == num_blocks){
                str_num_file = to_string(num_file);
                str_file_name = start_file + str_num_file + end_file;
                ofstream sortedFile(str_file_name);
                saveOnDisk(emps, sortedFile);
                sortedFile.close();
                emps.clear();
                count = 0;
                num_file ++;
            }
            Employee emp = getEmployee(tuple);
            while(sorted == false){

                if(emps.size() == 0){
                    emps.push_back(emp);
                    sorted = true;
                }
                else if(emps.size() == pos){
                    emps.push_back(emp);
                    sorted = true;
                }
                else if(emps[pos].getId() > emp.getId()){
                    emps.insert(emps.begin() + pos, emp);
                    sorted = true;
                }
                pos++;

            }

            sorted = false;
            pos = 0;
            count ++;
            num_chunks ++;
        }
        if(count != 0){
            str_num_file = to_string(num_file);
            str_file_name = start_file + str_num_file + end_file;
            ofstream sortedFile(str_file_name);
            saveOnDisk(emps, sortedFile);
            emps.clear();
        }
        for(int i = 0; i < emps.size(); i++)
            cout << emps[i].getId() << " ";
        //sortedFile.close();
        emp_file.close();
    }

    return num_chunks;
}

// Get to tuple on a certain line in a file
Employee toTuple(ifstream &chunk_file, int line){
    int cur_line = 0;
    string tuple;
    while(getline(chunk_file, tuple)){
        if(cur_line == line)
            break;
        cur_line ++;
    }
    Employee emp = getEmployee(tuple);
    return emp;
}

// Check if all of the employees from a file  have been added to new clump
bool check_file_complete(string file_name, int line_pos){
    int total_lines = 0;
    string tuple;
    ifstream check_file(file_name);
    if(check_file.is_open()){
        while(getline(check_file, tuple)){
            total_lines ++;
        }
    }
    if(line_pos >= total_lines)
        return true;
    else
        return false;
}

// Go through K-1 passes until > (M-1)
int multi_pass(int num_blocks, int cur_chunk, int num_chunks, int new_disk) {
    string tuple, str_file_name, new_file_name, str_num_file, start_file = "sortedFile", new_start_file = "newSortedFile", end_file = ".txt";
    int num_file = cur_chunk, emp_change = 0, lowest_id = 0;
    char fileNameS[15];
    char fileNameL[16];
    bool merged = false;
    vector<Employee> emps;
    vector<int> pos;
    vector<int> file;

    // Initialize vectors, emps has first tuples in each file M-1
    for(int i = 0; i < (num_chunks - cur_chunk); i++){
        str_num_file = to_string(num_file);
        str_file_name = start_file + str_num_file + end_file;
        ifstream chunk_file(str_file_name);
        Employee emp = toTuple(chunk_file, 0);
        chunk_file.close();
        emps.push_back(emp);
        pos.push_back(0);
        file.push_back(num_file);
        num_file ++;
        if(i == num_blocks - 2)
            break;
    }

    str_num_file = to_string(new_disk);
    new_file_name = new_start_file + str_num_file + end_file;
    ofstream new_data(new_file_name);
    if(new_data.is_open()){

        while(merged != true){

            for(int i = 0; i < emps.size(); i++){

                if(i == 0)
                    lowest_id = emps[i].getId();

                else{

                    if(emps[i].getId() < lowest_id){
                        lowest_id = emps[i].getId();
                        emp_change = i;
                    }
                }
            }

            new_data << emps[emp_change].getId() << ", " << emps[emp_change].getName() << ", " << emps[emp_change].getAge() << ", " << emps[emp_change].getSalary() << "\n";
            pos[emp_change] ++;
            str_num_file = to_string(file[emp_change]);
            str_file_name = start_file + str_num_file + end_file;
            ifstream chunk_file(str_file_name);

            if(chunk_file.is_open()){
                Employee emp = toTuple(chunk_file, pos[emp_change]);
                emps.at(emp_change) = emp;
            }

            chunk_file.close();
            if(check_file_complete(str_file_name, pos[emp_change])){
                int deletion = 0;
                char fileName[str_file_name.size()+1];
                strcpy(fileName, str_file_name.c_str());
                deletion = remove(fileName);

                if(deletion != 0)
                    cout << str_file_name << " was not able to be deleted\n";
                emps.erase(emps.begin() + emp_change);
                pos.erase(pos.begin() + emp_change);
                file.erase(file.begin() + emp_change);
            }

            if(emps.size() == 0 || pos.size() == 0 || file.size() == 0)
                merged = true;
            emp_change = 0;
        }
    }
    new_data.close();
    return num_file;
}

// Increase the chunk size by going through another k-pass
int incChunkSz(int num_blocks, int k_pass, int num_chunks){
    int cur_chunk = 0;
    int new_num_chunks = 0;
    bool merge = false;
    for(int i = 0; i < k_pass; i++) // Add to number of blocks in the pass depending on the number of the pass
        num_blocks = num_blocks * (num_blocks-1);
    while(merge == false){
        cur_chunk = multi_pass(num_blocks, cur_chunk, num_chunks, new_num_chunks); // Sort M-1 chunks
        new_num_chunks ++;
        if(cur_chunk >= num_chunks)
            merge = true;
    }
    return new_num_chunks;
}

// Run through the last pass of > (M - 1)
void last_pass(int num_chunks){
    string str_num_file, str_file_name;
    int num_file = 0, lowest_id = 0, emp_change = 0;
    bool merged = false;
    vector<Employee> emps;
    vector<int> pos;
    vector<int> file;

    for(int i = 0; i < num_chunks; i++){
        str_num_file = to_string(num_file);
        str_file_name = "newSortedFile" + str_num_file + ".txt";
        ifstream chunk_file(str_file_name);
        Employee emp = toTuple(chunk_file, 0);
        chunk_file.close();
        emps.push_back(emp);
        pos.push_back(0);
        file.push_back(num_file);
        num_file ++;
    }

    ofstream sorted_file("EmpSorted.csv");
    if(sorted_file.is_open()){

        while(merged != true){

            for(int i = 0; i < emps.size(); i ++){

                if(i == 0)
                    lowest_id = emps[i].getId();

                else{

                    if(emps[i].getId() < lowest_id){
                        lowest_id = emps[i].getId();
                        emp_change = i;
                    }
                }
            }
            sorted_file << emps[emp_change].getId() << "," << emps[emp_change].getName() << "," << emps[emp_change].getAge() << "," << emps[emp_change].getSalary() << "\n";

            pos[emp_change] ++;
            str_num_file = to_string(file[emp_change]);
            str_file_name = "newSortedFile" + str_num_file + ".txt";
            ifstream chunk_file(str_file_name);
            if(chunk_file.is_open()){
                Employee emp = toTuple(chunk_file, pos[emp_change]);
                emps.at(emp_change) = emp;
            }

            chunk_file.close();
            if(check_file_complete(str_file_name, pos[emp_change])){
                int deletion = 0;
                char fileName[str_file_name.size()+1];
                strcpy(fileName, str_file_name.c_str());
                deletion = remove(fileName);

                if(deletion != 0)
                    cout << str_file_name << " was not able to be deleted\n";
                emps.erase(emps.begin() + emp_change);
                pos.erase(pos.begin() + emp_change);
                file.erase(file.begin() + emp_change);
            }

            if(emps.size() == 0 || pos.size() == 0 || file.size() == 0)
                merged = true;
            emp_change = 0;
        }
    }

    sorted_file.close();
}

// Multi-pass Multi-way sorting algorithm
void mpmw_sorting(int num_blocks){
    int num_chunks = 0, k_pass = 0, total_tuples = 0, remainder = 0;
    total_tuples = pass1(num_blocks); // Run through the first pass and calculate the number of total tuples
    num_chunks = total_tuples / num_blocks;
    remainder = total_tuples / num_blocks;
    if(remainder != 0) // Add one if the number does not evenly divide into number of blocks
        num_chunks ++;
    while(num_chunks > num_blocks - 1){ // Continue to go through k-passes until the number of chunks in less than or equal to M - 1
        num_chunks = incChunkSz(num_blocks, k_pass, num_chunks);
        k_pass ++;
    }
    last_pass(num_chunks);
}

// Call the multi-pass multi-way sorting algorithm
int main() {
    int num_blocks = 22;

    mpmw_sorting(num_blocks);

    return 0;
}
