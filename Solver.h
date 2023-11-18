class Solver;
#ifndef SCHEDULER_SOLVER_H
#define SCHEDULER_SOLVER_H
#include <bits/stdc++.h>
#include "Wrappers.h"
class Solver {
    std::map<std::string, Class> classes;
    std::vector<std::string> wanted_classes;
    std::vector<std::string> sequence;
    std::map<std::string, Term> set_schedule;
    public:
    void read_prerequisites(const std::string &file_name);
    void read_courses(const std::string &file_name);
    void read_sequence(const std::string &file_name);
    void read_fixed_schedule(const std::string &file_name);
    void solve(const std::string &file_name);
    std::vector<Schedule> apply_heuristic(std::vector<Schedule> &schedules);
};
#endif //SCHEDULER_SOLVER_H
