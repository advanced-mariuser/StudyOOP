#include "../stdafx.h"
#include "../Utils.h"
#include "../Protocol/CProtocol.h"
#include "../UrlParsingError/CUrlParsingError.h"

//TODO если при преобразовании порта выбрасывается исключение то надо преобразовать его в Invalid port
class CHttpUrl
{
public:
    // выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    explicit CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
            std::string const& domain,
            std::string const& document,
            CProtocol protocol = CProtocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
            std::string const& domain,
            std::string const& document,
            CProtocol protocol,
            unsigned short port);

    // возвращает строковое представление URL-а. Порт, являющийся стандартным для
    // выбранного протокола (80 для http и 443 для https) в эту строку
    // не должен включаться
    std::string GetURL() const;

    // возвращает доменное имя
    std::string GetDomain() const;

    /*
        Возвращает имя документа. Примеры:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument() const;

    // возвращает тип протокола
    CProtocol GetProtocol() const;

    // возвращает номер порта
    unsigned short GetPort() const;

private:
    std::string m_url;

    std::string m_domain;

    std::string m_document;

    CProtocol m_protocol;

    unsigned short m_port;

    static void ParseProtocol(const std::string &protocolParsed, CProtocol &protocol);

    static void ParseDomain(const std::string &hostParsed, std::string &host);

    static void ParsePort(const std::string &portParsed, CProtocol &protocol, unsigned short &port);

    static void ParseDocument(const std::string &parsedDocument, std::string &document);

    static void CheckValidProtocol(const std::string &protocol);

    static void CheckValidDomain(const std::string &domain);

    static void CheckValidPort(int port);
};