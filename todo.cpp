#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;


void ShowUsage(){ // Funtion to show usages of todo.
   std::cout << "Usage:" << std::endl;

   std::cout << setw(30) << left << "  -a --add"
             << setw(50) << "Add a new TODO task" << endl;
   std::cout << setw(30) << left << "  -r --remove"
             << setw(50) << "Remove a finished work by its ID" << endl;
   std::cout << setw(30) << left << "  -s --show"
             << setw(50) << "Show your worklist" << endl;
   std::cout << setw(30) << left << "  -v --version"
             << setw(50) << "Display version" << endl;
   std::cout << setw(30) << left << "  -h --help"
             << setw(50) << "Display Usage" << endl;
   std::cout << setw(30) << left << "  -cl --clear"
             << setw(50) << "Clear all tasks" << endl;
}


void Show(){
  ifstream todo_file("/tmp/todo");
  int cnt = 0;
  string temp;
  if (todo_file.is_open()) {
    while (getline(todo_file, temp)){
      std::cout << "[" << ++cnt << "] " << temp << std::endl;
    }
    todo_file.close();
  } else{
    cerr << "File not exist." << endl;
    exit(1);
  }
}


void Add(int argc, const char* argv[]){
  string task;
  for (int i = 2; i < argc; i++) {
    task.append(string(argv[i]) + ' ');
  } 
  // File entry
  ofstream todo_file("/tmp/todo", ios::app);
  if(!todo_file.is_open()){
    cerr << "No file found." << endl;
    exit(1);
  } else{
    todo_file << task;
  }
  todo_file << "\n";
  todo_file.close();
}


/*
int TaskParse(string t){
  int pos_i, pos_j;
  pos_i = t.find_first_of('[') + 1;
  pos_j = t.find_first_of(']') - 1;
  string t_sub = t.substr(pos_i, pos_j);
  int t_sub_n = std::stod(t_sub);
  return t_sub_n;
} */


void Remove(int argc, const char* argv[]){
  ofstream temp_todo_file("/tmp/todo.tmp");
  ifstream todo_file("/tmp/todo");
  if(!todo_file.is_open()){
    cerr << "No file found." << endl;
    exit(1);
  }
  int del_id = std::stod(argv[2]);
  string task_elem;
  int id = 1; // re-align the indexes
  while(getline(todo_file, task_elem)){
    if(id++ != del_id)
      temp_todo_file << task_elem + '\n';
    else
      std::cout << "Deleted task: " << task_elem << std::endl;
  }
  temp_todo_file.close();
  todo_file.close();
  if(rename("/tmp/todo.tmp", "~/Documents/todo")){
    std::cout << "Permission denied: Can't overwrite TODO file." << std::endl;
    exit(1);
  }

}


int main(int argc, const char *argv[])
{
  int mode;
  if(argc < 2){
    ShowUsage();
    return 1;
  }
  // mode assign
  if(string(argv[1]) == "-s" or string(argv[1]) == "--show")  mode = 1;
  else if(string(argv[1]) == "-a" or string(argv[1]) == "--add") mode = 2;
  else if(string(argv[1]) == "-r" or string(argv[1]) == "--remove")  mode = 3;
  else if(string(argv[1]) == "-h" or string(argv[1]) == "--help") mode = 4;
  else if(string(argv[1]) == "-cl" or string(argv[1]) == "--clear")  mode = 5;
  else mode = 0;
  switch(mode){ // function entry
    case 0:
      ShowUsage();
      break;
    case 1:
      Show();
      break;
    case 2:
      Add(argc, argv);
      break;
    case 3:
      Remove(argc, argv);
      break;
    case 4:
      ShowUsage();
      break;
    case 5:
      if( remove("/tmp/todo") )
        std::cout << "Permission denied: Can't clear all tasks." << std::endl;
      std::cout << "All tasks cleared." << std::endl;
      break;
  }

  return 0;
}