#include "string_utils.hpp"

#include <regex>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>

namespace opossum {

std::vector<std::string> trim_and_split(const std::string& input) {
  auto converted = input;

  boost::algorithm::trim_all<std::string>(converted);
  auto arguments = std::vector<std::string>{};
  boost::algorithm::split(arguments, converted, boost::is_space());

  return arguments;
}

std::vector<std::string> split_string_by_delimiter(const std::string& str, char delimiter) {
  auto result = std::vector<std::string>{};
  auto stream = std::stringstream{str};
  auto tok = std::string{};

  while (std::getline(stream, tok, delimiter)) {
    result.push_back(tok);
  }

  return result;
}

std::string trim_source_file_path(const std::string& path) {
  const auto src_pos = path.find("/src/");
  if (src_pos == std::string::npos) {
    return path;
  }

  // "+ 1", since we want "src/lib/file.cpp" and not "/src/lib/file.cpp"
  return path.substr(src_pos + 1);
}

}  // namespace opossum
