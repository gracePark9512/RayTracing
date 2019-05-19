/* $Rev: 250 $ */
#include "Cube.h"

#include "utility.h"

Cube::Cube() : Object() {

}

Cube::Cube(const Cube& cube) : Object(cube) {

}

Cube::~Cube() {

}

const Cube& Cube::operator=(const Cube& cube) {
	if (this != &cube) {
		Object::operator=(cube);
	}
	return *this;
}

std::vector<RayIntersection> Cube::intersect(const Ray& ray) const {
    
    std::vector<RayIntersection> result;
    Ray inverseRay = transform.applyInverse(ray);

    //multiple starting point for 6 planes
    double z0 = inverseRay.point(2);
    double dz = inverseRay.direction(2);
    double y0 = inverseRay.point(1);
    double dy = inverseRay.direction(1);
    double x0 = inverseRay.point(0);
    double dx = inverseRay.direction(0);
    
    if((std::abs(dz) < epsilon) || (std::abs(dy) < epsilon) || (std::abs(dx) < epsilon)){
        return result;
    }
    
    double t = (-1-z0)/dz;
    double t1 = (1-z0)/dz;
    double t2 = (-1-y0)/dy;
    double t3 = (1-y0)/dy;
    double t4 = (-1-x0)/dx;
    double t5 = (1-x0)/dx;
    
    RayIntersection hit;
    hit.material = material;
    
    //right plane
    if(t>0){
        hit.point = inverseRay.point + t*inverseRay.direction;

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
    }


    //left plane
    if(t1>0){
        hit.point = inverseRay.point + t1*inverseRay.direction;

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
    }
    
    //top plane
    if(t2>0){
        hit.point = inverseRay.point + t2*inverseRay.direction;

    if (( hit.point(0) < 1 && hit.point(0) > -1) && (hit.point(2)< 1 && hit.point(2) > -1)){

        hit.point = transform.apply(Point(hit.point));

        hit.normal = Normal(0, 1, 0);
        hit.normal = transform.apply(Normal(hit.normal));

        if(hit.normal.dot(ray.direction) > 0){
            hit.normal = -hit.normal;
        }


        hit.distance = (hit.point - ray.point).norm();
        result.push_back(hit);
    }
    }
    
    //bottom plane
    if(t3>0){
        hit.point = inverseRay.point + t3*inverseRay.direction;

    if (( hit.point(0) < 1 && hit.point(0) > -1) && (hit.point(2)< 1 && hit.point(2) > -1)){

        hit.point = transform.apply(Point(hit.point));

        hit.normal = Normal(0, 1, 0);
        hit.normal = transform.apply(Normal(hit.normal));

        if(hit.normal.dot(ray.direction) > 0){
            hit.normal = -hit.normal;
        }


        hit.distance = (hit.point - ray.point).norm();
        result.push_back(hit);
    }
    }
    
    // front plane
    if(t4>0){
        hit.point = inverseRay.point + t4*inverseRay.direction;

    if (( hit.point(1) < 1 && hit.point(1) > -1) && (hit.point(2)< 1 && hit.point(2) > -1)){

        hit.point = transform.apply(Point(hit.point));

        hit.normal = Normal(1, 0, 0);
        hit.normal = transform.apply(Normal(hit.normal));

        if(hit.normal.dot(ray.direction) > 0){
            hit.normal = -hit.normal;
        }

        hit.distance = (hit.point - ray.point).norm();
        result.push_back(hit);
    }
    }

    //back plane
    if(t5>0){
        hit.point = inverseRay.point + t5*inverseRay.direction;
    if (( hit.point(1) < 1 && hit.point(1) > -1) && (hit.point(2)< 1 && hit.point(2) > -1)){


        hit.point = transform.apply(Point(hit.point));

        hit.normal = Normal(1, 0, 0);
        hit.normal = transform.apply(Normal(hit.normal));

        if(hit.normal.dot(ray.direction) > 0){
            hit.normal = -hit.normal;
        }

        hit.distance = (hit.point - ray.point).norm();
        result.push_back(hit);
    }
    }

    return result;
}
