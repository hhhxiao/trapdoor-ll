#ifndef TRAPDOOR_SIM_PLAYER_H
#define TRAPDOOR_SIM_PLAYER_H
#include <MC/BlockSource.hpp>
#include <MC/SimulatedPlayer.hpp>
#include <unordered_map>
#include <unordered_set>

#include "CommandHelper.h"
#include "DynamicCommandAPI.h"
#include "ScheduleAPI.h"

namespace trapdoor {
    class SimPlayerManager {
        struct SimInfo {
            std::string name;
            SimulatedPlayer* simPlayer;
            ScheduleTask task;
        };

        void syncPlayerListToFile();

       public:
        inline void setupCommandInstance(const DynamicCommandInstance* instance) {
            this->cmdInstance = instance;
        }

        void addPlayersInCache();

        void tick();

        void processDieEvent(const std::string& name);

        void tryRefreshInv(Player* player);

        SimulatedPlayer* tryFetchSimPlayer(const std::string& name, bool needFree);

        ActionResult listAll();

        ActionResult getBackpack(const std::string& name, int slot);

        ActionResult behavior(const std::string& name, const std::string& behType, const Vec3& vec);

        ActionResult addPlayer(const std::string& name, const BlockPos& p, int dimID,
                               Player* origin);

        ActionResult removePlayer(const std::string& name);

        ActionResult interactSchedule(const std::string& name, Player* origin, int repType,
                                      int interval, int times);

        ActionResult attackSchedule(const std::string& name, Player* origin, int repType,
                                    int interval, int times);

        ActionResult destroyOnSchedule(const std::string& name, const BlockPos& p, Player* origin,
                                       int repType, int interval, int times);

        ActionResult destroySchedule(const std::string& name, int repType, int interval, int times);

        ActionResult jumpSchedule(const std::string& name, int repType, int interval, int times);

        ActionResult useSchedule(const std::string& name, int itemId, int repType, int interval,
                                 int times);

        ActionResult useOnBlockSchedule(const std::string& name, int itemID, const BlockPos& p,
                                        Player* ori, int repType, int interval, int times);

        ActionResult setItem(const std::string& name, int itemId);

        ActionResult dropItem(const std::string& name, int itemId);

        void cancel(const std::string& name);

        void stopAction(const std::string& name);

        bool checkSurvival(const std::string& name);

       private:
        void refreshCommandSoftEnum();

        std::unordered_map<std::string, SimInfo> simPlayers;
        const DynamicCommandInstance* cmdInstance = nullptr;
    };
}  // namespace trapdoor

#endif