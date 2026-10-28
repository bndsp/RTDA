#pragma once

#include <cstdint>
#include <cstddef>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace rtda {

    struct Observation {
        std::optional<double> timestamp;

        std::variant<
            std::int64_t,
            double,
            std::string,
            bool,
            std::vector<std::byte>
        > value;
    };

}