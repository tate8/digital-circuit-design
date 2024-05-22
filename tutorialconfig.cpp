#include "tutorialconfig.h"

// Tutorial 1 Configuration
TutorialConfig Tutorial1Config = {
    "<html><body><h2>Tutorial</h2></body></html>",
    "<html><body>"
    "<p>In this level, you will learn the basics of <b>AND</b> and <b>OR</b> gates.</p>"
    "<h3>Your task:</h3>"
    "<ul>"
    "<li>Connect the input gates to the AND and OR gates.</li>"
    "<li>Observe the output gates.</li>"
    "<li>Try different combinations of input values to see how the gates behave.</li>"
    "<li>Your goal is to understand how AND and OR gates work together to produce different outputs.</li>"
    "</ul>"
    "<h3>Expected Output Values:</h3>"
    "<table border='1'>"
    "<tr><th>Input 1</th><th>Input 2</th><th>Output</th></tr>"
    "<tr><td>false</td><td>false</td><td>false</td></tr>"
    "<tr><td>false</td><td>true</td><td>true</td></tr>"
    "<tr><td>true</td><td>false</td><td>true</td></tr>"
    "<tr><td>true</td><td>true</td><td>false</td></tr>"
    "</body></html>",
    2,
    { GateType::AndGateType, GateType::OrGateType },
    { false, false, false, false }
};

// Tutorial 2 Configuration
TutorialConfig Tutorial2Config = {
    "Tutorial Title",
    "Welcome to Tutorial 2! This level introduces the NOT gate.",
    1,
    { GateType::NotGateType },
    { true, false }
};

// Tutorial 3 Configuration
TutorialConfig Tutorial3Config = {
    "Tutorial Title",
    "Welcome to Tutorial 3! Combine AND, OR, and NOT gates to achieve the desired outputs.",
    2,
    { GateType::AndGateType, GateType::OrGateType, GateType::NotGateType },
    { true, true, true, false }
};

// Tutorial 4 Configuration
TutorialConfig Tutorial4Config = {
    "Tutorial Title",
    "Welcome to Tutorial 4! Explore the NAND gate.",
    2,
    { GateType::NandGateType },
    { true, true, true, false }
};

// Tutorial 5 Configuration
TutorialConfig Tutorial5Config = {
    "Tutorial Title",
    "Welcome to Tutorial 5! Discover the XOR gate.",
    2,
    { GateType::XorGateType },
    { false, true, true, false }
};

// Tutorial 6 Configuration
TutorialConfig Tutorial6Config = {
    "Tutorial Title",
    "Welcome to Tutorial 6! Mix multiple gate types.",
    3,
    { GateType::AndGateType, GateType::OrGateType, GateType::NotGateType, GateType::XorGateType },
    { false, true, true, false, true, false, false, true }
};
