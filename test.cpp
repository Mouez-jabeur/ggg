#include <iostream>
#include <thread>
#include <chrono>

int main() {
    int h, m, s, err;
    err = 0;
    
    while (err == 0) {
        std::cout << "Enter hour: " << std::endl;
        std::cin >> h;
        std::cout << "Enter minutes: " << std::endl;
        std::cin >> m;
        std::cout << "Enter seconds: " << std::endl;
        std::cin >> s;
        
        if (h < 24 && m < 60 && s < 60)
            err++;
        else
            system("clear");
    }
    
    while (true) {
        system("clear");
        std::cout << h << ":" << m << ":" << s << std::endl;
        
        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        s++;
        if (s > 59) {
            s = 0;
            m++;
        }
        if (m > 59) {
            m = 0;
            h++;
        }
        if (h > 23) {
            h = 0;
        }
    }
    
    return 0;
}

