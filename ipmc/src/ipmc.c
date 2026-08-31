/* Mockup of ipmc (Yacoda). */

#include <ipmc/ipmc.h>

#include <string.h>

IPMC_EXPORT IpmcSolver* ipmc_create(const IpmcProblem* problem, IpmcError* error) {
  (void) problem;
  if (error) *error = IPMC_ERR_MOCKUP;
  return 0;
}

IPMC_EXPORT void ipmc_destroy(IpmcSolver* s) { (void) s; }

IPMC_EXPORT void ipmc_set_bounds(IpmcSolver* s,
                                 const double* lower,
                                 const double* upper) {
  (void) s; (void) lower; (void) upper;
}

IPMC_EXPORT void ipmc_set_initial(IpmcSolver* s, const double* ux) {
  (void) s; (void) ux;
}

IPMC_EXPORT IpmcError ipmc_set_soft_penalty(IpmcSolver* s,
                                            const double* Zl,
                                            const double* Zu,
                                            const double* zl,
                                            const double* zu,
                                            const double* ubsl,
                                            const double* ubsu) {
  (void) s; (void) Zl; (void) Zu; (void) zl; (void) zu; (void) ubsl; (void) ubsu;
  return IPMC_ERR_MOCKUP;
}

IPMC_EXPORT void ipmc_set_initial_slack(IpmcSolver* s,
                                        const double* sl,
                                        const double* su) {
  (void) s; (void) sl; (void) su;
}

/* -1 is "no such option", which is also the honest answer for a library
   that has no options because it has no solver. */
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

/* Zeroed rather than NULL: a caller that ignores the ipmc_create() failure
   and reads on gets an empty problem (K == 0, no rows, no slacks) instead of
   a null dereference. */
IPMC_EXPORT const IpmcLayout* ipmc_get_layout(IpmcSolver* s) {
  static const IpmcLayout layout = {0};
  (void) s;
  return &layout;
}

IPMC_EXPORT const double* ipmc_get_primal(IpmcSolver* s) { (void) s; return 0; }
IPMC_EXPORT const double* ipmc_get_dual(IpmcSolver* s) { (void) s; return 0; }

IPMC_EXPORT ipmc_int ipmc_get_slack(IpmcSolver* s, double* sl, double* su) {
  (void) s; (void) sl; (void) su; return 0;
}
IPMC_EXPORT ipmc_int ipmc_get_slack_dual(IpmcSolver* s, double* zsl, double* zsu) {
  (void) s; (void) zsl; (void) zsu; return 0;
}

IPMC_EXPORT const IpmcStats* ipmc_get_stats(IpmcSolver* s) {
  static const IpmcStats stats = {0};
  (void) s;
  return &stats;
}
