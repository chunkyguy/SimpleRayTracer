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

#include "Ray.hpp"
#include "Sphere.hpp"
#include "Space.hpp"
#include "Utils.hpp"

int main(int argc, const char * argv[]) {
    
    int nx = 200;
    int ny = 100;
    
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;
    
    simd::float3 bottomLeft = simd::make_float3(-2.0f, -1.0f, -1.0f);
    simd::float3 horizontal = simd::make_float3(4.0f, 0.0f, 0.0f);
    simd::float3 vertical = simd::make_float3(0.0f, 2.0f, 0.0f);
    simd::float3 origin = simd::make_float3(0.0f, 0.0f, 0.0f);
    
    Sphere *sphere0 = new Sphere(simd::make_float3(0, 0, -1), 0.5);
    Sphere *sphere1 = new Sphere(simd::make_float3(0, -100.5, -1), 100);
    std::vector<HitTestable *> spheres = {sphere0, sphere1};
    Space space(spheres);
    
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            
            Ray ray(origin, bottomLeft + (horizontal * u) + (vertical * v));
            simd::float3 color = Utils::trace(ray, space);
            
            simd::float3 colorScaled = color * 255.0f;
            
            int rr = int(ceil(colorScaled.r));
            int gg = int(ceil(colorScaled.g));
            int bb = int(ceil(colorScaled.b));
            std::cout << rr << " " << gg << " " << bb << std::endl;
        }
    }    
    return 0;
}
