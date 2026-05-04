#ifndef _LIBMAD_H
#define _LIBMAD_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>

#define libmad_int long long int
#define libmad_real double

#define LIBMAD_CCOPT_VARVAR 0
#define LIBMAD_CCOPT_VARCON 1
#define LIBMAD_CCOPT_CONVAR 2
#define LIBMAD_CCOPT_CONCON 3

// function pointer types
typedef int (*NlpConstrJacStructure)(libmad_int*, libmad_int*, void*);
typedef int (*NlpLagHessStructure)(libmad_int*, libmad_int*, void*);
typedef int (*NlpEvalObj)(const libmad_real*, libmad_real*, void*);
typedef int (*NlpEvalConstr)(const libmad_real*, libmad_real*, void*);
typedef int (*NlpEvalObjGrad)(const libmad_real*, libmad_real*, void*);
typedef int (*NlpEvalConstrJac)(const libmad_real*, libmad_real*, void*);
typedef int (*NlpEvalLagHess)(libmad_real, const libmad_real*, const libmad_real*, libmad_real*, void*);

typedef struct OptsDict OptsDict;
typedef struct CNLPModel CNLPModel;
typedef struct MadNLPExecutionStats MadNLPExecutionStats;
typedef struct MadNLPSolver MadNLPSolver;
typedef struct CMPCCModel CMPCCModel;
typedef struct CCOptExecutionStats CCOptExecutionStats;
typedef struct RelaxationSolver RelaxationSolver;

int libmad_create_options_dict(OptsDict**);

int libmad_set_int64_option(OptsDict*, const char*, libmad_int);

int libmad_set_double_option(OptsDict*, const char*, libmad_real);

int libmad_set_bool_option(OptsDict*, const char*, bool);

int libmad_set_string_option(OptsDict*, const char*, const char*);

int libmad_delete_options_dict(OptsDict*);

int libmad_nlpmodel_create(CNLPModel**,
const char*,
libmad_int, libmad_int,
libmad_int, libmad_int,
NlpConstrJacStructure, NlpLagHessStructure,
NlpEvalObj, NlpEvalConstr,
NlpEvalObjGrad, NlpEvalConstrJac,
NlpEvalLagHess,
void*);

int libmad_nlpmodel_set_numerics(CNLPModel*,
 const libmad_real*, const libmad_real*,
 const libmad_real*, const libmad_real*,
 const libmad_real*, const libmad_real*
);

int madnlp_get_obj(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_solution(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_constraints(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_multipliers(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_multipliers_L(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_multipliers_U(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_bound_multipliers(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_success(MadNLPExecutionStats*, bool*);

int madnlp_get_iters(MadNLPExecutionStats*, libmad_int*);

int madnlp_get_total_wall_time(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_primal_feas(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_dual_feas(MadNLPExecutionStats*, libmad_real*);

int madnlp_get_status(MadNLPExecutionStats*, libmad_int*);

int madnlp_delete_stats(MadNLPExecutionStats*);

int madnlp_create_solver(MadNLPSolver**, CNLPModel*, OptsDict*);

int madnlp_delete_solver(MadNLPSolver*);

int madnlp_solve(MadNLPSolver*, OptsDict*, MadNLPExecutionStats**);

int libmad_mpccmodel_create(CMPCCModel**,
CNLPModel*,
libmad_int,
const libmad_int*, const libmad_int*,
const libmad_int*
);

int libmad_mpccmodel_set_numerics(CMPCCModel*,
const libmad_real*, const libmad_real*,
const libmad_real*, const libmad_real*,
const libmad_real*, const libmad_real*
);

int ccopt_relaxation_get_obj(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_solution(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_constraints(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_multipliers(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_multipliers_L(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_multipliers_U(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_bound_multipliers(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_success(CCOptExecutionStats*, bool*);

int ccopt_relaxation_get_iters(CCOptExecutionStats*, libmad_int*);

int ccopt_relaxation_get_total_wall_time(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_primal_feas(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_dual_feas(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_status(CCOptExecutionStats*, libmad_int*);

int ccopt_relaxation_get_cc_feas(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_multipliers_x1(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_get_multipliers_x2(CCOptExecutionStats*, libmad_real*);

int ccopt_relaxation_delete_stats(CCOptExecutionStats*);

int ccopt_relaxation_create_solver(RelaxationSolver**, CMPCCModel*, OptsDict*, OptsDict*);

int ccopt_relaxation_delete_solver(RelaxationSolver*);

int ccopt_relaxation_solve(RelaxationSolver*, OptsDict*, CCOptExecutionStats**);

#ifdef __cplusplus
}
#endif

#endif // _LIBMAD_H
