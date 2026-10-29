#pragma once
#include "rtda/core/Signal.hpp"
#include <string>
#include <vector>

namespace rtda {

    class Dataset { 
    public:
        Dataset(std::string name);

        void addSignal(Signal signal);

        const std::vector<Signal>& getSignals() const;

        const std::string& getName() const;

        Signal& getSignal(std::size_t index);
    
    private:
        std::string name_;
        std::vector<Signal> signals_;
    };

}