#include <iostream>
#include<chrono>
#include <thread>
// #include<time.h>
// #include <vector>
// #define freq INT 4000000;
class cpu
{
private:

public:
    cpu();
    double step;
    std::chrono::steady_clock::time_point startFrame;
    std::chrono::steady_clock::time_point finishFrame;
    void read_opcode();
    void tick();
    time_t current_time;
};
