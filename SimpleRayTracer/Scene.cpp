//
//  Scene.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/29/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Scene.hpp"
#include "HitTestable.h"
#include "LambertianMaterial.hpp"
#include "RandomNumGen.hpp"
#include "ReflectiveMaterial.hpp"
#include "RefractiveMaterial.hpp"
#include "Space.hpp"
#include "Sphere.hpp"

Scene::Scene()
{
    RandomNumGen rand;

    // background
    _spheres.push_back(new Sphere(glm::vec3(0, -1000, 0), 1000,
                                 new LambertianMaterial(glm::vec3(0.5f, 0.5f, 0.5f))));
    
    // fill random spheres
    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            glm::vec3 center = glm::vec3(a+0.9f*rand.generate(), 0.2f, b+0.9f*rand.generate());
            float distance = glm::length(center - glm::vec3(4.0f, 0.2f, 0.0f));
            if (distance > 0.9f) {
                float materialType = rand.generate();
                if (materialType < 0.8f) {
                    // diffuse
                    glm::vec3 albedo = glm::vec3(rand.generate() * rand.generate(),
                                                            rand.generate() * rand.generate(),
                                                            rand.generate() * rand.generate());
                    _spheres.push_back(new Sphere(center, 0.2f, new LambertianMaterial(albedo)));
                } else if (materialType < 0.95f) {
                    // metal
                    glm::vec3 albedo = glm::vec3(rand.generate(1.0f, 2.0f),
                                                            rand.generate(1.0f, 2.0f),
                                                            rand.generate(1.0f, 2.0f));
                    float fuzziness = rand.generate(0.0f, 0.5f);
                    _spheres.push_back(new Sphere(center, 0.2f, new ReflectiveMaterial(albedo, fuzziness)));
                } else {
                    //glass
                    _spheres.push_back(new Sphere(center, 0.2f, new RefractiveMaterial(1.5f)));
                }
            }
        }
    }
        
    // fill focus spheres
    _spheres.push_back(new Sphere(glm::vec3(-4, 1, 0), 1.0f,
                                 new LambertianMaterial(glm::vec3(0.4f, 0.2f, 0.1f))));
    _spheres.push_back(new Sphere(glm::vec3(4, 1, 0), 1.0f,
                                 new ReflectiveMaterial(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f)));
    _spheres.push_back(new Sphere(glm::vec3(0, 1, 0), 1.0f,
                                  new RefractiveMaterial(1.5f)));
}

Scene::~Scene()
{
    for (HitTestable *sphere : _spheres) {
        delete sphere;
    }
}

const Space Scene::getSpace() const
{
    return Space(_spheres);
}
