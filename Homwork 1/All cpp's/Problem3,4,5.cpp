/************************************************************************************************************************
Logan Feeney
Homework 1
Problem 3,4,5
2/14/24
************************************************************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <utility>

class Plane 
{
private:
    double pos, vel, distance;                                      // Creating double variables for pos, vel, and distance
    bool at_SCE;                                                    // Creating bollean variable for at_SCE
    std::string origin;                                             // Creating origin string variable
    std::string destination;                                        // Creating distination string variable
    std::map<std::pair<std::string, std::string>, int> Distance;    // Container from Question 2

public:
    Plane(const std::string& from, const std::string& to) : origin(from), destination(to)       // Constructor
    {
        // Using container for Question 2 to set the value of "distance"
        // Initialize flight distances
        Distance[{"SCE", "PHL"}] = 160;
        Distance[{"SCE", "ORD"}] = 640;
        Distance[{"SCE", "EWR"}] = 220;

        // Check distance between origin and destination airports
        auto check = Distance.find({ origin, destination });
        if (check != Distance.end()) 
        {
            distance = check->second;
            std::cout << "Distance between " << origin << " and " << destination << ": " << distance << " miles" << std::endl;
        }
        else {
            std::cerr << "Error: Distance between " << origin << " and " << destination << " not found!" << std::endl;
        }

        std::cout << "Plane Created at " << this << std::endl;
    }


    ~Plane()                                                                                    // Deconstructor
    {
        std::cout << "Plane Destroyed" << std::endl;
    }

    void operate(double dt)                             // Function named "operate" with "dt" as input variable
    {
        if (pos < distance)                             // if pos < distance is true, pos += vel*dt
        {
            pos += vel * dt;
            at_SCE = 0;
        }
        else                                            // if pos < distance is false, go to destination == "SCE" block
        {
            if (destination == "SCE")                   // if destination == "SCE" is true, set at_SCE = 1 making it true
            {                                   
                at_SCE = 1.0;
                std::string swap1 = origin;             // Using a swap variable to change origin to destination and vice versa
                origin = destination;
                destination = swap1;
            }
            
            else                                        // if false, swap origin and destination and make pos = 0.0 
            {
                std::string swap2 = origin;             // Using a swap variable to change origin to destination and vice versa
                origin = destination;
                destination = swap2;
            }
            
            pos = 0.0;
        }
    }

    double getPos() const { return pos; }                           // Get function for "pos"
    std::string getOrigin() const { return origin; }                // Get function for "origin"
    std::string getDestination() const { return destination; }      // Get function for "destination"
    bool IsAtSCE() const { return at_SCE; }                         // Get function for "at_SCE"
    double getVel() const { return vel; }                           // Get function for "vel"
    void setVel(double new_vel) { vel = new_vel; }                  // Set function for "vel"
   
};

int main() 
{
    Plane airplane("SCE", "PHL");                       // Instantiate airplane object with a chosen pair of arrival and departure flights

    double flightspeed = 450.0;                         // Set the flight speed of the airplane to 450 mph
    airplane.setVel(flightspeed);

    double dt = 20.0/3600;                              // Timestep of 20 seconds (converted to hours for mph multiplication in "operate")
    int maxIterations = 1500;                           // Maximum iterations of 1500
    
    std::cout << "Time: " << 0.0 << " seconds, Position: " << airplane.getPos() << " miles." << std::endl;

    // Iterate through the operate function for each airplane object with the given time step
    for (int i = 0; i < maxIterations; i += 20) 
    {
        airplane.operate(dt);                           // operate function call

        // Print out the airplane position at each timestep
        std::cout << "Time: " << i+20 << " seconds, Position: " << airplane.getPos() << " miles." << std::endl;
    }
    
    return 0;
}

