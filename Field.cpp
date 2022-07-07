#include "Field.h"
#include <chrono>
void Field::Copy() {
  s_.clear();
  ///Копирование
  for (const auto &it : a_) {
    s_.emplace_back(it);
  }
}
void Field::Flag(int32_t x, int32_t y) {
  ///Проверка на наличие флага на клетке
  if (!a_[y][x].second) {
    a_[y][x] = std::make_pair(-2, true);
  } else if (a_[y][x].first == -2) {
    a_[y][x] = s_[y][x];
  }
}
void Field::Open(int32_t i, int32_t j) {
  int32_t sizi = a_.size();
  ///Открытие клетки
  a_[i][j] = std::make_pair(0, true);
  ///Проверка на открытие остальных клеток
  if (i - 1 >= 0) {
    if (a_[i - 1][j].first == 0 && !a_[i - 1][j].second) {
      Open(i - 1, j);
    } else if (a_[i - 1][j].first > 0 && !a_[i - 1][j].
        second) {
      int32_t s = a_[i - 1][j].first;
      a_[i - 1][j] = std::make_pair(s, true);
    }
  }
  if (i + 1 < sizi) {
    if (a_[i + 1][j].first == 0 && !a_[i + 1][j].second) {
      Open(i + 1, j);
    } else if (a_[i + 1][j].first > 0 && !a_[i + 1][j].second) {
      int32_t s = a_[i + 1][j].first;
      a_[i + 1][j] = std::make_pair(s, true);
    }
  }
  if (j - 1 >= 0 && a_[i][j - 1].first == 0 && !a_[i][j - 1].second) {
    Open(i, j - 1);
  } else if (j - 1 >= 0 && a_[i][j - 1].first > 0 && !a_[i][j - 1].second) {
    int32_t s = a_[i][j - 1].first;
    a_[i][j - 1] = std::make_pair(s, true);
  }
  if (j + 1 < sizi * 2 && a_[i][j + 1].first == 0 && !a_[i][j + 1].second) {
    Open(i, j + 1);
  } else if (j + 1 < sizi * 2 && a_[i][j + 1].first > 0 && !a_[i][j + 1].second) {
    int32_t s = a_[i][j + 1].first;
    a_[i][j + 1] = std::make_pair(s, true);
  }
}
void Field::Color(int32_t text, int32_t bg) {
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  ///Установка цвета фона и шрифта
  SetConsoleTextAttribute(hStdOut, (WORD) ((bg << 4) | text));
}
void Field::Shrift(int32_t a) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_FONT_INFOEX fontInfo;
  fontInfo.cbSize = sizeof(fontInfo);
  ///Получение текущего размера консоли в переменную hConsole
  GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
  ///Установка шрифта
  wcscpy(fontInfo.FaceName, L"Lucida Console");
  ///Изменение размера шрифта
  fontInfo.dwFontSize.Y = static_cast<int16_t> (a);
  ///Установка нового шрифта
  SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
}
Field::Field() {
  Shrift(30);
}
void Field::Print() {
  bool a = true;
  for (const auto &it : a_) {
    a = !(a);
    for (const auto it1 : it) {
      if (it1.second) {
        if (it1.first == -1) {
          Color(4, 8);
          std::cout << char(15);
        } else if (it1.first == 0) {
          Color(0, 8);
          std::cout << ' ';
        } else if (it1.first == 8) {
          Color(14, 8);
          std::cout << it1.first;
        } else if (it1.first == -2) {
          if (a) {
            Color(4, 3);
            std::cout << char(5);
          } else {
            Color(4, 7);
            std::cout << char(5);
          }
        } else if (it1.first == -3) {
          Color(4, 10);
          std::cout << char(15);
        } else {
          Color(it1.first, 8);
          std::cout << it1.first;
        }
        a = !(a);
      } else if (a) {
        Color(3, 0);
        a = !(a);
        std::cout << char(219);
      } else {
        Color(7, 0);
        a = !(a);
        std::cout << char(219);
      }
    }
    Color(7, 0);
    std::cout << std::endl;
  }
}
void Field::Chake(int32_t x, int32_t y) {
  ///Проверка на повторное нажатие
  if (a_[y][x].second) {
    return;
  } else {
    ///Нажатие на бомбу
    if (a_[y][x].first == -1) {
      for (int32_t i = 0; i < a_.size(); ++i) {
        for (int32_t j = 0; j < (a_[i]).size(); ++j) {
          if (s_[i][j].first == -1 && a_[i][j].first == -2) {
            a_[i][j] = std::make_pair(-3, true);
          } else {
            a_[i][j] = std::make_pair(a_[i][j].first, true);
          }
        }
      }
    } else {
      int32_t s = (a_[y][x]).first;
      if (s == 0) {
        Open(y, x);
      } else {
        a_[y][x] = std::make_pair(s, true);
      }
    }
  }
}
int32_t Field::Chake2(int32_t x, int32_t y) {
  ///Проверка на выигрыш
  bool fl = true;
  for (int32_t i = 0; i < a_.size(); ++i) {
    for (int32_t j = 0; j < a_[i].size(); ++j) {
      if (a_[i][j].first == -2 && s_[i][j].first != -1 || !a_[i][j].second) {
        fl = false;
      }
    }
  }
  if (fl) {
    for (int32_t i = 0; i < a_.size(); ++i) {
      for (int32_t j = 0; j < a_[i].size(); ++j) {
        if (a_[i][j].first == -2 && s_[i][j].first == -1) {
          a_[i][j] = std::make_pair(-3, true);
        } else {
          a_[i][j] = std::make_pair(s_[i][j].first, true);
        }
      }
    }
    return 4;
  }
  ///Если кнопка уже нажата
  if (a_[y][x].second) {
    return 3;
    ///Если бомба
  } else {
    if (a_[y][x].first == -1) {
      return 2;
    } else {
      return 1;
    }
  }
}
void Field::Reset(int32_t sizi) {
  Color(4, 0);
  a_.clear();
  for (int32_t i = 0; i < sizi; ++i) {
    std::vector<std::pair<int32_t, bool>> a(sizi * 2, std::make_pair(0, false));
    a_.emplace_back(a);
  }
  int32_t h = (sizi * sizi) * 4 / 12;
  ///Генерация бомб
  for (int32_t i = 0; i < h; ++i) {
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    int32_t x = gen() % (sizi);
    int32_t y = gen() % (sizi * 2);
    while (a_[x][y].first == -1) {
      x = gen() % (sizi);
      y = gen() % (sizi * 2);
    }
    a_[x][y] = std::make_pair(-1, false);
  }
  ///Установка цифр
  for (int32_t i = 0; i < sizi; ++i) {
    for (int32_t j = 0; j < sizi * 2; ++j) {
      int32_t cnt = 0;
      if (a_[i][j].first != -1) {
        if (i - 1 >= 0) {
          if (j - 1 >= 0 && a_[i - 1][j - 1].first == -1) {
            cnt++;
          }
          if (j + 1 < sizi * 2 && a_[i - 1][j + 1].first == -1) {
            cnt++;
          }
          if (a_[i - 1][j].first == -1) {
            cnt++;
          }
        }
        if (i + 1 < sizi) {
          if (j + 1 < sizi * 2 && a_[i + 1][j + 1].first == -1) {
            cnt++;
          }
          if (j - 1 >= 0 && a_[i + 1][j - 1].first == -1) {
            cnt++;
          }
          if (a_[i + 1][j].first == -1) {
            cnt++;
          }
        }
        if (j - 1 >= 0 && a_[i][j - 1].first == -1) {
          cnt++;
        }
        if (j + 1 < sizi * 2 && a_[i][j + 1].first == -1) {
          cnt++;
        }
        a_[i][j] = std::make_pair(cnt, false);
      }
    }
  }
}
