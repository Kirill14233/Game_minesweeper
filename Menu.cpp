#include "Menu.h"
#include "Field.h"
#include <chrono>
int32_t Menu::GetSize() const {
  return sizi;
}
void Menu::Size(int32_t a, int32_t b) {
  HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD crd = {static_cast<int16_t> (a), static_cast<int16_t> (b)};
  ///Установление размера консоли
  SMALL_RECT src = {0, 0, static_cast<int16_t> (crd.X - 1), static_cast<int16_t> (crd.Y - 1)};
  SetConsoleWindowInfo(out_handle, true, &src);
  SetConsoleScreenBufferSize(out_handle, crd);
}
void Menu::Meni() {
  ///Запуск наального экрана
  Field a;
  a.Color(14, 0);
  std::cout << "Settings";
  a.Color(14, 0);
  std::cout << std::endl << std::endl;
  a.Color(15, 0);
  std::cout << "P";
  a.Color(3, 0);
  std::cout << "l";
  a.Color(15, 0);
  std::cout << "a";
  a.Color(3, 0);
  std::cout << "y";
  for (int32_t i = 0; i < 8; ++i) {
    for (int32_t j = 0; j < 40; ++j) {
      std::cout << ' ';
    }
    std::cout << std::endl;
  }
  ///Получаем дискриптор
  HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
  ///возвращает информацию о входных сообщениях в консольном входном буфере
  INPUT_RECORD InputRecord;
  DWORD Events;
  COORD coord;
  ///Запрещаем выделение консоли
  DWORD prev_mode;
  GetConsoleMode(hin, &prev_mode);
  SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
  ///разрешаем обработку мыши
  SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
  bool fl = false;
  ///Цикл для считывания нажатий
  while (true) {
    ///Считывание мышки
    ReadConsoleInput(hin, &InputRecord, 1, &Events);
    ///Нажатие на левую кнопку
    if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
      coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
      coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
      ///Нажатие на кнопку "PLAY" и начало игры
      if (coord.Y == 2 && coord.X >= 0 && coord.X <= 4) {
        COORD cord;
        cord.X = 0;
        cord.Y = 0;
        ///Курсор на начало
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
        break;
        ///Нажтие на кнопку "SETTINGS" и переход к настройкам
      } else if (coord.Y == 0 && coord.X >= 0 && coord.X <= 8 && !fl) {
        ///Переход в настройки
        fl = true;
        ///Печать режимов
        if (sizi == 8) {
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Color(3, 0);
          std::cout << char(283) << "EASY" << char(282) << "    " << std::endl << "EXIT" << std::endl << "       ";
          a.Color(3, 0);
        } else if (sizi == 12) {
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Color(3, 0);
          std::cout << char(283) << "NORM" << char(282) << "    " << std::endl << "EXIT" << std::endl << "       ";
          a.Color(3, 0);
        } else {
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Color(3, 0);
          std::cout << char(283) << "HARD" << char(282) << "    " << std::endl << "EXIT" << std::endl << "       ";
          a.Color(3, 0);
        }
        ///Смена режима
      } else if (coord.Y == 0 && coord.X == 5 && fl) {
        ///Вывод режима после смены
        if (sizi == 8) {
          sizi = 12;
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Color(3, 0);
          std::cout << char(283) << "NORM" << char(282) << "    " << std::endl << "EXIT" << std::endl << "       ";
          a.Color(3, 0);
        } else if (sizi == 12) {
          sizi = 16;
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Color(3, 0);
          std::cout << char(283) << "HARD" << char(282) << "    " << std::endl << "EXIT" << std::endl << "       ";
          a.Color(3, 0);
        } else {
          sizi = 8;
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Color(3, 0);
          std::cout << char(283) << "EASY" << char(282) << "    " << std::endl << "EXIT" << std::endl << "       ";
          a.Color(3, 0);
        }
        ///Нажатие на кнопку "EXIT" и выход в меню
      } else if (coord.Y == 1 && coord.X >= 0 && coord.X <= 4 && fl) {
        ///Переход в меню
        fl = false;
        a.Color(0, 0);
        COORD cord;
        cord.X = 0;
        cord.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
        ///Вывод меню
        a.Color(14, 0);
        std::cout << "Settings";
        a.Color(14, 0);
        std::cout << std::endl << "      " << std::endl;
        a.Color(15, 0);
        std::cout << "P";
        a.Color(3, 0);
        std::cout << "l";
        a.Color(15, 0);
        std::cout << "a";
        a.Color(3, 0);
        std::cout << "y";
        a.Color(3, 0);
      }
    }
  }
}
Menu::Menu() {
  Size(45, 20);
}