#ifndef CHTTPURL_H
#define CHTTPURL_H

#include "CHttpUrl.h"

static const std::string PATTERN_TO_URL = R"(([^:/]+)://([^/:]+)(?::(\d+))?/?(.*)$)";
static const int PORT_MIN = 1;
static const int PORT_MAX = 65535;

CHttpUrl::CHttpUrl(const std::string &url)
{
    std::regex pattern(PATTERN_TO_URL, std::regex_constants::icase);
    std::smatch matches;

    bool isMatched;
    try
    {
        isMatched = std::regex_match(url, matches, pattern);
    }
    catch (const std::exception &e)
    {
        throw CUrlParsingError("Invalid url");
    }

    if (!isMatched)
    {
        throw CUrlParsingError("Invalid url");
    }

    CProtocol protocol;
    ParseProtocol(matches[1], protocol);

    std::string domain;
    ParseDomain(matches[2], domain);

    unsigned short port;
    ParsePort(matches[3], protocol, port);

    std::string document;
    ParseDocument(matches[4], document);

    m_protocol = protocol;
    m_domain = domain;
    m_port = port;
    m_document = document;

    if(m_port == protocolsDefaultPort.at(CProtocol::HTTP) || m_port == protocolsDefaultPort.at(CProtocol::HTTPS))
    {
        if(m_document.empty())
        {
            m_url = protocolToStringMap.at(m_protocol) + SEPARATOR_URL_PROTOCOL + m_domain;
            return;
        }
        m_url = protocolToStringMap.at(m_protocol) + SEPARATOR_URL_PROTOCOL + m_domain + m_document;
        return;
    }

    if(m_document.empty())
    {
        m_url = protocolToStringMap.at(m_protocol) + SEPARATOR_URL_PROTOCOL + m_domain + SEPARATOR_URL_PORT + std::to_string(m_port);
        return;
    }

    m_url = protocolToStringMap.at(m_protocol) + SEPARATOR_URL_PROTOCOL + m_domain
            + SEPARATOR_URL_PORT + std::to_string(m_port) + m_document;
}

CHttpUrl::CHttpUrl(const std::string &domain, const std::string &document, CProtocol protocol)
{
    CheckValidDomain(domain);

    m_domain = domain;
    m_document = document;
    if (document.empty())
    {
        m_document = SEPARATOR_URL;
    }

    m_protocol = protocol;
    m_port = protocolsDefaultPort.at(protocol);

    m_url = protocolToStringMap.at(protocol) + SEPARATOR_URL_PROTOCOL + domain + m_document;
}

CHttpUrl::CHttpUrl(const std::string &domain, const std::string &document, CProtocol protocol, unsigned short port)
{
    CheckValidDomain(domain);
    CheckValidPort(port);

    m_domain = domain;
    m_document = document;
    if (document.empty())
    {
        m_document = SEPARATOR_URL;
    }
    m_protocol = protocol;
    m_port = port;

    m_url =
            protocolToStringMap.at(protocol) + SEPARATOR_URL_PROTOCOL + domain
            + SEPARATOR_URL_PORT + std::to_string(m_port) + m_document;
}

std::string CHttpUrl::GetURL() const
{
    return m_url;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}

CProtocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

void CHttpUrl::ParseProtocol(const std::string &protocolParsed, CProtocol &protocol)
{
    std::string protocolParsedCopy = protocolParsed;

    std::transform(protocolParsedCopy.begin(), protocolParsedCopy.end(), protocolParsedCopy.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    CheckValidProtocol(protocolParsedCopy);

    protocol = protocolsString[protocolParsedCopy];
}

void CHttpUrl::ParseDomain(const std::string &hostParsed, std::string &domain)
{
    CheckValidDomain(hostParsed);

    domain = hostParsed;
}

void CHttpUrl::ParsePort(const std::string &portParsed, CProtocol &protocol, unsigned short &port)
{
    if (portParsed.empty() && protocolsDefaultPort.find(protocol) != protocolsDefaultPort.end())
    {
        port = protocolsDefaultPort[protocol];
        return;
    }

    try
    {
        int portParsedInt = std::stoi(portParsed);
        CheckValidPort(portParsedInt);

        port = portParsedInt;
    }
    catch(const std::exception &e)
    {
        throw std::invalid_argument("Invalid port");
    }
}

void CHttpUrl::ParseDocument(const std::string &parsedDocument, std::string &document)
{
    document += parsedDocument;
}

void CHttpUrl::CheckValidProtocol(const std::string &protocol)
{
    if (protocolsString.find(protocol) == protocolsString.end())
    {
        throw std::invalid_argument("Invalid protocol");
    }
}

void CHttpUrl::CheckValidDomain(const std::string &domain)
{
    if (domain.empty())
    {
        throw std::invalid_argument("Invalid domain");
    }
}

void CHttpUrl::CheckValidPort(int port)
{
    if (port < PORT_MIN || port > PORT_MAX)
    {
        throw std::invalid_argument("Invalid port");
    }
}

#endif // CHTTPURL_H