#pragma once

#include "rtda/core/Observation.hpp"
#include <vector>

namespace rtda::analysis {

    double mean(const std::vector<Observation>& observations);

}