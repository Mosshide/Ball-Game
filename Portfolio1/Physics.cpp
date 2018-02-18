#include "Physics.h"

Timer::Timer()
{
	_totalTime = 0;
	_deltaTime = 0;
}

Timer::~Timer()
{
}

void Timer::update()
{
	_deltaTime = SDL_GetTicks() - _totalTime;

	if (_deltaTime < 1000.f / 1000.f)
	{
		SDL_Delay(1000.f / 1000.f - _deltaTime);
		_deltaTime = 1000.f / 1000.f;
	}

	if (_deltaTime > 50) _deltaTime = 50;

	_totalTime = SDL_GetTicks();
}

Uint32 Timer::getTotal()
{
	return _totalTime;
}

Uint32 Timer::getDelta()
{
	return _deltaTime;
}

Timer gameTimer;


////////////////
bool pointInRect(Vertex v, fRectangle *r)
{
	if ((v.x >= r->x) && (v.x <= r->x + r->w) && (v.y >= r->y) && (v.y <= r->y + r->h))
		return true;

	else return false;
}

bool pointInRect(Vertex v, fRectangle r)
{
	if ((v.x >= r.x) && (v.x <= r.x + r.w) && (v.y >= r.y) && (v.y <= r.y + r.h))
		return true;

	else return false;
}

bool rectCollison(fRectangle a, fRectangle b)
{
	if (pointInRect(a.getVertex(0), b)) return true;
	else if (pointInRect(a.getVertex(1), b)) return true;
	else if (pointInRect(a.getVertex(2), b)) return true;
	else if (pointInRect(a.getVertex(3), b)) return true;

	else if (pointInRect(b.getVertex(0), a)) return true;
	else if (pointInRect(b.getVertex(1), a)) return true;
	else if (pointInRect(b.getVertex(2), a)) return true;
	else if (pointInRect(b.getVertex(3), a)) return true;

	else return false;
}

fRectangle rectIntersection(fRectangle a, fRectangle b)
{
	fRectangle c;

	if (a.x > b.x) c.x = a.x;
	else c.x = b.x;

	if (a.y > b.y) c.y = a.y;
	else c.y = b.y;

	if (a.x + a.w > b.x + b.w) c.w = b.x + b.w - c.x;
	else c.w = a.x + a.w - c.x;

	if (a.y + a.h > b.y + b.h) c.h = b.y + b.h - c.y;
	else c.h = a.y + a.h - c.y;

	return c;
}

float distanc3(V3rtex a, V3rtex b)
{
	GLfloat distancex = (b.x - a.x) * (b.x - a.x);
	GLfloat distancey = (b.y - a.y) * (b.y - a.y);
	GLfloat distancez = (b.z - a.z) * (b.z - a.z);

	return sqrt(distancex + distancey + distancez);
}

float distance(Vertex a, Vertex b)
{
	GLfloat distancex = (b.x - a.x) * (b.x - a.x);
	GLfloat distancey = (b.y - a.y) * (b.y - a.y);

	return sqrt(distancex + distancey); 
}

float distance(SDL_Point a, SDL_Point b)
{
	GLfloat distancex = GLfloat((b.x - a.x) * (b.x - a.x));
	GLfloat distancey = GLfloat((b.y - a.y) * (b.y - a.y));

	return sqrt(distancex + distancey);
}

void getDirectedVelocity(Vertex a, Vertex b, GLfloat speed, Vertex &vel)
{
	float dir = getDirection(a, b);
	vel.x = -speed*cos(dir);
	vel.y = -speed*sin(dir);
}

float getDirection(Vertex a, Vertex b)
{
	return atan2((a.y - b.y), (a.x - b.x));
}

void rotate(Vertex pivot, GLfloat angle, Vertex &point)
{
	GLfloat s = sin(angle);
	GLfloat c = cos(angle);

	// translate point back to origin:
	point.x -= pivot.x;
	point.y -= pivot.y;

	// rotate point
	GLfloat xnew = point.x * c - point.y * s;
	GLfloat ynew = point.x * s + point.y * c;

	// translate point back:
	point.x = xnew + pivot.x;
	point.y = ynew + pivot.y;
}

bool rayPlaneCollision(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 pNormal, glm::vec3 pPoint, GLfloat *distance)
{
	GLfloat distanceNumerator = glm::dot(pNormal, pPoint - rayOrigin);
	GLfloat distanceDenominator = glm::dot(pNormal, rayDirection);

	if (distanceDenominator != 0)
	{
		if (distance != nullptr) *distance = distanceNumerator / distanceDenominator;
		return true;
	}
	else return false;
}

bool segIntersection(Vertex x, Vertex y, Vertex a, Vertex b, Vertex *i)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = y.x - x.x;     
	s1_y = y.y - x.y;
	s2_x = b.x - a.x;     
	s2_y = b.y - a.y;

	float s, t;
	s = (-s1_y * (x.x - a.x) + s1_x * (x.y - a.y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (x.y - a.y) - s2_y * (x.x - a.x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		if (i != nullptr)
		{//return intersection
			i->x = x.x + (t * s1_x);
			i->y = x.y + (t * s1_y);
		}
			
		return true;
	}

	return false; // No collision
}

bool segIntersection(lineSeg r, lineSeg s, Vertex *i)
{
	return segIntersection(r.a, r.b, s.a, s.b, i);
}