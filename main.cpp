#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "Classes.h"
#include "CSP.h"
#include "include/Schedule.h"

using namespace std;

constexpr int TEACHERS_PER_SUBJECT = 4;
constexpr int SUBJECTS_PER_GROUP = 7;
constexpr int LESSONS_PER_DAY = 3;

template<typename T>
static vector<T> GetRandomSubset(vector<T> vec, size_t len) {
    shuffle(vec.begin(), vec.end(), mt19937(random_device()()));
    return {vec.begin(), vec.begin() + len};
}

static vector<Teacher> GetRandomSubsetOfTeachers(const vector<Teacher>& teachers) {
    return GetRandomSubset(teachers, TEACHERS_PER_SUBJECT);
}

static vector<Subject> GetRandomSubsetOfSubjects(const vector<Subject>& subjects) {
    return GetRandomSubset(subjects, SUBJECTS_PER_GROUP);
}

int main() {
    const vector<Day> days = {"Monday", "Tuesday", "Wednesday", "Thursday"}; // 4
    const vector<Teacher> teachers = {
            Teacher("Stadnyk"),
            Teacher("Pashko"),
            Teacher("Fedorus"),
            Teacher("Efremov"),
            Teacher("Krak"),
            Teacher("Trotsenko"),
            Teacher("Korobova"),
            Teacher("Krasovska"),
    }; // 8
    const vector<Room> rooms = {
            Room(1, 30),
            Room(2, 35),
            Room(3, 27),
            Room(4, 100),
            Room(5, 25),
            Room(6, 35),
    }; // 6
    const vector<Subject> subjects = {
            Subject("RPZ", GetRandomSubsetOfTeachers(teachers)),
            Subject("AI", GetRandomSubsetOfTeachers(teachers)),
            Subject("IS", GetRandomSubsetOfTeachers(teachers)),
            Subject("IT", GetRandomSubsetOfTeachers(teachers)),
            Subject("MMS", GetRandomSubsetOfTeachers(teachers)),
            Subject("SM", GetRandomSubsetOfTeachers(teachers)),
            Subject("TPR", GetRandomSubsetOfTeachers(teachers)),
            Subject("IAD", GetRandomSubsetOfTeachers(teachers)),
            Subject("English", GetRandomSubsetOfTeachers(teachers)),
    }; // 9
    const vector<Group> groups = {
            Group("TK-41", GetRandomSubsetOfSubjects(subjects), 20),
            Group("TK-42", GetRandomSubsetOfSubjects(subjects), 20),
            Group("MI-4", GetRandomSubsetOfSubjects(subjects), 26)
    };

    {
        int cnt = 0;
        for (int i = 0; i < 100; ++i) {
            CSPSolver cspSolver;
            cspSolver.SetVariables(groups, days, LESSONS_PER_DAY);
            cspSolver.SetDomains(rooms);
            auto schedule = cspSolver.Solve().schedule;
            const bool found = !schedule.empty();
            cnt += !found;
        }
        cout << "Not found: " << cnt << "\n";
    }

    CSPSolver cspSolver;
    cspSolver.SetVariables(groups, days, LESSONS_PER_DAY);
    cspSolver.SetDomains(rooms);
    auto schedule = cspSolver.Solve().schedule;

    cout << "=================================\n";

    for (const Day& mainDay : days) {
        cout << "[Day: " << mainDay << "]\n";

        for (auto&[group, schedulePerGroup] : schedule) {
            auto& listOfClasses = schedulePerGroup[mainDay];
            cout << "  Group: " << group.name << "\n";
            for (Class& class_ : listOfClasses) {
                cout << "  " << class_.time.number << ")\n";
                cout << "  room = " << class_.room.number << "\n";
                cout << "  lesson = " << class_.subject.name << "\n";
                cout << "  teacher = " << class_.teacher.name << "\n";
            }
            cout << "  --------------------\n";
        }
        cout << "=================================\n";
    }

    return 0;
}
