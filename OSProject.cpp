#include <iostream>
#include <string>

#include "auth.h"
#include "process.h"


using namespace std;


// Made to show process info but won't be part of final OS
static void printProcess(const Process& p, int t, const char* label) {
    cout << "t=" << t << " [" << label << "] "
        << "PID=" << p.getPid()
        << " state=" << p.getState()
        << " arrivalTime=" << p.getArrivalTime()
        << " burstTime=" << p.getBurstTime()
        << " remainingTime=" << p.getRemainingTime()
        << " waitTime=" << p.getWaitingTime()
        << " turnAroundTime=" << p.getTurnAroundTime()
        << " priority=" << p.getPriority()
        << " memoryReq=" << p.getMemoryRequired()
        << "\n\n";
}

int main()
{
    cout << "Booting up ArtOS..." << endl;

    if (!authenticateUser())
    {
        cout << "Error: Failed to boot ArtOS." << endl;
        return 1;
    }

    cout << "ArtOS booted successfully!" << endl;
    

    // Process Assignment Example
    int time = 0; 

    // pid, arrival, burst, priority, memory
    Process p1(1, 0, 5, 1, 64);
    Process p2(2, 2, 3, 0, 32);
    Process p3(3, 4, 4, 2, 16);

    // At time = 0 p1 arrives
    p1.set_state(ProcessState::READY, time);
    printProcess(p1, time, "p1 READY");
    p1.set_state(ProcessState::RUNNING, time);
    bool done = p1.tickCPU(2, time += 2); 
    printProcess(p1, time, done ? "p1 FINISHED" : "p1 RUN 2");

    // At t=2 p2 arrives
    p2.set_state(ProcessState::READY, time);
    printProcess(p2, time, "p2 READY");

    // p1 is switched to ready
    // p2 gets CPU for 2 units
    p1.set_state(ProcessState::READY, time);
    p2.set_state(ProcessState::RUNNING, time);
    done = p2.tickCPU(2, time += 2); // t=4
    printProcess(p2, time, done ? "p2 FINISHED" : "p2 RUN 2");

    // WAITING for 1 unit and back to READY at time = 5
    p2.set_state(ProcessState::WAITING, time);
    p2.tickWait(1);
    ++time; // time passes during I/O
    p2.set_state(ProcessState::READY, time);
    printProcess(p2, time, "p2 WAIT to READY");

    // At t=4 p3 arrived earlier so make it READY
    p3.set_state(ProcessState::READY, 4);
    printProcess(p3, 4, "p3 READY");

    // Give CPU to p1 to finish its remaining 3 units
    p1.set_state(ProcessState::RUNNING, time);
    done = p1.tickCPU(3, time += 3); // t=8
    printProcess(p1, time, done ? "p1 FINISHED" : "p1 RUN more");

    // Finish p2
    p2.set_state(ProcessState::RUNNING, time);
    done = p2.tickCPU(1, time += 1); // t=9
    printProcess(p2, time, done ? "p2 FINISHED" : "p2 RUN more");

    // Finish p3
    p3.set_state(ProcessState::RUNNING, time);
    done = p3.tickCPU(4, time += 4); // t=13
    printProcess(p3, time, done ? "p3 FINISHED" : "p3 RUN more");

    return 0;

}


