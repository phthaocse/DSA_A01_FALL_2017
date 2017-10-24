/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
#define ID_MAX_LENGTH   10

bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList,void* pGData)  {
    // TODO: Your code comes here

    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    return true;
}


void processEvent_0(){

}

void processEvent_1(L1List<NinjaInfo_t>& nList){
	cout << "1:" << nList.getHead()->data.id << endl;
}

void processEvent_2(L1List<NinjaInfo_t>& nList){
	cout <<"2:" << nList.getLast()->data.id <<endl;
}

void processEvent_3(L1List<NinjaInfo_t>& nList){
	L1List<char[ID_MAX_LENGTH]>* ninjaid = new L1List<char[ID_MAX_LENGTH]>();
}

