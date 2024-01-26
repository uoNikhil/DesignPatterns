#include<iostream>
#include<memory>
#include<string>

/**
 * Here
 * Implementation : device
 *      Concrete Implementation : TV, Radio
 * Abstraction : Remote
*/


class device{
public:
    virtual ~device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setChannel(int) = 0;
    virtual void addFavourite(int) = 0;
    virtual void mute() = 0;
    virtual void setVolume(int) = 0;
    virtual bool getState() = 0;
};

class TV : public device
{
public:
    TV(): m_name("TV"), m_state(false){}
    void turnOn()
    {
        std::cout << m_name << ": Turning ON\n";
        m_state = true;
    }
    void turnOff()
    {
        std::cout << m_name << ": Turning OFF\n";
        m_state = false;
    }
    void setChannel(int channel)
    {
        std::cout << m_name << ": Changing channel to " << channel << "\n";
        m_channel = channel;
    }
    void addFavourite(int channel)
    {
        std::cout << m_name << ": Adding " << channel << " to Favourites\n";
        // Assume you have a vector of favorites you add channel to it
    }
    void mute()
    {
        std::cout << m_name << ": Putting on Mute\n";
        m_volume = 0;
    }

    void setVolume(int vol)
    {
        std::cout << m_name << ": Setting Volume to \n" << vol;
        m_volume = vol;
    }

    bool getState()
    {
        return m_state;
    }
private:
    int m_volume;
    int m_channel;
    std::string m_name;
    bool m_state;
};

class Radio : public device
{
public:
    Radio(): m_name("Radio"), m_state(false){}
    void turnOn()
    {
        std::cout << m_name << ": Turning ON\n";
        m_state = true;
    }
    void turnOff()
    {
        std::cout << m_name << ": Turning OFF\n";
        m_state = false;
    }
    void setChannel(int channel)
    {
        std::cout << m_name << ": Changing channel to " << channel << "\n";
        m_channel = channel;
    }
    void addFavourite(int channel)
    {
    }
    void mute()
    {
        std::cout << m_name << ": Putting on Mute\n";
        m_volume = 0;
    }

    void setVolume(int vol)
    {
        std::cout << m_name << ": Setting Volume to \n" << vol;
        m_volume = vol;
    }
    bool getState()
    {
        return m_state;
    }
private:
    int m_volume;
    int m_channel;
    std::string m_name;
    bool m_state;
};


class Remote{
public:
    Remote(std::shared_ptr<device> dev) : m_device(dev){}
    void togglePower()
    {
        if (m_device->getState())
            m_device->turnOff();
        else
            m_device->turnOn();
    }
    void setChannel(int channel)
    {
        m_device->setChannel(channel);
    }
    std::shared_ptr<device> getDevice()
    {
        return m_device;
    }
protected:
    std::shared_ptr<device> m_device;
};

class AdvancedRemote: public Remote
{
public:
    AdvancedRemote(std::shared_ptr<device> dev) : Remote(dev){}
    void addFavourite(int channel)
    {
        getDevice()->addFavourite(channel);        
    }
    void mute()
    {
        getDevice()->mute();
    }
    void setVolume(int Volume)
    {
        getDevice()->setVolume(Volume);
    }
};

int main()
{
    Remote basic_remote(std::make_shared<Radio>());
    AdvancedRemote advanced_remote(std::make_shared<TV>());
    
    basic_remote.togglePower();
    advanced_remote.mute();
}