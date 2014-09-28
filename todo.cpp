#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <boost/algorithm/string.hpp>
#include "utils/color.hpp"

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
  // TODO make it fancy!
  ifstream todo_file("/tmp/todo");
  int cnt = 0;
  string temp;
  if (todo_file.is_open()) {
    while (getline(todo_file, temp)){
      temp = "[" + std::to_string(++cnt) + "] " + temp + "\n";
      ColorPrint(temp);
      //std::cout << "[" << ++cnt << "] " << temp << std::endl;
    }
    todo_file.close();
  } else{
    cerr << "File not exist." << endl;
    exit(1);
  }
}


void Add(int argc, const char* argv[]){
  string argv_sum;
  vector<string> tasks;
  for (int i = 2; i < argc; i++) {
    argv_sum.append(argv[i]);
    argv_sum.append(" ");
  }
  // boost split string!
  boost::split(tasks, argv_sum, boost::is_any_of(","));
  // File entry
  ofstream todo_file("/tmp/todo", ios::app);
  if(!todo_file.is_open()){
    cerr << "No file found." << endl;
    exit(1);
  } else{
    for (int i = 0; i < tasks.size(); i++) {
      todo_file << tasks[i] << '\n';
    }
  }
  todo_file.close();
}


void Remove(int argc, const char* argv[]){
  vector<string> del_id_str;
  vector<int> del_id;
  string argv_sum;
  for (int i = 2; i < argc; i++) {
    argv_sum.append(argv[i]);
  }
  boost::split(del_id_str, argv_sum, boost::is_any_of(","));
  for (int i = 0; i < del_id_str.size(); i++) {
    if(int tmp = std::stod(del_id_str[i]))
      del_id.push_back(tmp);
    else{
      std::cout << "Remove only accept INTEGER as argument" << std::endl;
      return;
    }
  }
  ofstream temp_todo_file("/tmp/todo.tmp");
  ifstream todo_file("/tmp/todo");
  if(!todo_file.is_open()){
    cerr << "No file found." << endl;
    exit(1);
  }
  string task_elem;
  int id = 1; // re-align the indexes
  vector<int>::iterator it;
  while(getline(todo_file, task_elem)){
    it = find(del_id.begin(), del_id.end(), id++);
    if(it == del_id.end())  // not found and reserve.
      temp_todo_file << task_elem + '\n';
    else  // not found and delete
      std::cout << "Deleted task: " << task_elem << std::endl;
  }
  temp_todo_file.close();
  todo_file.close();
  if(rename("/tmp/todo.tmp", "/tmp/todo")){
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
  else if(string(argv[1]) == "-v" or string(argv[1]) == "--version")  mode = 6;
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
    case 6:
      std::cout << "TODO - a useful terminal tool" << std::endl;
      std::cout << "version: 1.0.0, released 09/28/2014" << std::endl;
      break;
  }

  return 0;
}
