#include <gtest/gtest.h>
#include "../src/HttpUrl/CHttpUrl.h"

TEST (CHttpUrlTests, Construct_Url_Without_Port_Success)
{
    std::string expectedUrl = "https://github.com/alexey-malov/oop/blob/master/tasks/06/README.md";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 443;
    std::string expectedDocument = "/alexey-malov/oop/blob/master/tasks/06/README.md";
    CHttpUrl cHttpUrl{expectedUrl};

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(expectedDocument, cHttpUrl.GetDocument());
}

TEST (CHttpUrlTests, Construct_Url_Without_Port_And_Document_Success)
{
    std::string expectedUrl = "https://github.com/";
    std::string expectedDomain = "github.com";
    CHttpUrl cHttpUrl = CHttpUrl(expectedUrl);

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());

    expectedUrl = "https://github.com";
    cHttpUrl = CHttpUrl(expectedUrl);

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());
}

TEST (CHttpUrlTests, Construct_Url_Without_Domain_Success)
{
    std::string expectedUrl = "https://github.com:8080";
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 8080;
    CHttpUrl cHttpUrl = CHttpUrl(expectedUrl);

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());

    expectedUrl = "https://github.com:8080/";
    cHttpUrl = CHttpUrl(expectedUrl);

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());
}

TEST (CHttpUrlTests, Construct_Url_Empty_Failed)
{
    EXPECT_THROW(CHttpUrl(""), CUrlParsingError);
}

TEST (CHttpUrlTests, Construct_Url_Without_Port_Failed)
{
    EXPECT_THROW(CHttpUrl("htt://github.com/alexey-malov/oop/blob/master/tasks/06/README.md"), std::invalid_argument);
}

TEST (CHttpUrlTests, Construct_Url_Domain_Failed)
{
    EXPECT_THROW(CHttpUrl("https:///alexey-malov/oop/blob/master/tasks/06/README.md"), CUrlParsingError);
}

TEST (CHttpUrlTests, Construct_Url_Port_Failed)
{
    EXPECT_THROW(CHttpUrl("https://github.com:0/alexey-malov/oop/blob/master/tasks/06/README.md"),
                 std::invalid_argument);
    EXPECT_THROW(CHttpUrl("https://github.com:65536/alexey-malov/oop/blob/master/tasks/06/README.md"),
                 std::invalid_argument);
}

TEST (CHttpUrlTests, Construct_Without_Port_Success)
{
    std::string expectedUrl = "https://github.com/alexey-malov/oop/blob/master/tasks/06/README.md";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 443;
    std::string expectedDocument = "/alexey-malov/oop/blob/master/tasks/06/README.md";

    CHttpUrl cHttpUrl{expectedDomain, expectedDocument, expectedProtocol};

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(expectedDocument, cHttpUrl.GetDocument());
}

TEST (CHttpUrlTests, Construct_Url_Without_Port_Without_Document_Success)
{
    std::string expectedUrl = "https://github.com/";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 443;

    CHttpUrl cHttpUrl{expectedDomain, "", expectedProtocol};

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());

    CHttpUrl cHttpUrl2{expectedDomain, "/", expectedProtocol};

    EXPECT_EQ(expectedUrl, cHttpUrl2.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl2.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl2.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl2.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl2.GetDocument());
}

TEST (CHttpUrlTests, Construct_Url_Without_Port_Domain_Failed)
{
    EXPECT_THROW(CHttpUrl("", "/alexey-malov/oop/blob/master/tasks/06/README.md", CProtocol::HTTPS),
                 std::invalid_argument);
}

TEST (CHttpUrlTests, Construct_Url_With_Port_Success)
{
    std::string expectedUrl = "https://github.com:8080/alexey-malov/oop/blob/master/tasks/06/README.md";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 8080;
    std::string expectedDocument = "/alexey-malov/oop/blob/master/tasks/06/README.md";

    CHttpUrl cHttpUrl{expectedDomain, expectedDocument, expectedProtocol, expectedPort};

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(expectedDocument, cHttpUrl.GetDocument());
}

TEST (CHttpUrlTests, Construct_Url_With_Port_Without_document_Success)
{
    std::string expectedUrl = "https://github.com:8080/";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 8080;

    CHttpUrl cHttpUrl{expectedDomain, "", expectedProtocol, expectedPort};

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());

    CHttpUrl cHttpUrl1{expectedDomain, "/", expectedProtocol, expectedPort};

    EXPECT_EQ(expectedUrl, cHttpUrl1.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl1.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl1.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl1.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl1.GetDocument());
}

TEST (CHttpUrlTests, Construct_Url_With_Port_Invalid_Port_Failed)
{
    EXPECT_THROW(CHttpUrl("github.com", "/alexey-malov/oop/blob/master/tasks/06/README.md", CProtocol::HTTPS, 0),
                 std::invalid_argument);
    EXPECT_THROW(
            CHttpUrl(
                    "github.com",
                    "/alexey-malov/oop/blob/master/tasks/06/README.md",
                    CProtocol::HTTPS,
                    static_cast<unsigned short>(65536)
            ),
            std::invalid_argument
    );
}

TEST (CHttpUrlTests, Construct_Url_With_Port_Invalid_Domain_Failed)
{
    EXPECT_THROW(CHttpUrl("", "/alexey-malov/oop/blob/master/tasks/06/README.md", CProtocol::HTTPS, 8080),
                 std::invalid_argument);
}

TEST (CHttpUrlTest, Construct_With_Invalid_Port_Less)
{
    EXPECT_THROW(CHttpUrl("https://github.com:0/"),
                 std::invalid_argument);
}

TEST (CHttpUrlTest, Construct_With_Invalid_Port_Bigger)
{
    EXPECT_THROW(CHttpUrl("https://github.com:65536/"),
                 std::invalid_argument);
}

TEST (CHttpUrlTest, Construct_With_Invalid_Port_Larger_Limit_Value)
{
    std::string expectedUrl = "https://github.com:65535/";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 65535;

    CHttpUrl cHttpUrl{expectedDomain, "", expectedProtocol, expectedPort};

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());
}

TEST (CHttpUrlTest, Construct_With_Invalid_Port_Lower_Boundary_Value)
{
    std::string expectedUrl = "https://github.com:1";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 1;

    CHttpUrl cHttpUrl{expectedDomain, "", expectedProtocol, expectedPort};

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());
}

TEST (CHttpUrlTest, Construct_With_Valid_Non_Register_Protocol)
{
    std::string expectedUrl = "https://github.com:1";
    CProtocol expectedProtocol = CProtocol::HTTPS;
    std::string expectedDomain = "github.com";
    unsigned short expectedPort = 1;

    CHttpUrl cHttpUrl("HttPS://github.com:1");

    EXPECT_EQ(expectedUrl, cHttpUrl.GetURL());
    EXPECT_EQ(expectedProtocol, cHttpUrl.GetProtocol());
    EXPECT_EQ(expectedDomain, cHttpUrl.GetDomain());
    EXPECT_EQ(expectedPort, cHttpUrl.GetPort());
    EXPECT_EQ(SEPARATOR_URL, cHttpUrl.GetDocument());
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}