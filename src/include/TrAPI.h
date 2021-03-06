//
// Created by xhy on 2022/6/20.
//

#ifndef TRAPDOOR_TRAPI_H
#define TRAPDOOR_TRAPI_H

#include <MC/Biome.hpp>
#include <MC/CircuitSceneGraph.hpp>
#include <MC/CircuitSystem.hpp>
#include <string>
namespace trapdoor {
    std::string getBiomeName(Biome * biome);

    CircuitSceneGraph &getCircuitSceneGraph(CircuitSystem * system);
}  // namespace trapdoor

#endif  // TRAPDOOR_TRAPI_H
