#ifndef projectile_h
#define projectile_h
#include <iostream> 
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
namespace projectile_NS{
    class basicProjectile{
        public:
        float speedX;
        float speedY;
        Vector2 pos;
        Rectangle frameRec = {0.0f, 0.0f, 24, 24};
        Rectangle destRec = {pos.x, pos.y, 24, 24};
        basicProjectile(Vector2 aPos, float IspeedX, float IspeedY){
            pos = aPos;
            speedX = IspeedX;
            speedY = IspeedY;
        }
        
        
    };
};

#endif