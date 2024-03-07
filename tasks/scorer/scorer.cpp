#include "scorer.h"

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> events_ptr(events.size());
    for (std::size_t index = 0; index < events_ptr.size(); index++) {
        events_ptr[index] = &events[index];
    }
    std::sort(events_ptr.begin(), events_ptr.end(),
              [](const Event* lhs, const Event* rhs) { return lhs->time < rhs->time; });
    while (!events_ptr.empty() && events_ptr.back()->time > score_time) {
        events_ptr.pop_back();
    }

    struct TaskState {
        EventType task_last_result = EventType::CheckFailed;
        bool merge_request_is_open = false;
    };
    std::map<std::pair<std::string, std::string>, TaskState> task_states;
    for (const Event* event_ptr : events_ptr) {
        auto [student_name, task_name, time, event_type] = *event_ptr;
        TaskState& state = task_states[{student_name, task_name}];
        switch (event_type) {
            case EventType::MergeRequestOpen: {
                state.merge_request_is_open = true;
            } break;
            case EventType::MergeRequestClosed: {
                state.merge_request_is_open = false;
            } break;
            default: {  // success or failed
                state.task_last_result = event_type;
            } break;
        }
    }

    ScoreTable result;
    for (auto [student_and_task, task_state] : task_states) {
        if (!task_state.merge_request_is_open && task_state.task_last_result == EventType::CheckSuccess) {
            result[student_and_task.first].insert(student_and_task.second);
        }
    }
    return result;
}
