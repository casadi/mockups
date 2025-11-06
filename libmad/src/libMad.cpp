#include "libMad.h"

int libmad_create_options_dict(OptsDict** opts_ptr) { return 0; }

int libmad_set_int_option(OptsDict* opts_ptr, char* name, int val) { return 0; }

int libmad_set_long_option(OptsDict* opts_ptr, char* name, long val) { return 0; }

int libmad_set_float_option(OptsDict* opts_ptr, char* name, float val) { return 0; }

int libmad_set_double_option(OptsDict* opts_ptr, char* name, double val) { return 0; }

int libmad_set_bool_option(OptsDict* opts_ptr, char* name, bool val) { return 0; }

int libmad_set_string_option(OptsDict* opts_ptr, char* name, char* val) { return 0; }

int libmad_delete_options_dict(OptsDict* stats_ptr) { return 0; }

int libmad_nlpmodel_create(CNLPModel** nlp_ptr_ptr,
char* name,
long nvar, long ncon,
long nnzj, long nnzh,
void* jac_struct, void* hess_struct,
void* eval_f, void* eval_g,
void* eval_grad_f, void* eval_jac_g,
void* eval_h,
void* user_data) { return 0; }

int libmad_nlpmodel_set_numerics(CNLPModel* nlp_ptr,
 double* x0, double* y0,
 double* lvar, double* uvar,
 double* lcon, double* ucon
) { return 0; }

int madnlp_get_obj(MadNLPExecutionStats* stats_ptr, double* out) { return 0; }

int madnlp_get_solution(MadNLPExecutionStats* stats_ptr, double* out) { return 0; }

int madnlp_get_constraints(MadNLPExecutionStats* stats_ptr, double* out) { return 0; }

int madnlp_get_multipliers(MadNLPExecutionStats* stats_ptr, double* out) { return 0; }

int madnlp_get_multipliers_L(MadNLPExecutionStats* stats_ptr, double* out) { return 0; }

int madnlp_get_multipliers_U(MadNLPExecutionStats* stats_ptr, double* out) { return 0; }

int madnlp_get_bound_multipliers(MadNLPExecutionStats* stats_ptr, double* out) { return 0; }

int madnlp_get_success(MadNLPExecutionStats* stats_ptr, bool* out) { return 0; }

int madnlp_get_iters(MadNLPExecutionStats* stats_ptr, long* out) { return 0; }

int madnlp_get_primal_feas(MadNLPExecutionStats* stats_ptr, long* out) { return 0; }

int madnlp_get_dual_feas(MadNLPExecutionStats* stats_ptr, long* out) { return 0; }

int madnlp_get_status(MadNLPExecutionStats* stats_ptr, long* out) { return 0; }

int madnlp_delete_stats(MadNLPExecutionStats* stats_ptr) { return 0; }

int madnlp_create_solver(MadNLPSolver** solver_ptr_ptr, CNLPModel* nlp_ptr, OptsDict* opts_ptr) { return 0; }

int madnlp_delete_solver(MadNLPSolver* solver_ptr) { return 0; }

int madnlp_solve(MadNLPSolver* solver_ptr, OptsDict* opts_ptr, MadNLPExecutionStats** stats_ptr_ptr) { return 0; }
