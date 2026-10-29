#include "rtda/core/Dataset.hpp"

namespace rtda{

    Dataset::Dataset(std::string name)
        : name_(name) {
        }
    
    void Dataset::addSignal(Signal signal) {
        signals_.push_back(signal);
    }

    const std::vector<Signal>& Dataset::getSignals() const {
        return signals_;
    }

    const std::string& Dataset::getName() const {
        return name_;
    }

    Signal& Dataset::getSignal(std::size_t index) {
        return signals_.at(index);
    }
}