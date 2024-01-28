#include <iostream>
#include <string>
#include <memory>

class Image
{
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

class RealImage: public Image
{
public:
    RealImage(std::string filename) : m_name(filename){
        loadFromDisk();
    }
    void loadFromDisk()
    {
        std::cout << "LOADING image from the disk\n";
    }

    void display()
    {
        std::cout << "Displaying the Image\n";
    }
private:
    std::string m_name;
};

class ProxyImage: public Image
{
public:
    ProxyImage(std::string filename) : m_name(filename){}
    void display()
    {
        if (!m_image)
        {
            m_image = std::make_shared<RealImage>(m_name);
        }
        m_image->display();
    }
private:
    std::string m_name;
    std::shared_ptr<RealImage> m_image;
};

int main()
{
    ProxyImage img("my_image");

    img.display();
    img.display();
}