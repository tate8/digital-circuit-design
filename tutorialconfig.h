#ifndef TUTORIALCONFIG_H
#define TUTORIALCONFIG_H

#include <string>
#include <vector>
#include "GateTypes.h"

struct TutorialConfig {
    std::string titleText;
    std::string tutorialText;
    int numInputs;
    int numOutputs;
    std::vector<GateType> allowedGates;
    std::vector<bool> expectedResults;
};

extern TutorialConfig Tutorial1Config;
extern TutorialConfig Tutorial2Config;
extern TutorialConfig Tutorial3Config;
extern TutorialConfig Tutorial4Config;
extern TutorialConfig Tutorial5Config;
extern TutorialConfig Tutorial6Config;
extern TutorialConfig SandboxTutorialConfig;

#endif // TUTORIALCONFIG_H
