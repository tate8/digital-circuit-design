#include "tutorialconfig.h"

// Tutorial 1 Configuration
TutorialConfig Tutorial1Config = {
    "<html><body><h2>Tutorial</h2></body></html>",
    "<html><body>"
    "<p>In this introductory level, you will learn the basics of the <b>AND</b> gate.</p>"
    "<h3>Your Task:</h3>"
    "<ul>"
    "<li>Connect the input gates to the AND gate.</li>"
    "<li>Observe the output gate's behavior.</li>"
    "<li>Try different combinations of input values to see how the AND gate responds.</li>"
    "<li>Your goal is to understand the basic operation of the AND gate.</li>"
    "</ul>"
    "<h3>Expected Output Values:</h3>"
    "<table border='1'>"
    "<tr><th>Input 1</th><th>Input 2</th><th>AND Gate Output</th></tr>"
    "<tr><td>false</td><td>false</td><td>false</td></tr>"
    "<tr><td>false</td><td>true</td><td>false</td></tr>"
    "<tr><td>true</td><td>false</td><td>false</td></tr>"
    "<tr><td>true</td><td>true</td><td>true</td></tr>"
    "</table>"
    "<p>For this level, you only need to create a simple connection as shown in the table above. "
    "Use the AND gate to achieve the specified outputs.</p>"
    "</body></html>",
    2, // Number of inputs
    { GateType::AndGateType }, // Allowed gate
    { false, false, false, true } // Expected results for AND gate
};

// Tutorial 2 Configuration
TutorialConfig Tutorial2Config = {
    "<html><body><h2>Tutorial</h2></body></html>",
    "<html><body>"
    "<p>In this level, you will learn about the <b>NOT</b> and <b>OR</b> gates.</p>"
    "<h3>Your Task:</h3>"
    "<ul>"
    "<li>Connect the two input gates to two NOT gates.</li>"
    "<li>Then connect the outputs of the NOT gates to an OR gate.</li>"
    "<li>Observe the final output of the OR gate.</li>"
    "<li>Your goal is to understand how NOT gates invert the inputs and how the OR gate combines these inverted inputs.</li>"
    "</ul>"
    "<h3>Expected Output Values:</h3>"
    "<table border='1'>"
    "<tr><th>Input 1</th><th>Input 2</th><th>Output</th></tr>"
    "<tr><td>false</td><td>false</td><td>true</td></tr>"
    "<tr><td>false</td><td>true</td><td>true</td></tr>"
    "<tr><td>true</td><td>false</td><td>true</td></tr>"
    "<tr><td>true</td><td>true</td><td>false</td></tr>"
    "</table>"
    "</body></html>",
    2, // Number of inputs
    { GateType::NotGateType, GateType::OrGateType }, // Allowed gates
    { true, true, true, false } // Expected results
};

// Tutorial 3 Configuration
TutorialConfig Tutorial3Config = {
    "<html><body><h2>Tutorial</h2></body></html>",
    "<html><body>"
    "<p>In this level, you will combine <b>AND</b>, <b>OR</b>, and <b>NOT</b> gates to achieve the desired output.</p>"
    "<h3>Your Task:</h3>"
    "<ul>"
    "<li>Connect the input gates through a combination of AND, OR, and NOT gates.</li>"
    "<li>Your goal is to replicate the desired output as specified in the table.</li>"
    "</ul>"
    "<h3>Expected Output Values:</h3>"
    "<table border='1'>"
    "<tr><th>Input 1</th><th>Input 2</th><th>Output</th></tr>"
    "<tr><td>false</td><td>false</td><td>true</td></tr>"
    "<tr><td>false</td><td>true</td><td>false</td></tr>"
    "<tr><td>true</td><td>false</td><td>false</td></tr>"
    "<tr><td>true</td><td>true</td><td>true</td></tr>"
    "</table>"
    "</body></html>",
    2, // Number of inputs
    { GateType::AndGateType, GateType::OrGateType, GateType::NotGateType }, // Allowed gates
    { true, false, false, true } // Expected results
};

// Tutorial 4 Configuration
TutorialConfig Tutorial4Config = {
    "<html><body><h2>Tutorial</h2></body></html>",
    "<html><body>"
    "<p>In this level, you will build an <b>XOR</b> gate using basic gates like <b>AND</b>, <b>OR</b>, and <b>NOT</b>.</p>"
    "<h3>Your Task:</h3>"
    "<ul>"
    "<li>The XOR gate outputs true only if the inputs are different.</li>"
    "<li>Combine AND, OR, and NOT gates to create an XOR gate.</li>"
    "<li>Connect the input gates to your XOR gate.</li>"
    "<li>Observe the final output.</li>"
    "<li>Your goal is to replicate the XOR functionality.</li>"
    "</ul>"
    "<h3>Expected Output Values:</h3>"
    "<table border='1'>"
    "<tr><th>Input 1</th><th>Input 2</th><th>Output</th></tr>"
    "<tr><td>false</td><td>false</td><td>false</td></tr>"
    "<tr><td>false</td><td>true</td><td>true</td></tr>"
    "<tr><td>true</td><td>false</td><td>true</td></tr>"
    "<tr><td>true</td><td>true</td><td>false</td></tr>"
    "</table>"
    "</body></html>",
    2, // Number of inputs
    { GateType::AndGateType, GateType::OrGateType, GateType::NotGateType }, // Allowed gates
    { false, true, true, false } // Expected results for XOR gate
};

// Tutorial 5 Configuration
TutorialConfig Tutorial5Config = {
    "<html><body><h2>Tutorial</h2></body></html>",
    "<html><body>"
    "<p>In this level, you will work with three inputs to build a circuit that matches the given truth table.</p>"
    "<h3>Your Task:</h3>"
    "<ul>"
    "<li>Connect the three input gates through a combination of AND, OR, and NOT gates.</li>"
    "<li>Achieve the desired outputs as specified in the table.</li>"
    "<li>Your goal is to understand how to manage multiple inputs and gates.</li>"
    "</ul>"
    "<h3>Expected Output Values:</h3>"
    "<table border='1'>"
    "<tr><th>Input 1</th><th>Input 2</th><th>Input 3</th><th>Output</th></tr>"
    "<tr><td>false</td><td>false</td><td>false</td><td>false</td></tr>"
    "<tr><td>false</td><td>false</td><td>true</td><td>true</td></tr>"
    "<tr><td>false</td><td>true</td><td>false</td><td>false</td></tr>"
    "<tr><td>false</td><td>true</td><td>true</td><td>true</td></tr>"
    "<tr><td>true</td><td>false</td><td>false</td><td>true</td></tr>"
    "<tr><td>true</td><td>false</td><td>true</td><td>false</td></tr>"
    "<tr><td>true</td><td>true</td><td>false</td><td>true</td></tr>"
    "<tr><td>true</td><td>true</td><td>true</td><td>false</td></tr>"
    "</table>"
    "</body></html>",
    3, // Number of inputs
    { GateType::AndGateType, GateType::OrGateType, GateType::NotGateType }, // Allowed gates
    { false, true, false, true, true, false, true, false } // Expected results
};

// Tutorial 6 Configuration
TutorialConfig Tutorial6Config = {
    "<html><body><h2>Tutorial</h2></body></html>",
    "<html><body>"
    "<p>In this challenging level, you will work with four inputs to build a complex circuit.</p>"
    "<h3>Your Task:</h3>"
    "<ul>"
    "<li>Connect the four input gates through a combination of AND, OR, NOT, NAND, and NOR gates.</li>"
    "<li>Achieve the desired outputs as specified in the table.</li>"
    "<li>Your goal is to solve the complex logic and achieve the correct outputs.</li>"
    "</ul>"
    "<h3>Expected Output Values:</h3>"
    "<table border='1'>"
    "<tr><th>Input 1</th><th>Input 2</th><th>Input 3</th><th>Input 4</th><th>Output</th></tr>"
    "<tr><td>false</td><td>false</td><td>false</td><td>false</td><td>false</td></tr>"
    "<tr><td>false</td><td>false</td><td>false</td><td>true</td><td>true</td></tr>"
    "<tr><td>false</td><td>false</td><td>true</td><td>false</td><td>false</td></tr>"
    "<tr><td>false</td><td>false</td><td>true</td><td>true</td><td>true</td></tr>"
    "<tr><td>false</td><td>true</td><td>false</td><td>false</td><td>true</td></tr>"
    "<tr><td>false</td><td>true</td><td>false</td><td>true</td><td>false</td></tr>"
    "<tr><td>false</td><td>true</td><td>true</td><td>false</td><td>true</td></tr>"
    "<tr><td>false</td><td>true</td><td>true</td><td>true</td><td>false</td></tr>"
    "<tr><td>true</td><td>false</td><td>false</td><td>false</td><td>false</td></tr>"
    "<tr><td>true</td><td>false</td><td>false</td><td>true</td><td>true</td></tr>"
    "<tr><td>true</td><td>false</td><td>true</td><td>false</td><td>false</td></tr>"
    "<tr><td>true</td><td>false</td><td>true</td><td>true</td><td>true</td></tr>"
    "<tr><td>true</td><td>true</td><td>false</td><td>false</td><td>true</td></tr>"
    "<tr><td>true</td><td>true</td><td>false</td><td>true</td><td>false</td></tr>"
    "<tr><td>true</td><td>true</td><td>true</td><td>false</td><td>true</td></tr>"
    "<tr><td>true</td><td>true</td><td>true</td><td>true</td><td>false</td></tr>"
    "</table>"
    "</body></html>",
    4, // Number of inputs
    { GateType::AndGateType, GateType::OrGateType, GateType::NotGateType, GateType::NandGateType, GateType::NorGateType }, // Allowed gates
    { false, true, false, true, true, false, true, false, false, true, false, true, true, false, true, false } // Expected results
};
