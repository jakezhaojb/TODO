#ifndef _PROC_HPP_
#define _PROC_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

bool endswith(const string& str, const string& key){
  return str.rfind(key) == str.length() - key.length();
}


// Search objective string in a vector<string>
vector<int> search(vector<string> a, string b){
  std::vector<int> res;
  if(endswith(b, " "))
    b.erase(b.end()-1);
  if (a.empty()) 
    return vector<int>(0);
  for (int i = 0; i < a.size(); i++) {
    if (a[i].find(b) != string::npos)
      res.push_back(i);
  }
  return res;
}

template<typename T>
void reorder(vector<T>& a, const vector<int>& idx){
  assert(a.size() == idx.size());
  vector<T> b;
  for (int i = 0; i < a.size(); i++) {
    b.push_back(a[idx[i]]);
  }
  a.assign(b.begin(), b.end());
}


#endif
