#include <stdio.h>
#include <tgbot/tgbot.h>
#include <iostream>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>
#include "../inc/config.hpp"

#define DEBUG
#define BOT

using namespace TgBot;

#ifdef BOT
void on_startBot()
{
    conf date;
    TgBot::Bot bot(date.API_TOKEN);
    
    TgBot::ReplyKeyboardMarkup button;
    TgBot::KeyboardButton keybut;
    
    // button.keyboard.data()

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi! " + message->chat->username);
    });
    
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Твое сообщение: " + message->text);
    });
    
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
}
#endif


int main(void)
{

#ifdef BOT
    std::cout << "START BOT" << std::endl;
#endif

    // on_startBot();

    try
    {
        SQLite::Database db("my_database.db");
        
        SQLite::Statement queri(db, "SELECT * FROM test WHERE size > ?");

        queri.bind(1, 2);

        while (queri.executeStep())
        {
            int id              = queri.getColumn(0);
            const char* value   = queri.getColumn(1);
            int size            = queri.getColumn(2);

            std::cout << "row: " << id << ", " << value << ", " << size << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

    return 0;
}