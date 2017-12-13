//
//  main.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/6/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include <cmath>
#include <iostream>
#include <random>
#include <simd/simd.h>
#include "Camera.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Space.hpp"
#include "Utils.hpp"

int main(int argc, const char * argv[]) {
    
    int nx = 200;
    int ny = 100;
    int ns = 100;
    
    std::default_random_engine randGen;
    std::uniform_real_distribution<float> rand(0.0f, 1.0f);
    
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;
    
    Camera camera(simd::make_float3(0.0f, 0.0f, 0.0f),
                  simd::make_float3(-2.0f, -1.0f, -1.0f),
                  simd::make_float3(4.0f, 0.0f, 0.0f),
                  simd::make_float3(0.0f, 2.0f, 0.0f));

    Sphere *sphere0 = new Sphere(simd::make_float3(0, 0, -1), 0.5);
    Sphere *sphere1 = new Sphere(simd::make_float3(0, -100.5, -1), 100);
    std::vector<HitTestable *> spheres = {sphere0, sphere1};
    Space space(spheres);
    
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            simd::float3 color = {0};
            for (int s = 0; s < ns; ++s) {
                Ray ray = camera.getRay(simd::make_float2(float(i + rand(randGen))/float(nx),
                                                          float(j + rand(randGen))/float(ny)));
                color += Utils::trace(ray, space);
            }
            simd::float3 colorScaled = (color/float(ns)) * 255.0f;
            int rr = int(ceil(colorScaled.r));
            int gg = int(ceil(colorScaled.g));
            int bb = int(ceil(colorScaled.b));
            std::cout << rr << " " << gg << " " << bb << std::endl;
        }
    }
    
    delete sphere0;
    delete sphere1;
    
    return 0;
}
