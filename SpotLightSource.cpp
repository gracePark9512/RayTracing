#include "SpotLightSource.h"

#include "utility.h"

SpotLightSource::SpotLightSource(const Colour& colour, const Point& location, const Direction& direction, double angle) :
	LightSource(colour), location_(location), direction_(direction), angle_(angle) {

}




SpotLightSource::SpotLightSource(const SpotLightSource& lightSource) :
LightSource(lightSource),  location_(lightSource.location_), direction_(lightSource.direction_), angle_(lightSource.angle_) {

}


SpotLightSource::~SpotLightSource() {

}

const SpotLightSource& SpotLightSource::operator=(const SpotLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
		location_ = lightSource.location_;
		direction_ = lightSource.direction_;
		angle_ = lightSource.angle_;
	}
	return *this;
}

Colour SpotLightSource::getIlluminationAt(const Point& point) const {
  
	Colour colour;

	/****************************************************************
 	 * Code to compute directional illumination at point goes here. *
	 ****************************************************************/

  return colour_;
}

double SpotLightSource::getDistanceToLight(const Point& point) const {

	/*******************************************************************
	* Code to compute distance to directional light source goes here. *
	*******************************************************************/

	return (location_ - point).norm();
}

Direction SpotLightSource::getLightDirection(const Point& point) const {
	Direction direction(0, 0, 0);

	/**************************************************************
	* Code to compute direction of light at the point goes here. *
	**************************************************************/

    return point - location_; //direction of hit point to light source would always be a euclidean distance, assuming that refraction is not a concern
}

