/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#include "PlayerbotModAPI.h"

#include "ObjectAccessor.h"
#include "PlayerbotAI.h"
#include "PlayerbotMgr.h"

bool PlayerbotModAPI::TriggerChatCommandHandlers(Player* requester, Player* bot, uint32 type, std::string& msg)
{
    for (auto& hook : chat_command_hooks_)
        if (hook(requester, bot, type, msg))
            return true;

    return false;
}

void PlayerbotModAPI::AddStrategyToBot(ObjectGuid botGuid, std::string const name, BotState type)
{
    if (Player* bot = ObjectAccessor::FindConnectedPlayer(botGuid))
    {
        if (PlayerbotAI* ai = sPlayerbotsMgr.GetPlayerbotAI(bot))
        {
            if (!ai->HasStrategy(name, type))
                ai->ChangeStrategy("+" + name, type);
        }
    }
}

void PlayerbotModAPI::RemoveStrategyFromBot(ObjectGuid botGuid, std::string const name, BotState type)
{
    if (Player* bot = ObjectAccessor::FindConnectedPlayer(botGuid))
    {
        if (PlayerbotAI* ai = sPlayerbotsMgr.GetPlayerbotAI(bot))
        {
            if (ai->HasStrategy(name, type))
                ai->ChangeStrategy("-" + name, type);
        }
    }
}
