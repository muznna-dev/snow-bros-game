#include "EnemyFactory.h"
#include "Botom.h"
#include "FlyngFoogaFooga.h"
#include "Tornado.h"
#include "Mogera.h"
#include "Gamakichi.h"

Enemy* EnemyFactory::create(const std::string& type, float x, float y, float speed) {

    if (type == "Botom")          return new Botom(x, y, speed);
    if (type == "FlyngFoogaFoog") return new FlyngFoogaFoog(x, y, speed);
    if (type == "Tornado")        return new Tornado(x, y, speed);
    if (type == "Mogera")         return new Mogera(x, y, speed);
    if (type == "Gamakichi")      return new Gamakichi(x, y, speed);
    return nullptr;
}