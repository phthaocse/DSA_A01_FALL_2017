/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
#include<cstdlib>
#define ID_MAX_LENGTH   10

typedef struct NinjaID{
	char ID[ID_MAX_LENGTH];
	 NinjaID(char* str) {
	   strncpy(ID, str,ID_MAX_LENGTH - 1);
	}
}NinjaID_t;

//check Id if exist
bool checkID(char* ID, L1List<NinjaID_t>& ninjaid){
	L1Item<NinjaID_t>* pHead_id = ninjaid.getHead();
	while(pHead_id){
		if(strcmp(ID,pHead_id->data.ID) == 0) return true;
		pHead_id = pHead_id->pNext;
	}
	return false;
}

//get ID from events code
char* getID(char* events){
	char* id = new char();
	if(strlen(events) == 5){
		for(int i = 0; i < 4; i++){
			id[i] = events[i+1];
		}
	}
	else{
		for(int i = 0; i < 4; i++){
			id[i] = events[i+2];
		}
	}
	id[4] = '\0';
	return id;
}

// return true if distance>5
bool checkDistance(double lat1d, double lon1d, double lat2d, double lon2d){
	if((distanceEarth(lat1d, lon1d, lat2d,  lon2d)*1000)>5)return true; // don vi km->m
	else return false;
}

bool findID(L1Item<NinjaInfo_t>* nListHead, char* id,L1Item<NinjaInfo_t>*& pResult){
	L1Item<NinjaInfo_t>* pHead_info = nListHead;
	while(pHead_info){
		if(strcmp(pHead_info->data.id,id) == 0){
			pResult = pHead_info;
			return true;
		}
		pHead_info = pHead_info->pNext;
	}
	pResult = pHead_info;
	return false;
}

L1List<NinjaInfo_t> createListID(L1List<NinjaInfo_t>&  nList, char*ID)
{
	L1List<NinjaInfo_t> ListID;
	L1Item<NinjaInfo_t>* pInfo = nList.getHead();
	if(findID(pInfo,ID,pInfo)){
		ListID.push_back(pInfo->data);
	}
	while(findID(pInfo->pNext,ID,pInfo)){
		ListID.push_back(pInfo->data);
	}
	return ListID;
}


bool findNextStop(L1Item<NinjaInfo_t>* pID,L1Item<NinjaInfo_t>*& pResult ){
	if(pID == NULL) return false;
	L1Item<NinjaInfo_t>* p1 = pID;
	L1Item<NinjaInfo_t>* p2 = pID->pNext;
	bool b = true;
	while(b)
	{
		if(p1 == NULL || p2 ==NULL){ b = false;}
		else if(checkDistance(p1->data.latitude,p1->data.longitude,p2->data.latitude,p2->data.longitude)){
			p1 = p1->pNext;
			p2 = p2->pNext;
		}
		else{
			pResult = p2;
			b = false;
			return true;
		}
	}
	return false;
}

bool findNextMove(L1Item<NinjaInfo_t>* pID_stop,L1Item<NinjaInfo_t>*& pResult ){
	if(pID_stop == NULL) return false;
	L1Item<NinjaInfo_t>* p1 = pID_stop;// diem dang dung
	L1Item<NinjaInfo_t>* p2 = pID_stop->pNext;
	bool b = true;
	while(b)
	{
		if(p1 == NULL || p2 ==NULL){ b = false;}
		else if(!checkDistance(p1->data.latitude,p1->data.longitude,p2->data.latitude,p2->data.longitude)){
			p2 = p2->pNext;
		}
		else{
			pResult = p2;
			b = false;
			return true;
		}
	}
	return false;
}

void processEvent_0(void* pGData){
	cout <<"0: ";
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
	cout << "1: " << nList.getHead()->data.id << endl;
}

void processEvent_2(L1List<NinjaInfo_t>& nList){
	cout <<"2: " << nList.getLast()->data.id <<endl;
}

void processEvent_3(L1List<NinjaID_t>& ninjaid){
	unsigned int size;
	size = ninjaid.getSize();
	cout <<"3: "<<size<<endl;
}

void processEvent_4(L1List<NinjaID_t>& ninjaid){
	char *max = ninjaid.getHead()->data.ID;
	L1Item<NinjaID_t>* pHead_id = ninjaid.getHead();
	while(pHead_id){
		if(strcmp(pHead_id->data.ID,max) > 0) max = pHead_id->data.ID;
		pHead_id = pHead_id->pNext;
	}
	cout <<"4: "<<max<<endl;
}

void processEvent_5(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1Item<NinjaInfo_t>* pInfo1;
	findID(nList.getHead(),ID,pInfo1);// lay con tro khi phat hien ID lan dau
	L1Item<NinjaInfo_t>* pInfo2;
	findID(pInfo1->pNext,ID,pInfo2);// lay con tro khi thay ID lan ke tiep

	// neu khoang cach 2 lan duoi 5 tiep tuc tim lan ke tiep xuat hien ID
	bool b = true;
	while(b)
	{
		if(!checkDistance(pInfo1->data.latitude,pInfo1->data.latitude,pInfo2->data.latitude,pInfo2->data.latitude))
		{
			if(!findID(pInfo2->pNext,ID,pInfo2)){cout << "Ninja khong di chuyen";b = false;}
		}
		else{
			char* time = new char();
			cout << "5: ";
			strPrintTime(time,pInfo2->data.timestamp);
			cout << time << endl;
			b = false;
		}
	}

}


void processEvent_6(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1Item<NinjaInfo_t>* pIf1;// luon la diem hien tai
	L1Item<NinjaInfo_t>* pIf2;// luon la diem ke tiep
	L1List<NinjaInfo_t> ListID = createListID(nList,ID);
	 pIf1 = ListID.getHead();

	// tim lan dau tien ninja di chuyen
	findNextMove(pIf1,pIf2);
	pIf1 = pIf2; // gan ve diem hien tai

	L1List<NinjaInfo_t> freezeStt;// List luu cac lan dung lai
	bool status = true; // trang thai ninja true = dang di chuyen, false = dang dung lai
	bool b = true;
	while(b){
		if(status){
			if(findNextStop(pIf1,pIf2)){
				freezeStt.push_back(pIf2->data);
				status = false;
				pIf1 = pIf2;
			}
			else b = false;
		}
		else{
			if(findNextMove(pIf1,pIf2)){
				status = true;
				pIf1 = pIf2;
			}
			else b = false;
		}
	}

	char* time = new char();
	cout <<"6: ";
	strPrintTime(time,freezeStt.getLast()->data.timestamp);
	cout << time <<endl;
}


void processEvent_7(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1Item<NinjaInfo_t>* pIf1;// luon la diem hien tai
	L1Item<NinjaInfo_t>* pIf2;// luon la diem ke tiep
	L1List<NinjaInfo_t> ListID = createListID(nList,ID);
	 pIf1 = ListID.getHead();

	// tim lan dau tien ninja di chuyen
	findNextMove(pIf1,pIf2);
	pIf1 = pIf2; // gan ve diem hien tai

	L1List<NinjaInfo_t> freezeStt;// List luu cac lan dung lai
	bool status = true; // trang thai ninja true = dang di chuyen, false = dang dung lai
	bool b = true;
	while(b){
		if(status){
			if(findNextStop(pIf1,pIf2)){
				freezeStt.push_back(pIf2->data);
				status = false;
				pIf1 = pIf2;
			}
			else b = false;
		}
		else{
			if(findNextMove(pIf1,pIf2)){
				status = true;
				pIf1 = pIf2;
			}
			else b = false;
		}
	}
	int size = freezeStt.getSize();
	cout << "7: "<< size <<endl;
}

void processEvent_8(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1List<NinjaInfo_t> ListID = createListID(nList,ID);
	L1Item<NinjaInfo_t>* pInfo = ListID.getHead();
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

	int i;
	char s[2];

	if(strlen(event.code) == 1 || strlen(event.code) == 5){
		strncpy(s,event.code,1);
		i = atoi(s);
	}
	else if(strlen(event.code) == 2 || strlen(event.code) == 6){
		strncpy(s,event.code,2);
		i = atoi(s);
	}
	else{
		strncpy(s,event.code,2);
		i = atoi(s);
	}


	//Xu ly events
	switch(i){
	case 0:
		processEvent_0(pGData); break;
	case 1:
		processEvent_1(nList); break;
	case 2:
		processEvent_2(nList); break;
	case 3:
		processEvent_3(ninjaid); break;
	case 4:
		processEvent_4(ninjaid); break;
	case 5:
		//char* id = getID(event.code);
		if(!checkID(getID(event.code),ninjaid)) cout << "-1" <<endl;
		else{
			processEvent_5(nList,event.code);
		}break;
	case 6:
		if(!checkID(getID(event.code),ninjaid)) cout << "-1" <<endl;
		else{
			processEvent_6(nList,event.code);
		}break;
	case 7:
		if(!checkID(getID(event.code),ninjaid)) cout << "-1" <<endl;
		else{
			processEvent_7(nList,event.code);
		}break;
	}

	//
    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    return true;
}



