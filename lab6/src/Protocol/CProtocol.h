#include "../stdafx.h"

enum class CProtocol
{
    HTTP,
    HTTPS
};

extern std::unordered_map<CProtocol, std::string> protocolToStringMap;
extern std::unordered_map<std::string, CProtocol> protocolsString;
extern std::unordered_map<CProtocol, unsigned short> protocolsDefaultPort;
