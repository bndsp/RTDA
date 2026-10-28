#include "rtda/analysis/Statistics.hpp"
#include <stdexcept>
#include <variant>
#include <cstdint>

namespace rtda::analysis {

    double mean(const std::vector<Observation>& observations) {

        double total = 0.0;
        std::size_t count = 0;

        for (const Observation& observation : observations) {

            if (const auto* value = std::get_if<double>(&observation.value)) {
                total += *value;
                ++count;
            }
            else if (const auto* value = std::get_if<std::int64_t>(&observation.value)) {
                total += static_cast<double>(*value);
                ++count;
            }
        }

        if (count == 0) {
            throw std::invalid_argument("No numeric observations available.");
        }

        return total / count;
    }

}