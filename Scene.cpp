#include "Scene.h"

#include "Colour.h"
#include "ImageDisplay.h"
#include "utility.h"

Scene::Scene() : backgroundColour(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	ImageDisplay display("Render", renderWidth, renderHeight);
	
	std::cout << "Rendering a scene with " << objects_.size() << " objects" << std::endl;
	
	const double w = double(renderWidth);
	const double h = double(renderHeight);

	for (unsigned int v = 0; v < renderHeight; ++v) {
		for (unsigned int u = 0; u < renderWidth; ++u) {
			double cu = -1 + (u + 0.5)*(2.0 / w);
			double cv = -h/w + (v + 0.5)*(2.0 / w);
			Ray ray = camera_->castRay(cu, cv);
			display.set(u, v, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}

	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
	RayIntersection firstHit;
	firstHit.distance = infinity;
	for (auto& obj : objects_) {
		for (auto& hit : obj->intersect(ray)) {
			if (hit.distance > epsilon && hit.distance < firstHit.distance) {
				firstHit = hit;
			}
		}
	}	return firstHit;
}

Colour Scene::computeColour(const Ray& ray, unsigned int rayDepth) const {
	RayIntersection hitPoint = intersect(ray);
	if (hitPoint.distance == infinity) {
		return backgroundColour;
	}
	Colour hitColour(0, 0, 0);
	// Code to do better lighting, shadows, and reflections goes here.
    for (auto light: lights_) {
        // Compute the influence of this light on the appearance of the hit object.
		if (light->getDistanceToLight(hitPoint.point) < 0) {
			// An ambient light, ignore shadows and add appropriate colour
			hitColour += light->getIlluminationAt(hitPoint.point) * hitPoint.material.ambientColour;
		} else {
            // vector from the hit point back along the view ray
            Vector l = -light -> getLightDirection(hitPoint.point);
            //normal vector from the hit point towards the ith light source
            Vector n = hitPoint.normal;
            //colour of the light at hitpoint
            Colour id = light -> getIlluminationAt(hitPoint.point);
            // diffuse colour of the material at the hitpoint
            Colour kd = hitPoint.material.diffuseColour;
            
            //specular lelment of the ith light
            Colour is = light -> getIlluminationAt(hitPoint.point);
            //reflection of l about n
            Vector r = 2*(n.dot(l)) * (n-l);
            //vector from the hit point back along the view ray
            Vector v = -ray.direction;
            Colour ks = hitPoint.material.specularColour;
            
            //normalise vectors
            r = r/r.norm();
            v = v/v.norm();
            
            l = l/l.norm();
            n = n/n.norm();
            
            double diffusion = std::max<double>(0, n.dot(l));

            //shadow ray generated
            Ray shadowRay;
            shadowRay.direction = l;
            shadowRay.point = hitPoint.point;
            double spec = std::max<double>(0, r.dot(v));

            RayIntersection shadow = intersect(shadowRay);

            if(shadow.distance > light -> getDistanceToLight(hitPoint.point)){
                hitColour += id*(kd*diffusion + ks*pow(spec, hitPoint.material.specularExponent));

            }
        }
	/**********************************
   	 * TODO - ADD MIRROR EFFECTS HERE *
	 **********************************/
    if(rayDepth >0){
        Vector n = hitPoint.normal;

        Vector v = -ray.direction;
        
        v = v/v.norm();
        
        n = n/n.norm();
        
        Ray mirrorRay;
        
        mirrorRay.direction = 2 * n.dot(v) * n - v;

        mirrorRay.point = hitPoint.point;
        hitColour += hitPoint.material.mirrorColour * computeColour(mirrorRay, rayDepth-1);
        }
    }
	hitColour.clip();
	return hitColour;
}

bool Scene::hasCamera() const {
	return bool(camera_);
}
