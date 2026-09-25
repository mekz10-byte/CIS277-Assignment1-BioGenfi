#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>

#include "MemoryPool.h"

int main()
{
    std::cout << "Network Packet Buffer Pool\n\n";

    // Create a pool with 8 blocks of 512 bytes each.
    MemoryPool pool(512, 8);

    std::cout << "Block Size:       "
              << pool.blockSize() << " bytes\n";

    std::cout << "Blocks:           "
              << pool.availableBlocks() << '\n';

    std::cout << "Total Capacity:   "
              << pool.capacity() << " bytes\n\n";


    // Allocate three blocks.
    void* packet1 = pool.allocate();
    void* packet2 = pool.allocate();
    void* packet3 = pool.allocate();

    std::cout << "Packet 1 allocated: " << packet1 << '\n';
    std::cout << "Packet 2 allocated: " << packet2 << '\n';
    std::cout << "Packet 3 allocated: " << packet3 << "\n\n";

    std::cout << "Available blocks: "
              << pool.availableBlocks() << '\n';

    std::cout << "Allocated blocks: "
              << pool.allocatedBlocks() << "\n\n";


    // Binary packet data.
    unsigned char packetData[] =
    {
        0x45, 0x00, 0x00, 0x3C,
        0xAB, 0xCD, 0x12, 0x34
    };

    if (packet1 != nullptr &&
        sizeof(packetData) <= pool.blockSize())
    {
        std::memcpy(packet1, packetData, sizeof(packetData));

        std::cout << "Binary packet written to Packet 1.\n";

        unsigned char* storedData =
            static_cast<unsigned char*>(packet1);

        std::cout << "Packet 1 data: ";

        for (size_t i = 0; i < sizeof(packetData); i++)
        {
            std::cout << std::hex
                      << std::setw(2)
                      << std::setfill('0')
                      << static_cast<int>(storedData[i])
                      << ' ';
        }

        std::cout << std::dec << "\n\n";
    }


    // Release Packet 2.
    void* releasedAddress = packet2;

    if (pool.deallocate(packet2))
    {
        std::cout << "Packet 2 released.\n";
    }

    std::cout << "Available blocks: "
              << pool.availableBlocks() << '\n';

    std::cout << "Allocated blocks: "
              << pool.allocatedBlocks() << "\n\n";


    // Allocate again to demonstrate memory reuse.
    void* packet4 = pool.allocate();

    std::cout << "Packet 4 allocated: "
              << packet4 << '\n';

    if (packet4 == releasedAddress)
    {
        std::cout
            << "Packet 4 reused the previously released block.\n\n";
    }
    else
    {
        std::cout
            << "Packet 4 did not reuse the released block.\n\n";
    }


    // Exhaust the memory pool.
    std::cout << "Attempting to exhaust pool...\n";

    std::vector<void*> extraBlocks;

    while (true)
    {
        void* block = pool.allocate();

        if (block == nullptr)
        {
            std::cout << "No blocks available.\n";
            std::cout << "allocate() returned nullptr.\n\n";
            break;
        }

        extraBlocks.push_back(block);
    }

    std::cout << "Available blocks: "
              << pool.availableBlocks() << '\n';

    std::cout << "Allocated blocks: "
              << pool.allocatedBlocks() << "\n\n";


    // Demonstrate double deallocation protection.
    std::cout << "Attempting double deallocation...\n";

    bool firstRelease = pool.deallocate(packet3);
    bool secondRelease = pool.deallocate(packet3);

    std::cout << "First deallocation: "
              << (firstRelease ? "accepted" : "rejected")
              << '\n';

    std::cout << "Second deallocation: "
              << (secondRelease ? "accepted" : "rejected")
              << '\n';

    if (!secondRelease)
    {
        std::cout << "Double deallocation rejected.\n";
    }

    return 0;
}