//
//  Scene.cpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/29/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#include "Scene.hpp"

#include "Camera.hpp"
#include "HitTestable.h"
#include "LambertianMaterial.hpp"
#include "RandomNumGen.hpp"
#include "ReflectiveMaterial.hpp"
#include "RefractiveMaterial.hpp"
#include "Space.hpp"
#include "Sphere.hpp"
#include "MovingSphere.h"

Scene::Scene()
{
    Material *material;

    // film size
    filmSize_ = glm::uvec2(
        200.0f, // width
        100.0f // height
    );
    filmResolution_ = 100.0f;

	// camera
    camera_ = new Camera(
		glm::vec3(13.0f, 2.0f, 3.0f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // target
		glm::vec3(0.0f, 1.0f, 0.0f), // up 
		20.0f, // fov
		float(filmSize_.x) / float(filmSize_.y), // aspect ratio
		0.1f, // aperture
		10.0f, // focal distance
        glm::vec2(0.0f, 1.0f)
	);

    // background
    material = new LambertianMaterial(glm::vec3(0.5f, 0.5f, 0.5f));
    materials_.push_back(material);
    spheres_.push_back(new Sphere(glm::vec3(0, -1000, 0), 1000, material));
    
    ///* fill random spheres */
    // RandomNumGen rand;
    //int fillRange = 3;
    //for (int a = -fillRange; a < fillRange; ++a) {
    //    for (int b = -fillRange; b < fillRange; ++b) {
    //        glm::vec3 center = glm::vec3(a+0.9f*rand.generate(), 0.2f, b+0.9f*rand.generate());
    //        float distance = glm::length(center - glm::vec3(4.0f, 0.2f, 0.0f));
    //        if (distance > 0.9f) {
    //            float materialType = rand.generate();
    //            if (materialType < 0.8f) {
    //                // diffuse
    //                glm::vec3 albedo = glm::vec3(rand.generate() * rand.generate(),
    //                                                        rand.generate() * rand.generate(),
    //                                                        rand.generate() * rand.generate());
    //                spheres_.push_back(new Sphere(center, 0.2f, new LambertianMaterial(albedo)));
    //            } else if (materialType < 0.95f) {
    //                // metal
    //                glm::vec3 albedo = glm::vec3(rand.generate(1.0f, 2.0f),
    //                                                        rand.generate(1.0f, 2.0f),
    //                                                        rand.generate(1.0f, 2.0f));
    //                float fuzziness = rand.generate(0.0f, 0.5f);
    //                spheres_.push_back(new Sphere(center, 0.2f, new ReflectiveMaterial(albedo, fuzziness)));
    //            } else {
    //                //glass
    //                spheres_.push_back(new Sphere(center, 0.2f, new RefractiveMaterial(1.5f)));
    //            }
    //        }
    //    }
    //}
        
    // fill focus spheres

    material = new LambertianMaterial(glm::vec3(0.4f, 0.2f, 0.1f));
    materials_.push_back(material);
    spheres_.push_back(new MovingSphere(
        glm::vec3(-4, 1, 0), 
        glm::vec3(-4, 1.3f, 0),
        glm::vec2(0.0f, 1.0f),
        1.0f,
        material
    ));

    material = new ReflectiveMaterial(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);
    materials_.push_back(material);
    spheres_.push_back(new MovingSphere(
        glm::vec3(4, 1, 0),
        glm::vec3(4, 1.5f, 0),
        glm::vec2(0.0f, 1.0f),
        1.0f, material
    ));

    material = new RefractiveMaterial(1.5f);
    materials_.push_back(material);
    spheres_.push_back(new MovingSphere(
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1.2f, 0),
        glm::vec2(0.0f, 1.0f),
        1.0f, material
    ));

    space_ = new Space(spheres_);
}

Scene::~Scene()
{
    delete camera_;
    delete space_;
    for (HitTestable *sphere : spheres_) {
        delete sphere;
    }
    for (Material *material : materials_) {
        delete material;
    }
}

const Space *Scene::getSpace() const
{
    return space_;
}

const Camera *Scene::getCamera() const 
{
    return camera_;
}

const glm::uvec2 Scene::getFilmSize() const
{
    return filmSize_;
}

const float Scene::getFilmResolution() const
{
    return filmResolution_;
}