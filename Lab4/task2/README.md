Примеры команд:

1) Загрузка массива из файла:
Load A, /home/dmitry/C/Labs2/Lab4/task2/in1.txt;
Load B, /home/dmitry/C/Labs2/Lab4/task2/in2.txt;
A — имя массива.
in.txt — имя файла, который должен существовать и содержать числа.


2) Сохранение массива в файл:
Save A, /home/dmitry/C/Labs2/Lab4/task2/out1.txt;
Save B, /home/dmitry/C/Labs2/Lab4/task2/out2.txt;
A — имя массива.
output.txt — имя файла, в который сохраняется массив.


3) Заполнение массива случайными числами:
Rand A, 10, 1, 100;
A — имя массива.
10 — количество чисел.
1, 100 — диапазон случайных чисел.


4) Конкатенация двух массивов:
Concat A, B;
A — имя первого массива.
B — имя второго массива.


5) Удаление элементов из массива:
Remove A, 3, 2;
A — имя массива.
3 — индекс, с которого начнется удаление.
2 — количество элементов для удаления.


6) Копирование элементов из одного массива в другой:
Copy A, 2, 5, B;
A — имя массива-источника.
2, 5 — диапазон индексов элементов для копирования.
B — имя массива-назначения.


7) Cортировка массива:
Sort A, A+;
A — имя массива.
A+ — сортировка по возрастанию (или A- для убывания).


8) Перемешивание массива:
Shuffle A;

9) Вывод статистики массива:
Stats A;

10) Печать массива:

Все элементы:
Print A, all;

Элемент по индексу:
Print A, 3;

Диапазон элементов:
Print A, 2 5;

11) Очистка массива:
Free A;