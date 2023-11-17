#include "../include/bm4d.h"
#include "../include/bm4d_core.h"
#include "../include/parameters.h"

BM4D::BM4D( bm4d_gpu::Parameters p, 
            const std::vector<unsigned char>& in_noisy_volume, 
            const int& width,
            const int& height, 
            const int& depth) : core(nullptr) 
            {
                core = new BM4D_Core(p, in_noisy_volume, width, height, depth) ;
            }

BM4D::~BM4D() { delete core;}    

std::vector<unsigned char> BM4D::run_first_step() 
{
    return core->run_first_step();
}

