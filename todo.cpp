#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include "utils/color.hpp"

using namespace std;

class todo{
 private:
   vector<string> info;
   int option;
 public:
   todo(int, const char*[]);
   void driver();
   ~todo();
   void ShowUsage();
   void Add();
   void Remove();
   void Show();
};


todo::todo(int n_par, const char* str_par[]){
  // option setting
  if (n_par < 2) {
    option = 0;
    return;
  }
  if(string(str_par[1]) == "-s" or string(str_par[1]) == "--show")
    option = 1;
  else if(string(str_par[1]) == "-a" or string(str_par[1]) == "--add")
    option = 2;
  else if(string(str_par[1]) == "-r" or string(str_par[1]) == "--remove")
    option = 3;
  else if(string(str_par[1]) == "-h" or string(str_par[1]) == "--help")
    option = 4;
  else if(string(str_par[1]) == "-cl" or string(str_par[1]) == "--clear")
    option = 5;
  else if(string(str_par[1]) == "-v" or string(str_par[1]) == "--version")
    option = 6;
  else option = 0;

  // task parsing
  string str_par_sum;
  for (int i = 2; i < n_par; i++) {
    str_par_sum.append(str_par[i]);
    str_par_sum.append(" ");
  }
  // if all white spaces of str_par_sum
  if (str_par_sum.size() == 0) {
    // Input is empty.
    return;
  }
  // boost split string!
  boost::split(info, str_par_sum, boost::is_any_of(","));
}


todo::~todo() {}


void todo::driver(){
  switch(option){
    case 0:
      ShowUsage();
      break;
    case 1:
      Show();
      break;
    case 2:
      Add();
      break;
    case 3:
      Remove();
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
    default:
      break;
  }

}

void todo::ShowUsage(){ // Funtion to show usages of todo.
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


void todo::Show(){
  ifstream todo_file("/tmp/todo");
  int cnt = 0;
  string temp;
  std::cout << std::endl;
  std::cout << "**********************************************************" << std::endl;
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
  std::cout << "**********************************************************" << std::endl;
  std::cout << std::endl;
}


void todo::Add(){
  // File entry
  ofstream todo_file("/tmp/todo", ios::app);
  if(!todo_file.is_open()){
    cerr << "No file found." << endl;
    exit(1);
  } else{
    for (int i = 0; i < info.size(); i++) {
      todo_file << info[i] << '\n';
    }
  }
  todo_file.close();
}


void todo::Remove(){
  std::vector<int> del_id;
  for (int i = 0; i < info.size(); i++) {
    if(int tmp = std::stod(info[i]))
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
  todo td(argc, argv);
  td.driver();
  return 0;
}
