# 静的メモリと動的メモリのアロケーション

## はじめに

FreeRTOSのV9.0.0より前のバージョンでは、以下のRTOSオブジェクトが使用する
メモリはFreeRTOSの特別なヒープから割り当てられます。FreeRTOSのV9.0.0以降では、
アプリケーションの作者がメモリを提供できるようになり、以下のオブジェクトを
動的にメモリを確保することなく作成できるようになりました。

- タスク
- ソフトウェアタイマー
- キュー
- イベントグループ
- バイナリセマフォ
- カウンティングセマフォ
- リカーシブセマフォ
- ミューテックス

静的メモリアロケーションと動的メモリアロケーションのどちらを使用するのが
望ましいかはアプリケーションやアプリケーションの作者の好みに依存します。
どちらの方法にも長所と短所があり、同一のRTOSアプリケーションにおいて両方の
方法を使用することができます。

FreeRTOSリポジトリのFreeRTOS/Source/WIN32-MSVC-Static-Allocation-Only
ディレクトリにある簡単なWin32サンプルは、プロジェクトにFreeRTOSヒープ実装を
含めずにFreeRTOSアプリケーションを作成する方法を示しています。

## 動的に割り当てられるRAMを使ったRTOSオブジェクトの作成

RTOSオブジェクトを動的に作成するとよりシンプルになるという利点があり、
アプリケーションの最大RAM使用量を最小にできる可能性があります：

- オブジェクトの作成時に必要な関数パラメータが少なくなります。
- メモリの割り当てはRTOS API関数内で自動的に行われます。
- アプリケーションの作者はメモリ割り当てを自分で行う必要がありません。
- RTOSオブジェクトに使用されたRAMはオブジェクトが削除された場合に
  再利用することができ、アプリケーションの最大RAMフットプリントを
  削減できる可能性があります。
- ヒープ使用に関する情報を返すRTOS API関数が提供されており、ヒープ
  サイズを最適化することができます。
- 使用されるメモリ割り当てスキームは次のようにアプリケーションに最適な
  ものを選択できます。単純性と安全性が重要なアプリケーションによく必要と
  される決定性のためのheap_1.c、断片化保護のためのheap_4.c、複数のRAM領域に
  わたってヒープを分割するheap_5.c、アプリケーションの作者自身が提供する
  割り当てスキームなど。

`configSUPPORT_DYNAMIC_ALLOCATION`に1を設定するか、未定義のままにしておくと、
使用できる次のAPI関数は動的に割り当てられたRAMを使用してRTOSオブジェクトを
作成します。

- xTaskCreate()
- xQueueCreate()
- xTimerCreate()
- xEventGroupCreate()
- xSemaphoreCreateBinary()
- xSemaphoreCreateCounting()
- xSemaphoreCreateMutex()
- xSemaphoreCreateRecursiveMutex()

##  静的に割り当てられるRAMを使ったRTOSオブジェクトの作成

静的に割り当てられたRAMを使ってRTOSオブジェクトを作成するとアプリケーションの
作者がより制御しやすくなるという利点があります。

- RTOSオブジェクトを特定のメモリ位置に配置できます。
- 最大RAMフットプリントを実行時ではなくリンク時に決定することができます。
- アプリケーションの作者はメモリの割り当てに失敗した場合の適切な処理を
  気にする必要がありません。
- 単純に動的なメモリ割り当てを許可しないアプリケーションでもRTOSを使用
  できるようになります（FreeRTOSにはほとんどの反対を克服できるような
  割り当てスキームが用意されてはいますが）。

`configSUPPORT_STATIC_ALLOCATION`に1を設定すると使用できる次のAPI関数は
アプリケーションの作者により提供されるメモリを使用してRTOSオブジェクトを
作成することができます。メモリを提供するためにアプリケーションの作者は
適切なオブジェクト型の変数を宣言し、その変数のアドレスをRTOS API関数に
渡すだけです。`StaticAllocation.c`にある標準的なデモ/テストタスクは
関数の使用法を示すために提供されています。

- xTaskCreateStatic()
- xQueueCreateStatic()
- xTimerCreateStatic()
- xEventGroupCreateStatic()
- xSemaphoreCreateBinaryStatic()
- xSemaphoreCreateCountingStatic()
- xSemaphoreCreateMutexStatic()
- xSemaphoreCreateRecursiveMutexStatic()
