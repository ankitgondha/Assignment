#include <bits/stdc++.h>
using namespace std;
struct Process
{
    int pid;
    int burst;
    int arrival;
    int priority;
    int waiting;
    int turnaround;
};

void RoundRobin(vector<Process> &processes, int quantum)
{
    int n = processes.size();
    int time = 0;
    queue<int> q;
    int i = 0;
    while (i < n || !q.empty())
    {
        if (!q.empty())
        {
            int pid = q.front();
            q.pop();
            if (processes[pid].burst > quantum)
            {
                time += quantum;
                processes[pid].burst -= quantum;
                while (i < n && processes[i].arrival <= time)
                {
                    q.push(i);
                    i++;
                }
                q.push(pid);
            }
            else
            {
                time += processes[pid].burst;
                processes[pid].waiting = time - processes[pid].burst - processes[pid].arrival;
                processes[pid].turnaround = time - processes[pid].arrival;
                while (i < n && processes[i].arrival <= time)
                {
                    q.push(i);
                    i++;
                }
            }
        }
        else
        {
            q.push(i);
            time = processes[i].arrival;
            i++;
        }
    }
}

void FCFS(vector<Process> &processes)
{
    int n = processes.size();
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        time = max(time, processes[i].arrival);
        processes[i].waiting = time - processes[i].arrival;
        time += processes[i].burst;
        processes[i].turnaround = time - processes[i].arrival;
    }
}

void SJF(vector<Process> &processes)
{
    int n = processes.size();
    int time = 0;
    int remaining = n;
    while (remaining > 0)
    {
        int shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival <= time && processes[i].burst > 0)
            {
                if (shortest == -1 || processes[i].burst < processes[shortest].burst)
                {
                    shortest = i;
                }
            }
        }
        if (shortest == -1)
        {
            time++;
        }
        else
        {
            processes[shortest].waiting = time - processes[shortest].arrival;
            time += processes[shortest].burst;
            processes[shortest].turnaround = time - processes[shortest].arrival;
            processes[shortest].burst = 0;
            remaining--;
        }
    }
}

void SRTF(vector<Process> &processes)
{
    int n = processes.size();
    int time = 0;
    int remaining = n;
    while (remaining > 0)
    {
        int shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival <= time && processes[i].burst > 0)
            {
                if (shortest == -1 || processes[i].burst < processes[shortest].burst)
                {
                    shortest = i;
                }
            }
        }
        if (shortest == -1)
        {
            time++;
        }
        else
        {
            processes[shortest].burst--;
            if (processes[shortest].burst == 0)
            {
                processes[shortest].waiting = time - processes[shortest].arrival - processes[shortest].burst + 1;
                processes[shortest].turnaround = time - processes[shortest].arrival;
                remaining--;
            }
            time++;
        }
    }
}

void priority(vector<Process> &processes)
{
    int n = processes.size();
    int time = 0;
    int remaining = n;
    while (remaining > 0)
    {
        int highest_priority = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival <= time && processes[i].burst > 0)
            {
                if (highest_priority == -1 || processes[i].priority < processes[highest_priority].priority)
                {
                    highest_priority = i;
                }
            }
        }
        if (highest_priority == -1)
        {
            time++;
        }
        else
        {
            processes[highest_priority].burst--;
            if (processes[highest_priority].burst == 0)
            {
                processes[highest_priority].waiting = time - processes[highest_priority].arrival - processes[highest_priority].burst + 1;
                processes[highest_priority].turnaround = time - processes[highest_priority].arrival;
                remaining--;
            }
            time++;
        }
    }
}

int main()
{
    // Define the processes
    vector<Process> processes = {
        {1, 6, 0, 1, 0, 0},
        {2, 8, 1, 3, 0, 0},
        {3, 7, 2, 2, 0, 0},
        {4, 3, 3, 4, 0, 0},
        {5, 4, 4, 5, 0, 0},
    };
    int quantum = 2;

    cout << "(1)FCFS" << endl;
    cout << "(2)SJF" << endl;
    cout << "(3)SRTF" << endl;
    cout << "(4)Round Robin" << endl;
    cout << "(5)Priority" << endl;
    cout << "Choose process number :---";
    int numberp;
    cin >> numberp;
    switch (numberp)
    {
    case 1:
        FCFS(processes);
        cout << setw(5) << "PID" << setw(10) << "Burst" << setw(10) << "Arrival"
             << setw(10) << "Priority" << setw(10) << "Waiting" << setw(16) << "Turnaround" << endl;
        for (auto &p : processes)
        {
            cout << setw(5) << p.pid << setw(10) << p.burst << setw(10) << p.arrival
                 << setw(10) << p.priority << setw(10) << p.waiting << setw(16) << p.turnaround << endl;
        }
        break;
    case 2:
        SJF(processes);
        cout << setw(5) << "PID" << setw(10) << "Burst" << setw(10) << "Arrival"
             << setw(10) << "Priority" << setw(10) << "Waiting" << setw(16) << "Turnaround" << endl;
        for (auto &p : processes)
        {
            cout << setw(5) << p.pid << setw(10) << p.burst << setw(10) << p.arrival
                 << setw(10) << p.priority << setw(10) << p.waiting << setw(16) << p.turnaround << endl;
        }
        break;
    case 3:
        SRTF(processes);
        cout << setw(5) << "PID" << setw(10) << "Burst" << setw(10) << "Arrival"
             << setw(10) << "Priority" << setw(10) << "Waiting" << setw(16) << "Turnaround" << endl;
        for (auto &p : processes)
        {
            cout << setw(5) << p.pid << setw(10) << p.burst << setw(10) << p.arrival
                 << setw(10) << p.priority << setw(10) << p.waiting << setw(16) << p.turnaround << endl;
        }
        break;
    case 4:
        RoundRobin(processes, quantum);
        cout << setw(5) << "PID" << setw(10) << "Burst" << setw(10) << "Arrival"
             << setw(10) << "Priority" << setw(10) << "Waiting" << setw(16) << "Turnaround" << endl;
        for (auto &p : processes)
        {
            cout << setw(5) << p.pid << setw(10) << p.burst << setw(10) << p.arrival
                 << setw(10) << p.priority << setw(10) << p.waiting << setw(16) << p.turnaround << endl;
        }
        break;

    case 5:
        priority(processes);
        cout << setw(5) << "PID" << setw(10) << "Burst" << setw(10) << "Arrival"
             << setw(10) << "Priority" << setw(10) << "Waiting" << setw(16) << "Turnaround" << endl;
        for (auto &p : processes)
        {
            cout << setw(5) << p.pid << setw(10) << p.burst << setw(10) << p.arrival
                 << setw(10) << p.priority << setw(10) << p.waiting << setw(16) << p.turnaround << endl;
        }
        break;

    default:
        cout << "wrong number" << endl;
        break;
    }

    return 0;
}