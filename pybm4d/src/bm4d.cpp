#include <bm4d.h>

#include <string>
#include <map>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <parameters.h>

namespace py = pybind11;

void bindBM4D(py::module &m)
{
    py::class_<BM4D> bm4dClass(m, "BM4D");

    bm4dClass.def(py::init());

    bm4dClass.def("run",
                [](BM4D &bm4d,
                py::array_t<unsigned char> &x,
                const py::dict &args)
                {
                    bm4d_gpu::Parameters p;
                    std::map<std::string, int> parMap = {{"sim_th", 0},
                                                         {"hard_th", 1},
                                                         {"window_size", 2},
                                                         {"step_size", 3},
                                                        //  {"patch_size", 4},
                                                        //  {"maxN", 5}
                                                         };

                    for (const auto & item : args)
                    {
                        auto key = py::cast<std::string>(item.first);
                        if (parMap.find(key) != parMap.end())
                        {
                            switch (parMap[key])
                            {

                                //{"sim_th",      0},        // Similarity threshold for the first step
                                case 0:
                                    p.sim_th = py::cast<float>(item.second);
                                    break;
                                // {"hard_th",     1},       // Hard shrinkage threshold
                                case 1:
                                    p.hard_th = py::cast<float>(item.second);
                                    break;  
                                // {"window_size", 2},   // Search window, barely affects the results [Lebrun M., 2013]
                                case 2:
                                    p.window_size = py::cast<int>(item.second);
                                    break;  
                                // {"step_size",   3},     // Reasonable values {1,2,3,4}
                                                    // Significantly (exponentially) affects speed,
                                                    // slightly affect results
                                case 3: 
                                    p.step_size = py::cast<int>(item.second);
                                    break;

                                // // Fixed in current implementation
                                // // TODO: check what's up here
                                // // {"patch_size",  4},  // Patch size
                                // case 4:
                                //     p.patch_size = py::cast<int>(item.second);
                                //     break;
                                // // {"maxN"      ,  5}};
                                // case 5:
                                //     p.maxN = py::cast<int>(item.second);
                                //     break;
                            }
                        }
                    }

                    py::buffer_info buf1 = x.request();

                    if (buf1.format!=py::format_descriptor<unsigned char>::format())
                        throw std::runtime_error("Incompatible format: expected an unsigned char array!");

                    if (buf1.shape.size() != 3UL)
                        throw std::runtime_error("Incompatible format: expected a 3D array!");

                    std::vector<size_t> dims={  static_cast<size_t>(buf1.shape[2]),
                                                static_cast<size_t>(buf1.shape[1]),
                                                static_cast<size_t>(buf1.shape[0])
                                             };

                    py::print(dims[0],dims[1],dims[2]);

                    std::vector<unsigned char> vec;
                    std::copy_n(static_cast<unsigned char*>(buf1.ptr),dims[0]*dims[1]*dims[2],vec.begin()); // data
                    auto res = bm4d.run(p, vec,dims[0],dims[1],dims[2] );  

                    return res;
                });


}
