#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
   // TODO;
   double min_t = std::numeric_limits<double>::max();
   Hit a_hit;
   a_hit.dist = 0;
   for (unsigned int i =0; i<objects.size(); i++)
  {
     Hit p_hit = objects.at(i)->Intersection(ray,objects.at(i)-> number_parts);

   if (p_hit.dist > small_t && min_t > p_hit.dist)
	{
    
    a_hit = p_hit;
	  min_t = p_hit.dist;
  }
 }
   return a_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
   // TODO;
   // set up the initial view ray here
Ray ray;
vec3 direction = (this->camera.World_Position(pixel_index)- camera.position).normalized();
ray.endpoint = camera.position;   //we know that the ray endpoint would be actually the position of the camera
ray.direction = direction;
vec3 color=Cast_Ray(ray,recursion_depth_limit);
camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;

    Hit h =Closest_Intersection(ray);
    if (h.dist >= small_t) {
        color =h.object->material_shader->Shade_Surface(ray, ray.Point(h.dist), h.object->Normal(ray.Point(h.dist), h.part), recursion_depth);
    }

    else
    {
      vec3 dumb; //empty vector TA told to do this
     color = background_shader->Shade_Surface(ray, ray.endpoint, dumb, recursion_depth) ;
        //color = {0,0,0};
    }
// determine the color here
    return color;
}

void Render_World::Initialize_Hierarchy()
{
  //  TODO; // Fill in hierarchy.entries; there should be one entry for
    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
