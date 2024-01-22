#include <memory>
#include <vector>
#include <string>
#include <iostream>


class Momento{
public:
    explicit Momento(std::string state):m_state(state){}
    std::string getState()
    {
        return m_state;
    }
private:
    std::string m_state;
};


class Editor{
public:
    void write(std::string text)
    {
        m_text += " " + text;
    }
    std::shared_ptr<Momento> save()
    {
        return std::make_shared<Momento>(m_text);
    }
    std::string getText()
    {
        std::cout << "TEXT: ";
        return m_text;
    }

    void setState(std::shared_ptr<Momento> state)
    {
        m_text = state->getState();
    }

private:
    std::string m_text;

};

class CareTaker{
public:
    explicit CareTaker(std::shared_ptr<Editor> editor):m_editor(editor){
        m_history.emplace_back(m_editor->save());
    }

    void save()
    {
        m_history.emplace_back(m_editor->save());
    }

    void undo()
    {
        if (!m_history.empty())
        {
            std::shared_ptr<Momento> temp = m_history.back();
            m_editor->setState(temp);
            m_history.pop_back();
        }
    }

private:
    std::vector<std::shared_ptr<Momento>> m_history;
    std::shared_ptr<Editor> m_editor;
};


int main()
{
    std::shared_ptr<Editor> editor = std::make_shared<Editor>();
    std::shared_ptr<CareTaker> care_taker = std::make_shared<CareTaker>(editor);

    editor->write("Hi this is a sample text.");
    editor->write("Making some more changes before saving.");
    care_taker->save();
    editor->write("Changes after saving-1.");
    editor->write("About to save second time.");
    care_taker->save();
    editor->write("Last edit changes");
    std::cout << "FINAL TEXT = " << editor->getText() << "\n";

    care_taker->undo();
    std::cout << "Text after Undo " << editor->getText() << "\n";
    care_taker->undo();
    std::cout << "Text after Undo " << editor->getText() << "\n";
    care_taker->undo();
    std::cout << "Text after Undo " << editor->getText() << "\n";
    

}