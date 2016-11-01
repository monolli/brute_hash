/*
Lucas Monteiro de Oliveira
E-mail:lumonoli@hotmail.com
Felipe Regis
E-mail: felipe.regis@outlook.com
Outubro 2016
AED II - Bechmark of hashing algorithms
*/

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>

#define start = 32; //32 == space ASCII
#define end = 126; //126 == ~ ASCII
#define max_size = 8 //max size of the password

using namespace std;

void load_hash(string name, vector<string>& l_hash){
  cout<< "Name of the file containing the hash: " <<endl;
  cin>>name;

  ifstream input(name.c_str());   //create the file stream
  string line;                    //temp line

  while(getline(input,line)){     //recieve the line
    l_hash.push_back(line);       //store the hash
  }
}

void gen_string(int start, int end){
  char try1[max_size];
  for(int i = start; i <= end; i++){
    try1[]
  }
}

int main(){
  string name;
  vector<string> hash_list;

  load_hash(name,hash_list);


  return 0;
}
