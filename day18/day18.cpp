//
// Created by hkoertge on 26.02.2024.
//

#include "day18.h"
#include "../util.h"
#include <map>
#include <queue>
#include <condition_variable>

using namespace std;

map<string, int> cmdToNum = {
        {"snd", 0},
        {"set", 1},
        {"add", 2},
        {"mul", 3},
        {"mod", 4},
        {"rcv", 5},
        {"jgz", 6}
};

struct pipe {
    int sndcnt = 0;
    queue<long long> q;
    mutex m;
    condition_variable cv;
    atomic<bool> is_waiting;
} pipePt1;

void snd(pipe& p, long long v) {
    {
        lock_guard lock(p.m);
        p.q.push(v);
        p.sndcnt++;
        p.cv.notify_one();
    }
}

long long rcv(pipe& p) {
    unique_lock lock(p.m);
    p.is_waiting.store(true);
    p.cv.wait(lock, [&] { return !p.q.empty(); });
    long long v = p.q.front();
    p.q.pop();
    p.m.unlock();
    p.is_waiting.store(false);
    return v;
}

class Duet {
private:
    bool pt1 = true;
    vector<string> instructions;
    pipe& readqueue;
    pipe& writequeue;
    map<char, long long> reg;
public:
    long long execute() {
        while (reg['.'] < instructions.size() && reg['.'] >= 0) {
            vector<string> parts = splitString(instructions[reg['.']], " ");
            int command = cmdToNum[parts[0]];
            char X = parts[1][0];
            long long Y = 0;
            if (parts.size() > 2) {
                if (parts[2][0] >= 'a' && parts[2][0] <= 'z') {
                    Y = reg[parts[2][0]];
                } else {
                    Y = stoi(parts[2]);
                }
            }
            switch (command) {
                case 0: // snd
                    snd(writequeue, reg[X]);
                    break;
                case 1: // set
                    reg[X] = Y;
                    break;
                case 2: // add
                    reg[X] += Y;
                    break;
                case 3: // mul
                    reg[X] *= Y;
                    break;
                case 4: // mod
                    reg[X] %= Y;
                    break;
                case 5: // rcv
                    if (pt1) {
                        if (reg[X] != 0) {
                            return readqueue.q.back();
                        }
                    } else {
                        reg[X] = rcv(readqueue);
                    }
                    break;
                case 6: // jgz
                    if (((X >= 'a' && X <= 'z') ? reg[X]: X - '0') > 0) {
                        reg['.'] += --Y;
                    }
                    break;
                default:
                    cout << "Unknown command: " << instructions[reg['.']] << endl;
                    return INT_MIN;
            }
            reg['.']++;
        }
        return INT_MIN;
    }
    explicit Duet(vector<string> instructions, pipe& readqueue, pipe& writequeue, bool pt1, int pid):
        instructions(std::move(instructions)), readqueue(readqueue), writequeue(writequeue), pt1(pt1) {
        reg['p'] = pid;
    }
};

string Day18::part_1(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();
    Duet duet = Duet(lines, pipePt1, pipePt1, true, 0);
    return to_string(duet.execute());
}

pipe pipe0, pipe1;

void monitor() {
    while (true) {
        bool deadlock = false;
        if (pipe0.is_waiting && pipe1.is_waiting) {
            deadlock = true;
        }

        if (deadlock) return;
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

string Day18::part_2(string input) {
    vector<string> lines = splitString(input, "\n");
    lines.pop_back();

    thread t0([&] {
        Duet(lines, pipe0, pipe1, false, 0).execute();
    });
    thread t1([&] {
        Duet(lines, pipe1, pipe0, false, 1).execute();
    });
    thread mon(monitor);
    if (mon.joinable()) {
        mon.join();
    }
    t0.detach();
    t1.detach();

    return to_string(pipe0.sndcnt);
}