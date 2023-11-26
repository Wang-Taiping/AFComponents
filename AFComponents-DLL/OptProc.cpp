#pragma warning(disable: 4996)

#include "OptProc.h"
#include <regex>

static std::string keyname(std::string str)
{
	for (size_t i = 0; i < 2; i++) if (str.front() == '-') str.erase(str.begin());
	size_t pos = str.find('=');
	if (pos != std::string::npos) return str.substr(0, pos);
	return str;
}

static std::string keyval(std::string str)
{
	size_t pos = str.find('=');
	if (pos == str.size()) return std::string();
	if (pos != std::string::npos) return str.substr(pos + 1);
	return std::string();
}

afc::optobj::optobj()
{
	baseaddr = nullptr;
	argc = 0;
	optid = 1;
}

afc::optobj::optobj(int argc, char* argv[])
{
	baseaddr = nullptr;
	this->argc = 0;
	optid = 1;
	bindopt(argc, argv);
}

afc::optobj::~optobj()
{
	optbuffer.clear();
	baseaddr = nullptr;
	argc = 0;
	optid = 0;
}

void afc::optobj::bindopt(int argc, char* argv[])
{
	this->argc = argc;
	this->baseaddr = argv;
}

int afc::optobj::procopt(rule* rulelist)
{
	if (optid >= argc) return AFC_OPT_ERROR;
	std::regex normal("^-{1,2}(\\w|-)+");
	std::regex optional("^-{1,2}(\\w|=|-)+");
	std::string temp;
	int i = 0, j = 0;
	bool finded = false;
	optbuffer.clear();
	if (std::regex_match(baseaddr[optid], normal))
	{
		temp = keyname(baseaddr[optid]);
		while (rulelist[i].Name != nullptr)
		{
			if (temp != rulelist[i].Name)
			{
				i++;
				continue;
			}
			optid++;
			if (rulelist[i].ArgNum > 0)
			{
				while (optid < argc && j < rulelist[i].ArgNum && !std::regex_match(baseaddr[optid], optional))
				{
					optbuffer.push_back(baseaddr[optid]);
					j++;
					optid++;
				}
				if (optbuffer.size() < rulelist[i].ArgNum)
				{
					optbuffer.clear();
					return AFC_OPT_NOT_ENOUGH;
				}
			}
			return rulelist[i].RetId;
		}
		if (!finded)
		{
			optid++;
			return AFC_OPT_NOT_FOUND;
		}
	}
	else if (std::regex_match(baseaddr[optid], optional))
	{
		temp = keyname(baseaddr[optid]);
		while (rulelist[i].Name != nullptr)
		{
			if (rulelist[i].ArgNum != AFC_OPT_OPT_ARG || temp != rulelist[i].Name)
			{
				i++;
				continue;
			}
			temp = keyval(baseaddr[optid]);
			if (!temp.empty()) optbuffer.push_back(temp);
			optid++;
			return rulelist[i].RetId;
		}
		if (!finded) return AFC_OPT_NOT_FOUND;
	}
	else
	{
		optbuffer.push_back(baseaddr[optid]);
		optid++;
		return 0;
	}
	return -1;
}

bool afc::optobj::getopt(char* buffer, int bufsize)
{
	if (optbuffer.empty()) return false;
	if (bufsize <= optbuffer.front().size()) return false;
	strcpy(buffer, optbuffer.front().c_str());
	buffer[optbuffer.front().size()] = 0;
	optbuffer.erase(optbuffer.begin());
	return true;
}

bool afc::optobj::getopt(std::string& buffer)
{
	if (optbuffer.empty()) return false;
	buffer = optbuffer.front();
	optbuffer.erase(optbuffer.begin());
	return true;
}

void afc::optobj::clear()
{
	optbuffer.clear();
	optid = 1;
}
