/**
 *    @file main.cpp
 *    @brief ch-126 Multimethods
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <map>
#include <typeindex>

struct GameObject;

void collide(GameObject &first, GameObject &second);

struct GameObject {
    virtual ~GameObject() = default;

    GameObject() = default;
    GameObject(const GameObject &) = default;
    GameObject(GameObject &&) = default;
    GameObject &operator=(const GameObject &) = default;
    GameObject &operator=(GameObject &&) = default;

    [[nodiscard]] virtual std::type_index type() const = 0;

    virtual void collide(GameObject &other) {
        ::collide(*this, other);
    }
};

template <typename T>
struct GameObjectImpl : GameObject {
    [[nodiscard]] std::type_index type() const override {
        return typeid(T);
    }
};

// CRTP
struct Planet : GameObjectImpl<Planet> {};

struct Asteroid : GameObjectImpl<Asteroid> {};

struct Spaceship : GameObjectImpl<Spaceship> {};

void spaceshipPlanet() {
    std::cout << "Spaceship lands on a Planet" << std::endl;
}
void asteroidPlanet() {
    std::cout << "Asteroid hits a Planet" << std::endl;
}
void spaceshipAsteroid() {
    std::cout << "Asteroid destroys a Spaceship" << std::endl;
}

const std::map<std::pair<std::type_index, std::type_index>, void (*)(void)> outcomes{
    {{typeid(Spaceship), typeid(Planet)}, spaceshipPlanet},
    {{typeid(Asteroid), typeid(Planet)}, asteroidPlanet},
    {{typeid(Spaceship), typeid(Asteroid)}, spaceshipAsteroid},
};

void collide(GameObject &first, GameObject &second) {
    auto it = outcomes.find({first.type(), second.type()});
    if (it != outcomes.end()) {
        it->second();
    } else {
        it = outcomes.find({second.type(), first.type()});
        if (it != outcomes.end()) {
            it->second();
        } else {
            std::cout << "No collision outcome found for " << first.type().name() << " and "
                      << second.type().name() << std::endl;
        }
    }
}

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 24 :\e[0m Visitor" << std::endl;
    std::cout << "\e[1mChapter 126 : Multimethods\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    Asteroid asteroid;
    Planet planet;
    Spaceship spaceship;
    collide(asteroid, planet);
    collide(spaceship, asteroid);
    collide(planet, spaceship);
    collide(planet, planet);

    return 0;
}
