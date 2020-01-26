#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    //TODO; // determine the color
    vec3 color = vec3(0,0,0);
        //TODO; // determine the color
        vec3 shade = (1-reflectivity)*(shader->Shade_Surface(ray, intersection_point, normal,recursion_depth)); //(1-k)*shade_surface
        color = shade;
        Ray ref_ray (intersection_point, (ray.direction - normal * 2 * dot(ray.direction,normal)).normalized());
       if (recursion_depth > 1)
    {
        vec3 r_col = world.Cast_Ray(ref_ray, recursion_depth-1);
        color += reflectivity * r_col; //k*(color )+ (1-k)*shade_surface
    }
    return color;
}
