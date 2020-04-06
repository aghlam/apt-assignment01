// Alan Lam s3436174

#include "Breadcrumb.h"

Breadcrumb::Breadcrumb(int x, int y, bool stale):
   x(x),
   y(y),
   stale(stale)
{
   this->direction = "no direction";
}

Breadcrumb::Breadcrumb(Breadcrumb& other) :
   x(other.x),
   y(other.y),
   stale(other.stale),
   direction(other.direction)
{

}

Breadcrumb::~Breadcrumb() {
   
}

int Breadcrumb::getX() {
   return x;
}

int Breadcrumb::getY() {
   return y;
}

bool Breadcrumb::isStale() {
   return stale;
}

void Breadcrumb::setStale(bool stale) {
   this->stale = stale;
}

// Milestone #3 Code

void Breadcrumb::setDirection(std::string direction) {
   this->direction = direction;
}

std::string Breadcrumb::getDirection() {
   return direction;
}