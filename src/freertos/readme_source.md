# `FreeRTOS/Source/README.md`

## はじめよう

このリポジトリにはFreeRTOSのカーネルソースとヘッダファイル、カーネルポートだけが
含まれています。このリポジトリは[FreeRTOS/FreeRTOS](https://github.com/FreeRTOS/FreeRTOS)
リポジトリのサブモジュールとして参照されています。FreeRTOSリポジトリには
```FreeRTOS/Demo``` ディレクトリに設定済みのデモアプリケーションプロジェクトが含まれています。

FreeRTOSを使う最も簡単な方法は設定済みのデモアプリケーションプロジェクトの1つを使って
始めることです。そうすれば、正しいFreeRTOSソースファイルが得られ、正しいインクルードパスが
設定されます。デモアプリケーションをビルドして実行したら、デモアプリケーションのファイルを
削除して、自身のアプリケーションのソースファイルの追加します。詳しい説明と有益なリンクが
[FreeRTOS Kernel Quick Start Guide](https://www.FreeRTOS.org/FreeRTOS-quick-start-guide.html)
にあります。

さらに、FreeRTOSカーネルの機能については[Developer Documentation](https://www.FreeRTOS.org/features.html)と
[API Reference](https://www.FreeRTOS.org/a00106.html)を参照してください。

また、コミュニティへの貢献とPull Requestの作成方法については
[ここ](https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/30f6061f48e2d54625d31e72ada6f5c474fba99f/.github/CONTRIBUTING.md)を参照してください。

### ヘルプ

FreeRTOSプロジェクトのトラブルシューティングについての質問やサポートが必要な場合は
[FreeRTOS Community Support Forum](https://forums.freertos.org)に活発なコミュニティが
あります。

## FreeRTOS-Kernelの利用法

### CMakeで利用

CMakeを使う場合は、FetchContentを使ってこのリポジトリを利用することを勧めます。
プロジェクトのメインまたはサブディレクトリの`CMakeLists.txt`に以下を追加して
ください。

- 使用したいソースとバージョン/タグを定義します。

```cmake
FetchContent_Declare( freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main #Note: Best practice to use specific git-hash or tagged version
)
```

gitサブモジュールとして追加したい場合は、次のようにします。

```bash
git submodule add https://github.com/FreeRTOS/FreeRTOS-Kernel.git <path of the submodule>
git submodule update --init
```

- freertos_config ライブラリの追加 (通常は INTERFACE ライブラリ) を追加します。
  次のディレクトリ構造を想定しています。
  - `include/FreeRTOSConfig.h`

```cmake
add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
INTERFACE
    include
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)
```

FreeRTOS-Kernelをサブモジュールとしてインストールした場合は、サブディレクトリと
して追加する必要があります。

```cmake
add_subdirectory(${FREERTOS_PATH})
```

- FreeRTOS-Kernelを構成して、利用可能にします。
  - 以下の例ではnativeとクロスコンパイルビルドオプションをサポートしています。

```cmake
set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
# Select the native compile PORT
set( FREERTOS_PORT "GCC_POSIX" CACHE STRING "" FORCE)
# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
  set(FREERTOS_PORT "GCC_ARM_CA9" CACHE STRING "" FORCE)
endif()

FetchContent_MakeAvailable(freertos_kernel)
```

- クロスコンパイルの場合は、以下も`freertos_config`に追加する必要があります。

```cmake
target_compile_definitions(freertos_config INTERFACE ${definitions})
target_compile_options(freertos_config INTERFACE ${options})
```

### スタンドアロンで使用する - 個のリポジトリをクローンする

HTTPSを使ってクローンするには

```
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
```

SSHをを使ってクローンするには

```
git clone git@github.com:FreeRTOS/FreeRTOS-Kernel.git
```

## リポジトリの構成

- このリポジトリのルートにはすべてのポートで共通の3つのファイル: list.c, queue.c,
  tasks.c が含まれています。カーネルはこれら3つのファイルに含まれています。
  croutine.cはオプションのコルーチン機能を実装しています。通常、これはメモリの
  制限が非常にきついシステムでだけ使用されます。
- ```./portable```ディレクトリには特定のマイクロコントローラーやコンパイラに固有の
  ファイルが含まれています。詳細については ```./portable``` ディレクトリのreadme
  ファイルを参照してください。
- ```./include``` ディレクトリにはリアルタイムカーネルヘッダファイルが含まれています。
- ```./template_configuration``` ディレクトリには新しいプロジェクトを始めるための
  FreeRTOSConfig.h のサンプルがあります。内容については
  [FreeRTOSConfig.h](examples/template_configuration/FreeRTOSConfig.h)ファイルを参照
  してください。

### Code Formatting

FreeRTOS files are formatted using the
"[uncrustify](https://github.com/uncrustify/uncrustify)" tool.
The configuration file used by uncrustify can be found in the
[FreeRTOS/CI-CD-GitHub-Actions's](https://github.com/FreeRTOS/CI-CD-Github-Actions)
[uncrustify.cfg](https://github.com/FreeRTOS/CI-CD-Github-Actions/tree/main/formatting)
file.

### Line Endings

File checked into the FreeRTOS-Kernel repository use unix-style LF line endings
for the best compatibility with git.

For optimal compatibility with Microsoft Windows tools, it is best to enable
the git autocrlf feature. You can enable this setting for the current
repository using the following command:

```
git config core.autocrlf true
```

### Git History Optimizations

Some commits in this repository perform large refactors which touch many lines
and lead to unwanted behavior when using the `git blame` command. You can
configure git to ignore the list of large refactor commits in this repository
with the following command:

```
git config blame.ignoreRevsFile .git-blame-ignore-revs
```

### Spelling and Formatting

We recommend using [Visual Studio Code](https://code.visualstudio.com),
commonly referred to as VSCode, when working on the FreeRTOS-Kernel.
The FreeRTOS-Kernel also uses [cSpell](https://cspell.org/) as part of its
spelling check. The config file for which can be found at [cspell.config.yaml](cspell.config.yaml)
There is additionally a
[cSpell plugin for VSCode](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker)
that can be used as well.
*[.cSpellWords.txt](.github/.cSpellWords.txt)* contains words that are not
traditionally found in an English dictionary. It is used by the spellchecker
to verify the various jargon, variable names, and other odd words used in the
FreeRTOS code base are correct. If your pull request fails to pass the spelling
and you believe this is a mistake, then add the word to
*[.cSpellWords.txt](.github/.cSpellWords.txt)*. When adding a word please
then sort the list, which can be done by running the bash command:
`sort -u .cSpellWords.txt -o .cSpellWords.txt`
Note that only the FreeRTOS-Kernel Source Files, [include](include),
[portable/MemMang](portable/MemMang), and [portable/Common](portable/Common)
files are checked for proper spelling, and formatting at this time.
