#include <iostream>

#include "listLib.h"
#include "eventLib.h"
#include "dbLib.h"

using namespace std;

/// NOTE: student must defined this function if they use dynamically allocated global data.
/// If student do not use any dynamic global data, please define this function as empty function
/// in your code (file processData.cpp) as follows
/// void releaseNinjaGlobalData() {}
void releaseNinjaGlobalData();

/// This function displays the content of database
void display(L1List<NinjaInfo_t>& nList) {
    cout.flush();
    nList.traverse(printNinjaInfo);
}

int main(int narg, char** argv) {
    L1List<ninjaEvent_t>  eventList;
    L1List<NinjaInfo_t>   db;// database of NinjaInfo
    loadEvents(argv[1], eventList);
    loadNinjaDB(argv[2], db);

    cout << fixed << setprecision(12);// preset for floating point numbers
    /// Process events
    process(eventList, db);

    cout << resetiosflags(ios::showbase) << setprecision(-1);
    /// Release any global allocaed data
    releaseNinjaGlobalData();
    return 0;
}