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

##  Запуск тестов

Выполните бинарник тестов напрямую:

```bash
# Linux/macOS
./tests

# Windows
.\tests.exe
```

Пример вывода:

```
Running 11 tests...

[PASS] min3(3,2,1) == 1
[PASS] min3(1,2,3) == 1
...
[PASS] maxOnAndBelow empty throws

=================== Test summary ===================
Total:  11
Passed: 11
Failed: 0
====================================================
```

---

## Управляющие графы программы (УГП)

В папке `diagrams/` находятся `.dot`-файлы для функций:

* `min3.dot`
* `sumEvenIndexSum.dot`
* `maxOnAndBelowMainDiagonal.dot`

Для генерации изображений:

```bash
dot -Tpng diagrams/min3.dot -o diagrams/min3.png
dot -Tpng diagrams/sumEvenIndexSum.dot -o diagrams/sumEvenIndexSum.png
dot -Tpng diagrams/maxOnAndBelowMainDiagonal.dot -o diagrams/maxOnAndBelowMainDiagonal.png
```

Файлы `.png` можно открыть любым просмотрщиком.

В папке `correct_diagrams/` находятся более понятные и удобные `.dot` файлы для тех же функций. Для генерации изображений:

```bash
dot -Tpng correct_diagrams/min3.dot -o correct_diagrams/min3.png
dot -Tpng correct_diagrams/sumEvenIndexSum.dot -o correct_diagrams/sumEvenIndexSum.png
dot -Tpng correct_diagrams/maxOnAndBelowMainDiagonal.dot -o correct_diagrams/maxOnAndBelowMainDiagonal.png
```

---

## Итог

* Библиотека `MyLib` реализует три функции:

  * `min3` — минимум из трёх чисел;
  * `sumEvenIndexSum` — сумма элементов массива, где сумма индексов чётная;
  * `maxOnAndBelowMainDiagonal` — максимум на и ниже главной диагонали.
* Тесты покрывают все ветви (критерий C1).
