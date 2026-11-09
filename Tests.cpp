#include <gtest/gtest.h>
#include "DifferentiationTask.h"
#include <cmath>

// Тест успішного розрахунку (EXPECT_NEAR)
TEST(DifferentiationTest, SuccessfulCalculation) {
    DifferentiationTask task;
    task.calculate(2.0, 1e-5);

    ASSERT_TRUE(task.hasResult());
    EXPECT_DOUBLE_EQ(task.getSavedX(), 2.0);

    // Похідна від ln(x) в точці 2.0 дорівнює 1/2.0 = 0.5
    DifferentiationResult res = task.getResult();
    EXPECT_NEAR(res.centralDerivative, 0.5, 1e-4);
}

// Робимо тест винятку: неправильний крок (EXPECT_THROW)
TEST(DifferentiationTest, ThrowsOnNegativeStep) {
    DifferentiationTask task;
    EXPECT_THROW(task.calculate(2.0, -0.1), InvalidStepException);
}

// Потім тест винятку: неправильна точка для ln(x)
TEST(DifferentiationTest, ThrowsOnInvalidDomain) {
    DifferentiationTask task;
    EXPECT_THROW(task.calculate(-2.0, 0.1), std::domain_error);
}

// І тест сильної гарантії безпеки (Strong Guarantee)
TEST(DifferentiationTest, StrongGuaranteeOnException) {
    DifferentiationTask task;
    // Спочатку робимо успішний розрахунок
    task.calculate(2.0, 0.1);
    ASSERT_TRUE(task.hasResult());

    double oldX = task.getSavedX();
    double oldH = task.getSavedH();

    // Намагаємося зробити помилковий розрахунок
    EXPECT_THROW(task.calculate(-1.0, 0.1), std::domain_error);

    // Перевіряємо, що старі значення залишилися незмінними!
    EXPECT_DOUBLE_EQ(task.getSavedX(), oldX);
    EXPECT_DOUBLE_EQ(task.getSavedH(), oldH);
}