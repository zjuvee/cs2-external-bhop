#include "memory.h"
#include <thread>
#include <iostream>

#define SPACE_BAR 0x20;

const uint32_t STANDING = 65665;
const uint32_t CROUCHING = 65667;
const uint32_t PLUS_JUMP = 65537;
const uint32_t MINUS_JUMP = 256;

// https://github.com/a2x/cs2-dumper/tree/main/output

int dwLocalPlayerPawn = 0x17CF698;
int dwForceJump = 0x17C83E0;
int m_fFlag = 0x3CC;

void Bhop()
{
    Memory mem("cs2.exe");
    std::uintptr_t client = mem.GetModuleAddress("client.dll");
    std::uintptr_t ForceJump = client + dwForceJump;

    while (true)
    {
        std::uintptr_t LocalPlayer = mem.Read<std::uintptr_t>(client + dwLocalPlayerPawn);
        uint32_t fFlag = mem.Read<uint32_t>(LocalPlayer + m_fFlag);

        if (GetAsyncKeyState(0x20) & 0x8000)
        {
            if (fFlag == STANDING || fFlag == CROUCHING)
            {
                std::cout << "Jump!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                mem.Write<uint32_t>(ForceJump, PLUS_JUMP);
            }
            else
            {
                mem.Write<uint32_t>(ForceJump, MINUS_JUMP);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    }
}

int main()
{
    Bhop();
    return 0;
}