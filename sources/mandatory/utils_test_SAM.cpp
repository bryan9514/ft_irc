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

int		handleCmd(/*Client &Client,*/ std::string& cmd)
{
	std::vector<std::string> splited = this->Tokenizer(cmd);
	unsigned int size = splited.size();
}
