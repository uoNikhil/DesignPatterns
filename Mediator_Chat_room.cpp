#include <iostream>
#include <string>
#include <memory>
#include <vector>



class Participant;
class ChatRoomMediator : public std::enable_shared_from_this<ChatRoomMediator>
{
public:
    virtual void OnSend(std::string msg, std::shared_ptr<Participant> user) = 0;
    virtual void RegisterUser(std::shared_ptr<Participant> usesr) = 0;

};


class Participant : public std::enable_shared_from_this<Participant>
{
public:
    Participant(std::string name, std::shared_ptr<ChatRoomMediator> room) : m_name(name), m_room(room)
    {
    }

    void send(std::string msg)
    {
        std::cout << m_name << ": Send : " << msg << std::endl;
        m_room->OnSend(msg, shared_from_this());
    }

    void receive(std::string msg)
    {
        std::cout << m_name << ": Receive : " << msg << std::endl;
    }

    std::string getName()
    {
        return m_name;
    }

private:
    std::string m_name;
    std::shared_ptr<ChatRoomMediator> m_room;
};




class ChatRoom: public ChatRoomMediator
{
public:
    ChatRoom()
    {
        m_count++;
        m_name = "Group" + std::to_string(m_count);   
    }
    void OnSend(std::string msg, std::shared_ptr<Participant> user) override
    {
        for (auto participant : m_participants)
        {
            if (participant != user)
            {
                participant->receive(msg);
            }
        }
    }

    void RegisterUser(std::shared_ptr<Participant> participant) override
    {
        std::cout << "Register User = " << participant->getName() << " to Room = " << m_name << std::endl;
        m_participants.emplace_back(participant);
    }

private:
    static int m_count;
    std::string m_name;
    std::vector<std::shared_ptr<Participant>> m_participants;

};
int ChatRoom::m_count = 0;

int main()
{
    std::shared_ptr<ChatRoom> grp = std::make_shared<ChatRoom>();
    
    std::shared_ptr<Participant> alice = std::make_shared<Participant>("Alice", grp);
    std::shared_ptr<Participant> bob = std::make_shared<Participant>("Bob", grp);
    std::shared_ptr<Participant> Eve = std::make_shared<Participant>("Eve", grp);


    grp->RegisterUser(alice);
    grp->RegisterUser(bob);
    grp->RegisterUser(Eve);
    alice->send("Hi Bob and Eve");
    
}