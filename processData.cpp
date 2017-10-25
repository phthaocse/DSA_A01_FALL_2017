/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
#define ID_MAX_LENGTH   10

typedef struct NinjaID{
	char ID[ID_MAX_LENGTH];
	 NinjaID(char* str) {
	   strncpy(ID, str,ID_MAX_LENGTH - 1);
	}
}NinjaID_t;


bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList,void* pGData)  {
    // TODO: Your code comes here
	//create List to store ninjaid
	L1List<NinjaID_t> ninjaid;
	L1Item<NinjaID_t>* pHead_id = ninjaid.getHead();// lay con tro head cua list id
	L1Item<NinjaID_t>* temp_id = pHead_id;
	L1Item<NinjaID_t>* pLast_id = pHead_id;//khoi tao con tro last

	L1Item<NinjaInfo_t>* pHead = nList.getHead();// lay con tro head cua list ninjainfo nList
	L1Item<NinjaInfo_t>* temp_info = pHead;
	//add id tu du lieu vao list id
	while(temp_info){
		while(temp_id){
			if(strcmp(temp_info->data.id,temp_id->data.ID) == 0) break;
			temp_id = temp_id->pNext;
		}
		if(temp_id == NULL){
			NinjaID_t id(temp_info->data.id);// luu tam id kieu ninjaid
			pLast_id = ninjaid.pushBack(id,pLast_id);
		}
		temp_info = temp_info->pNext;
	}




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

void processEvent_3(L1List<NinjaID_t>& ninjaid){
	unsigned int size;
	size = ninjaid.getSize();
	cout <<"3:"<<size<<endl;
}


