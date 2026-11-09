#include <iostream>
#include "DifferentiationTask.h"
#include "ScopeLogger.h"

void functionC() {
    ScopeLogger logger("functionC");
    std::cout << "Starting calculations in functionC...\n";
    DifferentiationTask task;
    // Робимо навмисну помилку: крок менший за нуль
    task.calculate(2.0, -1.0);
}

void functionB() {
    ScopeLogger logger("functionB");
    try {
        functionC();
    }
    catch (const MathException& e) {
        std::cerr << "[LOG] functionB caught exception: " << e.what() << '\n';
        std::cerr << "[LOG] Rethrowing to higher level...\n";
        throw; // Повторне генерування винятку
    }
}

void functionA() {
    ScopeLogger logger("functionA");
    functionB();
}

int main() {
    std::cout << "=== Demo App Started ===\n";
    try {
        functionA();
    }
    catch (const InvalidStepException& e) {
        std::cerr << "[MAIN] Caught specific InvalidStepException: " << e.what()
            << ", step = " << e.getStep() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "[MAIN] Caught general exception: " << e.what() << '\n';
    }
    std::cout << "=== Demo App Finished Gracefully ===\n";
    return 0;
}