#include "message_log.h"

MessageLog* MessageLog::instance = NULL;

MessageLog::MessageLog() {
}

MessageLog::~MessageLog() {
}

MessageLog* MessageLog::get_instance() {
    if (!instance) {
        instance = new MessageLog();
    }

    return instance;
}

void MessageLog::add_message(string* msg) {
    get_instance()->messages.push_back(msg);
}

void MessageLog::add_message(const char* msg) {
    get_instance()->messages.push_back(new string(msg));
}

vector<string*> MessageLog::latest_messages(unsigned count) {
    vector<string*> msgs;
    MessageLog* ml = get_instance();

    if (ml->messages.size() < count) {
        return ml->messages;
    }

    for (unsigned i = 0; i < count; i++) {
        string* s = ml->messages.at(ml->messages.size() - i - 1);
        msgs.push_back(s);
    }

    return msgs;
}
