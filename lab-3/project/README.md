# Практическая работа №3 — проект (C++)

## Требования

* Установленный компилятор C++17:
  * Linux/macOS: `g++` или `clang++`
  * Windows: MinGW-w64 или MSVC (через Visual Studio Build Tools)
* CMake ≥ 3.14
* VSCode + расширения:
  * **C/C++**
  * **CMake Tools**

(опционально) Graphviz — для отрисовки УГП.

---

## Сборка проекта в VSCode

Из папки `project/`:
```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Debug
```

---

## Запуск тестов

**Выполните бинарник тестов напрямую:**
```bash
# Linux/macOS
./tests

# Windows
.\tests.exe
```
Пример вывода (ожидаемый):
```bash
Running 14 tests...

[PASS] buildBFromOddDigits 12345 -> 531
[PASS] buildBFromOddDigits 2468 -> 0
[PASS] buildBFromOddDigits -135 -> 531
[PASS] buildBFromOddDigits 0 -> 0
[PASS] maxEvenPositionWithEvenDigit 62543 -> 2
[PASS] maxEvenPositionWithEvenDigit 13579 -> 0
[PASS] maxEvenPositionWithEvenDigit 28462 -> 4
[PASS] cyclicRightShift 123456 k=2 -> 561234
[PASS] cyclicRightShift 123 k=0 -> 123
[PASS] cyclicRightShift 123 k=3 -> 123
[PASS] cyclicRightShift -12345 k=2 -> -45123
[PASS] sumEvenAboveSecondaryDiagonal square
[PASS] sumEvenAboveSecondaryDiagonal rect
[PASS] sumEvenAboveSecondaryDiagonal empty -> 0

=================== Test summary ===================
Total:  14
Passed: 14
Failed: 0
====================================================
```

## Описание
Этот проект содержит библиотеку `MyLib` с четырьмя функциями (вариант 3) и набор встроенных модульных тестов (без внешних тестовых фреймворков).

Реализованные функции:

* `buildBFromOddDigits(long long a)`  
  Формирует и возвращает целое число `b`, составленное из нечётных цифр числа `a`, **в обратном порядке**.  
  Пример: `a = 12345` → `b = 531`.

* `maxEvenPositionWithEvenDigit(long long n)`  
  Находит номер разряда `r` (нумерация **справа → налево**, младший разряд имеет номер 1), в котором находится максимальное значение среди **чётных номеров разрядов**, содержащих **чётные цифры**. Если таких разрядов нет — возвращает `0`.  
  Пример: `n = 62543` → разряды справа->налево: pos1=3,pos2=4,pos3=5,pos4=2,pos5=6 — среди чётных позиций (2 и 4) цифры `4` и `2`, максимум `4` в позиции `2` → результат `2`.

* `cyclicRightShift(long long n, int k)`  
  Возвращает число, полученное циклическим сдвигом цифр `n` **вправо** на `k` позиций. Отрицательные входы сохраняют знак.  
  Пример: `n = 123456`, `k = 2` → `561234`.

* `sumEvenAboveSecondaryDiagonal(const std::vector<std::vector<int>>& A)`  
  Находит сумму чётных значений компонентов двумерного массива `A`, лежащих **выше побочной диагонали** (условие: `j < cols - 1 - i`). При пустой матрице возвращает `0`.

---

## Управляющие графы программы (УГП)

В папке diagrams/ находятся .dot-файлы для функций:

- buildBFromOddDigits.dot
- maxEvenPositionWithEvenDigit.dot
- cyclicRightShift.dot
- sumEvenAboveSecondaryDiagonal.dot

Для генерации изображений (при установленном Graphviz):
```bash
dot -Tpng diagrams/buildBFromOddDigits.dot -o diagrams/buildBFromOddDigits.png
dot -Tpng diagrams/maxEvenPosDot.dot -o diagrams/maxEvenPosDot.png
dot -Tpng diagrams/cyclicRightShift.dot -o diagrams/cyclicRightShift.png
dot -Tpng diagrams/sumEvenAboveSecDiag.dot -o diagrams/sumEvenAboveSecDiag.png
```

В папке correct_diagrams/ находятся более читабельные .dot-версии
```bash
dot -Tpng correct_diagrams/buildBFromOddDigits.dot -o correct_diagrams/buildBFromOddDigits.png
dot -Tpng correct_diagrams/maxEvenPosDot.dot -o correct_diagrams/maxEvenPosDot.png
dot -Tpng correct_diagrams/cyclicRightShift.dot -o correct_diagrams/cyclicRightShift.png
dot -Tpng correct_diagrams/sumEvenAboveSecDiag.dot -o correct_diagrams/sumEvenAboveSecDiag.png
```
