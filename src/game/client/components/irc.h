#ifndef GAME_CLIENT_COMPONENTS_IRC_H
#define GAME_CLIENT_COMPONENTS_IRC_H

#include <stdlib.h>
#include <string>

#include <base/tl/sorted_array.h>

#include <engine/external/cpirc/IRC.h>
#include <game/client/component.h>

class CIRC : public CComponent
{
public:
	struct IRCUser
	{
		std::string User;
		std::string Domain;
		std::string Server;
		std::string Nick;
		std::string Modes;
		//std::string pNoIdeaHowToNameIt; // what is this? (:3 or :0)
		std::string Realname;

		bool operator <(const CIRC::IRCUser& other) { return User[0] < other.User[0]; }
	};

	enum
	{
		IRC_LINETYPE_CHAT=0,
		IRC_LINETYPE_NOTICE,
		//IRC_LINETYPE_SYSTEM, // this one not (yet)
	};

private:
	IRC m_Connection;

	void *m_pIRCThread;
	static void ListenIRCThread(void *pUser);

	sorted_array<IRCUser> m_UserList;

public:
	CIRC();

	void SendChat(const char *pMsg);
	void SendRaw(const char *pMsg);

	void Connect();
	void Disconnect(char *pReason);

	void SendRequestUserList();
	void SendNickChange(const char *pNewNick);
	void AddLine(int Type, const char *pNick, const char *pLine); // chat
	void AddLine(const char *pLine); // system

	char *CurrentNick() { return m_Connection.current_nick(); }
	bool IsConnected() { return m_Connection.is_connected(); }

	virtual void OnConsoleInit();
	virtual void OnReset();
	virtual void OnRender();
	virtual void OnShutdown();

};
#endif