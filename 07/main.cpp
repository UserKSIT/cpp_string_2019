//
//  main.cpp
//  PingPongThread
//
//  Created by Артём on 19/04/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include <thread>
#include <atomic>

const int COUNT = 500000;

std::atomic<bool> ball;

void ping_pong(const char * string, bool value)
{
    for(int counter = 0; counter < COUNT; counter++)
    {
        while(ball == value);//wait until another thread changes the ball
        
        std::cout << string << std::endl;
        ball = value;//change the ball
    }
}

int main(int argc, const char * argv[])
{
    ball = false;
    
    std::thread ping(ping_pong, "ping", true);
    std::thread pong(ping_pong, "pong", false);
    
    ping.join();
    pong.join();
    
    return 0;
}
