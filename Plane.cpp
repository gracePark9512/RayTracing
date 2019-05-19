#include "Plane.h"

#include "utility.h"

Plane::Plane() : Object() {

}

Plane::Plane(const Plane& plane) : Object(plane) {

}

Plane::~Plane() {

}

const Plane& Plane::operator=(const Plane& plane) {
	if (this != &plane) {
		Object::operator=(plane);
	}
	return *this;
}

std::vector<RayIntersection> Plane::intersect(const Ray& ray) const {

    std::vector<RayIntersection> result;
    Ray inverseRay = transform.applyInverse(ray);
    
    //compute the intersection
    double z0 = inverseRay.point(2);
    double dz = inverseRay.direction(2);
    
    // make sure that point is not devided by 0
    if(std::abs(dz) < epsilon){
        return result;
    }
    
    double t = -z0/dz;
    
    // calculate intersection
    RayIntersection hit;
    hit.point = inverseRay.point + t*inverseRay.direction;
    hit.material = material;
    
    // if t is too small == unstable
    if(t<0){
        return result;
    }
    
    // x and y values lie in the range [-1,1]
    if (( hit.point(0) < 1 && hit.point(0) > -1) && (hit.point(1)< 1 && hit.point(1) > -1)){
        
        hit.point = transform.apply(Point(hit.point));
        
        hit.normal = Normal(0, 0, 1);
        hit.normal = transform.apply(Normal(hit.normal));
        
        if(hit.normal.dot(ray.direction) > 0){
            hit.normal = -hit.normal;
        }
        
        hit.distance = (hit.point - ray.point).norm();
        result.push_back(hit);
    }
	return result;
}
