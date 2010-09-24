#include "message_log.h"

MessageLog* MessageLog::instance = NULL;

MessageLog::MessageLog() {
}

MessageLog::~MessageLog() {
    for (unsigned i = 0; i < messages.size(); i++) {
        delete messages.at(i);
    }
    messages.clear();
}

MessageLog* MessageLog::get_instance() {
    if (!instance) {
        instance = new MessageLog();
    }

    return instance;
}

void MessageLog::add_message(string msg) {
    get_instance()->messages.push_back(new string(msg));
}

void MessageLog::add_message(const char* msg) {
    get_instance()->messages.push_back(new string(msg));
}

vector<string*> MessageLog::latest_messages(unsigned count) {
    vector<string*> msgs;
    MessageLog* ml = get_instance();

    if (ml->messages.size() < count) {
        count = ml->messages.size();
    }

    msgs.resize(count);
    copy(ml->messages.end()-count, ml->messages.end(), msgs.begin());

    return msgs;
}
