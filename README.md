# SignatureCalculator

Требуется написать консольную программу на C++ для генерации сигнатуры указанного файла. <br>
Сигнатура генерируется следующим образом: <br>
исходный файл делится на блоки равной (фиксированной) длины
(если размер файла не кратен размеру блока, последний фрагмент может быть меньше или дополнен нулями до размера полного
блока). Для каждого блока вычисляется значение hash функции и дописывается в выходной файл-сигнатуру.

## Интерфейс:

командная строка, в которой указаны:

* Путь до входного файла
* Путь до выходной файла
* Размер блока (по умолчанию, 1 Мб)

## Обязательные требования:

* Следует максимально оптимизировать скорость работы утилиты с учетом работы в многопроцессорной среде
* Нужно реализовать правильную обработку ошибок на основе эксепшенов
* При работе с ресурсами нужно использовать умные указатели
* Не допускается использовать сторонние библиотеки OpenMP, OpenCL, etc

## Дополнительные требования:

* В задании не должно присутствовать неиспользуемого кода (как и других вариантов выполнения задания);
* Предпочтение лучше отдавать подходу ООП перед функциональным.

## Допущения:

* Размер входного файла может быть много больше размера доступной физической памяти (> 4 Гб)
* Разрешается использовать boost
* В качестве хэш функции можно использовать любую хэш функцию (MD5, CRC и т.д.)
