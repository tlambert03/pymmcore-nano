#include <nanobind/nanobind.h>

#include "MMCore.h"

namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(_pymmcore_nano, m) {
  m.doc() = "This is a \"hello world\" example with nanobind";
  m.def("add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
}