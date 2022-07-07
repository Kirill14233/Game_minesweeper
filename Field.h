#ifndef GAMESAPER1__FIELD_H_
#define GAMESAPER1__FIELD_H_
#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <conio.h>
#include <windows.h>
class Field {
 public:
  ///Открытие пустых клеток(рекурсивное)
  /// \param x столбец \param y строка
  void Open(int32_t x, int32_t y);
  ///Установление цвета фона и шрифта
  /// \param bg цвет фона \param text цвет шрифта
  void Color(int32_t text, int32_t bg);
  ///Установление размера шрифта
  /// \param a размер
  void Shrift(int32_t a);
  ///Установка/снятие флага
  /// \param x столбец \param y строка
  void Flag(int32_t x, int32_t y);
  ///Копирование массива a_ в s_
  void Copy();
  ///Конструктор
  Field();
  ///Вывод поля
  void Print();
  ///Изменение поля после нажатия
  /// \param x столбец \param y строка
  void Chake(int32_t x, int32_t y);
  ///Вид нажатой клетки
  /// \param x столбец \param y строка
  int32_t Chake2(int32_t x, int32_t y);
  ///Регенерация поля
  /// \param sizi размер
  void Reset(int32_t sizi);
 private:
  ///Изменяющиеся поле
  std::vector<std::vector<std::pair<int32_t, bool>>> a_;
  ///Неизменяющиеся поле
  std::vector<std::vector<std::pair<int32_t, bool>>> s_;
};
#endif //GAMESAPER1__FIELD_H_
