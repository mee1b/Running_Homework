#ifndef M_DATA_H
#define M_DATA_H
#include <string>
#include <mutex>

class m_data
{
private:
    int value_1{};
public:
    m_data(int value) : value_1(value) {};
    std::mutex m_mutex;

    int get_data();
    void set_data(int value);
};

#endif // M_DATA_H
