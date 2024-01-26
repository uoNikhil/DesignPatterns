#include <iostream>
#include <string>

class CPU {
public:
    void freeze() { std::cout << "CPU freeze.\n"; }
    void jump(long position) { std::cout << "CPU jump to " << position << ".\n"; }
    void execute() { std::cout << "CPU execute.\n"; }
};

class Memory {
public:
    void load(long position, const std::string& data) { 
        std::cout << "Memory load \"" << data << "\" at " << position << ".\n"; 
    }
};

class HardDrive {
public:
    std::string read(long lba, int size) { 
        return "Some data from sector " + std::to_string(lba); 
    }
};


class ComputerFacade {
    CPU processor;
    Memory ram;
    HardDrive hd;

public:
    void start() {
        processor.freeze();
        ram.load(BOOT_ADDRESS, hd.read(BOOT_SECTOR, SECTOR_SIZE));
        processor.jump(BOOT_ADDRESS);
        processor.execute();
    }

private:
    static const long BOOT_ADDRESS = 0x00000000;
    static const long BOOT_SECTOR = 0x00000001;
    static const int SECTOR_SIZE = 1024;
};


int main() {
    ComputerFacade computer;
    computer.start(); // Simplified interface

    return 0;
}
