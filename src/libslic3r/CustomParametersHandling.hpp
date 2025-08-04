#ifndef LIBSLIC3R_CUSTOMPARAMETERSHANDLING_HPP
#define LIBSLIC3R_CUSTOMPARAMETERSHANDLING_HPP

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <variant>

namespace Slic3r {

using CustomParameterType = std::variant<std::monostate, std::string, int, double, bool>;
using CustomParameterValues = std::map<std::string, CustomParameterType>;

std::optional<CustomParameterValues> parse_custom_parameters(const std::string& input);

} // namespace Slic3r

#endif // LIBSLIC3R_CUSTOMPARAMETERSHANDLING_HPP