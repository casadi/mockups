/* Mockup of ipmc solver: the declarations of ipmc's public header (branch ipmc-v3),
 * field for field, so a plugin compiled here has the layout the real library expects. */

#ifndef IPMC_H
#define IPMC_H

#include <stddef.h>
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
struct blasfeo_dvec;

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ipmc_int
#define ipmc_int int
#endif

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

#ifndef IPMC_IMPLEMENTATION
typedef struct IpmcSolver IpmcSolver;
#endif

struct IpmcProblem {

  ipmc_int K;

  const ipmc_int* nu;

  const ipmc_int* nx;

  const ipmc_int* ng;

  const ipmc_int* ng_ineq;

  ipmc_int nxc;

  const ipmc_int* ns;

  const ipmc_int* soft_lo;

  const ipmc_int* soft_up;

  ipmc_int nxc_slack;

  const ipmc_int* slack_helper;

  const ipmc_int* nb;

  const ipmc_int* idxb;
};
typedef struct IpmcProblem IpmcProblem;

enum IpmcError {
  IPMC_OK = 0,

  IPMC_ERR_NS = 1,

  IPMC_ERR_SOFT_IDX = 2,

  IPMC_ERR_PENALTY = 3,

  IPMC_ERR_SLACK_BOUND = 4,

  IPMC_ERR_NXC = 5,

  IPMC_ERR_SLACK_HELPER = 6,

  IPMC_ERR_BOUND_IDX = 7,

  IPMC_ERR_MEMORY = 8,
  /* MOCKUP ONLY, and deliberately far away from the real codes: what
     ipmc_memsize() and ipmc_create_in() report here, so that a build that
     reaches a mockup libipmc at RUNTIME (rather than failing to load, which is
     the ordinary outcome) says so instead of quietly solving nothing.  The
     real ipmc never returns it, and no consumer should name the enumerator. */
  IPMC_ERR_MOCKUP = 99
};
typedef enum IpmcError IpmcError;

IPMC_EXPORT size_t ipmc_memsize(const IpmcProblem* problem, IpmcError* error);

IPMC_EXPORT IpmcSolver* ipmc_create_in(const IpmcProblem* problem, void* mem, size_t size,
                                       IpmcError* error);

IPMC_EXPORT void ipmc_set_bounds(IpmcSolver* s, const double* lower, const double* upper);

IPMC_EXPORT void ipmc_set_initial(IpmcSolver* s, const double* ux);

IPMC_EXPORT IpmcError ipmc_set_soft_penalty(IpmcSolver* s, const double* Z, const double* z,
                                            const double* ubs);

IPMC_EXPORT void ipmc_set_initial_slack(IpmcSolver* s, const double* s0);

IPMC_EXPORT int ipmc_option_type(const char* name);
IPMC_EXPORT int ipmc_set_option_double(IpmcSolver* s, const char* name, double val);
IPMC_EXPORT int ipmc_set_option_int(IpmcSolver* s, const char* name, int val);
IPMC_EXPORT int ipmc_set_option_bool(IpmcSolver* s, const char* name, int val);
IPMC_EXPORT int ipmc_set_option_string(IpmcSolver* s, const char* name, const char* val);

typedef void (*IpmcWrite)(const char* msg, int num);
typedef void (*IpmcFlush)(void);
IPMC_EXPORT void ipmc_set_output(IpmcSolver* s, IpmcWrite write, IpmcFlush flush);

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

struct IpmcEval {

  IpmcRequest request;

  ipmc_int iter;

  const double* x;

  const double* lam;

  double obj_scale;

  double* obj;

  double* grad;

  double* cv;

  struct blasfeo_dmat* BAt;

  struct blasfeo_dvec* b;

  struct blasfeo_dmat* Gt;

  struct blasfeo_dvec* g;

  struct blasfeo_dmat* Gt_ineq;

  struct blasfeo_dvec* g_ineq;

  struct blasfeo_dmat* RSQ;

  struct blasfeo_dvec* RSQ_slack;

  struct blasfeo_dvec* rq;

  double objective;

  double constr_viol;

  ipmc_int restoration;
};
typedef struct IpmcEval IpmcEval;

IPMC_EXPORT void ipmc_start(IpmcSolver* s);

IPMC_EXPORT IpmcRequest ipmc_step(IpmcSolver* s, IpmcEval* e);

IPMC_EXPORT void ipmc_abort(IpmcSolver* s);

enum IpmcStatus {

  IPMC_SOLVED = 0,

  IPMC_FAILED = 1,

  IPMC_INFEASIBLE = 2,

  IPMC_INTERRUPTED = 3,

  IPMC_RETURNED_FROM_RESTO = 100
};
typedef enum IpmcStatus IpmcStatus;

IPMC_EXPORT int ipmc_get_status(IpmcSolver* s);

struct IpmcLayout {

  ipmc_int K;

  const ipmc_int* nu;
  const ipmc_int* nx;
  const ipmc_int* ng;
  const ipmc_int* ng_ineq;

  ipmc_int nxc;

  ipmc_int nxc_slack;

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

IPMC_EXPORT ipmc_int ipmc_get_slack(IpmcSolver* s, double* sv);

IPMC_EXPORT ipmc_int ipmc_get_slack_dual(IpmcSolver* s, double* zs_lo, double* zs_up);

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
}
#endif

#endif
