#include <bits/stdc++.h>
#include "Solver.h"
#include "Wrappers.h"

void Solver::read_prerequisites(const std::string &file_name) {
    std::ifstream file{file_name};
    std::string line, current_course, min_term = "1A";
    int difficulty;
    std::vector<std::vector<std::string>> prerequisites;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        if (current_course.empty()) {
            current_course = line;
        }
        else if (line[0] == '%') {
            difficulty = stoi(line.substr(1));
        }
        else if (line.size() == 2 && std::isdigit(line[0])) {
            min_term = line;
        }
        else if (line.size() <= 3) {
            this->classes[current_course] = Class(current_course, prerequisites, line, min_term, difficulty);
            current_course = ""; prerequisites = {}; min_term = "1A";
        }
        else {
            std::stringstream courses;
            courses << line;
            std::string tmp_course;
            std::vector<std::string> prerequisite;
            while (courses >> tmp_course) {
                prerequisite.emplace_back(tmp_course);
            }
            prerequisites.emplace_back(prerequisite);
        }
    }
}
void Solver::read_courses(const std::string &file_name) {
    std::ifstream file{file_name};
    std::string course_name;
    while (file >> course_name) {
        if (!this->classes.count(course_name)) {
            std::cerr << "Unable to find " << course_name << " in prerequisites. Did you type the name correctly?\n";
            exit(1);
        }
        this->wanted_classes.emplace_back(course_name);
    }
}
void Solver::read_sequence(const std::string &file_name) {
    std::ifstream file{file_name};
    std::string term_type;
    std::vector<std::string> valid_term_types = {"1A", "1B", "2A", "2B", "3A", "3B", "4A", "4B", "WT1", "WT2", "WT3", "WT4", "WT5", "WT6", "OFF"};
    while (file >> term_type) {
        transform(term_type.begin(), term_type.end(), term_type.begin(), ::toupper);
        bool in_types = false;
        for (const std::string &type : valid_term_types) {
            in_types |= type == term_type;
        }
        if (!in_types) {
            std::cerr << "Invalid type in sequence (" << term_type << "). Did you type the sequence correctly?\n";
            exit(1);
        }
        this->sequence.emplace_back(term_type);
    }
    if (this->sequence.size() != 14 && this->sequence.size() != 15) {
        std::cerr << "Invalid sequence length. Did you copy your sequence correctly?\n";
        exit(1);
    }
}
void Solver::read_fixed_schedule(const std::string &file_name) {
    std::ifstream file{file_name};
    std::string line, term;
    std::vector<Class> courses;
    while (std::getline(file, line)) {
        if (line.size() == 2 && std::isdigit(line[0])) {
            if (!courses.empty()) {
                this->set_schedule[term] = Term(term, courses);
                courses = {};
            }
            term = line;
        }
        else if (!line.empty()) {
            courses.emplace_back(this->classes[line]);
        }
    }
    if (!courses.empty()) {
        this->set_schedule[term] = Term(term, courses);
    }
}
std::vector<Schedule> Solver::apply_heuristic(std::vector<Schedule> &schedules) {
    int best_score = INT_MAX;
    std::vector<Schedule> results;
    for (Schedule &s : schedules) {
        int cur_score = 0;
        for (int term = 0, shift = 0; term < this->sequence.size(); term++) {
            //Skip work terms or fixed terms:
            if (!isdigit(this->sequence[term][0])) {
                continue;
            }
            if (!this->set_schedule.count(this->sequence[term])) {
                int term_score = 0;
                for (const Class &c : s.terms[shift].classes) {
                    term_score += c.difficulty;
                }
                cur_score = std::max(term_score, cur_score);
            }
            shift++;
        }
        if (cur_score < best_score) {
            best_score = cur_score;
            results = {s};
        }
        else if (cur_score == best_score) {
            results.push_back(s);
        }
    }
    return results;
}
void Solver::solve(const std::string &file_name) {
    std::vector<Schedule> schedules = {{}};
    for (int term = 0; term < this->sequence.size(); term++) {
        //If we are a work term, do not schedule classes for it:
        if (!isdigit(this->sequence[term][0])) {
            continue;
        }
        //If this term is already specified, do not overwrite it:
        if (this->set_schedule.count(this->sequence[term])) {
            for (Schedule &schedule : schedules) {
                schedule.terms.push_back(this->set_schedule[this->sequence[term]]);
                for (Class &c : this->set_schedule[this->sequence[term]].classes) {
                    schedule.courses.insert(c.name);
                }
            }
            continue;
        }
        //Now, consider ALL possible classes we can use (5 courses per term):
        std::vector<Schedule> next_schedules;
        for (Schedule schedule : schedules) {
            for (int i = 0; i < this->wanted_classes.size(); i++) {
                std::string &c1 = this->wanted_classes[i];
                if (!this->classes[c1].is_availabile(term) || schedule.courses.count(c1) ||
                    !this->classes[c1].has_prerequisites(schedule.courses, this->classes[c1].prerequisites))
                    continue;
                for (int j = i + 1; j < this->wanted_classes.size(); j++) {
                    std::string &c2 = this->wanted_classes[j];
                    if (!this->classes[c2].is_availabile(term) || schedule.courses.count(c2) ||
                        !this->classes[c2].has_prerequisites(schedule.courses, this->classes[c2].prerequisites))
                        continue;
                    for (int k = j + 1; k < this->wanted_classes.size(); k++) {
                        std::string &c3 = this->wanted_classes[k];
                        if (!this->classes[c3].is_availabile(term) || schedule.courses.count(c3) ||
                            !this->classes[c3].has_prerequisites(schedule.courses, this->classes[c3].prerequisites))
                            continue;
                        for (int l = k + 1; l < this->wanted_classes.size(); l++) {
                            std::string &c4 = this->wanted_classes[l];
                            if (!this->classes[c4].is_availabile(term) || schedule.courses.count(c4) ||
                                !this->classes[c4].has_prerequisites(schedule.courses, this->classes[c4].prerequisites))
                                continue;
                            for (int m = l + 1; m < this->wanted_classes.size(); m++) {
                                std::string &c5 = this->wanted_classes[m];
                                if (!this->classes[c5].is_availabile(term) || schedule.courses.count(c5) ||
                                    !this->classes[c5].has_prerequisites(schedule.courses, this->classes[c5].prerequisites))
                                    continue;
                                Term next_term = Term(this->sequence[term], {this->classes[c1], this->classes[c2], this->classes[c3], this->classes[c4], this->classes[c5]});
                                for (Class &c : next_term.classes) {
                                    schedule.courses.insert(c.name);
                                }
                                schedule.terms.emplace_back(next_term);
                                next_schedules.emplace_back(schedule);
                                schedule.terms.pop_back();
                                for (Class &c : next_term.classes) {
                                    schedule.courses.erase(c.name);
                                }
                            }
                        }
                    }
                }
            }
        }
        schedules = next_schedules;
    }
    std::cout << "Found " << schedules.size() << " possible schedules!\n";
    schedules = apply_heuristic(schedules);
    std::cout << "Found " << schedules.size() << " possible schedules (after heuristic)!\n";
    if (!schedules.empty()) {
        std::cout << "Possible sample schedule:\n";
        schedules[0].output(std::cout);
        std::cout << "(Note: other schedules were written to " << file_name << ".)\n";
        std::ofstream output_file(file_name);
        for (Schedule s : schedules) {
            s.output(output_file);
        }
    }
    else {
        std::cerr << "No schedules found. Did you specify 40 courses to take?\n";
    }
}
