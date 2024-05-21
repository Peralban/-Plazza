/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** MessageQueue for communication between threads
*/

#pragma once

#include <iostream>
#include <queue>
#include <mutex>

/**
 * @class MessageQueueThread
 * @brief A class to handle communication between threads using a message queue.
 * @tparam T The type of the messages in the queue.
 */
template <typename T>
class MessageQueueThread {
public:
    /**
     * @brief Default constructor for the MessageQueueThread class.
     */
    MessageQueueThread() = default;

    /**
     * @brief Default destructor for the MessageQueueThread class.
     */
    ~MessageQueueThread() = default;

    /**
     * @brief Pushes a message to the message queue.
     * @param message The message to be pushed.
     */
    void push(T message)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(message);
    }

    /**
     * @brief Pops a message from the message queue.
     * @return The popped message. If the queue is empty, returns a default-constructed object of type T.
     */
    T pop()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_queue.empty()) {
            return T();
        }
        T message = _queue.front();
        _queue.pop();
        return message;
    }

    /**
     * @brief Gets the message at the front of the queue without removing it.
     * @return The message at the front of the queue. If the queue is empty, returns a default-constructed object of type T.
     */
    [[nodiscard]] T front()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_queue.empty()) {
            return T();
        }
        return _queue.front();
    }

    /**
     * @brief Checks if the message queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool empty()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.empty();
    }

private:
    std::queue<T> _queue; ///< The queue used for storing messages.
    std::mutex _mutex; ///< The mutex used for synchronizing access to the queue.
};
