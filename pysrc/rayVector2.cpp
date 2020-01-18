#include "rayVector2.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/operators.h>
#include <pybind11/complex.h>

namespace py = pybind11;

namespace batoid {
    void pyExportRayVector2(py::module& m) {
        auto dvd = py::class_<DualView<double>>(m, "CPPDualViewDouble")
            .def("syncToHost", &DualView<double>::syncToHost)
            .def("syncToDevice", &DualView<double>::syncToDevice);

        auto dvb = py::class_<DualView<bool>>(m, "CPPDualViewBool")
            .def("syncToHost", &DualView<bool>::syncToHost)
            .def("syncToDevice", &DualView<bool>::syncToDevice);

        auto rv4 = py::class_<RayVector2>(m, "CPPRayVector2")
            .def(py::init(
                [](
                    size_t r_ptr,
                    size_t v_ptr,
                    size_t t_ptr,
                    size_t w_ptr,
                    size_t f_ptr,
                    size_t vig_ptr,
                    size_t fail_ptr,
                    size_t size
                ){
                    return new RayVector2(
                        reinterpret_cast<double*>(r_ptr),
                        reinterpret_cast<double*>(v_ptr),
                        reinterpret_cast<double*>(t_ptr),
                        reinterpret_cast<double*>(w_ptr),
                        reinterpret_cast<double*>(f_ptr),
                        reinterpret_cast<bool*>(vig_ptr),
                        reinterpret_cast<bool*>(fail_ptr),
                        size
                    );
                }
            ))
            .def("positionAtTime",
                [](const RayVector2& rv4, double t, size_t out_ptr){
                    rv4.positionAtTime(t, reinterpret_cast<double*>(out_ptr));
                }
            )
            .def("propagateInPlace", &RayVector2::propagateInPlace)
            .def("phase",
                [](const RayVector2& rv4, double x, double y, double z, double t, size_t out_ptr){
                    rv4.phase(x, y, z, t, reinterpret_cast<double*>(out_ptr));
                }
            )
            .def("amplitude",
                [](const RayVector2& rv4, double x, double y, double z, double t, size_t out_ptr){
                    rv4.amplitude(x, y, z, t, reinterpret_cast<std::complex<double>*>(out_ptr));
                }
            )
            .def("sumAmplitude", &RayVector2::sumAmplitude)
            .def(py::self == py::self)
            .def(py::self != py::self)

            // Expose dualviews so can access their syncToHost methods
            .def_readonly("r", &RayVector2::r)
            .def_readonly("v", &RayVector2::v)
            .def_readonly("t", &RayVector2::t)
            .def_readonly("wavelength", &RayVector2::wavelength)
            .def_readonly("flux", &RayVector2::flux)
            .def_readonly("vignetted", &RayVector2::vignetted)
            .def_readonly("failed", &RayVector2::failed);
    }
}
