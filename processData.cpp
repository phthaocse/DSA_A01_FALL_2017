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
	L1List<NinjaInfo_t> ninjaid;
	L1Item<NinjaInfo_t>* pHead_id = ninjaid.getHead();// lay con tro head cua list id
	L1Item<NinjaInfo_t>* temp = pHead_id;
	L1Item<NinjaInfo_t>* pHead = nList.getHead();// lay con tro head cua list ninjainfo nList
	unsigned int size;
	while(pHead){
		while(temp){
			if(strcmp(pHead->data.id,temp->data.id) == 0) break;
			temp = temp->pNext;
		}
		if(temp == NULL) ninjaid.push_back(pHead->data);
		pHead = pHead->pNext;
	}
	size = ninjaid.getSize();
	cout <<"3:"<<size<<endl;
}

