#include <iostream>
#include <vector>

using namespace std;


vector<int> readTimes(int totalSongs) {

    vector<int> songs;
    songs.push_back(0);

    for (int i = 1; i <= totalSongs; i++) {
        int totalPlays, duration;
        cin >> totalPlays >> duration;
        songs.push_back(songs[i-1] + totalPlays * duration);
    }

    return songs;
}


int main(void) {

    int totalSongs, totalQueries;
    cin >> totalSongs >> totalQueries;

    vector<int> times = readTimes(totalSongs);

    int songIdx = 0;

    for (int i = 0; i < totalQueries; i++) {
        int time; cin >> time;
        while (time > times[songIdx]) 
            songIdx++;
        cout << songIdx << "\n";
    }

    return 0;
}
