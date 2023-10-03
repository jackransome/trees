#pragma once
#include "Globals.h"
#include "Csegment.h"
class Entity1 : public Polyhedron {
public:
	explicit Entity1(Csegment* startingSegment);
	void perLoop() override;
	void changeSegment(Csegment* _segment);
	Csegment* getSegment();
	void setHeight(float _height);
	void setPlanePos(glm::vec2 _planePos);
private:
	
	glm::vec2 planePos;
	glm::vec2 segmentBounds;
	Csegment* segment;
	float directionAngle = 0;
	glm::vec2 planeDirection;
	glm::vec2 planeDirectionRight;
	float hVel = 0;
	float height;
	bool onGround = true;
	glm::vec2 correctPlanePos(glm::vec2 _planePos);
	//camera manual values:
	glm::vec3 cameraFrom;
	glm::vec3 cameraTo;
	glm::vec3 cameraUp;
	glm::vec3 oldCameraFrom;
	glm::vec3 oldCameraTo;
	glm::vec3 oldCameraUp;
	float speed = 0.01f;
	bool switched = false;
	float switchCounter = 0;
};