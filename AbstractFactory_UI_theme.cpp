#include <iostream>
#include <string>
#include <memory>

class Button{
public:
    virtual ~Button() = default;
    virtual void onPress() = 0;
};

class CheckBox{
public:
    virtual ~CheckBox() = default;
    virtual void onCheck() = 0;
};



class LightButton: public Button{
public:
    
    void onPress() override
    {
        std::cout << "Pressed Light Button\n";
    }
};

class DarkButton: public Button{
public:
    
    void onPress() override
    {
        std::cout << "Pressed Dark Button\n";
    }
};

class LightCheckBox: public CheckBox{
public:
    
    void onCheck() override
    {
        std::cout << "Checked Light CheckBox\n";
    }
};

class DarkCheckBox: public CheckBox{
public:
    
    void onCheck() override
    {
        std::cout << "Checked Dark CheckBox\n";
    }
};


class GUIFactory
{
public:
    virtual ~GUIFactory() = default;
    virtual std::shared_ptr<Button> CreateButton() = 0;
    virtual std::shared_ptr<CheckBox> CreateCheckbox() = 0;
};

class LightFactory: public GUIFactory
{
public:
    std::shared_ptr<Button> CreateButton()
    {
        return std::make_shared<LightButton>();
    }
    std::shared_ptr<CheckBox> CreateCheckbox()
    {
        return std::make_shared<LightCheckBox>();
    }
};


class DarkFactory: public GUIFactory
{
public:
    std::shared_ptr<Button> CreateButton()
    {
        return std::make_shared<DarkButton>();
    }
    std::shared_ptr<CheckBox> CreateCheckbox()
    {
        return std::make_shared<DarkCheckBox>();
    }
};

int main()
{
    std::shared_ptr<GUIFactory> light_factory = std::make_shared<LightFactory>();
    auto lbutton = light_factory->CreateButton();
    auto lcheckbox = light_factory->CreateCheckbox();
    lbutton->onPress();
    lcheckbox->onCheck();


    std::shared_ptr<GUIFactory> dark_factory = std::make_shared<DarkFactory>();
    auto dbutton = dark_factory->CreateButton();
    auto dcheckbox = dark_factory->CreateCheckbox();
    dbutton->onPress();
    dcheckbox->onCheck();
    
    
}