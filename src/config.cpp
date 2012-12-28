
#include "condor_common.h"
#include "condor_config.h"

#include <boost/python.hpp>

using namespace boost::python;

struct Param
{
    std::string getitem(const std::string &attr)
    {
        std::string result;
        if (!param(result, attr.c_str()))
        {
            PyErr_SetString(PyExc_KeyError, attr.c_str());
            throw_error_already_set();
        }
        return result;
    }

    void setitem(const std::string &attr, const std::string &val)
    {
        param_insert(attr.c_str(), val.c_str());
    }

    std::string setdefault(const std::string &attr, const std::string &def)
    {
        std::string result;
        if (!param(result, attr.c_str()))
        {
           param_insert(attr.c_str(), def.c_str());
           return def;
        }
        return result;
    }
};

void export_config()
{
    config();
    def("reload_config", config, "Reload the HTCondor configuration from disk.");
    class_<Param>("_Param")
        .def("__getitem__", &Param::getitem)
        .def("__setitem__", &Param::setitem)
        .def("setdefault", &Param::setdefault)
        ;
    object param = object(Param());
    param.attr("__doc__") = "A dictionary-like object containing the HTCondor configuration.";
    scope().attr("param") = param;
}