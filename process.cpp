#include "process.h"
#include <iostream>
#include <algorithm>

using namespace std;

Process::Process(int pid, int arrivalTime, int burstTime, int priority, int memory, const vector<int>& ioOperations)
    : pid(pid), state(ProcessState::NEW), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime),
      waitingTime(0), turnAroundTime(0), priority(priority), memoryRequired(memory),
      ioOperations(ioOperations) {}

void Process::set_state(const string& newState, int currentTime) {
    state = newState;
    if(state == ProcessState::TERMINATED && currentTime != -1){
        processDone(currentTime);
    }
}

bool Process::tickCPU(int cpuTime, int currentTime){
    if(state != ProcessState::RUNNING) return false;
    if(remainingTime <= 0 || cpuTime <= 0) return false;

    int timeSpent = min(remainingTime, cpuTime);
    remainingTime -= timeSpent;

    if(remainingTime == 0){
        set_state(ProcessState::TERMINATED, currentTime);
        return true;
    }
    return false;

}

void Process::tickWait(int cpuTime){
    waitingTime += cpuTime;
}

void Process::processDone(int currentTime){
    turnAroundTime = currentTime - arrivalTime;
}

// Not used for Process Assignment
void Process::summary() const {
    cout << "Process Summary for PID=" << pid << ":\n";
    cout << "State: " << state << "\n";
    cout << "Arrival Time: " << arrivalTime << "\n";
    cout << "Burst Time: " << burstTime << "\n";
    cout << "Remaining Time: " << remainingTime << "\n";
    cout << "Waiting Time: " << waitingTime << "\n";
    cout << "Turnaround Time: " << turnAroundTime << "\n";
    cout << "Priority: " << priority << "\n";
    cout << "Memory Required: " << memoryRequired << "\n";
    cout << "I/O Operations: ";
    for (const auto& io : ioOperations) {
        cout << io << " ";
    }
    cout << "\n";
}
