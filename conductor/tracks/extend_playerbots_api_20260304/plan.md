# Plan: Extend mod-playerbots API

## Phase 1: Core Hook System Implementation [checkpoint: b0b19d6]

### Goal
Implement the initial bot lifecycle hooks and the primary singleton interface for external modules.

- [x] Task: Define the `PlayerbotModAPI` singleton structure and registration methods. [0c06a22]
    - [x] Implement `PlayerbotModAPI` singleton in a new file `src/Bot/PlayerbotModAPI.h`.
- [x] Task: Integrate `OnBotLogin` and `OnBotLogout` hooks into `PlayerbotMgr`. [0c06a22]
    - [x] Modify `PlayerbotMgr::AddPlayerbot` and `PlayerbotMgr::RemovePlayerbot` to trigger the new hooks.
- [x] Task: Conductor - User Manual Verification 'Core Hook System Implementation' (Protocol in workflow.md)

## Phase 2: Action & Strategy Registration API

### Goal
Refactor existing context logic to allow external modules to register custom actions and strategies dynamically.

- [x] Task: Extend `AiObjectContext` to support dynamic registration of triggers, actions, and strategies. [f78e737]
    - [x] Refactor `AiObjectContext` to maintain a registry of externally provided AI objects.
- [x] Task: Implement a public method to add a new strategy to a specific bot's current strategy list. [f78e737]
    - [x] Implement `PlayerbotModAPI::AddStrategyToBot(guid, strategy_name)`.
- [x] Task: Conductor - User Manual Verification 'Action & Strategy Registration API' (Protocol in workflow.md)

## Phase 3: External Access & Documentation [checkpoint: 60f1175]

### Goal
Finalize the API for external use and provide documentation for module developers.

- [x] Task: Create a dedicated `PlayerbotAPI.h` header file for external inclusion. [f78e737]
    - [x] Aggregate public API methods into `PlayerbotAPI.h`.
- [x] Task: Write a README-API.md for the `mod-playerbots` module. [f78e737]
    - [x] Document the available hooks and registration methods.
    - [x] Provide a code snippet example for a simple "Hello Bot" external module.
- [x] Task: Conductor - User Manual Verification 'External Access & Documentation' (Protocol in workflow.md)

## Phase: Review Fixes
- [~] Task: Apply review suggestions
