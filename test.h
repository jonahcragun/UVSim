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

    void exception_test(const std::string& description, const std::function<void()>& testFunction, const std::string& expectedException, const std::string& fileName, long lineNumber) {
        try {
            testFunction();
            add_test(description + " (expected exception not thrown)", "Exception not thrown", false, fileName, lineNumber);
        } catch (const std::exception& e) {
            if (std::string(typeid(e).name()) == expectedException) {
                add_test(description + " (expected exception thrown)", "", true, fileName, lineNumber);
            } else {
                add_test(description + " (unexpected exception thrown)", "Unexpected exception: " + std::string(e.what()), false, fileName, lineNumber);
            }
        } catch (...) {
            add_test(description + " (non-standard exception thrown)", "Non-standard exception", false, fileName, lineNumber);
        }
    }

    void generate_report() const {
        if (verbose) {
            for (const auto& result : tests) {
                std::cout << (result.passed ? "PASS" : "FAIL") << ": " << result.testDescription << "\n"
                          << (result.passed ? "" : "\t" + result.failureMessage) << "\n"
                          << "\tin file " << result.fileName << " on line " << result.lineNumber << std::endl;
            }
        }
        std::cout << "\nTest Report:\n\n";
        std::cout << "\tPassed: " << passedTests << std::endl;
        std::cout << "\tFailed: " << failedTests << std::endl;
    }

private:
    std::vector<TestResult> tests;
    size_t passedTests{0};
    size_t failedTests{0};
    bool verbose{false};
};

// Test scafolding user calls TEST, TEST_WITH_FAILURE_MSG, EXCEPTION_TEST, and TEST_REPORT
// Create an instance of TestHandler
extern TestHandler testHandler;

// Macros for adding a test
#define TEST(description, condition) \
    testHandler.add_test(description, "", condition, __FILE__, __LINE__)

#define TEST_WITH_FAILURE_MSG(description, condition, failureMessage) \
    testHandler.add_test(description, failureMessage, condition, __FILE__, __LINE__)

// Macro for adding an exception test
#define EXCEPTION_TEST(description, testFunction, expectedException) \
    testHandler.exception_test(description, testFunction, typeid(expectedException).name(), __FILE__, __LINE__)

// Macro for generating a test report
#define TEST_REPORT testHandler.generate_report()

#endif