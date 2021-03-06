//
// Created by xhy on 2022/5/17.
//
#include "DynamicCommandAPI.h"
#include "TrapdoorMod.h"
#include "VillageHelper.h"

namespace trapdoor {
    void setup_villageCommand(int level) {
        using ParamType = DynamicCommand::ParameterType;
        // create a dynamic command
        auto command = DynamicCommand::createCommand("village", "village helper",
                                                     static_cast<CommandPermissionLevel>(level));

        auto &optSwitch =
            command->setEnum("optSwitch", {"bound", "spawn", "center", "poi", "head"});
        command->mandatory("village", ParamType::Enum, optSwitch,
                           CommandParameterOption::EnumAutocompleteExpansion);
        command->mandatory("onoroff", ParamType::Bool);
        command->addOverload({optSwitch, "onoroff"});

        auto &optList = command->setEnum("optList", {"list"});
        command->mandatory("village", ParamType::Enum, optList,
                           CommandParameterOption::EnumAutocompleteExpansion);
        command->addOverload({optList});

        auto &optOther = command->setEnum("optOther", {"info"});
        command->optional("village", ParamType::Enum, optOther,
                          CommandParameterOption::EnumAutocompleteExpansion);
        command->addOverload({optOther});
        command->mandatory("villageID", ParamType::Int);
        command->addOverload({optOther, "villageID"});

        auto cb = [](DynamicCommand const &command, CommandOrigin const &origin,
                     CommandOutput &output,
                     std::unordered_map<std::string, DynamicCommand::Result> &results) {
            auto show = results["onoroff"].getRaw<bool>();
            switch (do_hash(results["village"].getRaw<std::string>().c_str())) {
                case do_hash("list"):
                    trapdoor::mod().getVillageHelper().listTickingVillages(true).sendTo(output);
                    break;

                case do_hash("bound"):
                    trapdoor::mod().getVillageHelper().setShowBounds(show).sendTo(output);
                    break;

                case do_hash("spawn"):
                    trapdoor::mod().getVillageHelper().setShowIronSpawnArea(show).sendTo(output);
                    break;

                case do_hash("center"):
                    trapdoor::mod().getVillageHelper().setShowCenter(show).sendTo(output);
                    break;

                case do_hash("poi"):
                    trapdoor::mod().getVillageHelper().setShowPoiQuery(show).sendTo(output);
                    break;

                case do_hash("head"):
                    trapdoor::mod().getVillageHelper().setShowVillagerHeadInfo(show).sendTo(output);
                    break;
                case do_hash("info"):
                    if (results["villageID"].isSet) {
                        trapdoor::mod()
                            .getVillageHelper()
                            .printDetails(results["villageID"].getRaw<int>(), Vec3::ZERO)
                            .sendTo(output);
                    } else {
                        trapdoor::mod()
                            .getVillageHelper()
                            .printDetails(-1, origin.getPlayer()->getPos())
                            .sendTo(output);
                    }
                    break;
            }
        };
        command->setCallback(cb);
        DynamicCommand::setup(std::move(command));
    }

}  // namespace trapdoor