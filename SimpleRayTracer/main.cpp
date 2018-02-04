//
//  main.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/6/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include <cmath>
#include <iostream>

#include <dispatch/dispatch.h>
#include <simd/simd.h>

#include "Camera.hpp"
#include "Film.hpp"
#include "RandomNumGen.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Space.hpp"
#include "Utils.hpp"

simd::float3 getColor(const int nx, const int ny, const int ns,
               const int i, const int j,
               const Camera &camera, const Space &space)
{
    RandomNumGen rand;
    simd::float3 color = simd::make_float3(0.0f, 0.0f, 0.0f);
    for (int s = 0; s < ns; ++s) {
        simd::float2 uv = simd::make_float2(float(i + rand.generate())/float(nx),
                                            float(j + rand.generate())/float(ny));
        Ray ray = camera.getRay(uv);
        color += Utils::trace(ray, space, 0);
    }
    simd::float3 aggregateColor = color/float(ns);
    return simd::make_float3(simd::sqrt(aggregateColor.x),
                             simd::sqrt(aggregateColor.y),
                             simd::sqrt(aggregateColor.z));
}

int main(int argc, const char * argv[]) {
    
    int nx = 1200;
    int ny = 800;
    int ns = 10;
    
    simd::float3 from = simd::make_float3(13.0f, 2.0f, 3.0f);
    simd::float3 target = simd::make_float3(0.0f, 0.0f, 0.0f);
    simd::float3 up = simd::make_float3(0.0f, 1.0f, 0.0f);
    float fov = 20.0f;
    float aspectRatio = float(nx)/float(ny);
    float aperture = 0.1f;
    float focalDistance = 10.0f;
    Camera camera(from, target, up, fov, aspectRatio, aperture, focalDistance);
    
    __block Film film(nx, ny);
    
    Scene scene;
    const Space space = scene.getSpace();
    
    dispatch_queue_t mainQueue = dispatch_get_main_queue();
    dispatch_queue_t rayQueue = dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0);
    dispatch_queue_t filmQueue = dispatch_queue_create("com.whackylabs.srt", DISPATCH_QUEUE_SERIAL);
    dispatch_group_t rayTask = dispatch_group_create();

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            dispatch_group_enter(rayTask);
            dispatch_async(rayQueue, ^{
                simd::float3 color = getColor(nx, ny, ns, i, j, camera, space);
                dispatch_async(filmQueue, ^{
                    film.updateColor(color, i, j);
                    dispatch_group_leave(rayTask);
                });
            });
        }
    }
    
    dispatch_group_notify(rayTask, filmQueue, ^{
        film.process();
        dispatch_async(mainQueue, ^{
            exit(0);
        });
    });
    
    dispatch_main();
    
    return 0;
}
