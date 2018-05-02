# Minimal repro of InterruptedException not being caught

Demonstrates that a `throw Rcpp::internal::InterruptedException()` in compilation unit A cannot be caught by a `catch(Rcpp::internal::InterruptedException)` in compilation unit B.

Repro:

1. Run `exceptiontest::throwAndCatchInterrupt()`, note that it prints `Interrupted` (the desired behavior).
2. Run the following code (will create a separate compilation unit):
```r
Rcpp::cppFunction('
void throwAndCatchInterrupt2() {
  typedef void (*tifunc)();
  tifunc func = (tifunc)R_GetCCallable("exceptiontest", "throwInterrupt");
  try {
    func();
  } catch (Rcpp::internal::InterruptedException) {
    fprintf(stderr, "Interrupted\\n");
  } catch (...) {
    fprintf(stderr, "Unknown error\\n");
  }
}
')
```
3. Run the newly compiled `throwAndCatchInterrupt2()`, note that it prints `Unknown error`.