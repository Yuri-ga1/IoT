import numpy as np
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
import serial


def read_values(ser):
    x = []
    y = []
    num_points = int(ser.readline().decode('utf-8').strip())

    for _ in range(num_points):
        value = float(ser.readline().decode('utf-8').strip())
        distance = int(ser.readline().decode('utf-8').strip())
        x.append(value)
        y.append(distance)
    return x, y


def calculate_values(ser):
    values, distances = read_values(ser)
    X = np.array(values).reshape(-1, 1)
    Y = np.array(distances).reshape(-1, 1)
    model = LinearRegression()
    model.fit(X, Y)

    slope = model.coef_[0]
    intercept = model.intercept_

    show_data(model, slope, intercept, X, Y)


def show_data(model, slope, intercept, x, y):
    print(f'Уравнение линейной регрессии: y = {slope}, x + {intercept}')

    predictions = model.predict(x)

    plt.scatter(y, x, label='Исходные данные')
    plt.plot(predictions, x, color='red', label='Линейная регрессия')
    plt.xlabel('voltage')
    plt.ylabel('distance')
    plt.legend()
    plt.show()


def get_message(ser):
    mess = ser.read()
    message = mess
    while mess != "\n".encode():
        mess = ser.read()
        message += mess
        print(message)
    return message.decode('utf-8')


ser = serial.Serial('COM7', 9600)

while True:
    message = ser.readline().decode('utf-8').strip()
    print(message)

    if message == 'Введите диапазон:':
        min_value = int(input("Введите минимальное значение: "))
        max_value = int(input("Введите максимальное значение: "))
        ser.write(f"{min_value}\n".encode())
        ser.write(f"{max_value}\n".encode())
    if message == 'Build graph':
        calculate_values(ser)
        break

print("end")
ser.close()