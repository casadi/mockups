/* Mockup CONOPT library.
 *
 * Lets CasADi's conopt nlpsol plugin link and load on platforms where the real
 * CONOPT (proprietary, GAMS) is not available. Every COIDEF_* setter succeeds so
 * the plugin can complete init/setup; COI_Solve fails, which the plugin reports
 * as SOLVER_RET_UNKNOWN. The real library, when present, shadows this one
 * (same SONAME libconopt.so.4 / conopt4.dll).
 */

#include <conopt.h>

/* One shared dummy control vector: the plugin only ever passes the handle back. */
static int coi_mockup_control;

int COI_CALLCONV COI_Create(coiHandle_t *cntvect) {
  if (!cntvect) return 1;
  *cntvect = (coiHandle_t)&coi_mockup_control;
  return 0;
}

int COI_CALLCONV COI_Free(coiHandle_t *cntvect) {
  if (cntvect) *cntvect = 0;
  return 0;
}

/* Nonzero: "no solution", the plugin's failure path. */
int COI_CALLCONV COI_Solve(coiHandle_t cntvect) { (void)cntvect; return 1; }

#define COI_MOCKUP_DEF(name, type) \
  int COI_CALLCONV name(coiHandle_t cntvect, type arg) { (void)cntvect; (void)arg; return 0; }

COI_MOCKUP_DEF(COIDEF_NumVar, int)
COI_MOCKUP_DEF(COIDEF_NumCon, int)
COI_MOCKUP_DEF(COIDEF_NumNz, int)
COI_MOCKUP_DEF(COIDEF_NumNlNz, int)
COI_MOCKUP_DEF(COIDEF_NumHess, int)
COI_MOCKUP_DEF(COIDEF_OptDir, int)
COI_MOCKUP_DEF(COIDEF_ObjCon, int)
COI_MOCKUP_DEF(COIDEF_ItLim, int)
COI_MOCKUP_DEF(COIDEF_ErrLim, int)
COI_MOCKUP_DEF(COIDEF_IniStat, int)
COI_MOCKUP_DEF(COIDEF_FVincLin, int)
COI_MOCKUP_DEF(COIDEF_ResLim, double)
COI_MOCKUP_DEF(COIDEF_MaxHeap, double)
COI_MOCKUP_DEF(COIDEF_Optfile, const char *)
COI_MOCKUP_DEF(COIDEF_UsrMem, void *)
COI_MOCKUP_DEF(COIDEF_ReadMatrix, COI_READMATRIX_t)
COI_MOCKUP_DEF(COIDEF_FDEval, COI_FDEVAL_t)
COI_MOCKUP_DEF(COIDEF_FDEvalIni, COI_FDEVALINI_t)
COI_MOCKUP_DEF(COIDEF_FDEvalEnd, COI_FDEVALEND_t)
COI_MOCKUP_DEF(COIDEF_Status, COI_STATUS_t)
COI_MOCKUP_DEF(COIDEF_Solution, COI_SOLUTION_t)
COI_MOCKUP_DEF(COIDEF_Message, COI_MESSAGE_t)
COI_MOCKUP_DEF(COIDEF_ErrMsg, COI_ERRMSG_t)
COI_MOCKUP_DEF(COIDEF_Progress, COI_PROGRESS_t)
COI_MOCKUP_DEF(COIDEF_Option, COI_OPTION_t)
COI_MOCKUP_DEF(COIDEF_2DLagrStr, COI_2DLAGRSTR_t)
COI_MOCKUP_DEF(COIDEF_2DLagrVal, COI_2DLAGRVAL_t)
