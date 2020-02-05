#include <executors/executors.h>


//Task
bool Task::isCompleted()
{
    return (status == TaskStatus::Completed);
}

bool Task::isFailed()
{
    return (status == TaskStatus::Failed);
}

bool Task::isCanceled()
{
    return (isCompleted() || isFailed() || isCanceled());
}

bool Task::isFinished()
{
    return(isCompleted() || isFailed() || isCanceled());
}

bool Task::isProcessing()
{
    return (status == TaskStatus::Processing);
}

bool Task::isAwaiting()
{
    return (status == TaskStatus::Awaiting);
}

std::exception_ptr Task::getError()
{
    return eptr;
}

void Task::addTrigger(std::shared_ptr<Task> trigger)
{
    have_trigger = true;
    trigger->triggers.push_back(shared_from_this());
}

void Task::addDependency(std::shared_ptr<Task> dependency)
{
    dependencies.push_back(dependency);   
}

void Task::setTimeTrigger(std::chrono::system_clock::time_point at)
{
    if (!have_time_trigger) {
        have_time_trigger = true;
        deadline = at;
    }
}

void Task::cancel()
{
    TaskStatus temp_status = TaskStatus::Awaiting;
    status.compare_exchange_strong(temp_status, TaskStatus::Canceled);
}

void Task::wait()
{
    while (!isFinished()) {}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
