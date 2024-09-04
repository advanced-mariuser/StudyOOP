#include "CParserUrlHandler.h"

void CParserUrlHandler::ParseUrls()
{
    std::string encodeHTML;
    while(std::getline(std::cin, encodeHTML))
    {
        if (encodeHTML.empty()) {
            break;
        }

        try {
            CHttpUrl cHttpUrl{encodeHTML};

            std::cout << "Url: " << cHttpUrl.GetURL() << "\n"
                      << "Protocol: "<<  protocolToStringMap.at(cHttpUrl.GetProtocol())  << "\n"
                      << "Domain: "<<  cHttpUrl.GetDomain()  << "\n"
                      << "Port: "<<  cHttpUrl.GetPort()  << "\n"
                      << "Document: "<<  cHttpUrl.GetDocument()  << "\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}