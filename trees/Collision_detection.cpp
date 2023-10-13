#include "Collision_detection.h"
#include <algorithm>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
float Collision_detection::getDistanceFromSeg(glm::vec3 point, glm::vec3 start, glm::vec3 end, float diameter) {
    // Calculate the vector from the start to the end of the segment
    glm::vec3 segVector = end - start;

    // Calculate the vector from the start to the point
    glm::vec3 startToPoint = point - start;

    // Project startToPoint onto segVector
    float projectionLength = glm::dot(startToPoint, glm::normalize(segVector));

    // If the projection falls outside the segment, return max float
    if (projectionLength < 0 || projectionLength > glm::length(segVector)) {
        return std::numeric_limits<float>::max();
    }

    // Find the projected point
    glm::vec3 projectedPoint = start + glm::normalize(segVector) * projectionLength;

    // Calculate the distance from the point to the projected point
    float distanceToPoint = glm::length(point - projectedPoint);

    // Subtract the radius of the cylinder from the distance to get the distance from the point to the surface of the cylinder
    float distanceToSurface = distanceToPoint - diameter / 2.0f;
    return distanceToSurface;
}

glm::vec3 Collision_detection::projectOnto(glm::vec3 A, glm::vec3 B) {
    float dotProduct = glm::dot(A, B);
    float magnitudeSquared = glm::dot(B, B);
    return (dotProduct / magnitudeSquared) * B;
}

float Collision_detection::getAngle(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
    // Calculate the lengths of the sides of the triangle
    float AB_length = glm::length(A - B);
    float BC_length = glm::length(B - C);
    float AC_length = glm::length(A - C);

    // Use the Law of Cosines to find the angle at B
    float numerator = AB_length * AB_length + BC_length * BC_length - AC_length * AC_length;
    float denominator = 2.0f * AB_length * BC_length;

    // Handle possible division by zero (if either side is zero-length)
    if (denominator == 0.0f) {
        return 0.0f;
    }

    float cosine_angle = numerator / denominator;

    // Clamp the cosine value to the range [-1, 1] to handle potential floating-point errors
    cosine_angle = glm::clamp(cosine_angle, -1.0f, 1.0f);

    // Return the angle in degrees
    return std::acos(cosine_angle);
}

glm::vec2 Collision_detection::getRotationAngles(glm::vec3 A, glm::vec3 B, glm::vec3 C){
    // Normalize the input vectors
    A = glm::normalize(A);
    B = glm::normalize(B);
    C = glm::normalize(C);
   /* std::cout << "angles: -----\n";
    std::cout << "A: (" << A.x << " , " << A.y << " , " << A.z << ")\n";
    std::cout << "B: (" << B.x << " , " << B.y << " , " << B.z << ")\n";
    std::cout << "C: (" << C.x << " , " << C.y << " , " << C.z << ")\n";*/

    // Compute the cross product of vectors A and B
    glm::vec3 crossAB = glm::normalize(glm::cross(A, B));
    //std::cout << "CrossAB: (" << crossAB.x << " , " << crossAB.y << " , " << crossAB.z << ")\n";
    // Project vector C onto the plane defined by vectors A and B
    glm::vec3 projection = C - projectOnto(C, crossAB);
    //std::cout << "projection: (" << projection.x << " , " << projection.y << " , " << projection.z << ")\n";

    //std::cout << glm::orientedAngle(glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)) << "\n";

    // Find the angle to rotate around the B axis
    float yAngle = glm::orientedAngle(A, projection, crossAB);

    //rotate C by angle Y around cross

   // Rotate vector A around the B axis
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -yAngle, crossAB);
    glm::vec3 C_rotated = glm::vec3(rotationMatrix * glm::vec4(C, 1.0f));
    //std::cout << "C_rotated: (" << C_rotated.x << " , " << C_rotated.y << " , " << C_rotated.z << ")\n";

    // Project vector C onto the plane defined by vectors A and AB cross
    projection = C - projectOnto(C, B);
    //std::cout << "projection: (" << projection.x << " , " << projection.y << " , " << projection.z << ")\n";
    

    // Find the angle to rotate around the B axis
    float xAngle = glm::orientedAngle(A, C_rotated, B);


    //std::cout << xAngle << " | " << yAngle << "\n";
    return glm::vec2(xAngle, yAngle);
}

bool Collision_detection::correctSpherePositionC(glm::vec3 dynamicPosPrev, glm::vec3* dynamicPos, float rd, glm::vec3 staticPos, glm::vec3 staticPos2, float rs) {

    // early exit if no collision at any point
    if (shortestDistanceBetweenSegments(dynamicPosPrev, *dynamicPos, staticPos, staticPos2) > rd + rs) {
        return false;
    }

    // checking to see if the sphere started in line with the main part of the segment
    
    //get length of cylinder
    float cylinderLength = glm::length(staticPos2 - staticPos);

    //get sphere pos projected onto cylinder
    glm::vec3 proj = staticPos + projectOnto(dynamicPosPrev - staticPos, staticPos2 - staticPos);
    // if neg or further along than cyl length, was not in line
    if (dot(projectOnto(dynamicPosPrev - staticPos, staticPos2 - staticPos), staticPos2 - staticPos) < 0) {
        //if not in corner seg, treat as plane
        if (glm::length((dynamicPosPrev - staticPos) - projectOnto((dynamicPosPrev - staticPos), (staticPos2 - staticPos))) < rs + rd) {
            //take away proj onto cyl line, add cyl line dir * rd
            if (glm::length(projectOnto((dynamicPosPrev - staticPos), (staticPos2 - staticPos))) < rd) {
                //*dynamicPos += projectOnto((dynamicPosPrev - staticPos), (staticPos2 - staticPos));
                *dynamicPos -= glm::normalize(staticPos2 - staticPos) * (rd - glm::length(projectOnto((dynamicPosPrev - staticPos), (staticPos2 - staticPos))));
            }

        }
        else {
            std::cout << "yep 1\n";
        }
    } else if (glm::length(projectOnto(dynamicPosPrev - staticPos, staticPos2 - staticPos)) > cylinderLength) {
        //if not in corner seg, treat as plane
        if (glm::length((dynamicPosPrev - staticPos) - projectOnto((dynamicPosPrev - staticPos), (staticPos2 - staticPos))) < rs + rd) {
            if (glm::length(projectOnto((dynamicPosPrev - staticPos2), (staticPos - staticPos2))) < rd) {
                
                //*dynamicPos += projectOnto((dynamicPosPrev - staticPos), (staticPos2 - staticPos));
                *dynamicPos -= glm::normalize(staticPos - staticPos2) * (rd - glm::length(projectOnto((dynamicPosPrev - staticPos2), (staticPos - staticPos2))));
            }
        }
        else {
            std::cout << "yep 2\n";
        }
    }
    else {
        // get direction from prev pos projection onto cylinder, to prev pos

        glm::vec3 startDirNorm = glm::normalize(dynamicPosPrev - staticPos - projectOnto(dynamicPosPrev - staticPos, staticPos2 - staticPos));

        // get direction from next pos projection onto cylinder, to next pos

        glm::vec3 endDir = *dynamicPos - staticPos - projectOnto(*dynamicPos - staticPos, staticPos2 - staticPos);

        //correct pos onto the right side if it passed to the other side of the centreline of the cylinder
        if (glm::dot(startDirNorm, endDir) < 0) {
            *dynamicPos -= endDir + 0.01f * startDirNorm;
        }

        //recalc vector to current vector from cylinder centerline to new sphere pos
         endDir = *dynamicPos - staticPos - projectOnto(*dynamicPos - staticPos, staticPos2 - staticPos);

        //correct position
        float currentDist = glm::length(endDir);
        *dynamicPos += startDirNorm * (rd + rs - currentDist);
        return true;

    }


    //project sphere pos onto cylinder line
    //glm::vec3 projection = projectOnto()

    // treat as circle circle

    //for cases where the center of the static circle are between the current and previous dynamic pos; just move the current pos back to in line with the static one and then do circle correction there
    // (just use correctSpherePositions????)
    

    // ends

    return false;
}

bool Collision_detection::correctSpherePositionS(glm::vec3 dynamicPosPrev, glm::vec3* dynamicPos, float rd, glm::vec3 staticPos, float rs) {
    if (glm::distance(*dynamicPos, staticPos) < rd + rs) {
        *dynamicPos = staticPos + glm::normalize(*dynamicPos - staticPos) * (rd + rs);
        return true;
    }
    return false;
}


float Collision_detection::pointToSegmentDistance(const glm::vec3& point, const glm::vec3& segStart, const glm::vec3& segEnd) {
    const glm::vec3 segDir = segEnd - segStart;
    const float segLengthSquared = glm::dot(segDir, segDir);
    if (segLengthSquared == 0.0f) {
        // Segment is a point
        return glm::length(point - segStart);
    }
    const float t = std::max(0.0f, std::min(1.0f, glm::dot(point - segStart, segDir) / segLengthSquared));
    const glm::vec3 projection = segStart + t * segDir;
    return glm::length(point - projection);
}

float Collision_detection::shortestDistanceBetweenSegments(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& q1, const glm::vec3& q2) {
    float minDist = std::numeric_limits<float>::infinity();
    minDist = std::min(minDist, pointToSegmentDistance(p1, q1, q2));
    minDist = std::min(minDist, pointToSegmentDistance(p2, q1, q2));
    minDist = std::min(minDist, pointToSegmentDistance(q1, p1, p2));
    minDist = std::min(minDist, pointToSegmentDistance(q2, p1, p2));
    return minDist;
}