//chapter 2 exercise to instruct someone to find the bathroom
#include <iostream>

using namespace std;

int main()
{
	//instructions to find the bathroom in a house
	cout << "Instructions to find the bathroom in a house: \n";
	cout << "Walk up stairs on the porch.\n";
	cout << "Knock on door and wait for an answer.\n";
	cout << "If answered, ask to use bathroom. Wait for reply.\n";
	cout << "If no answer, walk down the stairs and go to the next house.\n";
	cout << "If reply is consent, ask for instructions to find the bathroom.\n";
	cout << "If door is open, walk though the door and enter the hallway.\n";
	cout << "If the door between the hallway and the dining room is open, walk into the dining room.\n";
	cout << "If the door between the hallway and the dining room is closed, open the door and walk into the dining room.\n";
	cout << "Walk 4.5 meters away from the door you entered from and pause.\n";
	cout << "Rotate entire body 270 degrees in a clockwise direction.\n";
	cout << "Walk 1.5 meters forward in the direction you currently face.\n";
	cout << "If the bathroom door is open, walk into the bathroom.\n";
	cout << "If the bathroom door is closed, knock and wait 2 minutes for a possible response.\n";
	cout << "If the bathroom door is closed and there is a response, apologise and leave.\n";
	cout << "If the bathroom door is closed and there is no response, wait 30 seconds and gently attempt to open the door.\n";
	cout << "If the attempt to open the door is successful, check that no people are in the bathroom.\n";
	cout << "If there are people in the bathroom, apologize and leave.\n";
	cout << "If there aer no people in the bathroom, walk into the bathroom.\n";
	cout << "If you are alone in the bathroom, close the door.\n";
	cout << "If you are alone in the bathroom with the door closed, perform a celebratory dance.\n";

	return 0;
}