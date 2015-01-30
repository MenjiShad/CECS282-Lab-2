#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
	
   // Prompt user for rng seed
   int seed = -1;
	
   // input validation
   while (seed <= 0) {
	  cout << "Please enter a positive integer for the seed" << endl;
      cin >> seed;
   }

   // create rng and generate the distance
   default_random_engine engine(seed); 
   uniform_real_distribution<double> distr(1.00, 1000.00);
   double targetDistance = distr(engine);
   cout << "The target is " << fixed << setprecision(2) << targetDistance
    << " meters away" << endl;
	
   bool gameOn = true;
   do {
	  // Prompt user for angle and gunpowder
	  double angle = -1.0, gunpowder = -1.0;
	  while (angle < 0 || angle > 90) {
		 cout << "Enter an angle between 0 and 90 degrees: " << endl; // 20 lines
		 cin >> angle;
	  }
	  while (gunpowder < 0) {
		 cout << "Enter in the kilogram amount of gunpowder to use: " << endl;
		 cin >> gunpowder; 
	  }

	  // Calculate y-distance and time
	  // y(t) = (.5)*a*t^2 + Vy*t, where a = gravity constant
	  // Vy(t) = a * t + Vy
	  // When Vy(t) = 0, max height has been reached
	  // Velocity (V) = Gunpowder (kg) * 30 m/s
	  // Vy = V * sin(angle) <- convert to radians
	  // radians = (pi/180) * angle
	  // t = -(gunpowder*30*sin(angle*pi/180) / a, where a = -g
	  // When the ball hits the ground, the above time is doubled
	  double xDistance, time;
	  const double GRAVITY_CONSTANT = 9.8, PI = 3.1415926535897;
	  time = 2 * (gunpowder * 30 * sin(angle * PI / 180) / GRAVITY_CONSTANT);

	  // Calculate the x-distance
	  // x = Vx*t
	  xDistance = gunpowder * 30 * cos(angle * PI / 180) * time; // 29 lines
	  if (xDistance <= targetDistance + 1 && xDistance >= targetDistance - 1) { 
	     cout << "You got a hit!" << endl;
		 gameOn = false;
      } else {
	     if (targetDistance - xDistance > 0) {
		    cout << "You were " << targetDistance - xDistance
			 << " meters short.\n" << endl;
		 } else {
		    cout << "You were " << xDistance - targetDistance
			 << " meters too far.\n" << endl;
		 }
	  }
   } while (gameOn); // 40 lines

   return 0; // 41 lines
}
