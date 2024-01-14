import random
import string
import subprocess

def generate_random_string(length):
    return ''.join(random.choices(string.ascii_lowercase, k=length))


text = generate_random_string(100)
pattern_length = random.randint(1, 10)
pattern = text[random.randint(0, 90): random.randint(0, 90) + pattern_length]
with open('text_file.txt', 'w') as text_file:
    text_file.write(text)

with open('pattern_file.txt', 'w') as pattern_file:
    pattern_file.write(pattern)

