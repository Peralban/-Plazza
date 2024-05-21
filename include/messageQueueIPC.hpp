/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>

class MessageQueueIPC {
public:
    MessageQueueIPC() {
        _key = ftok("tmpfile", 1);
        _msg_id = msgget(_key, 0666 | IPC_CREAT);
    }
    ~MessageQueueIPC() {
        msgctl(_msg_id, IPC_RMID, nullptr);
    }

    void push(std::string message)
    {
        message_buf buf = {};
        buf.mtype = 1;
        strcpy(buf.mtext, message.c_str());
        msgsnd(_msg_id, &buf, sizeof(buf.mtext), IPC_NOWAIT);
    }

    std::string pop()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 1, IPC_NOWAIT);
        return std::string(buf.mtext);
    }

    std::string front()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 0, MSG_COPY | IPC_NOWAIT);
        return std::string(buf.mtext);
    }

    bool empty()
    {
        message_buf buf = {};
        msgrcv(_msg_id, &buf, sizeof(buf.mtext), 0, MSG_COPY | IPC_NOWAIT);
        return buf.mtext[0] == 0;
    }

private:
    key_t _key;
    int _msg_id;

    typedef struct msgbuf {
        long mtype;
        char mtext[100];
    } message_buf;
};
