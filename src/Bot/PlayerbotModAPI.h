/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_PLAYERBOTMODAPI_H
#define _PLAYERBOT_PLAYERBOTMODAPI_H

#include <functional>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "ObjectGuid.h"

class Player;
class PlayerbotAI;
class Strategy;
class Action;
class Trigger;
enum BotState : uint32;

typedef std::function<void(Player*)> BotLifecycleHook;
typedef std::function<Strategy*(PlayerbotAI*)> StrategyCreator;
typedef std::function<Action*(PlayerbotAI*)> ActionCreator;
typedef std::function<Trigger*(PlayerbotAI*)> TriggerCreator;

class PlayerbotModAPI
{
public:
    static PlayerbotModAPI& instance()
    {
        static PlayerbotModAPI instance;
        return instance;
    }

    // Lifecycle Hooks Registration
    void RegisterOnBotLogin(BotLifecycleHook hook) { onBotLoginHooks.push_back(hook); }
    void RegisterOnBotLogout(BotLifecycleHook hook) { onBotLogoutHooks.push_back(hook); }

    // Internal triggers for hooks (used by mod-playerbots)
    void TriggerOnBotLogin(Player* bot) { for (auto& hook : onBotLoginHooks) hook(bot); }
    void TriggerOnBotLogout(Player* bot) { for (auto& hook : onBotLogoutHooks) hook(bot); }

    // Dynamic AI Object Registration
    void RegisterStrategy(std::string name, StrategyCreator creator) { strategyCreators[name] = creator; }
    void RegisterAction(std::string name, ActionCreator creator) { actionCreators[name] = creator; }
    void RegisterTrigger(std::string name, TriggerCreator creator) { triggerCreators[name] = creator; }

    StrategyCreator GetStrategyCreator(std::string name) { return strategyCreators.count(name) ? strategyCreators[name] : nullptr; }
    ActionCreator GetActionCreator(std::string name) { return actionCreators.count(name) ? actionCreators[name] : nullptr; }
    TriggerCreator GetTriggerCreator(std::string name) { return triggerCreators.count(name) ? triggerCreators[name] : nullptr; }

    std::vector<std::string> GetRegisteredStrategies() { 
        std::vector<std::string> names;
        for (auto const& [name, _] : strategyCreators) names.push_back(name);
        return names;
    }

    std::vector<std::string> GetRegisteredActions() { 
        std::vector<std::string> names;
        for (auto const& [name, _] : actionCreators) names.push_back(name);
        return names;
    }

    std::vector<std::string> GetRegisteredTriggers() { 
        std::vector<std::string> names;
        for (auto const& [name, _] : triggerCreators) names.push_back(name);
        return names;
    }

    // Bot Strategy Management
    void AddStrategyToBot(ObjectGuid botGuid, std::string const name, BotState type);
    void RemoveStrategyFromBot(ObjectGuid botGuid, std::string const name, BotState type);

private:
    PlayerbotModAPI() = default;
    ~PlayerbotModAPI() = default;

    std::vector<BotLifecycleHook> onBotLoginHooks;
    std::vector<BotLifecycleHook> onBotLogoutHooks;

    std::unordered_map<std::string, StrategyCreator> strategyCreators;
    std::unordered_map<std::string, ActionCreator> actionCreators;
    std::unordered_map<std::string, TriggerCreator> triggerCreators;
};

#define sPlayerbotModAPI PlayerbotModAPI::instance()

#endif
