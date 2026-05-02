#ifndef MOSEK_H
#define MOSEK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Opaque handles */
typedef struct MSKenv  *MSKenv_t;
typedef struct MSKtask *MSKtask_t;
typedef void           *MSKuserhandle_t;

/* Numeric / boolean primitives */
typedef int      MSKint32t;
typedef int      MSKbooleant;
typedef double   MSKrealt;
typedef int      MSKrescodee;
typedef int      MSKboundkeye;
typedef int      MSKvariabletypee;
typedef int      MSKsoltypee;
typedef int      MSKsolstae;
typedef int      MSKprostae;
typedef int      MSKconetypee;
typedef int      MSKobjsensee;
typedef int      MSKstreamtypee;

/* Stream callback signature */
typedef void (*MSKstreamfunc)(MSKuserhandle_t, const char *);

/* Result codes -- only OK is referenced by the plugin */
#define MSK_RES_OK                            0

/* Bound keys */
#define MSK_BK_LO                             0
#define MSK_BK_UP                             1
#define MSK_BK_FX                             2
#define MSK_BK_FR                             3
#define MSK_BK_RA                             4

/* Variable types */
#define MSK_VAR_TYPE_CONT                     0
#define MSK_VAR_TYPE_INT                      1

/* Objective sense */
#define MSK_OBJECTIVE_SENSE_MINIMIZE          0
#define MSK_OBJECTIVE_SENSE_MAXIMIZE          1

/* Solution types */
#define MSK_SOL_ITR                           0
#define MSK_SOL_BAS                           1
#define MSK_SOL_ITG                           2

/* Solution status (only the values the plugin checks) */
#define MSK_SOL_STA_UNKNOWN                   0
#define MSK_SOL_STA_OPTIMAL                   1
#define MSK_SOL_STA_PRIM_AND_DUAL_FEAS        4
#define MSK_SOL_STA_INTEGER_OPTIMAL           9

/* Problem status */
#define MSK_PRO_STA_UNKNOWN                   0

/* Cone type */
#define MSK_CT_QUAD                           0

/* Stream type */
#define MSK_STREAM_LOG                        0

/* Function declarations: signatures match the real Mosek 11 API
 * (return type and parameter types only; parameter names are dummies). */

MSKrescodee MSK_makeenv  (MSKenv_t *, const char *);
MSKrescodee MSK_deleteenv(MSKenv_t *);
MSKrescodee MSK_maketask (MSKenv_t, MSKint32t, MSKint32t, MSKtask_t *);
MSKrescodee MSK_deletetask(MSKtask_t *);

MSKrescodee MSK_appendvars(MSKtask_t, MSKint32t);
MSKrescodee MSK_appendcons(MSKtask_t, MSKint32t);
MSKrescodee MSK_putobjsense(MSKtask_t, MSKobjsensee);

MSKrescodee MSK_putcj      (MSKtask_t, MSKint32t, MSKrealt);
MSKrescodee MSK_putvarbound(MSKtask_t, MSKint32t, MSKboundkeye, MSKrealt, MSKrealt);
MSKrescodee MSK_putconbound(MSKtask_t, MSKint32t, MSKboundkeye, MSKrealt, MSKrealt);
MSKrescodee MSK_putacol    (MSKtask_t, MSKint32t, MSKint32t, const MSKint32t *, const MSKrealt *);
MSKrescodee MSK_putarow    (MSKtask_t, MSKint32t, MSKint32t, const MSKint32t *, const MSKrealt *);
MSKrescodee MSK_putqobj    (MSKtask_t, MSKint32t, const MSKint32t *, const MSKint32t *, const MSKrealt *);
MSKrescodee MSK_putvartype (MSKtask_t, MSKint32t, MSKvariabletypee);
MSKrescodee MSK_appendcone (MSKtask_t, MSKconetypee, MSKrealt, MSKint32t, const MSKint32t *);

MSKrescodee MSK_optimizetrm(MSKtask_t, MSKrescodee *);

MSKrescodee MSK_getsolsta   (MSKtask_t, MSKsoltypee, MSKsolstae *);
MSKrescodee MSK_getprosta   (MSKtask_t, MSKsoltypee, MSKprostae *);
MSKrescodee MSK_solutiondef (MSKtask_t, MSKsoltypee, MSKbooleant *);
MSKrescodee MSK_getxxslice  (MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *);
MSKrescodee MSK_getyslice   (MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *);
MSKrescodee MSK_getslxslice (MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *);
MSKrescodee MSK_getsuxslice (MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *);
MSKrescodee MSK_getprimalobj(MSKtask_t, MSKsoltypee, MSKrealt *);

MSKrescodee MSK_putnaintparam(MSKtask_t, const char *, MSKint32t);
MSKrescodee MSK_putnadouparam(MSKtask_t, const char *, MSKrealt);
MSKrescodee MSK_putnastrparam(MSKtask_t, const char *, const char *);

MSKrescodee MSK_linkfunctotaskstream(MSKtask_t, MSKstreamtypee, MSKuserhandle_t, MSKstreamfunc);

#ifdef __cplusplus
}
#endif

#endif /* MOSEK_H */
