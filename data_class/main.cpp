#include "m_data.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <thread>


void swapWithLock(m_data& d1, m_data& d2)
{
    std::lock(d1.m_mutex, d2.m_mutex);
    std::lock_guard<std::mutex> lock1(d1.m_mutex, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(d2.m_mutex, std::adopt_lock);

    int tmp = d1.get_data();
    d1.set_data(d2.get_data());
    d2.set_data(tmp);

    std::cout << std::endl << "This Thread - swapWithLock" << std::endl;
    std::cout << "value_1 d1 = " << d1.get_data() << ";" << std::endl;
    std::cout << "value_1 d2 = " << d2.get_data() << ";" << std::endl;
}

void swapWithScopedLock(m_data& d1, m_data& d2)
{
    std::scoped_lock lock(d1.m_mutex, d2.m_mutex);

    int tmp = d1.get_data();
    d1.set_data(d2.get_data());
    d2.set_data(tmp);

    std::cout << std::endl << "This Thread - swapWithScopedLock" << std::endl;
    std::cout << "value_1 d1 = " << d1.get_data() << ";" << std::endl;
    std::cout << "value_1 d2 = " << d2.get_data() << ";" << std::endl;
}

void swapWithUniqueLock(m_data& d1, m_data& d2)
{
    std::unique_lock<std::mutex> lock1(d1.m_mutex, std::defer_lock);
    std::unique_lock<std::mutex> lock2(d2.m_mutex, std::defer_lock);
    std::lock(lock1, lock2);

    int tmp = d1.get_data();
    d1.set_data(d2.get_data());
    d2.set_data(tmp);

    std::cout << std::endl << "This Thread - swapWithUniqueLock" << std::endl;
    std::cout << "value_1 d1 = " << d1.get_data() << ";" << std::endl;
    std::cout << "value_1 d2 = " << d2.get_data() << ";" << std::endl;
    lock1.unlock();
    lock2.unlock();
}

int main()
{
    std::cout << "ID main thread: " << std::this_thread::get_id() << "\n";

    m_data d1(10);
    m_data d2(20);

    std::cout << "\nbefore:\n";
    std::cout << "value_1 d1 = " << d1.get_data() << ";" << std::endl;
    std::cout << "value_2 d2 = " << d2.get_data() << ";" << std::endl;

    std::thread thread1(swapWithLock, std::ref(d1), std::ref(d2));
    std::thread thread2(swapWithScopedLock, std::ref(d1), std::ref(d2));
    std::thread thread3(swapWithUniqueLock, std::ref(d1), std::ref(d2));

    thread1.join();
    thread2.join();
    thread3.join();

    return EXIT_SUCCESS;
}
