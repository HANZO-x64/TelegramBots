#define SQLITTERCPP_COMPILATE_DLL
#include <SQLiteCpp/SQLiteCpp.h>
#include <stdio.h>
#include <tgbot/tgbot.h>

using namespace std;
using namespace SQLite;

int main() {

    // Создание/открытие базы данных
    Database db("example.db3", OPEN_READWRITE | OPEN_CREATE);

    // Создание таблицы
    db.exec("CREATE TABLE person (id INTEGER PRIMARY KEY, name TEXT, age INT)");

    // Вставка данных
    Statement query(db, "INSERT INTO person (name, age) VALUES (?, ?)");
    query.bind(1, "John Doe");
    query.bind(2, 30);
    query.exec();

    // Выборка данных
    Statement select(db, "SELECT * FROM person");
    while (select.executeStep()) {

        int id = select.getColumn(0);
        string name = select.getColumn(1);
        int age = select.getColumn(2);

        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << std::endl;
    }

    return 0;

    TgBot::Bot bot("KEY");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
        });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, u8"Сообщение: " + message->text);
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
