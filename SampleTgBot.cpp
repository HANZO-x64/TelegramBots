/*
*   У меня код работал в:
*	1) Visual Studion 2022 (143v)
*   2) SDK 10.0 (latest installed version)
*	3) C++ Language Standard: C++ 17
*   4) Default (Legacy MSVC): Default (Legacy MSVC)
*	5) vcpkg:
*		    tgbot-cpp
*		    tgbot-cpp:x64-windows
*/

#define BOOST_DISABLE_CURRENT_LOCATION
#include <boost/variant.hpp> 
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <tgbot/tgbot.h>

int main() {
    TgBot::Bot bot("TOKEN");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
        });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
        });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}