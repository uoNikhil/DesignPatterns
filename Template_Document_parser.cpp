#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <tinyxml2.h>
#include <nlohmann/json.hpp>

/**
 * Library Installations
 * sudo apt install libtinyxml2-dev
 * sudo apt install nlohmann-json3-dev
 * 
 * Building this file: 
 * nlohmann-json being a header-only library simplifies its usage - you don't need to worry about linking against a binary. 
 * Just including the header file is enough for the compiler to find and compile all the necessary code. 
 * command:
 * g++ -o templ Template_Document_parser.cpp -ltinyxml2
*/


using json = nlohmann::json;
using namespace tinyxml2;

class DocumentParser{
public:
    void parseDocument(const std::string& text){
        Preprocess();
        TypeSpecificProcess(text);
        Postprocess();
    }

protected:
    void Preprocess()
    {
        std::cout << "Pre-Processing Step\n";
    }
    virtual void TypeSpecificProcess(const std::string& text) = 0;
    void Postprocess()
    {
        std::cout << "Post-Processing Step\n";
    }
};

class XMLParser : public DocumentParser
{
protected:
    void TypeSpecificProcess(const std::string& text) override{
        tinyxml2::XMLDocument doc;
        doc.Parse(text.c_str());
        // Process the XML document
        tinyxml2::XMLElement* element = doc.FirstChildElement();
        if (element != nullptr) {
            std::cout << "Root element: " << element->Name() << std::endl;
        }
    }
};

class JsonParser : public DocumentParser
{
protected:
    void TypeSpecificProcess(const std::string& text) override{
        auto parsed = nlohmann::json::parse(text);
        // Process the JSON object
        std::cout << "Parsed JSON: " << parsed.dump(4) << std::endl;
    }
};

class Document{
public:
    Document(std::shared_ptr<DocumentParser> parser): m_parser(parser){}

    void Parse(std::string text)
    {
        m_parser->parseDocument(text);
    }

private:
    std::shared_ptr<DocumentParser> m_parser;
};

int main()
{
    std::string xmlContent = "<root><child>Hello XML</child></root>";
    std::string jsonContent = R"({"key": "Hello JSON"})";

    auto xmlDoc = std::make_shared<Document>(std::make_shared<XMLParser>());
    auto jsonDoc = std::make_shared<Document>(std::make_shared<JsonParser>());

    std::cout << "\t\tProcessing XML\n";
    xmlDoc->Parse(xmlContent);
    std::cout << "\t\tProcessing JSON\n";
    jsonDoc->Parse(jsonContent); 
}