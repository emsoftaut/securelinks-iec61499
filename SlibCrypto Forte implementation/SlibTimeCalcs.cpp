/*
 * SlibTimeCalcs.cpp
 *
 * 
 */

#include "SlibTimeCalcs.h"



SlibTimeCalcs::SlibTimeCalcs() {
	// TODO Auto-generated constructor stub

}

SlibTimeCalcs::~SlibTimeCalcs() {
	// TODO Auto-generated destructor stub
}



long SlibTimeCalcs::getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void SlibTimeCalcs::registerTime(const char* filename) {
	FILE *fp = fopen(filename, "a");
	if(!fp) {
		perror("Error in opening file:");
		return;
	}

	unsigned long t = (unsigned)getMicrotime(); //time(NULL);
	fprintf(fp, "%u,", t);
	fclose(fp);
}
