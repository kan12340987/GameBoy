#include "cpu.h"

using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 576;
cpu::cpu() {
    step = (double) 1000/60;
    // current_time = ;
}
void cpu::read_opcode() {

}
void cpu::tick() {
    // cout << "Write Pixel" << endl;
    std::this_thread::sleep_for(std::chrono::nanoseconds(240));
}


