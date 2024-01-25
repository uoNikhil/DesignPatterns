#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

class Visitor;

class Product : public std::enable_shared_from_this<Product>
{
private:
    int m_quantity;
    int m_price;
    std::string m_name;
public:
    virtual ~Product() = default;
    virtual void accept(std::shared_ptr<Visitor> visitor) = 0;
    int getQuantity()
    {
        return m_quantity;
    }
    void setQuantity(int quantity)
    {
        m_quantity = quantity;
    }
    int getPrice()
    {
        return m_price;
    }
    void setPrice(int price)
    {
        m_price = price;
    }
    std::string getName()
    {
        return m_name;
    }
    void setName(std::string name)
    {
        m_name = name;
    }
};

class Laptop : public Product
{
public:
    Laptop(int quantity = 0)
    {
        setQuantity(quantity);
        setPrice(1000);
        setName("Laptop");
    }
    void accept(std::shared_ptr<Visitor> visitor) override;
};

class Phone : public Product
{
public:
    Phone(int quantity = 0)
    {
        setQuantity(quantity);
        setPrice(500);
        setName("Phone");
    }
    void accept(std::shared_ptr<Visitor> visitor) override;

};
class Tablet : public Product
{
public:
    Tablet(int quantity = 0)
    {
        setQuantity(quantity);
        setPrice(700);
        setName("Tablet");
    }
    void accept(std::shared_ptr<Visitor> visitor) override;

};

class Invetory
{
public:
    void addProduct(std::shared_ptr<Product> product)
    {
        m_prods.emplace_back(std::move(product));
    }

    void apply(std::shared_ptr<Visitor> visitor)
    {
        for (auto product : m_prods)
        {
            product->accept(visitor);
        }
    }

    void getAllQuantities()
    {
        std::stringstream ss;

        for (auto product : m_prods)
        {
            ss << "{Name=" << product->getName() << ": Quantity=" << product->getQuantity() << "} ";
        }
        ss << "\n";
        std::cout << ss.str();
    }

private:
    std::vector<std::shared_ptr<Product>> m_prods;
};

class Visitor
{
public:
    virtual void visitLaptop(std::shared_ptr<Product>) = 0;
    virtual void visitPhone(std::shared_ptr<Product>) = 0;
    virtual void visitTablet(std::shared_ptr<Product>) = 0;
};

class TotalPrice: public Visitor
{
public:
    TotalPrice(): m_total_price(0){}
    void visitLaptop(std::shared_ptr<Product> prod) override
    {
        m_total_price += prod->getPrice()*prod->getQuantity();
    }
    void visitPhone(std::shared_ptr<Product> prod) override
    {
        m_total_price += prod->getPrice()*prod->getQuantity();
    }
    void visitTablet(std::shared_ptr<Product> prod) override
    {
        m_total_price += prod->getPrice()*prod->getQuantity();
    }
    void GetTotal()
    {
        std::cout << "Total Price = " << m_total_price << std::endl;
    }
private:
    int m_total_price;
};

class StockManagement: public Visitor
{
public:
    void visitLaptop(std::shared_ptr<Product> prod) override
    {
        prod->setQuantity(prod->getQuantity() -1);
    }
    void visitPhone(std::shared_ptr<Product> prod) override
    {
        prod->setQuantity(prod->getQuantity() -1);
    }
    void visitTablet(std::shared_ptr<Product> prod) override
    {
        prod->setQuantity(prod->getQuantity() -1);
    }
};

void Laptop::accept(std::shared_ptr<Visitor> visitor)
{
        visitor->visitLaptop(shared_from_this());
}
void Phone::accept(std::shared_ptr<Visitor> visitor)
{
        visitor->visitPhone(shared_from_this());
}
void Tablet::accept(std::shared_ptr<Visitor> visitor)
{
        visitor->visitTablet(shared_from_this());
}


int main()
{
    Invetory inventory;
    inventory.addProduct(std::make_shared<Laptop>(10));
    inventory.addProduct(std::make_shared<Phone>(5));
    inventory.addProduct(std::make_shared<Tablet>(1));

    std::shared_ptr<TotalPrice> price_visitor = std::make_shared<TotalPrice>();
    std::shared_ptr<StockManagement> stk_mgt = std::make_shared<StockManagement>(); 

    inventory.apply(price_visitor);
    price_visitor->GetTotal();

    inventory.getAllQuantities();
    inventory.apply(stk_mgt);
    inventory.getAllQuantities();

}