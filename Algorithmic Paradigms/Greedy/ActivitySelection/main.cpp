#include <iostream>
using namespace std;

int findMaximumActivities(int** activities, int n) {
    // sort by end time (activities[_][1])
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (activities[j][1] > activities[j+1][1]) {
                int tempstart = activities[j][0];
                int tempend = activities[j][1];
                activities[j][0] = activities[j+1][0];
                activities[j][1] = activities[j+1][1];
                activities[j+1][0] = tempstart;
                activities[j+1][1] = tempend;
            }
        }
    }

    // set counter and currenttime
    int count = 0, currentTime = 0;

    // if start time is after current time, then it can be added to sequence
    for (int i = 0; i < n; i++) {
        if (activities[i][0] >= currentTime) {
            count++;
            currentTime = activities[i][1];
        }
    }

    return count;
}

int main() {
    int n;

    cout << "Enter number of activities: ";
    cin >> n;

    cout << "Enter start and end times: " << endl;
    int** activities = new int*[n];
    for (int i = 0; i < n; i++) {
        activities[i] = new int[2];
        cin >> activities[i][0];
        cin >> activities[i][1];
    }

    int count = findMaximumActivities(activities, n);

    cout << "Maximum possible non-overlapping activities: " << count;
}