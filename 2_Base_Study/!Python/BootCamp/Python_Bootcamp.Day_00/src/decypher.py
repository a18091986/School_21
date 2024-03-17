import argparse


def form_out_string(input_string: str):
    print(''.join([x.strip()[0].lower() for x in input_string.split(' ')]))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('text', type=str, help='required string')
    form_out_string(parser.parse_args().text)

