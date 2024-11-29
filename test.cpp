#include "pch.h"
#include "CppUnitTest.h"

#include "calculate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests {
    TEST_CLASS(CalculateTests)
    {
    public:
        TEST_METHOD(Test_X_NonPositive) {
            double x = -1.0;
            int n = 4;
            double expected = -1.0;
            for (int i = 0; i < n; i++) {
                expected *= (i * i - x);
            }

            double result = calculate(x, n);
            Assert::AreEqual(expected, result, 0.001, L"Error: x <= 0 case failed");
        }

        TEST_METHOD(Test_X_Positive) {
            double x = 1.0;
            int n = 3;
            double expected = 0.0;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    expected += x / (i + j);
                }
            }

            double result = calculate(x, n);
            Assert::AreEqual(expected, result, 0.001, L"Error: x > 0 case failed");
        }

        TEST_METHOD(Test_Large_N) {
            double x = 2.0;
            int n = 5;
            double expected = 0.0;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    expected += x / (i + j);
                }
            }

            double result = calculate(x, n);
            Assert::AreEqual(expected, result, 0.001, L"Error: Large n case failed");
        }

        TEST_METHOD(Test_Boundary_X_Zero) {
            double x = 0.0;
            int n = 4;
            double expected = 0.0;

            double result = calculate(x, n);
            Assert::AreEqual(expected, result, 0.001, L"Error: x = 0 boundary case failed");
        }
    };
}
