#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "parameters.h"

class BM4D_Core;

class BM4D 
{
 public:
  BM4D( bm4d_gpu::Parameters p, 
        const std::vector<unsigned char>& in_noisy_volume, 
        const int& width,
        const int& height, 
        const int& depth);

  inline ~BM4D();

  std::vector<unsigned char> run_first_step();

  private:
    BM4D_Core* core;
};
