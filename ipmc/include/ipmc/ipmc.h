/* Mockup of ipmc solver */

#ifndef IPMC_H
#define IPMC_H

/* ipmc's own header includes <blasfeo.h>, because a caller that answers an
 * IPMC_EVAL_CONSTR_JAC or IPMC_EVAL_LAG_HESS request has to fill in blasfeo
 * matrices.  Nothing HERE needs blasfeo's definitions -- the matrices only
 * ever cross this interface by pointer -- but a consumer built against the
 * mockup must see the same declarations it would see against the real
 * header, so include blasfeo when it is reachable and fall back on an
 * incomplete type when it is not (which is the case when this mockup is
 * built on its own). */
#if defined(__has_include)
#if __has_include(<blasfeo.h>)
#include <blasfeo.h>
#endif
#endif
struct blasfeo_dmat;

#ifdef __cplusplus
extern "C" {
#endif

/* Integer type used throughout the interface. */
#ifndef ipmc_int
#define ipmc_int int
#endif

/* Symbol visibility in DLLs */
#ifndef IPMC_EXPORT
#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#if defined(STATIC_LINKED)
#define IPMC_EXPORT
#else
#define IPMC_EXPORT __declspec(dllexport)
#endif
#elif defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#define IPMC_EXPORT __attribute__((visibility("default")))
#else
#define IPMC_EXPORT
#endif
#endif

/* The solver.  Opaque; created by ipmc_create, released by ipmc_destroy. */
#ifndef IPMC_IMPLEMENTATION
typedef struct IpmcSolver IpmcSolver;
#endif

/* ===========================================================================
 *  The problem
 * =========================================================================== */

/// @brief the structure of the optimal control problem
struct IpmcProblem {
  /// @brief number of stages, >= 1
  ipmc_int K;
  /// @brief [K] number of inputs u_k of stage k
  const ipmc_int* nu;
  /// @brief [K] number of states x_k of stage k
  const ipmc_int* nx;
  /// @brief [K] number of stagewise equality rows of stage k
  const ipmc_int* ng;
  /// @brief [K] number of stagewise inequality rows of stage k
  const ipmc_int* ng_ineq;
  /// @brief number of trailing components of every x_k with identity
  ///        dynamics, 0 for none
  ipmc_int nxc;
  /// @brief [K] number of slack pairs of stage k, NULL for no soft rows
  const ipmc_int* ns;
  /// @brief [sum(ng_ineq)] which slack pair softens each inequality row,
  ///        -1 for a hard row, NULL when every row is hard
  const ipmc_int* soft_idx;
};
typedef struct IpmcProblem IpmcProblem;

/// @brief why ipmc refused a description
enum IpmcError {
  IPMC_OK = 0,
  IPMC_ERR_NS = 1,
  IPMC_ERR_SOFT_IDX = 2,
  IPMC_ERR_PENALTY = 3,
  IPMC_ERR_SLACK_BOUND = 4,
  IPMC_ERR_NXC = 5,
  /* MOCKUP ONLY, and deliberately far away from the real codes: what
     ipmc_create() reports here, so that a build that reaches a mockup
     libipmc at RUNTIME (rather than failing to load, which is the ordinary
     outcome) says so instead of quietly solving nothing.  The real ipmc
     never returns it, and no consumer should name the enumerator. */
  IPMC_ERR_MOCKUP = 99
};
typedef enum IpmcError IpmcError;

IPMC_EXPORT IpmcSolver* ipmc_create(const IpmcProblem* problem, IpmcError* error);
IPMC_EXPORT void ipmc_destroy(IpmcSolver* s);

/* ===========================================================================
 *  The numbers that can change between solves
 * =========================================================================== */

IPMC_EXPORT void ipmc_set_bounds(IpmcSolver* s,
                                 const double* lower,
                                 const double* upper);
IPMC_EXPORT void ipmc_set_initial(IpmcSolver* s, const double* ux);
IPMC_EXPORT IpmcError ipmc_set_soft_penalty(IpmcSolver* s,
                                            const double* Zl,
                                            const double* Zu,
                                            const double* zl,
                                            const double* zu,
                                            const double* ubsl,
                                            const double* ubsu);
IPMC_EXPORT void ipmc_set_initial_slack(IpmcSolver* s,
                                        const double* sl,
                                        const double* su);

/* ===========================================================================
 *  Options
 * =========================================================================== */

/// @brief the type of an option: -1 not found, 0 double, 1 int, 2 bool, 3 string
IPMC_EXPORT int ipmc_option_type(const char* name);
IPMC_EXPORT int ipmc_set_option_double(IpmcSolver* s, const char* name, double val);
IPMC_EXPORT int ipmc_set_option_int(IpmcSolver* s, const char* name, int val);
IPMC_EXPORT int ipmc_set_option_bool(IpmcSolver* s, const char* name, int val);
IPMC_EXPORT int ipmc_set_option_string(IpmcSolver* s, const char* name, const char* val);

typedef void (*IpmcWrite)(const char* msg, int num);
typedef void (*IpmcFlush)(void);
IPMC_EXPORT void ipmc_set_output(IpmcSolver* s, IpmcWrite write, IpmcFlush flush);

/* ===========================================================================
 *  Driving the solver
 * =========================================================================== */

/// @brief what ipmc wants before it can continue
enum IpmcRequest {
  IPMC_EVAL_OBJ,
  IPMC_EVAL_OBJ_GRAD,
  IPMC_EVAL_CONSTR_VIOL,
  IPMC_EVAL_CONSTR_JAC,
  IPMC_EVAL_LAG_HESS,
  IPMC_POST_ITERATION,
  IPMC_DONE
};
typedef enum IpmcRequest IpmcRequest;

/// @brief the request ipmc_step() just returned, and everything it needs
struct IpmcEval {
  IpmcRequest request;
  ipmc_int iter;
  const double* x;
  const double* lam;
  double obj_scale;
  double* obj;
  double* grad;
  double* cv;
  struct blasfeo_dmat* BAbt;
  struct blasfeo_dmat* Ggt;
  struct blasfeo_dmat* Ggt_ineq;
  struct blasfeo_dmat* RSQrqt;
  double objective;
  double constr_viol;
  ipmc_int restoration;
};
typedef struct IpmcEval IpmcEval;

IPMC_EXPORT void ipmc_start(IpmcSolver* s);
IPMC_EXPORT IpmcRequest ipmc_step(IpmcSolver* s, IpmcEval* e);
IPMC_EXPORT void ipmc_abort(IpmcSolver* s);

/// @brief how the solve ended
enum IpmcStatus {
  IPMC_SOLVED = 0,
  IPMC_FAILED = 1,
  IPMC_INFEASIBLE = 2,
  IPMC_INTERRUPTED = 3,
  IPMC_RETURNED_FROM_RESTO = 100
};
typedef enum IpmcStatus IpmcStatus;

IPMC_EXPORT int ipmc_get_status(IpmcSolver* s);

/* ===========================================================================
 *  Reading the answer
 * =========================================================================== */

/// @brief where everything sits in the vectors that cross this interface
struct IpmcLayout {
  ipmc_int K;
  const ipmc_int* nu;
  const ipmc_int* nx;
  const ipmc_int* ng;
  const ipmc_int* ng_ineq;
  ipmc_int nxc;
  ipmc_int max_nu;
  ipmc_int max_nx;
  ipmc_int max_ng;
  ipmc_int max_ngineq;
  const ipmc_int* ux_offs;
  const ipmc_int* g_offs;
  const ipmc_int* dyn_eq_offs;
  const ipmc_int* g_ineq_offs;
  const ipmc_int* dyn_offs;
  const ipmc_int* ineq_offs;
  ipmc_int n_ineqs;
  const ipmc_int* ns;
  const ipmc_int* soft_offs;
  ipmc_int n_soft;
};
typedef struct IpmcLayout IpmcLayout;

IPMC_EXPORT const IpmcLayout* ipmc_get_layout(IpmcSolver* s);
IPMC_EXPORT const double* ipmc_get_primal(IpmcSolver* s);
IPMC_EXPORT const double* ipmc_get_dual(IpmcSolver* s);
IPMC_EXPORT ipmc_int ipmc_get_slack(IpmcSolver* s, double* sl, double* su);
IPMC_EXPORT ipmc_int ipmc_get_slack_dual(IpmcSolver* s, double* zsl, double* zsu);

/// @brief what the solve cost
struct IpmcStats {
  double compute_sd_time;
  double duinf_time;
  double eval_hess_time;
  double eval_jac_time;
  double eval_cv_time;
  double eval_grad_time;
  double eval_obj_time;
  double initialization_time;
  double time_total;
  int eval_hess_count;
  int eval_jac_count;
  int eval_cv_count;
  int eval_grad_count;
  int eval_obj_count;
  int iterations_count;
  int restoration_iterations_count;
  int return_flag;
};
typedef struct IpmcStats IpmcStats;

IPMC_EXPORT const IpmcStats* ipmc_get_stats(IpmcSolver* s);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif  /* IPMC_H */
