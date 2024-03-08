# `FreeRTOS/Demo/ThirdParty/Community-Supported-Demos/CORTEX_M0+_RP2040/README.md`

## はじめに

FreeRTOS-KernelのRP2040移植版のデモプログラムです。これらのデモはRP2040 FreeRTOS-Kernelの
通常版とSMP版で同じものが使われていますが。通常版ではSMP版に特化したデモはもちろん省略
されていることに注意してください。

SMP版と通常版のFreeRTOS-Kernelを切り替えるには、 `/Source` にあるFreeRTOS-Kernelのブランチを
`main`と`smp`の間で都度変更するか、`FREERTOS_KERNEL_PATH` (後述) を使って希望のバージョンを
指定してください。

## ビルド

サンプルは通常のRaspberry Pi Pico SDKアプリケーションと同じようにビルドします。
このルートディレクトリからビルドすることも、個々のサンプルディレクトリから
ビルドすることもできます。

Raspberry Pi Pico SDKのビルド環境のセットアップについてはSDKドキュメントの
[Getting Started With Pico](https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf)を
参照してください。すでにセットアップされている場合は環境変数 `PICO_SDK_PATH` を
設定するか、Cmakeコマンドラインで `-DPICO_SDK_PATH=xxx` として渡してください。

unixでコマンドラインからビルドするには、このディレクトリ（または個々のサンプルの
ディレクトリ）で次のようにタイプしてください。

```shell
mkdir build
cd build
cmake ..
make
```

これにより関連するビルドディレクトに各サンプルの`.uf2`ファイルが生成されます。

環境変数 `FREERTOS_KERNEL_PATH` か、CMakeコマンドラインでFreeRTOSカーネルの
特定のインスタンスを設定することができます。そうしない場合は、このプロジェクトに
ある`Source/`のFreeRTOSカーネルが使用されます。

## デモ

### 標準

標準的な _Minimal_ な main_blinkとmain_fullテストデモです。

### OnEitherCore

一方のコアで実行されるSDKコードと、もう一方のコアで実行されるFreeRTOSタスクとの
相互作用を示す同じデモの2つのバージョンです（両者の通信にはSDK同期プリミティブを
使用しています）。一方のバージョンではコア0でFreeRTOSが動作し、もう一方ではコア1で
FreeRTOSが動作します。

## 訳注

1. `Source`リポジトリの`smp`ブランチはdeprecatedで、`main`にマージされた。
2. `Demo`のソースはすでにmainブランチを使用するようになっている。
3. したがって、以下（`Source`リポジトリの`smp`ブランチのREADMEの冒頭にある）
   は今となっては意味はないがとりあえず残しておく。

### アナウンス

FreeRTOSのSMP機能はFreeRTOS-Kernelのmainブランチにマージされました。
FreeRTOS SMPアプリケーションの開発にはFreeRTOS-Kernelのmainブランチを
使うことを推奨します。

smpブランチの内容は一定期間利用可能ですが、更新の提供や新しい貢献や
pull requestの受付は終了します。

他に質問がありますか? [FreeRTOSフォーラム](https://forums.freertos.org/)に
投稿してください。

### SMPブランチからFreeRTOS v11へポートを移行する

SMPブランチからFreeRTOS v11にポートを移行するには、以下の変更を適用する必要があります.

- ポートのクリティカルセクションで`xTaskIncrementTick`を呼び出す。

RP2040の例:

```c
void xPortSysTickHandler( void )
{
    portBASE_TYPE xPreviousMask;

    /* xTaskIncrementTick now must be called in critical section. */
    xPreviousMask = taskENTER_CRITICAL_FROM_ISR();
    {
        /* Increment the RTOS tick. */
        if( xTaskIncrementTick() != pdFALSE )
        {
            /* Pend a context switch. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
    }
    taskEXIT_CRITICAL_FROM_ISR( xPreviousMask );
}
```

- `configNUM_CORES` を `configNUMBER_OF_CORES` に変更する
- ポートで `portSET/CLEAR_INTERRUPT_MASK` を定義する
- ポートでSMP用に `portENTER/EXIT_CRITICAL_FROM_ISR` を定義する
    - これらのマクロは `vTaskEnterCriticalFromISR` / `xTaskExitCriticalFromISR` で
      実装する必要がある
- ポートの `portSET/CLEAR_INTERRUPT_MASK_FROM_ISR` の実装を更新する
    - SMP版ではISRからクリティカルセクションに入る/出るためにこれらのマクロは
      使用せず、`portENTER/EXIT_CRITICAL_FROM_ISR` を使用していた。
      これらの関数は、マクロ名が示唆するように、ネストされた割り込みがサポートされて
      いる場合にISRから割り込みマスクをセットまたはクリアするように実装する
      必要がある。
