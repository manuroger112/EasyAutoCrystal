#include <Windows.h>
#include <iostream>
#include <ctime>
#include <thread>

//kept it as barebone and simple as possible, maybe I will update it in the future to offer more features :) 


void moveMouse(int x, int y, int smoothnessCoefficient) {
    x /= smoothnessCoefficient;
    y /= smoothnessCoefficient;
    for (int i = 0; i < smoothnessCoefficient; i++) {
        mouse_event(MOUSEEVENTF_MOVE, x, y, 0, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void pressKey(WORD key) {
    INPUT ip = { };
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = key;
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(ip));
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(ip));
}

void pressMouseLeft() {
    INPUT ip = { };
    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &ip, sizeof(ip));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &ip, sizeof(ip));
}

void pressMouseRight() {
    INPUT ip = { };
    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &ip, sizeof(ip));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &ip, sizeof(ip));
}

int main()
{
    //CHANGE THIS TO YOUR PREFERENCE
    WORD CrystalHotbarKey = 0x31;
    WORD ObbyHotbarKey = 0x32;
    WORD SwordHotbarKey = 0x33;

    std::srand(std::time(0));
    int delay = 5 + std::rand() % 14;
    int placeBlocks = true;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_XBUTTON1) < 0 || GetAsyncKeyState(VK_XBUTTON1) & 1) {
            if (placeBlocks == true) {
                placeBlocks = false;

                pressKey(ObbyHotbarKey);
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                pressMouseRight();
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
            
            pressKey(CrystalHotbarKey);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            pressMouseRight();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            moveMouse(0, -800, 2);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            pressMouseLeft();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            moveMouse(0, 800, 2);
        }

        else if(GetAsyncKeyState(VK_XBUTTON1) == 0 && placeBlocks != true){
            pressKey(SwordHotbarKey);
            placeBlocks = true;
            delay = 5 + std::rand() % 14;
        }
    }
    std::cout << "Bye \n";
    return 0;
}

