#ifndef TEST_H
#define TEST_H

void case_one();
void case_two();
void case_three();
void case_four();
void case_five();
void case_six();
void case_seven();
void case_eight();
void case_nine();
void case_ten();
void case_eleven();
void case_twelve();
void case_thirteen();
void case_fourteen();
void case_fifteen();
void case_sixteen();
void case_seventeen();
void case_eighteen();
void case_nineteen();
void case_twenty();
void case_twentyone();
void case_twentytwo();
void case_twentythree();
void case_twentyfour();

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <typeinfo>
#include <stdexcept>

using std::size_t;

// Struct to hold test result information
struct TestResult {
    std::string testDescription;
    std::string failureMessage;
    bool passed;
    std::string fileName;
    long lineNumber;
};

// Class to handle unit testing
class TestHandler {
public:
    static TestHandler& get_instance() {
        static TestHandler instance;
        return instance;
    }

    void set_verbose(bool verbose) {
        this->verbose = verbose;
    }

    void add_test(const std::string& description, const std::string& failureMessage, bool condition, const std::string& fileName, long lineNumber) {
        tests.push_back({description, failureMessage, condition, fileName, lineNumber});
        if (condition) {
            ++passedTests;
        } else {
            ++failedTests;
        }
    }

    template<typename Func, typename... Args>
    void function_test(const std::string& description, Func testFunction, const std::string& fileName, long lineNumber, Args&&... args) {
        try {
            std::invoke(testFunction, std::forward<Args>(args)...);
            add_test(description, "", true, fileName, lineNumber);
        } catch (const std::exception& e) {
            add_test(description, "Exception thrown: " + std::string(e.what()), false, fileName, lineNumber);
        } catch (...) {
            add_test(description, "Non-standard exception", false, fileName, lineNumber);
        }
    }

    template<typename ExceptionType, typename Func, typename... Args>
    void exception_test_func(const std::string& description, Func testFunction, const std::string& fileName, long lineNumber, Args&&... args) {
        try {
            std::invoke(testFunction, std::forward<Args>(args)...);
            TestHandler::get_instance().add_test(description, "Exception not thrown. ", false, fileName, lineNumber);
        } catch (const ExceptionType&) {
            TestHandler::get_instance().add_test(description, "", true, fileName, lineNumber);
        } catch (const std::exception& e) {
            TestHandler::get_instance().add_test(description, "Unexpected exception: " + std::string(e.what()), false, fileName, lineNumber);
        } catch (...) {
            TestHandler::get_instance().add_test(description, "Non-standard exception", false, fileName, lineNumber);
        }
    }

    template<typename ExceptionType>
    void exception_test_conditional(const std::string& description, bool condition, const std::string& throwMessage, const std::string& fileName, long lineNumber) {
        auto testFunction = [condition, throwMessage]() {
            if (!condition)
                throw ExceptionType(throwMessage);
        };
        exception_test_func<ExceptionType>(description, testFunction, fileName, lineNumber);
    }

    void generate_report(int num) const {
        std::cout << "\nUnit test " << (num > 0 ? std::to_string(num) + " " : "") << "Report:\n";
        std::cout << "\tPassed: " << passedTests << std::endl;
        std::cout << "\tFailed: " << failedTests << std::endl << std::endl;
        if (verbose) {
            for (const auto& result : tests) {
                std::cout << (result.passed ? "PASSED: " : "FAILED: ") << "Test in file " << result.fileName << " on line " << result.lineNumber
                          << " {\n\t\tDESCRIPTION: '" << result.testDescription << (result.passed ? "'" : "'\n\t\tERROR MESSAGE: " + result.failureMessage)
                          << "\n\t}\n" << std::endl << std::endl;
            }
        } else {
            for (const auto& result : tests) {
                if (!result.passed) {
                    std::cout << "FAILED: Test in file " << result.fileName << " on line " << result.lineNumber << " {" << "\n\t\tDESCRIPTION: '" << result.testDescription
                              << "'\n\t\tERROR MESSAGE: " << result.failureMessage << "\n\t}\n" << std::endl << std::endl;
                }
            }
        }
    }

    void clear_results() {
        tests.clear();
        passedTests = 0;
        failedTests = 0;
    }

private:
    TestHandler() = default;
    std::vector<TestResult> tests;
    size_t passedTests{0};
    size_t failedTests{0};
    bool verbose{false};
};

// MACRO Structure:
// TEST : param 1: Description of the test, param 2: Condition to test, param 3: Failure message
// FUNCTION_TEST : param 1: Description of the test, param 2: Function to test
// EXCEPTION_TEST_FUNC : param 1: Description of the test, param 2: Function to test, param 3: Expected exception
// EXCEPTION_TEST_COND : param 1: Description of the test, param 2: Condition to test, param 3: Expected exception
// TEST_REPORT : takes an optional integer parameter, Generates a test report for all tests run and not cleared
// CLEAR_RESULTS : takes no parameters, Clears all test results

// Macros for adding a test, uses variadic macros (... and __VA_ARGS__) to allow for a custom failure message (Defaults to an empty string if no message is provided)
#define TEST(description, condition, ...) \
    TestHandler::get_instance().add_test(description, "" __VA_ARGS__, condition, __FILE__, __LINE__)

// Macros for adding a function test
#define TEST_FUNCTION(description, testFunction, ...) \
    TestHandler::get_instance().function_test(description, [&]() { testFunction; }, __FILE__, __LINE__, ##__VA_ARGS__) // ##__VA_ARGS__ is used to allow for an empty variadic macro

// Macro for adding an exception test for functions
#define EXCEPTION_TEST_FUNC(description, testFunction, expectedException, ...) \
    TestHandler::get_instance().exception_test_func<expectedException>(description, [&]() { testFunction; }, __FILE__, __LINE__, ##__VA_ARGS__) // ##__VA_ARGS__ is used to allow for an empty variadic macro

// Macro for adding an exception test for conditions
#define EXCEPTION_TEST_COND(description, condition, expectedException, ...) \
    TestHandler::get_instance().exception_test_conditional<expectedException>(description, condition, "" __VA_ARGS__, __FILE__, __LINE__)

// Macro for generating a test report
#define TEST_REPORT(...) TestHandler::get_instance().generate_report(__VA_ARGS__)

#define CLEAR_RESULTS() TestHandler::get_instance().clear_results()

#endif // TEST_H