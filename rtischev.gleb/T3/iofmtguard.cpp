#include "iofmtguard.hpp"

// Реализация конструктора: запоминаем поток и копируем его текущие настройки
iofmtguard::iofmtguard(std::ios& s) :
stream_(s),
flags_(s.flags()),
precision_(s.precision()),
fill_(s.fill())
{}

// Реализация деструктора: при уничтожении объекта возвращаем потоку старые настройки
iofmtguard::~iofmtguard() {
    stream_.flags(flags_);
    stream_.precision(precision_);
    stream_.fill(fill_);
}
