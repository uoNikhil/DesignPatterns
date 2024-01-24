#include<iostream>
#include<string>
#include<vector>
#include<memory>

class Connection;

class IConnectionState
{
public:
    virtual ~IConnectionState() = default;
    virtual void Open(std::shared_ptr<Connection> Connection) = 0;
    virtual void Close(std::shared_ptr<Connection> Connection) = 0;
    virtual void Reset(std::shared_ptr<Connection> Connection) = 0;
};

class OpenConnection : public IConnectionState
{
public:
    void Open(std::shared_ptr<Connection> Connection) override;
    void Close(std::shared_ptr<Connection> Connection) override;
    void Reset(std::shared_ptr<Connection> Connection) override;
};

class InUseConnection : public IConnectionState
{
public:
    void Open(std::shared_ptr<Connection> Connection) override;
    void Close(std::shared_ptr<Connection> Connection) override;
    void Reset(std::shared_ptr<Connection> Connection) override;
};

class CloseConnection : public IConnectionState
{
public:
    void Open(std::shared_ptr<Connection> Connection) override;
    void Close(std::shared_ptr<Connection> Connection) override;
    void Reset(std::shared_ptr<Connection> Connection) override;
};


class Connection: public std::enable_shared_from_this<Connection>
{
public:
    Connection(): m_state(std::make_shared<OpenConnection>()){}

    void Open()
    {
        m_state->Open(shared_from_this());
    }
    void Close()
    {
        m_state->Close(shared_from_this());
    }
    void Reset()
    {
        m_state->Reset(shared_from_this());
    }
    void setState(std::shared_ptr<IConnectionState> state)
    {
        m_state = std::move(state);
    }

private:
    std::shared_ptr<IConnectionState> m_state;
};


void OpenConnection::Open(std::shared_ptr<Connection> conn)
{
    std::cout << "Opening new connection port\n";
    conn->setState(std::make_shared<InUseConnection>());
    std::cout << "New connection Opened successfully\n";
}

void OpenConnection::Close(std::shared_ptr<Connection> conn)
{
    std::cout << "Can't close Available Connection\n";
}

void OpenConnection::Reset(std::shared_ptr<Connection> conn)
{
    std::cout << "Can't reset Available Connection\n";
}
//---------------------------------------------------------------
void InUseConnection::Open(std::shared_ptr<Connection> conn)
{
    std::cout << "Can't open new connection - Connection already IN USE\n";
}

void InUseConnection::Close(std::shared_ptr<Connection> conn)
{
    std::cout << "Closing Active connection\n";
    conn->setState(std::make_shared<CloseConnection>());
    std::cout << "Successfully closed Active connection\n";
}

void InUseConnection::Reset(std::shared_ptr<Connection> conn)
{
    std::cout << "Resetting Active Connection\n";
    conn->setState(std::make_shared<OpenConnection>());
    std::cout << "Successfully Reset Active Connection\n";
}
//---------------------------------------------------------------
void CloseConnection::Open(std::shared_ptr<Connection> conn)
{
    std::cout << "Reopening the connection\n";
    conn->setState(std::make_shared<OpenConnection>());
    std::cout << "New connection Opened successfully\n";
}

void CloseConnection::Close(std::shared_ptr<Connection> conn)
{
    std::cout << "Can't close Already closed connection\n";
}

void CloseConnection::Reset(std::shared_ptr<Connection> conn)
{
    std::cout << "Resetting closed Connection\n";
    conn->setState(std::make_shared<OpenConnection>());

}

int main()
{
    std::shared_ptr<Connection> conn = std::make_shared<Connection>();

    conn->Open();
    conn->Close();
    conn->Reset();
    conn->Open();
}