/*
 * SlibTimeCalcs.h
 *
 *
 */

#ifndef SRC_MODULES_SLIBCRYPTO_SLIBTIMECALCS_H_
#define SRC_MODULES_SLIBCRYPTO_SLIBTIMECALCS_H_

#include <stdio.h>
#include <sys/time.h>

class SlibTimeCalcs {
public:
	SlibTimeCalcs();
	virtual ~SlibTimeCalcs();
	long getMicrotime();
	void registerTime(const char* filename);
};


#endif /* SRC_MODULES_SLIBCRYPTO_SLIBTIMECALCS_H_ */
