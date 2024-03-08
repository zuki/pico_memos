# カスタマイズ

FreeRTOSは`FreeRTOSConfig.h`と呼ばれる構成ファイルを使って
カスタマイズされます。すべてのFreeRTOSアプリケーションは
プリプロセッサのインクルードパスにFreeRTOSConfig.hヘッダ
ファイルを持つ必要があります。FreeRTOSConfig.hはビルドする
アプリケーションに合わせてRTOSカーネルを調整します。そのため、
RTOSではなくアプリケーション固有であり、RTOSカーネルソースコード
ディレクトリではなく、アプリケーションディレクトリに配置する
必要があります。

ダウンロードしたRTOSソースコードに含まれている各デモアプリ
ケーションにはそれぞれ各自のFreeRTOSConfig.hファイルがあります。
デモの中にはかなり古いものもあり、利用可能な構成オプションが
すべて含まれているわけではありません。省略された構成オプションは
RTOSソースファイルにあるデフォルト値に設定されます。

以下は典型的なFreeRTOSConfig.hの定義と各パラメータの説明を
示しています。

```c
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* ここにはアプリケーション全体で必要なヘッダをincludeします */
#include "something.h"

#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_TICKLESS_IDLE                 0
#define configCPU_CLOCK_HZ                      60000000
#define configSYSTICK_CLOCK_HZ                  1000000
#define configTICK_RATE_HZ                      250
#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                128
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configTICK_TYPE_WIDTH_IN_BITS           TICK_TYPE_WIDTH_16_BITS
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_TASK_NOTIFICATIONS            1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   3
#define configUSE_MUTEXES                       0
#define configUSE_RECURSIVE_MUTEXES             0
#define configUSE_COUNTING_SEMAPHORES           0
#define configUSE_ALTERNATIVE_API               0 /* 非推奨! */
#define configQUEUE_REGISTRY_SIZE               10
#define configUSE_QUEUE_SETS                    0
#define configUSE_TIME_SLICING                  0
#define configUSE_NEWLIB_REENTRANT              0
#define configENABLE_BACKWARD_COMPATIBILITY     0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5
#define configUSE_MINI_LIST_ITEM                1
#define configSTACK_DEPTH_TYPE                  uint32_t
#define configMESSAGE_BUFFER_LENGTH_TYPE        size_t
#define configHEAP_CLEAR_MEMORY_ON_FREE         1
#define configUSE_APPLICATION_TASK_TAG          0
#define configSTATS_BUFFER_MAX_LENGTH           0xFFFF

/* メモリ割り当て関連の定義. */
#define configSUPPORT_STATIC_ALLOCATION             1
#define configSUPPORT_DYNAMIC_ALLOCATION            1
#define configKERNEL_PROVIDED_STATIC_MEMORY         1
#define configTOTAL_HEAP_SIZE                       10240
#define configAPPLICATION_ALLOCATED_HEAP            1
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP   1
#define configENABLE_HEAP_PROTECTOR                 1

/* フック関数関連の定義. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0
#define configUSE_SB_COMPLETED_CALLBACK         0

/* 実行時統計とタスク統計の収集関連の定義. */
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                0
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

/* コルーチン関連の定義. */
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         1

/* ソフトウェアタイマー関連の定義. */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               3
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            configMINIMAL_STACK_SIZE

/* ネストした割り込み動作の構成. */
#define configKERNEL_INTERRUPT_PRIORITY         [dependent of processor]
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    [dependent on processor and application]
#define configMAX_API_CALL_INTERRUPT_PRIORITY   [dependent on processor and application]

/* 開発中のエラー捕捉のための定義. */
#define configASSERT( ( x ) ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )

/* FreeRTOS MPU固有の定義. */
#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 0
#define configTOTAL_MPU_REGIONS                                8 /* デフォルト値 */
#define configTEX_S_C_B_FLASH                                  0x07UL /* デフォルト値 */
#define configTEX_S_C_B_SRAM                                   0x07UL /* デフォルト値 */
#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY            1
#define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS             1
#define configENABLE_ERRATA_837070_WORKAROUND                  1
#define configUSE_MPU_WRAPPERS_V1                              0
#define configPROTECTED_KERNEL_OBJECT_POOL_SIZE                10
#define configSYSTEM_CALL_STACK_SIZE                           128
#define configENABLE_ACCESS_CONTROL_LIST                       1

/* ARMv8-M セキュアサイドポート関連の定義. */
#define secureconfigMAX_SECURE_CONTEXTS         5

/* オプション関数 - いずれにせよほとんどのリンカは未使用の関数は削除する. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_uxTaskGetStackHighWaterMark2    0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_eTaskGetState                   0
#define INCLUDE_xEventGroupSetBitFromISR        1
#define INCLUDE_xTimerPendFunctionCall          0
#define INCLUDE_xTaskAbortDelay                 0
#define INCLUDE_xTaskGetHandle                  0
#define INCLUDE_xTaskResumeFromISR              1

/* トレースマクロを定義するヘッダはここでincludeする. */

#endif /* FREERTOS_CONFIG_H */
```

## `config`パラメタ

### `configUSE_PREEMPTION`

1をセットするとプリエンプティブRTOSスケジューラを、0をセットすると
協調型RTOSスケジューラを使用します。

### `configUSE_PORT_OPTIMISED_TASK_SELECTION`

FreeRTOSのポートの中には次に実行するタスクを選択する方法を2つ、
汎用的な方法とそのポート固有の方法を持つものがあります。

汎用的な方法:

- configUSE_PORT_OPTIMISED_TASK_SELECTIONに0が設定されている場合、
  または、ポート固有の方法が実装されていない場合に使用されます。
- FreeRTOSのすべてのポートで使用できます。
- 完全にC言語で書かれているためポート固有のメソッドよりも効率が悪い。
- 利用可能な優先順位の最大数に制限はありません。

ポート固有の方法:

- すべてのポートで利用できるわけではありません。
- configUSE_PORT_OPTIMISED_TASK_SELECTIONに1が設定されている場合に
  使用されます。
- 1つ以上のアーキテクチャ固有のアセンブリ命令（通常は、Count Leading
  Zeros [CLZ] 相当の命令）に依存するため、専用に書かれたアーキテクチャ
  でのみ使用できます。
- 汎用的な方法よりも効率的です。
- 通常、利用可能な優先順位の最大数は32に制限されています。


### `configKERNEL_INTERRUPT_PRIORITY`
### `configMAX_SYSCALL_INTERRUPT_PRIORITY`
### `configMAX_API_CALL_INTERRUPT_PRIORITY`



## `INCLUDE`パラメタ

`INCLUDE'で始まるマクロを使うとアプリケーションで使用されない
リアルタイムカーネルのコンポーネントをビルドから除外することが
できます。これによりRTOSが特定の組み込みアプリケーションで必要
以上のROMやRAMを使用しないようにします。

個のマクロは次のような形を取ります。

```c
#define INCLUDE_vTaskDelete         1
```

ビルドから`vTaskDelete()`を除外するには次のように定義します。

```c
#define INCLUDE_vTaskDelete         0
```
