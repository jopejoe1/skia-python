#include <pybind11/pybind11.h>
#include <skia.h>

namespace py = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, sk_sp<T>);

void initSurface(py::module &m) {
py::class_<SkSurfaceProps>(m, "SurfaceProps")
    ;
py::class_<SkSurface, sk_sp<SkSurface>>(m, "Surface")
    .def(py::init([](int width, int height) -> sk_sp<SkSurface> {
        auto surface = SkSurface::MakeRasterN32Premul(width, height);
        if (surface.get() == nullptr)
            throw std::runtime_error("Failed to allocate surface.");
        return surface;
    }))
    .def("getCanvas", [](sk_sp<SkSurface>& surface) {
        if (surface.get() == nullptr)
            throw std::runtime_error("Null pointer exception.");
        auto canvas = surface->getCanvas();
        if (canvas == nullptr)
            throw std::runtime_error("Failed to get canvas.");
        return canvas;
    },
        py::return_value_policy::reference)
    .def("makeImageSnapshot",
        py::overload_cast<>(&SkSurface::makeImageSnapshot),
        "Returns SkImage capturing SkSurface contents.")
    ;
}
