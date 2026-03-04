/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#include "AiObjectContext.h"
#include "Helpers.h"
#include "PlayerbotModAPI.h"

#include "ActionContext.h"
#include "ChatActionContext.h"
#include "ChatTriggerContext.h"
#include "DKAiObjectContext.h"
#include "DruidAiObjectContext.h"
#include "HunterAiObjectContext.h"
#include "MageAiObjectContext.h"
#include "PaladinAiObjectContext.h"
#include "PriestAiObjectContext.h"
#include "RogueAiObjectContext.h"
#include "ShamanAiObjectContext.h"
#include "WarlockAiObjectContext.h"
#include "WarriorAiObjectContext.h"

SharedNamedObjectContextList<Strategy> AiObjectContext::sharedStrategyContexts;
SharedNamedObjectContextList<Action> AiObjectContext::sharedActionContexts;
SharedNamedObjectContextList<Trigger> AiObjectContext::sharedTriggerContexts;
SharedNamedObjectContextList<UntypedValue> AiObjectContext::sharedValueContexts;

AiObjectContext::AiObjectContext(PlayerbotAI* botAI, SharedNamedObjectContextList<Strategy>& sharedStrategyContext,
                                 SharedNamedObjectContextList<Action>& sharedActionContext,
                                 SharedNamedObjectContextList<Trigger>& sharedTriggerContext,
                                 SharedNamedObjectContextList<UntypedValue>& sharedValueContext)
    : PlayerbotAIAware(botAI),
      strategyContexts(sharedStrategyContext),
      actionContexts(sharedActionContext),
      triggerContexts(sharedTriggerContext),
      valueContexts(sharedValueContext)
{
}

void AiObjectContext::BuildAllSharedContexts()
{
    AiObjectContext::BuildSharedContexts();
    PriestAiObjectContext::BuildSharedContexts();
    MageAiObjectContext::BuildSharedContexts();
    WarlockAiObjectContext::BuildSharedContexts();
    WarriorAiObjectContext::BuildSharedContexts();
    ShamanAiObjectContext::BuildSharedContexts();
    PaladinAiObjectContext::BuildSharedContexts();
    DruidAiObjectContext::BuildSharedContexts();
    HunterAiObjectContext::BuildSharedContexts();
    RogueAiObjectContext::BuildSharedContexts();
    DKAiObjectContext::BuildSharedContexts();
}

void AiObjectContext::BuildSharedContexts()
{
    BuildSharedStrategyContexts(sharedStrategyContexts);
    BuildSharedActionContexts(sharedActionContexts);
    BuildSharedTriggerContexts(sharedTriggerContexts);
    BuildSharedValueContexts(sharedValueContexts);
}

std::vector<std::string> AiObjectContext::Save()
{
    std::vector<std::string> result;

    std::set<std::string> names = valueContexts.GetCreated();
    for (std::set<std::string>::iterator i = names.begin(); i != names.end(); ++i)
    {
        UntypedValue* value = GetUntypedValue(*i);
        if (!value)
            continue;

        std::string const data = value->Save();
        if (data == "?")
            continue;

        std::string const name = *i;
        std::ostringstream out;
        out << name;

        out << ">" << data;
        result.push_back(out.str());
    }

    return result;
}

void AiObjectContext::Load(std::vector<std::string> data)
{
    for (std::vector<std::string>::iterator i = data.begin(); i != data.end(); ++i)
    {
        std::string const row = *i;
        std::vector<std::string> parts = split(row, '>');
        if (parts.size() != 2)
            continue;

        std::string const name = parts[0];
        std::string const text = parts[1];

        UntypedValue* value = GetUntypedValue(name);
        if (!value)
            continue;

        value->Load(text);
    }
}

Strategy* AiObjectContext::GetStrategy(std::string const name)
{
    Strategy* strategy = strategyContexts.GetContextObject(name, botAI);
    if (!strategy)
    {
        if (StrategyCreator creator = sPlayerbotModAPI.GetStrategyCreator(name))
        {
            strategy = creator(botAI);
        }
    }
    return strategy;
}

std::set<std::string> AiObjectContext::GetSiblingStrategy(std::string const name)
{
    return strategyContexts.GetSiblings(name);
}

Trigger* AiObjectContext::GetTrigger(std::string const name) 
{ 
    Trigger* trigger = triggerContexts.GetContextObject(name, botAI); 
    if (!trigger)
    {
        if (TriggerCreator creator = sPlayerbotModAPI.GetTriggerCreator(name))
        {
            trigger = creator(botAI);
        }
    }
    return trigger;
}

Action* AiObjectContext::GetAction(std::string const name) 
{ 
    Action* action = actionContexts.GetContextObject(name, botAI); 
    if (!action)
    {
        if (ActionCreator creator = sPlayerbotModAPI.GetActionCreator(name))
        {
            action = creator(botAI);
        }
    }
    return action;
}

UntypedValue* AiObjectContext::GetUntypedValue(std::string const name)
{
    return valueContexts.GetContextObject(name, botAI);
}

std::set<std::string> AiObjectContext::GetValues() { return valueContexts.GetCreated(); }

std::set<std::string> AiObjectContext::GetSupportedStrategies() 
{ 
    std::set<std::string> names = strategyContexts.supports(); 
    std::vector<std::string> dynamicNames = sPlayerbotModAPI.GetRegisteredStrategies();
    for (std::string const& name : dynamicNames)
    {
        names.insert(name);
    }
    return names;
}

std::set<std::string> AiObjectContext::GetSupportedActions() 
{ 
    std::set<std::string> names = actionContexts.supports(); 
    std::vector<std::string> dynamicNames = sPlayerbotModAPI.GetRegisteredActions();
    for (std::string const& name : dynamicNames)
    {
        names.insert(name);
    }
    return names;
}

std::string const AiObjectContext::FormatValues()
{
    std::ostringstream out;
    std::set<std::string> names = valueContexts.GetCreated();
    for (std::set<std::string>::iterator i = names.begin(); i != names.end(); ++i, out << "|")
    {
        UntypedValue* value = GetUntypedValue(*i);
        if (!value)
            continue;

        std::string const text = value->Format();
        if (text == "?")
            continue;

        out << "{" << *i << "=" << text << "}";
    }

    return out.str();
}
