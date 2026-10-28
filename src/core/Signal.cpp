#include "rtda/core/Signal.hpp"

namespace rtda {

    Signal::Signal(std::string name, std::string unit, std::vector<Observation> observations)
        : name_(name), unit_(unit), observations_(observations) {
    }

    Signal::Signal(std::string name, std::string unit)
        : name_(name), unit_(unit) {
    }

    void Signal::addObs(Observation observation) {
        observations_.push_back(observation);
    }

    const std::vector<Observation>& Signal::getObs() const {
        return observations_;
    }

}