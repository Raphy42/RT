//
// Created by Raphaël Dantzer on 29/06/16.
//

float       clamp(float x, float min, float max)
{
    if (x < min)
        return (min);
    if (x > max)
        return (max);
    return (x);
}