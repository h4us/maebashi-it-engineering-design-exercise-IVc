# serial2kbd

このアプリケーションはUSBシリアル接続経由で送られてくる任意のコマンドをキーボード入力に変換するものです。

- 修飾キーを含むキーボードの Press / Release 動作のエミュレーション。
- 特定の文字列のタイピングのエミュレーション。
- 基本的にUSキー配列のキーボードとして振る舞います。


## アプリケーションの開発とビルド

Chromium と Node.jsを利用したアプリケーションフレームワークである [Electron](https://www.electronjs.org/ja/) を使用しています。

本アプリケーションの仕様を変更したい場合は、PCに Node.js をインストールすることで、自身でビルドし直すすことが可能です。

### Node.jsのインストール

使用しているOSに応じた [Node.js](https://nodejs.org/ja) をPCにインストールしてください。

### アプリケーションの依存パッケージのインストール

Node.js をインストールした上で、使用しているOSに応じたコマンドラインインターフェース（WindowsであればWindows PowerShell やコマンド プロンプト、macOSであればターミナルなど）から下記のコマンドを実行します。

```bash
npm i
```

### 開発モードでのアプリケーションの起動

開発モードでコマンドラインインターフェースからアプリケーションを起動します。

```bash
npm run dev
```


### リリース用のビルド

スタンドアローンのアプリケーションとしてビルドします。

```bash
npm run dist
```


## キーボードやマウスのエミュレーションを行うライブラリ

デスクトップ自動化用ツールキットである [nut.js](https://github.com/nut-tree/nut.js) を使用しています。

必要に応じてインテーフェースを実装すれば、マウスのエミュレーションも行えます。詳しい仕様はドキュメントを参照してください。

