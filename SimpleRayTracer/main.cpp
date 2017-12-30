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
#include "Camera.hpp"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Space.hpp"
#include "Utils.hpp"

int main(int argc, const char * argv[]) {
    
    int nx = 1200;
    int ny = 800;
    int ns = 10;
    RandomNumGen rand;
    
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;
    
    simd::float3 from = simd::make_float3(13.0f, 2.0f, 3.0f);
    simd::float3 target = simd::make_float3(0.0f, 0.0f, 0.0f);
    simd::float3 up = simd::make_float3(0.0f, 1.0f, 0.0f);
    float fov = 20.0f;
    float aspectRatio = float(nx)/float(ny);
    float aperture = 0.1f;
    float focalDistance = 10.0f;
    Camera camera(from, target, up, fov, aspectRatio, aperture, focalDistance);
    
    Scene scene;
    const Space space = scene.getSpace();
    
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            simd::float3 color = simd::make_float3(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < ns; ++s) {
                simd::float2 uv = simd::make_float2(float(i + rand.generate())/float(nx), float(j + rand.generate())/float(ny));
                Ray ray = camera.getRay(uv);
                color += Utils::trace(ray, space, 0);
            }
            simd::float3 aggregateColor = color/float(ns);
            simd::float3 gammaCorrectedColor = simd::make_float3(simd::sqrt(aggregateColor.x),
                                                                 simd::sqrt(aggregateColor.y),
                                                                 simd::sqrt(aggregateColor.z));
            simd::float3 colorRGB = gammaCorrectedColor * 255.0f;
            int rr = int(ceil(colorRGB.r));
            int gg = int(ceil(colorRGB.g));
            int bb = int(ceil(colorRGB.b));
            std::cout << rr << " " << gg << " " << bb << std::endl;
        }
    }

    
    return 0;
}
