#pragma once
#include "Enemy.h"
#include <string>
class EnemyFactory {
public:
    static Enemy* create(const std::string& type, float x, float y, float speed);
};
