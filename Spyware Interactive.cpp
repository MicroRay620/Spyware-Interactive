#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <random>

using namespace std;

int class_choice = 0; // 1 is knight, 2 is mage
long long player_hp = 100; //long long makes it so the amount removed can be large
int player_atk = 20;
int player_sanity = 100;
int player_def; //0 is unarmored //1 is starting armor //2 is better armor
int attack_choice = 0; //used when choosing an enemy to attack
int weapon_choice = 0;
int crit_chance = 0;
char proceed = ' '; //have the = ' ' removes an error where it is saying get(proceed) is not an acceptable input 
vector<string> player_inventory{ "Fists" }; //Is an array //Change number in the [ ] //Can be declared the same way as a list
//^may switch the vector to list, having issues adding values to it

int tavern_choice = 0;

int enemy1_hp = 0;
int enemy2_hp = 0;
int enemy3_hp = 0;

//0 is dead, 1 is parasite, 2 is infected, 3 is metal pipe
//Parasite has 25hp, infected has 75hp, juggernaut has 150hp, metal pipe has 1738hp
int enemy1 = 0;
int enemy2 = 0;
int enemy3 = 0;

int loop = 0; //exists to stop infinite loops when something breaks

int random_crit(int low, int high) {
	random_device rd;
	uniform_int_distribution<int> dist(low, high);
	return dist(rd);
}

void enemy_turn(int current_enemy) {
	if (current_enemy == 1) {
		cout << "\nEnemy parasite attacks!\n";
		player_hp -= 5;
		player_sanity -= 5;
	}
	else if (current_enemy == 2) {
		cout << "\nEnemy infected attacks!\n";
		player_hp -= 10;
		player_sanity -= 10;
	}
	else if (current_enemy == 3) {
		cout << "\nThe metal pipe breaks your kneecaps!\n";
		player_hp -= 194530298001;
		player_sanity -= 420;
	}
}

void battle() {
	while (true) {
		if (player_hp <= 0 && enemy1 == 3) {
			cout << "\n'but the Lord laughs at the wicked, for he knows their day is coming.'\n";
			cin.ignore();
			cin.get(proceed); //continues by just pressing 'enter'
			exit(0);
		}
		else if (player_hp <= 0) {
			cout << "Game Over";
			cin.ignore();
			cin.get(proceed);
			exit(0);
		}
		if (enemy1 == 0 && enemy2 == 0 && enemy3 == 0) {
			player_hp = 100;
			cout << "\nVictory!\n";
			cout << " hit ENTER to continue:\n";
			cin.ignore();
			cin.get(proceed);
			break;
		}

		cout << "\nCurrent HP: " << player_hp << endl; //Having an error when we reach this line //error is an issue with the vector sub-script //no idea what that means
		cout << "\nType in the number of your weapon:\n1." << player_inventory[0] << "\n2." << player_inventory[1] << endl;
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
		else { //resets the battle
			cout << "why?";
			continue;
		}

		cout << "\nEnter the number of the enemy you will attack\n";
		if (enemy1 != 0) {
			cout << "Enemy 1: " << enemy1_hp << "hp\n";
		}
		if (enemy2 != 0) {
			cout << "Enemy 2: " << enemy2_hp << "hp\n";
		}
		if (enemy3 != 0) {
			cout << "Enemy 3: " << enemy3_hp << "hp\n";
		}
		cin >> attack_choice;
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
		else { //resets the turn, can be exploited to force a crit but it's fine
			cout << "bruh";
			continue;
		}

		//enemy turns start here
		enemy_turn(enemy1);
		enemy_turn(enemy2);
		enemy_turn(enemy3);
	}
}

void door_kicked() {
	cout << "\nWorking up the impaired judgment caused by your three-day bender, you effortlessly kick down the door and face the demonic door-puncher.\n" << endl;
	cout << "It was a horrific sight indeed. The man- no, the beast before you was a man, but its clammy flesh has been contorted in a manner where its head is dangling to the side,";
	cout << "\na face of anguish and suffering frozen in the exact moment of its initial form being violated.";
	cout << "\nWithin its bosom lies a squirming little parasite burrowed in, with its red tendrils sticking out and aimlessly feeling everything it can.";
	cout << "\n press ENTER to continue.\n" << endl;
	cin.ignore();
	cin.get(proceed);
	cout << "Upon sighting you, it immediately charges at you, thirsting for another body to add to the fold." << endl;
	cout << "\nGet ready to fight!  press ENTER to continue.\n" << endl;
	cin.ignore();
	cin.get(proceed);
	enemy1 = 2;
	enemy1_hp = 50;
	enemy2 = 2;
	enemy2_hp = 50;
	battle();
	cout << "Your bones ache and your brain is burning, but at least you're still alive.";
	cout << "\nGingerly stepping over the now motionless husks, you walk outside to find the entire town in ruin.";
	cout << "\n Knowing fully well that you won't last in the middle of a town full of these zombie-like freaks, you run into the forest...";
}

void backdoor() {
	cout << "Deciding that perhaps confronting a horror beyond your comprehension head-on isn't smart, you carefully sneak into the back of the bar," << endl;
	cout << "hoping that you can easily get out of this mess. You're stopped dead in your tracks by two fleshy, pulsating parasites about the size of your head.\n";
	cout << "Press ENTER to continue.";
	cin.ignore();
	cin.get(proceed);
	cout << "                                        =================\n                                  =============================\n                                  =======               =======\n                               ====                           ====\n                               ====                           ====\n                            ====                                 ====\n                            ====                                 ====\n                            ====                                 ====\n                         ======                                  =======\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                         ===                                         ===\n                            ====     -------         -------     ====\n                            ====     -------         -------     ====\n                            ====     -------         -------     ====\n                               ====                           ====\n                               ====                           ====\n                               ==========               =============\n                               ==========               =============\n                            ====     ==========================  =======\n                            ====  ============================================\n                            ====  ====  ====   ===   ====  =======      ======\n                         ===   ====     ====   ===   ====     =======      ===\n                         ===   ====     ====   ===   ====     =======      ===\n                      ======   ====     ====   ======   ====     ====      ===\n                   ================     ====   ======   ====     =======   ===\n                   ======   ====        ====      ===   ====         ===   ===\n                   ===      ====        ====      ===   ====         ===      ====\n                   ===      ====        ====      ===   ====         ===      ====\n               =======      ====        ====      ===   ====         ======   ====\n               =======      ====        ====      ===   ====         ======   ====\n               ====         ====        =======   ===   =======         ===\n                ======      =======      ======   =============         ===\n                   ===         ====         ===      ====  ====\n";
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
	cout << "Unsure of the idea that you wish to leave your only idea of shelter, you hide behind the bar counter, praying that the incessant knocking stops." << endl;
	cout << "The knocking ends. For a brief moment, you stop to consider if it was only a drunkard, and you're almost a little at ease at the idea.\n";
	cout << "Maybe you're still a little woozy and just imagining stuff...\n";
	cout << "\nPress ENTER to continue.\n" << endl;
	cin.ignore();
	cin.get(proceed);
	cout << "Your hopes for salvation are dashed as the door explodes into countless jagged bits of wood, and the assailant enters, its feet stomping against the tile." << endl;
	cout << "You hold your breath behind the counter as the thing slinks about the place. The stench of rot permeates the air as it gets ever so closer to the counter...\n";
	cout << "\nPress ENTER to continue.\n" << endl;
	cin.get(proceed);
	cout << "Its face is contorted and frozen in a moment of sheer pain and anguish before its initial death, and within its chest is a giant parasite burrowed inside." << endl;
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
		enemy1 = 3;
		enemy1_hp = 1738;
		battle();
	}

}

int main() {
	while (class_choice < 1 && class_choice > 2) {
		cout << "\nYou're slightly coming to. You can't remember your name, but you at least remember your occupation. You are a...\n1. Knight\n2. Mage (Coming Soon)\nType the number of your choice and press ENTER to continue.\n";
		cin >> class_choice;
		//cout << class_choice;
		loop += 1;
		if (loop > 10) {
			exit(0); //Ends code
		}

		if (class_choice == 1) {
			player_inventory.push_back("Arming Sword");
		}

		else if (class_choice == 2) {
			cout << "\nComing Soon\n";
		}
	}

	cout << "You awaken in a hazy stupor, the past few nights seeming to be nothing more than a barrage of unpaid bar tabs and enough liver damage to make a dwarf go cold turkey.";
	cout << "\nThe lights are dim, and nobody else is in sight. Perhaps the barkeep closed up for the day and didn't bother to drag you out. Can't say you blame them, though.";
	cout << "\nEver since your partner went missing after last week's expedition, you've turned to drinking and vice to keep your mind off of it.";
	cout << "\nHowever, this massive hangover dawning upon you signals that you can't just keep putting it off forever.\n";
	cout << "\nPress ENTER to continue.\n";
	//removed the cin.ignore() at this line because it made you have to press ENTER twice instead of once
	cin.get(proceed);
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
		cout << "\nThanks for playing the demo! Please fill out the form, or play again to see the other paths!";
		cin.ignore();
		cin.get(proceed);
		exit(0);
	}

	else if (tavern_choice == 2) {
		backdoor();
		cout << "\nThanks for playing the demo! Please fill out the form, or play again to see the other paths!";
		cin.ignore();
		cin.get(proceed);
		exit(0);
	}

	else if (tavern_choice == 3) {
		coward();
		cout << "\nThanks for playing the demo! Please fill out the form, or play again to see the other paths!";
		cin.ignore();
		cin.get(proceed);
		exit(0);
	}

	else {
		cout << "Incorrect. Please select a valid option." << endl;
	}
}