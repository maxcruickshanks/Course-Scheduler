#include "Solver.h"

bool Class::operator<(Class &other) const {
    return name < other.name;
}
bool Class::has_prerequisites(std::set<std::string> &courses, std::vector<std::vector<std::string>> &prereqs) {
    bool has_reqs = 1;
    for (std::vector<std::string> &prereq : prereqs) {
        bool sat = 0;
        for (std::string &pos_preq : prereq) {
            if (courses.count(pos_preq)) {
                sat = 1; break;
            }
        }
        has_reqs &= sat;
        if (!has_reqs) {
            break;
        }
    }
    return has_reqs;
}
bool Class::is_availabile(int term) {
    int conv_min_term = 2 * (minimum_term[0] - '1') + minimum_term[1] - 'A';
    if (term < conv_min_term) return false;
    char req_card = ((term % 3 == 0) ? 'F' : ((term % 3 == 1) ? 'W' : 'S'));
    for (char ch : availability) {
        if (ch == req_card) {
            return true;
        }
    }
    return false;
}
Term::Term(std::string t, std::vector<Class> c) : term_type{std::move(t)}, classes{std::move(c)} {}
void Term::output(std::ostream &out_stream) {
    out_stream << term_type << ":\n";
    for (Class &c : classes) {
        out_stream << c.name << "\n";
    }
    out_stream << "\n";
}
void Schedule::output(std::ostream &out_stream) {
    for (Term t : terms) {
        t.output(out_stream);
    }
}
