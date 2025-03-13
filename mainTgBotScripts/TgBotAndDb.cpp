#define BOOST_DISABLE_CURRENT_LOCATION  
#include <boost/variant.hpp> 
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <tgbot/tgbot.h>

// добавить макро-определение для воизбежаний ошибок
#define SQLITECPP_COMPILE_DLL
#include <SQLiteCpp/SQLiteCpp.h>

void saveMessage(const std::string& message) {
    try {
        // Открываем или создаем базу данных
        SQLite::Database db("messages.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // Создаем таблицу, если она не существует
        db.exec("CREATE TABLE IF NOT EXISTS Messages (ID INTEGER PRIMARY KEY AUTOINCREMENT, Message TEXT)");

        // Вставляем сообщение в таблицу
        SQLite::Statement query(db, "INSERT INTO Messages (Message) VALUES (?)");
        query.bind(1, message);
        query.exec();

    }
    catch (const SQLite::Exception& e) {
        std::cerr << "SQLite error: " << e.what() << std::endl;
    }
}

int main() {
    TgBot::Bot bot("7700896530:AAF3ACxMM5rM7L2ei_38VpMnZNNSxkwsqf4");

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        std::string text = message->text;
        std::cout << "Received message: " << text << std::endl;

        // Сохраняем сообщение в базе данных
        saveMessage(text);

        // Отвечаем пользователю
        bot.getApi().sendMessage(message->chat->id, "Message saved!");
        });

    // Запускаем бота
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