#include "CustomParametersHandling.hpp"

#include "nlohmann/json.hpp"

namespace Slic3r {

std::optional<CustomParameterValues> parse_custom_parameters(const std::string& input)
{
    if (input.empty())
        return CustomParameterValues();

    using json = nlohmann::json;

    try {
        json j = json::parse(input);

        if (!j.is_object()) {
            return std::nullopt;
        }

        CustomParameterValues values;

        for (auto& [key, val] : j.items()) {
            if (val.is_null()) {
                values[key] = std::monostate{};
            } else if (val.is_string()) {
                values[key] = val.get<std::string>();
            } else if (val.is_number_integer()) {
                values[key] = val.get<int>();
            } else if (val.is_number_float()) {
                values[key] = val.get<double>();
            } else if (val.is_boolean()) {
                values[key] = val.get<bool>();
            } else if (val.is_array()) {
                    return std::nullopt;
            } else {
                // Unsupported type
                return std::nullopt;
            }
        }
        return values;
    } catch (const json::parse_error&) {
        return std::nullopt;
    }

    return std::nullopt;
}

} // namespace Slic3r
