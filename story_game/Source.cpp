/*
	"life story" is adven game is for those who wants to play something diffrente
	By mohammad hossein asghari

*/

/* we need some class for stages:
	stage:
		choices: list1, list2
		stage number
		stage pic: some sort of ascii picture!

after checking the user input with stage lists decide what to do with the stage

input ---> checking --> map to one of lists ----> change the state or stay on same stage
*/
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <unistd.h>
#include <string>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

int calc_lenght_noS(string input)
{
	int size = 0;
	for(int i = 0 ; i < input.length() ; i++)
	{
		if(input[i]!= ' ')
			size++;
	}
	return size;
}
void print_text(string text,unsigned int mil)
{
	for(int i = 0 ; i < text.length(); i++)
	{	
		cout<<text[i];
		cout.flush();
		usleep(mil*100);
	}
}
enum state{
	stage_0,
	stage_1,
	stage_2,
	stage_3,
	stage_4,
	stage_5,
	stage_6,
	stage_7,
	stage_8,
	stage_9,
	stage_10,
	stage_11,
	stage_12,
	stage_13,
	stage_14,
	stage_15,
	stage_16,
	stage_17,
	stage_18,
	stage_19,
	stage_20,
	stage_21
};

class Lists{
public:
	Lists()
	{

	}
	vector <vector <string>> groups;
	vector <state> sstate;
};
class Stage
{
public:
	Stage()
	{
		c_state = stage_0;
	}
	~Stage()
	{
	}
	void add_choice(string input)
	{
		choices.push_back(input);
	}
	void create_group(state s)
	{
		lists.groups.push_back(choices);
		lists.sstate.push_back(s);
		choices.clear();
	}
	void print_choices()
	{
		for(int i = 0 ; i < choices.size(); i++)
		{
			cout<<choices[i].c_str()<<endl;
		}
	}
	void print_by_groups()
	{
		for(int i = 0 ; i < lists.groups.size(); i++)
		{
			cout<<"\ngroup number "<<i<<":"<<endl;
			for(int j = 0 ; j < lists.groups[i].size(); j++)
			{
				cout<<lists.groups[i][j].c_str()<<" ";
			}
		}
	}
	int pointing(string input, vector <string> match_group)
	{
		/*
			1. find exact match with some high point value (if input is large decrese the sensivity, or it's just one word increase the sensivity)
		*/
		int max_point = 0;
		int  point = 0;
		int sensivity = 0;
		string match;
		for(int g = 0 ; g < match_group.size(); g++)
		{
			match = match_group[g];
			sensivity = calc_lenght_noS(input) / calc_lenght_noS(match);
			
			for(int i = 0 ; i < match.length() ; i++)
			{
				///optional
				/*if(input[i] == match[i])
				{
					point += 7;
				}
				*/
				for(int j = (-1)*(sensivity/2) ; ; j++)
				{
					if(i + j >= 0 && i + j < input.length())
					{
						if(input[i+j] == match[i] && match[i] != ' ')
						{
							point += 10 / (sensivity + 1);///point+=3 * (sensivity+1);
						}
						//cout<<endl<<input[i+j]<<" "<<match[i]<<endl;
					}
					if(j >= sensivity/2)
						 break;
				}
			}
			//cout<<"string 1: "<<input.c_str()<<endl<<"string 2: "<<match.c_str()<<endl<<"point: "<<point<<endl;
			if(point > max_point)
			{
				max_point = point;
			}
			point = 0;
		}
		return max_point;
	}
	state stage_calc(string input)
	{
		// most matching with group should be handled here
		// if can't find matching stay this stage with some error print
		int choice_match = -1, max_max_point = 0;
		int *group_points = new int[lists.groups.size()];
		for(int i = 0 ; i < lists.groups.size(); i++)
		{
			group_points[i] = pointing(input, lists.groups[i]);
			if(max_max_point < group_points[i] && group_points[i] > 10)
			{
				choice_match = i;
				max_max_point = group_points[i];
			}
		}
		if(choice_match == -1)
			return c_state;
		return lists.sstate.at(choice_match);
	}
	
	void show()
	{
		int temp = 0;
		for(int i = 0; ;i++)
		{
			if(pic.c_str()[i] == '`')
				break;
			cout<<pic.c_str()[i];
			if((i+1)%(62) == 0 && i!=0)
			{
				cout<<"\n";
			}
			
		}
	}
	Lists						lists;
	//vector <vector <string>>	lists;
	vector <string>				choices;
	state						c_state;// current_state
	string						story_line;
	string						pic;

};
void game_looser()
{
	string symbols = "@#$%^&*";
	string secret;
	string input;
	int point = 0;
	srand(time(NULL));
	cout<<"Enter the symbols left to right to open the door.\n\n\n";
	usleep(3000000);
	while(1)
	{
		system("clear");
		cout<<"Secret symbols are:\n\n\n";
		for(int i = 0 ; i < 4; i++)
		{
			secret += symbols[rand()%6];
		}

		for(int i = 0 ; i < 4; i++)
		{
			cout<<"\t"<<"[ "<<secret[i]<<" ]";
		}
		cout<<endl;
		usleep(3000000);
		system("clear");
		cout<<"Your turn.\n";
		
		for(int i = 0; i < 4 ;i++)
		{
			cout<<"> ";
			fflush(stdin);
			cin>>input;
			if(input[0] == secret[i])
			{
				point++;
			}
			else
			{
				cout<<"You entered wrong symbole. game will restart automaticlly after 3 sec.\n";
				usleep(3000000);

				break;
			}
		}
		if(point>=4)
		{
			break;
		}
		else
		{
			point = 0;
			secret = "";
		}
	}
}

void print_game(int **game)
{
	cout<<"       1      2      3   \n";
	for(int i = 0 ; i < 3 ; i++)
	{
		cout<<"  -------------------------\n";
		cout<<i+1<<" |";
		for(int j = 0 ; j < 3 ; j++)
		{
			if(game[i][j] == 1)
				cout<<"   "<<"O"<<"   ";
			else if(game[i][j] == 2)
				cout<<"   "<<"X"<<"   ";
			else
				cout<<"       ";
			cout<<"|";
		}
		cout<<"\n";
	}
	cout<<"  -------------------------\n";
}



void game_winner()
{
	sleep(2);
	system("clear");
	// 1 -> o, 2 --> x
	int **game = (int **)calloc(3, sizeof(int *));
	for(int i = 0 ; i < 3 ; i++)
	{
		game[i] = (int *)calloc(3, sizeof(int));
	}
	game[1][1] = 1;
	print_text("You are 'X'. enter cell position. example: 1 2 will Xed the first record second column.\n",300);
	usleep(2000000);
	string first,second;
	cout<<"Your turn.\n";
	print_game(game);
	cout<<"Enter record number.\n";
	cout<<"> ";
	fflush(stdin);
	cin>>first;
	cout<<"Enter column number.\n";
	fflush(stdin);
	cout<<"> ";
	cin>>second;
	if(game[atoi(first.c_str())-1][atoi(second.c_str())-1] == 0 &&  atoi(second.c_str())-1 > -1 && atoi(second.c_str())-1 < 3 && atoi(first.c_str())-1 > -1 && atoi(first.c_str())-1 < 3)
	{
		game[atoi(first.c_str())-1][atoi(second.c_str())-1] = 2;
	}
	else
	{
		cout<<"Your input is not valid.\n";
		game_winner();
		return;
	}
	system("clear");
	print_game(game);
	usleep(2000000);
	print_text("friend: ahon... (Cough)...", 500);
	usleep(2000000);
	system("clear");
	print_game(game);
	usleep(1000000);
	system("clear");
	print_text("Your firend Smiled and gone so far away...\nIsn't that a beautiful way to go out?\nWe have a true winner:\n", 600);
	print_text("\n\n\n\n\n\nY O U!", 10000);
	cout<<endl;
	usleep(5000000);
}
Stage * initial_game_states(int number_of_stages)
{
	Stage *stages = new Stage[number_of_stages];

	stages[0].c_state = stage_0;
	stages[0].story_line = "You are trapped in a dungeon with your friend.\nYou see a barrel. What do you do?\n";
	stages[0].pic = "|                                                            ||                                                            ||                                                            ||                                                            ||                                                            ||                                                            ||                                                            ||                              (.. )                         || _____                        __|__                     (. )|  |---|                        | | |                    _  | |  |***|                         / \\                   */-\\-| |  |---|                        /   \\                  /   \\| |`";
	///stage PIC: 62 char every line size
	stages[0].add_choice("take a look at barrel");
	stages[0].add_choice("look at barrel");
	stages[0].add_choice("look at the barrel");
	stages[0].create_group(stage_1);
	stages[0].add_choice("look at my friend");
	stages[0].add_choice("take a look at my friend");
	stages[0].add_choice("check my friend");
	stages[0].add_choice("look at friend");
	stages[0].create_group(stage_2);
	stages[0].add_choice("move barrel");
	stages[0].add_choice("push barrel");
	stages[0].add_choice("roll over barrel");
	stages[0].add_choice("grab barrel");
	stages[0].add_choice("look at the barrel");
	stages[0].add_choice("move the barrel");
	stages[0].add_choice("push the barrel");
	stages[0].add_choice("roll the over barrel");
	stages[0].add_choice("grab the barrel");
	stages[0].add_choice("move");
	stages[0].add_choice("push");
	stages[0].add_choice("grab");
	stages[0].add_choice("roll over");
	stages[0].create_group(stage_3);
	stages[0].add_choice("look at the dungeon");
	stages[0].add_choice("look dungeon");
	stages[0].add_choice("see dungeon");
	stages[0].add_choice("see the dungeon");
	stages[0].add_choice("check dungeon");
	stages[0].add_choice("check the dungeon");
	stages[0].create_group(stage_4);
	///need to be tested confilict with stage_2
	stages[0].add_choice("stay with friend");
	stages[0].add_choice("sit next to my friend");
	stages[0].add_choice("sit around my friend");
	stages[0].add_choice("stay");
	stages[0].create_group(stage_14);
	////
	stages[3].c_state = stage_3;
	stages[3].story_line = "The barrel rolls aside and you find a secret tunnel\nWhat do you do?\n";
	stages[3].pic = "|                                                            ||                                                            ||                                                            ||                                                            ||                                                            ||                                                            ||                                                            ||  (.. )                                                     ||  __|__        ___                                      (. )|   | | |       |---|                                       | |    / \\        |***|                                  */-\\-| |   /   \\       |---|                                  /   \\| |`";
	stages[3].add_choice("enter tunnel");
	stages[3].add_choice("go to tunnel");
	stages[3].add_choice("leave my friend");
	stages[3].add_choice("leave the dungeon");
	stages[3].add_choice("move to the tunnel");
	stages[3].add_choice("go to the tunnel");
	stages[3].add_choice("enter the tunnel");
	stages[3].add_choice("go");
	stages[3].add_choice("enter");
	stages[3].add_choice("escape");
	stages[3].add_choice("leave");
	stages[3].create_group(stage_5);
	stages[3].add_choice("stay with friend");
	stages[3].add_choice("sit next to my friend");
	stages[3].add_choice("sit around my friend");
	stages[3].add_choice("stay");
	stages[3].add_choice("sit");
	stages[3].create_group(stage_14);
	////
	stages[5].c_state = stage_5;
	stages[5].story_line = "You are in the tunnel. You start to escape but your friend is too weak to go with you.\nYou have to go alone.\nhe hand you a note.\nWhat do you do?\n";
	stages[5].pic = "`";
	stages[5].add_choice("read the note");
	stages[5].add_choice("read");
	stages[5].add_choice("look at note");
	stages[5].create_group(stage_6);// go there and its a trap to say leave
	stages[5].add_choice("leave");
	stages[5].add_choice("exit");
	stages[5].add_choice("go");
	stages[5].add_choice("move");
	stages[5].add_choice("move on");
	stages[5].add_choice("leave it");
	stages[5].add_choice("escape");
	stages[5].add_choice("enter tunnel");
	stages[5].add_choice("go to tunnel");
	stages[5].add_choice("leave my friend");
	stages[5].add_choice("leave the dungeon");
	stages[5].add_choice("move to the tunnel");
	stages[5].add_choice("go to the tunnel");
	stages[5].add_choice("enter the tunnel");
	stages[5].create_group(stage_7);/// jump
	/////
	stages[7].c_state = stage_7;
	stages[7].story_line = "You crawl through the tunnel and the tunnel leads you to big pits. What do you do?\n";
	stages[7].pic = "                                                                                           (.. )                                                         __|__                                                         | | |                                                          / \\                                                         _/___\\__()___(-- )____-___)_)%%)__                           |                                                             |                                                             |                                                             |                                                             |                                                             |                                                             |                                  )___)$_#__$)________       |                                                      |      |                                                      |      |                                                      |^^^^^^|                                  `";
	stages[7].add_choice("jump");
	stages[7].add_choice("jump above the pits");
	stages[7].add_choice("run and jump");
	stages[7].add_choice("long jump");
	stages[7].add_choice("take a long jump");
	stages[7].create_group(stage_8);
	/////
	stages[8].c_state = stage_8;
	stages[8].story_line = "You reach to a strange door with some symboles on it that changes after a while.\n";
	////play game
	/*
						^@#%^*

			[ _ ]	[ _ ]	[ _ ]	[ _ ]
	

		Enter what did you just saw with same ordinary
		after game we should move to stage_9
	*/
	stages[6].c_state = stage_6;
	stages[6].story_line = "It's too dark to read the note. what do you do?\n";
	stages[6].pic = "                ~~~-----~~~---~~~~~~~~~~~~                                   /                         /                                  /                         /                                  /    &@#%@#$%@^&@##%      /                                  /   #$@%#^#@$^@%#@%@#%    /                                  /                         /                                  /                         /                                  /                         /                                  /                         /                                   -~--~~~~~~~~~~---~~~~~~--                             `";
	stages[6].add_choice("leave");
	stages[6].add_choice("exit");
	stages[6].add_choice("go");
	stages[6].add_choice("move");
	stages[6].add_choice("move on");
	stages[6].add_choice("leave it");
	stages[6].add_choice("escape");
	stages[6].add_choice("enter tunnel");
	stages[6].add_choice("go to tunnel");
	stages[6].add_choice("leave my friend");
	stages[6].add_choice("leave the dungeon");
	stages[6].add_choice("move to the tunnel");
	stages[6].add_choice("go to the tunnel");
	stages[6].add_choice("enter the tunnel");
	stages[6].create_group(stage_7);

	///////
	stages[9].c_state = stage_9;
	stages[9].story_line = "Door opend and you walk to pass a dark dolon. then you reach a 'room' with opened door to a beach.\nWhat do you do?\n";
	stages[9].pic = "/////////////////////////////////////////////////////////////|/////////////////////////////////////////////////////////////|////////////////////===========//////////////////////////////||-----------------||          ||-----------------------------||-----------------||          ||----=------------------------||----=------------||          ||-----------------------------||-----------------||          ||-------------=-------=---=---||-----------------||          ||------=------(.. )=----------||---------=-------||          ||-------------__|__---=--=----||-----------------||          ||-------=---- |-|-|-----------||-----=-----------||          ||---=----------/-\\------------||--------------=--||          ||-------------/---\\-----------|//////////////////// / / / / / /////////////////////////////////////////////////    /   / /  /   ////////////////////////////////////////                          ////////////////////////////////                                ///////////////////////////////////////////////////////////////////////////////////`";
	stages[9].add_choice("go");
	stages[9].add_choice("enter door");
	stages[9].add_choice("leave room");
	stages[9].add_choice("move to the door");
	stages[9].add_choice("exit room");
	stages[9].add_choice("exit");
	stages[9].add_choice("leave");
	stages[9].add_choice("go to the beach");
	stages[9].add_choice("walk");
	stages[9].add_choice("walk through door");
	stages[9].add_choice("move to beach");
	stages[9].add_choice("move to the beach");
	stages[9].create_group(stage_10);
	//////
	stages[10].c_state = stage_10;
	stages[10].story_line = "In beach you see a boat in the water.\nWhat do you do?\n";
	stages[10].pic = "    ^       /|                                                 v^  v     / |                 ^    v   ^v ^                            /  |                    ^                                    /   |                                                ~~~-----/    |~~~~~~~~-~--~~~~~~~~~~~-~-----~~~~~~~-------~~~~       /_____|                                                             |  .  .                                           ____________|__^__^_            \\  /                          \\     -    ---   - /       ----)()()(---                       \\_-_____ __      /      /     |  |    \\                                                     ||                          ~~~~~~~~~~~~~~~~~~~~~~~~~~~---~~~~||~~~~~~-----------~~~~~~~~~                                  ||                              (   )           *&!@#         ||                              __|__          (stone)        ||          -----               | | |         (ano stone)     ||         /     \\                |                           ||                               / \\                          ||                              /   \\                         ||                          `";
	stages[10].add_choice("get on the boat");
	stages[10].add_choice("swim to boat");
	stages[10].add_choice("ride");
	stages[10].add_choice("swim");
	stages[10].add_choice("ask");
	stages[10].add_choice("ask for help");
	stages[10].add_choice("cry");
	stages[10].add_choice("make noises");
	stages[10].add_choice("make noise");
	stages[10].add_choice("raise hand");
	stages[10].add_choice("raise my hand");
	stages[10].add_choice("jump to water");
	stages[10].create_group(stage_11);
	///
	stages[11].c_state = stage_11;
	stages[11].story_line = "Congratz! You are just \"another winner\" that heading to a new world.\nDo you want to play again?\n";
	stages[11].pic = "          _______________________                                       | /|                   |                                      |/ |                   |                                      /  |    New World      |                                     /   |                   |                                    /    |___________________|                                   /     |                                                      /      |                                                     /       |  (   )                                          |--/        |--__|__-------|                                  | /---------|  | | |       |                                  |           |--------      |                                  |           /       /      |                                  |__________________________|                                 `";
	stages[11].add_choice("yeah");
	stages[11].add_choice("yes");
	stages[11].add_choice("i love to");
	stages[11].add_choice("i want to");
	stages[11].add_choice("i want");
	stages[11].add_choice("play");
	stages[11].add_choice("play again");
	stages[11].add_choice("again");
	stages[11].create_group(stage_0);
	///
	stages[1].c_state = stage_1;
	stages[1].story_line = "It's just a barrel. but there something behind it. (type: > skip)\n";
	stages[1].add_choice("get it");
	stages[1].add_choice("ahan");
	stages[1].add_choice("skip");
	stages[1].create_group(stage_0);///always go back
	////
	stages[2].c_state = stage_2;
	stages[2].story_line = "Your friend is too weak and sick. (type: > skip)\n";
	stages[2].add_choice("get it");
	stages[2].add_choice("ahan");
	stages[2].add_choice("skip");
	stages[2].create_group(stage_0);///always go back
	/////
	stages[4].c_state = stage_4;
	stages[4].story_line = "There is nothing in there except a barrel. (type: > skip)\n";
	stages[4].add_choice("get it");
	stages[4].add_choice("ahan");
	stages[4].add_choice("skip");
	stages[4].create_group(stage_0);///always go back

	////
	stages[14].c_state = stage_14;
	stages[14].story_line = "Your friend hand you a note.\nWhat do you do?\n";
	stages[14].pic = "`";
	stages[14].add_choice("read");
	stages[14].add_choice("read the note");
	stages[14].add_choice("use light");
	stages[14].add_choice("see the note");
	stages[14].add_choice("check the note");
	stages[14].add_choice("check");
	stages[14].add_choice("see");
	stages[14].create_group(stage_15);
	/////

	stages[15].c_state = stage_15;
	stages[15].story_line = "The note says, \"Don't leave me here.\" Do you leave your friend or stay?\n\n\n";
	stages[15].pic = "                  ~~~-----~~~---~~~~~~~~~~~~                                   /                         /                                  /                         /                                  /   Don't LEAVE ME here   /                                  /                         /                                  /                         /                                  /                         /                                  /                         /                                  /                         /                                   -~--~~~~~~~~~~---~~~~~~--                           `";
	stages[15].add_choice("stay");
	stages[15].add_choice("stay with my friend");
	stages[15].create_group(stage_16);

	////
	stages[16].c_state = stage_16;
	stages[16].story_line = "Your friend invite you to a game.\nDo you want to play with your friend?\n\n";
	stages[16].add_choice("yes");
	stages[16].add_choice("ok");
	stages[16].add_choice("play");
	stages[16].add_choice("i want to");
	stages[16].add_choice("want to");
	stages[16].add_choice("i want to play");
	stages[16].create_group(stage_17);

	//////
	stages[17].c_state = stage_17;
	stages[17].story_line = "A hand made \"tic tac toe\" game.\n";
	return stages;
}


int main()
{

	/*
		for every state we need stage instant. ex. state_0 - state_9 we need 10 state

		+ flush stdin before cins
	*/
	print_text("A game by mohammad hossein asghari",500);
	sleep(2);
	int number_of_stages = 19;
	state current_state = stage_0;
	state next_state;
	Stage * stages = initial_game_states(number_of_stages);
	string input;
	Stage stage;
	stage = stages[0];
	while(1)
	{
		system("clear");
		cout<<endl<<"stage is: "<< (int)stage.c_state<<endl;
		print_text(stage.story_line, 300);
		stage.show();
		cout<<"\n\n> ";
		fflush(stdin);
		getline(cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		system("clear");
		next_state = stage.stage_calc(input);
		stage = stages[next_state];
		if(stage.c_state == 8)
		{
			print_text(stage.story_line, 300);
			game_looser();
			stage = stages[9];
		}
		if(stage.c_state == 17)
		{
			print_text(stage.story_line, 300);
			game_winner();
			break;
		}
		
	}

	
}
