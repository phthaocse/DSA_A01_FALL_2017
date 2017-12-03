/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"
#include<string>
#include<cstring>

/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	//TODO 
	ifstream ifile;
	ifile.open(fName);

	ninjaEvent_t temp;
	if(ifile.good())
	{
		string str;//luu cac phan khong can thiet
		bool b = true;
		while(getline(ifile,str))
		{
			istringstream ss(str);
			while( ss >> str){
				strcpy((temp.code), str.c_str());
				if(temp.code[strlen(temp.code)-1] == ';'){
					temp.code[strlen(temp.code)-1] = '\0';
					eList.push_back(temp);
					b =false;
					break;
				}
				else eList.push_back(temp);
			}
			if(b == false) break;
		}
	}
	ifile.close();
}
