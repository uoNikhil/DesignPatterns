#include<iostream>
#include<string>
#include<memory>
#include<queue>


//INTERFACE CLASS
class Command{
public:
    virtual void execute() = 0;
};

//CONCRETE CLASSES
class OnCommand: public Command
{
public:
    void execute() override{
        std::cout << "\t\tCommad: Turing On\n";
    }

};

class OffCommand: public Command
{
public:
    void execute() override{
        std::cout << "\t\tCommand: Turing Off\n";
    }

};

//INVOKER CLASS
class Remote{
private:
    std::shared_ptr<OnCommand> m_on_command;
    std::shared_ptr<OffCommand> m_off_command;
    std::queue<std::shared_ptr<Command>> m_queue;
    
public:
    Remote(std::shared_ptr<OnCommand> on_command,std::shared_ptr<OffCommand> off_command) : m_on_command(on_command), m_off_command(off_command){}

    void TurnOn()
    {
        std::cout << "\tRemote Controller: Turn on executing instantly \n"; 
        m_on_command->execute();
    }
    void TurnOff()
    {
        std::cout << "\tRemote Controller: Turn off executing instantly \n"; 
        m_off_command->execute();
    }

    void addCommand(std::shared_ptr<Command> command)
    {
        m_queue.push(command);
        std::cout<< "\tRemote Controller: Command Queued Successfully\n";
    }

    void executeCommands()
    {
        std::queue<std::shared_ptr<Command>> temp ;
        m_queue.swap(temp);
        while(!temp.empty())
        {
            auto command = temp.front();
            command->execute();
            temp.pop();
        }

    }

};

// CLIENT Code
int main()
{
    auto on_command = std::make_shared<OnCommand>();
    auto off_command = std::make_shared<OffCommand>();

    auto remote = std::make_shared<Remote>(on_command, off_command);

    std::cout << "CLIENT: executing instant commands\n";
    remote->TurnOn();
    remote->TurnOff();

    std::cout << "CLIENT: queuing commands\n";
    remote->addCommand(on_command);
    remote->addCommand(off_command);
    std::cout << "CLIENT: executing queued commands\n";
    remote->executeCommands();
}