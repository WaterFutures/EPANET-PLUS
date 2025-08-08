#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "epanet2.h"
#include "epanet2_2.h"
#include "types.h"
#include "text.h"

extern Project *_defaultProject;
extern read_data_from_buffer(Project *pr, const char *inpBuffer);
extern netsize_from_buffer(Project *pr, const char *inpBuffer);


int DLLEXPORT ENopenfrombuffer(const char *inpBuffer, const char *inpFile, const char *rptFile, const char *outFile)
{
    int errcode = 0;
    createtmpfiles();
    errcode = EN_openfrombuffer(_defaultProject, inpBuffer, inpFile, rptFile, outFile);
    return errcode;
}

int getdata_from_buffer(Project *pr, const char *inpBuffer)
{
    int errcode = 0;

    // Assign default data values & reporting options
    setdefaults(pr);
    initreport(&pr->report);

    // Read in network data
    //rewind(pr->parser.InFile);
    ERRCODE(read_data_from_buffer(pr, inpBuffer));

    // Adjust data and convert it to internal units
    if (!errcode)
        adjustdata(pr);
    if (!errcode)
        initunits(pr);
    ERRCODE(inittanks(pr));
    if (!errcode)
        convertunits(pr);
    return errcode;
}


int DLLEXPORT EN_openfrombuffer(EN_Project p, const char *inpBuffer, const char *inpFile, const char *rptFile, const char *outFile)
{
    int errcode = 0;

    // Set system flags
    p->Openflag = FALSE;
    p->hydraul.OpenHflag = FALSE;
    p->quality.OpenQflag = FALSE;
    p->outfile.SaveHflag = FALSE;
    p->outfile.SaveQflag = FALSE;
    p->Warnflag = FALSE;
    p->report.Messageflag = TRUE;
    p->report.Rptflag = 1;

    // Initialize data arrays to NULL
    initpointers(p);

    // Open input & report files
    ERRCODE(openfiles(p, "", rptFile, outFile));
    if (errcode > 0)
    {
        errmsg(p, errcode);
        return errcode;
    }

    // Allocate memory for project's data arrays
    writewin(p->viewprog, FMT100);
    ERRCODE(netsize_from_buffer(p, inpBuffer));
    ERRCODE(allocdata(p));

    // Read input data
    ERRCODE(getdata_from_buffer(p, inpBuffer));

    // Close input file
    if (p->parser.InFile != NULL)
    {
        fclose(p->parser.InFile);
        p->parser.InFile = NULL;
    }

    // If using previously saved hydraulics file then open it
    if (p->outfile.Hydflag == USE) ERRCODE(openhydfile(p));

    // Write input summary to report file
    if (!errcode)
    {
        if (p->report.Summaryflag) writesummary(p);
        writetime(p, FMT104);
        p->Openflag = TRUE;
    }
    else errmsg(p, errcode);
    return errcode;
}