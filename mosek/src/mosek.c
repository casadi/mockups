#define DLL_IMPLEMENTATION
#include "mosek.h"

#ifdef _WIN32

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/* Function-pointer storage.  Names below are rewritten by mosek.h's
 * `#define MSK_xxx adaptor_MSK_xxx`, so the symbols actually exported
 * from this DLL are adaptor_MSK_*. */
MSKrescodee (*MSK_makeenv)(MSKenv_t *, const char *) = NULL;
MSKrescodee (*MSK_deleteenv)(MSKenv_t *) = NULL;
MSKrescodee (*MSK_maketask)(MSKenv_t, MSKint32t, MSKint32t, MSKtask_t *) = NULL;
MSKrescodee (*MSK_deletetask)(MSKtask_t *) = NULL;
MSKrescodee (*MSK_appendvars)(MSKtask_t, MSKint32t) = NULL;
MSKrescodee (*MSK_appendcons)(MSKtask_t, MSKint32t) = NULL;
MSKrescodee (*MSK_putobjsense)(MSKtask_t, MSKobjsensee) = NULL;
MSKrescodee (*MSK_putcj)(MSKtask_t, MSKint32t, MSKrealt) = NULL;
MSKrescodee (*MSK_putvarbound)(MSKtask_t, MSKint32t, MSKboundkeye, MSKrealt, MSKrealt) = NULL;
MSKrescodee (*MSK_putconbound)(MSKtask_t, MSKint32t, MSKboundkeye, MSKrealt, MSKrealt) = NULL;
MSKrescodee (*MSK_putacol)(MSKtask_t, MSKint32t, MSKint32t, const MSKint32t *, const MSKrealt *) = NULL;
MSKrescodee (*MSK_putarow)(MSKtask_t, MSKint32t, MSKint32t, const MSKint32t *, const MSKrealt *) = NULL;
MSKrescodee (*MSK_putqobj)(MSKtask_t, MSKint32t, const MSKint32t *, const MSKint32t *, const MSKrealt *) = NULL;
MSKrescodee (*MSK_putvartype)(MSKtask_t, MSKint32t, MSKvariabletypee) = NULL;
MSKrescodee (*MSK_appendcone)(MSKtask_t, MSKconetypee, MSKrealt, MSKint32t, const MSKint32t *) = NULL;
MSKrescodee (*MSK_optimizetrm)(MSKtask_t, MSKrescodee *) = NULL;
MSKrescodee (*MSK_getsolsta)(MSKtask_t, MSKsoltypee, MSKsolstae *) = NULL;
MSKrescodee (*MSK_getprosta)(MSKtask_t, MSKsoltypee, MSKprostae *) = NULL;
MSKrescodee (*MSK_solutiondef)(MSKtask_t, MSKsoltypee, MSKbooleant *) = NULL;
MSKrescodee (*MSK_getxxslice)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *) = NULL;
MSKrescodee (*MSK_getyslice)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *) = NULL;
MSKrescodee (*MSK_getslxslice)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *) = NULL;
MSKrescodee (*MSK_getsuxslice)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *) = NULL;
MSKrescodee (*MSK_getprimalobj)(MSKtask_t, MSKsoltypee, MSKrealt *) = NULL;
MSKrescodee (*MSK_putnaintparam)(MSKtask_t, const char *, MSKint32t) = NULL;
MSKrescodee (*MSK_putnadouparam)(MSKtask_t, const char *, MSKrealt) = NULL;
MSKrescodee (*MSK_putnastrparam)(MSKtask_t, const char *, const char *) = NULL;
MSKrescodee (*MSK_linkfunctotaskstream)(MSKtask_t, MSKstreamtypee, MSKuserhandle_t, MSKstreamfunc) = NULL;

static HINSTANCE h = NULL;

void mosek_adaptor_unload(void) {
    if (h) {
        FreeLibrary(h);
        h = NULL;
    }
}

/* `NAME` is used only with `#` and `##` so it is not pre-expanded by
 * the `#define MSK_xxx adaptor_MSK_xxx` macros from the header. */
#define LOAD_SYM(NAME, SIG) \
    do { \
        adaptor_##NAME = (SIG) GetProcAddress(h, #NAME); \
        if (adaptor_##NAME == NULL) { \
            snprintf(err_msg, err_msg_len, \
                "Could not find symbol '" #NAME "' in mosek64_%s.dll", suffix); \
            return 2; \
        } \
    } while (0)

int mosek_adaptor_load(char* err_msg, unsigned int err_msg_len) {
    const char* suffix = getenv("MOSEK_VERSION");
    if (suffix == NULL) {
        snprintf(err_msg, err_msg_len,
            "Mosek load adaptor needs an environmental variable <MOSEK_VERSION> "
            "such that mosek64_<MOSEK_VERSION>.dll can be found "
            "(e.g. MOSEK_VERSION=11_1).");
        return 1;
    }

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "mosek64_%s.dll", suffix);

    h = LoadLibraryA(buffer);
    if (!h) {
        snprintf(err_msg, err_msg_len,
            "Could not find library '%s'. "
            "Consider adding the appropriate Mosek folder to environmental variable 'PATH', "
            "or specifying a different value for 'MOSEK_VERSION'.",
            buffer);
        return 1;
    }

    LOAD_SYM(MSK_makeenv,              MSKrescodee (*)(MSKenv_t *, const char *));
    LOAD_SYM(MSK_deleteenv,            MSKrescodee (*)(MSKenv_t *));
    LOAD_SYM(MSK_maketask,             MSKrescodee (*)(MSKenv_t, MSKint32t, MSKint32t, MSKtask_t *));
    LOAD_SYM(MSK_deletetask,           MSKrescodee (*)(MSKtask_t *));
    LOAD_SYM(MSK_appendvars,           MSKrescodee (*)(MSKtask_t, MSKint32t));
    LOAD_SYM(MSK_appendcons,           MSKrescodee (*)(MSKtask_t, MSKint32t));
    LOAD_SYM(MSK_putobjsense,          MSKrescodee (*)(MSKtask_t, MSKobjsensee));
    LOAD_SYM(MSK_putcj,                MSKrescodee (*)(MSKtask_t, MSKint32t, MSKrealt));
    LOAD_SYM(MSK_putvarbound,          MSKrescodee (*)(MSKtask_t, MSKint32t, MSKboundkeye, MSKrealt, MSKrealt));
    LOAD_SYM(MSK_putconbound,          MSKrescodee (*)(MSKtask_t, MSKint32t, MSKboundkeye, MSKrealt, MSKrealt));
    LOAD_SYM(MSK_putacol,              MSKrescodee (*)(MSKtask_t, MSKint32t, MSKint32t, const MSKint32t *, const MSKrealt *));
    LOAD_SYM(MSK_putarow,              MSKrescodee (*)(MSKtask_t, MSKint32t, MSKint32t, const MSKint32t *, const MSKrealt *));
    LOAD_SYM(MSK_putqobj,              MSKrescodee (*)(MSKtask_t, MSKint32t, const MSKint32t *, const MSKint32t *, const MSKrealt *));
    LOAD_SYM(MSK_putvartype,           MSKrescodee (*)(MSKtask_t, MSKint32t, MSKvariabletypee));
    LOAD_SYM(MSK_appendcone,           MSKrescodee (*)(MSKtask_t, MSKconetypee, MSKrealt, MSKint32t, const MSKint32t *));
    LOAD_SYM(MSK_optimizetrm,          MSKrescodee (*)(MSKtask_t, MSKrescodee *));
    LOAD_SYM(MSK_getsolsta,            MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKsolstae *));
    LOAD_SYM(MSK_getprosta,            MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKprostae *));
    LOAD_SYM(MSK_solutiondef,          MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKbooleant *));
    LOAD_SYM(MSK_getxxslice,           MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *));
    LOAD_SYM(MSK_getyslice,            MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *));
    LOAD_SYM(MSK_getslxslice,          MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *));
    LOAD_SYM(MSK_getsuxslice,          MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKint32t, MSKint32t, MSKrealt *));
    LOAD_SYM(MSK_getprimalobj,         MSKrescodee (*)(MSKtask_t, MSKsoltypee, MSKrealt *));
    LOAD_SYM(MSK_putnaintparam,        MSKrescodee (*)(MSKtask_t, const char *, MSKint32t));
    LOAD_SYM(MSK_putnadouparam,        MSKrescodee (*)(MSKtask_t, const char *, MSKrealt));
    LOAD_SYM(MSK_putnastrparam,        MSKrescodee (*)(MSKtask_t, const char *, const char *));
    LOAD_SYM(MSK_linkfunctotaskstream, MSKrescodee (*)(MSKtask_t, MSKstreamtypee, MSKuserhandle_t, MSKstreamfunc));

    return 0;
}

#undef LOAD_SYM

#else  /* _WIN32 */

/* Linux/Mac: no-op stubs.  The real libmosek64.{so,dylib} replaces this
 * library at runtime via LD_LIBRARY_PATH / DYLD_LIBRARY_PATH (the real
 * library is shipped under the unversioned name on these platforms). */

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

#endif  /* _WIN32 */
