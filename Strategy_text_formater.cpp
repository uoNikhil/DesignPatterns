#include <iostream>
#include <vector>
#include <memory>
#include <string>

class TextFormater
{
public:
    virtual ~TextFormater() = default;
    virtual std::string Format(std::string text) = 0;
};



class PlainTextFormater: public TextFormater
{
public:
    std::string Format(std::string text) override
    {
        m_text = text;
        return m_text;
    }
private:
    std::string m_text;
};

class MarkdownFormater: public TextFormater
{
public:
    std::string Format(std::string text) override
    {
        m_text = "**" + text + "**";
        return m_text;
    }
private:
    std::string m_text;
};

class HTMLFormater: public TextFormater
{
public:
    std::string Format(std::string text) override
    {
        m_text = "<html><body><p>" + text + "</p></body></html>";
        return m_text;
    }
private:
    std::string m_text;
};

class TextEditor
{
public:
    TextEditor(std::shared_ptr<TextFormater> formater = NULL)
    {
        if (formater == NULL)
            m_formater = std::make_shared<PlainTextFormater>();
        else
            m_formater = formater;
    }
    void setFormater(std::shared_ptr<TextFormater> formater)
    {
        if (formater == NULL)
            return;
        m_formater = formater;
    }

    void publish(std::string str)
    {
        std::cout << m_formater->Format(str) << std::endl;
    }

private:
    std::shared_ptr<TextFormater> m_formater;
};

int main()
{
    std::shared_ptr<TextEditor> editor = std::make_shared<TextEditor>();
    
    editor->publish("Publishing for Plain Text");

    editor->setFormater(std::make_shared<MarkdownFormater>());
    editor->publish("Publishing for Markdown Text Format");

    editor->setFormater(std::make_shared<HTMLFormater>());
    editor->publish("Publishing for HTML Text Format");
}