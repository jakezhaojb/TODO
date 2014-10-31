#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include "utils/disp.hpp"
#include "utils/prio.hpp"
#include "utils/proc.hpp"

using namespace std;

class todo{
 private:
   string str_par_sum;  // input string concatenated.
   vector<string> task;
   vector<string> Dtask;
   vector<int> prio;
   int option;

   void ShowUsage();
   void Add();
   void Remove();
   void Show();
   vector<int> LoadSort();
   void LoadDialy();
   void Search();

 public:
   todo(int, const char*[]);
   void driver();
   ~todo();
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
  else if(string(str_par[1]) == "-i" or string(str_par[1]) == "--index")
    option = 7;
  else option = 0;

  // task parsing
  for (int i = 2; i < n_par; i++) {
    str_par_sum.append(str_par[i]);
    str_par_sum.append(" ");
  }
  // if all white spaces of str_par_sum
  if (str_par_sum.size() == 0) {
    // Input is empty.
    return;
  }
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
      if( remove("/Users/Shared/todo/todo") )
        std::cout << "Permission denied: Can't clear all tasks." << std::endl;
      std::cout << "All tasks cleared." << std::endl;
      break;
    case 6:
      std::cout << "TODO - a useful terminal tool" << std::endl;
      std::cout << "version: 1.0.0, released 09/28/2014" << std::endl;
      break;
    case 7:
      Search();
    default:
      break;
  }

}


void todo::ShowUsage(){ // Funtion to show usages of todo.
   std::cout << "TODO Usage:" << std::endl;

   std::cout << setw(60) << left << "  -a --add <task> --p <priority>"
             << setw(50) << "Add a new TODO task with a priority code." << endl
             << setw(60) << left << " "
             << setw(50) << "Default priority code is 1(lowest)." << endl;
   std::cout << setw(60) << left << "  -a --add --d <task>"
             << setw(50) << "Add a dialy task" << endl << endl;
   std::cout << setw(60) << left << "  -r --remove"
             << setw(50) << "Remove a finished work by its ID" << endl << endl;
   std::cout << setw(60) << left << "  -s --show <priority>"
             << setw(50) << "Show your worklist" << endl
             << setw(60) << left << ""
             << setw(50) << "Default setting shows entire todo list." << endl << endl;
   std::cout << setw(60) << left << "  -v --version"
             << setw(50) << "Display version" << endl << endl;
   std::cout << setw(60) << left << "  -h --help"
             << setw(50) << "Display Usage" << endl << endl;
   std::cout << setw(60) << left << "  -cl --clear"
             << setw(50) << "Clear all tasks" << endl << endl;
}

void todo::LoadDialy(){
  ifstream Dtask_file("/Users/Shared/todo/Dtodo");
  string tmp;
  if (Dtask_file.is_open()) {
    while(getline(Dtask_file, tmp)){
      Dtask.push_back(tmp);
    }
  }
  Dtask_file.close();
}

vector<int> todo::LoadSort(){
  ifstream task_file("/Users/Shared/todo/todo");
  ifstream prio_file("/Users/Shared/todo/prio");
  string tmp;
  // task_file reading
  if(task_file.is_open()){
    while (getline(task_file, tmp)){
      task.push_back(tmp);
    }
  } else{
    cerr << "Task file not exist." << endl;
    exit(1);
  }
  task_file.close();
  // prio file reading
  if(prio_file.is_open()){
    while (getline(prio_file, tmp)){
      prio.push_back(std::stod(tmp));
    }
  } else{
    cerr << "Priority file not exist." << endl;
    exit(1);
  }
  prio_file.close();
  // align
  vector<int> prio_idx;
  for (int i = 0; i < prio.size(); i++) {
    prio_idx.push_back(i);
  }
  sort(prio_idx.begin(), prio_idx.end(),
       [this](int i1, int i2) {return prio[i1] > prio[i2];} );
  return prio_idx;
}


void todo::Show(){
  vector<int> prio_idx = LoadSort();
  LoadDialy();
  vector<int> prio_set;
  vector<string> info;

  // reorder task and prio as prio_idx
  reorder<string>(task, prio_idx);
  reorder<int>(prio, prio_idx);

  bool prio_output_flag = false;
  int prio_tmp = -1;

  boost::split(info, str_par_sum, boost::is_any_of(","));
  if (info.size() == 1 && info[0] == "") {
    prio_output_flag = true;
    for (int i = 1; i < 7; i++) {  // priority code
      prio_set.push_back(i);  // If "-s", print whole todo list
    }
  } else {  // showing tasks of specific priority codes
      for (int i = 0; i < info.size(); i++) 
        prio_set.push_back(std::stoi(info[i]));
  }
  // print out
  vector<int> idx;
  vector<string> task_to_show;
  vector<int> prio_to_show;
  for (int i = 0; i < task.size(); i++) {
    if (find(prio_set.begin(), prio_set.end(), prio[i]) == prio_set.end())
      continue;
    task_to_show.push_back("[" + to_string(i+1) + "] " + task[i]);
    prio_to_show.push_back(prio[i]);
    idx.push_back(i);
  }
  for (int i = 0; i < Dtask.size(); i++) {
    Dtask[i] = "[" + to_string(i+1) +  "] " + Dtask[i];
  }
  DoubleColumnPrint(task_to_show, Dtask, prio_to_show);
}


void todo::Search(){
  std::vector<int> prio_idx = LoadSort();
  std::vector<int> s;
  // reorder task and prio as prio_idx
  reorder<string>(task, prio_idx);
  reorder<int>(prio, prio_idx);
  s = search(task, str_par_sum);
  for (int i = 0; i < s.size(); i++) {
    std::cout << "[" << s[i]+1 << "]" << " ";
    ColorPrint(task[s[i]], prio[s[i]]);
    std::cout << std::endl;
  }
}


void todo::Add(){
  // boost split string!
  vector<string> info;
  string task_elem;
  int prio_elem;
  boost::split(info, str_par_sum, boost::is_any_of(","));
  // Add tasks and categorize by theri prio code
  for (int i = 0; i < info.size(); i++) {
    trim(info[i]);
    if (!proc_info(task_elem, prio_elem, info[i]) ) {
      std::cout << "Low priority set." << std::endl;
    }
    task.push_back(task_elem);
    prio.push_back(prio_elem);
  }
  // File entry
  ofstream task_file("/Users/Shared/todo/todo", ios::app);
  ofstream prio_file("/Users/Shared/todo/prio", ios::app);
  ofstream Dtask_file("/Users/Shared/todo/Dtodo", ios::app);
  ofstream Dprio_file("/Users/Shared/todo/Dprio", ios::app);
  if (task.size() != prio.size()) {
    std::cout << "Tasks and Priority codes are not of same dim." << std::endl;
  }
  for (int i = 0; i < task.size(); i++) {
    if (prio[i] == 99) {
      Dtask_file << task[i] << '\n';
      Dprio_file << prio[i] << '\n';
    } else {
      task_file << task[i] << '\n';
      prio_file << prio[i] << '\n';
    }
  }
  task_file.close();
  prio_file.close();
  Dtask_file.close();
  Dprio_file.close();
}


void todo::Remove(){
  int pos_d = str_par_sum.find("--d");
  vector<string> del_id_set, del_id_set_dialy;
  if (pos_d != string::npos){
    string tmp, tmpD;
    tmp = str_par_sum.substr(0, pos_d-1);
    tmpD = str_par_sum.substr(pos_d+3);
    boost::split(del_id_set, tmp, boost::is_any_of(","));
    boost::split(del_id_set_dialy, tmpD, boost::is_any_of(","));
  } else{
    boost::split(del_id_set, str_par_sum, boost::is_any_of(","));
  }
  // prepare deleting ID.
  std::vector<int> del_id, del_id_dialy;
  for (int i = 0; i < del_id_set.size(); i++) {
    try{
      int tmp = std::stod(del_id_set[i]);
      del_id.push_back(tmp);
    }
    catch(...){
      //std::cout << "Remove only accept INTEGER as argument" << std::endl;
    }
  }
  for (int i = 0; i < del_id_set_dialy.size(); i++) {
    try{
      int tmp = std::stod(del_id_set_dialy[i]);
      del_id_dialy.push_back(tmp);
    }
    catch(...){
      //std::cout << "Remove only accept INTEGER as argument" << std::endl;
    }
  }
  // File entry
  ofstream temp_task_file("/Users/Shared/todo/todo.tmp");
  ofstream temp_prio_file("/Users/Shared/todo/prio.tmp");
  ofstream temp_task_file_dialy("/Users/Shared/todo/Dtodo.tmp");
  vector<int> prio_idx = LoadSort();
  LoadDialy();
  // Deleting and write in new files.
  vector<int>::iterator it;
  vector<int>::iterator itD;
  for (int i = 0; i < task.size(); i++) {
    it = find(del_id.begin(), del_id.end(), i+1);
    if (it == del_id.end()) { // not found and reserve
      temp_task_file << task[prio_idx[i]] + "\n";
      temp_prio_file << to_string(prio[prio_idx[i]]) + "\n";
    } else  // found and delete
      std::cout << "Deleted task: " << task[prio_idx[i]] << std::endl;
  }
  for (int i = 0; i < Dtask.size(); i++) {
    itD = find(del_id_dialy.begin(), del_id_dialy.end(), i+1);
    if (itD == del_id_dialy.end()) {
      temp_task_file_dialy << Dtask[i] + "\n";
   } else
     std::cout << "Deleted task: " << Dtask[i] << std::endl;
  }
  temp_task_file.close();
  temp_prio_file.close();
  temp_task_file_dialy.close();
  if(rename("/Users/Shared/todo/todo.tmp", "/Users/Shared/todo/todo") || 
     rename("/Users/Shared/todo/prio.tmp", "/Users/Shared/todo/prio") ||
     rename("/Users/Shared/todo/Dtodo.tmp", "/Users/Shared/todo/Dtodo")){
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
