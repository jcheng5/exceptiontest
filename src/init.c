#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _exceptiontest_throwAndCatchInterrupt();

static const R_CallMethodDef CallEntries[] = {
  {"_exceptiontest_throwAndCatchInterrupt",   (DL_FUNC) &_exceptiontest_throwAndCatchInterrupt,   0},
  {NULL, NULL, 0}
};

void throwInterrupt();

void R_init_exceptiontest(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_RegisterCCallable("exceptiontest", "throwInterrupt", (DL_FUNC)&throwInterrupt);
}
