#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>

class MemoryManagementSimulator {
private:
    const static int TOTAL_PAGES = 100;
    const static int PAGE_SIZE_MB = 160;
    const static int STARTING_ADDRESS = 2000;

    int memoryPages[TOTAL_PAGES];
    int currentAddress;
    std::random_device rd;
    std::mt19937 gen;

public:
    MemoryManagementSimulator() : gen(rd()) {
        currentAddress = STARTING_ADDRESS;
        // This is to set all memory pages to -1 to set them as unassigned
        for(int i = 0; i < TOTAL_PAGES; i++) {
            memoryPages[i] = -1;
        }
    }

    void userMemoryAllocation() {
        int processId = 1;

        while (processId <= TOTAL_PAGES &&
               currentAddress < (STARTING_ADDRESS + (TOTAL_PAGES * PAGE_SIZE_MB))) {
            // This is to create a random process size between 1 and 30 pages
            std::uniform_int_distribution<> dis(1, 30);
            int pageSize = dis(gen);

            // This is to determine memory needed
            int totalSizeMB = pageSize * 80;
            int pagesNeeded = static_cast<int>(std::ceil(static_cast<double>(totalSizeMB) / PAGE_SIZE_MB));

            // This is to check if we have enough space
            if ((currentAddress + (pagesNeeded * PAGE_SIZE_MB)) >
                (STARTING_ADDRESS + (TOTAL_PAGES * PAGE_SIZE_MB))) {
                break;
            }

            // This is to allocate memory
            allocateProcess(processId, currentAddress, totalSizeMB, pagesNeeded);

            // This is to update current address
            currentAddress += (pagesNeeded * PAGE_SIZE_MB);
            processId++;
        }
    }

    void allocateProcess(int processId, int startingAddress, int totalSizeMB, int pagesUsed) {
        int unusedSpaceMB = (pagesUsed * PAGE_SIZE_MB) - totalSizeMB;

        std::cout << std::setw(11) << std::left << processId
                 << std::setw(23) << std::left << startingAddress
                 << std::setw(25) << std::left << totalSizeMB
                 << std::setw(15) << std::left << unusedSpaceMB
                 << std::endl;
    }

    void printSummaryReport() {
        std::cout << "\nSummary Report\n";
        std::cout << "=================================\n";
        std::cout << std::setw(11) << std::left << "Process Id"
                 << std::setw(23) << std::left << "Starting Memory Address "
                 << std::setw(25) << std::left << "Size of the Process MB"
                 << std::setw(15) << std::left << "Unused Space MB"
                 << std::endl;
        std::cout << "=================================\n";

        userMemoryAllocation();
    }
};

int main() {
    MemoryManagementSimulator simulator;
    simulator.printSummaryReport();
    return 0;
}