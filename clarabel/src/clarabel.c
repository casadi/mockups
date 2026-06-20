/* Mockup Clarabel C library.
 *
 * Lets CasADi's clarabel conic plugin link, load and run its self-test on
 * platforms/build-combos where the real Clarabel (a Rust crate built via
 * Clarabel.cpp + cbindgen) is not available. The plugin references exactly the
 * f64 entry points of the Clarabel C API that the inline wrappers in
 * <Clarabel.h> dispatch to; everything else goes through the returned structs.
 *
 * Solves return ClarabelUnsolved with zeroed outputs (non-NULL buffers so an
 * accidental solve doesn't crash), so clarabel tests are expected to be skipped
 * (SKIP_CLARABEL_TESTS) rather than trusted. The real library, when present,
 * shadows this one.
 */

#include <Clarabel.h>
#include <string.h>

#if defined(_WIN32)
#define CLARABEL_MOCKUP_EXPORT __declspec(dllexport)
#else
#define CLARABEL_MOCKUP_EXPORT __attribute__((visibility("default")))
#endif

CLARABEL_MOCKUP_EXPORT void clarabel_CscMatrix_f64_init(ClarabelCscMatrix_f64 *ptr,
                                                        uintptr_t m,
                                                        uintptr_t n,
                                                        const uintptr_t *colptr,
                                                        const uintptr_t *rowval,
                                                        const double *nzval) {
  if (!ptr) return;
  ptr->m = m;
  ptr->n = n;
  ptr->colptr = colptr;
  ptr->rowval = rowval;
  ptr->nzval = nzval;
}

CLARABEL_MOCKUP_EXPORT ClarabelDefaultSettings_f64 clarabel_DefaultSettings_f64_default(void) {
  ClarabelDefaultSettings_f64 s;
  memset(&s, 0, sizeof(s));
  return s;
}

/* Opaque, non-NULL handle. Real lib returns a heap pointer; the plugin only
 * passes it back to us, never dereferences it. */
static int clarabel_mockup_solver_handle = 0;

CLARABEL_MOCKUP_EXPORT ClarabelDefaultSolver_f64 *clarabel_DefaultSolver_f64_new(
    const ClarabelCscMatrix_f64 *P, const double *q,
    const ClarabelCscMatrix_f64 *A, const double *b,
    uintptr_t n_cones, const ClarabelSupportedConeT_f64 *cones,
    const ClarabelDefaultSettings_f64 *settings) {
  (void)P; (void)q; (void)A; (void)b; (void)n_cones; (void)cones; (void)settings;
  return (ClarabelDefaultSolver_f64 *)&clarabel_mockup_solver_handle;
}

CLARABEL_MOCKUP_EXPORT void clarabel_DefaultSolver_f64_solve(ClarabelDefaultSolver_f64 *solver) {
  (void)solver;
}

CLARABEL_MOCKUP_EXPORT ClarabelDefaultSolution_f64 clarabel_DefaultSolver_f64_solution(
    ClarabelDefaultSolver_f64 *solver) {
  (void)solver;
  /* Non-NULL output buffers so a stray solve reading solution.x[i] is safe. */
  static double zeros[1024];
  ClarabelDefaultSolution_f64 sol;
  memset(&sol, 0, sizeof(sol));
  sol.x = zeros; sol.x_length = 0;
  sol.z = zeros; sol.z_length = 0;
  sol.s = zeros; sol.s_length = 0;
  sol.status = ClarabelUnsolved;
  return sol;
}

CLARABEL_MOCKUP_EXPORT void clarabel_DefaultSolver_f64_free(ClarabelDefaultSolver_f64 *solver) {
  (void)solver;
}
