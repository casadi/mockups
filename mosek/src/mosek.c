#include "mosek.h"

MSKrescodee MSK_makeenv(MSKenv_t *a, const char *b) { (void)a; (void)b; return 0; }
MSKrescodee MSK_deleteenv(MSKenv_t *a) { (void)a; return 0; }
MSKrescodee MSK_maketask(MSKenv_t a, MSKint32t b, MSKint32t c, MSKtask_t *d) { (void)a; (void)b; (void)c; (void)d; return 0; }
MSKrescodee MSK_deletetask(MSKtask_t *a) { (void)a; return 0; }

MSKrescodee MSK_appendvars(MSKtask_t a, MSKint32t b) { (void)a; (void)b; return 0; }
MSKrescodee MSK_appendcons(MSKtask_t a, MSKint32t b) { (void)a; (void)b; return 0; }
MSKrescodee MSK_putobjsense(MSKtask_t a, MSKobjsensee b) { (void)a; (void)b; return 0; }

MSKrescodee MSK_putcj(MSKtask_t a, MSKint32t b, MSKrealt c) { (void)a; (void)b; (void)c; return 0; }
MSKrescodee MSK_putvarbound(MSKtask_t a, MSKint32t b, MSKboundkeye c, MSKrealt d, MSKrealt e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_putconbound(MSKtask_t a, MSKint32t b, MSKboundkeye c, MSKrealt d, MSKrealt e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_putacol(MSKtask_t a, MSKint32t b, MSKint32t c, const MSKint32t *d, const MSKrealt *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_putarow(MSKtask_t a, MSKint32t b, MSKint32t c, const MSKint32t *d, const MSKrealt *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_putqobj(MSKtask_t a, MSKint32t b, const MSKint32t *c, const MSKint32t *d, const MSKrealt *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_putvartype(MSKtask_t a, MSKint32t b, MSKvariabletypee c) { (void)a; (void)b; (void)c; return 0; }
MSKrescodee MSK_appendcone(MSKtask_t a, MSKconetypee b, MSKrealt c, MSKint32t d, const MSKint32t *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }

MSKrescodee MSK_optimizetrm(MSKtask_t a, MSKrescodee *b) { (void)a; (void)b; return 0; }

MSKrescodee MSK_getsolsta(MSKtask_t a, MSKsoltypee b, MSKsolstae *c) { (void)a; (void)b; (void)c; return 0; }
MSKrescodee MSK_getprosta(MSKtask_t a, MSKsoltypee b, MSKprostae *c) { (void)a; (void)b; (void)c; return 0; }
MSKrescodee MSK_solutiondef(MSKtask_t a, MSKsoltypee b, MSKbooleant *c) { (void)a; (void)b; (void)c; return 0; }
MSKrescodee MSK_getxxslice(MSKtask_t a, MSKsoltypee b, MSKint32t c, MSKint32t d, MSKrealt *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_getyslice(MSKtask_t a, MSKsoltypee b, MSKint32t c, MSKint32t d, MSKrealt *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_getslxslice(MSKtask_t a, MSKsoltypee b, MSKint32t c, MSKint32t d, MSKrealt *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_getsuxslice(MSKtask_t a, MSKsoltypee b, MSKint32t c, MSKint32t d, MSKrealt *e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
MSKrescodee MSK_getprimalobj(MSKtask_t a, MSKsoltypee b, MSKrealt *c) { (void)a; (void)b; (void)c; return 0; }

MSKrescodee MSK_putnaintparam(MSKtask_t a, const char *b, MSKint32t c) { (void)a; (void)b; (void)c; return 0; }
MSKrescodee MSK_putnadouparam(MSKtask_t a, const char *b, MSKrealt c) { (void)a; (void)b; (void)c; return 0; }
MSKrescodee MSK_putnastrparam(MSKtask_t a, const char *b, const char *c) { (void)a; (void)b; (void)c; return 0; }

MSKrescodee MSK_linkfunctotaskstream(MSKtask_t a, MSKstreamtypee b, MSKuserhandle_t c, MSKstreamfunc d) { (void)a; (void)b; (void)c; (void)d; return 0; }
