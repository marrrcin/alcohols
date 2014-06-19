#include "CollisionDetector.h"

const double CollisionDetector::degreesToRad = 3.14159265359/180.0;
double CollisionDetector::maxX=-666;
double CollisionDetector::maxY=-666;
std::vector<glm::vec2> CollisionDetector::boundLines;
std::vector<glm::vec2> CollisionDetector::boundPoints;

CollisionDetector::CollisionDetector(void)
{
}


CollisionDetector::~CollisionDetector(void)
{
}
