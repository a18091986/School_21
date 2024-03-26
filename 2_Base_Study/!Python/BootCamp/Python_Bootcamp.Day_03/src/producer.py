import json
import redis
import random
from typing import Optional
import logging

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO, filename='log.txt')

def generate_transaction(sender: Optional[str] = None, 
                         reciever: Optional[str] = None, 
                         amount: Optional[int] = None):
    if sender and reciever and amount:
        data = {
                "metadata": 
                    {
                    "from": sender,
                    "to": reciever
                    },
                 "amount": amount
                 }
    else:
        data = {
                "metadata": 
                    {
                    "from": random.randint(1000000000, 9999999999),
                    "to": random.randint(1000000000, 9999999999)
                    },
                 "amount": random.randint(-1000, 1000)
                 }

    return data

def insert_transaction(data: dict):
    with redis.Redis() as rc:
        rc.publish('some_channel', 
                json.dumps(data))

def check_sender_reciever(s_or_r: str):
    try:
        s_or_r = int(s_or_r)
        if 1000000000 <= s_or_r < 10000000000:
            return True
        else:
            return False
    except Exception as e:
        print(e)
        return False

def check_amount(amount: str):
    try:
        amount = int(amount)
        return True
    except Exception as e:
        print(e)
        return False


def get_data_for_transaction():
    while True:
        answer = input(f"Сгенерировать транзакцию автоматически - 1\n"
                    f"Ввести данные для транзакции вручную - 2\n"
                    f"Закончить - 0\n")
        if answer == '1':
            data = generate_transaction()
            print(data)
            logger.info(data)
            insert_transaction(data)
        elif answer == '2':
            while True:
                sender = input("Введите номер отправителя: ")
                reciever = input("Введите номер получателя: ")
                amount = input("Введите сумму: ")
                if all([check_sender_reciever(sender), 
                    check_sender_reciever(reciever),
                    check_amount(amount)]):
                    data = generate_transaction(int(sender), 
                                                int(reciever), 
                                                int(amount))
                    print(data)
                    logger.info(data)
                    insert_transaction(data)
                    break
        elif answer == '0':
            break
        


if __name__ == "__main__":
    get_data_for_transaction()
        
    


    