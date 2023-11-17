//<LICENSE>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void bindBM4D(py::module &m);

PYBIND11_MODULE(pybm4d,m)
{
    bindBM4D(m);
    
    // py::register_exception<AdvancedFiltersException>(m, "AdvancedFiltersException");
}
