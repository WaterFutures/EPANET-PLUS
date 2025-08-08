#ifndef EPANETPLUS_H
#define EPANETPLUS_H

#include "epanet2_2.h"

int DLLEXPORT ENopenfrombuffer(const char *inpBuffer, const char *inpFile, const char *rptFile, const char *outFile);
int DLLEXPORT EN_openfrombuffer(EN_Project p, const char *inpBuffer, const char *inpFile, const char *rptFile, const char *outFile);

#endif //EPANETPLUS_H