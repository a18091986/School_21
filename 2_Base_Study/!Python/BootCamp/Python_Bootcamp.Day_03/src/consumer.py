import argparse
import redis
import json
import logging

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


logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO, filename='log.txt')

def process_message(message: bytes, recievers: list):
    transaction = json.loads(message)
    if recievers:
        if transaction.get('metadata').get('to') in recievers:
            if transaction.get('amount') >= 0:
                msg = dict(
                    metadata={"from":transaction.get('metadata').get('to'),
                            "to":transaction.get('metadata').get('from')}
                            ,amount=transaction.get('amount'))
                print(msg)
                logger.info(str(msg))
            else:
                print(transaction)
                logger.info(str(transaction))
        else:
            print(transaction)
            logger.info(str(transaction))
    else:
        print(transaction)
        logger.info(str(transaction))


if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument('-e', type=str, help='required')
    e = parser.parse_args().e
    recievers = [int(x) for x in e.split(',') if check_sender_reciever(x)]
    with redis.Redis() as rc:
        ps = rc.pubsub()
        ps.subscribe('some_channel')
        while True:
            transaction = ps.get_message()
            if transaction and isinstance(transaction.get('data'), bytes):
                process_message(transaction.get('data'), recievers)
    
