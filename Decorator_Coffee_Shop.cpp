#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

class Coffee
{
public:
    virtual std::string getDescription() = 0;
    virtual float getPrice() = 0;
};

class BasicCoffee: public Coffee
{
public:
    std::string getDescription() override
    {
        return "Basic Coffee";
    }
    float getPrice()
    {
        return 1;
    }
};


class CoffeeDecorator : public Coffee{
public:
    CoffeeDecorator(std::shared_ptr<Coffee> coffee): m_coffee(coffee){}
    std::string getDescription()
    {
        return m_coffee->getDescription();
    }

    float getPrice()
    {
        return m_coffee->getPrice();
    }
protected:
    // This m_coffee is basically responsible for CHAINING,
    std::shared_ptr<Coffee> m_coffee;
};

class MilkDecorator: public CoffeeDecorator
{
public:
    MilkDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee){}
    std::string getDescription()
    {
        return m_coffee->getDescription() + ", Milk";
    }

    float getPrice()
    {
        return m_coffee->getPrice() + 0.5;
    }
};

class SugarDecorator: public CoffeeDecorator
{
public:
    SugarDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee){}
    std::string getDescription()
    {
        return m_coffee->getDescription() + ", Sugar";
    }

    float getPrice()
    {
        return m_coffee->getPrice() + 0.5;
    }
};

class WhippedCreamDecorator: public CoffeeDecorator
{
public:
    WhippedCreamDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee){}
    std::string getDescription()
    {
        return m_coffee->getDescription() + ", WhippedCreamDecorator";
    }

    float getPrice()
    {
        return m_coffee->getPrice() + 0.5;
    }
};


int main()
{
    std::shared_ptr<Coffee> my_coffee = std::make_shared<BasicCoffee>();
    std::cout << "Coffe Description: " << my_coffee->getDescription() << ",\t\t\t\t\tPrice: " << my_coffee->getPrice() << "\n";

    my_coffee = std::make_shared<MilkDecorator>(my_coffee);
    std::cout << "Coffe Description: " << my_coffee->getDescription() << ",\t\t\t\t\tPrice: " << my_coffee->getPrice() << "\n";

    my_coffee = std::make_shared<SugarDecorator>(my_coffee);
    std::cout << "Coffe Description: " << my_coffee->getDescription() << ",\t\t\t\tPrice: " << my_coffee->getPrice() << "\n";

    my_coffee = std::make_shared<WhippedCreamDecorator>(my_coffee);
    std::cout << "Coffe Description: " << my_coffee->getDescription() << ",\tPrice: " << my_coffee->getPrice() << "\n";
}
