#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include "process.h"
#include "process.h"

using namespace std;

void scheduleFCFS(vector<Process>& processes) {
    // to sort by arrival time for user defined types from geeks for geeks
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    
    int time = 0;
    for (auto& proc : processes){

        if (time < proc.arrivalTime) 
            time = proc.arrivalTime;

        time += proc.burstTime;
        proc.turnAroundTime = time - proc.arrivalTime;
        proc.waitingTime = proc.turnAroundTime - proc.burstTime;
        proc.remainingTime = 0;
        proc.state = ProcessState::TERMINATED;

    }
}

void scheduleSJF(vector <Process>& processes){

    // used to track completed processes
    vector<bool> done(processes.size(), false);
    int time = 0;
    int completed = 0;

    while(completed < processes.size()){\
        
        // to save index of process with shortest burst time
        int index = -1;

        // default to the largest integer to ensure any burst time is smaller
        int shortestBurst = INT_MAX;


    // To pick shortest job 
        for(int i = 0; i < processes.size(); i++){
            if(!done[i] && processes[i].arrivalTime <= time){
                if(processes[i].burstTime < shortestBurst){
                    shortestBurst = processes[i].burstTime;
                    index = i;
                }
            }
        }

        if (index == -1){
            time++;
        }

        time += processes[index].burstTime;
        processes[index].turnAroundTime = time - processes[index].arrivalTime;
        processes[index].waitingTime = processes[index].turnAroundTime - processes[index].burstTime;
        processes[index].remainingTime = 0;
        processes[index].state = ProcessState::TERMINATED;
        done[index] = true;
        completed++;
    }
}

void scheduleSRTF(vector<Process>& processes){
    int time = 0;
    int completed = 0;
    for (auto& proc : processes){
        proc.remainingTime = proc.burstTime;
    }

    while(completed < processes.size()){
        int index = -1;
        int shortestTime = INT_MAX;

        for(int i = 0; i < processes.size(); i++){
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0){
                if(processes[i].remainingTime < shortestTime){
                    shortestTime = processes[i].remainingTime;
                    index = i;
                }
            }
        }

        if(index == -1){
            time++;
        }

        if (processes[index].remainingTime == 0) {
            int completedTime = time;
            processes[index].turnAroundTime = completedTime = processes[index].arrivalTime;
            processes[index].waitingTime = processes[index].turnAroundTime - processes[index].burstTime;
            processes[index].state = ProcessState::TERMINATED;
            completed++;
        }
    }
}


void printSchedule(const vector<Process>& processes, const string& scheduleType){
    cout << endl << endl << scheduleType << endl;
    int turnAroundTime = 0;
    int waitingTime = 0;

    for(auto& proc : processes){
        cout << "PID: " << proc.pid << endl;
        cout << "Arrival Time: " << proc.arrivalTime << endl;
        cout << "Burst Time: " << proc.burstTime << endl;
        cout << "Time of Completion: " << proc.arrivalTime + proc.turnAroundTime << endl;

        turnAroundTime+=proc.turnAroundTime;
        waitingTime+=proc.waitingTime;

        cout << "Turnaround Time: " << proc.turnAroundTime << endl;
        cout << "Waiting Time: " << proc.waitingTime << endl;
    }
    cout << "Average Turnaround Time: " << turnAroundTime / processes.size() << endl;
    cout << "Average Waiting Time: " << waitingTime / processes.size() << endl;
} 