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

template <typename T>
class MessageQueueThread {
public:
    MessageQueueThread() = default;
    ~MessageQueueThread() = default;

    void push(T message)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(message);
    }

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

    T front()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_queue.empty()) {
            return T();
        }
        return _queue.front();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.empty();
    }

private:
    std::queue<T> _queue;
    std::mutex _mutex;
};
