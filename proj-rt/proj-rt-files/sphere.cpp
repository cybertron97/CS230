#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
Hit result {this, 0 , part};
vec3 diff = ray.endpoint - center; //e-c
double a = dot(ray.direction, diff); //d . (e-c)
double b = dot(ray.direction,ray.direction); //d .d =1
double c = dot(diff,diff) - pow(radius,2);
double discr = pow(a,2) - (b * c); //the one inside the square rooot
if(discr == 0) //if the discr is zero , it just checks for the -b/a, which saves us memory
{
   double t = (-1 * a/ b);
   if(t > small_t)
   {
      result.dist = t;
    }
}
else if(discr > 0) //if the discriminant is greater than zero, then it checks the following conditions
{
  double t1 = (-1 * a + sqrt(discr)) / b;
  double t2 = (-1 * a - sqrt(discr)) / b;
  if(t1> small_t && t2 > small_t)
  {
    result.dist = std::min(t1,t2);
  }
}
return result;
}
vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = point - center;
    //TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
