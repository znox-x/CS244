#include <iostream>
#include "job.hpp"
using namespace std;

int greedy(int n, job** jobs, job** slots, int maxDeadline) {
    for (int i = 0; i < n; i++) {
        if (!slots[jobs[i]->deadline - 1]) {
            slots[jobs[i]->deadline - 1] = jobs[i];
        } else {
            for (int j = jobs[i]->deadline - 2; j >= 0; j--) {
                if (!slots[j]) {
                    slots[j] = jobs[i];
                    break;
                }
            }
        }
    }

    int total = 0;
    for (int i = 0; i < maxDeadline; i++) {
        if (slots[i])   total += slots[i]->profit;
    }

    return total;
}

int main() {
    int n;

    cout << "Enter number of j*bs: ";
    cin >> n;

    job** jobs = new job*[n];
    cout << "Enter j*b details: " << endl;
    for (int i = 0; i < n; i++) {
        jobs[i] = new job;
        cout << "Name: ";
        cin >> jobs[i]->name;
        cout << "Deadline: ";
        cin >> jobs[i]->deadline;
        cout << "Profit: ";
        cin >> jobs[i]->profit;
        cout << endl;
    }

    // sort j*bs to find maximum deadline 
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (jobs[j]->deadline < jobs[j+1]->deadline) {
                job* temp = jobs[j];
                jobs[j] = jobs[j+1];
                jobs[j+1] = temp;
            }
        }
    }

    // initialize slot
    int maxDeadline = jobs[0]->deadline;
    job** slots = new job*[maxDeadline];
    for (int i = 0; i < maxDeadline; i++) {
        slots[i] = nullptr;
    }

    // sort j*bs by profit DESC
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (jobs[j]->profit < jobs[j+1]->profit) {
                job* temp = jobs[j];
                jobs[j] = jobs[j+1];
                jobs[j+1] = temp;
            }
        }
    }

    int profit = greedy(n, jobs, slots, maxDeadline);

    cout << "Scheduled J*bs: [ ";
    for (int i = 0; i < maxDeadline; i++) {
        if(slots[i])    cout << slots[i]->name << " ";
    }
    cout << "]" << endl << "Total Profit = " << profit;
}