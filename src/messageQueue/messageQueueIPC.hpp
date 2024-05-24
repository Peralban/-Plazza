/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** MessageQueue for communication between processes
*/

#pragma once

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <fstream>

/**
 * @class MessageQueueIPC
 * @brief A class to handle inter-process communication using message queues.
 * @tparam T The type of the messages in the queue.
 * T must be a type that can be constructed from a string.
 * Strings must be constructable from T.
 */
template <typename T>
class MessageQueueIPC {
public:
    /**
     * @brief Constructor for the MessageQueueIPC class.
     * @param id The ID of the message queue.
     * Initializes the key and message queue ID.
     */
    explicit MessageQueueIPC(int id) : _key(0), _msg_id(0), _id(id) {
        std::string tmpfile = "/tmp/MessageQueueIPC_Plazza" + std::to_string(id);
        std::ofstream file(tmpfile);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot create tmpfile");
        }
        file.close();
        if (id <= 0) {
            throw std::runtime_error("Invalid id");
        }
        _key = ftok(tmpfile.c_str(), id);
        _msg_id = msgget(_key, 0666 | IPC_CREAT);
    }

    MessageQueueIPC() = delete;

    ~MessageQueueIPC() = default;

    /**
     * @brief Removes the message queue.
     */
    void destroy() {
        msgctl(_msg_id, IPC_RMID, nullptr);
    }

    /**
     * @brief Pushes a message to the message queue.
     * @tparam message The message to be pushed.
     */
    void push(T message)
    {
        message_buf buf = {};
        std::string message_str = message;
        strcpy(buf.mtext, message_str.c_str());
        buf.mtype = 1;
        msgsnd(_msg_id, &buf, sizeof(buf.mtext), IPC_NOWAIT);
    }

    /**
     * @brief Pops a message from the message queue.
     * @return The popped message.
     */
    T pop()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 0, IPC_NOWAIT);
        return T(buf.mtext);
    }

    /**
     * @brief Pops a message from the message queue at index.
     * @return The popped message.
     */
    T pop(int index)
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), index, IPC_NOWAIT);
        return T(buf.mtext);
    }

    /**
     * @brief Gets the message at the front of the queue without removing it.
     * @return The message at the front of the queue.
     */
    [[nodiscard]] T front()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 0, MSG_COPY | IPC_NOWAIT);
        return T(buf.mtext);
    }

    /**
     * @brief Gets the message at the specified index without removing it.
     * @return The message at the front of the queue.
     */
    [[nodiscard]] T operator[](int index)
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), index, MSG_COPY | IPC_NOWAIT);
        return T(buf.mtext);
    }

    /**
     * @brief Checks if the message queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool empty()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 0, MSG_COPY | IPC_NOWAIT);
        return buf.mtext[0] == 0;
    }

    /**
     * @brief Resets the message queue.
     */
    void reset()
    {
        msgctl(_msg_id, IPC_RMID, nullptr);
        _msg_id = msgget(_key, 0666 | IPC_CREAT);
    }

    /**
     * @brief Gets the size of the message queue.
     * @return The size of the message queue.
     */
    int size()
    {
        struct msqid_ds buf = {};
        msgctl(_msg_id, IPC_STAT, &buf);
        return (int)buf.msg_qnum;
    }

    [[ nodiscard ]] int getID() const
    {
        return _id;
    }

private:
    key_t _key; ///< The key used for the message queue.
    int _msg_id; ///< The ID of the message queue used for communication.
    int _id; ///< The ID of the message queue.

    /**
     * @struct message_buf
     * @brief A struct to hold the message type and text.
     */
    typedef struct msgbuf {
        long mtype; ///< The type of the message.
        char mtext[100]; ///< The text of the message.
    } message_buf;
};
