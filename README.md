# ファイル暗号化・復号化 C++ アプリケーション

## 概要

このアプリケーションは、任意の秘密鍵（16・24・32バイト相当のHEX文字列）でファイルを暗号化・復号化するものです。  
暗号化・復号化処理には [Crypto++ ライブラリ](https://www.cryptopp.com/) の AES-CBC モードを使用しています。

---

## ファイル一覧

- `encrypt_file.cpp` : 任意鍵でファイルを暗号化するソースコード
- `decrypt_file.cpp` : 任意鍵でファイルを復号化するソースコード

---

## ビルド方法

Crypto++ ライブラリが必要です。（例: Ubuntuの場合）

```bash
sudo apt-get install libcrypto++-dev
```

ビルド例：

```bash
g++ encrypt_file.cpp -lcryptopp -o encrypt_file
g++ decrypt_file.cpp -lcryptopp -o decrypt_file
```

---

## 使い方

### 暗号化

```bash
./encrypt_file <元ファイル> <暗号化ファイル> <鍵HEX文字列>
```

例:
```bash
./encrypt_file plain.txt encrypted.txt 00112233445566778899aabbccddeeff
```

### 復号化

```bash
./decrypt_file <暗号化ファイル> <復号ファイル> <鍵HEX文字列>
```

例:
```bash
./decrypt_file encrypted.txt plain.txt 00112233445566778899aabbccddeeff
```

---

## 注意事項

- 鍵は16・24・32バイト（HEX文字列長で32・48・64文字）を利用してください。
- セキュリティの観点から、IVはゼロ埋めで固定しています。十分な安全性が必要な場合は毎回ランダムでIVを生成し、暗号化ファイルの先頭にIVを書き込んで、復号時に読み込むことを推奨します。
- ファイル処理エラーや鍵ミス時は標準エラー出力にメッセージが表示されます。

---

## ライセンス

MIT
