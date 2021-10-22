#pragma once

//    Growtopia Bot
//    Copyright (C) 2018  Growtopia Noobs
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "json.hpp"
#include <sstream>
#include <vector>
#include <limits>
#include <math.h>
#include <string>
#include <iostream>
#include <regex>
#include <iterator>
#include <algorithm>

#include "utilsfunc.h"
#include "corefunc.h"
#include "enet/include/enet.h"
//#define WORLD_GO
using namespace std;
char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

std::string hexStr(unsigned char data)
{
	std::string s(2, ' ');
	s[0] = hexmap[(data & 0xF0) >> 4];
	s[1] = hexmap[data & 0x0F];
	return s;
}

string generateMeta()
{
	string x = to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255);
	return x;
}

string generateMac()
{
	string x;
	for (int i = 0; i < 6; i++)
	{
		x += hexStr(rand());
		if (i != 5)
			x += ":";
	}
	return x;
}

string generateRid()
{
	string x;
	for (int i = 0; i < 16; i++)
	{
		x += hexStr(rand());
	}
	for (auto & c : x) c = toupper(c);
	return x;
}

string stripMessage(string msg) {
	regex e("\\x60[a-zA-Z0-9!@#$%^&*()_+\\-=\\[\\]\\{};':\"\\\\|,.<>\\/?]");
	string result = regex_replace(msg, e, "");
	result.erase(std::remove(result.begin(), result.end(), '`'), result.end());
	return result;
}

void GrowtopiaBot::onLoginRequested()
{
	string token;
	if (!login_user && !login_token) {
		token = "";
	} else {
		token = "\nuser|" + std::to_string(login_user) + "\ntoken|" + std::to_string(login_token);
	}
	string ver = gameVersion;
	string hash = std::to_string((unsigned int)rand());
	string hash2 = std::to_string((unsigned int)rand());
	//string packet = "Logging on: " + uname + " Token: " + to_string(login_token) + " UserID: " + to_string(login_user) + "\n";
	//if (login_token != 0 || login_token != -1) //cout << packet;
	SendPacket(2, "tankIDName|" + uname + "\ntankIDPass|" + upass + "\nrequestedName|SmellZero\nf|1\nprotocol|127\ngame_version|" + ver + "\nfz|5367464\nlmode|0\ncbits|0\nplayer_age|18\nGDPR|1\nhash2|" + hash2 + "\nmeta|" + generateMeta() + "\nfhash|-716928004\nrid|" + generateRid() + "\nplatformID|0\ndeviceVersion|0\ncountry|us\nhash|" + hash + "\nmac|" + generateMac() + "\nwk|" + generateRid() + "\nzf|-496303939" + token, peer);
	//currentWorld = "";
}
void GrowtopiaBot::packet_type3(string text)
{
	if (text.find("action|log\nmsg|") != std::string::npos) {
		string t = explode("msg|", text)[1];
		cout << "Message: " << t << endl;
	}
	//dbgPrint("[" + uname + " ]Some text is here: " + text);
	if (text.find("LOGON ATTEMPTS") != string::npos)
	{
		//cout << "Wrong username / password!. (LOGON ATTEMPTS)";
	}
	if (text.find("password is wrong") != string::npos)
	{
		//cout << "Wrong password!";
	}
	//if (text.find("action|log\n") != std::string::npos) cout << uname << " " << text << endl;
	if (text.find("action|logon_fail") != string::npos)
	{
		connectClient();
		objects.clear();
	}
}

void GrowtopiaBot::packet_type6(string text)
{
	//dbgPrint("Some text is here: " + text);
	SendPacket(2, "action|enter_game\n", peer);
	enet_host_flush(client);
}

void GrowtopiaBot::packet_unknown(ENetPacket* packet)
{
	//dbgPrint("Got unknown packet type: " + std::to_string(GetMessageTypeFromPacket(packet)));
	//dbgPrint("Packet size is " + std::to_string(packet->dataLength));
}
void GrowtopiaBot::WhenConnected()
{
	cout << uname << " Connected to server, creating account!" << endl;
}

void GrowtopiaBot::WhenDisconnected()
{
	cout << uname << " Disconnected from server..." << endl;
	connectClient();
}

void GrowtopiaBot::userInit() {
	connectClient();
	//cout << flush;
}
