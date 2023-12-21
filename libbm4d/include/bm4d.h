#pragma once
#include "bm4d_global.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "parameters.h"

class BM4D_Core;

class BM4D_EXPORT BM4D 
{
public:
      BM4D();

      inline ~BM4D();

      std::vector<unsigned char> run(bm4d_gpu::Parameters p,
                                     const std::vector<unsigned char> &in_noisy_volume,
                                     const int &width,
                                     const int &height,
                                     const int &depth);

private:
      BM4D_Core *core;
};
