#pragma once

#include <chrono>
#include <vector>

namespace nstl {

class timer {
public:
    typedef double   timer_id;
private:
    inline static timer_id get_current_time() {
        using std::chrono::duration_cast;
        using std::chrono::microseconds;
        using std::chrono::system_clock;
        auto micros_since_epoch = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        return static_cast<timer_id>(micros_since_epoch) / 1000;
    }
public:
    static timer_id start() {
        return get_current_time();
    }

    static double end(timer_id id) {
        return get_current_time() - id;
    }
};

}  // nstl