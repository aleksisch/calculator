# Дифференциатор математических выражений

## Build
```
mkdir build
cd ./build
cmake ..
make
./calculator path_to_file.txt
```

## Алгоритм
Парсинг грамматики реализован на алгоритме рекурсивного списка, которвые строит AST, после чего к нему применяются преобразования, простые оптимизации и вычисление производной. Результат работы лежит в файле `result.pdf`.
 
## Возможные улучшения
Для разбора грамматики лучше использовать уже готовые решения, например `bison` и `flex`. Обходить дерево можно используя паттерн `visitor`.