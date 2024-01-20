#include<iostream>
#include<memory>
#include<string>

struct AuthContext{
    std::string Username;
    std::string Password;
    std::string OTP;
};


class Handler
{
public:
    virtual std::shared_ptr<Handler> setNext(std::shared_ptr<Handler> handler) = 0;
    virtual bool Handle(AuthContext ctx) = 0;
};

class BaseHandler : public Handler
{
private:
    std::shared_ptr<Handler> m_nextHandler;
public:
    BaseHandler():m_nextHandler(NULL){}

    std::shared_ptr<Handler> setNext(std::shared_ptr<Handler> handler)
    {
        m_nextHandler = handler;
        return handler;
    }

    virtual bool Handle(AuthContext ctx) override
    {
        if (m_nextHandler)
            return m_nextHandler->Handle(ctx);
        return false;
    }
};

class UserHandler : public BaseHandler
{
public:
    bool Handle(AuthContext ctx) override
    {
        if (ctx.Username == "User1")
        {
            std::cout << "User check Passed\n";
            return BaseHandler::Handle(ctx);
        }
        std::cout << "User check FAILED\n";
        return false;
    }

};

class PasswordHandler : public BaseHandler
{
public:
    bool Handle(AuthContext ctx) override
    {
        if (ctx.Password == "Password1")
        {
            std::cout << "Password check Passed\n";
            return BaseHandler::Handle(ctx);
        }
        std::cout << "Password check FAILED\n";
        return false;
    }

};
class TwoFactorAuthHandler : public BaseHandler
{
public:
    bool Handle(AuthContext ctx) override
    {
        if (ctx.OTP == "123456")
        {
            std::cout << "OTP check Passed\n";
            return true;
        }
        std::cout << "OTP check FAILED\n";
        return false;
    }

};

int main()
{
    auto userH = std::make_shared<UserHandler>();
    auto passwordH = std::make_shared<PasswordHandler>();
    auto otpH = std::make_shared<TwoFactorAuthHandler>();

    userH->setNext(passwordH)->setNext(otpH);

    AuthContext ctx = {"User1", "Password1", "123456"};
    if (userH->Handle(ctx))
        std::cout << "Login Successful\n";
    else
        std::cout << "Login Failed\n";
    return 0;
}