/************************************************************************************************************************
Logan Feeney
Homework 1
Probem 1
2/8/24
************************************************************************************************************************/

#include <iostream>
#include <array>
using namespace std;

int main()
{
    // Initializing allof the required variables
    int number_of_front, number_of_rear;
    double empty_weight, empty_weight_moment, weight_of_front, total_weight_of_front = 0.0,
        front_moment, weight_of_rear, total_weight_of_rear = 0.0, rear_moment, number_of_gal,
        usable_fuel_weight, fuel_tank_moment, baggage_weight, baggage_moment;

    const double max_allowable_weight = 2950.0;     // Airplane Design Limit
    const double forward_CG = 82.1;                 // Airplane Design Limit
    const double aft_CG = 84.7;                     // Airplane Design Limit

    // recieve information from the user and storing in an appropriate variable
    cout << "Please enter the airplane's empty weight (pounds): ";
    cin >> empty_weight;
    cout << "Please enter the airplane's empty-weight moment (pounds-inches): ";
    cin >> empty_weight_moment;
    cout << "Please enter the number of front seat occupants: ";
    cin >> number_of_front;

    for (int i = 0; i < number_of_front; i++)
    {
        cout << "Please enter the weight of the " << i + 1 << " front seat occupant (pounds) : ";
        cin >> weight_of_front;
        total_weight_of_front += weight_of_front;
    }

    cout << "Please enter the front seat moment arm (inches): ";
    cin >> front_moment;
    cout << "Please enter the number of rear seat occupants: ";
    cin >> number_of_rear;

    for (int i = 0; i < number_of_rear; i++)
    {
        cout << "Please enter the weight of the " << i + 1 << " rear seat occupant (pounds) : ";
        cin >> weight_of_rear;
        total_weight_of_rear += weight_of_rear;
    }

    cout << "Please enter the rear seat moment arm (inches): ";
    cin >> rear_moment;
    cout << "Please enter the number of gallons of usable fuel (gallons): ";
    cin >> number_of_gal;
    cout << "Please enter the useable fuel weights per gallon (pounds): ";
    cin >> usable_fuel_weight;
    cout << "Please enter the fuel tank moment arm (inches): ";
    cin >> fuel_tank_moment;
    cout << "Please enter the baggage weight (pounds): ";
    cin >> baggage_weight;
    cout << "Please enter the baggage moment arm (inches): ";
    cin >> baggage_moment;

    // Initializing a new gross weight and CG location varaible
    double gross_weight, total_moment, CG_location;

    // Calculating the gross weight
    gross_weight = empty_weight + total_weight_of_front + total_weight_of_rear +
        (number_of_gal * usable_fuel_weight) + baggage_weight;

    // Calcuating the total moment arm
    total_moment = empty_weight_moment + (total_weight_of_front * front_moment)
        + (total_weight_of_rear * rear_moment)
        + (number_of_gal * usable_fuel_weight * fuel_tank_moment)
        + (baggage_weight * baggage_moment);

    // Calculating the CG location
    CG_location = total_moment / gross_weight;

    // Calculating the total fuel weight
    double total_fuel_weight = number_of_gal * usable_fuel_weight;

    if (gross_weight < max_allowable_weight && CG_location < aft_CG && CG_location > forward_CG)
    {
        cout << "The values are all within the airplanes design limits." << endl;
    }
    else
    {
        cout << "\nEither the gross weight and/or the CG location exceeds the airplane's design limits." << endl;
        cout << "A fuel adjustment will be made to correct for any limit exceedance." << endl;

        double total_fuel_adjusted = 0.0; // Variable to track total fuel adjusted

        // Determining whether the values meet the airplane's design limits
        while (gross_weight > max_allowable_weight || CG_location > aft_CG || CG_location < forward_CG)
        {

            if (gross_weight > max_allowable_weight)            // if the gross weight exceedance is met
            {
                gross_weight = gross_weight - 0.1;              // subtract from the total gross weight until condition is met
                total_fuel_weight = total_fuel_weight - 0.1;    // suctract from the total fuel weight which is how the gross weight is reduced
                CG_location = total_moment / gross_weight;      // calculate a new CG location
                total_fuel_adjusted += 0.1;                     // Add to total fuel adjusted
            }
            else
            {
                gross_weight = gross_weight;                    // if the if statement becomes false, leave all values as is.
                total_fuel_weight = total_fuel_weight;
                CG_location = total_moment / gross_weight;
            }

            if (CG_location > aft_CG)                           // if the CG is too far aft
            {
                gross_weight = gross_weight + 0.1;              // Add to the total gross weight until condition is met
                total_fuel_weight = total_fuel_weight + 0.1;    // Add to the total fuel weight which is how the gross weight is increased
                CG_location = total_moment / gross_weight;      // calculate a new CG location
                total_fuel_adjusted -= 0.1;                     // Subtract from total fuel adjusted
            }
            else
            {
                gross_weight = gross_weight;                    // if the if statement becomes false, leave all values as is.
                total_fuel_weight = total_fuel_weight;
                CG_location = total_moment / gross_weight;
            }

            if (CG_location < forward_CG)                       // if the CG is too far forward
            {
                gross_weight = gross_weight - 0.1;              // subtract from the total gross weight until condition is met
                total_fuel_weight = total_fuel_weight - 0.1;    // suctract from the total fuel weight which is how the gross weight is reduced
                CG_location = total_moment / gross_weight;      // calculate a new CG location
                total_fuel_adjusted += 0.1;                     // Add to total fuel adjusted
            }
            else
            {
                gross_weight = gross_weight;                    // if the if statement becomes false, leave all values as is.
                total_fuel_weight = total_fuel_weight;
                CG_location = total_moment / gross_weight;
            }
        }

        cout << "\nTotal fuel adjusted: " << total_fuel_adjusted << " lbs." << endl;
        cout << "The new gross weight is " << gross_weight << " (pounds)." << endl;
        cout << "The new CG location is " << CG_location << " (inches)." << endl;
    }


    return 0;
}


