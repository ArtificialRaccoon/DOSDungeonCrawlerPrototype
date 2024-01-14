#include "VisionCone.h"

VisionCone::VisionCone()
{
    for (auto &space : Tier0) { space = MapSpace(); }
    for (auto &space : Tier1) { space = MapSpace(); }
    for (auto &space : Tier2) { space = MapSpace(); }
    for (auto &space : Tier3) { space = MapSpace(); }
    for (auto &space : Tier4) { space = MapSpace(); }
}