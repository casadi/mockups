#include "libMad.h"

int libmad_create_options_dict(OptsDict**) { return 0; }

int libmad_set_int64_option(OptsDict*, const char*, libmad_int) { return 0; }
int libmad_set_double_option(OptsDict*, const char*, libmad_real) { return 0; }
int libmad_set_bool_option(OptsDict*, const char*, bool) { return 0; }
int libmad_set_string_option(OptsDict*, const char*, const char*) { return 0; }

int libmad_delete_options_dict(OptsDict*) { return 0; }

int libmad_nlpmodel_create(CNLPModel**,
                           const char*,
                           libmad_int, libmad_int,
                           libmad_int, libmad_int,
                           NlpConstrJacStructure, NlpLagHessStructure,
                           NlpEvalObj, NlpEvalConstr,
                           NlpEvalObjGrad, NlpEvalConstrJac,
                           NlpEvalLagHess,
                           void*) { return 0; }

int libmad_nlpmodel_set_numerics(CNLPModel*,
                                 const libmad_real*, const libmad_real*,
                                 const libmad_real*, const libmad_real*,
                                 const libmad_real*, const libmad_real*) { return 0; }

int madnlp_get_obj(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_solution(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_constraints(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_multipliers(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_multipliers_L(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_multipliers_U(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_bound_multipliers(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_success(MadNLPExecutionStats*, bool*) { return 0; }
int madnlp_get_iters(MadNLPExecutionStats*, libmad_int*) { return 0; }
int madnlp_get_total_wall_time(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_primal_feas(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_dual_feas(MadNLPExecutionStats*, libmad_real*) { return 0; }
int madnlp_get_status(MadNLPExecutionStats*, libmad_int*) { return 0; }

int madnlp_delete_stats(MadNLPExecutionStats*) { return 0; }

int madnlp_create_solver(MadNLPSolver**, CNLPModel*, OptsDict*) { return 0; }
int madnlp_delete_solver(MadNLPSolver*) { return 0; }
int madnlp_solve(MadNLPSolver*, OptsDict*, MadNLPExecutionStats**) { return 0; }

int libmad_mpccmodel_create(CMPCCModel**,
                            CNLPModel*,
                            libmad_int,
                            const libmad_int*, const libmad_int*,
                            const libmad_int*) { return 0; }

int libmad_mpccmodel_set_numerics(CMPCCModel*,
                                  const libmad_real*, const libmad_real*,
                                  const libmad_real*, const libmad_real*,
                                  const libmad_real*, const libmad_real*) { return 0; }

int ccopt_relaxation_get_obj(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_solution(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_constraints(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_multipliers(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_multipliers_L(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_multipliers_U(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_bound_multipliers(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_success(CCOptExecutionStats*, bool*) { return 0; }
int ccopt_relaxation_get_iters(CCOptExecutionStats*, libmad_int*) { return 0; }
int ccopt_relaxation_get_total_wall_time(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_primal_feas(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_dual_feas(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_status(CCOptExecutionStats*, libmad_int*) { return 0; }
int ccopt_relaxation_get_cc_feas(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_multipliers_x1(CCOptExecutionStats*, libmad_real*) { return 0; }
int ccopt_relaxation_get_multipliers_x2(CCOptExecutionStats*, libmad_real*) { return 0; }

int ccopt_relaxation_delete_stats(CCOptExecutionStats*) { return 0; }

int ccopt_relaxation_create_solver(RelaxationSolver**, CMPCCModel*, OptsDict*, OptsDict*) { return 0; }
int ccopt_relaxation_delete_solver(RelaxationSolver*) { return 0; }
int ccopt_relaxation_solve(RelaxationSolver*, OptsDict*, CCOptExecutionStats**) { return 0; }
