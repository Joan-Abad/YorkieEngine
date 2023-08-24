#include <iostream>
#include <vector>
#include <functional>

// Define the type for the callback function
using CallbackFunction = std::function<void()>;

// Event class to manage subscribers and notify them when an event occurs
class Event {
public:
    // Function to subscribe a callback
    void subscribe(CallbackFunction callback) {
        callbacks.push_back(callback);
    }

    // Function to notify all subscribers
    void notify() {
        for (const auto& callback : callbacks) {
            callback();
        }
    }

private:
    std::vector<CallbackFunction> callbacks;
};