
#include "Trail.h"


Trail::Trail() {
   this->length = 0;
   for(int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i) {
      this->breadcrumbs[i] = nullptr;
   }
}

Trail::Trail(Trail& other) {
   this->length = other.length;
   for (int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i) {
      this->breadcrumbs[i] = nullptr;
      if(other.breadcrumbs[i] != nullptr) {
         this->breadcrumbs[i] = new Breadcrumb(*other.breadcrumbs[i]);
      }
   }
}

Trail::~Trail() {
   for(int i = 0; i < length; ++i) {
      if(breadcrumbs[i] != nullptr){
         delete breadcrumbs[i];
         breadcrumbs[i] = nullptr;
      }
   }
}

// Return length of trail
int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   return breadcrumbs[i];
}

// Adds a breadcrumb object to the trail array, adds to length size
void Trail::addCopy(Breadcrumb* t) {
   breadcrumbs[length] = t;
   length++;
}

// Check to see if there is a breadcrumb at coordinates x, y
bool Trail::contains(int x, int y) {
   for(int i = 0; i < length; i++) {
      if(breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y) {
         return true;
      }
   }
   return false;
}


// Milestone #4 Code

// Milestone #4 Constructor
Trail::Trail(int rows, int cols) {
   this->length = 0;
   breadcrumbs = nullptr;
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i < (rows*cols); ++i) {
         breadcrumbs = new Breadcrumb*[rows*cols];
         breadcrumbs[i] = nullptr;
      }
   }
}

// Milestone #4 Copy Constructor
Trail::Trail(Trail& other, int rows, int cols) {
   this->length = other.length;
   breadcrumbs = new Breadcrumb*[rows*cols];
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i < rows*cols; ++i) {
         breadcrumbs[i] = other.breadcrumbs[i];
      }
   }
}