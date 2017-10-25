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



void processEvent_0(void* pGData){
	cout <<"0:";
	// xu ly in ra man hinh cac events
	L1List<ninjaEvent_t>* HeadList = (L1List<ninjaEvent_t>*) pGData;
	L1Item<ninjaEvent_t>* pHead = HeadList->getHead();
	while(pHead){
		cout << pHead->data.code << " ";
		pHead = pHead->pNext;
	}
	cout <<endl;
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




bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList,void* pGData)  {

    // TODO: Your code comes here
	//create List to store ninjaid
	L1List<NinjaID_t> ninjaid;
	L1Item<NinjaID_t>* pHead_id = ninjaid.getHead();// lay con tro head cua list id

	L1Item<NinjaID_t>* pLast_id = pHead_id;//khoi tao con tro last

	L1Item<NinjaInfo_t>* pHead = nList.getHead();// lay con tro head cua list ninjainfo nList
	L1Item<NinjaInfo_t>* temp_info = pHead->pNext;
	//add id tu du lieu vao list id

	// can khoi tao cho list id chinh la id dau tien trong du lieu
	//khoi tao se giup cho phan code phia duoi chay dung vi neu khong khoi tao dieu kien if(*) luon dung
	NinjaID_t _id(nList.getHead()->data.id);// luu tam id kieu ninjaid
	pLast_id = ninjaid.pushBack(_id,pLast_id);
	L1Item<NinjaID_t>* temp_id = ninjaid.getHead();

	while(temp_info){

		while(temp_id){
			if(strcmp(temp_info->data.id,temp_id->data.ID) == 0) break;
			temp_id = temp_id->pNext;
		}
		if(temp_id == NULL){//(*)
			NinjaID_t id(temp_info->data.id);// luu tam id kieu ninjaid
			pLast_id = ninjaid.pushBack(id,pLast_id);
		}
		temp_id =  ninjaid.getHead();
		temp_info = temp_info->pNext;
	}
	string str = event.code;
	char i = str.at(0);

	//Xu ly events
	switch(i){
	case '0':
		processEvent_0(pGData); break;
	case '1':
		processEvent_1(nList); break;
	case '2':
		processEvent_2(nList); break;
	case '3':
		processEvent_3(ninjaid); break;
	}


    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    return true;
}



