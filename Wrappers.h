#ifndef SCHEDULER_WRAPPERS_H
#define SCHEDULER_WRAPPERS_H
#include <bits/stdc++.h>
#include "Solver.h"
class Term;
class Class {
    std::string availability, name, minimum_term;
    std::vector<std::vector<std::string>> prerequisites;
    int difficulty;
    public:
    Class(std::string n = "", std::vector<std::vector<std::string>> p = {}, std::string a = "", std::string m = "", int d = 0):
        availability{std::move(a)}, minimum_term{std::move(m)}, name{std::move(n)}, prerequisites{std::move(p)}, difficulty{100 - d} {}
    bool operator<(Class &other) const;
    static bool has_prerequisites(std::set<std::string> &courses, std::vector<std::vector<std::string>> &prereqs);
    bool is_availabile(int term);
    friend Solver;
    friend Term;
};
class Term {
    std::string term_type;
    std::vector<Class> classes;
    public:
    Term(std::string t = "", std::vector<Class> c = {});
    void output(std::ostream &out_stream);
    friend Solver;
};
class Schedule {
    std::set<std::string> courses;
    std::vector<Term> terms;
    public:
    void output(std::ostream &out_stream);
    friend Solver;
};
#endif //SCHEDULER_WRAPPERS_H
