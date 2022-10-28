import telebot
import cezar
import vigener
from option import Options
from config import token
from telebot import types

bot = telebot.TeleBot(token)
options = Options()


@bot.message_handler(commands=["start"])
def start(message):
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    cipher = types.KeyboardButton("Зашифровать")
    decipher = types.KeyboardButton("Дешифровать")
    markup.add(cipher)
    markup.add(decipher)
    bot.send_message(message.chat.id, "Здравствуй, друг, выбери, что хочешь сделать", reply_markup=markup)


@bot.message_handler(content_types=["text"])
def take_message(message):
    cez_but = types.KeyboardButton("шифр Цезаря")
    vig_but = types.KeyboardButton("шифр Виженера")
    back_but = types.KeyboardButton("Главное меню")
    cipher = types.KeyboardButton("Зашифровать")
    decipher = types.KeyboardButton("Дешифровать")
    is_own_but = types.KeyboardButton("Да, свой")
    is_lat_but = types.KeyboardButton("Латиница или кириллица")
    is_have_but = types.KeyboardButton("Да, есть")
    no_but = types.KeyboardButton("Нет(")
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    if message.text == "Зашифровать" or message.text == "Дешифровать":
        if message.text == "Зашифровать":
            options.is_encrypt = 1
        else:
            options.is_encrypt = -1
        markup.add(cez_but, vig_but)
        markup.add(back_but)
        bot.send_message(message.chat.id, "Выбери же шифр!", reply_markup=markup)
    elif message.text == "Главное меню":
        options.is_cezar = 0
        options.is_vigener = 0
        options.is_encrypt = 0
        options.key = -1
        options.str_key = ""
        options.text = ""
        options.is_own = 0
        options.know_key = 0
        options.most_freq = ""
        options.alphabet = ""
        options.text = ""
        markup.add(cipher)
        markup.add(decipher)
        bot.send_message(message.chat.id, "Друг, выбери, что хочешь сделать", reply_markup=markup)
    elif message.text == "шифр Цезаря":
        options.is_cezar = 1
        markup.add(is_own_but, is_lat_but)
        markup.add(back_but)
        bot.send_message(message.chat.id, "У тебя свой алфавит?", reply_markup=markup)
    elif message.text == "шифр Виженера":
        options.is_vigener = 1
        markup.add(is_own_but, is_lat_but)
        markup.add(back_but)
        bot.send_message(message.chat.id, "У тебя свой алфавит?", reply_markup=markup)
    elif message.text == "Да, свой":
        options.is_own = 1
        markup.add(back_but)
        bot.send_message(message.chat.id, "Введи свой алфавит(слитно, не разделяя пробелами)", reply_markup=markup)
    elif message.text == "Латиница или кириллица":
        options.is_own = -1
        if options.is_cezar != 0:
            markup.add(is_have_but, no_but)
            markup.add(back_but)
            bot.send_message(message.chat.id, "У тебя есть ключ?", reply_markup=markup)
        else:
            markup.add(back_but)
            bot.send_message(message.chat.id, "Введи-ка ключ)", reply_markup=markup)
    elif message.text == "Да, есть":
        options.know_key = 1
        markup.add(back_but)
        bot.send_message(message.chat.id, "Вводи, чего ты ждёшь?!", reply_markup=markup)

    elif message.text == "Нет(":
        options.know_key = -1
        markup.add(back_but)
        if options.is_own != -1:
            options.is_own = 0
            options.most_freq = "0"
            bot.send_message(message.chat.id, "Введи самый встречающийся символ в твоём алфавите",
                             reply_markup=markup)
        else:
            bot.send_message(message.chat.id, "Не проблема(если текст большой), можешь вводить текст)",
                             reply_markup=markup)
    elif options.is_own == 1:
        options.is_own = 0
        options.alphabet = message.text
        if options.is_cezar != 0 and options.know_key == -1:
            options.most_freq = "0"
            markup.add(is_have_but, no_but)
            markup.add(back_but)
            bot.send_message(message.chat.id, "У тебя есть ключ?", reply_markup=markup)
        else:
            markup.add(back_but)
            bot.send_message(message.chat.id, "Введи-ка ключ", reply_markup=markup)
    elif options.most_freq == "0":
        options.most_freq = message.text
        markup.add(back_but)
        bot.send_message(message.chat.id, "Можешь вводить текст)", reply_markup=markup)
    elif options.key == -1 and options.is_cezar != 0 and options.know_key != -1 and \
            message.text not in options.str_buttons:
        options.key = int(message.text)
        markup.add(back_but)
        bot.send_message(message.chat.id, "Введи текст)", reply_markup=markup)
    elif options.str_key == "" and options.is_vigener != 0 and options.know_key != -1 and \
            message.text not in options.str_buttons:
        options.str_key = str(message.text)
        markup.add(back_but)
        bot.send_message(message.chat.id, "Введи текст)", reply_markup=markup)
    elif options.know_key == -1 or options.key != -1 and options.is_cezar != 0 \
            and message.text not in options.str_buttons:
        cez = cezar.Cezar(text=message.text, is_encrypt=options.is_encrypt, key=options.key, alphabet=options.alphabet,
                          most_freq=options.most_freq)
        markup.add(back_but)
        bot.send_message(message.chat.id, cez.cypher(), reply_markup=markup)
    elif options.str_key != 0 and options.is_vigener != 0 and message.text not in options.str_buttons:
        vig = vigener.Vigener(text=message.text, is_encrypt=options.is_encrypt, str_key=options.str_key,
                              alphabet=options.alphabet)
        markup.add(back_but)
        bot.send_message(message.chat.id, vig.cypher(), reply_markup=markup)


bot.polling(none_stop=True, interval=0)
