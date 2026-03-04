/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#ifndef MOD_PLAYERBOTS_SRC_BOT_PLAYERBOTMODAPI_H_
#define MOD_PLAYERBOTS_SRC_BOT_PLAYERBOTMODAPI_H_

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
    void RegisterOnBotLogin(BotLifecycleHook hook) { on_bot_login_hooks_.push_back(hook); }
    void RegisterOnBotLogout(BotLifecycleHook hook) { on_bot_logout_hooks_.push_back(hook); }

    // Internal triggers for hooks (used by mod-playerbots)
    void TriggerOnBotLogin(Player* bot) { for (auto& hook : on_bot_login_hooks_) hook(bot); }
    void TriggerOnBotLogout(Player* bot) { for (auto& hook : on_bot_logout_hooks_) hook(bot); }

    // Dynamic AI Object Registration
    void RegisterStrategy(std::string name, StrategyCreator creator) { strategy_creators_[name] = creator; }
    void RegisterAction(std::string name, ActionCreator creator) { action_creators_[name] = creator; }
    void RegisterTrigger(std::string name, TriggerCreator creator) { trigger_creators_[name] = creator; }

    StrategyCreator GetStrategyCreator(std::string name) { return strategy_creators_.count(name) ? strategy_creators_[name] : nullptr; }
    ActionCreator GetActionCreator(std::string name) { return action_creators_.count(name) ? action_creators_[name] : nullptr; }
    TriggerCreator GetTriggerCreator(std::string name) { return trigger_creators_.count(name) ? trigger_creators_[name] : nullptr; }

    std::vector<std::string> GetRegisteredStrategies() { 
        std::vector<std::string> names;
        for (auto const& [name, _] : strategy_creators_) names.push_back(name);
        return names;
    }

    std::vector<std::string> GetRegisteredActions() { 
        std::vector<std::string> names;
        for (auto const& [name, _] : action_creators_) names.push_back(name);
        return names;
    }

    std::vector<std::string> GetRegisteredTriggers() { 
        std::vector<std::string> names;
        for (auto const& [name, _] : trigger_creators_) names.push_back(name);
        return names;
    }

    // Bot Strategy Management
    void AddStrategyToBot(ObjectGuid botGuid, std::string const name, BotState type);
    void RemoveStrategyFromBot(ObjectGuid botGuid, std::string const name, BotState type);

private:
    PlayerbotModAPI() = default;
    ~PlayerbotModAPI() = default;

    std::vector<BotLifecycleHook> on_bot_login_hooks_;
    std::vector<BotLifecycleHook> on_bot_logout_hooks_;

    std::unordered_map<std::string, StrategyCreator> strategy_creators_;
    std::unordered_map<std::string, ActionCreator> action_creators_;
    std::unordered_map<std::string, TriggerCreator> trigger_creators_;
};

#define sPlayerbotModAPI PlayerbotModAPI::instance()

#endif
