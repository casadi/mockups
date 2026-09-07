/* Mockup CONOPT C API header.
 *
 * Declares only the subset of the CONOPT 4 C API that CasADi's conopt nlpsol
 * plugin uses, ABI-compatible with the real <conopt.h> shipped by GAMS.
 */

#ifndef CONOPT_H_
#define CONOPT_H_

#define CONOPT_VERSION_MAJOR 4
#define CONOPT_VERSION_MINOR 39
#define CONOPT_VERSION_PATCH 2

#if defined(_WIN32)
#define COI_CALLCONV __stdcall
#else
#define COI_CALLCONV
#endif

#if defined(COI_API)
#elif defined(_WIN32)
#define COI_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define COI_API __attribute__((__visibility__("default")))
#else
#define COI_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct coiRec* coiHandle_t;

    typedef int(COI_CALLCONV *COI_READMATRIX_t)(double LOWER[], double CURR[], double UPPER[], int VSTA[], int TYPEX[], double RHS[], int ESTA[], int COLSTA[], int ROWNO[], double VALUE[], int NLFLAG[], int NUMVAR, int NUMCON, int NUMNZ, void* USRMEM);
    typedef int(COI_CALLCONV *COI_FDEVAL_t)(const double X[], double* G, double JAC[], int ROWNO, const int JACNUM[], int MODE, int IGNERR, int* ERRCNT, int NUMVAR, int NUMJAC, int THREAD, void* USRMEM);
    typedef int(COI_CALLCONV *COI_FDEVALINI_t)(const double X[], const int ROWLIST[], int MODE, int LISTSIZE, int NUMTHREAD, int IGNERR, int* ERRCNT, int NUMVAR, void* USRMEM);
    typedef int(COI_CALLCONV *COI_FDEVALEND_t)(int IGNERR, int* ERRCNT, void* USRMEM);
    typedef int(COI_CALLCONV *COI_STATUS_t)(int MODSTA, int SOLSTA, int ITER, double OBJVAL, void* USRMEM);
    typedef int(COI_CALLCONV *COI_SOLUTION_t)(const double XVAL[], const double XMAR[], const int XBAS[], const int XSTA[], const double YVAL[], const double YMAR[], const int YBAS[], const int YSTA[], int NUMVAR, int NUMCON, void* USRMEM);
    typedef int(COI_CALLCONV *COI_MESSAGE_t)(int SMSG, int DMSG, int NMSG, char* MSGV[], void* USRMEM);
    typedef int(COI_CALLCONV *COI_ERRMSG_t)(int ROWNO, int COLNO, int POSNO, const char* MSG, void* USRMEM);
    typedef int(COI_CALLCONV *COI_PROGRESS_t)(int LEN_INT, const int INTX[], int LEN_RL, const double RL[], const double X[], void* USRMEM);
    typedef int(COI_CALLCONV *COI_OPTION_t)(int NCALL, double* RVAL, int* IVAL, int* LVAL, char* NAME, void* USRMEM);
    typedef int(COI_CALLCONV *COI_2DLAGRSTR_t)(int HSRW[], int HSCL[], int* NODRV, int NUMVAR, int NUMCON, int NHESS, void* USRMEM);
    typedef int(COI_CALLCONV *COI_2DLAGRVAL_t)(const double X[], const double U[], const int HSRW[], const int HSCL[], double HSVL[], int* NODRV, int NUMVAR, int NUMCON, int NHESS, void* USRMEM);

    COI_API int COI_CALLCONV COI_Create(coiHandle_t *cntvect);
    COI_API int COI_CALLCONV COI_Free(coiHandle_t *cntvect);
    COI_API int COI_CALLCONV COI_Solve(coiHandle_t cntvect);

    COI_API int COI_CALLCONV COIDEF_NumVar(coiHandle_t cntvect, int numvar);
    COI_API int COI_CALLCONV COIDEF_NumCon(coiHandle_t cntvect, int numcon);
    COI_API int COI_CALLCONV COIDEF_NumNz(coiHandle_t cntvect, int numnz);
    COI_API int COI_CALLCONV COIDEF_NumNlNz(coiHandle_t cntvect, int numnlnz);
    COI_API int COI_CALLCONV COIDEF_NumHess(coiHandle_t cntvect, int numhess);
    COI_API int COI_CALLCONV COIDEF_OptDir(coiHandle_t cntvect, int optdir);
    COI_API int COI_CALLCONV COIDEF_ObjCon(coiHandle_t cntvect, int objcon);
    COI_API int COI_CALLCONV COIDEF_ItLim(coiHandle_t cntvect, int itlim);
    COI_API int COI_CALLCONV COIDEF_ErrLim(coiHandle_t cntvect, int errlim);
    COI_API int COI_CALLCONV COIDEF_ResLim(coiHandle_t cntvect, double reslim);
    COI_API int COI_CALLCONV COIDEF_MaxHeap(coiHandle_t cntvect, double maxheap);
    COI_API int COI_CALLCONV COIDEF_IniStat(coiHandle_t cntvect, int inistat);
    COI_API int COI_CALLCONV COIDEF_FVincLin(coiHandle_t cntvect, int fvinclin);
    COI_API int COI_CALLCONV COIDEF_Optfile(coiHandle_t cntvect, const char *optfile);
    COI_API int COI_CALLCONV COIDEF_UsrMem(coiHandle_t cntvect, void* usrmem);

    COI_API int COI_CALLCONV COIDEF_ReadMatrix(coiHandle_t cntvect, COI_READMATRIX_t coi_readmatrix);
    COI_API int COI_CALLCONV COIDEF_FDEval(coiHandle_t cntvect, COI_FDEVAL_t coi_fdeval);
    COI_API int COI_CALLCONV COIDEF_FDEvalIni(coiHandle_t cntvect, COI_FDEVALINI_t coi_fdevalini);
    COI_API int COI_CALLCONV COIDEF_FDEvalEnd(coiHandle_t cntvect, COI_FDEVALEND_t coi_fdevalend);
    COI_API int COI_CALLCONV COIDEF_Status(coiHandle_t cntvect, COI_STATUS_t coi_status);
    COI_API int COI_CALLCONV COIDEF_Solution(coiHandle_t cntvect, COI_SOLUTION_t coi_solution);
    COI_API int COI_CALLCONV COIDEF_Message(coiHandle_t cntvect, COI_MESSAGE_t coi_message);
    COI_API int COI_CALLCONV COIDEF_ErrMsg(coiHandle_t cntvect, COI_ERRMSG_t coi_errmsg);
    COI_API int COI_CALLCONV COIDEF_Progress(coiHandle_t cntvect, COI_PROGRESS_t coi_progress);
    COI_API int COI_CALLCONV COIDEF_Option(coiHandle_t cntvect, COI_OPTION_t coi_option);
    COI_API int COI_CALLCONV COIDEF_2DLagrStr(coiHandle_t cntvect, COI_2DLAGRSTR_t coi_2dlagrstr);
    COI_API int COI_CALLCONV COIDEF_2DLagrVal(coiHandle_t cntvect, COI_2DLAGRVAL_t coi_2dlagrval);

#ifdef __cplusplus
}
#endif

#endif /* CONOPT_H_ */
