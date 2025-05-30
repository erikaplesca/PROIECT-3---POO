#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
private:
    std::string m_nume;
    std::string m_tipClient;

public:
    Client();
    Client(const std::string& m_nume,
        const std::string& m_tipClient);
    ~Client();

    Client(const Client& other);
    Client& operator=(const Client& other);

    std::string getNume() const;
    std::string getTipClient() const;

    void setNume(const std::string& m_nume);
    void setTipClient(const std::string& m_tipClient);

    friend std::ostream& operator<<(std::ostream& os, const Client& client);
    friend std::istream& operator>>(std::istream& is, Client& client);
};

#endif //CLIENT_H
