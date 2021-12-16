// CPPBot.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include <string>
#include <unistd.h>
#include <stdint.h>
#include "json.hpp"
//#include <curses.h>
//#include <conio.h>
//#include <windows.h>

using json = nlohmann::json;
using namespace std;
vector<GrowtopiaBot> bots;

GrowtopiaBot bot1 = {"", "", "", -1};

GrowtopiaBot makeBot(string user, string pass, string host, int port, string vers, string wname) {
	GrowtopiaBot bot = {user, pass, host, port};
	bot.gameVersion = vers;
	bot.currentWorld = wname;
	bot.userInit();
	bots.push_back(bot);
	return bot;
}
void botSetup() {
	ifstream i("config.json");
	json j;
	i >> j;
	init();
	system("clear");
	string user1 = j["bot1"].get<string>(), pass1 = j["pass1"].get<string>();
	string vers = j["gtversion"].get<string>();
	string wn = j["home"].get<string>();
	bot1 = makeBot(user1, pass1,"213.179.209.168", 17198, vers, wn);
	while (true) {
		bot1.eventLoop();
	}
}
int main() {
	botSetup();
}
