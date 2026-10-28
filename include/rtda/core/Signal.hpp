#pragma once

#include "rtda/core/Observation.hpp"
#include <string>
#include <vector>

namespace rtda {

    class Signal {
    public:
        Signal(std::string name, std::string unit, std::vector<Observation> observations);
        Signal(std::string name, std::string unit);

        const std::vector<Observation>& getObs() const;

        void addObs(Observation observation);

    private:
        std::string name_;
        std::string unit_;
        std::vector<Observation> observations_;
    };

}