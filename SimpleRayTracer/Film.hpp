//
//  Film.hpp
//  SimpleRayTracer
//
//  Created by Sidharth on 12/31/17.
//  Copyright © 2017 whackylabs. All rights reserved.
//

#ifndef Film_hpp
#define Film_hpp
#include <map>
#include <simd/simd.h>

// Store all color information. Not threadsafe
class Film {
public:
    Film(const int x, const int y);
    void updateColor(const simd::float3 &color, const int i, const int j);
    void process() const;
    
private:
    
    int getPosition(const int i, const int j) const;
    
    int _x;
    int _y;
    std::map<int, simd::float3> _pixelData;
};

#endif /* Film_hpp */
