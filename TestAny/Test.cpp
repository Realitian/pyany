#include <boost/python.hpp>
#include <boost/any.hpp>
#include <stdlib.h>

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
