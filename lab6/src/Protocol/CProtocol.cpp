#include "CProtocol.h"

std::unordered_map<CProtocol, std::string> protocolToStringMap = {
        {CProtocol::HTTP, "http"},
        {CProtocol::HTTPS, "https"}
};

std::unordered_map<std::string, CProtocol> protocolsString = {
        {"http", CProtocol::HTTP},
        {"https", CProtocol::HTTPS}
};

std::unordered_map<CProtocol, unsigned short> protocolsDefaultPort = {
        {CProtocol::HTTP, 80},
        {CProtocol::HTTPS, 443}
};