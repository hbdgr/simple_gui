#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include "mainwindow.hpp"
#include "netclient.hpp"
#include "json.hpp"
#include <memory>

class order final {
public:
	order(nlohmann::json params);
	~order() = default;
	std::string get_str() const;

private:
	std::string m_cmd;
	std::string m_msg;
};

class MainWindow;
class netClient;

class commandExecutor final : public std::enable_shared_from_this<commandExecutor> {
	public:
		static std::shared_ptr<commandExecutor> construct(std::shared_ptr<MainWindow> window);
		void parseAndExecMsg(const std::string &msg); ///< parse network msg
		void sendNetRequest(const order &ord); ///< send order via network
		void startConnect(const QHostAddress &address, uint16_t port);

	private:
		commandExecutor(std::shared_ptr<MainWindow> window);
		std::weak_ptr<MainWindow> m_main_window;
		std::shared_ptr<netClient> m_net_client;
};

#endif // COMMANDEXECUTOR_H


/**
  communication protocol :

  using example
  initial message - starting peer :




	{
	"id": 1234,			- message id - number
	"cmd": "addpeer",	activity type 
	"topic: "addpeer"+id, 	-creating new topic of conversation to easer manage many conversations 
	"msg":{					the main 
					"type": "question",				-podjecia decyzji
					."text":"do i need to make a coffe?",
					"ans":"yes/no/info";,
						parametry komendy
		}
	}
//info msg ://////////////////
{
	"id":1,
	"cmd":"info",
	"topic":"info1",
	"msg":{
		"text":"show first info"
	}
}
ans:
{
	"id":2,
	"cmd":"ans1",
	"topic":"info1",
}
//question/////////////////////////
{
	"id":3,
	"cmd":"ask",
	"topic":"ask3",
	"msg":{
		"text":"do a coffe?",
		"pans":"yes/no"
	}
}
ans:
{
	"id":4
	"cmd":"ans3"
	"topic":"ask3"
	"msg":{
		"ans":"yes"
	}
}



//////////////////////////////////
	answer:

	{
		"id":1235,
		"cmd":"ans"+1234,	 		-odpowiedz na rozkaz 1234
		"topic":"addpeer1234",		-temat rozmowy
		"err":"0",						-ewentualnie blad wkonania
		"msg":{					-ewentualne parametry odpowiedzi- z mozliwoscia wprasowania koniecznosci
					"type": "ans",				-podjecia decyzji"
					"ans":"yes"
		}
	}

  */


