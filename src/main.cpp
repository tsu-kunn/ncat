#include "mto_common.h"
#include "mto_string.h"
#include "mto_dir.h"


#ifdef __linux__
#include <unistd.h>
#define ISATTY(x) isatty(x)
#else
#include <io.h>
#define ISATTY(x)	_isatty(x)
#endif

/*========================================================
【機能】操作説明
=========================================================*/
static void _info_draw(void)
{
	printf("|||||||||||||||          ncat            ||||||||||||||||\n");
	printf("ncat.exe Version 0.01           (c)Tsuyoshi.A-2022/09/16-\n");
	printf("\n");
	printf("ncat [option] [in file] ...\n");
	printf("    [option]\n");
	printf("       -? : ヘルプ出力\n");
	printf("\n");
}

/*========================================================
【機能】オプションの有無を調べる
=========================================================*/
static int _check_option(int argc, char *argv[])
{
	int opt = 1;

	// 引数なし
	if (argc == 1) {
		_info_draw();
		return 0;
	}

	if (argc < 2) {
		printf("引数の指定が不正です。\n");
		return 0;
	}

	// オプションがある？
	while (argv[opt][0] == '-') {
		switch (argv[opt][1]) {
		case '?':
			_info_draw();
			return 0;

		default:
			printf("サポートされていない拡張子です\n");
			printf("『mkedat -?』でヘルプ\n");
			return 0;
		}

		if (++opt > 2) {
			printf("オプションの指定が不正です。\n");
			return 0;
		}
	}

	return opt;
}

/*========================================================
【機能】終了処理
=========================================================*/
static void _release(void)
{
}



	/*------------------------------------------------------------*/
	/*------------------------------------------------------------*/
	/*------------------------------------------------------------*/
	/*------------------------------------------------------------*/
	/*------------------------------------------------------------*/



/*========================================================
【機能】テキスト出力ツール
=========================================================*/
int main(int argc, char *argv[])
{
	SET_CRTDBG();

	int opt_idx;

	// パイプラインからの入力かの確認
	if (ISATTY(fileno(stdin))) {
		// オプションチェック
		if (!(opt_idx = _check_option(argc, argv))) {
			_release();
			return 1;
		}

		printf("stdin:terminal\n");
	} else {
		printf("stdin:pipe\n");
	}

	// 終了
	_release();

	return 0;
}
