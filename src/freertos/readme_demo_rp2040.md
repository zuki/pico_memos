# `FreeRTOS/Source/portable/ThirdParty/GCC/RP2040/README.md`

## 概要

このディレクトリはRaspberry Pi Pico SDKとともに使用できるSMP対応のFreeRTOS-Kernelポートを
提供します。このポートは以下をサポートしています。

* シンプルなCMake INTERFACEライブラリ。ユーザのプロジェクトにコードをコピーすることなく
  FreeRTOS-Kernelと必要なメモリ割り当てタイプを提供します。
* FreeRTOS-Kernelとタスクをコア0、コア1、その両方で実行します。
* FreeRTOSタスクとFreeRTOS以外のコアで実行されるコード、または、IRQハンドラとの間でSDKの
  同期プリミティブ (ミューテックス、セマフォ、pico_syncのキューなど) を使用します。

このSMP版は(どちらかの) コア単独で実行することもできますが、その場合はFreeRTOS-Kernelの
mainブランチにある非SMP版を使った方がおそらく効率的なことに注意してください。

## このポートの使用法

[FreeRTOS_Kernel_import.cmake](FreeRTOS_Kernel_import.cmake)をプロジェクトにコピーして
`CMakeLists.txt`に以下を追加してください.

```cmake
include(FreeRTOS_Kernel_import.cmake)
```

これにより、FreeRTOSカーネルをプロジェクトにサブモジュールとして直接置いても、
環境変数 `FREERTOS_KERNEL_PATH`、または、CMakeコマンドラインの
`-DFREERTOS_KERNEL_PATH=/path/to/FreeRTOS-Kernel` で指定しても、その配置場所が
特定されます。

**注意:** Raspberry Pi Pico SDKのバージョン1.3.1以前を使用している場合、この行は
`pico_sdk_init()`より前に記述する必要があります。これによりプロジェクト内のすべての
RP2040ターゲットにFreeRTOSが含まれるようになります。これ以降のバージョンのSDKでは
CMakeビルドの後半（おそらくサブディレクト）でFreeRTOS-Kernelサポートを含めることが
でき、この場合は明示的にFreeRTOSサポートをインクルードしたターゲットにだけFreeRTOS-
Kernelのサポートが適用されます。

上記の`import`文の代わりに以下のように直接このディレクトリを追加することもできます
（上記のRaspberry Pi Pico SDKバージョンの制限と同じ配置制限があります）。

```cmake
add_subdirectory(path/to/this/directory FreeRTOS-Kernel)
```

## 高度な設定

いくつかの低レベルの実装の詳細を制御する追加の`config`オプションが
[`include/rp2040_config.h`](rp2040_config.h)定義されています。

## 既知の制限

- Tickless idleは現在のところテストされておらず、機能しないと思われます。
