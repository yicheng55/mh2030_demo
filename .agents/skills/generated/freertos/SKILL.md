---
name: freertos
description: "Skill for the Freertos area of mh2030_demo. 157 symbols across 13 files."
---

# Freertos

157 symbols | 13 files | Cohesion: 83%

## When to Use

- Working with code in `ModuleDemo/`
- Understanding how vCoRoutineSchedule, xEventGroupSync, xEventGroupWaitBits work
- Modifying freertos-related functionality

## Key Files

| File | Symbols |
|------|---------|
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/tasks.c` | vApplicationStackOverflowHook, vApplicationTickHook, prvSearchForNameWithinSingleList, prvResetNextTaskUnblockTime, prvWriteNameToBuffer (+56) |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/queue.c` | vQueueWaitForMessageRestricted, xQueueGiveMutexRecursive, xQueueTakeMutexRecursive, xQueueGenericReceive, prvIsQueueEmpty (+29) |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/timers.c` | xTimerGenericCommand, prvProcessExpiredTimer, prvTimerTask, prvProcessTimerOrBlockTask, prvGetNextExpireTime (+11) |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c` | xEventGroupSync, xEventGroupWaitBits, xEventGroupSetBits, vEventGroupDelete, vEventGroupSetBitsCallback (+7) |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/croutine.c` | prvCheckPendingReadyList, prvCheckDelayedList, vCoRoutineSchedule, vCoRoutineAddToDelayedList, xCoRoutineRemoveFromEventList (+2) |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/list.c` | vListInsertEnd, vListInsert, uxListRemove, vListInitialiseItem, vListInitialise |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/port.c` | xPortPendSVHandler, pxPortInitialiseStack, prvSetupTimerInterrupt, prvPortStartFirstTask, vPortEndScheduler |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_4.c` | prvInsertBlockIntoFreeList, prvHeapInit, pvPortMalloc, vPortFree |
| `ModuleDemo/OS/FREERTOS/USER/main.c` | NVIC_Configuration, main, TEST_Thread1, TEST_Thread2 |
| `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_2.c` | prvHeapInit, pvPortMalloc, vPortFree |

## Entry Points

Start here when exploring this area:

- **`vCoRoutineSchedule`** (Function) — `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/croutine.c:319`
- **`xEventGroupSync`** (Function) — `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c:207`
- **`xEventGroupWaitBits`** (Function) — `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c:323`
- **`xEventGroupSetBits`** (Function) — `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c:529`
- **`vEventGroupDelete`** (Function) — `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c:623`

## Key Symbols

| Symbol | Type | File | Line |
|--------|------|------|------|
| `vCoRoutineSchedule` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/croutine.c` | 319 |
| `xEventGroupSync` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c` | 207 |
| `xEventGroupWaitBits` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c` | 323 |
| `xEventGroupSetBits` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c` | 529 |
| `vEventGroupDelete` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c` | 623 |
| `vEventGroupSetBitsCallback` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/event_groups.c` | 667 |
| `pvPortMalloc` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_1.c` | 110 |
| `pvPortMalloc` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_2.c` | 159 |
| `vPortFree` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_2.c` | 251 |
| `pvPortMalloc` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_3.c` | 99 |
| `vPortFree` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_3.c` | 124 |
| `pvPortMalloc` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_4.c` | 154 |
| `vPortFree` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_4.c` | 304 |
| `pvPortMalloc` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_5.c` | 173 |
| `vPortFree` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/heap_5.c` | 313 |
| `vListInsertEnd` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/list.c` | 115 |
| `vListInsert` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/list.c` | 144 |
| `uxListRemove` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/list.c` | 211 |
| `xPortPendSVHandler` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/port.c` | 108 |
| `vQueueWaitForMessageRestricted` | Function | `ModuleDemo/OS/FREERTOS/SYSTEM/freertos/queue.c` | 2357 |

## Execution Flows

| Flow | Type | Steps |
|------|------|-------|
| `Main → RCC_DeInit` | cross_community | 3 |
| `Main → RCC_HSEConfig` | cross_community | 3 |
| `Main → RCC_GetFlagStatus` | cross_community | 3 |
| `Main → RCC_PLLCmd` | cross_community | 3 |
| `Main → RCC_APB2PeriphClockCmd` | cross_community | 3 |
| `Main → RCC_AHBPeriphClockCmd` | cross_community | 3 |
| `Main → GPIO_PinAFConfig` | cross_community | 3 |
| `Main → GPIO_Init` | cross_community | 3 |
| `Main → NVIC_Init` | cross_community | 3 |

## Connected Areas

| Area | Connections |
|------|-------------|
| USER | 4 calls |

## How to Explore

1. `gitnexus_context({name: "vCoRoutineSchedule"})` — see callers and callees
2. `gitnexus_query({query: "freertos"})` — find related execution flows
3. Read key files listed above for implementation details
