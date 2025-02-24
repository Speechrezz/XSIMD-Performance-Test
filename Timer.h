//
//  Timer.hpp
//
//  Created by rick gessner on 5/25/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#pragma once

#include <chrono>

class Timer {
public:
    Timer() {
        stopped=started=std::chrono::high_resolution_clock::now();
    };

    Timer& start() {
        started=std::chrono::high_resolution_clock::now();
        return *this;
    }

    Timer& stop() {
        stopped=std::chrono::high_resolution_clock::now();
        return *this;
    }

    double elapsed() {
        if(started!=stopped) {
            std::chrono::duration<double> elapsed = stopped - started;
            return elapsed.count();
        }
        return 0.0;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> started;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopped;
};
