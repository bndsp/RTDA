#pragma once
#include <string>
#include "rtda/core/Dataset.hpp"

namespace rtda::io {

    Dataset importCSV(const std::string& path);
}