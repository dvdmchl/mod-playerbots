# Plan: Extend mod-playerbots API

## Phase 1: Core Hook System Implementation

### Goal
Implement the initial bot lifecycle hooks and the primary singleton interface for external modules.

- [ ] Task: Define the `PlayerbotModAPI` singleton structure and registration methods.
    - [ ] Write failing unit test for `PlayerbotModAPI` instance retrieval and registration logic.
    - [ ] Implement `PlayerbotModAPI` singleton in `src/Bot/PlayerbotAIConfig.h` or a new API file.
    - [ ] Verify test passes and mark task as complete.
- [ ] Task: Integrate `OnBotLogin` and `OnBotLogout` hooks into `PlayerbotMgr`.
    - [ ] Write failing unit test to verify hook callback registration and execution.
    - [ ] Modify `PlayerbotMgr::AddPlayerbot` and `PlayerbotMgr::RemovePlayerbot` to trigger the new hooks.
    - [ ] Verify test passes and mark task as complete.
- [ ] Task: Conductor - User Manual Verification 'Core Hook System Implementation' (Protocol in workflow.md)

## Phase 2: Action & Strategy Registration API

### Goal
Refactor existing context logic to allow external modules to register custom actions and strategies dynamically.

- [ ] Task: Extend `AiObjectContext` to support dynamic registration of triggers, actions, and strategies.
    - [ ] Write failing unit test for dynamic strategy registration.
    - [ ] Refactor `AiObjectContext` to maintain a registry of externally provided AI objects.
    - [ ] Verify test passes and mark task as complete.
- [ ] Task: Implement a public method to add a new strategy to a specific bot's current strategy list.
    - [ ] Write failing unit test to verify an external strategy can be activated on a bot.
    - [ ] Implement `PlayerbotModAPI::AddStrategyToBot(guid, strategy_name)`.
    - [ ] Verify test passes and mark task as complete.
- [ ] Task: Conductor - User Manual Verification 'Action & Strategy Registration API' (Protocol in workflow.md)

## Phase 3: External Access & Documentation

### Goal
Finalize the API for external use and provide documentation for module developers.

- [ ] Task: Create a dedicated `PlayerbotAPI.h` header file for external inclusion.
    - [ ] Write unit test to verify that the API header contains all necessary symbols without including too many internals.
    - [ ] Aggregate public API methods into `PlayerbotAPI.h`.
    - [ ] Verify test passes and mark task as complete.
- [ ] Task: Write a README-API.md for the `mod-playerbots` module.
    - [ ] Document the available hooks and registration methods.
    - [ ] Provide a code snippet example for a simple "Hello Bot" external module.
    - [ ] Mark task as complete.
- [ ] Task: Conductor - User Manual Verification 'External Access & Documentation' (Protocol in workflow.md)
