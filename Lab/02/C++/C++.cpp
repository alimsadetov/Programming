#include <iostream>
#include <vector>
#include <iomanip>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include "WebHook.h"
#include "Dialogs.h"

using namespace httplib;
using std::string;
using json = nlohmann::json;

TAlice Alice;

string replace_str(string str, string source, string nw) {
	SIZE_T sbegin = str.find(source);
	return str.replace(sbegin, source.length(), nw);
}

string readFile(string filename) {
	std::ifstream is(filename);
	std::stringstream ss;
	ss << is.rdbuf();
	return ss.str();
}

void process_post(const Request& req, Response& res) {
	if (req.method != "POST")
		return;

	if (req.has_param("del")) {
		string val = req.get_param_value("del");
		int id = wh.Search(val);
		if (id >= 0)
			wh.Erase(id);
	}
	if  (req.has_param("set")) {
		string val = req.get_param_value("set");
		wh.PushBack(val);
	}
	res.set_redirect("#");
}

void wh_response(const Request& req, Response& res) {
	string block_original = readFile("block.html");
	string blocks = "";
	for (int i = 0; i < wh.Size(); i++) {
		string block_temp = block_original;
		block_temp = replace_str(block_temp, "Webhook URL", wh.Get(i));
		block_temp = replace_str(block_temp, "Webhook URL", wh.Get(i));
		blocks += block_temp+"\n";
	}
	string templ = readFile("template.html");
	templ = replace_str(templ, "{webhooks_list}", blocks);
	process_post(req, res);
	res.set_content(templ, "text/html");
}

void dialog_response(const Request& req, Response& res) {
	string body = req.body.c_str();
	string aresp = Alice.GetResponse(body);
	res.set_content(aresp, "text/plain");
}

int main()
{
	Server svr;   
	svr.Post("/", dialog_response);
	svr.Get("/webhooks", wh_response);
	svr.Post("/webhooks", wh_response);
	std::cout << "Start server... OK\n";
	svr.listen("127.0.0.1", 1234);
}