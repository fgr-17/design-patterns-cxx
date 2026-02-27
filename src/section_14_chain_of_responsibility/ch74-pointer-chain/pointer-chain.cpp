/**
 *    @file pointer-chain.cpp
 *    @brief ch-74 Pointer Chain
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <string>
#include <utility>

struct Creature {
   private:
    std::string name_;
    int attack_;
    int defense_;

   public:
    Creature(std::string name, int attack, int defense)
        : name_(std::move(name)), attack_(attack), defense_(defense) {}

    [[nodiscard]] int getAttack() const {
        return attack_;
    }

    void setAttack(int attack) {
        this->attack_ = attack;
    }

    [[nodiscard]] int getDefense() const {
        return defense_;
    }

    void setDefense(int defense) {
        this->defense_ = defense;
    }

    [[nodiscard]] std::string getName() const {
        return name_;
    }

    void setName(const std::string& name) {
        this->name_ = name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Creature& creature) {
        os << "Creature(name: " << creature.getName() << ", attack: " << creature.getAttack()
           << ", defense: " << creature.getDefense() << ")";
        return os;
    }
};

class CreatureModifier {
    Creature& creature_;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    CreatureModifier* next_{nullptr};

   public:
    CreatureModifier(Creature& creature) : creature_(creature) {}
    virtual ~CreatureModifier() = default;

    CreatureModifier(const CreatureModifier&) = delete;
    CreatureModifier(CreatureModifier&&) = delete;
    CreatureModifier& operator=(const CreatureModifier&) = delete;
    CreatureModifier& operator=(CreatureModifier&&) = delete;

    void add(CreatureModifier* modifier) {
        if (next_) {
            next_->add(modifier);
        } else {
            next_ = modifier;
        }
    }

    virtual void handle() {
        if (next_) next_->handle();
    }

    [[nodiscard]] Creature& getCreature() const {
        return creature_;
    }
};

class DoubleAttackModifier final : public CreatureModifier {
   public:
    DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        getCreature().setAttack(getCreature().getAttack() * multiplier);
        CreatureModifier::handle();  // pass the request to the next modifier
    }

    static constexpr int multiplier = 2;
};

class IncreasedDefenseModifier final : public CreatureModifier {
   public:
    IncreasedDefenseModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        if (getCreature().getDefense() < maxDefense) {
            getCreature().setDefense(getCreature().getDefense() + 1);
        }
        CreatureModifier::handle();  // pass the request to the next modifier
    }
    static constexpr int maxDefense = 2;
};

class NoBonusesModifier final : public CreatureModifier {
   public:
    NoBonusesModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        // do nothing
    }
};
/**
 *   @fn printTitle
 *   @brief chapter title
 */
static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 14 :\e[0m Chain of Responsibility" << std::endl;
    std::cout << "\e[1mChapter 74 : Pointer Chain\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Pointer Chain
 */
int main() {
    printTitle();
    Creature goblin{"Goblin", 1, 1};

    // start of chain
    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r2{goblin};
    IncreasedDefenseModifier r3{goblin};
    NoBonusesModifier curse{goblin};
    IncreasedDefenseModifier r4{goblin};

    std::cout << "Before modifiers: " << goblin << std::endl;
    root.add(&curse);
    root.add(&r1);
    root.add(&r2);
    root.add(&r3);
    root.handle();
    root.add(&r4);
    root.handle();
    std::cout << "After r4(increase defense and curse): " << goblin << std::endl;

    return 0;
}
