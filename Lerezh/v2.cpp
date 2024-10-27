#include <stdio.h>
#include <tgbot/tgbot.h>
#include <Magick++.h>
#include <string>

using namespace std;
using namespace TgBot;
using namespace Message;
using namespace Magick;

Image createGraph(int sizeX, int sizeY, string colorDraw)
{
    Image image(Geometry(sizeX, sizeY), Color("white"));

    // Здесь должен быть ваш код для создания изображения с графиком
    // Используйте Magick++ API для рисования на изображении
}

//-- Name bot: Math bot Venjuh
int main()
{
    setlocale(LC_ALL, "Russian");
    
    bool ChangingSettings = fa;
    int sizeX = 800;
    int sizeY = 600;
    
    // Создание изображения
    bot.getEvents().onCommand("graph", [&bot](TgBot::Message::Ptr message)
    {
        try 
        {
            Image graph = createGraph(sizeX, sizeY);
            // Сохраняем изображение
            graph.write("graph.png");
            // Отправляем изображение в чат
            InputFile::Ptr graphFile(new TgBot::InputFile("graph.png"));
            bot.getApi().sendPhoto(message->chat->id, graphFile);
        } 
        
        catch (Magick::Exception& e) 
        {
            bot.getApi().sendMessage(message->chat->id, "Произошла ошибка при создании графика: " + std::string(e.what()));
        }
    });
    
    
    
    // Подключение бота
    Bot bot("--> Link on bot <--");
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "Venjuh v.1");
        bot.getApi().sendMessage(message->chat->id, u8"/fun1 - позволит вести вести функцию f(x).");
        bot.getApi().sendMessage(message->chat->id, u8"/settings - изменить параметры бота.");
        
    });
    bot.getEvents().onCommand("settings", [&bot](TgBot::Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, u8"Настройки бота");
        bot.getApi().sendMessage(message->chat->id, u8"/axisX - ось Х = ");
        bot.getApi().sendMessage(message->chat->id, u8"/settings - изменить параметры бота.");
        
        
    });
    
    // Команды бота
    bot.getEvents().onAnyMessage([&bot](Ptr message)
    {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/fun1")) {
            bot.getApi().sendMessage(message->chat->id, "Привет! Я бот, который проверяет ваши сообщения.");
        }
        else { return; }
        
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });
    
    // Ошибки выполнеиня
    try
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgLongPoll longPoll(bot);
        
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();
        }
        
    } 
    
    catch (TgBot::TgException& e) 
    {
        printf("error: %s\n", e.what());
    }
    return 0;
}
