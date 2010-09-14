#ifndef MESSAGE_LOG_H
#define MESSAGE_LOG_H

#include <vector>
#include <string>

using namespace std;

class MessageLog {
    private:
        vector<string*> messages;

        MessageLog();
        ~MessageLog();

        static MessageLog* instance;
        static MessageLog* get_instance();

    public:
        static void add_message(string* msg);
        static void add_message(const char* msg);
        static vector<string*> latest_messages(unsigned count);
};

#endif
