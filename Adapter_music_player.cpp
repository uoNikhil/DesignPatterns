#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <algorithm>

// For OLD lagacy System:: incapable of handling any other format other than .mp3
std::string FileNameExtentionRemoverMP3(std::string file)
{
    size_t pos = file.find_last_of(".mp3");
    if (pos == std::string::npos)
    {
        return "ERROR";
    }
    else
    {
        return file.substr(pos);
    }
}

// For newer System: capable of playing any file
std::string FileNameExtentionRemover(std::string file)
{
    size_t pos = file.find_last_of(".");
    if (pos == std::string::npos)
    {
        return "ERROR";
    }
    else
    {
        return file.substr(pos);
    }
}


class LagacyMediaPlayer
{
public: 
    LagacyMediaPlayer():m_player_name("Lagacy Media Player") {};

    // Old lagacy system: o/p is stringstream : i/p is only .mp3 file
    std::stringstream playMP3(std::string file)
    {
        std::string file_name = FileNameExtentionRemoverMP3(file);
        std::stringstream ss;
        if (file_name == "ERROR")
            return ss;
        
        ss << m_player_name << ": Playing file - " << file << std::endl;
        return ss;
    }
private:
    std::string m_player_name;
};

class NewMediaPlayer
{
public: 
    // New system: i/p is string : i/p can be any extention file
    NewMediaPlayer():m_player_name("New Media Player") {}
    virtual std::string play(std::string file)
    {
        std::string file_name = FileNameExtentionRemover(file);
        if (file_name == "ERROR")
            return "ERROR\n";
        
        return m_player_name + ": Playing file - " + file + "\n";
    }
private:
    std::string m_player_name;
};


class adapter: public NewMediaPlayer
{
public:
    adapter(): m_adaptee(std::make_shared<LagacyMediaPlayer>()){}
    std::string play(std::string file) override
    {
        /**
         * Need to FIX I/P mismatch - OLD system needs .mp3, New can work with anything
         * Need to FIX O/P mismatch - OLD system return stringstream, NEW system return string
        */

       // I/P mismatch fix
       size_t pos = file.find_last_of(".mp3");
       if (pos == std::string::npos)
            return "ERROR: Lagacy System only works with .mp3 file\n";
        
        std::stringstream ss;
        ss << "Adapter: ";
        ss << m_adaptee->playMP3(file).str();

        // O/P mismatch fix
        return ss.str();    
    }
private:
    std::shared_ptr<LagacyMediaPlayer> m_adaptee;
};

int main()
{
    adapter myadapter;
    NewMediaPlayer myplayer;
    std::cout << myadapter.play("mysong.mp3");
    std::cout << myplayer.play("my_song.mp4");
}