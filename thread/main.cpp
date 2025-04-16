#include <iostream>
#include <thread>
#include <atomic>



int main()
{
    std::atomic<int> clients = 0;
    std::atomic<int> maxClients = 10;
    std::thread t1(
        [&clients, &maxClients]()
        {
            while (clients != maxClients)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                clients += 1;
                std::cout << "Clients now " << clients << std::endl;
            }
        }
        );
    std::thread t2(
        [&clients]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1200));
            while (clients >= 0)
            {
                if (clients == 0)
                {
                    std::cout << "Everyone's gone" << std::endl;
                    return;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                clients -= 1;
                std::cout << "Client go out. Clients now " << clients << std::endl;
            }
        }
        );

    t1.join();
    t2.join();


    return 0;
}
