/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void    strPrintTime(char* des, time_t& t) {
    tm *pTime = gmtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
	// TODO: write code to load information from file into db
	ifstream ifile;
	ifile.open(fName);
	string str;//luu cac phan khong can thiet
	string str1, str2, str3, str4;
	NinjaInfo temp1;// luu du lieu ninja tam
	getline(ifile, str);//lay dong dau cua file
	//int i;
	L1Item<NinjaInfo_t>* pLast= db.getHead();
	while (!ifile.eof())
	{
		getline(ifile, str, ',');
		getline(ifile, str1, ',');
		getline(ifile, str2, ',');
		getline(ifile, str3, ',');
		getline(ifile, str4, ',');
		getline(ifile, str);
		//doi string thanh time_t
		char strtemp;
		int hh, mm, ss, DD, MM, YYYY;// Luu tru ngay thang nam
		// phan tach chuoi
		stringstream input(str1);
		input >> DD >> strtemp >> MM >> strtemp >> YYYY >> hh >> strtemp >> mm >> strtemp >> ss;

		//gan vao tm
		struct tm tm;
		tm.tm_hour = hh;
		tm.tm_min = mm;
		tm.tm_sec = ss;
		tm.tm_mday = DD;
		tm.tm_mon = MM - 1;// mont [0,11] nen tru di 1
		tm.tm_year = YYYY - 1900;
		tm.tm_isdst = -1;// khong co gio mua he
		temp1.timestamp = mktime(&tm);

		strcpy(temp1.id,str2.c_str());
		temp1.longitude = atof(str3.c_str());//chuyen string thanh char roi chuyen thanh double
		temp1.latitude = atof(str4.c_str());
		// push du lieu vao list db
		pLast = db.pushBack(temp1,pLast);
		//db.push_back(temp1);
		//i++;
		//if(i == 100000) break;
	}

	ifile.close();
}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
    // TODO: write code to parse information from a string buffer, ignore if you don't use it
    return true;
}


void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
	void*   pGData = NULL;
	initNinjaGlobalData(&pGData);
	L1List<ninjaEvent_t>* temp = eventList.copyList();
	pGData = temp;

    while (!eventList.isEmpty()) {
    	if(!processEvent(eventList[0], bList, pGData))
            cout << eventList[0].code << " is an invalid event\n";
        eventList.removeHead();
    }

    releaseNinjaGlobalData(pGData);
}


bool initNinjaGlobalData(void** pGData) {
      /// TODO: You should define this function if you would like to use some extra data
      /// the data should be allocated and pass the address into pGData
  }

void releaseNinjaGlobalData(void* pGData) {
      /// TODO: You should define this function if you allocated extra data at initialization stage
      /// The data pointed by pGData should be released
	delete pGData;
  }


void printNinjaInfo(NinjaInfo_t& b) {
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg) {
    return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
