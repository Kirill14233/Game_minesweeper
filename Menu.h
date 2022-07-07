#ifndef GAMESAPER1__MENU_H_
#define GAMESAPER1__MENU_H_

#include <iostream>
class Menu {
 public:
  ///Конструктор
  Menu();
  ///Получение размера поля
  int32_t GetSize() const;
  ///Установление размера кансоли
  /// \param a ширина \param b длина
  void Size(int32_t a, int32_t b);
  ///Запуск меню
  void Meni();
 private:
  ///Размер поля
  int32_t sizi = 8;
};

#endif //GAMESAPER1__MENU_H_
