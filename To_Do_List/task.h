#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
public:
    Task(const QString &description, bool completed = false)
        : description(description), completed(completed)
    {}

    bool isCompleted() const { return completed; }
    QString getDescription() const { return description; }
    // Function to mark a task as completed
    void setCompleted(bool completed) { this -> completed = completed; }

private:
    QString description;
    bool completed;
};

#endif // TASK_H
