#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Room {
    int number{};
    size_t capacity{};

    Room() = default;

    explicit Room(int roomNumber, size_t roomCapacity) :
            number(roomNumber), capacity(roomCapacity) {}

    bool operator==(const Room& other) const {
        return capacity == other.capacity && number == other.number;
    }
};

struct Teacher {
    string name;

    Teacher() = default;

    explicit Teacher(string teacherName) : name(move(teacherName)) {}

    bool operator==(const Teacher& other) const {
        return name == other.name;
    }
};

struct Subject {
    string name;
    vector<Teacher> teachers;

    Subject() = default;

    explicit Subject(string subjectName, vector<Teacher> subjectTeachers) :
            name(move(subjectName)), teachers(move(subjectTeachers)) {}
};

struct Group {
    int id;
    string name;
    vector<Subject> subjects;
    size_t size{};

    Group() : id(counter++) {}

    explicit Group(string groupName, vector<Subject> groupSubjects, const size_t groupSize) :
            id(counter++), name(move(groupName)), subjects(move(groupSubjects)), size(groupSize) {}

    bool operator<(const Group& other) const {
        return id < other.id;
    }

    bool operator==(const Group& other) const {
        return id == other.id;
    }

    Group& operator=(const Group& other) {
        if (this != &other) {
            this->id = other.id;
            this->name = other.name;
            this->subjects = other.subjects;
            this->size = other.size;
        }
        return *this;
    }

private:
    static int counter;
};

using Day = string;

struct Time {
    Day day;
    size_t number{};

    Time() = default;

    explicit Time(Day day_, size_t number_) : day(move(day_)), number(number_) {}

    bool operator == (const Time& other) const {
        return number == other.number && day == other.day;
    }
};

struct Class {
    Group group;
    Subject subject;
    Room room;
    Teacher teacher;
    Time time;

    Class() = default;

    Class(const Group& classGroup,
          Subject classSubject,
          const Room& classRoom,
          Teacher classTeacher,
          Time classTime) :
            group(classGroup),
            subject(move(classSubject)),
            room(classRoom),
            teacher(move(classTeacher)),
            time(move(classTime)) {}
};