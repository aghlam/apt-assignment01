
#ifndef COSC_ASS_ONE_BREADCRUMB
#define COSC_ASS_ONE_BREADCRUMB

#include "Types.h"

#include <iostream>
#include <string>

class Breadcrumb {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Constructor/Desctructor
   Breadcrumb(int x, int y, bool stale);
   ~Breadcrumb();

   // x-co-ordinate of the particle
   int getX();

   // y-co-ordinate of the particle
   int getY();

   // Get if the Breadcrumb is stale. (If false, it is good/fresh)
   bool isStale();

   // Mark this Breadcrumb as stale (or not)
   void setStale(bool stale);

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Copy Constructor
   Breadcrumb(Breadcrumb& other);

   // Milestone #3

   void setDirection(std::string direction);

   std::string getDirection();

private:

   /*                                           */
   /* DO NOT MOFIFY THESE VARIABLES             */
   /*                                           */
   int x;
   int y;
   bool stale;


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   // Milestone #3
   std::string direction;

   
};

#endif // COSC_ASS_ONE_BREADCRUMB
