import random

def generate_random_floats(num):
    with open('test5.txt', 'w') as file:
        file.write(f"{num}\n")
        
        for _ in range(num):
            floats = [random.uniform(-1000, 1000.0) for _ in range(6)]
            file.write(' '.join(map(str, floats)) + '\n')

if __name__ == "__main__":
    try:
        num = random.randint(10,1000)
        generate_random_floats(num)
        print(f"Файл 'random_floats.txt' успешно создан с {num} строками.")
    except ValueError:
        print("Пожалуйста, введите корректное целое число.")
