/**
 *    @file geometric-shapes.cpp
 *    @brief Geometric shapes - example on composition
 *    @author rouxfederico@gmail.com
 */
#include <cstdint>
#include <fstream>      // IWYU pragma: keep
#include <iostream>
#include <ostream>      // IWYU pragma: keep
#include <sstream>      // IWYU pragma: keep
#include <vector>
#include <iterator>


// CRTP idiomatic design pattern
// curiously recursive template pattern
template <typename Self>
struct SomeNeurons {
  template <typename T>
  void connectTo(T& other) {
    for (auto& from : *static_cast<Self*>(this)) {
      for (auto& to : other) {
        from.out.push_back(&to);
        to.in.push_back(&from);
      }
    }
  }
};

struct Neuron: SomeNeurons<Neuron> {
  std::vector<Neuron*> in, out;
  uint32_t id;

  Neuron() {
    static uint32_t id{1};
    this->id = id++;
  }

  Neuron* begin() {return this;}
  Neuron* end() {return std::next(this);}

  friend std::ostream &operator<<(std::ostream &os, const Neuron& obj) {
    for (Neuron* n : obj.in) {
      os << n->id << "\t-->\t[" << obj.id << "]" << std::endl;
    }
    for (Neuron* n : obj.out) {
      os << "[" << obj.id << "]\t-->\t" << n->id << std::endl;
    }
    return os;
  }
};

// note: shouldn't inherit from std classes as they don't have virt destructors
struct NeuronLayer : std::vector<Neuron>,  SomeNeurons<NeuronLayer> {
  explicit NeuronLayer(int count) {
    while (count-- > 0) {
      emplace_back(Neuron{});
    }
  }

  friend std::ostream &operator<<(std::ostream& os, const NeuronLayer &obj) {
    for (auto& n : obj) {
      os << n;
    }
    return os;
  }
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */

static int printTitle() {
  std::cout << "=========================================" << std::endl;
  std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
  std::cout << "\e[1mSection 9:\e[0m Composition" << std::endl;
  std::cout << "\e[1mCH50: Neural Networks\e[0m" << std::endl;
  std::cout << "=========================================" << std::endl;
  return 0;
}

/**
 *   @fn main
 *   @brief Coding Excercise
 */

int main() {
  printTitle();
  Neuron n1, n2;
  n1.connectTo(n2);

  std::cout << "Neuron 1\n" << n1 << std::endl;
  std::cout << "Neuron 2\n" << n2 << std::endl;

  NeuronLayer l1{2}, l2{3};

  n1.connectTo(l1);
  l2.connectTo(n2);
  l1.connectTo(l2);

  std::cout << "Layer 1\n" << l1 << std::endl;
  std::cout << "Layer 2\n"<< l2 << std::endl;

  return 0;
}
