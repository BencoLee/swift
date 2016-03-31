/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <string>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <Swiften/Base/Log.h>

int main(int argc, char* argv[]) {
    bool verbose = false;
    bool outputXML = false;

    Swift::Log::setLogLevel(Swift::Log::error);

    // Parse parameters
    std::vector<std::string> testsToRun;
    for (int i = 1; i < argc; ++i) {
        std::string param(argv[i]);
        if (param == "--verbose") {
            verbose = true;
        }
        else if (param == "--xml") {
            outputXML = true;
        }
        else if (param == "--debug") {
            Swift::Log::setLogLevel(Swift::Log::debug);
        }
        else {
            testsToRun.push_back(param);
        }
    }
    if (testsToRun.empty()) {
        testsToRun.push_back("");
    }

    // Set up the listeners
    CppUnit::TestResult controller;

    CppUnit::TestResultCollector result;
    controller.addListener(&result);

    CppUnit::TextTestProgressListener progressListener;
    CppUnit::BriefTestProgressListener verboseListener;
    if (!outputXML) {
        if (verbose) {
            controller.addListener(&verboseListener);
        }
        else {
            controller.addListener(&progressListener);
        }
    }

    // Run the tests
    CppUnit::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    for (std::vector<std::string>::const_iterator i = testsToRun.begin(); i != testsToRun.end(); ++i) {
        try {
            runner.run(controller, *i);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }

    // Output the results
    if (outputXML) {
        CppUnit::XmlOutputter outputter(&result, std::cout);
        outputter.write();
    }
    else {
        CppUnit::TextOutputter outputter(&result, std::cerr);
        outputter.write();
    }

    return result.wasSuccessful() ? 0 : 1;
}
