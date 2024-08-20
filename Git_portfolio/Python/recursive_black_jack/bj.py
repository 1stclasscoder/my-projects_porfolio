import telebot
bot = telebot.TeleBot(token='6409595177:AAHOXWY5j49TMPDNtvHjWkWf1koZdUHLwZw')
from telebot import types
from multiprocessing.dummy import Pool
pool = Pool(20)
result = 0
flag_global = 0

def executor(fu):
    def run(*a,**kw):
        pool.apply_async(fu, a, kw, callback=lambda result: None, error_callback=lambda error: print(error))

    return run


def output_score(sum_two_cards, flag_tuz, message):
    # print("Your sum is", sum_two_cards, end = " ")
    msg = "Your sum is " + str(sum_two_cards)
    if flag_tuz > 0:
        for i in range(1, flag_tuz+1):
            if sum_two_cards - 10*i > 0:
                msg += " or " + str((sum_two_cards - 10*i))
                # print ("or", sum_two_cards - 10*i, end = " ")
    bot.send_message(message.from_user.id, msg)
    # print("")

def choice_card2(message):
    @bot.message_handler(func=lambda message: True)
    def handle_start01(message):
        keyboard = types.InlineKeyboardMarkup()
        key_one = types.InlineKeyboardButton(text='split',  callback_data='2')
        keyboard.add(key_one)
        key_two = types.InlineKeyboardButton(text='/hit',  callback_data='1')
        keyboard.add(key_two)
        bot.send_message(message.from_user.id, text='Please choose your decision: split - 2 or hit - 1:', reply_markup=keyboard)
    handle_start01()

    @bot.message_handler(func=lambda message: True)
    def handle_start2():
        print('', end = '')
    @bot.callback_query_handler(func=lambda call: True)
    def handle_callback_query(call):
        global result
        result = int(call.data)
    while result == 0:
        handle_start2()

def choice_card(flag, message):
    @bot.message_handler(func=lambda message: True)
    def handle_start00(flag, message):
        keyboard = types.InlineKeyboardMarkup()
        # По очереди готовим текст и обработчик для каждой карты
        key_two = types.InlineKeyboardButton(text='2', callback_data='2')
        # И добавляем кнопку на экран
        keyboard.add(key_two)
        key_three = types.InlineKeyboardButton(text='3', callback_data='3')
        keyboard.add(key_three)
        key_four = types.InlineKeyboardButton(text='4', callback_data='4')
        keyboard.add(key_four)
        key_five = types.InlineKeyboardButton(text='5', callback_data='5')
        keyboard.add(key_five)
        key_six = types.InlineKeyboardButton(text='6', callback_data='6')
        keyboard.add(key_six)
        key_seven = types.InlineKeyboardButton(text='7', callback_data='7')
        keyboard.add(key_seven)
        key_eight = types.InlineKeyboardButton(text='8', callback_data='8')
        keyboard.add(key_eight)
        key_nine = types.InlineKeyboardButton(text='9', callback_data='9')
        keyboard.add(key_nine)
        key_ten = types.InlineKeyboardButton(text='10', callback_data='10')
        keyboard.add(key_ten)
        key_tuz = types.InlineKeyboardButton(text='11', callback_data='11')
        keyboard.add(key_tuz)
        # Показываем все кнопки сразу и пишем сообщение о выборе
        if flag == 1:
            bot.send_message(message.from_user.id, text='Выбери карту дилера:', reply_markup=keyboard)
        elif flag == 2:
            bot.send_message(message.from_user.id, text='Выбери свою карту:', reply_markup=keyboard)
    handle_start00(flag, message)

    @bot.message_handler(func=lambda message: True)
    def handle_start(flag, message):
        print("", end = '')
        
    @bot.callback_query_handler(func=lambda call: True)
    def handle_callback_query(call):
        global result
        result = int(call.data)
    while result == 0:
         handle_start(flag,message)

def equal_cards(dealers_card, sum_cards, decision):
    if sum_cards / 2 == 2:
        if 2 <= dealers_card <= 3:
            decision = 5
        elif 4 <= dealers_card <= 7:
            decision = 4
        else:
            decision = 3
    if sum_cards / 2 == 3:
        if 2 <= dealers_card <= 3:
            decision = 5
        elif 4 <= dealers_card <= 7:
            decision = 4
        else:
            decision = 3
    if sum_cards / 2 == 4:
        if 5 <= dealers_card <= 6:
            decision = 5
        else:
            decision = 3
    if sum_cards / 2 == 5:
        if 2 <= dealers_card <= 9:
            decision = 1
        else:
            decision = 3
    if sum_cards / 2 == 6:
        if dealers_card == 1:
            decision = 5
        elif 3 <= dealers_card <= 6:
            decision = 4
        else:
            decision = 3
    if sum_cards / 2 == 7:
        if 2 <= dealers_card <= 7:
            decision = 4
        else:
            decision = 3
    if sum_cards / 2 == 8:
        decision = 4
    if sum_cards / 2 == 9:
        if dealers_card == 7 or 10 <= dealers_card <= 11:
            decision = 2
        else:
            decision = 3
    if sum_cards / 2 == 10:
        decision = 2
    if sum_cards / 2 == 11:
        decision = 4
    return decision

def chec_tuz(dealers_card, sum_cards, decision, flag_tuz):
    if sum_cards - 11*flag_tuz == 2:
        if 5 <= dealers_card <= 6:
            decision = 1
        else:
            decision = 3
    elif sum_cards - 11*flag_tuz == 3:
        if 5 <= dealers_card <= 6:
            decision = 1
        else:
            decision = 3            
    elif sum_cards - 11*flag_tuz == 4:
        if 4 <= dealers_card <= 6:
            decision = 1
        else:
            decision = 3
    elif sum_cards - 11*flag_tuz == 5:
        if 4 <= dealers_card <= 6:
            decision = 1
        else:
            decision = 3
    elif sum_cards - 11*flag_tuz == 6:
        if 3 <= dealers_card <= 6:
            decision = 1
        else:
            decision = 3  
    elif sum_cards - 11*flag_tuz == 7:
        if dealers_card == 2 or 7 <= dealers_card <= 8:
            decision = 2
        elif 3 <= dealers_card <= 6:
            decision = 1
        else:
            decision = 3  
    elif sum_cards - 11*flag_tuz == 8:
        decision = 2
    elif sum_cards - 11*flag_tuz == 9:
        decision = 2
    elif sum_cards - 11*flag_tuz == 10:
        decision = 2
    return decision

def check_without_flags(dealers_card, sum_cards, decision):
    if 2 <= sum_cards <= 7:
        decision = 3 
    if sum_cards == 8:
        decision = 3
    elif sum_cards == 9:
        if 3 <= dealers_card <= 6:
            decision = 1
        else:
            decision = 3
    elif sum_cards == 10:
        if 2 <= dealers_card <= 9:
            decision = 1
        else:
            decision = 3
    elif sum_cards == 11:
        if 2 <= dealers_card <= 10:
            decision = 1
        else:
            decision = 3
    elif sum_cards == 12:
        if 4 <= dealers_card <= 6:
            decision = 2
        else:
            decision = 3
    elif sum_cards == 13:
        if 2 <= dealers_card <= 6:
            decision = 2
        else:
            decision = 3
    elif sum_cards == 14:
        if 2 <= dealers_card <= 6:
            decision = 2
        else:
            decision = 3
    elif sum_cards == 15:
        if 2 <= dealers_card <= 6:
            decision = 2
        elif dealers_card == 10:
            decision = 6
        else:
            decision = 3
    elif sum_cards == 16:
        if 2 <= dealers_card <= 6:
            decision = 2
        elif 9 <= dealers_card <= 11:
            decision = 6
        else:
            decision = 3
    elif sum_cards == 17 or sum_cards == 18 or sum_cards == 19 or sum_cards == 20:
        decision = 2
    elif sum_cards == 21:
        decision = 7
    
    return decision

def input_dealer_card(message):
    flag_error = 0
    flag_dealer = 1
    card = 0
    choice_card(flag_dealer, message)
    global result
    card = result
    result = 0
    if card >= 12 or card <= 1:
        flag_error = 1
    return card, flag_error

def input_your_cards(sum_two_cards, cnt, cnt_split, flag_tuz, flag_equal, message):
    card1 = 0
    card2 = 0
    flag_error = 0
    flag_your_card = 2
    choice_card(flag_your_card, message)
    global result
    card1 = result
    result =0
    if card1 == 11:
        flag_tuz += 1
    if sum_two_cards == card1 and cnt_split == 1:
        flag_equal = 1
    if cnt == 0 and cnt_split != 1:
        choice_card(flag_your_card, message)
        card2 = result
        result = 0
        if card2 >= 12 or card2 <= 1:
            flag_error = 1
        if card2 == 11:
            flag_tuz += 1
    if card1 == card2 and cnt == 0:
        flag_equal = 1
    if card1 >= 12 or card1 <= 1:
        flag_error = 1
    sum_two_cards += card1 + card2
    if flag_error != 1:
        output_score(sum_two_cards, flag_tuz, message)
    return sum_two_cards, flag_tuz, flag_equal, flag_error

def choose_decision(dealers_card, sum_cards, flag_tuz, flag_equal):
    decision = 0
    if flag_equal == 1:
        decision = equal_cards(dealers_card, sum_cards, decision)
    elif flag_tuz > 1 and sum_cards - 11*flag_tuz <= 9:
        decision = chec_tuz(dealers_card, sum_cards, decision)
    else:
        decision = check_without_flags(dealers_card, sum_cards, decision)
    if sum_cards - flag_tuz*10 > 21:
        decision = 8
    return decision

def output_decision(decision, message):
    words = "You should "
    if decision == 1:
        bot.send_message(message.from_user.id, words + "double")
        # print(words, "double")
    elif decision == 2:
        bot.send_message(message.from_user.id, words + "stop")
        # print(words, "stop")
    elif decision == 3:
        bot.send_message(message.from_user.id, words + "hit")
        # print(words, "hit")
    elif decision == 4:
        bot.send_message(message.from_user.id, words + "split")
        # print(words, "split")
    elif decision == 5:
        bot.send_message(message.from_user.id, words + "split or hit")
        # print(words, "split or hit")
        global result
        choice_card2()
        x = result
        result = 0
        if x == 1:
            decision = 4
        elif x == 2:
            decision = 3
    elif decision == 6:
        bot.send_message(message.from_user.id, "Surrender if allowed or hit")
        # print(words, "surrender if allowed or hit")
    elif decision == 7:
        bot.send_message(message.from_user.id, "You are scored 21")
        # print("You are score 21")
    elif decision == 8:
        bot.send_message(message.from_user.id, "You lose(")
        # print("You lose(")
    else:
        bot.send_message(message.from_user.id, "Something was wrong")
        # print("Something was wrong:")
    return decision

def split_function(dealers_card, sum_cards, flag_tuz, message):
    sum_cards = int(sum_cards/2)
    cnt_split = 1
    bot.send_message(message.from_user.id, "Split game")
    # print ("Split game", sum_cards)
    process_game_function(cnt_split, sum_cards, dealers_card, flag_tuz, message)
    bot.send_message(message.from_user.id, "Split game")
    # print ("Split game", sum_cards)
    process_game_function(cnt_split, sum_cards, dealers_card, flag_tuz, message)
    cnt_split = 0

def process_game_function(cnt_split, sum_cards, dealers_card, flag_tuz, message):
    decision = 0
    cnt = 0
    flag_exit = 0
    flag_error = 0
    if cnt_split == 1 and flag_tuz == 2:
        flag_tuz = 1
    else:
        flag_tuz = 0
    while flag_exit !=1:
        flag_equal = 0
        if cnt == 0 and cnt_split == 0:
            dealers_card, flag_error = input_dealer_card(message)
        sum_cards, flag_tuz, flag_equal, flag_error = input_your_cards(sum_cards, cnt, cnt_split, flag_tuz, flag_equal, message)
        if flag_error == 1:
            bot.send_message(message.from_user.id, "UNCORRECT information")
            # print ("UNCORRECT information")
            break
        decision = choose_decision(dealers_card, sum_cards, flag_tuz, flag_equal)
        decision = output_decision(decision, message)
        if decision == 2 or decision == 1 or decision == 6 or decision == 7 or decision == 8 or decision == 0:
            flag_exit = 1
        elif decision == 4:
            split_function(dealers_card, sum_cards, flag_tuz, message)
            flag_exit = 1
        cnt += 1
@bot.message_handler(commands=['text'])
def start1(message):
    bot.send_message(message.from_user.id, "Please write /start if you want to begin")
@bot.message_handler(commands=['start'])
def start(message):
    # print("xxx")
        bot.send_message(message.from_user.id, "NEW GAME!")
        process_game_function(0, 0, 0, 0, message)
    

bot.polling(none_stop=True)