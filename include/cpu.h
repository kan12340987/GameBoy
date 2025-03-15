#include "MMU.h"
#include "opcode.h"
#include<chrono>
#include <thread>
#include<SDL2/SDL.h>
// #include<time.h>
// #include <vector>
// #define freq INT 4000000;
class cpu
{
private:
    MMU mmu;
    opcode op_instance;
public:

    SDL_Event e;
    bool quit = false; 
    cpu(MMU,opcode);
    double step;
    std::chrono::steady_clock::time_point startFrame;
    std::chrono::steady_clock::time_point finishFrame;
    void read_opcode();
    void decodeOpcode(__uint8_t);
    void tick();
    void waitcycle(int);
    time_t current_time;
    __uint16_t combined_reg(__uint8_t, __uint8_t);

    void execute_ld_r_n(__uint8_t &reg);
    void execute_jr_cc_e(bool);
    void load_rr_nn(int opcode,__uint8_t &lsb, __uint8_t &msb);
    void indirect_hl_decrement();
    void xor_r(__uint8_t &);
    void execute_CB();
    bool execute_CB_bit(int,__uint8_t);
};
