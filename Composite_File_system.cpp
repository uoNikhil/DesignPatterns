#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

class FileSystemCompoent
{
public:
    virtual ~FileSystemCompoent() = default;
    FileSystemCompoent(std::string type = "FSComponent"): m_type(type){};
    virtual void addComponent(std::shared_ptr<FileSystemCompoent> component){
        std::cout << "Error: Can't add Copoenent of type " << component->getType() << " to Compoenent of type " << this->getType();
    }
    std::string getType()
    {
        return m_type;
    }
    virtual void list()
    {
        std::cout << "Error: Can't List under Compoenent of type " << this->getType() << "\n";
    }
    virtual std::string getName() = 0;

protected:
    std::string m_type;
};

class File : public FileSystemCompoent
{
public:
    File(std::string name): FileSystemCompoent("File"){
        m_name = name;
    }
    void Write(std::string data)
    {
        m_data += data;
    }
    std::string Read()
    {
        return m_data;
    }

    std::string getName()
    {
        return m_name;
    }
private:
    std::string m_name;
    std::string m_data;
};


class Directory : public FileSystemCompoent
{
public:
    Directory(std::string name): FileSystemCompoent("Directory")
    {
        m_name = name;
    }

    /**
    
    }
    virtual void list()
    {
        std::cout << "Error: Can't List under Compoenent of type " << this->getName();
    }
    */

   void addComponent(std::shared_ptr<FileSystemCompoent> component) override
   {
        for (auto comp : m_components)
        {
            if (comp->getName() == component->getName() && comp->getType() == component->getType())
            {
                std::cout << "ERROR: Component Named " << component->getName() << " Already EXISTS !!\n";
                return;
            }
        }
        m_components.emplace_back(component);
   }
    std::string getName()
    {
        return m_name;
    }
    void list() override{
        std::stringstream ss;
        for (auto component : m_components)
        {
            ss << "Compoenet Name: " << component->getName() << "\t\tComponent Type: " << component->getType() << "\n";
        }
        std::cout << ss.str();
    }

private:
    std::string m_name;
    std::vector<std::shared_ptr<FileSystemCompoent>> m_components;
};


int main()
{
    std::shared_ptr<Directory> root = std::make_shared<Directory>("root");
    
    std::shared_ptr<Directory> folder1 = std::make_shared<Directory>("folder1");
    std::shared_ptr<Directory> folder2 = std::make_shared<Directory>("folder2");
    std::shared_ptr<Directory> folder3 = std::make_shared<Directory>("folder3");
    std::shared_ptr<Directory> folder4 = std::make_shared<Directory>("folder4");
    
    std::shared_ptr<File> file1 = std::make_shared<File>("file1");
    std::shared_ptr<File> file2 = std::make_shared<File>("file2");
    std::shared_ptr<File> file3 = std::make_shared<File>("file3");

    root->addComponent(folder1);
    root->addComponent(folder2);
    root->addComponent(file2);

    folder1->addComponent(folder3);
    folder1->addComponent(file3);

    folder2->addComponent(folder4);

    folder3->addComponent(file3);

    std::cout << "\t\tCommand: ls root\n";
    root->list();
    std::cout << "\t\tCommand: ls folder1\n";
    folder1->list();
    std::cout << "\t\tCommand: ls folder2\n";
    folder2->list();
    std::cout << "\t\tCommand: ls file1\n";
    file1->list();
}