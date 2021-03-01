#pragma once

#include "WebHook.h"

using namespace httplib;
using std::string;
using json = nlohmann::json;

class TAlice {
public:
	string GetWordFromTokens(json tokens, unsigned int id);
	string GetWordsFromTokens(json tokens, unsigned int beginid, unsigned int endid);
	string GetResponse(string body);
	string GetResponseMain(string body, json j, json tokens, json state);
	string GetResponseHelp(string body, json j, json tokens, json state, bool start = false);
	json CreateButtonsMain(json state);
	json CreateButtonsHelp(json state);
	void EraseFromCart(json &state, string name);
	string GetCart(json state);
	string GetCartSum(json state);
	string CreateResponse(string s, json state, json buttons, bool end_session = false);
	TAlice();
};

string TAlice::CreateResponse(string s, json state, json buttons, bool end_session) {
	json j;
	j["response"]["text"] = s;
	if (state["canSpeak"])
		j["response"]["tts"] = s;
	j["response"]["buttons"] = buttons;
	j["response"]["end_session"] = end_session;
	j["version"] = "1.0";
	j["session_state"] = state;
	std::stringstream ss;
	ss << std::setw(2) << j << std::endl;
	return ss.str();
}

string TAlice::GetWordFromTokens(json tokens, unsigned int id) {
	if (id < tokens.size()) {
		string s = tokens[id];
		return s;
	}
	return "";
}

string TAlice::GetWordsFromTokens(json tokens, unsigned int beginid, unsigned int endid) {
	string rez = "";
	for (int i = beginid; i <= endid; i++) {
		rez += GetWordFromTokens(tokens, i);
		if (i != endid) rez += " ";
	}
	return rez;
}

json TAlice::CreateButtonsMain(json state) {
	json buttons = json::array();
	if (state["canSpeak"]) {
		buttons[0]["title"] = u8"�������";
	} else {
		buttons[0]["title"] = u8"��������";
	}
	buttons[1]["title"] = u8"������";
	return buttons;
}

json TAlice::CreateButtonsHelp(json state) {
	json buttons = json::array();
	buttons[0]["title"] = u8"�������";
	buttons[1]["title"] = u8"��������";
	buttons[2]["title"] = u8"������";
	buttons[3]["title"] = u8"�������� �������";
	buttons[4]["title"] = u8"�������� � �������";
	buttons[5]["title"] = u8"������� �� �������";
	buttons[6]["title"] = u8"��� � �������";
	buttons[7]["title"] = u8"�����";
	buttons[8]["title"] = u8"������� ���������";
	buttons[9]["title"] = u8"����� �� �������";
	return buttons;
}

void TAlice::EraseFromCart(json &state, string name) {
	for (int i = 0; i < state["check"].size(); i++) {
		if (state["check"][i]["item"] == name) {
			state["check"].erase(i);
			return;
		}
	}
}

string TAlice::GetCart(json state) {
	if (state["check"].size() <= 0) {
		return u8"������� �����";
	}
	string rez = "";
	for (int i = 0; i < state["check"].size(); i++) {
		string name = state["check"][i]["item"];
		int price = state["check"][i]["price"];
		string temp;
		temp = name + u8" " + std::to_string(price);
		temp = temp + u8" ������\n";
		rez += temp;
	}
	rez.pop_back(); //remove last return
	return rez;
}

string TAlice::GetCartSum(json state) {
	int total = 0;
	for (int i = 0; i < state["check"].size(); i++) {
		total += state["check"][i]["price"];
	}
	return u8"��������� ���������: " + std::to_string(total);
}

string TAlice::GetResponseMain(string body, json j, json tokens, json state) {
	if (j["session"]["new"]) {
		state["canSpeak"] = true;
		state["check"] = {};
		state["mode"] = "main";
	}

	string rez = "";
	json buttons = CreateButtonsMain(state);

	if (j["session"]["new"]) {
		rez = u8"������������! � ������ ��� � ���������.";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"�������") {
		state["canSpeak"] = false;
		json buttons = CreateButtonsMain(state);
		rez = u8"�����, �����";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"��������") {
		state["canSpeak"] = true;
		json buttons = CreateButtonsMain(state);
		rez = u8"������";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"������") {
		state["mode"] = u8"help";
		return GetResponseHelp(body, j, tokens, state, true);
	}
	if (GetWordsFromTokens(tokens, 0, 1) == u8"�������� �������")  {
		state["check"] = {};
		rez = u8"������� �����";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 2) == u8"�������� � �������") {
		string name = GetWordFromTokens(tokens, 3);
		int price = std::stoi(GetWordFromTokens(tokens, 4));
		state["check"].push_back({ {"item", name}, {"price", price} });
		rez = u8"��";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 2) == u8"������� �� �������") {
		string name = GetWordFromTokens(tokens, 3);
		EraseFromCart(state, name);
		rez = u8"��";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 2) == u8"��� � �������") {
		rez = GetCart(state);
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"�����") {
		rez = GetCartSum(state);
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 1) == u8"������� ���������") {
		wh.SendToAll(state["check"], j["session"]["user"]["user_id"]);
		return CreateResponse(u8"�������� ���", state, buttons, true);
	}
	if (/* COMMAND UNKNOWN */1) {
		rez = u8"����������� �������";
		return CreateResponse(rez, state, buttons);
	}
}

string TAlice::GetResponseHelp(string body, json j, json tokens, json state, bool start) {
	string rez;
	json buttons = CreateButtonsHelp(state);
	if (start) {
		rez = u8"�������. ������� ������������ �������.\n������. ������� ����������� � ��������� ������\n�������/��������.\
������� ��������� ����������� ���������\n� ��� ���������� ���������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"�������") {
		rez = u8"��� ����������� ��������� ����� ���������� ������� � �������� ������ ��������� ��� �����������";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"��������") {
		rez = u8"��� ����������� ��������� ����� ���������� ������� � �������� ������ ������������";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"������") {
		rez = u8"����� ������ ������ ������������� � ����� ������";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 1) == u8"�������� �������")
	{
		rez = u8"�������� ������� [��������]\n������ ������� �������. ����� ���������� ������� ��� �������� ������� ����� ������������ �������";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 2) == u8"�������� � �������") {
		rez = u8"�������� � ������� [��������, ����]\n� ������� ����������� ����� �����, ����������� ��� ���� � ������������. ���� ������ - ��� ����� �����";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 2) == u8"������� �� �������") {
		rez = u8"������� �� ������� [��������]\n������������ ������� ����� �� ������� �� �������� ������";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 2) == u8"��� � �������") {
		rez = u8"����������� ��� ������ � ������������ ������� � �������: �������� � ����";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordFromTokens(tokens, 0) == u8"�����") {
		rez = u8"�������� ������������ ��������� ��������� ������� � �������";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 1) == u8"������� ���������") {
		rez = u8"��������� ���������� ������� � ��������� ���������������� ������";
		rez += u8"\n� ��� ��� ����������?";
		return CreateResponse(rez, state, buttons);
	}
	if (GetWordsFromTokens(tokens, 0, 2) == u8"����� �� �������") {
		state["mode"] = u8"main";
		rez = u8"��������� ���";
		return CreateResponse(rez, state, CreateButtonsMain(state));
	}
	if (/* COMMAND UNKNOWN */1) {
		rez = u8"����������� �������";
		return CreateResponse(rez, state, buttons);
	}
}

string TAlice::GetResponse(string body) {
	json j = json::parse(body);
	json tokens = j["request"]["nlu"]["tokens"];
	json state = j["state"]["session"];
	string mode;

	try {
		mode = state["mode"];
	} catch (...) {
		mode = u8"main";
	}
	
	/* Main response */
	if (mode == u8"main") {
		return GetResponseMain(body, j, tokens, state);
	}
	if (mode == u8"help") {
		return GetResponseHelp(body, j, tokens, state);
	}

	string rez = "���������������� ������";
	return CreateResponse(rez, state, "{}");
}

TAlice::TAlice() {
	//DO NOTHING
}