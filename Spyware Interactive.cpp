#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <random>
#include <Windows.h>

using namespace std;

int class_choice = 0; // 1 is knight, 2 is mage 
int player_atk = 20;
int special_point_max = 100;
int turns_passed = 0;
int special_point;
int turn_special_point = 100; //This is so special points don't get used up when the player chooses to double down or use a spell then fails the next input - Nate
int player_sanity = 100;
int player_def; // 0 is unarmored; 1 is starting armor; 2 is better armor -Ruby
int attack; //whether the player is attack with spells or weapons; 1 is Weapons; 2 is Spells -Ruby
int attack_choice = 0; //used when choosing an enemy to attack
int weapon_choice = 0;
int spell_choice = 0;
int crit_chance = 0;
int double_down_choice;
int player_blind_turn = 0;
long long int player_hp = 100; //long long makes it so the amount removed can be large, the warning that is prompting this change is from Metal Pipe's Damage -Ruby
char proceed = ' '; //have the = ' ' removes an error where it is saying get(proceed) is not an acceptable input -Ruby
bool double_down = false;
bool special_point_upgrade = false;
bool battle_lost = false;
bool player_turn = true;
list<string> player_status_condition;
list<string>::iterator init_player_status_condition;
long long player_status_size = player_status_condition.size(); //How many values are in the list -Ruby
string final_string = "placeholder"; //Used at the end to start second pipe battle - Nate

//Weapons
//The battle system needed a lot of changes to work with multiple weapons, but adding a variable for your fist is pointless, we don't have a break-your-hand mechanic. - Nate
//Numbers are changed to be consistent with what the player enters during battle. - Nate
bool weapon2 = false; //arming sword (knight) or bo staff (mage) -Ruby
bool weapon3 = false; //halberd (knight) or quarterstaff (mage) -Ruby
bool weapon4 = false; //giant hammer (knight) or holy blade (mage) -Ruby

//Spells
bool light = false; //light spell -Ruby
bool magic_missile = false; //magic missile -Ruby
bool freeze = false; //freeze -Ruby
bool fireball = false; //fireball spell -Ruby

int tavern_choice = 0;
int bridge_choice = 0;
int spring_choice = 0;

int enemy1_hp = 0;
int enemy2_hp = 0;
int enemy3_hp = 0;

int enemy1_blind_turn = 0;
int enemy2_blind_turn = 0;
int enemy3_blind_turn = 0;

//0 is dead, 1 is parasite, 2 is infected, 3 is bear/juggernaut, 4 is gravemind, 1738 is metal pipe
//Parasite has 25hp, infected has 75hp, juggernaut has 165hp, metal pipe has 1738hp
int enemy1 = 0;
int enemy2 = 0;
int enemy3 = 0;

bool enemy1_blind = false;
bool enemy2_blind = false;
bool enemy3_blind = false;
bool froze_metal_pipe = false;

int loop = 0; //exists to stop infinite loops when something breaks, we shouldn't need it anymore. - Nate

//Functions for the ACSII art, I should have implemented this a while ago but we didn't have time - Nate
void game_over_ascii() {
	cout << "\n _____    ___   ___  ___  _____    _____   _   _   _____  ______\n|  __ \\  / _ \\  |  \\/  | |  ___|  |  _  | | | | | |  ___| | ___ \\\n| |  \\/ / /_\\ \\ | .  . | | |__    | | | | | | | | | |__   | |_/ /\n| | __  |  _  | | |\\/| | |  __|   | | | | | | | | |  __|  |    /\n| |_\\ \\ | | | | | |  | | | |___   \\ \\_/ / \\ \\_/ / | |___  | |\\ \\\n \\____/ \\_| |_/ \\_|  |_/ \\____/    \\___/   \\___/  \\____/  \\_| \\_|\n";
}

void victory_ascii() {
	cout << "\n:::     :::      :::::::::::       ::::::::       :::::::::::       ::::::::       :::::::::       :::   :::      :::\n:+:     :+:          :+:          :+:    :+:          :+:          :+:    :+:      :+:    :+:      :+:   :+:      :+:\n+:+     +:+          +:+          +:+                 +:+          +:+    +:+      +:+    +:+       +:+ +:+       +:+\n+#+     +:+          +#+          +#+                 +#+          +#+    +:+      +#++:++#:         +#++:        +#+\n +#+   +#+           +#+          +#+                 +#+          +#+    +#+      +#+    +#+         +#+         +#+\n  #+#+#+#            #+#          #+#    #+#          #+#          #+#    #+#      #+#    #+#         #+#             \n    ###          ###########       ########           ###           ########       ###    ###         ###         ###\n";
}

void team_logo_ascii() {
	cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n+++++++++++++++++++++++++++++++.                                    .+++++++++++++++++++++++++++++++\n++++++++++++++++++++++++++++:::.                                    .:::++++++++++++++++++++++++++++\n++++++++++++++++++++++++++++                                            ++++++++++++++++++++++++++++\n+++++++++++++++++++++++++                                                  +++++++++++++++++++++++++\n+++++++++++++++++++++++++                                                  +++++++++++++++++++++++++\n++++++++++++++++++++++                                                        ++++++++++++++++++++++\n++++++++++++++++++++++                  ....................                  ++++++++++++++++++++++\n++++++++++++++++++++++                  :++++++++++++++++++:                  ++++++++++++++++++++++\n++++++++++++++++++++++               -++++++++++++++++++++++++-               ++++++++++++++++++++++\n++++++++++++++++++++++               -++++++++++++++++++++++++-               ++++++++++++++++++++++\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ++++++++++++++++++++++\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ++++++++++++++++++++++\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ++++++++++++++++++++++\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ++++++++++++++++++++++\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ++++++++++++++++++++++\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ++++++++++++*#########\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ++++++++++++*#########\n++++++++++++++++++++++            =++++++++++++++++++++++++++++++=            ######################\n++++++++++++++++++++++            =++++++++++++++++++************+            ######################\n++++++++++++++++++++++            =++++++++++++++++++############*            ######################\n++++++++++++++++++++++            *##############################*            ######################\n++++++++++++++++++++++            *##############################*            ######################\n++++++++++++#######                                                              ###################\n++++++++++++#######                                                              ###################\n###############*                                                                    *###############\n############*==-                                                                    -==*############\n############=                                                                          =############\n############=                                                                          =############\n############=                                                                          =############\n############=                                  ######                                  =############\n############=                                  ######                                  =############\n############=                              .############.                              =############\n############=                              .############.                              =############\n############=                              .############.                              =############\n############=                                  ######                                  =############\n############=                                  ######                                  =############\n############=                                  ######                                  =############\n############=                              .---######---.                              =############\n############=                              .############.                              =############\n############=                              .############.                              =############\n############=                              .############.                              =############\n############=                           :##################-                           =############\n############=                           :##################-                           =############\n############=                                                                          =############\n############=                                                                          =############\n############=                                                                          =############\n############=                                                                          =############\n############=                                                                          =############\n###############*                                                                    *###############\n################---                                                              ---################\n###################                                                              ###################\n####################################################################################################\n####################################################################################################\n";
}

void parasite_ascii() {
	cout << "\n                                        =================\n                                  =============================\n                                  =======               =======\n                               ====                           ====\n                               ====                           ====\n                            ====                                 ====\n                            ====                                 ====\n                            ====                                 ====\n                         ======                                  =======\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                            ====     -------         -------     ====\n                            ====     -------         -------     ====\n                            ====     -------         -------     ====\n                               ====                           ====\n                               ====                           ====\n                               ==========               =============\n                               ==========               =============\n                            ====     ==========================  =======\n                            ====  ============================================\n                            ====  ====  ====   ===   ====  =======      ======\n                         ===   ====     ====   ===   ====     =======      ===\n                         ===   ====     ====   ===   ====     =======      ===\n                      ======   ====     ====   ======   ====     ====      ===\n                   ================     ====   ======   ====     =======   ===\n                   ======   ====        ====      ===   ====         ===   ===\n                   ===      ====        ====      ===   ====         ===      ====\n                   ===      ====        ====      ===   ====         ===      ====\n               =======      ====        ====      ===   ====         ======   ====\n               =======      ====        ====      ===   ====         ======   ====\n               ====         ====        =======   ===   =======         ===\n                ======      =======      ======   =============         ===\n                   ===         ====         ===      ====  ====\n";
}

void infected_ascii() {
	cout << "\n                            ===============\n                         ======@@@@=========\n                         ===   @@@@     ====\n                         ===         @@@@======\n                         ===         @@@@======\n                         ===   @@@@         ===\n                         ===   @@@@         ===\n                            ==========      =============\n                            =======================================\n                                     ==========#########=============\n                            ================###         ###=============\n                            ================###         ###=============\n                         ===================###---   ---###================\n                      ======================###---   ---###==================\n                      ======================###         ###====  =============\n                   =============     ==========#########====        ==========\n                   =============     =======================         =========\n               ==========            =======================         =============\n               ==========            =======================         =============\n               =======               =======================         =============\n            ==========###            =======================         =============\n            ==========###            =======================            ===   ===\n            ==========################################======            ===   ===\n            ==========#################################=====            ===   ===\n          @@@===@@@===##################################=====           ===   ===\n          @@@===@@@===###################################======         ===   ===\n                      ###         ==========         ==========         ===   ===\n                      ###         ==========         ==========         ===   ===\n                                  ==========            =======\n                                  =======               =======\n                                  =======               =======\n                                  =======               ==========\n                                  =======               ==========\n                                  =======                  =======\n                               ==========                  =======\n                               ==========                  =======\n                               ==========                  =======\n                               ==========                  =======\n                            =============                  ==========\n                         ================                  =============\n                         ================                  =============\n";
}

void gravemind_ascii() {
	cout << "\n                                                        #######\n                                                        #######\n                                                     ##########\n                                                     ##########\n                                                     #######\n   #######                                        #######\n   #######                                        #######\n   ##########                                  ##########                                     ######\n   #############                            #############                                  #########\n      ##########                            #########                                     ##########\n         ##########                         #########                                  #############\n         ##########                         #########                                  #############\n            #######                     ##########                               ################\n            #######                     ##########                               ################\n            ##########            ################################            #############\n            ##########      #########################################   ##################\n               #######      #########################################   ################\n                   ########################*=========#############################\n                   ########################*=========#############################\n                      ##################*===         ===*#########################\n                   #####################*===@@@   @@@===*###########################\n                   #####################*==+@@@   @@@===*############################\n                   #####################*===         ===*############################\n                   #####################*===         ===*############################\n               #########################*===   @@@   ===*##################################\n               #########################*===   @@@   ===*##################################\n   ########################################*=========############################################\n##################################****##****======*************#####################################\n##################################+==*##*=========###=========*#####################################\n#######     ###################===*#####*======###############*==+######################\n#######     ###################===*#####*======###############*==+######################\n###            ###################################################################\n###            ###################################################################\n               ################################=========*#####*==+############\n                ###############+++*#####*+++###=========*#####*==+############\n                   ############===*#####*===###=========*#####*==+#########\n                   #####################################################\n                   #####################################################\n               ################===*#####*===============*#####*==+############\n   ############################*++*#####*======+++======*#####*++*###############\n   ###################   ###############*======###======*#########################\n###################         ############*======   ======*#########         ##########\n###################         ############*======   ======*#########         ##########\n##########                        ####  =======   =======                     #############\n##########                        ####  =======   =======                     #############\n                                        =======   =======                        ################\n                                        =======   =======                        ###################\n                                        =======   =======                           ################\n";
}

int random_crit(int low, int high) {
	random_device rd;
	uniform_int_distribution<int> dist(low, high);
	return dist(rd);
}

void player_status() {
	if (spell_choice == 1) { //when the player is blinded -Ruby
		player_turn = false;
	}
}

void blind_turn() {
	if (enemy1_blind == true) {
		if (enemy1_blind_turn >= 3) {
			enemy1_blind = false;
			enemy1_blind_turn = 0;
			cout << "Enemy 1 has recovered from blindness!" << endl;
		}
		else {
			enemy1_blind_turn += 1;
			cout << "Enemy1 has been blinded for " << enemy1_blind_turn << " turns." << endl;
		}
	}
	if (enemy2_blind == true) {
		if (enemy2_blind_turn >= 3) {
			enemy2_blind = false;
			enemy2_blind_turn = 0;
			cout << "Enemy 2 has recovered from blindness!" << endl;
		}
		else {
			enemy2_blind_turn += 0;
			cout << "Enemy2 has been blinded for " << enemy2_blind_turn << " turns." << endl;
		}
	}
	if (enemy3_blind == true) {
		if (enemy3_blind_turn >= 3) {
			enemy3_blind = false;
			enemy3_blind_turn = 0;
			cout << "Enemy 3 has recovered from blindness!" << endl;
		}
		else {
			enemy3_blind_turn += 3;
			cout << "Enemy3 has been blinded for " << enemy3_blind_turn << " turns." << endl;
		}
	}
}

void enemy_turn(int current_enemy) {
	if (current_enemy == 1) {
		cout << "\nEnemy parasite attacks!\n";
		if (enemy1_blind == true) {
			player_hp -= 0;
		}
		else {
			player_hp -= 5;
		}
		player_sanity -= 5;
	}
	else if (current_enemy == 2) {
		cout << "\nEnemy infected attacks!\n";
		if (enemy2_blind == true) {
			player_hp -= 0;
		}
		else {
			player_hp -= 10;
		}
		player_sanity -= 10;
	}
	else if (current_enemy == 3) {
		cout << "\nEnemy Juggernaut attacks!\n";
		if (enemy3_blind == true) {
			player_hp -= 0;
		}
		else {
			player_hp -= 15;
		}
		player_sanity -= 10; //The old value was 25, a bit extreme for a boss fight that's supposed to take many turns. - Nate
	}
	else if (current_enemy == 4) {
		cout << "\nThe writhing mass shoots a crackling pain into your head...\n";
		player_hp -= 35;
		player_sanity -= 20;
	}
	else if (current_enemy == 1738) {
		//These special interactions are a cool idea, but since they're in a place that wouldn't work,
		//and they only exist for a fight most people won't see, that they'll lose anyway, they're commented out for now.
		//I have more important things to fix - Nate
		//It will be moved to the battle function later -Ruby

		cout << "\nThe metal pipe breaks your kneecaps!\n";
		player_hp -= 194530298001;
		player_sanity -= 420;
	}
}

void battle() {
	turns_passed = 0;
	while (true) {
		turn_special_point = special_point; //Restores SP if something goes wrong between using double down or a spell
		if (player_hp <= 0 && enemy1 == 1738) {
			cout << "\n'but the Lord laughs at the wicked, for he knows their day is coming.'\n";
			cin.ignore();
			cin.get(proceed); //continues by just pressing 'enter' -Ruby
			battle_lost = true;
			exit(0);
		}
		else if (player_hp <= 0) {
			cout << "\nYour body falls over, cold and lifeless. A perfect vessel for the parasite to enact its primal will...\n";
			Sleep(5000);
			game_over_ascii();
			cout << "\nThank you for playing the second demo! Feel free to play it again and make different choices.\nPlease be sure to fill out the QA form and let us know of any issues!\n";
			cin.get(proceed); //I remembered that the exe would exit as soon as it ended, so we needed these. - Nate
			cin.ignore();
			battle_lost = true;
			exit(0);
		}
		if (enemy1 == 0 && enemy2 == 0 && enemy3 == 0) {
			player_hp = 100;
			if (class_choice == 2) {
				player_hp = 150;
			}
			enemy1_blind = false;
			enemy2_blind = false;
			enemy3_blind = false;

			//If and first else if will raise SP when you have less than max but not more than the max -25, else will raise SP to the max when it is at max -24 or more.
			//The else will never run with how we currently use SP, but we might change values and I'd rather not have to add it again later -Nate 
			if (special_point_upgrade == false && special_point <= 75) {
				special_point += 25;
			}
			else if (special_point_upgrade == true && special_point <= 175) {
				special_point += 25;
			}
			else {
				special_point = special_point_max;
			}

			victory_ascii();
			cout << "\nHit ENTER to continue:\n";
			cin.ignore();
			cin.get(proceed);
			break;
		}

		blind_turn();

		cout << "\nCurrent HP: " << player_hp << endl;
		cout << "Current SP: " << special_point << endl;
		if (class_choice == 2) {
			cout << "\nOpen weapon selection or spell selection?\nType the number and press ENTER.\n1. Weapons\n2. Spells\n";
			cin >> attack;
		}
		else {
			attack = 1;
		}

		//bool for_valid_weapon_option = true; //This is for the while loop below; false will disable the loop and allow the player to progess -Ruby
		//The whole for_valid_weapon_option thing was pointless, I appreciate the effort but there are far less bugs when you just restart the turn - Nate

		if (attack == 1) { //Weapons -Ruby
			cout << "\nEnter a number to choose a weapon.\n1.Fist";
			if (weapon2 == true) {
				cout << "\n2.";
				if (class_choice == 1) {
					cout << "Arming Sword";
				}
				else if (class_choice == 2) {
					cout << "Bo Staff";
				}
			}

			if (weapon3 == true) {
				cout << "\n3.";
				if (class_choice == 1) {
					cout << "Halberd";
				}
				else if (class_choice == 2) {
					cout << "Quarterstaff";
				}
			}

			if (weapon4 == true) {
				cout << "\n4.";
				if (class_choice == 1) {
					cout << "Giant Hammer";
				}
				else if (class_choice == 2) {
					cout << "Energy Blade";
				}
			}
			std::cout << "\n";
			cin >> weapon_choice;
			if (weapon_choice == 1) {
				crit_chance = random_crit(1, 4);
				if (crit_chance == 1) {
					cout << "\nYou feel a little lucky...\n";
					player_atk = 12;
				}
				else {
					player_atk = 6;
				}
			}
			else if (weapon_choice == 2) {
				crit_chance = random_crit(1, 4);
				if (crit_chance == 1) {
					player_atk = 30;
					cout << "\nYou feel a little lucky...\n";
				}
				else {
					player_atk = 15;
				}

			}
			else if (weapon_choice == 3) {
				crit_chance = random_crit(1, 4);
				if (crit_chance == 1) {
					player_atk = 50;
					cout << "\nYou feel a little lucky...\n";
				}
				else {
					player_atk = 25;
				}
			}
			else { //resets the turn
				continue;
			}

			if (class_choice == 1 && special_point >= 25) {
				cout << "\nUse 25 SP to Double Down?\n1. Yes \n2. No\n";
				cin >> double_down_choice;

				if (double_down_choice == 1) {
					player_atk = player_atk * 2;
					special_point -= 25;
				}
				else {
					player_atk = player_atk;
				}
			}
		}
		else if (attack == 2) { //Spells -Ruby
			cout << "\nWhich spell would you like to use?";
			if (light == true) {
				cout << "\n1. Light 25 SP";
			}
			if (magic_missile == true) {
				cout << "\n2. Magic Missile 25 SP";
			}
			if (freeze == true) {
				cout << "\n3. Freeze";
			}
			if (fireball == true) {
				cout << "\n4. Fireball";
			}
			std::cout << "\n";

			cin >> spell_choice;

		}
		else {
			special_point = turn_special_point;
			continue;
		}

		cout << "\nAttack which enemy?\n";
		if (enemy1 != 0) { //These ifs display enemies currently on the field and their HP - Nate
			cout << "Enemy 1: " << enemy1_hp << "HP\n";
		}
		if (enemy2 != 0) {
			cout << "Enemy 2: " << enemy2_hp << "HP\n";
		}
		if (enemy3 != 0) {
			cout << "Enemy 3: " << enemy3_hp << "HP\n";
		}

		cin >> attack_choice; //For choosing which enemy to attack - Nate

		if (attack == 1) { //This code only runs when using a weapon or magic missile, the other spells can't fit this same structure of removing hp based on attack - Nate
			if (attack_choice == 1 && enemy1 != 0) {
				cout << "\nEnemy 1 takes " << player_atk << " damage!\n";
				enemy1_hp -= player_atk;
				if (enemy1_hp <= 0) {
					enemy1 = 0;
					cout << "\nEnemy 1 has been defeated!\n";
				}
			}
			else if (attack_choice == 2 && enemy2 != 0) {
				cout << "\nEnemy 2 takes " << player_atk << " damage!\n";
				enemy2_hp -= player_atk;
				if (enemy2_hp <= 0) {
					enemy2 = 0;
					cout << "\nEnemy 2 has been defeated!\n";
				}
			}
			else if (attack_choice == 3 && enemy3 != 0) {
				cout << "\nEnemy 3 takes " << player_atk << " damage!\n";
				enemy3_hp -= player_atk;
				if (enemy3_hp <= 0) {
					enemy3 = 0;
					cout << "\nEnemy 3 has been defeated!\n";
				}
			}
			else { //resets the turn, can be exploited to force a crit but it's fine - Nate
				special_point = turn_special_point;
				continue;
			}

		}

		else if (attack == 2) {
			if (enemy1 == 1738) {
				cout << "Test\n";
				if (spell_choice == 1 && light == true && special_point >= 25) { //Light Spell -Ruby
					cout << "The pipe reflected your light and blinded you instead!\n";
					enemy1_blind = false;
					player_status_condition.push_front("Blind"); //adds the blind condition to the player -Ruby
					player_status();
				}
				else if (spell_choice == 3) { //Freeze Spell -Ruby
					enemy1_blind = true;
					if (enemy1_blind == true) {
						player_sanity -= 42; //The answer to life, the universe, and everything in Hitchhiker's Guide to the Galaxy -Ruby
					}
				}
				else if (spell_choice == 4) {
					enemy1_hp = 1;
				}
				else {
					player_atk = 0;
				}
			}

			if (spell_choice == 1 && light == true && special_point >= 10) { //Light Spell -Ruby 
				special_point -= 10;
				int blind_chance = random_crit(1, 4);
				if (blind_chance == 1 && weapon3 == false) {
					if (attack_choice == 1) {
						enemy1_blind = true;
					}
					if (attack_choice == 2) {
						enemy2_blind = true;
					}
					if (attack_choice == 3) {
						enemy3_blind = true;
					}
					cout << "The enemy is blinded\n";
				}
				else if (weapon3 == true && blind_chance <= 2) {
					if (attack_choice == 1) {
						enemy1_blind = true;
					}
					if (attack_choice == 2) {
						enemy2_blind = true;
					}
					if (attack_choice == 3) {
						enemy3_blind = true;
					}
					cout << "The enemy is blinded\n";
				}
				else {
					cout << "The enemy wasn't blinded\n";
				}
			}
			else if (spell_choice == 2 && special_point >= 25) { //Magic Missile -Ruby
				special_point -= 25;
				if (weapon3 == false) {
					player_atk = 35;
				}
				else if (weapon3 == true) {
					special_point -= 15;
					player_atk = 55;
				}

				if (attack_choice == 1) {
					enemy1_hp -= player_atk;
				}
				else if (attack_choice == 2) {
					enemy2_hp -= player_atk;
				}
				else if (attack_choice == 3) {
					enemy3_hp -= player_atk;
				}
			}
			else if (spell_choice == 3 && fireball == true) {
				special_point -= 50;
				player_atk = 40;
				enemy1_hp -= player_atk;
				enemy2_hp -= player_atk;
				enemy3_hp -= player_atk;
				cout << "You fire a large cone of flames. All enemies take 40 damage" << endl;
			}
			else {
				special_point = turn_special_point;
				continue;
			}
		}

		else {
			continue;
		}

		//enemy turns start here
		enemy_turn(enemy1);
		enemy_turn(enemy2);
		enemy_turn(enemy3);
		turns_passed += 1;
	}
}

void door_kicked() {
	cout << "\nWorking up the impaired judgment caused by your three-day bender, you effortlessly kick down the door and face the demonic door-puncher.\n" << endl;
	cout << "\nIt was a horrific sight indeed. The man- no, the beast before you was a man, but its clammy flesh has been contorted in a manner where its head is dangling to the side,\n";
	cout << "\na face of anguish and suffering frozen in the exact moment of its initial form being violated.\n";
	cout << "\nBurrowed in its chest, a giant squirming parasite, with its red tendrils sticking out and aimlessly feeling everything it can.\n";
	cout << "\nPress ENTER to continue.\n" << endl;
	cin.ignore();
	cin.get(proceed);
	infected_ascii();
	cout << "Upon sighting you, it immediately charges at you, thirsting for another body to add to the fold." << endl;
	cout << "\nGet ready to fight! Press ENTER to continue.\n" << endl;
	cin.get(proceed);
	enemy1 = 2;
	enemy1_hp = 50;
	enemy2 = 2;
	enemy2_hp = 50;
	battle();
	cout << "Your bones ache and your brain is burning, but at least you're still alive.";
	cout << "\nGingerly stepping over the now motionless husks, you walk outside to find the entire town in ruin.";
	cout << "\nKnowing fully well that you won't last in the middle of a town full of these zombie-like freaks, you run into the forest...";
}

void backdoor() {
	cout << "Deciding that perhaps confronting a horror beyond your comprehension head-on isn't smart, you carefully sneak into the back of the bar," << endl;
	cout << "hoping that you can easily get out of this mess. You're stopped dead in your tracks by two fleshy, pulsating parasites about the size of your head.\n";
	cout << "Press ENTER to continue.";
	cin.ignore();
	cin.get(proceed);
	parasite_ascii();
	cout << "\nGet ready to fight! Press ENTER to continue.\n" << endl;
	cin.get(proceed);
	enemy1 = 1;
	enemy1_hp = 25;
	enemy2 = 1;
	enemy2_hp = 25;
	battle();
	cout << "That was easy, you thought. You leave silently through the back, and slip away into the forest, unsure of what has become of everyone else.";

}

void coward() {
	cout << "Unsure of the idea that you wish to leave your only shelter, you hide behind the bar counter, praying that the incessant knocking stops." << endl;
	cout << "The knocking ends. For a brief moment, you stop to consider if it was only a drunkard, and the idea almost puts you at ease.\n";
	cout << "Maybe you're still a little woozy and just imagining stuff...\n";
	cout << "\nPress ENTER to continue.\n" << endl;
	cin.ignore();
	cin.get(proceed);
	cout << "Your hopes for salvation are dashed as the door explodes into countless jagged bits of wood, and the assailant enters, its feet stomping against the tile." << endl;
	cout << "You hold your breath behind the counter as the thing slinks about the place. The stench of rot permeates the air as it gets ever so closer to the counter...\n";
	cout << "\nPress ENTER to continue.\n" << endl;
	cin.get(proceed);
	cout << "Its face is contorted and frozen in a moment of sheer pain and anguish before its initial death, and burrowed inside its chest is a giant parasite." << endl;
	infected_ascii();
	cout << "You know that you have to act now. You spring up, ready to finally deal with this foul mockery of life before you.\n";
	cout << "\nGet ready to fight! Press ENTER to continue.\n" << endl;
	cin.get(proceed);
	enemy1 = 2;
	enemy1_hp = 75;
	battle();
	cout << "You need to get out of here after that. So, you walk out only to find the entire town swarming with these pus-ridden acolytes of death." << endl;
	cout << "Fearing for your life, you find a sewer grate and head down. It stinks, but at least you're safe for now." << endl;
	cout << "\nPress ENTER to continue.\n" << endl;
	cin.get(proceed);
	if (player_sanity <= 50) {
		cout << "Suddenly, a metal pipe starts to move from the ground! You must be insane, but it's really happening!";
		cout << "\n                                                                       ============\n                                                                ======================\n                                                           ===========================\n                                                          ============================\n                                                    ==================================\n                                                    ===============================\n                                              ====================================\n                                         ===================================\n                                       =====================================\n                                  ====================================\n                                 ====================================\n                           =====================================\n                           ===============================\n                     ====================================\n               ====================================\n              =====================================\n            =================================\n           =====      =================\n           =====      =================\n           =====      ===========\n            ====================\n              =============\n                =========";
		cout << "\nThis looks like a one-way trip... Pray to your god, and press ENTER to accept your fate.\n" << endl;
		cin.get(proceed);
		enemy1 = 1738;
		enemy1_hp = 1738;
		battle();
		if (enemy1 == 1738 && enemy1_hp <= 0 && fireball == false) {
			fireball = true;
		}
	}
	cout << "\nYou exit the sewers near the edge of twon, and enter a forest...\n";
}

void forest() {
	std::cout << "\nEntering the forest, you see another one of those monsters, along with two of the parasites.\n";
	std::cout << "Get ready to battle! Press ENTER to continue.";
	cin.get(proceed);
	enemy1 = 2;
	enemy1_hp = 75;
	enemy2 = 1;
	enemy2_hp = 25;
	enemy3 = 1;
	enemy3_hp = 25;
	battle();

	std::cout << "Making it into the depths of the expansive forest, you hear groans and grunts of the dearly departed. Spores permeate the thick fog within." << endl;
	std::cout << "Luckily, you find a hot spring, completely isolated from the rest of the forest." << endl;
	std::cout << "Hit ENTER to continue.";
	cin.get(proceed);


	while (spring_choice != 1 && spring_choice != 2) {
		std::cout << "Will you take a break in the hot springs? Type the number of your choice, and hit ENTER." << endl;
		std::cout << "1. Yes\n2. No\n";
		cin >> spring_choice;
		if (spring_choice == 1) {
			player_hp = 125;
			player_sanity = 100;

			special_point_upgrade = true;
			special_point_max = 200;
			special_point = 200;

			std::cout << "You Special Points are increased to 200!" << endl;
			std::cout << "You feel a whole lot better. Onward..." << endl;
		}
		else if (spring_choice == 2) {
			std::cout << "You decide to not take a bath. Onward..." << endl;
			std::cout << "\nOut of the corner of your eye, you spot a discarded ";
			if (class_choice == 1) {
				std::cout << "halberd";
			}
			else {
				std::cout << "quarterstaff";
			}
			std::cout << ", it's seen better days, but even in this state, it's a powerful weapon.\n";
			weapon3 = true;
			if (class_choice == 2) {
				cout << "\n Beside it you see a piece of paper with the fireball spell";
				fireball = true;
			}
		}
	}
	//Commented out because this line doesn't fit here at all - Nate
	//cout << "\nThis game has a thing known as Special Points, or SP for short. These can be used for spells or stronger weapon attack (called Double Down)";
	cin.get(proceed);
	cin.ignore(); //having it here did work for me -Ruby
	std::cout << "As you venture forth through the forest, you stumble upon a bridge, its cobblestone exterior mixed with the same pus and broils that you saw on the bags of flesh moments before." << endl;
	std::cout << "On the other side of the bridge, a horrid beast that was once a bear stands, its arms broken and battered, with the same rancid, hardened sinew formed into disgusting organic blades." << endl;
	std::cout << "Press ENTER to continue." << endl;
	cin.get(proceed);
	std::cout << "You have a few options on your hands. You can either hide under the bridge, or fight the abomination head-on." << endl;
	while (bridge_choice != 1 && bridge_choice != 2) {
		std::cout << "1. Fight the bear\n2. Hide under the bridge\n";
		std::cout << "Select the number of your choice, then hit ENTER.\n";
		cin >> bridge_choice;
		if (bridge_choice == 1 && player_sanity >= 75) {
			std::cout << "Knowing that you'll need to fight them regardless, you shape up and charge towards the giant mutated bear, who is just as ready to kill as you are.\n";
			std::cout << "\nGet ready to fight! Press ENTER to continue.\n" << endl;
			cin.ignore();
			cin.get(proceed);
			enemy1 = 3;
			enemy1_hp = 165;
			battle();
		}
		else if (bridge_choice == 2 && player_sanity >= 75) {
			cout << "You can't take that on, so you decide to slide under the bridge and hope to God that the thing will move.\n";
			Sleep(3000);
			cout << "Giant stomps cause your adrenaline to peak. Above your head, the putrid monster's thunderous footsteps crackle with every hit against the loose stone.\n";
			Sleep(3000);
			cout << "\nGoing, going... gone. It leaves, and you're able to get up to the top.\n";
		}
		else if (player_sanity < 75) {
			std::cout << "The stress was getting to you. You charge head-on, ready to fight the beast. It must die.\n";
			std::cout << "\nPrepare for a tough fight! Press ENTER to continue.\n" << endl;
			cin.ignore();
			cin.get(proceed);
			enemy1 = 3;
			enemy1_hp = 165;
			battle();
		}
	}
	std::cout << "\nOn top of the bridge, you sit down and just take in the absolute miserable state you're in.\n";
	if (weapon3 == false) {
		std::cout << "\nResting on a crate, you spot a discarded ";
		if (class_choice == 1) {
			std::cout << "halberd";
		}
		else {
			std::cout << "quarterstaff";
		}
		std::cout << ", it's seen better days, but even in this state, it's a powerful weapon.\n";
		weapon3 = true;
		if (class_choice == 2) {
			cout << "\n Beside it you see a piece of paper with the fireball spell";
			fireball = true;
		}
	}
	std::cout << "\nYou're lost, battered, and completely unsure of how you could even end this madness enveloping around you.\n";
	std::cout << "\nHowever, you feel that the only key to getting through this is to barge into ground zero on your left, which is more forestation consumed by the parasite.\n";
	Sleep(3000);
	std::cout << "\nYou haven't seen anyone. In fact, you could be the last person on this planet for all you know. The screaming has stopped for a considerable amount of time.\n";
	Sleep(3000);
	std::cout << "\nYou might as well head in there and find out what's causing this, or die trying.\n";
	std::cout << "\nPress ENTER to begin your final stretch...\n";
	cin.ignore();
	cin.get(proceed);
}

void finale() {
	infected_ascii();
	std::cout << "\nImmediately, as you trek into the spore-ridden air and revolting pus and flesh-fungus, you are assaulted by three infected!\n";
	Sleep(3000);
	enemy1 = 2;
	enemy1_hp = 75;
	enemy2 = 2;
	enemy2_hp = 50;
	enemy3 = 2;
	enemy3_hp = 50;
	battle();
	cout << "\nAs you delve deeper into this sort of personal Tartarus, you once again have to fight even more infected. These look like they were once part of a guild...\n";
	Sleep(3000);
	enemy1 = 2;
	enemy1_hp = 75;
	enemy2 = 2;
	enemy2_hp = 50;
	enemy3 = 2;
	enemy3_hp = 60;
	battle();
	cout << "\nThe further you go, you feel as if the world you knew has vanished far behind you, leaving you in this abstract mockery of life.\n";
	Sleep(3000);
	cout << "\nBefore you is a cave entrance, blocked by an infected ogre. It's almost like the juggernaut from earlier, but a tad bit smaller.\n";
	cout << "\nOn sight, the beast calls for infected to back it up. There's no way to get past this one.\n";
	Sleep(3000);
	enemy1 = 3;
	enemy1_hp = 125;
	enemy2 = 2;
	enemy2_hp = 50;
	enemy3 = 2;
	enemy3_hp = 65;
	battle();
	cout << "\nThey lie on the ground, completely destroyed. A wail can nearly be heard. Unlike the others, this one sounds the least human overall.\n";
	cout << "\nThe screeches and cries continue, all of which is coming from the cave. You have nothing better to do than to head on inside.\n";
	cout << "\nThere's no going back after this. Press ENTER whenever you are ready.\n";
	cin.ignore();
	cin.get(proceed);
	cout << "\nThe cave is riddled with mashed-up bodies, some full of townsfolk that look pretty familiar.\n";
	Sleep(3000);
	cout << "\nThe groaning persists, and you turn to see a writhing mass of rotten flesh tapered to the cave wall.\n";
	cout << "\nIt's massive, even bigger than the mutated bear from earlier. The only part that looks human is-\n";
	gravemind_ascii();
	cout << "\nIt's... It's your partner. The giant pulsating glob of dead flesh was your comrade, now nothing more than a fancy house decoration for the dead.\n";
	Sleep(3000);
	cout << "\nYou grip your weapon. Your adrenaline is pumping. You know what must be done.\n";
	Sleep(5000);
	enemy1 = 4;
	enemy1_hp = 250;
	player_hp = 150;
	special_point = 150;
	battle();
	cout << "\nThe beast unleashes a roar of agony, and the pus-filled boils on the walls begin to pulsate and slosh around. Your friend can finally rest.\n";
	Sleep(2000);
	cout << "\nYou run out of the cave, watching multiple of the thralls simply drop dead. The broils begin to pop and dissipate. The sun pierces through the hazy fog.\n";
	Sleep(2000);
	if (turns_passed <= 5) {
		cout << "\nThe beasts are gone. You begin the long trek back home. Civilization may be gone, but you can rebuild.\n";
		cout << "\nYou don't know what comes next. All you know is that they're gone, and if they come back...\n";
		Sleep(3000);
		cout << "\nYou'll be ready.\n";
		Sleep(5000);
		cout << "\n===THE END===\n";
	}
	else if (class_chioce == 2 && turns_passed <= 8) {
		cout << "\nThe beasts are gone. You begin the long trek back home. Civilization may be gone, but you can rebuild.\n";
		cout << "\nYou don't know what comes next. All you know is that they're gone, and if they come back...\n";
		Sleep(3000);
		cout << "\nYou'll be ready.\n";
		Sleep(5000);
		cout << "\n===THE END===\n";
	}
	else {
		cout << "\nThe beasts may be gone, but they always come back. Why wouldn't they? You know that they'll come for you next, if not for your bloodline.\n";
		Sleep(3000);
		cout << "\nYou live alone in the cave, fearful of the parasite's return. It drives you mad how easy those little leeches were able to tear through sinnew, crunch down bone...\n";
		Sleep(3000);
		cout << "\nYou never leave the cave. The bodies don't taste so well, but going out there? Too dangerous. Better safe than sorry.\n";
		Sleep(3000);
		cout << "\nSo, as you eat the muddled inky flesh of one of the townsfolk, you sigh in the fact that you are safe and perfectly fine.\n";
		Sleep(5000);
		cout << "\n===THE END===\n";
	}
}

void credits() {
	cout << "\nSPYWARE INTERACTIVE IS...\n";
	Sleep(3000);
	cout << "\nCole Neely\n";
	Sleep(2000);
	cout << "\nNathan Beauchamp";
	Sleep(2000);
	cout << "\nRuby Winter";
	Sleep(5000);
	cout << "\nIf you have anything to say about the game, please type it in now.\n";
	getline(cin, final_string);
	if (final_string == "metal pipe") {
		cout << "Suddenly, a metal pipe starts to move from the ground! You must be insane, but it's really happening!";
		cout << "\n                                                                       ============\n                                                                ======================\n                                                           ===========================\n                                                          ============================\n                                                    ==================================\n                                                    ===============================\n                                              ====================================\n                                         ===================================\n                                       =====================================\n                                  ====================================\n                                 ====================================\n                           =====================================\n                           ===============================\n                     ====================================\n               ====================================\n              =====================================\n            =================================\n           =====      =================\n           =====      =================\n           =====      ===========\n            ====================\n              =============\n                =========";
		cout << "\nThis looks like a one-way trip... Pray to your god, and press ENTER to accept your fate.\n" << endl;
		cin.get(proceed);
		player_hp = 99999999999999;
		special_point_max = 50000;
		special_point = 50000;
		enemy1 = 1738;
		enemy1_hp = 1738;
		battle();
		cout << "\nThe pipe gets vaporized immediately. The President sends his thanks, you get a key to the White House, and you are loved by many for your pure act of selfless courage.\n";
		Sleep(3000);
		cout << "\nThanks for playing. Be sure to smash that like button, subscribe and ring that bell for future uploads.\n";
	}
	else {
		cout << "Thank you for playing!";
	}
}

int main() {
	tavern_choice = 0;
	bridge_choice = 0;
	spring_choice = 0;
	class_choice = 0;
	player_hp = 100;
	special_point = 100;
	special_point_max = 100;
	special_point_upgrade = false;
	player_sanity = 100; //Change back to 100 -Ruby
	weapon2 = false;
	weapon3 = false;
	weapon4 = false;
	light = false;
	magic_missile = false;
	freeze = false;
	fireball = false;
	std::cout << "This game is best experienced in fullscreen or a maximized window.\nHit F11 or click on the button next to the X in the top left corner.";
	Sleep(10000);
	team_logo_ascii();
	std::cout << "\nA game by Spyware Interactive\n";
	Sleep(5000);

	while (class_choice != 1 && class_choice != 2) {
		cout << "\nYou're slightly coming to. You can't remember your name, but you at least remember your occupation. You are a...\n1. Knight\n2. Mage \nType the number of your choice and press ENTER to continue.\n";

		cin >> class_choice;

		if (class_choice == 2) {
			light = true; //The Light Spell -Ruby //Commented out because it's unfinished - Nate
			magic_missile = true; //Magic Missile Spell -Ruby
			player_hp = 150;
		}
	}
	weapon2 = true;
	cout << "\nYou awaken in a hazy stupor, the past few nights seeming to be nothing more than a barrage of unpaid bar tabs and enough liver damage to make a dwarf go cold turkey.";
	cout << "\nThe lights are dim, and nobody else is in sight. Perhaps the barkeep closed up for the day and didn't bother to drag you out. Can't say you blame them, though.";
	cout << "\nEver since your partner went missing after last week's expedition, you've turned to drinking and vice to keep your mind off of it.";
	cout << "\nHowever, this massive hangover dawning upon you signals that you can't just keep putting it off forever.\n";
	cout << "\nPress ENTER to continue.\n";
	cin.get(proceed);
	cin.ignore(); //having it here did work for me -Ruby
	cout << "On cue, the front door is assaulted by three knocks that echo throughout the whole room. You almost go for it, but the knocking continues.";
	cout << "\nDemonic screeches and garbled cries for help muffled by frantic growls and horrid scraping.";
	cout << "\nPress ENTER to continue.\n";
	cin.get(proceed);
	cout << "Backing away, you figure that you need to get out of here before whatever this thing is comes in. You ponder your next choice of action." << endl;

	while (tavern_choice != 1 && tavern_choice != 2 && tavern_choice != 3) {
		cout << "\n1. Kick the front door down\n2. Go out through the back\n3. Hide behind the counter\n \nType the number of your choice and hit ENTER to continue." << endl;
		cin >> tavern_choice;
	}

	if (tavern_choice == 1) {
		door_kicked();
		forest();
		finale();
		credits();
		exit(0);
	}

	else if (tavern_choice == 2) {
		backdoor();
		forest();
		finale();
		credits();
		exit(0);
	}

	else if (tavern_choice == 3) {
		coward();
		forest();
		finale();
		credits();
		exit(0);
	}
}
