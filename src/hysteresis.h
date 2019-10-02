#pragma once

template<class T, class U>
class Hysteresis
{
public:
    Hysteresis(const T& current, const U min, const U max)
        : current{current}, min{min}, max{max}
    {}

    operator bool()
    {
        if (current > max)
            state = true;
        if (current < min)
            state = false;
        return state;
    }

    void set_min(U v) {min = v;}
    void set_max(U v) {max = v;}

private:
    const T& current;
    U min;
    U max;
    bool state {false};
};