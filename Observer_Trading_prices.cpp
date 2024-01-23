#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class IObserver: public std::enable_shared_from_this<IObserver>
{
public:
    virtual void update(std::string symbol, float price) = 0;
};

class ISubject{
public:
    virtual void RegisterObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void UnregisterObserver(std::shared_ptr<IObserver> observer) = 0;
    virtual void Notify() = 0;
    
};

class Stock: public ISubject
{
public:
    Stock(std::string symbol, float price = 0.0):m_symbol(symbol), m_price(price){}
    void RegisterObserver(std::shared_ptr<IObserver> observer) override
    {
        if (std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end())
            m_observers.emplace_back(observer);
    }

    void UnregisterObserver(std::shared_ptr<IObserver> observer) override
    {
        auto found = std::find(m_observers.begin(), m_observers.end(), observer);
        if (found != m_observers.end())
            m_observers.erase(found);
    }

    void Notify()
    {
        for (auto& observer: m_observers)
        {
            observer->update(m_symbol, m_price);
        }
    }

    void PriceChange(float new_price)
    {
        std::cout << "\t\t" << m_symbol << ": Price Changed from " << m_price << " to " << new_price << std::endl;
        m_price = new_price;
        Notify();
    }


private:
    std::string m_symbol;
    float m_price;
    std::vector<std::shared_ptr<IObserver>> m_observers;
};

class Observer : public IObserver
{
public:
    Observer(std::string name): m_name(name){}
    void update(std::string symbol, float price) override
    {
        std::cout << m_name << ": Price Update Received for Symbol = " << symbol << " | new Price = " << price << "\n";
    }

    void Subscribe(std::shared_ptr<ISubject> stock)
    {
        std::cout << m_name << ": Subscribing to Stock\n";
        stock->RegisterObserver(shared_from_this());
    }

private:
    std::string m_name;
};

int main()
{
    std::shared_ptr<Stock> google = std::make_shared<Stock>("GOOG");
    std::shared_ptr<Stock> apple = std::make_shared<Stock>("AAPL");

    std::shared_ptr<Observer> trader1 = std::make_shared<Observer>("Alice");
    std::shared_ptr<Observer> trader2 = std::make_shared<Observer>("Bob");
    std::shared_ptr<Observer> trader3 = std::make_shared<Observer>("Charlie");

    trader1->Subscribe(google);
    trader1->Subscribe(apple);

    trader2->Subscribe(google);

    trader3->Subscribe(apple);


    google->PriceChange(140.2);
    apple->PriceChange(196.6);
}