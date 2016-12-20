#include <boost/python.hpp>
#include <boost/any.hpp>
#include <stdlib.h>
#include <iostream>
#include <frameobject.h>

using namespace boost::python;

struct LoadCommand {
   public:
      LoadCommand(){}

      void processAny(boost::any const& a)
      {
         std::cout << "processing any : " << boost::any_cast<std::string>(a) << std::endl;
      }

      void loadModel(std::string const & modelFilename)
      {
         std::cout << "loadModel : " << modelFilename << std::endl;
      }
};

BOOST_PYTHON_MODULE(Test)
{
   class_<LoadCommand>("LoadCommand")
       .def("loadModel", &LoadCommand::loadModel)
       .def("processAny", &LoadCommand::processAny)
   ;
}

#if PY_MAJOR_VERSION >= 3
#   define INIT_MODULE PyInit_Test
    extern "C" PyObject* INIT_MODULE();
#else
#   define INIT_MODULE initTest
    extern "C" void INIT_MODULE();
#endif


int main(int argc, char** argv)
{
    try {
        PyImport_AppendInittab((char*)"Test", INIT_MODULE);
        Py_Initialize();
        object main_module = import("__main__");
        dict main_namespace = extract<dict>(main_module.attr("__dict__"));
        object mymodule = import("Test");

        main_namespace["precreated_object"] = LoadCommand();
        exec_file("Test.py", main_namespace, main_namespace);
    } catch (error_already_set& e) {
        PyErr_PrintEx(0);
        return 1;
    }
    return 0;
}
