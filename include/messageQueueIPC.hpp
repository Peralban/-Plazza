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

/**
 * @class MessageQueueIPC
 * @brief A class to handle inter-process communication using message queues.
 */
class MessageQueueIPC {
public:
    /**
     * @brief Constructor for the MessageQueueIPC class.
     * Initializes the key and message queue ID.
     */
    MessageQueueIPC() {
        _key = ftok("tmpfile", 1);
        _msg_id = msgget(_key, 0666 | IPC_CREAT);
    }

    /**
     * @brief Destructor for the MessageQueueIPC class.
     * Removes the message queue.
     */
    ~MessageQueueIPC() {
        msgctl(_msg_id, IPC_RMID, nullptr);
    }

    /**
     * @brief Pushes a message to the message queue.
     * @param message The message to be pushed.
     */
    void push(std::string message)
    {
        message_buf buf = {};
        buf.mtype = 1;
        strcpy(buf.mtext, message.c_str());
        msgsnd(_msg_id, &buf, sizeof(buf.mtext), IPC_NOWAIT);
    }

    /**
     * @brief Pops a message from the message queue.
     * @return The popped message.
     */
    std::string pop()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 1, IPC_NOWAIT);
        return std::string(buf.mtext);
    }

    /**
     * @brief Gets the message at the front of the queue without removing it.
     * @return The message at the front of the queue.
     */
    [[nodiscard]] std::string front()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 0, MSG_COPY | IPC_NOWAIT);
        return std::string(buf.mtext);
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

private:
    key_t _key; ///< The key used for the message queue.
    int _msg_id; ///< The ID of the message queue.

    /**
     * @struct message_buf
     * @brief A struct to hold the message type and text.
     */
    typedef struct msgbuf {
        long mtype; ///< The type of the message.
        char mtext[100]; ///< The text of the message.
    } message_buf;
};
