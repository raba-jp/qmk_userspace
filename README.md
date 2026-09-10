# QMK Userspace

QMK 本体のリポジトリとは別に、キーマップを定義・ビルドするためのテンプレートリポジトリです。QMK 本体をフォークせずに、自分のキーマップを管理できます。

## KeyPeek（Altair-X）

`stable` と `unstable` は、どちらも [KeyPeek のレイヤー通知モジュール](https://github.com/srwi/keypeek#setup)を組み込み、VIA と Raw HID を有効にしています。Altair-X の QMK 本体側の設定では、両キーマップに必要な6つの動的キーマップレイヤーを利用できます。Community Module API 1.1.0 以降に対応した QMK を使用してください。

1. `stable` 用の `sm_td` を含む各モジュールを初期化します。

   ```sh
   git submodule update --init --recursive
   ```

2. 使用するキーマップをビルドし、物理レイアウトを出力します。

   ```sh
   qmk compile -kb ai03/altair_x -km stable
   qmk info -kb ai03/altair_x -m -f json > keyboard_info.json
   ```

   必要に応じて `stable` を `unstable` に置き換えてください。mise を使う場合は、`mise run compile:stable` / `mise run compile:unstable` と `mise run keypeek:layout` を実行します。

3. 生成された `ai03_altair_x_stable.uf2`（または `ai03_altair_x_unstable.uf2`）を、基板の通常の RP2040 ブートローダー手順に従って左右両方に書き込みます。左右それぞれを個別に USB 接続して書き込んでください。

4. [KeyPeek のリリースページ](https://github.com/srwi/keypeek/releases/latest)から、Mac の CPU に合った macOS 用アーカイブをダウンロードします。展開した `KeyPeek.app` を「アプリケーション」に移動してください。キーボードを USB 接続した状態で起動し、Altair-X を選び、ファイルの選択を求められたら `keyboard_info.json` を指定します。

5. レイヤーキーを押したままにし、キーボードの状態に合わせてオーバーレイが変わることを確認します。`stable` の `sm_td` によるタップ／ホールド動作は C で実装されているため、KeyPeek は元のキーコードを読み取れますが、その独自動作は編集できません。`unstable` は QMK 標準の Mod-Tap と Layer-Tap キーコードを使用します。

VIA で編集したキーマップは EEPROM に保存されます。`keymap.c` を変更した場合や、`stable` と `unstable` を切り替えた場合は、保存済みの VIA キーマップ／EEPROM を初期化して、ビルド時の初期配列を読み込んでください。初期化すると KeyPeek や VIA で行った編集は失われます。

`stable` では、`sm_td` がキーイベントを処理する前に通知モジュールがイベントを確認できるよう、通知モジュールを先に登録しています。`sm_td` は Community Module のフックを自動で登録するため、`process_record_user()` から `process_smtd()` を重ねて呼び出さないでください。

## QMK 標準のホームロウ MOD の試用（`unstable`）

`unstable` は QMK の [Permissive Hold、Chordal Hold、Flow Tap](https://docs.qmk.fm/tap_hold)を使用します。比較用の `stable` には既存の `sm_td` 設定を残しています。`stable` のビルドには引き続き `sm_td` サブモジュールが必要です。

| 設定 | `unstable` の動作 |
| --- | --- |
| ホームロウ MOD（HRM） | タッピングタームは280ms。HRM を押したまま反対手のキーを押して離すと、修飾キーとして動作 |
| 同手入力 | Chordal Hold がタップを優先。同じ手の複数の HRM で、反対手のキーを修飾する操作は可能 |
| Flow Tap | 英字・主な句読点・Space・Minus の後、150ms以内の Mod-Tap 入力をタップに確定。Ctrl・GUI・左 Alt が有効な間は無効 |
| タップ後の長押しによる文字リピート | Quick Tap の判定時間は90ms |
| Space | タップで空白、180msの長押しで Symbols レイヤーを有効化。別キーを押した場合は即座にレイヤーを有効化。Flow Tap の対象外 |
| Hyper | Minus または K のホールドで、左 Ctrl＋Shift＋Alt＋GUI の4修飾キーを有効化 |

文字配列、専用 Shift キー、各レイヤーの内容、VIA、KeyPeek は引き続き利用できます。既存の左右判定マップでは、親指キーを左右どちらとも組み合わせられる位置（`'*'`）に指定しています。Space を押したまま次のキーを押すとレイヤー操作が優先されるため、通常の空白を入力するときは次のキーを押す前に Space を離してください。

QMK 標準のタップ／ホールド処理には、`sm_td` の解放タイミング補正はありません。タッピングターム内に相手キーより先に HRM を離すと、両キーの解放時刻が近くてもタップになります。ショートカットでは、相手キーを離すまで HRM を押したままにしてください。同手のショートカットは、HRM をタッピングタームより長く保持してから相手キーを押すか、反対手の HRM を使います。

`stable` に残している `SMTD_MT(..., KC_HYPR)` は、固定リビジョンのライブラリでは左 Ctrl として処理されます。`unstable` は `HYPR_T()` を使い、意図した Hyper の動作を実装しています。

`qmk compile -kb ai03/altair_x -km unstable`（または `mise run compile:unstable`）でビルドし、左右両方に書き込んでください。**新しい Mod-Tap／Layer-Tap の初期配列を読み込むには、保存済みの VIA キーマップ／EEPROM の初期化が必要です。** 保存済みの VIA／KeyPeek の編集は失われるため、変更内容を先に記録してください。`stable` に戻す場合も同じ初期化が必要です。

通常の文字入力（日本語 IME での入力を含む）、反対手のショートカット、複数の HRM、Space／Symbols、文字リピート、Hyper の動作を比較してください。判定時間と Flow Tap のコールバックは、`keyboards/ai03/altair_x/keymaps/unstable/config.h` と `keymap.c` にあります。

## ビルド対象の設定

1. 未実施の場合は、通常の `qmk setup` 手順を進めます。詳細は [QMK ドキュメント](https://docs.qmk.fm/#/newbs)を参照してください。
1. このリポジトリをフォークします。
1. フォークしたリポジトリをローカルマシンにクローンします。
1. `qmk config user.overlay_dir="$(realpath qmk_userspace)"` で QMK の userspace を有効にします。
1. `qmk new-keymap` で、使用するキーボードのキーマップを追加します。

   キーマップは、QMK 本体と同じディレクトリ構成で `keyboards` 配下に作成されます。例えば Planck なら、作成先は `keyboards/planck/keymaps/<your keymap name>` です。

   キーボードとキーマップ名を指定する場合は、`qmk new-keymap -kb <your_keyboard> -km <your_keymap>` を使用します。同じ場所に手動でファイルを置いても構いません。レイアウト共通の仕組みを使う場合は、`layouts/<layout name>/<your keymap name>/keymap.*` にも対応しています。

1. `qmk userspace-add -kb <your_keyboard> -km <your_keymap>` でビルド対象に追加します。

   `qmk.json` は自動で更新されます。ビルド対象から外す場合は `qmk userspace-remove -kb <your_keyboard> -km <your_keymap>`、対象の一覧を表示する場合は `qmk userspace-list` を使用します。

1. 変更をコミットします。

## GitHub でのビルド

1. GitHub の Actions タブでワークフローを有効にします。
1. 変更をフォーク先の GitHub リポジトリにプッシュします。
1. GitHub Actions で新しい実行が始まったことを確認します。
1. 実行が完了するまで待ちます。
1. リポジトリの Releases タブから、最新のファームウェアを確認します。

## ローカルでのビルド

1. 未実施の場合は、通常の `qmk setup` 手順を進めます。詳細は [QMK ドキュメント](https://docs.qmk.fm/#/newbs)を参照してください。
1. このリポジトリをフォークします。
1. フォークしたリポジトリをローカルマシンにクローンします。
1. `cd` でクローン先のディレクトリに移動します。
1. `qmk config user.overlay_dir="$(realpath .)"` で userspace のパスを設定します。**必ずクローンした userspace のディレクトリ内で実行してください。**

   userspace のリポジトリ内ではパスが自動検出されますが、この設定を行うと、別のディレクトリからでも userspace を利用できます。

1. `qmk compile -kb your_keyboard -km your_keymap` または `make your_keyboard:your_keymap` でビルドします。

前述の手順でビルド対象を設定済みなら、`qmk userspace-compile` ですべての対象をまとめてビルドできます。

## 補足

GitHub Actions のビルド設定を変更する場合は、`.github/workflows/build_binaries.yaml` を編集してください。

`build` ジョブで使用する QMK のリポジトリやブランチは、次のパラメーターで変更できます。

```yaml
    with:
      qmk_repo: qmk/qmk_firmware
      qmk_ref: master
```

userspace のリポジトリ内で `qmk_firmware` を Git 管理したい場合は、userspace ディレクトリにサブモジュールとして追加できます。サブモジュールがあれば、GitHub Actions は固定されたリビジョンを使用します。なければ、既定で QMK 本体の最新リビジョンを使用します。

この方法で、使用する QMK のフォークを指定することもできます。ただし、メーカー側のフォークでは、外部 userspace に対応する更新が取り込まれている必要があります。

1. 初回は `git submodule add https://github.com/qmk/qmk_firmware.git` で追加します。
1. 更新時は `git submodule update --init --recursive` を実行します。
1. 変更を userspace のリポジトリにコミットします。
