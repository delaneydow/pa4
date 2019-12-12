// include guards
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib> 
#include <vector> 
#include <sstream> 
#include <algorithm> 
#include <iterator> 
#include <ctime> 
#include <fstream>

// include all header files 
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Pokemon.h"
#include "building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h" 
#include "View.h"
#include "Model.h" 
#include "GameCommand.h"

using namespace std; 
// function prototypes, global and before main function  
bool IsNumber(string s); 
bool IsWhiteSpace(string s); 

const string POKEMON_BANNER = "                                  ,'\\\n"
                              "    _.----.        ____         ,'  _\\   ___    ___     ____\n"
                              "_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n"
                              "\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n"
                              " \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n"
                              "   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n"
                              "    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n"
                              "     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n"
                              "      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n"
                              "       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n"
                              "        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n"
                              "                                `'                            '-._|";

int main(int argc, char** argv)
{
	// add introductory menu 
	// Welcome Message
    cout << "EC327: Introduction to Software Engineering" << endl;
    cout << "Fall 2019" << endl;
    cout << "Welcome to Programming Assignment 4" << endl;
    cout << "Delaney M. Dow" << endl; 
    cout << POKEMON_BANNER << endl; // generate pokemon banner

    // construct game model
	Model game_model; 
	View game_view; 
	

	bool game_running = true; // tag
	bool read_file = false; // not reading input 

    char mode; 

    RIV: try // tagged , extra credit to add aditional feature
    {
        cout << "would you like to play in pokemon mode (Z) or in rival mode (E)? " << endl; 
        cin >> mode; 
        if (mode != 'Z' && mode != 'E')
        {
            throw Invalid_Input("Enter correct parameters for mode of game");
        }
    } catch(Invalid_Input& except) 
    {
        cout << "ERROR: " << except.msg_ptr << endl; 
        cin.clear(); 
        cin.ignore(256, '\n'); //ignored remainder of line
        goto RIV; //restart try glock
    }

    if (mode == 'Z')
    {
        cout << "Entering game in pokemon mode..." << endl; 
    } else if (mode == 'E') 
    {
        cout << "Entering game in rival mode..." << endl; 
    }

	// introduce game elements
	game_model.ShowStatus(); 
	game_model.Display(game_view); 
	ifstream input_file; 

	if (argc == 2) {
        input_file.open(argv[1], ios_base::in);
        if (!input_file.is_open()) {
            throw Invalid_Input("invalid number of command characters"); 
        }
        //read_from_file = true;
        srand(0);
    } else
        srand(time(NULL));

    while (game_running) {
        cout << "Enter command: ";

        try 
    {
        char command = 'a';
        int id = 0;
        int id1 = 0;
        int id2 = 0;
        bool error = false;
        string input = "'";
        double x = 0;
        double y = 0;
        unsigned int stamina_amount = 0;
        unsigned int training_unit_amount = 0;
        if (read_file) {
            getline(input_file, input);
        } else
            getline(cin, input);
        if (input.length() > 0 and !IsWhiteSpace(input)) { // output of game, display for user
            istringstream iss(input);
            vector<string> tokens;
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter<vector<string> >(tokens));
            if (tokens[0].length() == 1)
                command = tokens[0][0];
            else
                error = true;
            switch (command) {
                //moving a Pikachu to a location
                case 'm': // move command
                    if (tokens.size() == 4) {
                        id = atoi(tokens[1].c_str());
                        x = atof(tokens[2].c_str());
                        y = atof(tokens[3].c_str());
                    }
                    else {
                        error = true;
                    }
                    if (!error) {
                        Point2D moveTo = Point2D(x, y);
                        DoMoveCommand(game_model, id, moveTo);
                        game_model.Display(game_view);
                    }
                    break;
                case 'c': // center command
                    if (tokens.size() == 3) {
                        id = atoi(tokens[1].c_str());
                        id2 = atoi(tokens[2].c_str());
                    }
                    else {
                        error = true;
                    }
                    if (!error) {
                        DoMoveToCenterCommand(game_model, id, id2);
                        game_model.Display(game_view);
                    }
                    break;
                case 'g': //move to gym command
                    if (tokens.size() == 3) {
                        id = atoi(tokens[1].c_str());
                        id2 = atoi(tokens[2].c_str());
                    }
                    else {
                        error = true;
                    }
                    if (!error) {
                        DoMoveToGymCommand(game_model, id, id2);
                        game_model.Display(game_view);
                    }
                    break;
                case 'r': // stamina amount
                    if (tokens.size() == 3) {
                        id = atoi(tokens[1].c_str());
                        stamina_amount = atoi(tokens[2].c_str());
                    }
                    else {
                        error = true;
                    }
                    if (!error) {
                        DoRecoverInCenterCommand(game_model, id, stamina_amount);
                        game_model.Display(game_view);
                    }
                    break;
                case 't': // unit amount
                    if (tokens.size() == 3) {
                        id = atoi(tokens[1].c_str());
                        training_unit_amount = atoi(tokens[2].c_str());
                    }
                    else {
                        error = true;
                    }
                    if (!error) {
                        DoTrainInGymCommand(game_model, id, training_unit_amount);
                        game_model.Display(game_view);
                    }
                    break;
                case 's': // stop command
                    if (tokens.size() == 2) {
                        id = atoi(tokens[1].c_str());
                    }
                    else {
                        error = true;
                    }
                    if (!error) {
                        DoStopCommand(game_model, id);
                        game_model.Display(game_view);
                    }
                    break;
                case 'v': // go command
                    if (tokens.size() == 1) {
                        DoGoCommand(game_model, game_view);
                    }
                    else {
                        error = true;
                    }
                    break;
                //advance 5 time ticks or until next event

                case 'b': // battle command
                    if (tokens.size() == 3) {
                        id1 = atoi(tokens[1].c_str());
                        id2 = atoi(tokens[2].c_str());
                    }
                    else {
                        error = true;
                    }
                    if (!error) {
                       // DoMoveCommand(game_model, id1, id2); // ID1 inputted first
                        game_model.Display(game_view);
                    }
                    break; 

                case 'a': // move to arena command
                    if (tokens.size() == 3) {
                        id1 = atoi(tokens[1].c_str());
                        id2 = atoi(tokens[2].c_str());
                    if (!error) {
                    }
                    else {
                        error = true;
                    }
                        //DoMoveToArenaCommand(game_model, id1, id2);
                        game_model.Display(game_view);
                    }
                    break;

                case 'x': // run command
                    if (tokens.size() == 1) {
                        DoRunCommand(game_model, game_view);
                    }
                    else {
                        error = true;
                    }
                    break;


                //quit the program
                case 'q': // quit command
                    if (tokens.size() == 1) {
                        cout << "Terminating program." << endl;
                        game_running = false;
                    }
                    else {
                        error = true;
                    }
                    break;
                default:
                    error = true;
                    throw Invalid_Input("Please try a valid command");
                    break;

            }
        }
        if (error)
        {
            game_model.Display(game_view); // displays valid commands only 
        }
    }
    catch (Invalid_Input& except)
    {
        cout << "ERROR: " << except.msg_ptr << endl; 
        cin.clear(); 
        cin.ignore(256, '\n'); // creates new line 
    }
}
    return 0;
}

bool IsNumber(string s){
    for(int i = 0; i < s.length(); i++) {
        if(!(s[i] >= '0' && s[i] <= '9')) {
            return false;
        }
    }
    return true;
}

bool IsWhiteSpace(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ' && s[i] != '\t') {
            return false;
        }
    } // end of main program


	/* part of original submission, given solution was more robust
	char command; 
	cout << "Enter command: " << endl; 
	cin >> command; 

	// run program in loop until quit command is given 
	while (command != 'q')
{

		// switch statment for commands
			// executes and calls functions depending on which command is given
		switch (command)
{
	case 'm': // move command
	{
		cout << "Enter pokemon ID, x and y coordinates: " << endl; 
		cin >> pokemon_id; 
		cin >> x; 
		cin >>  y ; 
		cout << "move" << endl; 
		DoMoveCommand(*modelPtr, pokemon_id, Point2D(x,y));
		break; 
	}

	case 'g': // move to gym command
	{
		cout << "Enter pokemon ID, gym ID" << endl; 
		cin >> pokemon_id ; 
		cin >>  gym_id ; 
		cout << "Move towards a Pokemon Gym" << endl;  
		DoMoveToGymCommand(*modelPtr, pokemon_id, gym_id); 
		break; 
	}

	case 'c': // move to center command
	{
		cout << "Enter pokemon ID, center ID" << endl; 
		cin >> pokemon_id ; 
		cin >> center_id ; 
		cout << "Move towards a Pokemon Center" << endl; 
		DoMoveToCenterCommand(*modelPtr, pokemon_id, center_id);
		break; 
	}

	case 's': // stop command
	{
		cout << "Enter pokemon ID" << endl; 
		cin >> pokemon_id ; 
		cout << "stop" << endl; 
		DoStopCommand(*modelPtr, pokemon_id);
		break; 
	}

	case 'r': // stamina amount
	{
		cin >> pokemon_id ; 
		cin >>  stamina_points;  
		cout << "recover at a Pokemon Center" << endl; 
		DoRecoverInCenterCommand(*modelPtr, pokemon_id, stamina_points); 
	}

	case 't': // unit amount
	{
		cin >> pokemon_id ; 
		cin >> training_units;  
		cout << "complete " << training_units << " training units at a Pokemon Gym" << endl; 
		DoTrainInGymCommand(*modelPtr, pokemon_id, training_units);
		break; 
	}

	case 'v': // go command
	{
		cout << "go" << endl; 
		//DoGoCommand(*modelPtr, *viewPtr);
		break; 
	}

	case 'x': // run command
	{
		cout << "run" << endl; 
		//DoRunCommand(*modelPtr, *viewPtr); // repeats loop 
		break; 
	} 


	} // ends switch statement  

} // ends while loop

	if (command == 'q') 
	{
		cout << "quit." << endl; 
	}
	cout << "Ending program" << endl;
	//View -> ~View(); // deconstructs view 
	//Model -> ~Model(); // deconstructs model 
*/ 

	return 0; 
} // ends main function 

