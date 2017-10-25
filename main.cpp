#include <iostream>

#include "listLib.h"
#include "eventLib.h"
#include "dbLib.h"

using namespace std;


/// This function displays the content of database
void display(L1List<NinjaInfo_t>& nList) {
    cout.flush();
    nList.traverse(printNinjaInfo);
}


int main(int narg, char** argv) {
	const clock_t begin_time = clock();
	    // do something
    L1List<ninjaEvent_t>  eventList;
    L1List<NinjaInfo_t>   db;// database of NinjaInfo
    loadEvents(argv[1], eventList);
    loadNinjaDB(argv[2], db);

    cout << fixed << setprecision(12);// preset for floating point numbers

    cout << "Runtime: ";
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<"s" <<endl;
    /// Process events
    //display(db);
    process(eventList, db);

    cout << resetiosflags(ios::showbase) << setprecision(-1);

    return 0;
}