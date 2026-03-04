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

class Player;

typedef std::function<void(Player*)> BotLifecycleHook;

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

private:
    PlayerbotModAPI() = default;
    ~PlayerbotModAPI() = default;

    std::vector<BotLifecycleHook> onBotLoginHooks;
    std::vector<BotLifecycleHook> onBotLogoutHooks;
};

#define sPlayerbotModAPI PlayerbotModAPI::instance()

#endif
