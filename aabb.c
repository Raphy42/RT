////
//// Created by Raphaël Dantzer on 11/07/16.
////
//
//#include "rt.h"
//#include "aabb.h"
//
//t_aabb      *aabb_construct(t_aabb *aabb, const t_vec3 *a, const t_vec3 *b)
//{
//    vec3_assign(&aabb->min, a);
//    vec3_assign(&aabb->max, b);
//    return (aabb);
//}
//
//static float    vec3_get_from_offset(t_vec3 *v, int offset)
//{
//    if (!offset)
//        return (v->x);
//    else if (offset == 1)
//        return (v->y);
//    else
//        return (v->z);
//}
//
//t_bool          aabb_hit(t_aabb *aabb, t_precision *precision, const t_ray *ray)
//{
//    int         a;
//    float invD, t0, t1, t2;
//
//    a = -1;
//    while (++a < 3)
//    {
//        invD = 1.0f / vec3_get_from_offset(&RAY_DIRECTION(ray), a);
//        t0 = (vec3_get_from_offset(&aabb->min, a) - vec3_get_from_offset(&RAY_ORIGIN(ray), a) * invD);
//        t1 = (vec3_get_from_offset(&aabb->max, a) - vec3_get_from_offset(&RAY_ORIGIN(ray), a) * invD);
//        if (invD < 0.0f)
//        {
//            t2 = t0;
//            t0 = t1;
//            t1 = t2;
//            if (t0 > precision->min)
//                precision->min = t0;
//            if (t1 < precision->max)
//                precision->max = t1;
//            if (precision->max <= precision->min)
//                return (FALSE);
//        }
//    }
//    return (TRUE);
//}