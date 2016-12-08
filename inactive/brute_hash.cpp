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
#include <cstring>
#include <vector>
#include <iterator>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/whrlpool.h>

using namespace std;

const int start = 32; //32 == space ASCII
const int end = 126; //126 == ~ ASCII
const int max_size = 8; //max size of the password

//Funcao: load_hash
//Proposito: carregar a lista de hashes
//Parametros: vetor de strings que armazenara o hash
//Retorna: nada
void load_hash(vector<string>& l_hash){
  string name;
  cout<< "Name of the file containing the hash: " <<endl;
  cin>>name;


  vector<string>::iterator it;


  ifstream input(name.c_str());   //create the file stream
  string line;                    //temp line

  while(getline(input,line)){     //recieve the line
    l_hash.push_back(line);       //store the hash
  }
  for(it=l_hash.begin();it<l_hash.end();++it){
    cout<<*it<<endl;
  }

}

//Funcao: hash_crack
//Proposito: tentar fazer um brute force para crackear o hash
//Parametros: vetor de strings que armazenam os hashes
//Retorna: nada
void hash_crack(vector<string>& l_hash){

  string str=" ";
  char try1[8];
  int tam=0,done=0;
  time_t start,end;
  unsigned char digest[16];
  char string_x[10];
  vector<string>::iterator it;

  JMP:
  cout<<"foi"<<endl;
  while(l_hash.size()!=0){														//get the lines from the .txt
    //cout<<"foi"<<endl;
    time (&start);																//start the timer as soon as there is a target hash
    while(done==0){
      for(int p=start;p<=end;p++){												//go through characters in the last position
        //cout<<"aki"<<endl;
        if(tam>=7){
          try1[7]=p;														//change de value of the last position
        }
        for(int o=start;o<=end;o++){											//go through characters in the 7th position
          if(tam>=6){
            try1[6]=o;													//change de value of the 7th position
          }
          for(int n=start;n<=end;n++){										//go through characters in the 6th position
            if(tam>=5){
              try1[5]=n;												//change de value of the 6th position
            }
            for(int m=start;m<=end;m++){									//go through characters in the 5th position
              if(tam>=4){
                try1[4]=m;											//change de value of the 5th position
              }
              for(int l=start;l<=end;l++){								//go through characters in the 4th position
                if(tam>=3){
                  try1[3]=l;										//change de value of the 4th position
                }
                for(int k=start;k<=end;k++){							//go through characters in the 3rd position
                  if(tam>=2){
                    try1[2]=k;									//change de value of the 3rd position
                  }
                  for(int j=start;j<=end;j++){						//go through characters in the 2nd position
                    if(tam>=1){
                      try1[1]=j;								//change de value of the 2nd position
                    }
                    for(int i=start;i<=end;i++){								//go through characters in the 1st position
                        try1[0]=i;										//change the 1st position
                        str=try1;										//convert from char array to string

                        //MD5 crack
                        //cout<<str<<endl;

                        strcpy(string_x, str.c_str());					//convert the string to array char
                        MD5_CTX ctx;									//create the MD5 hash and store at mdString
                        MD5_Init(&ctx);
                        MD5_Update(&ctx, string_x, strlen(string_x));
                        MD5_Final(digest, &ctx);
                        char mdString[33];
                        for (int i = 0; i < 16; i++){
                          sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
                        }
                        //cout<<"PUUUUM"<<endl;
                        int pos=0;
                        for(it=l_hash.begin();it<l_hash.end();++it){
                          if(std::string(mdString)==*it){				//compare the generated has with the target one
                            time (&end);								//if they are equal print, stop timer, and go to the next password
                            double dif = difftime (end,start);
                            cout<<"Password: "<<str<<" Time: "<<dif<<" s"<<endl;
                            cout<<"Original MD5: "<<*it<<endl;
                            cout<<"Cracked:  "<<mdString<<endl<<endl;
                            l_hash.erase(l_hash.begin()+pos);
                            //done=1;
                            goto JMP;
                          }
                          pos++;
                        }

                        //SHA1 crack

                    }
                    if(tam==0){
                      tam++;
                    }
                  }
                  if(tam==1){
                    tam++;
                  }
                }
                if(tam==2){
                  tam++;
                }
              }
              if(tam==3){
                tam++;
              }
            }
            if(tam==4){
              tam++;
            }
          }
          if(tam==5){
            tam++;
          }
        }
        if(tam==6){
          tam++;
        }
      }
      if(tam==7){
        goto JMP;
        cout<<"Password bigger than 8"<<endl<<endl;			//could not find the password
      }
    }
  }
}

int main(){
  //string name;
  vector<string> hash_list;

  load_hash(hash_list);

  //cout<<"finish loading"<<endl;

  hash_crack(hash_list);
  return 0;
}
