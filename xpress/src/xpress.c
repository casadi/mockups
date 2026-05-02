#include "xprs.h"

int XPRSinit(const char *a) { (void)a; return 0; }
int XPRSfree(void) { return 0; }
int XPRScreateprob(XPRSprob *a) { (void)a; return 0; }
int XPRSdestroyprob(XPRSprob a) { (void)a; return 0; }
int XPRSloadqp(XPRSprob a, const char *b, int c, int d, const char e[], const double f[], const double g[], const double h[], const int i[], const int j[], const int k[], const double l[], const double m[], const double n[], int o, const int p[], const int q[], const double r[]) {
  (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j; (void)k; (void)l; (void)m; (void)n; (void)o; (void)p; (void)q; (void)r;
  return 0;
}
int XPRSchgcoltype(XPRSprob a, int b, const int c[], const char d[]) { (void)a; (void)b; (void)c; (void)d; return 0; }
int XPRSaddsets(XPRSprob a, int b, int c, const char d[], const int e[], const int f[], const double g[]) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; return 0; }
int XPRSaddcols(XPRSprob a, int b, int c, const double d[], const int e[], const int f[], const double g[], const double h[], const double i[]) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; return 0; }
int XPRSaddrows(XPRSprob a, int b, int c, const char d[], const double e[], const double f[], const int g[], const int h[], const double i[]) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; return 0; }
int XPRSaddqmatrix(XPRSprob a, int b, int c, const int d[], const int e[], const double f[]) { (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; return 0; }
int XPRSlpoptimize(XPRSprob a, const char *b) { (void)a; (void)b; return 0; }
int XPRSmipoptimize(XPRSprob a, const char *b) { (void)a; (void)b; return 0; }
int XPRSgetsolution(XPRSprob a, int *b, double c[], int d, int e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
int XPRSgetduals(XPRSprob a, int *b, double c[], int d, int e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
int XPRSgetredcosts(XPRSprob a, int *b, double c[], int d, int e) { (void)a; (void)b; (void)c; (void)d; (void)e; return 0; }
int XPRSgetintattrib(XPRSprob a, int b, int *c) { (void)a; (void)b; (void)c; return 0; }
int XPRSgetdblattrib(XPRSprob a, int b, double *c) { (void)a; (void)b; (void)c; return 0; }
int XPRSsetintcontrol(XPRSprob a, int b, int c) { (void)a; (void)b; (void)c; return 0; }
int XPRSsetintcontrol64(XPRSprob a, int b, XPRSint64 c) { (void)a; (void)b; (void)c; return 0; }
int XPRSsetdblcontrol(XPRSprob a, int b, double c) { (void)a; (void)b; (void)c; return 0; }
int XPRSsetstrcontrol(XPRSprob a, int b, const char *c) { (void)a; (void)b; (void)c; return 0; }
int XPRSgetcontrolinfo(XPRSprob a, const char *b, int *c, int *d) { (void)a; (void)b; (void)c; (void)d; return 0; }
