#include "Solver.h"

int main() {
    Solver solver = Solver();
    solver.read_prerequisites("prerequisites.txt");
    solver.read_courses("wanted courses.txt");
    solver.read_sequence("sequence.txt");
    solver.read_fixed_schedule("fixed schedule.txt");
    solver.solve("possible schedules.txt");
}
