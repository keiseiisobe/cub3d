# cub3D

cub3d is inspired by [Wolfenstein](http://users.atw.hu/wolf3d/) by using ray-casting.

![](minecraft.png)

## Usage
```bash
make
./cub3D map.cub
```
## arguments
*.cub  <a map cosists of the following elements>

## OK functions
- open
- close
- read
- write
- printf
- malloc
- free
- perror
- strerror
- exit
- gettimeofday
- All functions of the math library (-lm man man 3 math)
- All functions of the MinilibX
- Libft functions

# TODO
- 描画関連
	- 壁は、向いてる方角に従って違うテクスチャ
		- XPMファイル？
	- 天井と床の色は、互いに違う二色
		- RGBで指定される
- window関連
	- [x] <- -> で視点移動
		- 現状は90度回転
		- 余裕があれば回転角度を小さくしたら面白い？
	- [x] W, A, S, D で移動
	- [ ] ESC でwindowを閉じて、プログラム終了(cleanly)
		- cleanかどうかのチェック必須
	- [ ] x でwindowを閉じて、プログラム終了(cleanly)
		- cleanかどうかのチェック必須
- nonマップ関連
	- [ ] 重複する情報がある場合はエラー
	- [ ] 必要な情報が足りない場合はエラー
	- [ ] 無駄な情報がある場合はエラー
- マップ関連
	- [ ] マップが壁で囲まれてるチェック
	- [x] 地図以外は、空行で区切れる　＝＞　空行を適切に無視する
	- [x] 地図は常に最後
	- [x] 地図以外の情報の順番にきまりはない
	- [x] 地図以外の情報は、スペースで区切れる
		- ft_splitで区切る
	- [x] 必要な情報が足りない
	- [x] 無駄な情報がある
	- [ ] 地図内のスペースは意味を持つ (地図全体の歪な形とか)
	- [ ] 地図のエラーの時は "Error\n ********" の出力
	- [ ] 一つだけのN, S, E, W がある
	- [ ] mapがデカすぎる場合はエラー
	- [ ] mapの名前が　[].cub　でない場合はエラー
	- [ ] mapの情報が最後に来る　＝＝　mapの後に何かがある場合はエラー
- 入力解釈一覧
	- non_map_info
		- 東西南北のテクスチャのPATH
		- 天井と床の色
		- map情報が来るまでは、空行を認めて無視する
			- 空行の定義　＝＝　'\n'のみの行
			- スペースは認めない
		- 全ての情報はスペースで区切られる
- 一旦無視してるTODO
	- [ ] テクスチャ指定のファイルがvalidかどうかのチェック
	- [ ] RGBの値がvalidかどうかのチェック
	- [ ] マップの形がvalidかどうかのチェック


# ===== devlogs =====
### 2024/06/20 kisobe
- To compile, change "# include "../mlx-mms/mlx.h" in include/cub3d.h to # include "../mlx-linux/mlx.h"" and remove libmlx.dylib.
### 2024/06/21 kisobe
- Implemented event hook(W, A, S, D, ->, <-)
- floor and ceiling color
- wall collisions
- added event.c and move.c

### 2024/06/25 kmiyazaw
- 日本語で失礼します
- ブランチを分けました。
- 分けたブランチの先で、ft_err_printfをprintfに置き換えました。

### 2024/06/29 kmiyazaw
- kmiyazaw_inputChecker ブランチを作成しました。
	- マップの入力チェックを行う関数を追加する予定です
- kmiyazaw_def ブランチを整理し、pull requestを出しました。

### 2024/06/30 kmiyazaw
- kmiyazaw_inputChecker ブランチで、入力.cubが正しかった場合の、情報抽出をする関数を追加しました。
- これにより、non_map情報を含むinputしか(現状)読めなくなった。
- non_map情報の過不足はエラーで弾けるようになった？　多分
- また、non_map情報の順番は関係ないようになった。
- non_mapの情報のsuffix?のチェックのみの追加なので、以下の項目は未着手です。
	- non_mapの情報のテクスチャの指定がvalidかどうかのチェック
	- non_mapの情報のRGBの値がvalidかどうかのチェック
	- mapの形がvalidかどうかのチェック
- mallocした変数＝後々freeする必要のある変数の命名規則の追加をしたいです。
	- 例： char **input_
		- 変数名の最後にアンダースコアをつける

### 2024/07/07 kmiyazaw
- mapのチェックを作る関数を作っています。
	- 壁で囲まれてるかどうかのチェックの方針 多分完成？
		1. map部分に対して、上下左右にpaddingした新たなmapを作る
		2. その新たなmapは、widthを揃えている。＝＝　スペースなどのcharで埋める
		3. padding-char この場合は、' ' の四方の隣が '1' or ' ' であることを確認する
		4. valid check
	- mapの文字の正しさチェック
		- 順番に見ていって、'0' or '1' or '.' および、N, S, E, W があるかどうかを確認する
		- それ以外ならエラー
		- N, S, E, W が２つ以上ある場合はエラー
- エラーの出力は、わかりやすさ優先でsubjectに乗っ取らないで書いてあるものばかりです。笑
- 多分、mapのチェックは完成？と思われます。
- [ ] なぜか、caps lockをhookしていて、caps lockを押すとexitします。

