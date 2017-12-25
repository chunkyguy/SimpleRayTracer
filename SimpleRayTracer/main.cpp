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
#include "LambertianMaterial.hpp"
#include "ReflectiveMaterial.hpp"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Space.hpp"
#include "Sphere.hpp"
#include "Utils.hpp"

int main(int argc, const char * argv[]) {
    
    int nx = 200;
    int ny = 100;
    int ns = 100;
    RandomNumGen rand;
    
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;
    
    Camera camera(simd::make_float3(0.0f, 0.0f, 0.0f),
                  simd::make_float3(-2.0f, -1.0f, -1.0f),
                  simd::make_float3(4.0f, 0.0f, 0.0f),
                  simd::make_float3(0.0f, 2.0f, 0.0f));

    std::vector<HitTestable *> spheres;
    
    spheres.push_back(new Sphere(simd::make_float3(0, 0, -1), 0.5,
                                 new LambertianMaterial(simd::make_float3(0.8f, 0.3f, 0.3f))));
    spheres.push_back(new Sphere(simd::make_float3(0, -100.5, -1), 100,
                                 new LambertianMaterial(simd::make_float3(0.8f, 0.8f, 0.0f))));
    spheres.push_back(new Sphere(simd::make_float3(1, 0, -1), 0.5,
                                 new ReflectiveMaterial(simd::make_float3(0.8f, 0.6f, 0.2f), rand.generate(0.3f, 1.0f))));
    spheres.push_back(new Sphere(simd::make_float3(-1, 0, -1), 0.5,
                                 new ReflectiveMaterial(simd::make_float3(0.8f, 0.8f, 0.8f), rand.generate(0.3f, 1.0f))));
    Space space(spheres);
    
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

    for (HitTestable *sphere : spheres) {
        delete sphere;
    }
    
    return 0;
}
