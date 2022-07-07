#include <iostream>
#include <windows.h>
#include "Field.h"
#include "Menu.h"
int32_t main() {
  ///запуск программы и меню
  Menu b;
  b.Meni();
  ///Запуск игрового поля
  Field a;
  a.Reset(b.GetSize());
  a.Copy();
  COORD cord;
  cord.X = 0;
  cord.Y = 0;
  ///Ставим курсор на начало
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
  a.Print();
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
  bool cnt = true;
  ///Цикл для выхода в меню и смены режима
  while (true) {
    ///Цикл для управления игрой
    while (true) {
      ///Считывание мыши и курсора
      ReadConsoleInput(hin, &InputRecord, 1, &Events);
      ///Проверка на нажатие левой кнопки
      if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        _sleep(500);
        ///Получаем координаты курсора
        coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
        coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
        int32_t x = coord.X;
        int32_t y = coord.Y;
        ///Проверяем на невыход за границы
        if (y >= b.GetSize() || x >= b.GetSize() * 2) {
          continue;
        }
        ///Проверка на выигрыш
        if (a.Chake2(x, y) == 4) {
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          ///Курсор на начало
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Print();
          cord.X = 0;
          cord.Y = 0;
          ///Курсор на начало
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          ///Вывод строки выигрыша
          a.Color(4, 0);
          for (int32_t i = 0; i < 8; ++i) {
            for (int32_t i = 0; i < 40; ++i) {
              std::cout << ' ';
            }
            std::cout << std::endl;
          }
          std::cout << "          You are the GOD of this game!        ";
          for (int32_t i = 0; i < 10; ++i) {
            std::cout << std::endl;
            for (int32_t i = 0; i < 40; ++i) {
              std::cout << ' ';
            }
          }
          _sleep(2000);
          cord.X = 0;
          cord.Y = 0;
          ///Курсор на начало
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          break;
        }
        ///Проверка на повтор
        if (a.Chake2(x, y) == 3) {
          continue;
          ///Проверка на бомбу
        } else if (a.Chake2(x, y) == 2) {
          ///Проверка на нажатие  на бомбу первым ходом и последующую регенерацию массива
          while (cnt) {
            a.Reset(b.GetSize());
            a.Copy();
            if (a.Chake2(x, y) != 2) {
              cnt = false;
              COORD cord;
              cord.X = 0;
              cord.Y = 0;
              ///Курсор на начало
              SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
              a.Chake(x, y);
              a.Print();
            }
          }
          ///Проверка на нажатие  на бомбу первым ходом
          if (a.Chake2(x, y) != 2) {
            continue;
          }
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          ///Курсор на начало
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Chake(x, y);
          a.Print();
          _sleep(5000);
          cord.X = 0;
          cord.Y = 0;
          ///Курсор на начало
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          ///Вывод строки проигрыша
          a.Color(4, 0);
          for (int32_t i = 0; i < 8; ++i) {
            for (int32_t i = 0; i < 40; ++i) {
              std::cout << ' ';
            }
            std::cout << std::endl;
          }
          std::cout << "                 GAME OVER                 ";
          for (int32_t i = 0; i < 10; ++i) {
            std::cout << std::endl;
            for (int32_t i = 0; i < 40; ++i) {
              std::cout << ' ';
            }
          }
          _sleep(2000);
          cord.X = 0;
          cord.Y = 0;
          ///Курсор на начало
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          ///Выход в меню
          break;
        } else {
          ///Больше одного хода
          cnt = false;
          COORD cord;
          cord.X = 0;
          cord.Y = 0;
          ///Курсор на начало
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
          a.Chake(x, y);
          a.Print();
        }
        ///Нажатие правой кнопки
      } else if (InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) // правая кнопка
      {
        coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
        coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
        ///Проверяем на невыход за границы
        if (coord.Y >= b.GetSize() || coord.X >= b.GetSize() * 2) {
          continue;
        }
        a.Flag(coord.X, coord.Y);
        COORD cord;
        cord.X = 0;
        cord.Y = 0;
        ///Курсор на начало
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
        a.Print();
      }
    }
    ///Выход в меню
    b.Meni();
    a.Reset(b.GetSize());
    a.Copy();
    COORD cord;
    cord.X = 0;
    cord.Y = 0;
    ///Курсор на начало
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
    a.Print();
    ///Обнуление ходов
    cnt = true;
  }

}
