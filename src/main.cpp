#include "mto_common.h"
#include "mto_string.h"
#include "mto_dir.h"

#include <fstream>
#include <iomanip>

#ifdef __linux__
#include <unistd.h>
#define ISATTY(x) isatty(fileno(x))
#else
#include <io.h>
#define ISATTY(x) _isatty(_fileno(x))
#endif

// オプション情報
typedef struct tagOptionParam {
#if 0 
	int32_t 	padd;
#else
	int8_t opt_n;
	int8_t opt_h;
	int8_t opt_p0;
	int8_t opt_p1;
#endif
} OptionParam;

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
    printf("       -n : 行番号なし\n");
    printf("       -h : シンタックスハイライトなし\n");
	printf("       -? : ヘルプ出力\n");
	printf("\n");
}

/*========================================================
【機能】オプションの初期設定
=========================================================*/
static void _init_option(OptionParam *pOpt)
{
	if (pOpt == NULL)
		return;

	memcls(pOpt, sizeof(OptionParam));
}

/*========================================================
【機能】オプションの有無を調べる
=========================================================*/
static int _check_option(int argc, char *argv[], OptionParam *pOpt)
{
	int32_t opt = 1;

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
        case 'n':
            pOpt->opt_n = TRUE;
            break;
        case 'h':
            pOpt->opt_h = TRUE;
            break;
		case '?':
			_info_draw();
			return 0;

		default:
			printf("サポートされていない拡張子です\n");
			printf("『ncat -?』でヘルプ\n");
			return 0;
		}

		if (++opt >= argc) break;
	}

	if (opt > (argc - 1)) { // -1:入力
		printf("オプションの指定が不正です。\n");
		return 0;
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


static void output_line(const std::string &str, const uint32 line)
{
	std::cout << std::setw(5) << line << ": " << str << std::endl;
}

/*========================================================
【機能】テキスト出力ツール
=========================================================*/
int main(int argc, char *argv[])
{
	SET_CRTDBG();
	atexit(_release);

	uint32_t line = 1;
	std::string str;

	if (ISATTY(stdin)) {
		// オプションチェック
		int32_t opt_idx;
		OptionParam optParam;

		_init_option(&optParam);

		if (!(opt_idx = _check_option(argc, argv, &optParam))) {
			return 1;
		}

		std::ifstream fs;

		fs.open(argv[opt_idx], std::ios::in);
		if (!fs.is_open()) {
			std::cout << "ファイルが見つかりません: " << argv[opt_idx] << std::endl;
		}

		while (std::getline(fs, str)) {
			output_line(str, line++);
		}

		fs.close();
	} else {
		// パイプラインからの入力
		while (std::getline(std::cin, str)) {
			output_line(str, line++);
		}
	}

	return 0;
}
