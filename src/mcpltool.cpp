#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include "mcpl.h"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(_mcpltool_impl, m) {
  m.def("mcpl_tool", [](std::vector<std::string> options){
    char** args = new char*[options.size()];
    int i = 0;
    for (; i < options.size(); ++i) {
      args[i] = new char[options[i].size() + 1];
      strcpy(args[i], options[i].c_str());
    }
    auto result = mcpl_tool(i, args);
    for (i = 0; i < options.size(); ++i) {
      delete[] args[i];
    }
    delete[] args;
    return result;
  }, "args"_a);

  m.def("particle_count", [](const std::string & filename){
    auto f = mcpl_open_file(filename.c_str());
    auto count = mcpl_hdr_nparticles(f);
    mcpl_close_file(f);
    return count;
  }, "filename"_a);

  m.def("merge", [](const std::string & filename, const std::vector<std::string> & filenames){
    if (filenames.empty()) {
      return;
    }
    const auto & first_file = filenames.front();
    for (const auto & fn : filenames) {
      if (fn != first_file && !mcpl_can_merge(first_file.c_str(), fn.c_str())) {
        throw std::runtime_error("Files cannot be merged due to differing header information.");
      }
    }
    char ** files = new char*[filenames.size()];
    for (size_t i = 0; i < filenames.size(); ++i) {
      files[i] = new char[filenames[i].size() + 1];
      strcpy(files[i], filenames[i].c_str());
    }
    mcpl_merge_files(filename.c_str(), static_cast<int>(filenames.size()), (const char **)files);
  }, "filename"_a, "filenames"_a);
}
