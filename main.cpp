#include <iostream>
#include <cstring>
#include <cstdlib>
#include "classes.h"
#include <fstream>
#include <sstream>

using namespace std;



int main(int argc,char **argv) {
	graph mygraph(128);
	vertex *v;
	string input,s1,s2,s3,s4,s5,out_file_name,in_file_name,temp;
	int w,res;
	bool flag_input=false,flag_output=false;
	
	for (int i=0; i<argc; i++) {
		temp = argv[i];
		if (temp == "-i") {
			flag_input = true;
			in_file_name = argv[i+1];
		}
		if (temp == "-o") {
			flag_output = true;
			out_file_name = argv[i+1];
		}
	}
	if (flag_input == true) {
		
		ifstream inputfile(in_file_name.c_str());
		if (inputfile.is_open() == false) {
			cout <<"File error."<<endl;
		}
		else {
			while(inputfile >> s1 >> s2 >> w) {
				mygraph.insert_edge(s1,s2,w);
			}
			inputfile.close();
		}	
	}
	while (true) {
		s1=s2=s3=s4=s5="";
		getline (cin,input);
		istringstream iss (input);
		iss >> s1;
		if (s1 == "i") {
			iss >> s2;
			if (s2 == "") {
				cout <<"Invalid input"<<endl;
			}
			else {
				v = mygraph.insert_vertex(s2);
				if (v == NULL) {
					cout <<"Node |"<<s2<<"|"<<" Exists"<<endl;
				}
				else {
					cout <<"Inserted "<<"|"<<s2<<"|"<<endl;
				}
			}
		}
		else if (s1 == "n") {
			iss >>s2>>s3>>s4;
			if (s2 == "" || s3 == ""|| s4== ""||s2 == "") {
				cout <<"Invalid input"<<endl;
			}
			else {
				mygraph.insert_edge(s2,s3,atoi(s4.c_str()));
				cout <<"Inserted |"<<s2<<"|"<<"->"<<s4<<"->"<<"|"<<s3<<"|"<<endl;
			}
		}
		else if (s1 == "d") {
			iss >> s2;
			if (s2 == "") {
				cout <<"Invalid input"<<endl;
			}
			else {
				res = mygraph.delete_vertex(s2);
				if (res == -1) {
					cout <<"Node |"<<s2<<"|"<<" does not exist - abort-d;"<<endl;
				}
				else {
					cout <<"Deleted "<<"|"<<s2<<"|"<<endl;
				}

			}
		}
		else if (s1 == "l") {
			iss >>s2>>s3>>s4;
			if (s2 == "" || s3 == ""|| s4=="") {
				cout <<"Invalid input"<<endl;
			}
			else {
				res = mygraph.delete_edge(s2,s3,atoi(s4.c_str()));
				if (res == -1) {
					cout <<"|"<<s2<<"|"<<" does not exist - abort-l;"<<endl;
				}
				else if (res == -2) {
					cout <<"|"<<s3<<"|"<<" does not exist - abort-l;"<<endl;
				}
				else if (res == -3) {
					cout<<"|"<<s2<<"|"<<"->"<<s4<<"->"<<"|"<<s3<<"|"
						<<"does not exist - abort-l"<<endl;
				}
				else {
					cout<<"Del-vertex |"<<s2<<"|"<<"->"<<s4<<"->"
						<<"|"<<s3<<"|"<<endl;
				}
			}
		}
		else if (s1 == "m") {
			iss >>s2>>s3>>s4>>s5;
			if (s2 == "" || s3 == ""|| s4=="" || s5=="") {
				cout <<"Invalid input"<<endl;
			}
			else {
				res = mygraph.modify(s2,s3,atoi(s4.c_str()),atoi(s5.c_str()));
				if (res == -1) {
					cout <<"|"<<s2<<"|"<<" does not exist"<<endl;
				}
				else if (res == -2) {
					cout <<"|"<<s3<<"|"<<" does not exist"<<endl;
				}
				else if (res == -3) {
					cout<<"|"<<s2<<"|"<<"->"<<s4<<"->"<<"|"<<s3<<"|"
						<<"does not exist"<<endl;
				}
				else {
					cout<<"Mod-vertex |"<<s2<<"|"<<"->"<<s5
						<<"->"<<"|"<<s3<<"|"<<endl;
				}
			}
		}
		else if (s1 == "r") {
			iss >> s2;
			if (s2 == "") {
				cout <<"Invalid input"<<endl;
			}
			else {
				res = mygraph.receiving(s2);
				if (res == -1) {
					cout <<"|"<<s2<<"|"<<" does not exist - abort-r;"<<endl;
				}
				else if (res == 0) {
					cout <<"No-rec-edges "<<s2<<endl;
				}
			}
		}
		else if (s1 == "c") {
			iss >> s2;
			if (s2 == "") {
				cout <<"Invalid input"<<endl;
			}
			else {
				res = mygraph.circle_find(s2);
				if (res == -1) {
					cout <<"|"<<s2<<"|"<<" does not exist - abort-c;"<<endl;
				}
				else if (res == 0) {
					cout <<"No-circle-found |"<<s2<<"|"<<endl;
				}
			}
		}
		else if (s1 == "f") {
			iss >>s2>>s3;
			if (s2 == "" || s3 == "") {
				cout <<"Invalid input"<<endl;
			}
			else {
				res = mygraph.find_circles(s2,atoi(s3.c_str()));
				if (res == -1) {
					cout <<"|"<<s2<<"|"<<" does not exist - abort-f;"<<endl;
				}
				else if (res == 0) {
					cout <<"No-circle-found involving |"<<s2<<"| "<<s3<<endl;
				}
			}
		}
		else if (s1 == "t") {
			iss >>s2>>s3>>s4;
			if (s2 == "" || s3 == ""|| s4=="") {
				cout <<"Invalid input"<<endl;
			}
			else {
				res = mygraph.traceflow(s2,s3,atoi(s4.c_str()));
				if (res == -1) {
					cout <<"|"<<s2<<"|"<<" does not exist - abort-l;"<<endl;
				}
				else if (res == -2) {
					cout <<"|"<<s3<<"|"<<" does not exist - abort-l;"<<endl;
				}
				else if (res == 0) {
					cout<<"No-trace from |"<<s2<<"|"<<" to "
						<<"|"<<s3<<"|"<<endl;
				}
			}
		}
		else if (s1 == "e") {
			cout <<"exit program"<<endl;
			break;
		}
		else {
			cout <<"Invalid input"<<endl;
		}
		cout <<endl;
	}
	if (flag_output == true) {
		ofstream myfile;
		myfile.open(out_file_name.c_str());
		mygraph.print_to_file(&myfile);
		myfile.close();
	}
	return 0;
}