#include "irc.hpp"
#include "server.hpp"

std::vector<std::string>	Tokenizer(std::string& line)
{
	std::vector<std::string>	token;
	size_t pos = 0;
	size_t posend = 0;
	while (pos != std::string::npos) {
		pos = line.find_first_not_of(" \r\n", posend);
		if (pos != std::string::npos) {
			if (line[pos] == ':') {
				if (pos + 1 < line.length())
					token.push_back(line.substr(pos + 1, line.length() - pos));
				break;
			}
			posend = line.find_first_of(" \r\n", pos);
			if (posend == std::string::npos)
				posend = line.length();
			token.push_back(token.substr(pos, posend - pos));
		}
	}
	return (token);
}

int		handleCmd(Client &Client,std::string& buffer)
{
	std::vector<std::string> splitted = this->Tokenizer(buffer);
	unsigned int size = splited.size();
	if (!size)
		return (0);
	std::cout << "Buffer Splitted ( " << size << " ) : ";
	for(unsigned int i = 0; i < size; i++) 
	{
		if (!splitted[i].empty())
			std::cout << "\"" << splited[i] << "\"" << " ";
	}
	std::cout << std::endl;
	std::string commands[??] = { "PASS" , "QUIT" , "NICK", "USER", "KICK", "INVITE" , "TOPIC" ...}
	for (int i = 0; i <= ??; i++)
	{
		if (splitted[0] == commands[i])
			break;
	}
	if (i > 1 && !client->_is_Logged)
	{
		std::cout << "Register by using 'PASS <password>'\r\n" << std::endl;
		return (0);
	}
	if (i > 3 && !client->_is_registered)
	{
		std::cout << "Start logging in by using 'USER <username>\r\n" << std::endl;
		return (0);
	}
	switch (i) {
		case 0:
		  this->pass(client, splitted);
		  return (0);
		case 1:
			//[...]
	}
}

void	/*Server::*/displayMsg(std::string str, int clientFD)
{
	send(clientFD, str.c_str(), str.length(), 0);
}

void /*Server::*/sendToAll(const std::string& msg)
{
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        send(it->first, msg.c_str(), msg.length(), 0);
}
