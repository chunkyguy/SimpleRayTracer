//
//  main.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/6/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include <cmath>
#include <iostream>
#include <simd/simd.h>

int main(int argc, const char * argv[]) {
    
    int nx = 200;
    int ny = 100;
    
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;
    
    for (int j = 0; j < ny; ++j) {
        for (int i = 0; i < nx; ++i) {
            float r = float(i)/float(nx);
            float g = float(j)/float(ny);
            float b = 0.2f;
            simd::float3 color = simd::make_float3(r, g, b);
            simd::float3 colorScaled = color * 255.0f;
            
            int rr = int(ceil(colorScaled.r));
            int gg = int(ceil(colorScaled.g));
            int bb = int(ceil(colorScaled.b));
            std::cout << rr << " " << gg << " " << bb << std::endl;
        }
    }
    
    return 0;
}
