/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
#include "listLib.h"
#include<cstdlib>
#include<cmath>

struct gData{
	L1List<ninjaEvent_t>* headEvent;
	L1List<NinjaID_t>* headID;
};

typedef struct NinjaTime{
	char ID[ID_MAX_LENGTH];
	double Time;
	NinjaTime(char* str, double _time) {
		   strncpy(ID, str,ID_MAX_LENGTH - 1);
		   Time = _time;
	}
}NinjaTime_t;

//check Id if exist
bool checkID(char* ID,void* pGData){
	gData* p = (gData*) pGData;
	L1List<NinjaID_t>* ninjaid = p->headID;
	L1Item<NinjaID_t>* pHead_id = ninjaid->getHead();
	while(pHead_id){
		if(strcmp(ID,pHead_id->data.ID) == 0) return true;
		pHead_id = pHead_id->pNext;
	}
	return false;
}
 //
//get ID from events code
char* getID(char* events){
	char* id = new char();
	char* tmp = new char();
	strncpy(tmp,events,2);// lay 2 ky tu dau cua eventcode
	tmp[2] = '\0';

	if(strcmp(tmp,"11") == 0){
		for(int i = 0; i < strlen(events)-2; i++){
			id[i] = events[i+2];
			id[strlen(events)-2] = '\0';
		}
	}
	else{
		for(int i = 0; i < strlen(events)-1; i++){
			id[i] = events[i+1];
			id[strlen(events)-1] = '\0';
		}
	}

	return id;
}

// return true if distance>5
bool checkDistance(double lat1d, double lon1d, double lat2d, double lon2d){
	if(fabs(distanceEarth(lat1d, lon1d, lat2d,  lon2d)*1000) > 5)return true; // don vi km->m
	else return false;
}

bool checkEvent(char* events, char*& result) {
	char** chr = new char*[6]{ "5","6","7","8","11","13" };
	for (int i = 0; i<4; i++) {
		char* tmp = new char();
		tmp[1] = '\0';
		strncpy(tmp, events,1);
		if (strcmp(tmp, chr[i]) == 0) {
			result = tmp;
			return true;
		}
	}
	for (int j = 4; j<6; j++) {
		char* tmp = new char();
		strncpy(tmp, events, 2);
		tmp[2] = '\0';
		if (strcmp(tmp, chr[j]) == 0) {
			result = tmp; return true;
		}
	}
	return false;
}

bool findID(L1Item<NinjaInfo_t>* nListHead, char* id,L1Item<NinjaInfo_t>*& pResult){
	L1Item<NinjaInfo_t>* pHead_info = nListHead;
	bool b = false;
	while(pHead_info){
		if(strcmp(pHead_info->data.id,id) == 0){
			pResult = pHead_info;
			b = true;
			return true;
		}
		else {
			if(b == true) break;
		}
		pHead_info = pHead_info->pNext;
	}
	return false;
}

L1List<NinjaInfo_t> createListID(L1List<NinjaInfo_t>&  nList, char*ID)
{
	L1List<NinjaInfo_t> ListID;
	L1Item<NinjaInfo_t>* pInfo = nList.getHead();
	L1Item<NinjaInfo_t>* pResult;

	while(findID(pInfo,ID,pResult)){
		ListID.push_back(pResult->data);
		pInfo = pResult->pNext;
	}
	return ListID;
}


bool findNextStop(L1Item<NinjaInfo_t>* pID,L1Item<NinjaInfo_t>*& pResult ){
	if(pID == NULL) return false;
	L1Item<NinjaInfo_t>* p1 = pID;
	L1Item<NinjaInfo_t>* p2 = pID->pNext;
	while(p2 != NULL){
		if(checkDistance(p1->data.latitude,p1->data.longitude,p2->data.latitude,p2->data.longitude)){
			p1 = p2;
			p2 = p2->pNext;
		}
		else{
			pResult = p1;
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
	while(p2 != NULL){
		if(!checkDistance(p1->data.latitude,p1->data.longitude,p2->data.latitude,p2->data.longitude)){
			p2 = p2->pNext;
		}
		else{
			pResult = p2;
			return true;
		}
	}
	return false;
}

// ket qua dc luu la vi tri lan cuoi dung lai truoc khi di chuyen
bool findLastStop(L1Item<NinjaInfo_t>* pID_stop,L1Item<NinjaInfo_t>*& pResult ){
	if(pID_stop == NULL) return false;
		L1Item<NinjaInfo_t>* p1 = pID_stop;// diem dang dung
		L1Item<NinjaInfo_t>* p2 = pID_stop->pNext;
		L1Item<NinjaInfo_t>* temp;
		bool b = true;
		while(p2 != NULL){
			if(!checkDistance(p1->data.latitude,p1->data.longitude,p2->data.latitude,p2->data.longitude)){
				temp = p2;
				p2 = p2->pNext;
			}
			else{
				pResult = temp;
				return true;
			}
		}
		return false;
}

double stopTime(L1List<NinjaInfo_t> listID){
	if(listID.getHead() == NULL) return 0;
	L1Item<NinjaInfo_t>* p1 = listID.getHead();
	L1Item<NinjaInfo_t>* p2;
	double time;
	bool status = false; // trang thai false la dang dung yen
	bool b = true;
	while(b){
			if(status){
				if(findNextStop(p1,p2)){
						status = false;
						p1 = p2;
				}
				else b = false;
			}
			else{
				if(findLastStop(p1,p2)){
					time += fabs(difftime(p2->data.timestamp,p1->data.timestamp));
					status = true;
					p1 = p2->pNext;
				}
				else b = false;
			}
	}
	return time;
}


void processEvent_0(void* pGData){
	cout <<"0: ";
	// xu ly in ra man hinh cac events
	gData* p = (gData*) pGData;
	L1List<ninjaEvent_t>* pList = p->headEvent;
	L1Item<ninjaEvent_t>* pHead = pList->getHead();

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

void processEvent_3(void* pGData){
	unsigned int size;
	gData* p = (gData*) pGData;
	L1List<NinjaID_t>* pList = p->headID;
	size =pList->getSize();
	cout <<"3: "<<size<<endl;
}

void processEvent_4(void* pGData){
	gData* p = (gData*) pGData;
	L1List<NinjaID_t>*  ninjaid = p->headID;
	char *max = ninjaid->getHead()->data.ID;
	L1Item<NinjaID_t>* pHead_id = ninjaid->getHead();
	while(pHead_id){
		if(strcmp(pHead_id->data.ID,max) > 0) max = pHead_id->data.ID;
		pHead_id = pHead_id->pNext;
	}
	cout <<"4: "<<max<<endl;
}

void processEvent_5(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1Item<NinjaInfo_t>* pIf1;
	L1List<NinjaInfo_t> ListID = createListID(nList,ID);
	pIf1 = ListID.getHead();
	if(findNextMove(pIf1,pIf1)){
		char* time = new char();
		strPrintTime(time,pIf1->data.timestamp);
		cout <<"5" << ID <<": "<< time <<endl;
	}
	else cout << "-2" <<endl;

}


void processEvent_6(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1Item<NinjaInfo_t>* pStop;// luon la diem dung yen
	L1Item<NinjaInfo_t>* pMove;// luon la diem di chuyen
	L1List<NinjaInfo_t> ListID = createListID(nList,ID);
	pMove = ListID.getHead();

	L1List<NinjaInfo_t> freezeStt;// List luu cac lan dung lai
	bool b = true;
	while(b){
		if(findNextStop(pMove,pStop)){
			freezeStt.push_back(pStop->data);
			if(!findNextMove(pStop,pMove)){
				b = false;
			}
		}
		else b = false;
	}

	char* time = new char();
	cout <<"6" << ID << ": ";
	strPrintTime(time,freezeStt.getLast()->data.timestamp);
	cout << time <<endl;

}


void processEvent_7(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1Item<NinjaInfo_t>* pStop;// luon la diem dung yen
	L1Item<NinjaInfo_t>* pMove;// luon la diem di chuyen
	L1List<NinjaInfo_t> ListID = createListID(nList,ID);
	pMove = ListID.getHead();

	L1List<NinjaInfo_t> freezeStt;// List luu cac lan dung lai
	bool b = true;
	while(b){
		if(findNextStop(pMove,pStop)){
			freezeStt.push_back(pStop->data);
			if(!findNextMove(pStop,pMove)){
				b = false;
			}
		}
		else b = false;
	} 
	int size = freezeStt.getSize();
	L1Item<NinjaInfo_t>* p = freezeStt.getHead();
	cout << "7"<< ID << ": " << size << endl;
}

void processEvent_8(L1List<NinjaInfo_t>& nList,char* eventcode){
	char *ID = getID(eventcode);
	L1List<NinjaInfo_t> ListID = createListID(nList,ID);
	L1Item<NinjaInfo_t>* pInfo = ListID.getHead();
	double distance = 0;
	while(pInfo->pNext){
		distance +=distanceEarth(pInfo->data.latitude,pInfo->data.longitude,pInfo->pNext->data.latitude,pInfo->pNext->data.longitude);
		pInfo = pInfo->pNext;
	}

	cout << "8" << ID << ": " << distance <<endl;
}
void processEvent_9(L1List<NinjaInfo_t>& nList,void* pGData){
	gData* p = (gData*) pGData;
	L1List<NinjaID_t>* ninjaid = p->headID;
	L1Item<NinjaID_t>* pID = ninjaid->getHead();
	double max_dis = 0;
	L1List<NinjaInfo_t> maxList; // tao list luu tru cac khoang cach max
	while(pID){
		L1List<NinjaInfo_t> ListID = createListID(nList,pID->data.ID);
		L1Item<NinjaInfo_t>* pInfo = ListID.getHead();
		double distance = 0;
		while(pInfo->pNext){
			distance +=distanceEarth(pInfo->data.latitude,pInfo->data.longitude,pInfo->pNext->data.latitude,pInfo->pNext->data.longitude);
			pInfo = pInfo->pNext;
		}
		if(distance > max_dis){
			max_dis = distance;
			if(maxList.getHead() != NULL) maxList.removeHead();//xoa max lan trc
			maxList.push_back(ListID.getHead()->data);
		}
		else if(distance == max_dis) maxList.push_back(ListID.getHead()->data);//neu bang nhau se van push de so sanh thoi gian
		pID = pID->pNext;
	}
	//tim max
	L1Item<NinjaInfo_t>* pML = maxList.getHead();
	L1Item<NinjaInfo_t>* pMax = pML;//luu node chua ID co quang duong dai nhat


	while(pML->pNext){
		if(difftime(pMax->data.timestamp,pML->pNext->data.timestamp) < 0){ //end/beginning
			pMax = pML->pNext;
		}
		pML = pML->pNext;
	}

	cout << "9: " << pMax->data.id <<endl;

}



void processEvent_10(L1List<NinjaInfo_t>& nList,void* pGData){

	gData* p = (gData*) pGData;
	L1List<NinjaID_t>* ninjaid = p->headID;
	L1Item<NinjaID_t>* pID = ninjaid->getHead();
	double max_time = 0;
	L1List<NinjaInfo_t> maxList; // tao list luu tru cac thoi gian max
	while(pID){
			L1List<NinjaInfo_t> ListID = createListID(nList,pID->data.ID);
			L1Item<NinjaInfo_t>* pMove = ListID.getHead();
			L1Item<NinjaInfo_t>* pStop;
			L1Item<NinjaInfo_t>* temp = pMove;
			//time_t timeStop;
			//time_t timeMove;
			//double sumStop = 0;//tong thoi gian dung lai
			double resultTime = 0;
			//tinh thoi gian cac lan dung lai
			bool b = true;

			while(b){
				if(findNextStop(pMove,pStop)){
					resultTime += difftime(pStop->data.timestamp,temp->data.timestamp);
					if(!findLastStop(pStop,pMove)){
						b = false;

					}
					temp = pMove;
					pMove = pMove->pNext;

				}
				else{
					resultTime += difftime(ListID.getLast()->data.timestamp,temp->data.timestamp);
					b = false;
				}
			}


			if(resultTime>max_time){
				max_time = resultTime;
				if(maxList.getHead() != NULL){
					//xoa max lan trc
					for(int i = 0; i < maxList.getSize();i++){
						maxList.removeHead();
					}
				}
				maxList.push_back(ListID.getHead()->data);
			}
				else if(resultTime  == max_time) maxList.push_back(ListID.getHead()->data);//neu bang nhau se van push de so sanh thoi gian
			pID = pID->pNext;
	}

	//tim max
		L1Item<NinjaInfo_t>* pML = maxList.getHead();
		L1Item<NinjaInfo_t>* pMax = pML;//luu node chua ID co thoi gian lau nhat
		pML = pML->pNext;

		while(pML){
			if(difftime(pMax->data.timestamp,pML->data.timestamp) < 0){ //end/beginning
				pMax = pML;
			}
			pML = pML->pNext;
		}

		cout << "10: " << pMax->data.id << endl;


}


void processEvent_11(void* pGData,char* eventcode){
	gData* p = (gData*) pGData;
	L1List<NinjaID_t>* ninjaid = p->headID;
	L1Item<NinjaID_t>* pID = ninjaid->getHead();
	L1List<NinjaID_t> LowerID;
	L1Item<NinjaID_t>* temp_lid = LowerID.getHead();
	char *ID = getID(eventcode);
	char resultID[10] ="-1";
	// tim cac ID nho hon ID duoc truyen vao
	while(pID){
		if(strcmp(ID,pID->data.ID)>0){
			 temp_lid = LowerID.pushBack(pID->data, temp_lid);
		}
		pID = pID->pNext;
	}
	//tim max trong nhung id nho hon ID
	if(LowerID.getHead() != NULL){
		strncpy(resultID,LowerID.getHead()->data.ID,strlen(LowerID.getHead()->data.ID));// khoi tao result la ID dau cua list
		resultID[strlen(LowerID.getHead()->data.ID)] ='\0';
	}
	temp_lid = LowerID.getHead();
	while(temp_lid){
		if(strcmp(temp_lid->data.ID,resultID)>0){
			strncpy(resultID,temp_lid->data.ID,strlen(temp_lid->data.ID));
			resultID[strlen(temp_lid->data.ID)] ='\0';
		}
		temp_lid = temp_lid->pNext;
	}
	//xuat ket qua
	if(strcmp(resultID,"-1") == 0) cout << "11" << ID << ":-1" <<endl;
	else cout << "11" << ID << ": " << resultID << endl;
}

void processEvent_12(L1List<NinjaInfo_t>& nList,void* pGData){
	gData* p = (gData*) pGData;
	L1List<NinjaID_t>* ninjaid = p->headID;
	L1Item<NinjaID_t>* pID = ninjaid->getHead();
	double max_time = 0;
	L1List<NinjaInfo_t> maxList; // tao list luu tru cac thoi gian max
	while(pID){
			L1List<NinjaInfo_t> ListID = createListID(nList,pID->data.ID);
			L1Item<NinjaInfo_t>* pMove = ListID.getHead();
			L1Item<NinjaInfo_t>* pStop;
			L1Item<NinjaInfo_t>* temp = pMove;
			//time_t timeStop;
			//time_t timeMove;
			//double sumStop = 0;//tong thoi gian dung lai
			double resultTime = 0;
			//tinh thoi gian cac lan dung lai
			bool b = true;

			while(b){
				if(findNextStop(pMove,pStop)){

					if(!findLastStop(pStop,pMove)){
						resultTime += difftime(ListID.getLast()->data.timestamp,pStop->data.timestamp);
						b = false;

					}
					resultTime += difftime(pMove->data.timestamp,pStop->data.timestamp);
					temp = pMove;
					pMove = pMove->pNext;

				}
				else{
					b = false;
				}
			}


			if(resultTime>max_time){
				max_time = resultTime;
				if(maxList.getHead() != NULL){
					//xoa max lan trc
					for(int i = 0; i < maxList.getSize();i++){
						maxList.removeHead();
					}
				}
				maxList.push_back(ListID.getHead()->data);
			}
				else if(resultTime  == max_time) maxList.push_back(ListID.getHead()->data);//neu bang nhau se van push de so sanh thoi gian
			pID = pID->pNext;
	}

	//tim max
		L1Item<NinjaInfo_t>* pML = maxList.getHead();
		L1Item<NinjaInfo_t>* pMax = pML;//luu node chua ID co thoi gian lau nhat
		pML = pML->pNext;

		while(pML){
			if(difftime(pMax->data.timestamp,pML->data.timestamp) < 0){ //end/beginning
				pMax = pML;
			}
			pML = pML->pNext;
		}

		cout << "12: " << pMax->data.id << endl;


}

void processEvent_14(L1List<NinjaInfo_t>& nList,void* pGData){
	gData* p = (gData*) pGData;
	L1List<NinjaID_t>* ninjaid = p->headID;
	L1Item<NinjaID_t>* pID = ninjaid->getHead();
	cout << "14: ";
	while(pID){
		L1Item<NinjaInfo_t>* pStop;// luon la diem dung yen
		L1Item<NinjaInfo_t>* pMove;// luon la diem di chuyen
		L1List<NinjaInfo_t> ListID = createListID(nList,pID->data.ID);
		pMove = ListID.getHead();
		L1List<NinjaInfo_t> point;// List luu cac lan dung lai
		L1Item<NinjaInfo_t>* last = point.getHead();
		bool b = true;
		while(b){
			if(findNextStop(pMove,pStop)){
				last = point.pushBack(pStop->data,last);
				if(!findNextMove(pStop,pMove)){
					b = false;
				}
				last = point.pushBack(pMove->data,last);
			}
			else b = false;
		}
		L1Item<NinjaInfo_t>* p = ListID.getHead();
		L1Item<NinjaInfo_t>* p2 = point.getHead();
		bool bol = true;
		while(p){
			while(p2){
				if(difftime(p->data.timestamp,p2->data.timestamp)!=0){
					if(!checkDistance(p->data.latitude,p->data.longitude,p2->data.latitude,p2->data.longitude)){
						cout << p->data.id << " ";
						bol = false;
						break;
					}
				}
				p2 = p2->pNext;
			}
			if(bol == false) break;
			p = p->pNext;
		}
		pID = pID -> pNext;
	}
	cout << endl;
	
}

bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList,void* pGData) {

    // TODO: Your code comes here
	//create List to store ninjaid



	/*L1Item<NinjaID_t>* pHead_id = ninjaid.getHead();// lay con tro head cua list id

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
	}*/

	int i;
	char* s = new char[2];

	if(strlen(event.code) == 1){
		strncpy(s,event.code,1);
		s[1] = '\0';
		i = atoi(s);
	}
	else if(strlen(event.code) == 2){
		strncpy(s,event.code,2);
		s[2] = '\0';
		i = atoi(s);
	}
	else{
		checkEvent(event.code,s);
		s[strlen(s)] = '\0';
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
		processEvent_3(pGData); break;
	case 4:
		processEvent_4(pGData); break;
	case 5:
		//char* id = getID(event.code);
		if(!checkID(getID(event.code),pGData)) cout << "-1" <<endl;
		else{
			processEvent_5(nList,event.code);
		}break;
	case 6:
		if(!checkID(getID(event.code),pGData)) cout << "-1" <<endl;
		else{
			processEvent_6(nList,event.code);
		}break;
	case 7:
		if(!checkID(getID(event.code),pGData)) cout << "-1" <<endl;
		else{
			processEvent_7(nList,event.code);
		}break;
	case 8:
		if(!checkID(getID(event.code),pGData)) cout << "-1" <<endl;
		else{
			processEvent_8(nList,event.code);
		}break;
	case 9:
		processEvent_9(nList,pGData);break;
	case 10:
		processEvent_10(nList,pGData);break;
	case 11:
		if(!checkID(getID(event.code),pGData)) cout << "-1" <<endl;
		else{
			processEvent_11(pGData,event.code);
		}break;

	case 12:
		processEvent_12(nList,pGData);break;
	case 14:
		processEvent_14(nList,pGData);break;
	}

	//
    /// NOTE: The output of the event will be printed on one line
    /// end by the endline character.
    return true;
}



