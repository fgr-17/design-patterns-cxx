/**
 *    @file strategy-excercise.cpp
 *    @brief Strategy Coding Exercise
 *    @brief Consider the quadratic equation and its canonical solution:
 *    @brief The part `b^2-4*a*c` is called the discriminant. Suppose we want to provide an API with
 *    @brief two different strategies for calculating the discriminant:
 *    @brief 1. In `OrdinaryDiscriminantStrategy`, If the discriminant is negative, we return it
 *    @brief as-is. This is OK, since our main API returns std::complex  numbers anyway.
 *    @brief 2. In RealDiscriminantStrategy , if the discriminant is negative, the return value is
 *    @brief `NaN` (not a number). `NaN` propagates throughout the calculation, so the equation
 *    @brief solver gives two NaN values.
 *    @brief Please implement both of these strategies as well as the equation solver itself. With
 *    @brief regards to plus-minus in the formula, please return the + result as the first element
 *    @brief and - as the second.
 *    @author rouxfederico@gmail.com
 */

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
using namespace std;

struct DiscriminantStrategy {
    [[nodiscard]] virtual double calculateDiscriminant(double a, double b, double c) = 0;

    virtual ~DiscriminantStrategy() = default;
    DiscriminantStrategy() = default;
    DiscriminantStrategy(const DiscriminantStrategy& other) = default;
    DiscriminantStrategy& operator=(const DiscriminantStrategy& other) = default;
    DiscriminantStrategy(DiscriminantStrategy&& other) = default;
    DiscriminantStrategy& operator=(DiscriminantStrategy&& other) = default;
};

struct OrdinaryDiscriminantStrategy final : public DiscriminantStrategy {
    [[nodiscard]] double calculateDiscriminant(double a, double b, double c) override {
        return b * b - 4 * a * c;
    }
};

struct RealDiscriminantStrategy final : public DiscriminantStrategy {
    [[nodiscard]] double calculateDiscriminant(double a, double b, double c) override {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return std::numeric_limits<double>::quiet_NaN();
        } else {
            return discriminant;
        }
    }
};

class QuadraticEquationSolver {
    DiscriminantStrategy& strategy_;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

    static constexpr double factor = 2.0;

   public:
    QuadraticEquationSolver(DiscriminantStrategy& strategy) : strategy_(strategy) {}

    [[nodiscard]] std::tuple<std::complex<double>, std::complex<double>> solve(double a, double b,
                                                                               double c) {
        double discriminant = strategy_.calculateDiscriminant(a, b, c);
        auto root = std::sqrt(std::complex<double>(discriminant, 0.0));
        auto denominator = factor * a;
        return {(std::complex<double>(-b, 0.0) + root) / denominator,
                (std::complex<double>(-b, 0.0) - root) / denominator};
    }
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 22 :\e[0m Strategy" << std::endl;
    std::cout << "\e[1mStrategy Coding Exercise\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    static constexpr double a = 1;
    static constexpr double b = 10;
    static constexpr double c = 16;

    OrdinaryDiscriminantStrategy ordinaryDiscriminantStrategy;
    RealDiscriminantStrategy realDiscriminantStrategy;
    QuadraticEquationSolver ordinaryQuadraticEquationSolver{ordinaryDiscriminantStrategy};
    QuadraticEquationSolver realQuadraticEquationSolver{realDiscriminantStrategy};
    auto [x1, x2] = ordinaryQuadraticEquationSolver.solve(a, b, c);
    std::cout << "x1: " << x1 << ", x2: " << x2 << std::endl;
    auto [x1_real, x2_real] = realQuadraticEquationSolver.solve(a, b, c);
    std::cout << "x1_real: " << x1_real << ", x2_real: " << x2_real << std::endl;

    // Test case for negative discriminant with RealDiscriminantStrategy:
    // x^2 + 2x + 3 has discriminant = -8, so real parts should be NaN.
    auto [x1_nan, x2_nan] = realQuadraticEquationSolver.solve(1, 2, 3);
    if (!std::isnan(x1_nan.real()) || !std::isnan(x2_nan.real())) {
        std::cerr << "Test failed: expected NaN real parts for RealDiscriminantStrategy. "
                  << "x1=" << x1_nan << ", x2=" << x2_nan << std::endl;
        return 1;
    }
    std::cout << "Test passed: isnan(x1.real()) && isnan(x2.real())" << std::endl;

    return 0;
}
