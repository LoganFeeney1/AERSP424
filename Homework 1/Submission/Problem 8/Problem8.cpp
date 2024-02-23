/************************************************************************************************************************
Logan Feeney
Homework 1
Problem 8
2/17/24
* ***********************************************************************************************************************/


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
    std::map<std::pair<std::string, std::string>, int>* Distance;   // Container from Question 2

public:
    Plane(const std::string& from, const std::string& to) : origin(from), destination(to)   // Constructor
    {
        // Using container for Question 2 to set the value of "distance"
        // Initialize flight distances
        Distance = new std::map<std::pair<std::string, std::string>, int>;
        (*Distance)[std::make_pair("SCE", "PHL")] = 160;
        (*Distance)[std::make_pair("SCE", "ORD")] = 640;
        (*Distance)[std::make_pair("SCE", "EWR")] = 220;

        // Check distance between origin and destination airports
        std::map<std::pair<std::string, std::string>, int>::iterator check = Distance->find(std::make_pair(origin, destination));
        if (check != Distance->end())
        {
            distance = check->second;
            std::cout << "Distance between " << origin << " and " << destination << ": " << distance << " miles" << std::endl;
        }
        else {
            std::cerr << "Error: Distance between " << origin << " and " << destination << " not found!" << std::endl;
        }

        std::cout << "Plane Created at " << this << std::endl;
    }

    ~Plane()                                                    // Deconstructor
    {   
        delete Distance;
        std::cout << "Plane Destroyed" << std::endl;
    }

    void operate(double dt)                                     // Function named "operate" with "dt" as input variable
    {
        if (pos < distance)                                     // if pos < distance is true, pos += vel*dt
        {
            pos += vel * dt;
            at_SCE = false;
        }
        else                                                    // if pos < distance is false, go to destination == "SCE" block
        {
            if (destination == "SCE")                           // if destination == "SCE" is true, set at_SCE = 1 making it true
            {
                at_SCE = true;
                std::string swap1 = origin;
                origin = destination;
                destination = swap1;
            }
            else                                                // if false, swap origin and destination and make pos = 0.0
            {
                std::string swap2 = origin;                     // Using a swap variable to change origin to destination and vice versa
                origin = destination;
                destination = swap2;
            }

            pos = 0.0;
        }
    }

    double getPos() const { return pos; }                       // Get function for "pos"
    std::string getOrigin() const { return origin; }                // Get function for "origin"
    std::string getDestination() const { return destination; }      // Get function for "destination"
    bool IsAtSCE() const { return at_SCE; }                         // Get function for "at_SCE"
    double getVel() const { return vel; }                           // Get function for "vel"
    void setVel(double new_vel) { vel = new_vel; }                  // Set function for "vel"

};

class Pilot     //pilot class
{
private:
    std::string name;

public:
    Pilot(const std::string& pilotName) : name(pilotName), myPlane(NULL)
    {
        std::cout << name << " is at memory address " << this << " and is at the gate, ready to board the plane." << std::endl;
    }

    ~Pilot()
    {
        std::cout << name << " is out of the plane." << std::endl;
    }

    std::string getName() const { return name; }

    Plane* myPlane;
};

int main()
{
    Plane* airplane = new Plane("SCE", "PHL");          // Instantiate airplane object with a chosen pair of arrival and departure flights
    Pilot* alpha = new Pilot("Alpha");
    Pilot* bravo = new Pilot("Bravo");

    alpha->myPlane = airplane;
    bravo->myPlane = airplane;

    double flightspeed = 500.0;                         // Set the flight speed of the airplane to 500 mph
    airplane->setVel(flightspeed);

    double dt = 100.0 / 3600;                           // Timestep of 100 seconds (converted to hours for mph multiplication in "operate")      
    int maxIterations = 2000;                           // Maximum iterations of 2000

    Pilot* currentPilot = alpha;                        // Start with Alpha pilot controlling the plane
    std::string currentPilotName = currentPilot->getName();

    std::cout << "Time: " << 0.0 << " seconds, Position: " << airplane->getPos() << " miles." << std::endl;

    // Iterate through the operate function for each airplane object with the given time step
    for (int i = 0; i < maxIterations; i += 20)
    {
        currentPilot->myPlane->operate(dt);             // operate function call

        if (currentPilot->myPlane->IsAtSCE())           // condition if/else to check if pilot has returned to SCE
        {
            std::cout << "Plane is at SCE. Pilot: " << currentPilotName << ", Memory Address: " << currentPilot << std::endl;
            if (currentPilot == alpha)
            {
                currentPilot = bravo;
                currentPilotName = currentPilot->getName();
            }
            else
            {
                currentPilot = alpha;
                currentPilotName = currentPilot->getName();
            }
            std::cout << "New Pilot: " << currentPilotName << ", Memory Address: " << currentPilot << std::endl;
        }

        // Print out the airplane position at each timestep
        std::cout << "Time: " << i + 20 << " seconds, Position: " << airplane->getPos() << " miles." << std::endl;
    }

    delete alpha;
    delete bravo;
    delete airplane;

    return 0;
}
