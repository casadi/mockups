#ifndef XPRS_H
#define XPRS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef struct xo_prob_struct *XPRSprob;

#ifdef _WIN32
#define XPRSint64 __int64
#elif defined(__APPLE__)
#define XPRSint64 long long
#else
#define XPRSint64 long
#endif

#define XPRS_PLUSINFINITY              1.0e+20
#define XPRS_MINUSINFINITY          (-1.0e+20)

/* Integer attributes */
#define XPRS_ROWS                      1001
#define XPRS_SIMPLEXITER               1009
#define XPRS_LPSTATUS                  1010
#define XPRS_MIPSTATUS                 1011
#define XPRS_NODES                     1013
#define XPRS_BARITER                   5001

/* Double attributes */
#define XPRS_LPOBJVAL                  2001
#define XPRS_MIPOBJVAL                 2003

/* LP solution status */
#define XPRS_LP_OPTIMAL                 1
#define XPRS_LP_INFEAS                  2
#define XPRS_LP_CUTOFF                  3
#define XPRS_LP_UNFINISHED              4
#define XPRS_LP_UNBOUNDED               5
#define XPRS_LP_CUTOFF_IN_DUAL          6
#define XPRS_LP_UNSOLVED                7
#define XPRS_LP_NONCONVEX               8

/* MIP solution status */
#define XPRS_MIP_NOT_LOADED             0
#define XPRS_MIP_LP_NOT_OPTIMAL         1
#define XPRS_MIP_LP_OPTIMAL             2
#define XPRS_MIP_NO_SOL_FOUND           3
#define XPRS_MIP_SOLUTION               4
#define XPRS_MIP_INFEAS                 5
#define XPRS_MIP_OPTIMAL                6
#define XPRS_MIP_UNBOUNDED              7

/* Objective sense */
#define XPRS_OBJ_MINIMIZE               1
#define XPRS_OBJ_MAXIMIZE              -1

/* Control types (returned by XPRSgetcontrolinfo) */
#define XPRS_TYPE_NOTDEFINED            0
#define XPRS_TYPE_INT                   1
#define XPRS_TYPE_INT64                 2
#define XPRS_TYPE_DOUBLE                3
#define XPRS_TYPE_STRING                4

/* Common controls */
#define XPRS_FEASTOL                    7003
#define XPRS_OPTIMALITYTOL              7006
#define XPRS_BARGAPSTOP                 7033
#define XPRS_BARDUALSTOP                7034
#define XPRS_OUTPUTLOG                  8035
#define XPRS_CROSSOVER                  8044

int XPRSinit(const char*);
int XPRSfree(void);
int XPRScreateprob(XPRSprob*);
int XPRSdestroyprob(XPRSprob);
int XPRSloadqp(XPRSprob, const char*, int, int, const char[], const double[], const double[], const double[], const int[], const int[], const int[], const double[], const double[], const double[], int, const int[], const int[], const double[]);
int XPRSchgcoltype(XPRSprob, int, const int[], const char[]);
int XPRSaddsets(XPRSprob, int, int, const char[], const int[], const int[], const double[]);
int XPRSaddcols(XPRSprob, int, int, const double[], const int[], const int[], const double[], const double[], const double[]);
int XPRSaddrows(XPRSprob, int, int, const char[], const double[], const double[], const int[], const int[], const double[]);
int XPRSaddqmatrix(XPRSprob, int, int, const int[], const int[], const double[]);
int XPRSlpoptimize(XPRSprob, const char*);
int XPRSmipoptimize(XPRSprob, const char*);
int XPRSgetsolution(XPRSprob, int*, double[], int, int);
int XPRSgetduals(XPRSprob, int*, double[], int, int);
int XPRSgetredcosts(XPRSprob, int*, double[], int, int);
int XPRSgetintattrib(XPRSprob, int, int*);
int XPRSgetdblattrib(XPRSprob, int, double*);
int XPRSsetintcontrol(XPRSprob, int, int);
int XPRSsetintcontrol64(XPRSprob, int, XPRSint64);
int XPRSsetdblcontrol(XPRSprob, int, double);
int XPRSsetstrcontrol(XPRSprob, int, const char*);
int XPRSgetcontrolinfo(XPRSprob, const char*, int*, int*);

#ifdef __cplusplus
}
#endif

#endif /* XPRS_H */
