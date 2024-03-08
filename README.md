# picoを使った工作のメモと資料翻訳

## RP2040

- [RP2040データシート](src/rp2040/README.md)
  - [第1章 はじめに](src/rp2040/chap1/README.md)
  - [第2章 システム説明](src/rp2040/chap2/README.md)
    - [2.14. サブシステムのリセット](src/rp2040/chap2/resets.md)
    - [2.15 クロック](src/rp2040/chap2/clock.md)
    - [2.18 PLL](src/rp2040/chap2/pll.md)
    - [2.19 GPIO](src/rp2040/chap2/gpio.md)
  - [第4章 ペリフェラル](src/rp2040/chap4/README.md)
    - [4.3 I<sup>2</sup>C](src/rp2040/chap4/i2c.md)
    - [4.4 SPI](src/rp2040/chap4/spi.md)

## SSD1331

- [SSD1331](src/ssd1331/README.md)
  - [SSD1331データシート](src/ssd1331/ssd1331.md)
  - [フォントについて](src/ssd1331/font.md)
  - [BMPファイル](src/ssd1331/bmp.md)

## BME280

- [データシート](src/bme280/datasheet.md)

## FreeRTOS

- [FreeRTOS](src/freertos/README.md)
  - [カーネル開発者向けドキュメント](src/freertos/dev_docs/README.md)
    - [イベントグループ（イベントフラグ）](src/freertos/dev_docs/event.md)
    - [FreeRTOSConfig.h](src/freertos/dev_docs/customisation.md)
    - [静的メモリと動的メモリ](src/freertos/dev_docs/memory_allocation.md)
    - [メモリ管理](src/freertos/dev_docs/memory_management.md)
    - [スタックオーバーフローを防ぐ](src/freertos/dev_docs/stack.md)
    - [新規プロジェクトの作成](src/freertos/dev_docs/create_project.md)
  - [Source/README](src/freertos/readme_source.md)
  - [Source/portal/RP2040/README](src/freertos/readme_portal_rp2040.md)
  - [Demo/CORTEX_M0+_RP2040/README](src/freertos/readme_demo_rp2040.md)

## メモ

- [Pico Wを使う](src/pico_w/memo.md)
- [debugprobeを使う](src/debugprobe/debugprobe.md)
- [trykernel](src/trykernel/memo.md)
- [FreeRTOS](src/freertos/memo.md)
