#include <iostream>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

ifstream input("pss1.txt");
string line,str=" ";
char try1[8];
int tam=0;
time_t start,end;
CryptoPP::SHA1 sha1;

int main()
{
	JMP:
	while(getline(input,line)){														//get the lines from the .txt
		time (&start);																//start the timer as soon as there is a target hash
		while(true){
			for(int p=32;p<127;p++){												//go through characters in the last position
				if(tam>=7){
					try1[7]=p;														//change de value of the last position
				}
				for(int o=32;o<127;o++){											//go through characters in the 7th position
					if(tam>=6){
						try1[6]=o;													//change de value of the 7th position
					}
					for(int n=32;n<127;n++){										//go through characters in the 6th position
						if(tam>=5){
							try1[5]=n;												//change de value of the 6th position
						}
						for(int m=32;m<127;m++){									//go through characters in the 5th position
							if(tam>=4){
								try1[4]=m;											//change de value of the 5th position
							}
							for(int l=32;l<127;l++){								//go through characters in the 4th position
								if(tam>=3){
									try1[3]=l;										//change de value of the 4th position
								}
								for(int k=32;k<127;k++){							//go through characters in the 3rd position
									if(tam>=2){
										try1[2]=k;									//change de value of the 3rd position
									}
									for(int j=32;j<127;j++){						//go through characters in the 2nd position
										if(tam>=1){
											try1[1]=j;								//change de value of the 2nd position
										}
										for(int i=32;i<127;i++){								//go through characters in the 1st position
												try1[0]=i;										//change the 1st position
												str=try1;										//convert from char array to string
												//cout<<str<<endl;
												string hash;
												CryptoPP::StringSource(str, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
												//cout<<hash<<endl;


												if(hash==line){				//compare the generated has with the target one
													time (&end);								//if they are equal print, stop timer, and go to the next password
													double dif = difftime (end,start);
													cout<<"Password: "<<str<<" Time: "<<dif<<" s"<<endl;
													cout<<"Original: "<<line<<endl;
													cout<<"Cracked:  "<<hash<<endl<<endl;
													tam=0;
													goto JMP;
												}
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

	return 0;
}
