/* Mockup of ipmc (Yacoda). */

#include <ipmc/ipmc.h>

#include <string.h>

/* Zero bytes and IPMC_ERR_MOCKUP: a consumer that sizes a block with this and
   builds in it gets the refusal, not a solver that quietly solves nothing. */
IPMC_EXPORT size_t ipmc_memsize(const IpmcProblem* problem, IpmcError* error) {
  (void) problem;
  if (error) *error = IPMC_ERR_MOCKUP;
  return 0;
}

IPMC_EXPORT IpmcSolver* ipmc_create_in(const IpmcProblem* problem, void* mem, size_t size,
                                       IpmcError* error) {
  (void) problem; (void) mem; (void) size;
  if (error) *error = IPMC_ERR_MOCKUP;
  return 0;
}

IPMC_EXPORT void ipmc_set_bounds(IpmcSolver* s, const double* lower, const double* upper) {
  (void) s; (void) lower; (void) upper;
}

IPMC_EXPORT void ipmc_set_initial(IpmcSolver* s, const double* ux) {
  (void) s; (void) ux;
}

IPMC_EXPORT IpmcError ipmc_set_soft_penalty(IpmcSolver* s, const double* Z, const double* z,
                                            const double* ubs) {
  (void) s; (void) Z; (void) z; (void) ubs;
  return IPMC_ERR_MOCKUP;
}

IPMC_EXPORT void ipmc_set_initial_slack(IpmcSolver* s, const double* s0) {
  (void) s; (void) s0;
}

IPMC_EXPORT int ipmc_option_type(const char* name) { (void) name; return -1; }

IPMC_EXPORT int ipmc_set_option_double(IpmcSolver* s, const char* name, double val) {
  (void) s; (void) name; (void) val; return 1;
}
IPMC_EXPORT int ipmc_set_option_int(IpmcSolver* s, const char* name, int val) {
  (void) s; (void) name; (void) val; return 1;
}
IPMC_EXPORT int ipmc_set_option_bool(IpmcSolver* s, const char* name, int val) {
  (void) s; (void) name; (void) val; return 1;
}
IPMC_EXPORT int ipmc_set_option_string(IpmcSolver* s, const char* name, const char* val) {
  (void) s; (void) name; (void) val; return 1;
}

IPMC_EXPORT void ipmc_set_output(IpmcSolver* s, IpmcWrite write, IpmcFlush flush) {
  (void) s; (void) write; (void) flush;
}

IPMC_EXPORT void ipmc_start(IpmcSolver* s) { (void) s; }

IPMC_EXPORT IpmcRequest ipmc_step(IpmcSolver* s, IpmcEval* e) {
  (void) s;
  if (e) {
    memset(e, 0, sizeof(*e));
    e->request = IPMC_DONE;
  }
  return IPMC_DONE;
}

IPMC_EXPORT void ipmc_abort(IpmcSolver* s) { (void) s; }

IPMC_EXPORT int ipmc_get_status(IpmcSolver* s) { (void) s; return IPMC_FAILED; }

/* Zeroed rather than NULL: a caller that ignores the ipmc_create_in() failure
   and reads on gets an empty problem (K == 0, no rows, no slacks) instead of
   a null dereference. */
IPMC_EXPORT const IpmcLayout* ipmc_get_layout(IpmcSolver* s) {
  static const IpmcLayout layout = {0};
  (void) s;
  return &layout;
}

IPMC_EXPORT const double* ipmc_get_primal(IpmcSolver* s) { (void) s; return 0; }
IPMC_EXPORT const double* ipmc_get_dual(IpmcSolver* s) { (void) s; return 0; }

IPMC_EXPORT ipmc_int ipmc_get_slack(IpmcSolver* s, double* sv) {
  (void) s; (void) sv; return 0;
}
IPMC_EXPORT ipmc_int ipmc_get_slack_dual(IpmcSolver* s, double* zs_lo, double* zs_up) {
  (void) s; (void) zs_lo; (void) zs_up; return 0;
}

IPMC_EXPORT const IpmcStats* ipmc_get_stats(IpmcSolver* s) {
  static const IpmcStats stats = {0};
  (void) s;
  return &stats;
}
