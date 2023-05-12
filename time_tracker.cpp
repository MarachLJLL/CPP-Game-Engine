#include<chrono>
#include<iostream>

#define Steady_Time std::chrono::steady_clock::time_point
#define Seconds std::chrono::seconds
#define Elapsed_Seconds std::chrono::duration<double>
#define get_cur_time() std::chrono::steady_clock::now()

struct Player_Timers {
    Steady_Time prev_l_input;
    Seconds dash_cd = std::chrono::seconds(1);
};

Player_Timers p1_timer;
Steady_Time timer;

void put_on_cd(Steady_Time* timer) {
    *timer = get_cur_time();
}

bool cd_tracker(Steady_Time timer, Seconds cd_in_seconds) {
    Steady_Time current = get_cur_time();
    Elapsed_Seconds elapsed_time = current - timer;
    std::cout << "elapsed time: " << elapsed_time.count() << "s\n";
    return elapsed_time > cd_in_seconds;
}

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    put_on_cd(&p1_timer.prev_l_input);
    std::cout << "f(43) = " << fibonacci(43) << '\n';
    if (cd_tracker(p1_timer.prev_l_input, p1_timer.dash_cd)) std::cout << "passed" << '\n';
    put_on_cd(&p1_timer.prev_l_input);
    if (cd_tracker(p1_timer.prev_l_input, p1_timer.dash_cd)) std::cout << "passed" << '\n';
    else std::cout << "failed" << '\n';
    return 0;
}