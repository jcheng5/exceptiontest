
#include <Rcpp.h>
using namespace Rcpp;

extern "C" void throwInterrupt() {
  throw Rcpp::internal::InterruptedException();
}

// [[Rcpp::export]]
void throwAndCatchInterrupt() {
  typedef void (*tifunc)();
  tifunc func = (tifunc)R_GetCCallable("exceptiontest", "throwInterrupt");
  try {
    func();
  } catch (Rcpp::internal::InterruptedException) {
    fprintf(stderr, "Interrupted\n");
  } catch (...) {
    fprintf(stderr, "Unknown error\n");
  }
}
