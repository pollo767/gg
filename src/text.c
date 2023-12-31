//
// Created by laqieer on 2019/12/12.
//

// help debug: http://freaka.freehostia.com/charset_js.html

/* Notice: These Kanjis need "\" following it.
 * ?ソЫ?噂浬欺圭構蚕十申曾箪貼能表暴予禄兔喀媾彌拿杤歃濬畚秉綵臀藹觸軆鐔饅鷭??
 * That is gcc's bug:
 * http://www2d.biglobe.ne.jp/~gama/cgi/jcode/jcode.htm
 * https://gcc.gnu.org/projects/cpplib.html
 * https://www.novell.com/ja-jp/support/kb/tids/jp/00006500_/00006574.htm
 * https://unofficialnextion.com/t/shift-jis-encoding-escape-characters/262
 * */

#include <stdbool.h>
#include <stddef.h>

#include "text.h"
#include "text_id.h"
#include "portrait_id.h"
#include "skill.h"
#include "gba_debug_print.h"

// Add game text here
const char* const texts[] = {
        // Tutorial Lyn's character description
        //[0x01B4] = "キアラン公女、本名はリンディス。草原で一人、生きてきた過去を持つ、気丈でさっぱりとした性格。",

        // Summoner's default name
        [0x569] = "エクラ", // seems useless?
        [0x79D] = "エクラ", // default name for profile setting

        // Guide for profile setting
        [0x79E] = //"あなたはエレブ大陸を旅する" TCC_NEWLINE
                    //"見習いの軍師です。" TCC_PUSH_A TCC_NEWLINE2
                    "歴戦の英雄たちの" TCC_NEWLINE
                    "力を借り得る「召喚師」として" TCC_PUSH_A TCC_NEWLINE
                    "特別な力を持つあなたは、" TCC_NEWLINE
                    "滅亡の危機にひんする" TCC_PUSH_A TCC_NEWLINE
                    "アスク王国を救うため、" TCC_NEWLINE
                    "特務機関「ヴァイス・ブレイヴ」" TCC_PUSH_A TCC_NEWLINE
                    "の一員となり、" TCC_NEWLINE
                    "果てない戦いに挑みます。"  TCC_PUSH_A TCC_NEWLINE
                    "ちなみにマイ召喚師は２４４章後の" TCC_NEWLINE
                    "破章から参戦してきます。" TCC_PUSH_A TCC_NEWLINE
                    "最初に"TCC_TOGGLE_RED"名前"TCC_TOGGLE_RED"と" TCC_NEWLINE
                    TCC_TOGGLE_RED"血液型"TCC_TOGGLE_RED"、"TCC_TOGGLE_RED"生まれ月"TCC_TOGGLE_RED"、"TCC_TOGGLE_RED"性別"TCC_TOGGLE_RED TCC_NEWLINE
                    "を設定することができます。" TCC_PUSH_A TCC_NEWLINE2
                    "十\字ボタンとＡボタンを使って" TCC_NEWLINE
                    "項目ごとに設定してください。" TCC_PUSH_A TCC_NEWLINE2
                    "入力が面倒な方は、" TCC_NEWLINE
                    "「いいえ」を選んでください。" TCC_PUSH_A TCC_NEWLINE
                    "デフォルトの設定で" TCC_NEWLINE
                    "ゲームがスタートします。" TCC_PUSH_A TCC_NEWLINE,

        // Tactician -> Summoner
        /*
        [0x305] = "軍師"TCC_TACTICIAN_NAME"が記した書物" TCC_NEWLINE
                    "持っていると戦いが有利になります",
        [0x30F] = "軍師"TCC_TACTICIAN_NAME"の剣",
        [0x310] = "軍師"TCC_TACTICIAN_NAME"の槍",
        [0x311] = "軍師"TCC_TACTICIAN_NAME"の斧",
        [0x312] = "軍師"TCC_TACTICIAN_NAME"の斧",
        [0x380] = "軍師自身のことを" TCC_NEWLINE
                    "占ってくれます",
        [0x3E4] = "軍師の名前です",
        [0x3E5] = "軍師の血液型です",
        [0x3E6] = "軍師の生まれた月です",
        [0x3E7] = "軍師の性別です",
        [0x552] = "軍師",
        [0x7A0] = "軍師の設定は" TCC_NEWLINE
                    "これでよろしいですか？" TCC_NEWLINE
                    TCC_YES,
        [0x7A1] = "軍師を参加させますか？" TCC_NEWLINE2
                    TCC_YES,
        */
        [0x305] = "召喚師"TCC_SUMMONER_NAME"が記した書物" TCC_NEWLINE
                    "持っていると戦いが有利になります",
        [0x30F] = "召喚師"TCC_SUMMONER_NAME"の剣",
        [0x310] = "召喚師"TCC_SUMMONER_NAME"の槍",
        [0x311] = "召喚師"TCC_SUMMONER_NAME"の斧",
        [0x312] = "召喚師"TCC_SUMMONER_NAME"の弓",
        [0x380] = "召喚師自身のことを" TCC_NEWLINE
                    "占ってくれます",
        [0x3E4] = "召喚師の名前です",
        [0x3E5] = "召喚師の血液型です",
        [0x3E6] = "召喚師の生まれた月です",
        [0x3E7] = "召喚師の性別です",
        [0x552] = "召喚師",
        [0x7A0] = "召喚師の設定は" TCC_NEWLINE
                    "これでよろしいですか？" TCC_NEWLINE
                    TCC_YES,
        [0x7A1] = "召喚師を参加させますか？" TCC_NEWLINE2
                    TCC_YES,

        // MyUnit(Summoner) related
        //[TEXT_CHARACTER_NAME_MYUNIT] = TCC_SUMMONER_NAME,
        [TEXT_CHARACTER_NAME_MYUNIT] = gTacticianName,
        [TEXT_CHARACTER_HELP_MYUNIT] = "異世界から召喚された、あなた。伝説では、世界を救う救世主と伝えられている。",
        [TEXT_JOB_NAME_SUMMONER] = "しょうかん師",
        [TEXT_JOB_HELP_SUMMONER] = "異界から英雄たちを召喚できる召喚師",

        [0x36C] = "持ち物を輸送隊で整理します",

        // 重歩兵系→重甲系

        /*
        [0x284] = "騎馬系・重歩兵系に有効",
        [0x285] = "騎馬系・重歩兵系に有効",
        [0x2AD] = "騎馬系・重歩兵系に有効",
        [0x28A] = "重歩兵系に有効な剣",
        [0x29E] = "重歩兵系に有効な槍",
        [0x2A7] = "重歩兵系に有効な斧",
        */
        [0x284] = "騎馬系・重甲系に有効",
        [0x285] = "騎馬系・重甲系に有効",
        [0x2AD] = "騎馬系・重甲系に有効",
        [0x28A] = "重甲系に有効な剣",
        [0x29E] = "重甲系に有効な槍",
        [0x2A7] = "重甲系に有効な斧",

        // character GenericSoldierEmblianSuperWeak name
        [0x557] = "エンブラ兵",

        // character GenericSoldierEmblianSuperWeak description
        [0x221] = "エンブラ帝国の兵士",

        [TEXT_CHARACTER_NAME_GENERIC_FLAME] = "ムスペル兵",

        [TEXT_CHARACTER_HELP_GENERIC_FLAME] = "ムスペル帝国の兵士",

        // GenericSoldierSummoned name
        [1377] = "異界の英雄",

        // GenericSoldierSummoned description
        [555] = "異界から召喚されて契約を結んだ英雄",

        // character Alfonse name
        [0x4E4] = "アルフォンス",

        // character Alfonse description
        [0x1B2] = "アスク王国の王子。優しく真面目な性格。特務機関の一員として、国の平和を守っている。",

        // character Alfonse death quote
        [TEXT_DEATH_QUOTE_ALFONSE] = TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ALFONSE
                "僕の、負け。。。" TCC_NEWLINE
                "か。。。" TCC_PUSH_A,

        // character Anna name
        [0x4E5] = "アンナ",

        // character Anna description
        [0x1B3] = "特務機関の隊長。アルフォンスたちの上官。経験豊富な頼れる人物。",

        // character Anna death quote
        [TEXT_DEATH_QUOTE_ANNA] = TCC_OPEN_RIGHT
                                  TCC_LOAD_FACE PORTRAIT_ANNA
                                  "撤退。。。" TCC_NEWLINE
                                  "するわ。。。" TCC_PUSH_A,

        // character Sharena name
        [1254] = "シャロン",

        // character Sharena description
        [436] = "アスク王国の王女。アルフォンスの妹。明るく人懐っこい性格で、英雄とも仲が良い。",

        // character Sharena death quote
        [TEXT_DEATH_QUOTE_SHARENA] = TCC_OPEN_FAR_RIGHT
                  TCC_LOAD_FACE PORTRAIT_SHARENA
                  "失敗。。。" TCC_NEWLINE
                  "しちゃいました。。。" TCC_PUSH_A,

        // character Bruno name
        [1323] = "ブルーノ",

        // character Bruno description
        [522] = "仮面の騎士。その素性も目的も不明。",

         // character Bruno death quote
         [TEXT_DEATH_QUOTE_BRUNO] = TCC_OPEN_FAR_RIGHT
                TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
                    "グアアアア" TCC_PUSH_A,

        // character Veronica name
        [1335] = "ヴェロニカ",

        // character Veronica description
        [529] = "エンブラ帝国の皇女。英雄たちを使い、アスク王国へと侵攻する。",

        // Veronica job name
        [TEXT_JOB_NAME_VERONICA_PRINCESS] = "死の皇女",

        // Veronica job description
        [TEXT_JOB_HELP_VERONICA_PRINCESS] = "エンブラ帝国皇女",

        // character Veronica death quote
        [TEXT_DEATH_QUOTE_VERONICA] = TCC_OPEN_FAR_RIGHT
                TCC_LOAD_FACE PORTRAIT_VERONICA
                "つま。。。ないの。。。" TCC_PUSH_A,

        // character Xander name
        [1334] = "マークス",

        // character Xander description
        [528] = "暗夜王国の王子。神器「ジークフリート」の使い手。騎士道を重んじており、兵からの人望も厚い。",

        [TEXT_DEATH_QUOTE_XANDER] = TCC_OPEN_FAR_RIGHT
            TCC_LOAD_FACE PORTRAIT_XANDER
            "私は。。。" TCC_NEWLINE
            "ここまでだ。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_FJORM] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_FJORM
               "すみませ。。。ん。。。" TCC_NEWLINE
               "ご迷惑を。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_EIR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_EIR
               "死ぬのね。。。" TCC_NEWLINE
               "私。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_PEONY] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_PEONY
               "すごく。。。" TCC_NEWLINE
               "ねむいの。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_YURG] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_YLGR
               "あーあ。。。" TCC_NEWLINE
               "ざんねん。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_HELL] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_HEL
               "私は。。。" TCC_NEWLINE
               "死なぬのか。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_GUNNTHRA] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_GUNNTHRA
               "ごめんなさい。。。" TCC_NEWLINE
               "フィヨルム。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_HELBINDI] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_HELBINDI
               "。。。ゴミみてえな。。。" TCC_NEWLINE
               "最期だ。。。な。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_HRID] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_HRID
               "すまない。。。" TCC_NEWLINE
               "フィヨルム。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_LAEGJARN] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_LAEGJARN
               "レーヴァテイン。。。" TCC_NEWLINE
               "あなたは。。。どうか。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_LAEVATEIN] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_LAEVATEIN
               "もう。。。" TCC_NEWLINE
               "戦えない。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_LIF] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_LIF
               "死ぬことは。。。" TCC_NEWLINE
               "許されない。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_LOKI] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_LOKI
               "もう。。。" TCC_NEWLINE
               "だめ。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_GUSTAF] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_GUSTAV
               "アルフォンス。。。" TCC_NEWLINE
               "許せ。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_SURTR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_SURTR
               "馬。。。鹿なぁっ。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_SRASIR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_THRASIR
               "私は。。。" TCC_NEWLINE
               "死ねないの。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_MIRABILIS] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_MIRABILIS
               "ふかふかのベッドで。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_SCABIOSA] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_TRIANDRA
               "眠りに。。。" TCC_NEWLINE
               "つくのね。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_PLUMERIA] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_PLUMERIA
               "私になにを。。。" TCC_NEWLINE
               "するつもりです。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_FREYA] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_FREYJA
               "ああ。。。" TCC_NEWLINE
               "お兄様。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_HOOD] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_HOOD
               "。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_AVATAR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_AVATAR
               "。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_FREYR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_FREYR
               "戯れが。。。" TCC_NEWLINE
               "すぎたか。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_TAKUMI] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_TAKUMI
               "お前。。。" TCC_NEWLINE
               "なんかに。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_TOR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_TOR
               "。。。見事" TCC_NEWLINE
               "。。。だ。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_REGHIN] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_REGHIN
               "私。。。" TCC_NEWLINE
               "やっぱりダメなの。。。？" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_LETIZIA] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_LETIZIA
               "この恨み。。。" TCC_NEWLINE
               "かなら。。。ず。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_OTR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_OTR
               "嫌だ。。。" TCC_NEWLINE
               "兄さん。。。！" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_FAFNIR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_FAFNIR
               "。。。俺は。。。" TCC_NEWLINE
               "誰だ。。。？" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_FAFNIR2] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_FAFNIR2
               "アァ。。。" TCC_NEWLINE
               "ア。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_EITRI] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_EITRI
               "困ったな。。。" TCC_NEWLINE
               "私は。。。まだ。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_DAGR] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_DAGR
               "うっそ。。。" TCC_NEWLINE
               "マジで。。。？" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_NOTT] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_NOTT
               "負けましたわ。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_ASH] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_ASH
               "ふがいない最期で。。。" TCC_NEWLINE
               "ありました。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_VERONICA_STAIN] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_VERONICA_STAIN
               "エンブラ様。。。" TCC_NEWLINE
               "お許しください。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_DEATH_QUOTE_ELM] = TCC_OPEN_FAR_RIGHT
               TCC_LOAD_FACE PORTRAIT_ELM
               "エンブラ様。。。" TCC_NEWLINE
               "お許しください。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE,

        [TEXT_CHARACTER_NAME_LOKI] = "ロキ",

        [TEXT_CHARACTER_HELP_LOKI] = "炎の王国ムスペルの軍師。悪戯好きで、人を誘惑することを好む。",

        [TEXT_CHARACTER_NAME_FJORM] = "フィヨルム",

        [TEXT_CHARACTER_HELP_FJORM] = "氷の王国ニフルの第二王女。心優しい少女。仇敵スルトに対しては強い復讐心を抱く。",

        [TEXT_CHARACTER_NAME_SURTR] = "スルト",

        [TEXT_CHARACTER_HELP_SURTR] = "炎の王国ムスペルの王。炎竜の血を引く。苛烈な性格で、征服欲が極めて強い。",

        [TEXT_CHARACTER_NAME_LAEVATEIN] = "レーヴァテイン",

        [TEXT_CHARACTER_HELP_LAEVATEIN] = "炎の王国ムスペルの第二王女。みずからを剣と称し、自身の感情に乏しい。",

        [TEXT_CHARACTER_NAME_LAEGJARN] = "レーギャルン",

        [TEXT_CHARACTER_HELP_LAEGJARN] = "炎の王国ムスペルの第一王女。レーヴァテインの姉。ムスペル軍を率いる品性高潔な将軍。",

        [TEXT_CHARACTER_NAME_EIR] = "エイル",

        [TEXT_CHARACTER_HELP_EIR] = "死の王国ヘルの王女。母であるヘルを愛する反面、人間に対する母の無慈悲な行為に、胸を痛めている。",

        [TEXT_CHARACTER_NAME_GUNNTHRA] = "スリーズ",

        [TEXT_CHARACTER_HELP_GUNNTHRA] = "氷の王国ニフルの第一王女。おっとりとして母性あふれる性格。",

        [TEXT_CHARACTER_NAME_LIF] = "リーヴ",

        [TEXT_CHARACTER_HELP_LIF] = "死の王国ヘルの将。女王ヘルの命令を受け、生者を死者とするために戦う魔剣士。",

        [TEXT_CHARACTER_NAME_HELL] = "ヘル",

        [TEXT_CHARACTER_HELP_HELL] = "死の王国ヘルの王。人の死によって己の力を増す。すべての生者を死者とすることが望み。",

        [TEXT_CHARACTER_NAME_GUSTAF] = "グスタフ",

        [TEXT_CHARACTER_HELP_GUSTAF] = "死の王国ヘルの将。女王ヘルに呪縛され、生者を死者とするために戦う騎士。",

        [TEXT_CHARACTER_NAME_YURG] = "ユルグ",

        [TEXT_CHARACTER_HELP_YURG] = "氷の王国ニフルの第三王女。天真らんまん。好奇心おうせいで、色々な場所を見るのが好き。",

        [TEXT_CHARACTER_NAME_HELBINDI] = "ヘルビンディ",

        [TEXT_CHARACTER_HELP_HELBINDI] = "炎の王国ムスペルの将。最下層の貧民街の生まれ。みずからの武勇で成り上がりを望む粗暴\な将。",

        [TEXT_CHARACTER_NAME_HRID] = "フリーズ",

        [TEXT_CHARACTER_HELP_HRID] = "氷の王国ニフルの第一王子。冷静な性格で、常にあらゆる危険に思いを巡らせる。",

        [TEXT_CHARACTER_NAME_SRASIR] = "スラシル",

        [TEXT_CHARACTER_HELP_SRASIR] = "死の王国ヘルの将。女王ヘルの命令を受け、生者を死者とするために戦う魔女。",

        [TEXT_CHARACTER_NAME_PEONY] = "ピアニー",

        [TEXT_CHARACTER_HELP_PEONY] = "夢の国アルフの妖精。人に幸せな夢を見せる。純真で前向き、子供と遊ぶのが大好き。",

        [TEXT_CHARACTER_NAME_SCABIOSA] = "スカビオサ",

        [TEXT_CHARACTER_HELP_SCABIOSA] = "悪夢の国スヴァルトアルフの妖精。人に悪夢を見せる。無感動で後ろ向き、未来に希望を持たない。",

        [TEXT_CHARACTER_NAME_PLUMERIA] = "プルメリア",

        [TEXT_CHARACTER_HELP_PLUMERIA] = "悪夢の国スヴァルトアルフの妖精。みだらな夢を見せる。潔癖な性格で、人間が抱く欲望を嫌っている。",

        [TEXT_CHARACTER_NAME_MIRABILIS] = "ルピナス",

        [TEXT_CHARACTER_HELP_MIRABILIS] = "夢の国アルフの妖精。人に白昼夢を見せる。昼でも夜でも眠るのが好きで、いつも寝ぼけている。",

        [TEXT_ITEM_NAME_LEIPTR] = "レイプト",

        [TEXT_ITEM_HELP_LEIPTR] = "「フィヨルム専用」ニフルの神器",

        [TEXT_ITEM_NAME_HARDY_BEARING] = "不動の姿勢",

        [TEXT_ITEM_HELP_HARDY_BEARING] = "自身と敵の戦闘順入替スキル（待ち伏せ、攻め立て等）無効",

        [TEXT_CHAP_255_TITLE] = "NO DATA",

        [TEXT_CHARACTER_NAME_HOOD] = "？？？",

        [TEXT_CHARACTER_HELP_HOOD] = "？？？",

        [TEXT_ITEM_NAME_GRANIS_SHIELD] = "グラニの盾",

        [TEXT_ITEM_HELP_GRANIS_SHIELD] = "騎馬特効無効",

        [TEXT_JOB_NAME_GREAT_KNIGHT] = "スチームナイト",

        [TEXT_JOB_HELP_GREAT_KNIGHT] = "高い守備力と機動力を誇る魔道かがく騎兵。移動力に優れる。攻撃した後、再移動できる。装備「剣・槍・斧」",

        [TEXT_CHARACTER_NAME_REGHIN] = "レギン",

        [TEXT_CHARACTER_HELP_REGHIN] = "ニザヴェリル王ファフニールの義理の妹。ひょうへんした兄を止めるためアスク王国に協力する。",

        [TEXT_CHARACTER_NAME_GENERIC_NIOAVELLIR] = "ニザヴェリル兵",

        [TEXT_CHARACTER_HELP_GENERIC_NIOAVELLIR] = "小人族の国ニザヴェリルの兵士",

        [TEXT_CHARACTER_NAME_EITRI] = "エイトリ",

        [TEXT_CHARACTER_HELP_EITRI] = "ニザヴェリル王国の学者。幼いながらその優れた頭脳で賢者と呼ばれている。",

        [TEXT_JOB_NAME_YOUTHFUL_SAGE] = "幼き賢者",

        [TEXT_JOB_HELP_YOUTHFUL_SAGE] = "幼いながら知を究めた魔道士"TCC_NEWLINE"あらゆる魔法と杖を知る",

        [TEXT_JOB_NAME_BAT] = "バット",

        [TEXT_JOB_HELP_BAT] = "飛行するコウモリ。"TCC_NEWLINE"山や河にも移動できるが、弓に弱い。",

        [TEXT_CHARACTER_NAME_ELM] = "エルム",

        [TEXT_CHARACTER_HELP_ELM] = "閉ざす神エンブラのしもべであるけんぞく。冷酷な性格で、ちょくせつでトゲのある言葉を使う。",

        [TEXT_JOB_NAME_COW] = "カウガール",

        [TEXT_JOB_HELP_COW] = "ウシ娘。"TCC_NEWLINE"聖なる光魔法を使える。",

        [TEXT_CHARACTER_NAME_ASH] = "アシュ",

        [TEXT_CHARACTER_HELP_ASH] = "開く神アスクのしもべであるけんぞく。真面目な性格で、丁寧で回りくどい言葉を使う。",

        // Chapter event dialogue

                    // Chapter prologue opening
        [TEXT_CHAP_PRE_OP] = TCC_OPEN_MID_RIGHT
                   TCC_LOAD_FACE PORTRAIT_ALFONSE
                "アンナ隊長！" TCC_NEWLINE
                "無事で良かった。" TCC_NEWLINE TCC_PUSH_A
                "。。。？その人は。。。" TCC_NEWLINE TCC_PUSH_A
                "まさか！" TCC_PUSH_A
                   TCC_OPEN_LEFT
                   TCC_LOAD_FACE PORTRAIT_ANNA
                   "ええ。" TCC_NEWLINE
                   "例の儀式を試したら現れたの。" TCC_NEWLINE
                   TCC_TACTICIAN_NAME "というのよ。" TCC_NEWLINE TCC_PUSH_A
                   "古の伝承通り。。。" TCC_NEWLINE
                   "神器ブレイザブリクを撃ち放つ、" TCC_NEWLINE
                   "英雄を召喚する力を持つわ。" TCC_NEWLINE TCC_PUSH_A
                   TCC_OPEN_MID_RIGHT
                   "初めまして" TCC_TACTICIAN_NAME "。" TCC_NEWLINE
                   "君は異界の大英雄か。" TCC_NEWLINE
                   "お目にかかれて光栄だよ。" TCC_NEWLINE TCC_PUSH_A
                   "僕はアルフォンス。" TCC_NEWLINE
                   "特務機関の一員。。。" TCC_NEWLINE
                   "そして、このアスク王国の王子だ。" TCC_NEWLINE TCC_PUSH_A
                   "早速で悪いけれど、" TCC_NEWLINE
                   "君の力を貸してくれるかい？" TCC_NEWLINE TCC_PUSH_A
                   "先ほど、エンブラ兵が" TCC_NEWLINE
                   "「紋章の異界」を支配した。" TCC_NEWLINE
                   "彼らと戦って、異界の地を解放しよう。" TCC_NEWLINE TCC_PUSH_A
                   "そうだ、アンナ隊長。" TCC_NEWLINE
                   "先程。。。謎の人物を見かけたんだ。" TCC_NEWLINE
                   "この地の英雄ではないようだったけれど。" TCC_PUSH_A
                   TCC_OPEN_LEFT
                   "謎の人物。。。？" TCC_NEWLINE
                   "それも、エンブラの人間あの？" TCC_PUSH_A
                   TCC_OPEN_MID_RIGHT
                   "分からない。" TCC_NEWLINE
                   "見たことのない、仮面の男だった。" TCC_NEWLINE TCC_PUSH_A
                   "でもまずは。。。" TCC_NEWLINE
                   "目の前の敵を倒そう！" TCC_PUSH_A
                   TCC_END,

                   // Chapter prologue ending
        [TEXT_CHAP_PRE_ED] = TCC_OPEN_MID_RIGHT
                   TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
                   "。。。。。。。。。。。。" TCC_PUSH_A
                   TCC_OPEN_MID_LEFT
                   TCC_LOAD_FACE PORTRAIT_ANNA
                   "！！" TCC_NEWLINE
                   "あなたが、アルフォンスが見たって言う" TCC_NEWLINE
                   "仮面の男。。。？" TCC_PUSH_A
                   TCC_OPEN_LEFT
                   TCC_LOAD_FACE PORTRAIT_ALFONSE
                   "お前もエンブラ兵なのか？" TCC_NEWLINE
                   "だとしたら、容赦はしない。" TCC_NEWLINE
                   "英雄の地を支配するなど許されない！" TCC_PUSH_A
                   TCC_OPEN_MID_RIGHT
                   "。。。ならば大切に、" TCC_NEWLINE
                   "「扉」を閉めておくんだな。" TCC_PUSH_A
                   TCC_CLEAR_FACE
                   TCC_OPEN_LEFT
                   TCC_MOVE_TO_MID_RIGHT
                   "なに！？" TCC_NEWLINE
                   "くっ。。。逃げられてしまったか。" TCC_PUSH_A
                   TCC_OPEN_MID_LEFT
                   TCC_LOAD_FACE PORTRAIT_ANNA
                   "「扉」というのはね、" TCC_NEWLINE
                   "異界とこの世界を繋ぐものよ。" TCC_NEWLINE
                   "アスクの王族は「扉を開く力」を持つの。" TCC_PUSH_A
                   TCC_OPEN_MID_RIGHT
                   "そしてエンブラ帝国の皇族は" TCC_NEWLINE
                   "「扉を閉める力」を持っている。。。" TCC_NEWLINE
                   "両国の力は二つで一つだ。" TCC_NEWLINE TCC_PUSH_A
                   "それなのに奴等はいつしか" TCC_NEWLINE
                   "扉を閉めることを拒否し、" TCC_NEWLINE
                   "異界へと攻め込むようになってしまった。" TCC_PUSH_A
                   TCC_OPEN_MID_LEFT
                   "それを食い止める為に結成されたのが" TCC_NEWLINE
                   "私たち特務機関ってわけ。" TCC_NEWLINE TCC_PUSH_A
                   "さ、次の戦場へ急ぐわよ。" TCC_NEWLINE
                   "偵察に行っているシャロンが心配だわ。" TCC_PUSH_A
                   TCC_END,

                   // Chapter goal text

                   [TEXT_CHAP_GOAL_DEFEAT_ALL] = "目的：敵全滅",
                   [TEXT_CHAP_STATUS_GOAL_DEFEAT_ALL] = "敵部隊の全滅",
                   [TEXT_CHAP_GOAL_SEIZE] = "目的：制圧",
                   [TEXT_CHAP_STATUS_GOAL_SEIZE] = "目的地を制圧",
                   [TEXT_CHAP_GOAL_DEFEAT_BOSS] = "目的：ボス撃破",

                   // Chapter title
                   [TEXT_CHAP_PRE_TITLE] = "至天の世界",
                   [TEXT_CHAP_1_TITLE] = "奴が力を示せ",

                   // Chapter 1 opening part 1
                   [TEXT_CHAP_1_OP_1] = TCC_OPEN_MID_LEFT
                           TCC_LOAD_FACE PORTRAIT_SHARENA
                           "アンナ隊長、お兄様！" TCC_NEWLINE
                           "来るのが遅いですよーっ！" TCC_PUSH_A
                           TCC_OPEN_RIGHT
                           TCC_LOAD_FACE PORTRAIT_ALFONSE
                           "すまない、シャロン。" TCC_NEWLINE
                           "ここに来るまでに戦闘があってね。" TCC_PUSH_A
                           TCC_OPEN_MID_LEFT
                           "んん？そのお隣にいる方は。。。" TCC_NEWLINE
                           "その手にさんぜんと輝く神器は。。。" TCC_NEWLINE TCC_PUSH_A
                           "もしやあなたが、異界の大英雄様！？" TCC_NEWLINE
                           "機関全員で夢にまで見た、" TCC_NEWLINE
                           //"噂の救世主ですかーーっ！？" TCC_PUSH_A
                           // somehow kanji 噂 will miss 0x5c here
                           "\x89\x5Cの救世主ですかーーっ！？" TCC_PUSH_A
                           TCC_OPEN_RIGHT
                           "ああ。名は"TCC_TACTICIAN_NAME"だ。" TCC_NEWLINE
                           "先程も見事な指揮で、" TCC_NEWLINE
                           "僕たちに力を貸してくれた。" TCC_PUSH_A
                           TCC_OPEN_MID_LEFT
                           "すごーーい！すごいです！！" TCC_NEWLINE
                           "さすが"TCC_TACTICIAN_NAME"さん！" TCC_NEWLINE
                           "百年前からファンでしたっ！！" TCC_NEWLINE TCC_PUSH_A
                           //"あ、申し遅れました！私、シャロンです！" TCC_NEWLINE
                           "あ、\x90\x5Cし遅れました！私、シャロンです！" TCC_NEWLINE
                           "アスク王国の王女で、" TCC_NEWLINE
                           "アルフォンスお兄様の妹なんですよ。"TCC_PUSH_A
                           TCC_OPEN_RIGHT
                           "それでシャロン、戦況は？" TCC_PUSH_A
                           TCC_OPEN_MID_LEFT
                           "一言で言うとまずいですね。" TCC_NEWLINE
                           "エンブラ軍の奴ら、" TCC_NEWLINE
                           "空飛ぶ赤い英雄を従えたんです。" TCC_PUSH_A
                           TCC_OPEN_RIGHT
                           "紋章の異界にいる、" TCC_NEWLINE
                           "赤色の飛兵。。。" TCC_NEWLINE
                           "もしやミネルバ王女か？" TCC_NEWLINE TCC_PUSH_A
                           "苦戦を強いられるかもしれないが、" TCC_NEWLINE
                           "弓兵の英雄を連れていれば" TCC_NEWLINE
                           "あるいは。。。" TCC_NEWLINE TCC_PUSH_A
                           TCC_OPEN_RIGHT
                           TCC_CLEAR_FACE
                           TCC_OPEN_MID_LEFT
                           TCC_CLEAR_FACE,

        // Chapter 1 opening part 2
        [TEXT_CHAP_1_OP_2] = TCC_OPEN_LEFT
                             TCC_LOAD_FACE PORTRAIT_ALFONSE
                             TCC_OPEN_MID_LEFT
                             TCC_LOAD_FACE PORTRAIT_SHARENA
                             TCC_OPEN_FAR_LEFT
                             TCC_LOAD_FACE PORTRAIT_ANNA
                             TCC_OPEN_FAR_FAR_RIGHT
                             "わたしはミネルバ。" TCC_NEWLINE
                             "マケドニア王女だ。" TCC_NEWLINE
                             "いほうの旅人よ。元いた世界に帰りなさい。" TCC_NEWLINE TCC_PUSH_A
                             "我が身は既に「契約」を結ばれた。" TCC_NEWLINE
                             "エンブラ皇女ヴェロニカの命により、" TCC_NEWLINE
                             "これから異界に攻め入ることになる。" TCC_PUSH_A
                             TCC_OPEN_LEFT
                             "ミネルバ王女、僕はアルフォンス。" TCC_NEWLINE
                             "あなたが攻め入ることを命じられた" TCC_NEWLINE
                             "アスク王国の王子です。" TCC_NEWLINE TCC_PUSH_A
                             "どうか、武器を収めてください。" TCC_NEWLINE
                             "僕たちは英雄たちとの戦争を" TCC_NEWLINE
                             "望んではいません。" TCC_PUSH_A
                             TCC_OPEN_FAR_FAR_RIGHT
                             "ならば、力を示しなさい。" TCC_NEWLINE
                             "貴殿が力を示したならば、わたしは" TCC_NEWLINE
                             "ヴェロニカとの契約から解き放たれる。" TCC_PUSH_A
                             TCC_OPEN_LEFT
                             "力を示す。。" TCC_NEWLINE
                             "それはつまり。。。" TCC_PUSH_A
                             TCC_OPEN_FAR_LEFT
                             "戦って勝ちなさいってことね。" TCC_NEWLINE
                             "みんな、準備は良い？" TCC_PUSH_A,

                             // Chapter 1 ending part 1
                             [TEXT_CHAP_1_ED_1] = TCC_OPEN_FAR_FAR_RIGHT
                                     "見事。。。力は示された。" TCC_NEWLINE TCC_PUSH_A
                                     "ありがとう、アルフォンス王子。" TCC_NEWLINE
                                     "これで私たちは自由の身となった。" TCC_NEWLINE TCC_PUSH_A
                                     "もう貴国に攻め入ることはない。" TCC_NEWLINE
                                     "我が名において誓いましょう。" TCC_PUSH_A,

        // Chapter 1 ending part 2
        [TEXT_CHAP_1_ED_2] = TCC_OPEN_MID_LEFT
                TCC_LOAD_FACE PORTRAIT_SHARENA
                TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_ALFONSE
                "これで、任務は完了だね、" TCC_NEWLINE
                TCC_TACTICIAN_NAME"。" TCC_NEWLINE TCC_PUSH_A
                TCC_OPEN_MID_LEFT
                TCC_TACTICIAN_NAME"さんの指揮、" TCC_NEWLINE
                TCC_TACTICIAN_NAME"すっごく素晴らしかったです。。。！" TCC_NEWLINE
                "ますますほれ直しちゃいました！" TCC_PUSH_A
                TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "みんな聞いて！" TCC_NEWLINE
                "たった今入った知らせよ！" TCC_NEWLINE TCC_PUSH_A
                "エンブラ軍が大規模軍を展開して" TCC_NEWLINE
                "私たちの領地に侵攻してきたわ！" TCC_PUSH_A
                TCC_OPEN_LEFT
                "なんだって！？" TCC_NEWLINE
                "まさか、この地に来させたのは陽動。。。！？" TCC_PUSH_A
                TCC_OPEN_MID_LEFT
                "そんなあ。。。！" TCC_NEWLINE
                "私たち、まんまと敵の罠に" TCC_NEWLINE
                "はまっちゃったんですか！？" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "とにかく、" TCC_NEWLINE
                "急いで帰還しましょう！" TCC_PUSH_A,

    // Chapter 2 title
    [TEXT_CHAP_2_TITLE] = "英雄相争う",

    // Chapter 2 goal
    [TEXT_CHAP_STATUS_GOAL_DEFEAT_BOSS_XANDER] = "敵隊長マークスを倒す",

    // Chapter 2 opening
    [TEXT_CHAP_2_OP] = TCC_OPEN_LEFT
            TCC_LOAD_FACE PORTRAIT_VERONICA
            "いい子ね、あたしの英雄たち。。。" TCC_NEWLINE
            "もっと奪って、もっと壊して。。。" TCC_NEWLINE
            "邪魔する人は殺していいの。" TCC_NEWLINE TCC_PUSH_A
            "この国さえなくなれば、" TCC_NEWLINE
            "邪魔者はだれもいなくなる。。。" TCC_NEWLINE
            "私は全部の英雄を手に出来る。" TCC_PUSH_A
            TCC_OPEN_RIGHT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
            "そうはさせない！" TCC_NEWLINE
            "エンブラ帝国ヴェロニカ皇女。。。" TCC_NEWLINE
            "国を蹂躙すること、僕たちが許しはしない。" TCC_PUSH_A
            TCC_OPEN_LEFT
            "もう戻ってきたの。。。？" TCC_NEWLINE
            "せっかく遊び相手を用意してあげたのに、" TCC_NEWLINE
            "面倒な人たち。。。" TCC_NEWLINE TCC_PUSH_A
            "。。。？あなたは。。。" TCC_NEWLINE
            "その神器、まさか。。。" TCC_NEWLINE
            "伝承の召喚師なの。。。？" TCC_NEWLINE TCC_PUSH_A
            "そう。。。それなら、" TCC_NEWLINE
            "あなたを最初に殺すわ。。。" TCC_PUSH_A
            TCC_OPEN_MID_LEFT
            TCC_LOAD_FACE PORTRAIT_XANDER
            "。。。承知した、ヴェロニカ皇女。" TCC_NEWLINE
            "私が行こう。" TCC_PUSH_A
            TCC_OPEN_LEFT
            TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
            "あれは暗夜の英雄、マークス！？" TCC_NEWLINE
            "厄介だな。。。" TCC_NEWLINE
            "彼は圧倒的な力を持っている。" TCC_PUSH_A
            TCC_OPEN_MID_RIGHT
            TCC_LOAD_FACE PORTRAIT_SHARENA
            "で、でも大丈夫です！" TCC_NEWLINE
            TCC_TACTICIAN_NAME"さんは、" TCC_NEWLINE
            "私たちが守って見せますから！" TCC_PUSH_A
            TCC_OPEN_FAR_RIGHT
            TCC_LOAD_FACE PORTRAIT_ANNA
            "行くわよ、みんあ。" TCC_NEWLINE
            "アスク王国特務機関の力。。。" TCC_NEWLINE
            "あの皇女サマに見つけてやりましょ！" TCC_PUSH_A
            ,

        // Chapter 2 ending
        [TEXT_CHAP_2_ED] = TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_VERONICA
                "つまんないの。。。" TCC_NEWLINE
                "私はまた、ひとりぼっち。。。" TCC_NEWLINE TCC_PUSH_A
                "むしろに帰って、" TCC_NEWLINE
                "暖かい紅茶でも飲もうっと。。。" TCC_NEWLINE TCC_PUSH_A
                TCC_CLEAR_FACE
                TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "。。。。。。。。。" TCC_NEWLINE
                "なんとか撤退してくれたみたいね。" TCC_NEWLINE
                "皇女サマも、英雄たちも。" TCC_PUSH_A
                TCC_OPEN_MID_RIGHT
                TCC_LOAD_FACE PORTRAIT_ALFONSE
                "ああ。" TCC_NEWLINE
                "だが、これで終わるとは思えない。" TCC_NEWLINE
                "彼らはまた、この地に侵攻して来るだろう。" TCC_PUSH_A
                TCC_OPEN_FAR_RIGHT
                TCC_LOAD_FACE PORTRAIT_SHARENA
                "とにかくしつこいんですよね。" TCC_NEWLINE
                "話し合おうって言ってるのに、" TCC_NEWLINE
                "何度も何度も攻め込んでくるし！" TCC_NEWLINE TCC_PUSH_A
                "大体、エンブラ帝国の皇帝は" TCC_NEWLINE
                "いつになったらちゃんとした" TCC_NEWLINE
                "外交をしてくださるんでしょう！" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "シャロン、感情的になってはだめよ。" TCC_NEWLINE
                "そうれじゃ平和なんて夢のまた夢。" TCC_NEWLINE
                "機関の人間は、いつも冷静に。いい？" TCC_PUSH_A
                TCC_OPEN_FAR_RIGHT
                "はあい。" TCC_NEWLINE
                "わかりました、アンナ隊長。" TCC_PUSH_A
                TCC_OPEN_MID_RIGHT
                "すまない。。。"TCC_TACTICIAN_NAME"。" TCC_NEWLINE
                "こんな戦いに巻き込んでしまって、" TCC_NEWLINE
                "でも僕たちは、君が必要なんだ。" TCC_NEWLINE TCC_PUSH_A
                "どうかこれからも力を貸して欲しい。" TCC_NEWLINE
                "特務機関。。。" TCC_NEWLINE
                "「ヴァイス・ブレイヴ」の一員として。" TCC_PUSH_A
                ,

    [TEXT_CHAP_3_TITLE] = "紋章の試練",

    [TEXT_CHAP_3_OP_1] = TCC_OPEN_LEFT
            TCC_LOAD_FACE PORTRAIT_ANNA
            TCC_OPEN_RIGHT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
            TCC_OPEN_FAR_RIGHT
            TCC_LOAD_FACE PORTRAIT_SHARENA
            TCC_OPEN_LEFT
            "みんな聞いて。" TCC_NEWLINE
            "先程、エンブラ帝国軍が" TCC_NEWLINE
            "「紋章の異界」に侵入したわ。" TCC_NEWLINE TCC_PUSH_A
            "敵は英雄たちを支配に置き、" TCC_NEWLINE
            "私たちの国に侵攻するつもりよ。" TCC_NEWLINE
            "敵が狙う英雄の名は。。。マルス。" TCC_PUSH_A
            TCC_OPEN_RIGHT
            "マルス。。。" TCC_NEWLINE
            "英雄王ともうたわれた伝説の英雄か。" TCC_NEWLINE TCC_PUSH_A
            "彼が我が国に侵攻することは、" TCC_NEWLINE
            "なんとしても避けたいね。" TCC_PUSH_A
            TCC_OPEN_FAR_RIGHT
            "大丈夫ですっ。" TCC_NEWLINE
            "伝説の英雄王が敵でも、こっちには" TCC_NEWLINE
            "伝承の召喚し様がいるんですから！" TCC_PUSH_A
            TCC_OPEN_LEFT
            "手遅れになる前に、" TCC_NEWLINE
            "私たちも「紋章の異界」に入り、" TCC_NEWLINE
            "英雄を敵の支配から解放しましょう。" TCC_NEWLINE TCC_PUSH_A
            "さあ、"TCC_TACTICIAN_NAME"。" TCC_NEWLINE
            "用意はいいわね？" TCC_NEWLINE
            "出撃するわよ！" TCC_PUSH_A
            TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
            TCC_CLEAR_FACE
            TCC_OPEN_FAR_RIGHT
            TCC_CLEAR_FACE,

    [TEXT_CHAP_3_OP_2] = TCC_OPEN_FAR_FAR_RIGHT
            "僕はマルス。アリティアの王子だ。" TCC_NEWLINE
            "君たちが彼女。。。ヴェロニカ皇女が" TCC_NEWLINE
            "言っていた特務機関か。" TCC_NEWLINE TCC_PUSH_A
            "君たちも「契約」のことは知っているね。" TCC_NEWLINE
            "国を支配されてしまった英雄は" TCC_NEWLINE
            "支配者の命に服従せねばならない。。。" TCC_NEWLINE TCC_PUSH_A
            "契約を破るには僕を倒し、" TCC_NEWLINE
            "支配者よりも強い力を示すこと。" TCC_NEWLINE TCC_PUSH_A
            "では、正々堂々と戦おう。" TCC_NEWLINE
            "君たちの力、見せてもらうよ。" TCC_PUSH_A,

    [TEXT_CHAP_3_ED] = TCC_OPEN_FAR_FAR_RIGHT
            "。。。さすがだね。" TCC_NEWLINE
            "でも、僕はまだここでは" TCC_NEWLINE
            "諦めるわけにはいかない。" TCC_NEWLINE TCC_PUSH_A
            "一度退かせてもらうよ。" TCC_NEWLINE
            "次の戦いで、決着をつけよう。" TCC_PUSH_A,

    [TEXT_CHAP_4_TITLE] = "不屈なる猛者",

    [TEXT_CHAP_5_TITLE] = "光と風",
        [TEXT_CHAP_6_TITLE] = "赤と緑の双騎",
        [TEXT_CHAP_7_TITLE] = "紋章の王子",

        [TEXT_CHAP_8_TITLE] = "暗夜の試練",
        [TEXT_CHAP_9_TITLE] = "可憐な妹王女",
        [TEXT_CHAP_10_TITLE] = "冷酷な弟王子",
        [TEXT_CHAP_11_TITLE] = "妖艶な姉王女",
        [TEXT_CHAP_12_TITLE] = "暗夜の王子",

        [TEXT_CHAP_13_TITLE] = "封印の試練",
        [TEXT_CHAP_14_TITLE] = "高貴なる者",
        [TEXT_CHAP_15_TITLE] = "砂漠に住う竜",
        [TEXT_CHAP_16_TITLE] = "風変わりな親子",
        [TEXT_CHAP_17_TITLE] = "封印の公子",

        [TEXT_CHAP_18_TITLE] = "覚せいの試練",
        [TEXT_CHAP_19_TITLE] = "踊り子と剣士",
        [TEXT_CHAP_20_TITLE] = "包囲作戦",
        [TEXT_CHAP_21_TITLE] = "強き村人",
        [TEXT_CHAP_22_TITLE] = "覚せいの王子",

        [TEXT_CHAP_23_TITLE] = "紋章再び",
        [TEXT_CHAP_24_TITLE] = "要塞の姫君",
        [TEXT_CHAP_25_TITLE] = "挟撃",
        [TEXT_CHAP_26_TITLE] = "三姉妹、舞う",
        [TEXT_CHAP_27_TITLE] = "神竜の王女",

        [TEXT_CHAP_28_TITLE] = "白夜の試練",
        [TEXT_CHAP_29_TITLE] = "ひねくれ屋な弟王子",
        [TEXT_CHAP_30_TITLE] = "実直な姉王女",
        [TEXT_CHAP_31_TITLE] = "内気な妹王女",
        [TEXT_CHAP_32_TITLE] = "白夜の王子",

        [TEXT_CHAP_33_TITLE] = "烈火の試練",
        [TEXT_CHAP_34_TITLE] = "公子二人",
        [TEXT_CHAP_35_TITLE] = "迷宮に惑う",
        [TEXT_CHAP_36_TITLE] = "守護者は揺らがす",
        [TEXT_CHAP_37_TITLE] = "烈火の公子",

        [TEXT_CHAP_38_TITLE] = "物陰に潜みて",
        [TEXT_CHAP_39_TITLE] = "渓谷に臥す竜",
        [TEXT_CHAP_40_TITLE] = "貴族的な迎撃",
        [TEXT_CHAP_41_TITLE] = "帰還せし神竜",
        [TEXT_CHAP_42_TITLE] = "未来を知る王女",

        [TEXT_CHAP_43_TITLE] = "野望と忠義",
        [TEXT_CHAP_44_TITLE] = "王道と邪道",
        [TEXT_CHAP_45_TITLE] = "蒼鴉は見つめる",
        [TEXT_CHAP_46_TITLE] = "難攻不落",
        [TEXT_CHAP_47_TITLE] = "死の皇女",

        [TEXT_CHAP_48_TITLE] = "蒼炎の傭兵団",
        [TEXT_CHAP_49_TITLE] = "誇り高き副長",
        [TEXT_CHAP_50_TITLE] = "帝国の皇子",
        [TEXT_CHAP_51_TITLE] = "最後の砦",
        [TEXT_CHAP_52_TITLE] = "蒼炎の勇者",

        [TEXT_CHAP_53_TITLE] = "慈愛の王女",
        [TEXT_CHAP_54_TITLE] = "海戦",
        [TEXT_CHAP_55_TITLE] = "恐怖の山",
        [TEXT_CHAP_56_TITLE] = "海戦再び",
        [TEXT_CHAP_57_TITLE] = "呪詛の領域",

        [TEXT_CHAP_58_TITLE] = "水門",
        [TEXT_CHAP_59_TITLE] = "仇敵を追って",
        [TEXT_CHAP_60_TITLE] = "砂漠の砦",
        [TEXT_CHAP_61_TITLE] = "女神の神殿",
        [TEXT_CHAP_62_TITLE] = "帝国皇子ブルーノ",

        [TEXT_CHAP_63_TITLE] = "仮面お裏で",
        [TEXT_CHAP_64_TITLE] = "三隻の船",
        [TEXT_CHAP_65_TITLE] = "港町の死闘",
        [TEXT_CHAP_66_TITLE] = "全軍激突",
        [TEXT_CHAP_67_TITLE] = "友との再会",

        [TEXT_CHAP_68_TITLE] = "古より目覚めし",
        [TEXT_CHAP_69_TITLE] = "刃の儀式",

        // 第二部

        [TEXT_CHAP_70_TITLE] = "その炎、不死にして不滅",
        [TEXT_CHAP_71_TITLE] = "山は焼け、木は倒れ",
        [TEXT_CHAP_72_TITLE] = "水は乾き、海は呑まれ",
        [TEXT_CHAP_73_TITLE] = "天は焦げ、月は墜ちる",
        [TEXT_CHAP_74_TITLE] = "霧の妖婦",

        [TEXT_CHAP_75_TITLE] = "雪の娘",
        [TEXT_CHAP_76_TITLE] = "白き夜の子ら",
        [TEXT_CHAP_77_TITLE] = "黒き夜の子ら",
        [TEXT_CHAP_78_TITLE] = "黒白の子ら",
        [TEXT_CHAP_79_TITLE] = "炎の王",

        [TEXT_CHAP_80_TITLE] = "ニフルへの道",
        [TEXT_CHAP_81_TITLE] = "銀の髪の乙女",
        [TEXT_CHAP_82_TITLE] = "奇妙な守護者",
        [TEXT_CHAP_83_TITLE] = "異貌の騎士",
        [TEXT_CHAP_84_TITLE] = "炎剣、地を薙ぐ",

        [TEXT_CHAP_85_TITLE] = "守るべき人々のために",
        [TEXT_CHAP_86_TITLE] = "緋閃の女剣士",
        [TEXT_CHAP_87_TITLE] = "光と影の王女",
        [TEXT_CHAP_88_TITLE] = "幼き竜人",
        [TEXT_CHAP_89_TITLE] = "灼熱の決断",

        [TEXT_CHAP_90_TITLE] = "雪原の追跡者",
        [TEXT_CHAP_91_TITLE] = "灰空に舞う魔女",
        [TEXT_CHAP_92_TITLE] = "邪竜目覚めし時",
        [TEXT_CHAP_93_TITLE] = "暗黒皇帝",
        [TEXT_CHAP_94_TITLE] = "炎の狩人",

        [TEXT_CHAP_95_TITLE] = "夢見る姿は彼方に",
        [TEXT_CHAP_96_TITLE] = "聖痕の騎士",
        [TEXT_CHAP_97_TITLE] = "軍師の娘",
        [TEXT_CHAP_98_TITLE] = "軍師の息子",
        [TEXT_CHAP_99_TITLE] = "炎剣の鞘",

        // ../tool/chapter_title/make_chapter_title_text.py

        [TEXT_CHAP_100_TITLE] = "夢は間近に",
        [TEXT_CHAP_101_TITLE] = "魔道騎士の剣",
        [TEXT_CHAP_102_TITLE] = "不屈の意志",
        [TEXT_CHAP_103_TITLE] = "魔道騎士二人",
        [TEXT_CHAP_104_TITLE] = "邂逅、そして",

        [TEXT_CHAP_105_TITLE] = "氷の子はここで願う",
        [TEXT_CHAP_106_TITLE] = "荒ぶる炎鎮める力を",
        [TEXT_CHAP_107_TITLE] = "不死を殺し、不滅を滅す",
        [TEXT_CHAP_108_TITLE] = "その力を、器に",
        [TEXT_CHAP_109_TITLE] = "氷の儀",

        [TEXT_CHAP_110_TITLE] = "炎獄の門番",
        [TEXT_CHAP_111_TITLE] = "魔剣の黒騎士",
        [TEXT_CHAP_112_TITLE] = "雷神降り立つ",
        [TEXT_CHAP_113_TITLE] = "炎の踊り子",
        [TEXT_CHAP_114_TITLE] = "地獄の底",

        [TEXT_CHAP_115_TITLE] = "王城攻略",
        [TEXT_CHAP_116_TITLE] = "場違いな探求者",
        [TEXT_CHAP_117_TITLE] = "牙の兄妹",
        [TEXT_CHAP_118_TITLE] = "剣姫",
        [TEXT_CHAP_119_TITLE] = "炎の王、死す",

        [TEXT_CHAP_120_TITLE] = "敵の敵",
        [TEXT_CHAP_121_TITLE] = "花占いの行方",
        [TEXT_CHAP_122_TITLE] = "地獄の底から",
        [TEXT_CHAP_123_TITLE] = "天空の舞踏",
        [TEXT_CHAP_124_TITLE] = "骨灰の谷",

        [TEXT_CHAP_125_TITLE] = "疑心",
        [TEXT_CHAP_126_TITLE] = "地の継承者",
        [TEXT_CHAP_127_TITLE] = "這いずり彷徨う",
        [TEXT_CHAP_128_TITLE] = "風の継承者",
        [TEXT_CHAP_129_TITLE] = "裏切者は",

        [TEXT_CHAP_130_TITLE] = "王女レーギャルン",
        [TEXT_CHAP_131_TITLE] = "炎の贄たち",
        [TEXT_CHAP_132_TITLE] = "氷の従者",
        [TEXT_CHAP_133_TITLE] = "王女レーヴァテイン",
        [TEXT_CHAP_134_TITLE] = "炎王スルト",

        // 第三部

        [TEXT_CHAP_135_TITLE] = "死者は昼歩く",
        [TEXT_CHAP_136_TITLE] = "王国に差す影",
        [TEXT_CHAP_137_TITLE] = "撃殺の剣士",
        [TEXT_CHAP_138_TITLE] = "鏖殺の魔女",
        [TEXT_CHAP_139_TITLE] = "優しき死神",

        [TEXT_CHAP_140_TITLE] = "王命",
        [TEXT_CHAP_141_TITLE] = "冥府より吹く風",
        [TEXT_CHAP_142_TITLE] = "死者の道",
        [TEXT_CHAP_143_TITLE] = "先行偵察",
        [TEXT_CHAP_144_TITLE] = "王の姿",

        [TEXT_CHAP_145_TITLE] = "二十\年前の傷痕",
        [TEXT_CHAP_146_TITLE] = "凶兆の鴉王",
        [TEXT_CHAP_147_TITLE] = "狼女王の牙",
        [TEXT_CHAP_148_TITLE] = "鷹王と白の王子",
        [TEXT_CHAP_149_TITLE] = "死が、そこにいる",

        [TEXT_CHAP_150_TITLE] = "定められた死",
        [TEXT_CHAP_151_TITLE] = "妖狐の親子",
        [TEXT_CHAP_152_TITLE] = "ガルーの親子",
        [TEXT_CHAP_153_TITLE] = "零すゆく砂",
        [TEXT_CHAP_154_TITLE] = "死が、迎えに来る",

        [TEXT_CHAP_155_TITLE] = "失われたもの",
        [TEXT_CHAP_156_TITLE] = "傭兵天馬騎士",
        [TEXT_CHAP_157_TITLE] = "草原の戦士たち",
        [TEXT_CHAP_158_TITLE] = "魔竜の目覚め",
        [TEXT_CHAP_159_TITLE] = "死中に生を",

        [TEXT_CHAP_160_TITLE] = "幾千の惨劇を",
        [TEXT_CHAP_161_TITLE] = "獣戦士たち",
        [TEXT_CHAP_162_TITLE] = "再びの死",
        [TEXT_CHAP_163_TITLE] = "獅子王咆哮す",
        [TEXT_CHAP_164_TITLE] = "アスクの血脈",

        [TEXT_CHAP_165_TITLE] = "いつか見た景色",
        [TEXT_CHAP_166_TITLE] = "身を焦がす竜血",
        [TEXT_CHAP_167_TITLE] = "一人、見る夢",
        [TEXT_CHAP_168_TITLE] = "焼き尽くせぬ狂気",
        [TEXT_CHAP_169_TITLE] = "温もりの花",

        [TEXT_CHAP_170_TITLE] = "滅びの地で",
        [TEXT_CHAP_171_TITLE] = "最後の種族",
        [TEXT_CHAP_172_TITLE] = "花の残り香",
        [TEXT_CHAP_173_TITLE] = "神託の少女",
        [TEXT_CHAP_174_TITLE] = "書は語る、滅びを",

        [TEXT_CHAP_175_TITLE] = "一時の休戦",
        [TEXT_CHAP_176_TITLE] = "青獅子の守護者",
        [TEXT_CHAP_177_TITLE] = "野望の寵児",
        [TEXT_CHAP_178_TITLE] = "黒鷲を継ぐ者",
        [TEXT_CHAP_179_TITLE] = "正気を失うには、十\分だ",

        [TEXT_CHAP_180_TITLE] = "彼女の名は",
        [TEXT_CHAP_181_TITLE] = "令嬢と修道士",
        [TEXT_CHAP_182_TITLE] = "エンブラに入りて",
        [TEXT_CHAP_183_TITLE] = "悪鬼来たる",
        [TEXT_CHAP_184_TITLE] = "鮮血の神殿",

        [TEXT_CHAP_185_TITLE] = "希望の行方は",
        [TEXT_CHAP_186_TITLE] = "仮面騎士の放浪",
        [TEXT_CHAP_187_TITLE] = "踊り子の審美",
        [TEXT_CHAP_188_TITLE] = "神竜王の微睡み",
        [TEXT_CHAP_189_TITLE] = "俺は知り、お前は知らない",

        [TEXT_CHAP_190_TITLE] = "もう一人のシャロン",
        [TEXT_CHAP_191_TITLE] = "豪放なる重騎士",
        [TEXT_CHAP_192_TITLE] = "己が影を追って",
        [TEXT_CHAP_193_TITLE] = "三姉妹の次女",
        [TEXT_CHAP_194_TITLE] = "せめて、君たちは",

        [TEXT_CHAP_195_TITLE] = "私に従え",
        [TEXT_CHAP_196_TITLE] = "あの丘で共に",
        [TEXT_CHAP_197_TITLE] = "玩弄されるもの",
        [TEXT_CHAP_198_TITLE] = "あなたを殺す",
        [TEXT_CHAP_199_TITLE] = "死の王ヘル",

        // 第四部

        [TEXT_CHAP_200_TITLE] = "眠り病",
        [TEXT_CHAP_201_TITLE] = "それはあたかも現実のよう",
        [TEXT_CHAP_202_TITLE] = "見ている間はそれと気づかず",
        [TEXT_CHAP_203_TITLE] = "目覚めて初めてそれと知る",
        [TEXT_CHAP_204_TITLE] = "眠れる者の世界、それが",

        [TEXT_CHAP_205_TITLE] = "夢の迷い子",
        [TEXT_CHAP_206_TITLE] = "智将の憤懣",
        [TEXT_CHAP_207_TITLE] = "剣士の悔恨",
        [TEXT_CHAP_208_TITLE] = "女神の忘失",
        [TEXT_CHAP_209_TITLE] = "夢の中の夢へ",

        [TEXT_CHAP_210_TITLE] = "目覚めを告げるもの",
        [TEXT_CHAP_211_TITLE] = "妹王女の懐旧",
        [TEXT_CHAP_212_TITLE] = "娘の母恋い",
        [TEXT_CHAP_213_TITLE] = "勇者の心奥",
        [TEXT_CHAP_214_TITLE] = "友は遠く",

        [TEXT_CHAP_215_TITLE] = "人に見せる夢は",
        [TEXT_CHAP_216_TITLE] = "幼き竜の追憶",
        [TEXT_CHAP_217_TITLE] = "イリア騎士の決意",
        [TEXT_CHAP_218_TITLE] = "密偵の未来",
        [TEXT_CHAP_219_TITLE] = "響き渡る音色",

        [TEXT_CHAP_220_TITLE] = "その名を知る者は",
        [TEXT_CHAP_221_TITLE] = "少女の願い",
        [TEXT_CHAP_222_TITLE] = "優等生の溜息",
        [TEXT_CHAP_223_TITLE] = "引き籠もりの憂鬱",
        [TEXT_CHAP_224_TITLE] = "答えは夢に",

        [TEXT_CHAP_225_TITLE] = "夢現",
        [TEXT_CHAP_226_TITLE] = "炎の部族の気炎",
        [TEXT_CHAP_227_TITLE] = "星竜の誓い",
        [TEXT_CHAP_228_TITLE] = "心寂しき娘",
        [TEXT_CHAP_229_TITLE] = "思い出の友",

        [TEXT_CHAP_230_TITLE] = "白い夢",
        [TEXT_CHAP_231_TITLE] = "心よぎる名前",
        [TEXT_CHAP_232_TITLE] = "二つの心宿す者",
        [TEXT_CHAP_233_TITLE] = "心奥の戦い",
        [TEXT_CHAP_234_TITLE] = "現と夢を分かつ赤",

        [TEXT_CHAP_235_TITLE] = "甘やかな蜜の匂い",
        [TEXT_CHAP_236_TITLE] = "女王の理想",
        [TEXT_CHAP_237_TITLE] = "とりかえっこあそび",
        [TEXT_CHAP_238_TITLE] = "武将の葛藤",
        [TEXT_CHAP_239_TITLE] = "誰からも愛されない子",

        [TEXT_CHAP_240_TITLE] = "小さな姉妹の声",
        [TEXT_CHAP_241_TITLE] = "盗賊の改心",
        [TEXT_CHAP_242_TITLE] = "影の英雄の誓い",
        [TEXT_CHAP_243_TITLE] = "虐げられる子たち",
        [TEXT_CHAP_244_TITLE] = "すべての夢の王",

        [TEXT_CHAP_245_TITLE] = "我は汝を召喚す",
        [TEXT_CHAP_246_TITLE] = "伝承に曰く",

        [TEXT_CHAP_247_TITLE] = "いつか大人になったら",
        [TEXT_CHAP_248_TITLE] = "ファーガス王の道",
        [TEXT_CHAP_249_TITLE] = "パルミラ国王の道",
        [TEXT_CHAP_250_TITLE] = "アドラステア皇帝の道",
        [TEXT_CHAP_251_TITLE] = "ただ、愛してほしかった",
        [TEXT_CHAP_252_TITLE] = "終わっていない",
        [TEXT_CHAP_253_TITLE] = "ずっと泣いていた子",
        [TEXT_CHAP_254_TITLE] = "とりかえて、またとりかえて",
        [TEXT_CHAP_256_TITLE] = "私の夢を",
        [TEXT_CHAP_257_TITLE] = "すべてが始まった日",
        [TEXT_CHAP_258_TITLE] = "鋼の世界",
        [TEXT_CHAP_259_TITLE] = "聖教会の妹",
        [TEXT_CHAP_260_TITLE] = "聖教会の兄",
        [TEXT_CHAP_261_TITLE] = "守ってあげたかった",
        [TEXT_CHAP_262_TITLE] = "あなたは誰",
        [TEXT_CHAP_263_TITLE] = "それはあたかも夢のよう",
        [TEXT_CHAP_264_TITLE] = "日々繰り返しそれは現れ",
        [TEXT_CHAP_265_TITLE] = "それこそ真と信じるが",
        [TEXT_CHAP_266_TITLE] = "それを確かめる術はない",
        [TEXT_CHAP_267_TITLE] = "夢の終焉を告げる世界、それが",
        [TEXT_CHAP_268_TITLE] = "機械仕掛けの王女",
        [TEXT_CHAP_269_TITLE] = "曠野の王",
        [TEXT_CHAP_270_TITLE] = "道を拓く鍵は",
        [TEXT_CHAP_271_TITLE] = "王女の迷い",
        [TEXT_CHAP_272_TITLE] = "王国の兄妹",
        [TEXT_CHAP_273_TITLE] = "すれ違う想い",
        [TEXT_CHAP_274_TITLE] = "虎目石の野心",
        [TEXT_CHAP_275_TITLE] = "蛍石の誓い",
        [TEXT_CHAP_276_TITLE] = "黒曜石の忠義",
        [TEXT_CHAP_277_TITLE] = "お前なんかいらない",
        [TEXT_CHAP_278_TITLE] = "求めるものは",
        [TEXT_CHAP_279_TITLE] = "アルスターの王女",
        [TEXT_CHAP_280_TITLE] = "ロプトの姫",
        [TEXT_CHAP_281_TITLE] = "誓いの魔道士",
        [TEXT_CHAP_282_TITLE] = "王と賢者",
        [TEXT_CHAP_283_TITLE] = "幼き賢者",
        [TEXT_CHAP_284_TITLE] = "シレジアの誇り",
        [TEXT_CHAP_285_TITLE] = "泣き虫天馬騎士",
        [TEXT_CHAP_286_TITLE] = "ヴェルトマーの兄弟",
        [TEXT_CHAP_287_TITLE] = "巨人の国の王女",
        [TEXT_CHAP_288_TITLE] = "王女の本心",
        [TEXT_CHAP_289_TITLE] = "生真面目な騎士",
        [TEXT_CHAP_290_TITLE] = "居眠り同級生",
        [TEXT_CHAP_291_TITLE] = "エドマンド家の養女",
        [TEXT_CHAP_292_TITLE] = "諍いを越えて",
        [TEXT_CHAP_293_TITLE] = "遠い思い出",
        [TEXT_CHAP_294_TITLE] = "すご腕の天馬騎士",
        [TEXT_CHAP_295_TITLE] = "望まぬ再会",
        [TEXT_CHAP_296_TITLE] = "銀の魔道軍将",
        [TEXT_CHAP_297_TITLE] = "賢者の真実",
        [TEXT_CHAP_298_TITLE] = "読めぬ思惑",
        [TEXT_CHAP_299_TITLE] = "闇色の忠節",
        [TEXT_CHAP_300_TITLE] = "狂乱の王子",
        [TEXT_CHAP_301_TITLE] = "覇道の終着点",
        [TEXT_CHAP_302_TITLE] = "過去を求めて",
        [TEXT_CHAP_303_TITLE] = "軋む歯車",
        [TEXT_CHAP_304_TITLE] = "我道の魔道士",
        [TEXT_CHAP_305_TITLE] = "献身の聖女",
        [TEXT_CHAP_306_TITLE] = "優しき長女",
        [TEXT_CHAP_307_TITLE] = "失いし過去",
        [TEXT_CHAP_308_TITLE] = "あなたの居る場所",
        [TEXT_CHAP_309_TITLE] = "笑い上戸の呪い師",
        [TEXT_CHAP_310_TITLE] = "禁忌の呪術師",
        [TEXT_CHAP_311_TITLE] = "女の本性",
        [TEXT_CHAP_312_TITLE] = "強面の重騎士",
        [TEXT_CHAP_313_TITLE] = "狂気の襲撃者",
        [TEXT_CHAP_314_TITLE] = "穏やかなる祈り",
        [TEXT_CHAP_315_TITLE] = "誓いの優王女",
        [TEXT_CHAP_316_TITLE] = "大修道院の",
        [TEXT_CHAP_317_TITLE] = "光の王子",
        [TEXT_CHAP_318_TITLE] = "壊れゆく王国",
        [TEXT_CHAP_319_TITLE] = "どこにも帰さない",
        [TEXT_CHAP_320_TITLE] = "雌伏令嬢",
        [TEXT_CHAP_321_TITLE] = "灰色の義侠心",
        [TEXT_CHAP_322_TITLE] = "全てを失って",
        [TEXT_CHAP_323_TITLE] = "紡がれた歴史",
        [TEXT_CHAP_324_TITLE] = "異形の敵",
        [TEXT_CHAP_325_TITLE] = "決別",
        [TEXT_CHAP_326_TITLE] = "律義の狼",
        [TEXT_CHAP_327_TITLE] = "家族",
        [TEXT_CHAP_328_TITLE] = "懐かしい友",
        [TEXT_CHAP_329_TITLE] = "魔剣グラム",
        [TEXT_CHAP_330_TITLE] = "覚悟の伯爵家令嬢",
        [TEXT_CHAP_331_TITLE] = "小人の王冠",
        [TEXT_CHAP_332_TITLE] = "王女の旅立ち",
        [TEXT_CHAP_333_TITLE] = "エンブラの災厄",
        [TEXT_CHAP_334_TITLE] = "天を閉ざせば空はなく",
        [TEXT_CHAP_335_TITLE] = "地を閉ざせば命はなく",
        [TEXT_CHAP_336_TITLE] = "時を閉ざせば未来はない",
        [TEXT_CHAP_337_TITLE] = "閉ざされた世界",
        [TEXT_CHAP_338_TITLE] = "奇なる翼を追って",
        [TEXT_CHAP_339_TITLE] = "真理の探求者",
        [TEXT_CHAP_340_TITLE] = "勇者の末裔",
        [TEXT_CHAP_341_TITLE] = "東王と西王",
        [TEXT_CHAP_342_TITLE] = "呪詛部隊の長",
        [TEXT_CHAP_343_TITLE] = "声がきこえる",
        [TEXT_CHAP_344_TITLE] = "盗賊の達観",
        [TEXT_CHAP_345_TITLE] = "狩人の涙",
        [TEXT_CHAP_346_TITLE] = "砂塵の王の開花",
        [TEXT_CHAP_347_TITLE] = "すべてを失い、落ちなさい",
        [TEXT_CHAP_348_TITLE] = "味方はもういない",
        [TEXT_CHAP_349_TITLE] = "理魔道士の嘆息",
        [TEXT_CHAP_350_TITLE] = "黒の宣告",
        [TEXT_CHAP_351_TITLE] = "いつか、友達にだって",
        [TEXT_CHAP_352_TITLE] = "告げられた別離",
        [TEXT_CHAP_353_TITLE] = "光の眷属",
        [TEXT_CHAP_354_TITLE] = "軍師は語る",
        [TEXT_CHAP_355_TITLE] = "豊かなる恵みは",
        [TEXT_CHAP_356_TITLE] = "無情の策",
        [TEXT_CHAP_357_TITLE] = "僕が殺した",
        [TEXT_CHAP_358_TITLE] = "監獄要塞",
        [TEXT_CHAP_359_TITLE] = "囚われの皇女",
        [TEXT_CHAP_360_TITLE] = "嘘の形勢",
        [TEXT_CHAP_361_TITLE] = "あなたが決める",
        [TEXT_CHAP_362_TITLE] = "処刑の日",
        [TEXT_CHAP_363_TITLE] = "宮廷の舞曲",
        [TEXT_CHAP_364_TITLE] = "白き独白",
        [TEXT_CHAP_365_TITLE] = "心は死せず",
        [TEXT_CHAP_366_TITLE] = "姉、妹",
        [TEXT_CHAP_367_TITLE] = "すべては闇へ",


        [TEXT_CHAP_5_TIP] = TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "財宝の匂い。。。" TCC_PUSH_A
                TCC_CLEAR_FACE,

        [TEXT_CHAP_GET_SLIM_SWORD] = TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_CURRENT
                "巨竜の骸骨に刺さった細い剣。。。" TCC_NEWLINE
                "古いけどまだ使えそう。" TCC_PUSH_A
                TCC_CLEAR_FACE,

        [TEXT_CHAP_6_OP] = TCC_OPEN_FAR_LEFT
                "さすがだね。。。" TCC_NEWLINE
                "よくここまで来てくれた。" TCC_NEWLINE
                "君たちは平和を求めて戦っているんだね。" TCC_NEWLINE TCC_PUSH_A
                "その気持ちは、よくわかるつもりだよ。" TCC_NEWLINE
                "僕たちは似ている、同じ仲間として。" TCC_NEWLINE
                "出会えていたら。。。そう思うよ。" TCC_NEWLINE TCC_PUSH_A
                "さあ、最後の勝負だ。" TCC_NEWLINE
                "正々堂々戦おう！" TCC_PUSH_A,

        [TEXT_CHAP_6_ED] = TCC_OPEN_FAR_LEFT
                           "力は示された。。。" TCC_NEWLINE
                           "これで僕たちは、" TCC_NEWLINE
                           "契約から解放される。" TCC_NEWLINE TCC_PUSH_A
                           "ありがとう、感謝するよ。" TCC_NEWLINE
                           "僕たちは似ている、同じ仲間として。" TCC_NEWLINE
                           "君たちのような人と出会えて" TCC_NEWLINE TCC_PUSH_A
                           "本当によかった。" TCC_NEWLINE
                           "また、どこかで出会えたら良いね。" TCC_PUSH_A
                           TCC_OPEN_LEFT
                           TCC_LOAD_FACE PORTRAIT_ALFONSE
                           "これで、なんとか" TCC_NEWLINE
                           "危機は去ったようだね。" TCC_PUSH_A
                           TCC_OPEN_RIGHT
                           TCC_LOAD_FACE PORTRAIT_VERONICA
                           "つまらないの。。。" TCC_PUSH_A
                           TCC_OPEN_LEFT
                           "！？ヴェロニカ皇女。。。！" TCC_PUSH_A
                           TCC_OPEN_RIGHT
                           "せっかくマルスたちを" TCC_NEWLINE
                           "あたしのものにしたのに。。。" TCC_NEWLINE
                           "どうして解放しちゃうの？" TCC_NEWLINE TCC_PUSH_A
                           "邪魔者には、" TCC_NEWLINE
                           "みんな死でもらわなくちゃ。。。" TCC_PUSH_A
                           TCC_OPEN_MID_LEFT
                           TCC_LOAD_FACE PORTRAIT_ANNA
                           "くっ。。。！みんな、下がって。" TCC_NEWLINE
                           "今の私たちでは" TCC_NEWLINE
                           "ヴェロニカ皇女には勝てないわ。" TCC_NEWLINE TCC_PUSH_A
                           "全員の帰還を第一優先！" TCC_NEWLINE
                           "直ちに撤退！" TCC_PUSH_A
                           TCC_CLEAR_FACE
                           TCC_OPEN_LEFT
                           TCC_CLEAR_FACE
                           TCC_OPEN_RIGHT
                           "逃げるの？遊びたかったのに。。。" TCC_NEWLINE
                           "じゃああたしも、お城に帰るわ。" TCC_NEWLINE TCC_PUSH_A
                           "次はもっともっと強い英雄を" TCC_NEWLINE
                           "あたしのものにしようっと。。。" TCC_PUSH_A,

        [TEXT_CHAP_8_OP] = TCC_OPEN_FAR_LEFT
                TCC_LOAD_FACE PORTRAIT_XANDER
                "。。。来たか。" TCC_NEWLINE
                "剣を交えるのは、これで二度目だな。" TCC_NEWLINE
                "私たちはヴェロニカ皇女と契約した。" TCC_NEWLINE TCC_PUSH_A
                "皇女のあの寂しげな瞳。。。" TCC_NEWLINE
                "城塞から出られぬあいつを思わせて、" TCC_NEWLINE
                "どうしても逆らえん。" TCC_NEWLINE TCC_PUSH_A
                "カミラ、レオン、エリーゼ。" TCC_NEWLINE
                "準備はいいか？" TCC_NEWLINE
                "行くぞ！" TCC_PUSH_A,

        [TEXT_CHAP_8_ED] = TCC_OPEN_FAR_LEFT
                           TCC_LOAD_FACE PORTRAIT_XANDER
                           "ほう。。。" TCC_NEWLINE
                           "なかなかやるよだな。" TCC_NEWLINE
                           "だが、これで終わりではない。" TCC_NEWLINE TCC_PUSH_A
                           "行っておくが、" TCC_NEWLINE
                           "私のきょうだい。。。そして" TCC_NEWLINE
                           "その臣下たちは手強いぞ。" TCC_PUSH_A,

        [TEXT_CHAP_12_OP] = TCC_OPEN_FAR_LEFT
                            TCC_LOAD_FACE PORTRAIT_XANDER
                            "面白い。。。" TCC_NEWLINE
                            "ここまでたどり着くとはな。" TCC_NEWLINE TCC_PUSH_A
                            "これも特務機関の。。。" TCC_NEWLINE
                            "ヴェロニカ皇女の言っていた" TCC_NEWLINE
                            "伝承の召喚師の力か。" TCC_NEWLINE TCC_PUSH_A
                            "ならば最後まで全力で応じよう。" TCC_NEWLINE
                            "共に来てくれ、" TCC_NEWLINE
                            "ラズワルド、ピエり。" TCC_PUSH_A,

        [TEXT_CHAP_12_ED] = TCC_OPEN_FAR_LEFT
                            TCC_LOAD_FACE PORTRAIT_XANDER
                            "。。。私たちの負けか。" TCC_NEWLINE
                            "この地は解放された。" TCC_NEWLINE TCC_PUSH_A
                            "これで貴殿らと闘う理由も、" TCC_NEWLINE
                            "アスク王国に侵攻する理由もなくなった。" TCC_NEWLINE
                            "だが。。。" TCC_NEWLINE TCC_PUSH_A
                            "私はヴェロニカ皇女についていこう。" TCC_NEWLINE
                            "次に会う時は、負けませんぞ。" TCC_PUSH_A
                            TCC_CLEAR_FACE
                            TCC_OPEN_RIGHT
                            TCC_LOAD_FACE PORTRAIT_ANNA
                            "英雄マークス。。。" TCC_NEWLINE
                            "よりによって、ヴェロニカ皇女に" TCC_NEWLINE
                            "味方するだなんて。" TCC_PUSH_A
                            TCC_OPEN_MID_RIGHT
                            TCC_LOAD_FACE PORTRAIT_ALFONSE
                            "英雄の中には契約から解放されても、" TCC_NEWLINE
                            "自分の意思でこの世界の人間に" TCC_NEWLINE
                            "協力する者がいるんだ。" TCC_NEWLINE TCC_PUSH_A
                            TCC_TACTICIAN_NAME"に召喚された" TCC_NEWLINE
                            "英雄たちはすぐに味方になってくれるけど。。。" TCC_NEWLINE
                            "本来、そういった者はとても少ないんだよ。" TCC_PUSH_A
                            TCC_OPEN_FAR_RIGHT
                            TCC_LOAD_FACE PORTRAIT_SHARENA
                            "でも、その分仲良しになれると" TCC_NEWLINE
                            "すっごく嬉しいんです。" TCC_NEWLINE
                            "私にもいますよ、英雄のお友達。" TCC_PUSH_A
                            TCC_OPEN_MID_RIGHT
                            "シャロン。。。" TCC_NEWLINE
                            "あまり肩入れしすぎるなと言っただろう。" TCC_NEWLINE TCC_PUSH_A
                            "英雄たちとはあくまで協力関係。" TCC_NEWLINE
                            "友人ではないのだから" TCC_PUSH_A
                            TCC_OPEN_FAR_RIGHT
                            "えーっ。でもお兄様にっだて" TCC_NEWLINE
                            "仲良しの英雄がいたじゃないですか。" TCC_NEWLINE
                            "今は異界に帰ったんでしたっけ？" TCC_PUSH_A
                            TCC_OPEN_MID_RIGHT
                            "。。。ああ。" TCC_NEWLINE
                            "そうだね。。。" TCC_PUSH_A
                            TCC_OPEN_FAR_RIGHT
                            "お兄様。。。？" TCC_PUSH_A
                            TCC_OPEN_RIGHT
                            "はい、お話はそこまで。" TCC_NEWLINE
                            "解放した地に長居は無用よ。" TCC_NEWLINE
                            "帰還して、次の任務に備えましょう！" TCC_PUSH_A,

        [TEXT_CHAP_13_OP] = TCC_OPEN_LEFT
                            "あなたがアスク王国の" TCC_NEWLINE
                            "アルフォンス王子ですね。" TCC_NEWLINE
                            "初めてお目にかかります。" TCC_NEWLINE TCC_PUSH_A
                            "僕はロイ。若輩の身ですが、" TCC_NEWLINE
                            "父の代理として、" TCC_NEWLINE
                            "フェレの軍を率いています。" TCC_NEWLINE TCC_PUSH_A
                            "異界の王族に刃を向ける無礼、" TCC_NEWLINE
                            "どうかお許してください。" TCC_PUSH_A,

        [TEXT_CHAP_13_ED] = TCC_OPEN_LEFT
                            "強い。。。" TCC_NEWLINE
                            "話に聞いていた通り、" TCC_NEWLINE
                            "さすが異界の英雄。。。" TCC_NEWLINE TCC_PUSH_A
                            "でも、僕も契約を交した身。" TCC_NEWLINE
                            "まだ、ここで負けるわけには。。。" TCC_PUSH_A,

        [TEXT_CHAP_17_OP] = TCC_OPEN_FAR_FAR_RIGHT
                            "リリーナ、みんな！" TCC_NEWLINE
                            "アルフォンス王子たちが" TCC_NEWLINE
                            "ここへ来たみたいだ。" TCC_NEWLINE TCC_PUSH_A
                            "彼らが勝てば、" TCC_NEWLINE
                            "僕たちは契約から解き放たれる。" TCC_NEWLINE
                            "もちろん手加減したりはできないけどね。" TCC_NEWLINE TCC_PUSH_A
                            "リリーナの炎と、僕の剣で" TCC_NEWLINE
                            "彼らに全力で挑んでみよう。" TCC_NEWLINE
                            "さあ、行こう！" TCC_PUSH_A,

        [TEXT_CHAP_17_ED] = TCC_OPEN_FAR_FAR_RIGHT
                            "力は示された。。。" TCC_NEWLINE
                            "アルフォンス王子、" TCC_NEWLINE
                            "僕たちの完敗です。" TCC_NEWLINE TCC_PUSH_A
                            "そして"TCC_TACTICIAN_NAME"、" TCC_NEWLINE
                            "あなたの策にも感服したよ。" TCC_NEWLINE TCC_PUSH_A
                            "いつか、あなたたちと仲間になって、" TCC_NEWLINE
                            "共に戦える日が来ると良いな。。。" TCC_PUSH_A
                            TCC_OPEN_LEFT
                            TCC_LOAD_FACE PORTRAIT_ANNA
                            "「封印の異界」、確かに解放したわ。" TCC_NEWLINE
                            "みんな、お疲れ様。" TCC_PUSH_A
                            TCC_OPEN_MID_LEFT
                            TCC_LOAD_FACE PORTRAIT_ALFONSE
                            "今回の戦場は厳しかったね。" TCC_NEWLINE
                            TCC_TACTICIAN_NAME"、" TCC_NEWLINE
                            "疲れていないかい？" TCC_PUSH_A
                            TCC_OPEN_FAR_LEFT
                            TCC_LOAD_FACE PORTRAIT_SHARENA
                            "おお、涼しい顔をしてますね！" TCC_NEWLINE
                            "さすが"TCC_TACTICIAN_NAME"さん！" TCC_NEWLINE
                            "わたしなんかもう、暑くて暑くて。。。" TCC_PUSH_A
                            TCC_OPEN_LEFT
                            "位階には沢山の風景が広がっているわ。" TCC_NEWLINE
                            "森に、遺跡に、溶岩の河に。。。" TCC_NEWLINE TCC_PUSH_A
                            "もしかしたら、" TCC_NEWLINE
                            "あなたが見たことのある世界も" TCC_NEWLINE
                            "どこかにあるかもしれないわね。" TCC_PUSH_A
                            TCC_OPEN_MID_LEFT
                            "そういえば。。。" TCC_NEWLINE
                            "君はどこから来たんだ？" TCC_NEWLINE
                            "何か覚えている風景は" TCC_NEWLINE
                            "ないかい？" TCC_PUSH_A
                            "。。。鉄でできた大きな建物や、" TCC_NEWLINE
                            "馬のように走り回るキカイ？" TCC_NEWLINE
                            "へえ。興味深いよ。" TCC_PUSH_A
                            TCC_OPEN_LEFT
                            "そんな世界に続く扉は" TCC_NEWLINE
                            "見た事がないわね。。。" TCC_NEWLINE
                            "え、じゃあどうやって" TCC_NEWLINE
                            "帰るのかって？" TCC_NEWLINE TCC_PUSH_A
                            "。。。ま、まあ細かいことは" TCC_NEWLINE
                            "いいじゃない。" TCC_NEWLINE
                            "どのみちあなたはもう、" TCC_NEWLINE
                            "私たち機関の人間なんだもの！" TCC_NEWLINE TCC_PUSH_A
                            "さあみんな、" TCC_NEWLINE
                            "元気よく帰還するわよ！" TCC_PUSH_A,

        [TEXT_CHAP_15_GET_SLIM_LANCE] = TCC_OPEN_RIGHT
                                        TCC_LOAD_FACE PORTRAIT_CURRENT
                                        "巨竜の骸骨に刺さった細い槍。。。" TCC_NEWLINE
                                        "古いけどまだ使えそう。" TCC_PUSH_A
                                        TCC_CLEAR_FACE,

        [TEXT_SPECIAL_SKILL_HELP] = "奥義スキル",
        [TEXT_SPECIAL_SKILL_CD_HELP] = "奥義カウント",

        [TEXT_UNIT_STATE_MOBILITY_INCREASED_NAME] = "移動力上昇",
        [TEXT_UNIT_STATE_MOBILITY_INCREASED_HELP] = "移動力が上がっている",
        [TEXT_UNIT_STATE_GRAVITY_NAME] = "移動力下降",
        [TEXT_UNIT_STATE_GRAVITY_HELP] = "移動力が１に下がっている",
        [TEXT_UNIT_STATE_PANIC_NAME] = "パニック",
        [TEXT_UNIT_STATE_PANIC_HELP] = "＋の強化が−に変化している",
        [TEXT_UNIT_STATE_COUNTERATTACKS_DISRUPTED_NAME] = "反撃不可",
        [TEXT_UNIT_STATE_COUNTERATTACKS_DISRUPTED_HELP] = "反撃ができない",
        [TEXT_UNIT_STATE_TRIANGLE_ADEPT_NAME] = "相性激化",
        [TEXT_UNIT_STATE_TRIANGLE_ADEPT_HELP] = "相性激化の状態になっている",
        [TEXT_UNIT_STATE_GUARD_NAME] = "キャンセル",
        [TEXT_UNIT_STATE_GUARD_HELP] = "戦闘後、奥義発動カウント−が無効になり、奥義発動カウント変動量がー１となっている",
        [TEXT_UNIT_STATE_AIR_ORDERS_NAME] = "先導の伝令",
        [TEXT_UNIT_STATE_AIR_ORDERS_HELP] = "周囲２マス以内の味方の隣接マスに移動できるようになっている",
        [TEXT_UNIT_STATE_EFFECTIVE_AGAINST_DRAGONS_NAME] = "竜特効",
        [TEXT_UNIT_STATE_EFFECTIVE_AGAINST_DRAGONS_HELP] = "竜特効を得た状態になっている",
        [TEXT_UNIT_STATE_ISOLATION_NAME] = "補助不可",
        [TEXT_UNIT_STATE_ISOLATION_HELP] = "補助スキルを使うことも受けることもできない",
        [TEXT_UNIT_STATE_BONUS_DOUBLER_NAME] = "強化増幅",
        [TEXT_UNIT_STATE_BONUS_DOUBLER_HELP] = "戦闘中、攻撃、速さ、守備、魔防が自分が受けている攻撃、速さ、守備、魔防の強化の値だけ上昇（能\力値ごとに計算）",
        [TEXT_UNIT_STATE_DRAGON_SHIELD_NAME] = "竜特効無効",
        [TEXT_UNIT_STATE_DRAGON_SHIELD_HELP] = "竜に対する特効を無効にする",
        [TEXT_UNIT_STATE_SVALINN_SHIELD_NAME] = "重装特効無効",
        [TEXT_UNIT_STATE_SVALINN_SHIELD_HELP] = "重装に対する特効を無効にする",

        [TEXT_UNIT_POSITIVE_STATE_HELP] = "状態強化（有利な状態）",
        [TEXT_UNIT_NEGATIVE_STATE_HELP] = "状態異常（不利な状態）",
        [TEXT_NEW_UNIT_STATE_HELP] = "状態強化と状態異常",

        [TEXT_ASSIST_SKILL_NAME_IN_ACTION_MENU] = "補助スキル",
        [TEXT_ASSIST_SKILL_HELP_IN_ACTION_MENU] = "補助スキルヘルプ情報",
        [TEXT_ASSIST_SKILL_HELP_IN_STAT_SCREEN] = "補助スキルヘルプ情報",
        [TEXT_ASSIST_SKILL_DISABLED_HELP_IN_ACTION_MENU] = "補助スキルが使えない",
        [TEXT_ASSIST_SKILL_TARGET_SELECTION_HELP] = "補助スキルの対象を選びなさい",
        [TEXT_PASSIVE_SKILL_A_HELP] = "",
        [TEXT_PASSIVE_SKILL_B_HELP] = "",
        [TEXT_PASSIVE_SKILL_C_HELP] = "",
        [TEXT_PASSIVE_SKILL_S_HELP] = "",

        [TEXT_ITEM_CANNOT_USE] = "使用不可",
        [TEXT_ITEM_SACRED_SEAL_QUICKENED_PULSE_NAME] = "奥義のこどう",
        [TEXT_ITEM_SACRED_SEAL_QUICKENED_PULSE_HELP] = "１ターン目開始時、奥義発動カウントー１",

        [TEXT_SUPPORT_CONVERSATION_ALFONSE_SHARENA_C] = TCC_OPEN_LEFT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
                TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_SHARENA
                TCC_OPEN_LEFT
                "シャロン、今日はどんな予\定があるんだ？" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "ええと、まずは図書館で本を借りて、それから" TCC_NEWLINE
                "ソ\フィアさんに魔法の練習を教えてもらって、" TCC_NEWLINE
                "ごごはベロニカ姫とお茶会をするつもりよ。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "なるほど、充実した一日だな。私は今日は" TCC_NEWLINE
                "戦略会議に出席しなければならない。" TCC_NEWLINE
                "それから訓練場で剣の稽古をする。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "お兄様、いつも忙しそうね。" TCC_NEWLINE
                "でも、無理はしないでね。" TCC_NEWLINE
                "体調を崩したら大変だから。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "ありがとう、心配かけないようにするよ。" TCC_NEWLINE
                "でも、異界からやってきた英雄たちと共に" TCC_NEWLINE
                "戦っていると、故郷の平和な日々が" TCC_NEWLINE
                "懐かしくなるよ。いつになったら" TCC_NEWLINE
                "この戦争が終わるのだろうか。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "私もそう思うわ。" TCC_NEWLINE
                "でも、私たちは仲間たちと" TCC_NEWLINE
                "一緒に頑張っているんだから、" TCC_NEWLINE
                "きっといつかは夢が叶うと信じてる。" TCC_NEWLINE
                "お兄様もそう思わない？" TCC_PUSH_A
                TCC_OPEN_LEFT
                "うん、そうだね。" TCC_NEWLINE
                "シャロンの笑顔を見ると、" TCC_NEWLINE
                "希望が湧いてくるよ。" TCC_NEWLINE
                "ありがとう、シャロン。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "お兄様。。。" TCC_PUSH_A
                TCC_OPEN_LEFT
                TCC_CLEAR_FACE
                TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ALFONSE_SHARENA_B] = TCC_OPEN_LEFT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
                TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_SHARENA
                "お兄ちゃん、今日はどんな訓練を" TCC_NEWLINE
                "しましょうか？" TCC_PUSH_A
                TCC_OPEN_LEFT
                "ええと、私は剣の技術を磨きたい" TCC_NEWLINE
                "と思っているけど、シャロンはどうかな？" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "私も剣の技術を磨きたいです。" TCC_NEWLINE
                "でも、それだけではなくて、" TCC_NEWLINE
                "他の武器も使えるようになりたいです。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "そうか。じゃあ、何か試してみたい" TCC_NEWLINE
                "武器はあるかな？" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "ええと、私は。。。槍に興味があります。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "槍？シャロンは槍が好きなんだね。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "はい、好きです。槍はリーチが長くて、" TCC_NEWLINE
                "命中率が高くて、突き刺すと気持ちがいいです。" TCC_NEWLINE TCC_PUSH_A
                TCC_OPEN_LEFT
                "なるほど。私も槍は嫌いじゃないよ。" TCC_NEWLINE
                "特に、敵の移動を制限することができる" TCC_NEWLINE
                "槍が有効だと思う。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "私は攻撃力を上げることができる槍が好きです。" TCC_NEWLINE
                "敵の防御を貫いて一撃で倒します。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "ふふ、それぞれ違う槍が好きなんだね。" TCC_NEWLINE
                "でも、それがいいと思うよ。" TCC_NEWLINE
                "色々な槍があるからこそ、" TCC_NEWLINE
                "戦闘は面白いんだから。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "そうですね。色々な槍があるからこそ、" TCC_NEWLINE
                "戦略や判断力が問われます。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "そうだね。さあ、行こうか。" TCC_NEWLINE
                "訓練場に着くまでにはまだ少し走るから。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "はい、行きましょう。" TCC_NEWLINE
                "アルフォンスと一緒に" TCC_NEWLINE
                "槍を振るのが楽しみです。" TCC_PUSH_A
                TCC_OPEN_LEFT
                TCC_CLEAR_FACE
                TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ALFONSE_SHARENA_A] = TCC_OPEN_LEFT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
                TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_SHARENA
                TCC_OPEN_LEFT
                "この戦いは終わりが見えないな。" TCC_NEWLINE
                "敵はどこからともなく現れるし、" TCC_NEWLINE
                "味方は次々と倒れていく。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "でも、兄さん。" TCC_NEWLINE
                "私たちはあきらめられないよ。" TCC_NEWLINE
                "アスク王国を守るために、" TCC_NEWLINE
                "戦わなくちゃ。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "そうだね。" TCC_NEWLINE
                "君はいつも勇気づけてくれるね。" TCC_NEWLINE
                "ありがとう、シャロン。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "兄さんこそ、" TCC_NEWLINE"いつも私を守ってくれてありがとう。" TCC_NEWLINE
                "私は兄さんが大好きだよ。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "えっ、そうかい？" TCC_NEWLINE
                "それは嬉しいな。" TCC_NEWLINE
                "私も君が大好きだよ。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "ほんと？じゃあ、兄さん。" TCC_NEWLINE
                "私に一つだけ約束してほしい" TCC_NEWLINE
                "ことがあるんだけど。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "なんだい？" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "この戦いが終わったら、" TCC_NEWLINE
                "私と一緒に旅に出てくれる？" TCC_PUSH_A
                TCC_OPEN_LEFT
                "旅？どこに行くんだい？" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "どこでもいいの。" TCC_NEWLINE
                "私たちは色々な世界を見てきたけど、" TCC_NEWLINE
                "本当に自分たちの目で見たい" TCC_NEWLINE
                "ところがたくさんあるの。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "そうか。確かに、私もそう思うよ。" TCC_NEWLINE
                "でも、王国を放っておけるかな？" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "大丈夫だよ。" TCC_NEWLINE
                "王国は父様やキランさんや仲間たちが" TCC_NEWLINE
                "守ってくれるから。" TCC_NEWLINE
                "私たちは少しだけ自分の時間を" TCC_NEWLINE
                "楽しんでもいいんじゃないかな？" TCC_PUSH_A
                TCC_OPEN_LEFT
                "うーん、それもそうだね。" TCC_NEWLINE
                "じゃあ、約束するよ。" TCC_NEWLINE
                "この戦いが終わったら、" TCC_NEWLINE
                "君と一緒に旅に出よう。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "やった！ありがとう、兄さん！" TCC_NEWLINE
                "私、すごく嬉しいよ！" TCC_PUSH_A
                TCC_OPEN_LEFT
                "私もだよ。さあ、行こうか。" TCC_NEWLINE
                "敵はまだ待ってくれないからね。" TCC_PUSH_A
                TCC_OPEN_RIGHT
                "うん！兄さんと一緒なら、" TCC_NEWLINE
                "どんな敵も怖くないよ！" TCC_PUSH_A
                TCC_OPEN_LEFT
                TCC_CLEAR_FACE
                TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ALFONSE_ANNA_TEMP] = TCC_OPEN_LEFT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
                TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "敵が沸いてくる。行くわよ。" TCC_PUSH_A
                TCC_OPEN_LEFT
                "はい、隊長！" TCC_PUSH_A
                TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
                TCC_OPEN_LEFT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ALFONSE_ANNA_C] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_ALFONSE
                "アンナ隊長、" TCC_NEWLINE
                "ちょっとお時間いただけますか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "もちろん、アルフォンス王子。" TCC_NEWLINE
                "何でしょう？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "最近、私たちの軍団が拡大している" TCC_NEWLINE
                "ことについて考えていました。" TCC_NEWLINE
                "新しい英雄たちが加わり、" TCC_NEWLINE
                "私たちの力は確実に強くなっています。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そうですね。" TCC_NEWLINE
                "私たちの軍団はますます強くなっています。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "でも、それだけではありません。" TCC_NEWLINE
                "私たちは、新しい英雄たちとの絆" TCC_NEWLINE
                "を深めることも大切だと思います。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "確かに、絆は非常に重要です。" TCC_NEWLINE
                "英雄たちがお互いを信頼し、" TCC_NEWLINE
                "助け合うことができれば、" TCC_NEWLINE
                "私たちの力はさらに強くなります。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうですね。" TCC_NEWLINE
                "私たちは、英雄たちとの絆を深めるために" TCC_NEWLINE
                "もっと努力しなければなりません。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "私もそう思います。" TCC_NEWLINE
                "私たちは、" TCC_NEWLINE
                "英雄たちと一緒に訓練したり、" TCC_NEWLINE
                "お茶会を開いたりして、" TCC_NEWLINE
                "絆を深めることができます。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうしましょう。" TCC_NEWLINE
                "私たちの軍団がさらに強くなるように、" TCC_NEWLINE
                "一緒に頑張りましょう。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "はい、王子。" TCC_NEWLINE
                "一緒に頑張りましょう。" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE,
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ALFONSE_ANNA_B] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ALFONSE
                "よし、次は私と一緒に練習しよう！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_GENERIC_SOLDIER_BLUE
                "はい、王子！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "さあ、次は私と一緒に！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_LEFT
                TCC_LOAD_FACE PORTRAIT_GENERIC_SOLDIER_BLUE
                "はい、隊長！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "よくやった！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "ありがとうございます、王子！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_RIGHT
                "素晴らしい！" TCC_NEWLINE
                "もっと頑張ろう！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_LEFT
                "はい、隊長！" TCC_NEWLINE
                "もっと頑張ります！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "皆さん、今日も素晴らしい訓練でした。" TCC_NEWLINE
                "お互いに助け合いながら、" TCC_NEWLINE
                "技術を磨きましょう。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_RIGHT
                "そうですね。" TCC_NEWLINE
                "私たちはお互いを信頼し合い、" TCC_NEWLINE
                "助け合うことができれば、" TCC_NEWLINE
                "私たちの力はさらに強くなります。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "はい！" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_FAR_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
            TCC_OPEN_FAR_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ALFONSE_ANNA_A] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_ALFONSE
                "このお茶、とても美味しいですね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_FAR_RIGHT
                "本当に美味しいです。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "このお菓子も絶品です。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_FAR_LEFT
                "本当に美味しいです。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_FAR_RIGHT
                "私は最近、剣術の練習に夢中です。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_FAR_LEFT
                "私もそうです。" TCC_NEWLINE
                "剣術は本当に奥が深いですよね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_FAR_RIGHT
                "私は最近、料理に興味があります。" TCC_NEWLINE
                "新しいレシピを試してみるのが" TCC_NEWLINE
                "楽しいです。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "私も料理が好きです。" TCC_NEWLINE
                "一緒に料理を作ってみませんか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_FAR_RIGHT
                "それは良いですね！" TCC_NEWLINE
                "ぜひ一緒に料理を作りましょう！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "皆さん、今日も楽しい時間を" TCC_NEWLINE
                "ありがとうございました。" TCC_NEWLINE
                "また一緒にお茶会を開きましょう。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そうですね。" TCC_NEWLINE
                "私たちはお互いを知り合い、" TCC_NEWLINE
                "絆を深めることができます。" TCC_NEWLINE
                "また一緒に楽しい時間を過ごしましょう。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_FAR_FAR_LEFT
                "はい！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ANNA_SHARENA_C] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_SHARENA
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
            TCC_OPEN_LEFT
                "あの、アンナさん、" TCC_NEWLINE
                "ちょっとお話しできますか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "もちろん、シャロンちゃん。" TCC_NEWLINE
                "どうしたの？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "実は、私、" TCC_NEWLINE
                "アンナさんに憧れているんです。" TCC_NEWLINE
                "あなたは商売上手で、" TCC_NEWLINE
                "冒険好きで、" TCC_NEWLINE
                "自由奔放で。。。" TCC_NEWLINE
                "私もそんな風になりたいんです。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええっ？" TCC_NEWLINE"私に憧れてるの？" TCC_NEWLINE
                "それは嬉しいけど、" TCC_NEWLINE
                "私だって完璧じゃないよ。" TCC_NEWLINE
                "失敗もたくさんしてるし、" TCC_NEWLINE
                "困難もたくさん乗り越えてきたし。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "でも、それでも前向きに" TCC_NEWLINE
                "生きているんですよね。" TCC_NEWLINE
                "私は。。。" TCC_NEWLINE
                "自分に自信がなくて、" TCC_NEWLINE
                "いつも人に頼ってばかりで。" TCC_NEWLINE
                "だから、" TCC_NEWLINE
                "アンナさんに教えてほしいんです。" TCC_NEWLINE
                "どうしたら、" TCC_NEWLINE
                "あなたみたいに強くなれるんですか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "うーん、" TCC_NEWLINE
                "それは難しい質問だなぁ。" TCC_NEWLINE
                "私も自分で自分を強くしたわけじゃないし。" TCC_NEWLINE
                "でも、ひとつ言えることは。。。" TCC_NEWLINE
                "自分を信じることかな。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "自分を信じること。。。？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そう。" TCC_NEWLINE
                "自分には何かできることがあるって思うこと。" TCC_NEWLINE
                "自分には価値があるって思うこと。" TCC_NEWLINE
                "自分には夢があるって思うこと。" TCC_NEWLINE
                "そうやって自分をこうていすると、" TCC_NEWLINE
                "自信がつくし、" TCC_NEWLINE
                "勇気が出るし、" TCC_NEWLINE
                "楽しくなるよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうなんですか。。。？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "もちろん。" TCC_NEWLINE
                "だから、" TCC_NEWLINE
                "シャロンちゃんも、" TCC_NEWLINE
                "自分の良いところを見つけて、" TCC_NEWLINE
                "褒めてあげてね。" TCC_NEWLINE
                "私はシャロンちゃんのことを" TCC_NEWLINE
                "素直で優しくて可愛いって思ってるよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "あっ。。。" TCC_NEWLINE
                "ありがとうございます。" TCC_NEWLINE
                "アンナさんのお言葉、" TCC_NEWLINE
                "心に刻みます。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "いい子だね。" TCC_NEWLINE
                "これからも仲良くしてね。" TCC_NEWLINE
                "私もシャロンちゃんのことを" TCC_NEWLINE
                "応援してるから。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "はい！" TCC_NEWLINE
                "アンナさん、" TCC_NEWLINE
                "これからもよろしくお願いします！" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ANNA_SHARENA_B] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_SHARENA
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "シャロンちゃん、" TCC_NEWLINE
                "今日は一緒に買い物に行こうよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "えっ、買い物ですか？" TCC_NEWLINE
                "でも、私、お金があまりなくて。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "大丈夫、大丈夫。" TCC_NEWLINE
                "私がおごってあげるよ。" TCC_NEWLINE
                "それに、買い物といっても、" TCC_NEWLINE
                "見るだけでも楽しいんだから。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうですか。。。？" TCC_NEWLINE
                "でも、アンナさんは見るだけで" TCC_NEWLINE
                "満足できるんですか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "もちろん、できないよ。" TCC_NEWLINE
                "だから、見つけたら即買いするの。" TCC_NEWLINE
                "それが商売の鉄則だからね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "商売の鉄則。。。？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そう。" TCC_NEWLINE
                "迷ったら買え。" TCC_NEWLINE
                "後悔したら売れ。" TCC_NEWLINE
                "それが私のモットーだよ。" TCC_NEWLINE
                "だから、" TCC_NEWLINE
                "私はいつもお金に困らないし、" TCC_NEWLINE
                "楽しく暮らせるんだ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "すごいですね。。。" TCC_NEWLINE
                "でも、私には無理です。" TCC_NEWLINE
                "私はお金を使うのが怖くて、" TCC_NEWLINE
                "いつも節約してばかりで。" TCC_NEWLINE
                "だから、買い物に行っても、" TCC_NEWLINE
                "自分に必要なものしか買えないんです。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そんなこと言わないでよ。" TCC_NEWLINE
                "シャロンちゃんは自分に甘くないとダメだよ。" TCC_NEWLINE
                "自分にご褒美をあげることも大切だからね。" TCC_NEWLINE
                "たまには気分転換に、" TCC_NEWLINE
                "自分の好きなものを買ってみたら？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "自分の好きなもの。。。？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そう。" TCC_NEWLINE
                "例えば、" TCC_NEWLINE
                "可愛い服とか、" TCC_NEWLINE
                "美味しいお菓子とか、" TCC_NEWLINE
                "素敵なアクセサリーとか。" TCC_NEWLINE
                "そういうものを身につけたり食べたりすると、" TCC_NEWLINE
                "気分が上がるし、" TCC_NEWLINE
                "自信も出るよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうなんですか。。。？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "もちろん。" TCC_NEWLINE
                "だから、" TCC_NEWLINE
                "今日は私と一緒に、" TCC_NEWLINE
                "シャロンちゃんの好きなものを" TCC_NEWLINE
                "探してみようよ。" TCC_NEWLINE
                "私も一緒に選んであげるから。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "あっ。。。" TCC_NEWLINE
                "ありがとうございます。" TCC_NEWLINE
                "アンナさん、" TCC_NEWLINE
                "優しいですね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "いえいえ。" TCC_NEWLINE
                "私はシャロンちゃんの笑顔が" TCC_NEWLINE
                "見たいだけだよ。" TCC_NEWLINE
                "さあ、行こうか。" TCC_NEWLINE
                "今日は楽しい一日になりそうだね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "はい！" TCC_NEWLINE
                "アンナさん、" TCC_NEWLINE
                "今日は本当にありがとうございます！" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ANNA_SHARENA_A] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_SHARENA
                "アンナさん、" TCC_NEWLINE
                "今日は私に付き合ってくれて" TCC_NEWLINE
                "ありがとうございました。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "いえいえ、" TCC_NEWLINE"こちらこそ、" TCC_NEWLINE
                "シャロンちゃんと一緒に" TCC_NEWLINE
                "買い物ができて楽しかったよ。" TCC_NEWLINE
                "シャロンちゃん、" TCC_NEWLINE
                "いろいろなものを買ったね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "はい。" TCC_NEWLINE
                "アンナさんのおかげで、" TCC_NEWLINE
                "自分の好きなものを見つける" TCC_NEWLINE
                "ことができました。" TCC_NEWLINE
                "アンナさんは私にとって、" TCC_NEWLINE
                "良き先生であり、" TCC_NEWLINE
                "良き友人でもあります。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "あら、" TCC_NEWLINE
                "そんなに褒められると照れちゃうな。" TCC_NEWLINE
                "私もシャロンちゃんのことを、" TCC_NEWLINE
                "大切な友人だと思ってるよ。" TCC_NEWLINE
                "だから、これからも仲良くしてね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "はい、もちろんです。" TCC_NEWLINE
                "アンナさんと一緒にいると、" TCC_NEWLINE
                "私は自分を信じられるようになりました。" TCC_NEWLINE
                "アンナさんは私に勇気と希望をくれました。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そう言ってもらえると嬉しいよ。" TCC_NEWLINE
                "私もシャロンちゃんから" TCC_NEWLINE
                "たくさんのことを学びました。" TCC_NEWLINE
                "シャロンちゃんは私に" TCC_NEWLINE
                "優しさと真心をくれました。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "アンナさん。。。" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_ANNA_SHARENA_TEMP] = TCC_OPEN_MID_LEFT
            TCC_LOAD_FACE PORTRAIT_SHARENA
                TCC_OPEN_FAR_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
                "シャロン、怪我はありませんか。" TCC_PUSH_A
                TCC_OPEN_MID_LEFT
                "隊長、すみません。油断しました。" TCC_PUSH_A
                TCC_OPEN_FAR_RIGHT
                TCC_MOVE_TO_MID_RIGHT
                "薬を傷口に塗ってあげましょう。" TCC_PUSH_A
                TCC_OPEN_MID_LEFT
                "ありがとうございます。" TCC_NEWLINE
                TCC_OPEN_MID_RIGHT
                TCC_CLEAR_FACE
                TCC_OPEN_MID_LEFT
                "隊長さんは優しいですね。" TCC_PUSH_A
                TCC_CLEAR_FACE,

        [TEXT_NEW_PASSIVE_SKILL_UNLOCKED] = "新たなパッシブスキル",

        [TEXT_UNIT_LEVEL_HELP] = "ユニットのレベルです"TCC_NEWLINE"最高３０レベルです",

        [TEXT_CHAP_18_OP] = TCC_OPEN_LEFT
            "。。。現れたか。" TCC_NEWLINE
            "お前たちが特務機関を名乗る" TCC_NEWLINE
            "侵略者だな？" TCC_NEWLINE TCC_PUSH_A
            "先ほどエンブラ帝国の兵より、" TCC_NEWLINE
            "イーリス聖王国に仇なす勢力ありとの" TCC_NEWLINE
            "報せを受けた。" TCC_NEWLINE TCC_PUSH_A
            "イーリスの平和を乱す者は、" TCC_NEWLINE
            "このクロム自警団が許さん！" TCC_NEWLINE
            "行くぞ、リズ、フレデリク！" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

        [TEXT_CHAP_18_ED] = TCC_OPEN_LEFT
            "くっ。。。" TCC_NEWLINE
            "俺たちはまだ負けん。。。！" TCC_NEWLINE TCC_PUSH_A
            "ここからは自警団の皆で、" TCC_NEWLINE
            "お前たちを食い止めてみせる。" TCC_NEWLINE TCC_PUSH_A
            "クロム自警団の絆の力。。。" TCC_NEWLINE
            "よく見ておくんだな。" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

        [TEXT_CHAP_22_OP] = TCC_OPEN_RIGHT
            "ほう。。。ここまで来たか。" TCC_NEWLINE
            "その腕、敵にしておくのは" TCC_NEWLINE
            "惜しいほどだな。" TCC_NEWLINE TCC_PUSH_A
            "どうやらそちらにも" TCC_NEWLINE
            "有能\な軍師がいるようだが。。。" TCC_NEWLINE
            "こちらだって負けてはいない。"  TCC_NEWLINE TCC_PUSH_A
            "頼んだぞ、ルフレ！" TCC_NEWLINE
            "お前の策で俺たち自警団を、" TCC_NEWLINE
            "勝ちに導いてくれ！" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

        [TEXT_CHAP_22_ED] = TCC_OPEN_RIGHT
            "すまなかった、アルフォンス王子。。。" TCC_NEWLINE
            "どうやら俺たちはだまされていたらしい。" TCC_NEWLINE TCC_PUSH_A
            "侵略者はエンブラ帝国軍のほうで、" TCC_NEWLINE
            "特務機関は俺たちを" TCC_NEWLINE
            "助けに来てくれたんだな。" TCC_NEWLINE TCC_PUSH_A
            "無礼をどうか許してくれ。" TCC_NEWLINE
            "そして、ありがとう。" TCC_NEWLINE
            "この地を解放してくれて。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE
            TCC_OPEN_LEFT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
            "「覚せいの異界」。。。" TCC_NEWLINE
            "何とか解放できたね。" TCC_NEWLINE
            TCC_TACTICIAN_NAME "のおかげだ。" TCC_NEWLINE TCC_PUSH_A
            "君の指揮は、経験を重ねるごとに" TCC_NEWLINE
            "迷いのない確かなものになっていく。。。" TCC_NEWLINE
            "本当に心強いよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
            TCC_LOAD_FACE PORTRAIT_SHARENA
            "指揮といえば。。。" TCC_NEWLINE
            "さっきの軍師、ちょっと似てましたよね。" TCC_NEWLINE
            TCC_TACTICIAN_NAME "さんに。" TCC_NEWLINE TCC_PUSH_A
            "なんかこう、雰囲気とかがそっくりでした。" TCC_NEWLINE
            "わたしが愛するのはもちろん断然、" TCC_NEWLINE
            TCC_TACTICIAN_NAME "さんですが！" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_MID_LEFT
            TCC_LOAD_FACE PORTRAIT_ANNA
            "まあこんなに沢山異界があるのだもの。" TCC_NEWLINE
            "似ている人が１人や２人。。。いえ、" TCC_NEWLINE
            "５０人や１００人いても不思議じゃないわ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
            "多すぎです、アンナ隊長。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_MID_LEFT
            "あら、そうかしら？" TCC_NEWLINE
            "とにかく、今回も一件落着ね。" TCC_NEWLINE
            "アスク王国に帰還を。。。" TCC_NEWLINE TCC_PUSH_A
            "。。。！？" TCC_NEWLINE
            "大変だわ、みんな。" TCC_NEWLINE
            "たった今、隊員から連絡が入ったわ。" TCC_NEWLINE TCC_PUSH_A
            "「紋章の異界」の扉が。。。" TCC_NEWLINE
            "エンブラ帝国軍に襲撃されているの！" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
            "なんだって！？" TCC_NEWLINE
            "まさか奴ら、また英雄マルスを狙って。。。！？" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

    [TEXT_CHAP_23_OP] = TCC_OPEN_RIGHT
        "。。。来たか。" TCC_NEWLINE TCC_PUSH_A
        "お前たちに恨みはないが、" TCC_NEWLINE
        "雇われた以上、仕事は果たす。" TCC_NEWLINE TCC_PUSH_A
        "かわいそうだが。。。" TCC_NEWLINE
        "死んでもらう。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE,

    [TEXT_CHAP_23_ED] = TCC_OPEN_RIGHT
        "。。。やるな。。。" TCC_NEWLINE
        "あの男とどちらが上か。。。" TCC_NEWLINE TCC_PUSH_A
        "ふっ。。。面白い。" TCC_NEWLINE
        "また会おう。いずれ、な。。。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE,

    [TEXT_CHAP_27_OP] = TCC_OPEN_LEFT
        "あっ。。。" TCC_NEWLINE
        "あなたたちが、" TCC_NEWLINE
        "ヴェロニカの言ってた悪い人？" TCC_NEWLINE TCC_PUSH_A
        "ヤーっ、おねがい、来ないで！" TCC_NEWLINE
        "それ以上近付いたら。。。" TCC_NEWLINE TCC_PUSH_A
        "チキ、手加減できないの。" TCC_NEWLINE
        "あなたたちが、" TCC_NEWLINE
        "大変なことになっちゃう。。。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE,

    [TEXT_CHAP_27_ED] = TCC_OPEN_LEFT
        "やられちゃった。。。" TCC_NEWLINE
        "でも、ありがとう！" TCC_NEWLINE
        "これでチキ、もとに戻れるの。" TCC_NEWLINE TCC_PUSH_A
        "もう無理やり戦わなくても" TCC_NEWLINE
        "よくなったの。。。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE
        TCC_OPEN_RIGHT
        TCC_LOAD_FACE PORTRAIT_ANNA
        "ふうっ、お疲れさま。" TCC_NEWLINE
        "無事に任務を果たせたわ。" TCC_NEWLINE
        "今回の狙いはマルスではなかったようね。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_LEFT
        TCC_LOAD_FACE PORTRAIT_ALFONSE
        "「紋章の異界」は以前も解放した。" TCC_NEWLINE
        "けれど扉が開いている限り、" TCC_NEWLINE
        "奴等は何度も同じ異界に攻め込んでくる" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_MID_RIGHT
        TCC_LOAD_FACE PORTRAIT_SHARENA
        "もちろん特務機関は、" TCC_NEWLINE
        "扉の警護もしているんですよ？" TCC_NEWLINE
        "でも、存在する扉の数はぼうだいで。。。" TCC_NEWLINE TCC_PUSH_A
        "その上、エンブラ帝国軍は" TCC_NEWLINE
        "いつどこに攻め込んでくるかわかりません。" TCC_NEWLINE TCC_PUSH_A
        "私たち王族が扉を閉める力さえ" TCC_NEWLINE
        "持っていればいいんですけど。。。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_LEFT
        "両国の力は二つで一つ。" TCC_NEWLINE
        "僕たちが扉を閉める力を持つとしたら、" TCC_NEWLINE
        "向こうは扉を開く力を持つことになる。" TCC_NEWLINE TCC_PUSH_A
        "そうしたらエンブラ帝国軍は" TCC_NEWLINE
        "僕たちが閉める扉を、" TCC_NEWLINE
        "何度も開きにくることになるだろうね。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_MID_RIGHT
        "ううっ、それはそれで厄介です。。。！" TCC_NEWLINE
        "というか今より大変かもしれません。" TCC_NEWLINE
        "閉じてる扉でも油断できなくなりますから。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_RIGHT
        "片方の国が両方の力を持てない以上、" TCC_NEWLINE
        "協力しないことにはこの戦いは" TCC_NEWLINE
        "終わらないということね。" TCC_NEWLINE TCC_PUSH_A
        "。。。さて、この前の陽動を考えると、" TCC_NEWLINE
        "他の扉が襲撃されている可能\性もあるわ。" TCC_NEWLINE
        "念のため、見回りをしておきましょう！" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE,

    [TEXT_CHAP_28_OP] = TCC_OPEN_FAR_RIGHT
        "なに。。。？" TCC_NEWLINE
        "この地が異界の軍勢に" TCC_NEWLINE
        "支配されているだと？" TCC_NEWLINE TCC_PUSH_A
        "馬鹿を言え。" TCC_NEWLINE
        "この白夜王国は女王の力により" TCC_NEWLINE
        "悪しき者の侵入から守られている。" TCC_NEWLINE TCC_PUSH_A
        "どうやってここまで" TCC_NEWLINE
        "たどり着いたかは知らんが。。。" TCC_NEWLINE
        "貴様らは俺たちきょうだいが討つ！" TCC_NEWLINE TCC_PUSH_A,

    [TEXT_CHAP_28_ED] = TCC_OPEN_FAR_RIGHT
        "まさか、これほどの力とは。。。" TCC_NEWLINE
        "皆、態勢を整えて" TCC_NEWLINE
        "再度迎え撃つぞ！" TCC_NEWLINE TCC_PUSH_A
        "民たちのためにも、" TCC_NEWLINE
        "この白夜王国。。。" TCC_NEWLINE
        "落とさせてなるものか！" TCC_NEWLINE TCC_PUSH_A,

    [TEXT_CHAP_32_OP] = TCC_OPEN_LEFT
        "よくここまでたどり着いたな。" TCC_NEWLINE
        "我が白夜軍。。。そして" TCC_NEWLINE
        "きょうだいたちは敗れたということか。" TCC_NEWLINE TCC_PUSH_A
        "だが。。。ここは通さん。" TCC_NEWLINE
        "この命に代えても、" TCC_NEWLINE
        "貴様らを止めてみせよう！" TCC_NEWLINE TCC_PUSH_A
        "我が名は白夜王国第一の王子、" TCC_NEWLINE
        "リョウマ！！" TCC_NEWLINE
        "軍の将よ。。。一騎討ちを所望する！" TCC_NEWLINE TCC_PUSH_A,

    [TEXT_CHAP_32_ED] = TCC_OPEN_LEFT
        "この清清しい感じ。。。どういうことだ？" TCC_NEWLINE
        "お前たちの言うとおり、" TCC_NEWLINE
        "俺たちは何者かに洗脳されていたのか。" TCC_NEWLINE TCC_PUSH_A
        "お前たちが助けてくれたのだな、この国を、" TCC_NEWLINE
        "きょうだいや。。。臣下たちを。" TCC_NEWLINE
        "ありがとう。。。" TCC_NEWLINE TCC_PUSH_A
        "そして、すまなかった。" TCC_NEWLINE
        "悪しき者から解放してくれたこと、" TCC_NEWLINE
        "恩に着るぞ。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_RIGHT
        TCC_LOAD_FACE PORTRAIT_ANNA
        "おつかれさま。" TCC_NEWLINE
        "「白夜の異界」、" TCC_NEWLINE
        "無事に解放できたわね！" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_LEFT
        TCC_LOAD_FACE PORTRAIT_ALFONSE
        "一騎打ちに肝を冷やしたな。。。" TCC_NEWLINE
        "壁を壊せたからよかったけど、" TCC_NEWLINE
        "単独での戦闘はできれば避けたいよ。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_MID_LEFT
        TCC_LOAD_FACE PORTRAIT_SHARENA
        "ほんとですよーっ！" TCC_NEWLINE
        "あんな風に分断されて、" TCC_NEWLINE
        "そのまま会えなくなったらって思うと。。。" TCC_NEWLINE TCC_PUSH_A
        "そう思うと、たまらないです。" TCC_NEWLINE
        "あのとき。。。" TCC_NEWLINE
        "。。。サガリアさんのときみたいに。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_LEFT
        "。。。。。。" TCC_NEWLINE
        "そうだね。" TCC_NEWLINE
        "僕も少し、それを思い出したよ。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_RIGHT
        "。。。二人とも、" TCC_NEWLINE
        "その話は控えるように言ったでしょう。" TCC_NEWLINE
        "私達はできる限りのことをしたわ。" TCC_NEWLINE TCC_PUSH_A
        "。。。ああ、" TCC_TACTICIAN_NAME "、" TCC_NEWLINE
        "ごめんなさいね。" TCC_NEWLINE
        "あなたにも言っておくべきかもしれないわ。" TCC_NEWLINE TCC_PUSH_A
        "実は。。。私たちの隊には昔、" TCC_NEWLINE
        "もう一人の隊員がいたの。" TCC_NEWLINE
        "名前はザカリア。" TCC_NEWLINE TCC_PUSH_A
        "屈強な青年で、とても頼りになる子だった。" TCC_NEWLINE
        "でも、ある任務がきっかけで" TCC_NEWLINE
        "ザカリアは行方不明になってしまったわ。" TCC_NEWLINE TCC_PUSH_A
        "私達はずっと。。。" TCC_NEWLINE
        "彼を探しているのよ。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE,

    [TEXT_CHAP_33_OP] = TCC_OPEN_FAR_LEFT
        "あっ、来たわね。あなたたちが" TCC_NEWLINE
        "エリウッド様が言ってた異界の英雄？" TCC_NEWLINE
        "ふーん、なかなか強そうじゃない。" TCC_NEWLINE TCC_PUSH_A
        "でも、残念ね。" TCC_NEWLINE
        "このセーラ様と下僕たちに" TCC_NEWLINE
        "かなうはずないんだから！" TCC_NEWLINE TCC_PUSH_A
        TCC_CLOSE_FAST,

    [TEXT_CHAP_33_ED] = TCC_OPEN_FAR_LEFT
        "いたた。。。" TCC_NEWLINE
        "ちょっと！ひどいじゃない！" TCC_NEWLINE
        "私が傷ついたらかわいそうでしょ！" TCC_NEWLINE TCC_PUSH_A
        "私はこれで退いてあげるけど、" TCC_NEWLINE
        "エリウッド様たちはもっと強いんだから。" TCC_NEWLINE
        "覚えてなさいよね！" TCC_NEWLINE TCC_PUSH_A
        TCC_CLOSE_FAST,

    [TEXT_CHAP_37_OP] = TCC_OPEN_LEFT
        "僕はフェレ侯公子エリウッド。" TCC_NEWLINE
        "契約に基づき、" TCC_NEWLINE
        "君たちの相手を務めさせてもらうよ。" TCC_NEWLINE TCC_PUSH_A
        "ロイ？" TCC_NEWLINE
        "ああ、君たちが戦ったロイは僕の息子だよ。" TCC_NEWLINE
        "僕はロイほどの戦いの才はないけれど。。。" TCC_NEWLINE TCC_PUSH_A
        "けど、全くの無策と言うわけでもない。" TCC_NEWLINE
        "では、始めようか。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLOSE_FAST,

    [TEXT_CHAP_37_ED] = TCC_OPEN_LEFT
        "やはり、強いね。。。" TCC_NEWLINE
        "ありがとう、これで" TCC_NEWLINE
        "僕たちは契約から解放された。" TCC_NEWLINE TCC_PUSH_A
        "いつか。。。君たちと共にいられる" TCC_NEWLINE
        "日が来ることを願ってるよ。" TCC_NEWLINE
        "その時は、ロイも一緒にね。。。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_RIGHT
        TCC_LOAD_FACE PORTRAIT_ANNA
        "「烈火の異界」、解放できたわね。" TCC_NEWLINE
        "みんな、よくやってくれたわ。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_LEFT
        TCC_LOAD_FACE PORTRAIT_SHARENA
        "。。。あれ？" TCC_NEWLINE
        TCC_TACTICIAN_NAME"さん。。。？" TCC_NEWLINE
        "黙り込んでどうしたんですか？" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_RIGHT
        "もしかして、この前の話が気になるの？" TCC_NEWLINE
        "行方不明になった隊員。。。" TCC_NEWLINE
        "ザカリアのこと。" TCC_NEWLINE TCC_PUSH_A
        "。。。そう。じゃあ少し話しましょうか。" TCC_NEWLINE
        "彼は貴族の青年でね、" TCC_NEWLINE
        "アルフォンスとシャロンの幼馴染だったの。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_MID_RIGHT
        TCC_LOAD_FACE PORTRAIT_ALFONSE
        "ああ。明るくて優しくて、" TCC_NEWLINE
        "腕のいい槍使いだった。。。" TCC_NEWLINE
        "とても信頼していた仲間だった。" TCC_NEWLINE TCC_PUSH_A
        "少し前。。。僕たちは二手に分かれて" TCC_NEWLINE
        "単独で異界の扉の偵察に出掛けたんだ。" TCC_NEWLINE
        "その方が効率的だからって。。。" TCC_NEWLINE TCC_PUSH_A
        "でも、ザカリアは帰ってこなかった。" TCC_NEWLINE
        "彼が偵察に行った異界の扉は" TCC_NEWLINE
        "ヴェロニカ皇女によって閉じられ、" TCC_NEWLINE TCC_PUSH_A
        "中に閉じ込められてしまったんだ。" TCC_NEWLINE
        "王族でないものは、内側から扉を開けない。" TCC_NEWLINE
        "僕はすぐに扉を開いて彼を探したけど。。。" TCC_NEWLINE TCC_PUSH_A
        "いくら探しても結局、" TCC_NEWLINE
        "見つけることはできなかった。" TCC_NEWLINE TCC_PUSH_A
        "彼が閉じ込められたのは「覚せいの異界」。" TCC_NEWLINE
        "そうだね。。。次はもう一度、" TCC_NEWLINE
        "あの場所に行ってみてもいいかもしれない。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE,

    [TEXT_CHAP_38_OP] = TCC_OPEN_FAR_LEFT
        "君たちは何者だい？" TCC_NEWLINE
        "異界から来た、特務機関。。。？" TCC_NEWLINE
        "なんだか怪しいな。" TCC_NEWLINE TCC_PUSH_A
        "悪いけど、ここを通すわけにはいかないよ。" TCC_NEWLINE
        "クロムがいなくたって、" TCC_NEWLINE
        "僕一人でやってみせ。。。" TCC_NEWLINE TCC_PUSH_A
        "。。。あれ、サーリャもいたのかい？" TCC_NEWLINE
        "ああ。。。また僕の後をつけてたんだね。。。" TCC_NEWLINE
        "まあいい、君も力を貸してくれ！" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE TCC_CLOSE_FAST,

    [TEXT_CHAP_38_ED] = TCC_OPEN_FAR_LEFT
        "僕のさくを破るなんて。。。" TCC_NEWLINE
        "そちらの軍師もやるようだね。" TCC_NEWLINE TCC_PUSH_A
        "でも、これで終わりはしないさ。" TCC_NEWLINE
        "僕の策も仲間も、" TCC_NEWLINE
        "まだまだ尽きてはいないよ！" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE TCC_CLOSE_FAST,

    [TEXT_CHAP_42_OP] = TCC_OPEN_RIGHT
        "特務機関。。。" TCC_NEWLINE
        "ルフレさんの言っていた通り、" TCC_NEWLINE
        "一筋縄ではいかない相手のようですね。" TCC_NEWLINE TCC_PUSH_A
        "特に後方に控えている、" TCC_NEWLINE
        TCC_TACTICIAN_NAME"という軍師が"TCC_NEWLINE
        "なかなかの切れ者だとか。" TCC_NEWLINE TCC_PUSH_A
        "ですが負けはしませんよ。。。" TCC_NEWLINE
        "お父様の力を借りるまでもありません、" TCC_NEWLINE
        "私たちだけで片付けて見せます！" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE TCC_CLOSE_FAST,

    [TEXT_CHAP_42_ED] = TCC_OPEN_RIGHT
        "誤解をしてごめんなさい。。。" TCC_NEWLINE
        "あなたたちは、私たちを解放するために" TCC_NEWLINE
        "戦ってくださっていたのですね。" TCC_NEWLINE TCC_PUSH_A
        "。。。え？探している人がいるのですか？" TCC_NEWLINE
        "ザカリアさんという槍使い。。。" TCC_NEWLINE
        "いいえ、お見かけしたことはありません。" TCC_NEWLINE TCC_PUSH_A
        "ですが大切な人がいなくなる辛さは、" TCC_NEWLINE
        "私もよくわかります。。。" TCC_NEWLINE
        "早く再会できるといいですね。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_LEFT
        TCC_LOAD_FACE PORTRAIT_ALFONSE
        "やはり見つからなかったか。" TCC_NEWLINE
        "ザカリア。。。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_RIGHT
        TCC_LOAD_FACE PORTRAIT_SHARENA
        "ううっ。。。ザカリアさん。。。" TCC_NEWLINE
        "どこにいっちゃったんでしょう。。。" TCC_NEWLINE
        "私の槍の師匠だったのに。。。" TCC_NEWLINE TCC_PUSH_A
        "強くなったねって、" TCC_NEWLINE
        "いつかそう言って褒めてもらいたかったのに" TCC_NEWLINE
        "もう叶わないんでしょうか。。。！" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_MID_RIGHT
        TCC_LOAD_FACE PORTRAIT_ANNA
        "。。。。。。" TCC_NEWLINE
        "泣くのはやめなさい、シャロン。" TCC_NEWLINE
        "まだ任務中だということを忘れたの？" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_RIGHT
        "。。。！" TCC_NEWLINE
        "す、すみません、アンナ隊長。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_MID_RIGHT
        "アルフォンスも。落ち込むのはいいけど、" TCC_NEWLINE
        "ザカリアが帰ってきた時に" TCC_NEWLINE
        "そんな情けない姿を見せるつもり？" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_LEFT
        "すまない。。。" TCC_NEWLINE TCC_PUSH_A
        TCC_OPEN_MID_RIGHT
        "もし責任を感じているのならお門違いよ。" TCC_NEWLINE
        "任務中は何があっても、" TCC_NEWLINE
        "例え死んだとしても責任は自分自身に。。。" TCC_NEWLINE TCC_PUSH_A
        "そして、隊長である私にあるの。" TCC_NEWLINE
        "あなたたちはただ目の前にある" TCC_NEWLINE
        "任務に集中して。" TCC_NEWLINE TCC_PUSH_A
        "さあ、帰還するわよ。" TCC_NEWLINE
        "今日はだめでもいつか、" TCC_NEWLINE
        "また彼に会えると信じましょう。" TCC_NEWLINE TCC_PUSH_A
        TCC_CLEAR_FACE,

       [TEXT_CHAP_43_OP] = TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_ANNA
           "大変よ、みんな！" TCC_NEWLINE TCC_PUSH_A
           "エンブラ帝国軍が英雄を引き連れて" TCC_NEWLINE
           "アスク王国領内に侵攻してきたわ！" TCC_NEWLINE TCC_PUSH_A
           "情報によると、" TCC_NEWLINE
           "エンブラ軍の英雄は" TCC_NEWLINE
           "複数の異界から集められているみたいなの。" TCC_NEWLINE TCC_PUSH_A
           "「紋章の異界」、「封印の異界」。。。" TCC_NEWLINE
           "それから「烈火の異界」ね。" TCC_PUSH_A
           TCC_OPEN_RIGHT
           TCC_LOAD_FACE PORTRAIT_ALFONSE
           "紋章、封印、烈火。。。" TCC_NEWLINE
           "どれも最近支配を受けた異界だ。" TCC_NEWLINE
           "無事に解放したと思っていたのに。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_MID_RIGHT
           TCC_LOAD_FACE PORTRAIT_SHARENA
           "むむむ。。。" TCC_NEWLINE
           "エンブラ帝国軍の奴らーっ！" TCC_NEWLINE
           "裏で動いていたんですねっ！" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "英雄たちは王都に向かっているわ。" TCC_NEWLINE
           "このままでは民たちが危険よ。" TCC_NEWLINE
           "一刻も早く出動しましょう！" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_FAR_FAR_LEFT
           "貴様らがヴェロニカの言う邪魔者か。" TCC_NEWLINE
           "ふん。。。この程度の連中とはな。" TCC_NEWLINE TCC_PUSH_A
           "マケドニア王が" TCC_NEWLINE
           "わざわざ出向いてやったのだ。" TCC_NEWLINE
           "俺を失望させるなよ。" TCC_NEWLINE TCC_PUSH_A
           TCC_CLEAR_FACE TCC_CLOSE_FAST,

       [TEXT_CHAP_43_ED] = TCC_OPEN_FAR_FAR_LEFT
           "俺を破るか。。。" TCC_NEWLINE
           "気に入らぬが、認めてやろう。" TCC_NEWLINE
           "貴様らは確かに英雄の器。。。" TCC_NEWLINE TCC_PUSH_A
           "先へ進むがいい。" TCC_NEWLINE
           "俺に勝った以上。。。" TCC_NEWLINE
           "無様な敗北は許さんぞ。" TCC_NEWLINE TCC_PUSH_A
           TCC_CLEAR_FACE TCC_CLOSE_FAST,

       [TEXT_CHAP_46_OP] = TCC_OPEN_RIGHT
           TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
           "。。。退け。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_ALFONSE
           "君は、この前の。。。！" TCC_NEWLINE
           "やはりエンブラ側の者だったか。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_RIGHT
           "私はエンブラの人間ではない。。。" TCC_NEWLINE
           "だが、お前たちの味方でもない。" TCC_NEWLINE TCC_PUSH_A
           "もう一度言おう。。。" TCC_NEWLINE
           "おとなしく退け。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "悪いが、退くわけにはいかない。" TCC_NEWLINE
           "邪魔するつもりなら、" TCC_NEWLINE
           "力づくでも通してもらう！" TCC_NEWLINE TCC_PUSH_A
           TCC_CLOSE_FAST,

       [TEXT_CHAP_46_ED] = TCC_OPEN_RIGHT
           TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
           "くっ。。。これでは戦えんな。。。" TCC_NEWLINE
           "特務機関の者たちよ。。。" TCC_NEWLINE
           "英雄の動きにだまされるな。" TCC_NEWLINE TCC_PUSH_A
           "エンブラ帝国軍の本当の狙いは、" TCC_NEWLINE
           "王都への侵攻ではなく。。。" TCC_NEWLINE
           "召喚の遺跡の破壊だ。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_ALFONSE
           "え。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_RIGHT
           "その召喚師の能\力を封じること。。。" TCC_NEWLINE
           "それがヴェロニカ皇女の目的だ。" TCC_NEWLINE
           "わかったら。。。遺跡に向え。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "教えてくれるのか。。。？" TCC_NEWLINE
           "どうして。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_RIGHT
           "。。。。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_CLEAR_FACE
           TCC_LOAD_FACE PORTRAIT_ANNA
           "あ。。。待ちなさい！！" TCC_NEWLINE
           "。。。逃げられてしまったわね。" TCC_NEWLINE TCC_PUSH_A
           "どうするの、アルフォンス。" TCC_NEWLINE
           "罠ということも考えられるわよ。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "。。。。。。" TCC_NEWLINE
           "。。。遺跡に向かおう。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_MID_LEFT
           TCC_LOAD_FACE PORTRAIT_SHARENA
           "お兄様！？" TCC_NEWLINE
           "でも。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "あの男は嘘を言っていない。" TCC_NEWLINE
           "そんな気がするんだ。" TCC_NEWLINE
           "行こう、"TCC_TACTICIAN_NAME"！" TCC_NEWLINE TCC_PUSH_A
           TCC_CLOSE_FAST,

       [TEXT_CHAP_47_OP] = TCC_OPEN_MID_RIGHT
           TCC_LOAD_FACE PORTRAIT_VERONICA
           "あなたたち。。。" TCC_NEWLINE
           "どうしてここがわかったの。。。" TCC_NEWLINE TCC_PUSH_A
           "。。。まあいいわ。" TCC_NEWLINE
           "そんなに私と遊びたいのなら、" TCC_NEWLINE
           "観迎してあげる。。。" TCC_NEWLINE TCC_PUSH_A
           "それに、遺跡を壊すよりも。。。" TCC_NEWLINE
           "。。。"TCC_TACTICIAN_NAME"。"TCC_NEWLINE
           "あなたを殺したほうが早いものね。" TCC_NEWLINE TCC_PUSH_A
           TCC_CLOSE_FAST,

       [TEXT_CHAP_47_ED] = TCC_OPEN_MID_RIGHT
           TCC_LOAD_FACE PORTRAIT_VERONICA
           "どうして。。。" TCC_NEWLINE
           "いつも負けちゃうの。。。" TCC_NEWLINE
           "ずるい。。。" TCC_NEWLINE TCC_PUSH_A
           "あなたたちばかりずるいわ。。。" TCC_NEWLINE
           "英雄に、召喚師に。。。" TCC_NEWLINE
           "豊かな国に。。。" TCC_NEWLINE TCC_PUSH_A
           "これ以上何が欲しいの。。。" TCC_NEWLINE
           "私には。。。" TCC_NEWLINE
           "なんにもないのに。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_CLEAR_FACE
           TCC_OPEN_FAR_LEFT
           TCC_LOAD_FACE PORTRAIT_ANNA
           "。。。撤退したようね。" TCC_NEWLINE
           "でも、これで終わるとは思えないわ。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_MID_LEFT
           TCC_LOAD_FACE PORTRAIT_SHARENA
           "どうしてこんなことになったんでしょう。。。" TCC_NEWLINE
           "エンブラの先代皇帝が亡くなった時、" TCC_NEWLINE
           "もう戦争は終わるって言われてたのに。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_ALFONSE
           "先代皇帝。。。ヴェロニカ皇女の父上は" TCC_NEWLINE
           "英雄やアスク王国を支配することを" TCC_NEWLINE
           "画策していたんだ。" TCC_NEWLINE TCC_PUSH_A
           "それも自国を豊かにしたいがため。。。" TCC_NEWLINE
           "帝国内の人気は圧倒的だった。" TCC_NEWLINE
           "亡くなった時は後を追う民までいたほどの。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_FAR_LEFT
           "で、帝位を継いだのが皇帝の後妻。" TCC_NEWLINE
           "ヴェロニカ皇女は前妻との娘だから、" TCC_NEWLINE
           "女帝と皇女と血の繋がりはないのよ。" TCC_NEWLINE TCC_PUSH_A
           "女帝は支配的な性格ではなかったから" TCC_NEWLINE
           "異界やアスクへの侵攻もなくなって、" TCC_NEWLINE
           "束の間の平和が訪レたわ。" TCC_NEWLINE TCC_PUSH_A
           "数年前、ヴェロニカ皇女が突然" TCC_NEWLINE
           "異界を支配し。。。かつてのように" TCC_NEWLINE
           "アスク王国に侵攻を始めるまではね。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "民も、国の要人たちも。。。女帝ではなく" TCC_NEWLINE
           "先代皇帝の血と意志を継いだ" TCC_NEWLINE
           "ヴェロニカ皇女を支援していると聞くよ。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_MID_LEFT
           "狙いはアスク王国の支配。。。" TCC_NEWLINE
           "本当にそうでしょうか。" TCC_NEWLINE
           "私にはただ、寂しいだけに見えますが。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "例えそうだとしても、" TCC_NEWLINE
           "アスク王国に侵略していい" TCC_NEWLINE
           "理由にはならないよ。" TCC_NEWLINE TCC_PUSH_A
           TCC_TACTICIAN_NAME"。。。"TCC_NEWLINE
           "きっとこれからも厳しい戦いが待つだろう。" TCC_NEWLINE
           "けれど君は、僕たちが守ってみせる。" TCC_NEWLINE TCC_PUSH_A
           "だからこれからも僕たちと。。。" TCC_NEWLINE
           "そして英雄たちと共に、" TCC_NEWLINE
           "戦ってくれ。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_FAR_LEFT
           "さあ、それじゃみんな。" TCC_NEWLINE
           "お城に戻りましょうか。" TCC_NEWLINE TCC_PUSH_A
           "。。。！？あれは。。。！" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_MID_RIGHT
           TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
           "。。。。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "君は、さっきの。。。" TCC_NEWLINE TCC_PUSH_A
           "礼を言っておくよ。" TCC_NEWLINE
           "君のおかけで遺跡を無事に。。。" TCC_NEWLINE
           TCC_OPEN_MID_RIGHT
           "覚せいの異界にいる英雄に聞いた。" TCC_NEWLINE
           "貴様らは、人を捜しているようだな。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "ザカリアのことかい？" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_MID_RIGHT
           "ああ。" TCC_NEWLINE
           "気の毒だが、そいつはもう戻ってこない。" TCC_NEWLINE
           "。。。潔く諦めろ。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "！！なに。。。！？" TCC_NEWLINE
           "彼の行方を知っているのか！？" TCC_NEWLINE
           "お願いだ、何か知っているのなら。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_MID_RIGHT
           "。。。。。。" TCC_NEWLINE TCC_PUSH_A
           TCC_CLEAR_FACE
           TCC_OPEN_LEFT
           "あ。。。！" TCC_NEWLINE
           "待ってくれ！" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_FAR_LEFT
           "だめよアルフォンス！" TCC_NEWLINE
           "今度こそ罠かもしれないわ！" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "でも。。。！" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_FAR_LEFT
           "落ち着きなさい！" TCC_NEWLINE
           "敵か味方かわからない以上、" TCC_NEWLINE
           "誘いには乗らない方が賢明よ。" TCC_NEWLINE TCC_PUSH_A
           "あの男。。。" TCC_NEWLINE
           "きっとまた私たちに接触してくるわ。" TCC_NEWLINE
           "機が熟すのを待ちましょう。" TCC_NEWLINE TCC_PUSH_A
           TCC_OPEN_LEFT
           "くっ。。。！" TCC_NEWLINE
           "。。。わかったよ。" TCC_NEWLINE TCC_PUSH_A
           "ザカリア。。。" TCC_NEWLINE
           "どうか、無事でいてくれ。。。" TCC_NEWLINE TCC_PUSH_A
           ,

       [TEXT_ITEM_SACRED_SEAL_EMBLA_WARD_NAME] = "エンブラの加護",

       [TEXT_ITEM_SACRED_SEAL_EMBLA_WARD_HELP] = "自身が受けるダメージは０になる",

       [TEXT_ITEM_SACRED_SEAL_MUSPELL_FLAME_NAME] = "ムスペルの炎",

       [TEXT_ITEM_SACRED_SEAL_MUSPELL_FLAME_HELP] = "自身が受けるダメージは０になる",

       [TEXT_CHAP_GOAL_DEFENSE_6_TURNS] = "６ターン防御",

       [TEXT_CHAP_GOAL_DEFENSE_7_TURNS] = "７ターン防御",

       [TEXT_CHAP_GOAL_DEFENSE_10_TURNS] = "１０ターン防御",

       [TEXT_ANNA_JOB_NAME] = "隊長",

       [TEXT_ANNA_JOB_HELP] = "アスク王国特務機関のリーダー",

       [TEXT_BRUNO_JOIN_US] = TCC_OPEN_MID_LEFT
           TCC_LOAD_FACE PORTRAIT_ALFONSE
            TCC_OPEN_MID_RIGHT
            TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
            TCC_OPEN_MID_LEFT
            "ザカリア。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_MID_RIGHT
            "。。。。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_MID_LEFT
            "そうですか。" TCC_NEWLINE
            "とりあえず敵を一掃しましょう！" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

       [TEXT_SUPPORT_CONVERSATION_BRUNO_ALFONSE_TEMP] = TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
            TCC_OPEN_RIGHT
            TCC_LOAD_FACE PORTRAIT_ALFONSE
            "ザカリア。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
            "アルフォンス王子。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_BRUNO_ALFONSE_C] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ALFONSE

            TCC_OPEN_LEFT "アルフォンス、" TCC_NEWLINE "ちょっといいか？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "ブルーノ？" TCC_NEWLINE "どうしたんだ？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "君に謝りたいんだ。" TCC_NEWLINE "あの日、" TCC_NEWLINE "君たちに刃を向けたことを。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "。。。そうか。" TCC_NEWLINE "でも、それは君のせいじゃない。" TCC_NEWLINE "君は呪われていたんだから。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "呪われていたとしても、" TCC_NEWLINE "許されることじゃない。" TCC_NEWLINE "君は僕の友だったのに、" TCC_NEWLINE "僕は君を裏切った。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "友だった？" TCC_NEWLINE "今も友だろう？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "本当に？" TCC_NEWLINE "君は僕を許してくれるのか？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "もちろんだ。" TCC_NEWLINE "君は今、" TCC_NEWLINE "僕たちと一緒に戦ってくれている。" TCC_NEWLINE "それだけで十\分だ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "ありがとう、" TCC_NEWLINE "アルフォンス。" TCC_NEWLINE "君の言葉に救われるよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "いや、僕こそ感謝している。" TCC_NEWLINE "君がいなかったら、" TCC_NEWLINE "僕はもっと苦しんでいただろう。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "苦しんでいる？" TCC_NEWLINE "どういうことだ？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "。。。それはまた今度話そう。" TCC_NEWLINE "今は戦場だからな。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "分かった。" TCC_NEWLINE "では、また後で会おう。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "ああ、そうしよう。" TCC_NEWLINE "気をつけてな。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "君もな。" TCC_NEWLINE TCC_PUSH_A

            TCC_OPEN_LEFT
                TCC_CLEAR_FACE,
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_BRUNO_ALFONSE_B] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ALFONSE

            TCC_OPEN_LEFT "アルフォンス、" TCC_NEWLINE "話があるんだが。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "ブルーノ、" TCC_NEWLINE "どうしたんだ？" TCC_NEWLINE "顔色が悪いぞ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "実は、僕はもうすぐこの世界を" TCC_NEWLINE "去らなければならない。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "え？どういうことだ？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "僕はこの世界に来たときから、" TCC_NEWLINE "呪いの影響で体が蝕まれているんだ。" TCC_NEWLINE "もう長くは持たない。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "そんな。。。" TCC_NEWLINE "でも、何か方法はないのか？" TCC_NEWLINE "治療できないのか？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "残念ながら、" TCC_NEWLINE "この世界には僕を救える力はない。" TCC_NEWLINE "唯一の方法は、" TCC_NEWLINE "僕の故郷に帰ることだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "故郷に帰る？" TCC_NEWLINE "それはどこだ？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "。。。言えない。" TCC_NEWLINE "君にも危険が及ぶかもしれないから。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "危険だとしても、" TCC_NEWLINE "僕は君を見捨てない。" TCC_NEWLINE "君は僕の友だ。" TCC_NEWLINE "一緒に行こう。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "ありがとう、" TCC_NEWLINE "アルフォンス。" TCC_NEWLINE "でも、それはできない。" TCC_NEWLINE "君はこの世界の王子だ。" TCC_NEWLINE "君の居場所はここだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "そんなの関係ない。" TCC_NEWLINE "僕は君を失いたくないんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "。。。ごめんなさい、" TCC_NEWLINE "アルフォンス。" TCC_NEWLINE "でも、これが僕の決断だ。" TCC_NEWLINE "君に幸せになってほしい。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "ブルーノ。。。" TCC_NEWLINE TCC_PUSH_A

            TCC_OPEN_LEFT
                TCC_CLEAR_FACE,
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_CONVERSATION_BRUNO_ALFONSE_A] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ALFONSE

            TCC_OPEN_LEFT "アルフォンス、" TCC_NEWLINE "ちょっと話があるんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "ブルーノ、" TCC_NEWLINE "どうしたの？" TCC_NEWLINE "何か悩んでいることでも？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "いや、悩んでいるというよりは。。。" TCC_NEWLINE "感謝したいことがあるんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "感謝？" TCC_NEWLINE "僕に？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "ああ。" TCC_NEWLINE "君は僕にとって大切な友だ。" TCC_NEWLINE "僕が暗黒の魔力に囚われていた時も、" TCC_NEWLINE "君は僕を見捨てなかった。" TCC_NEWLINE "君は僕を信じてくれた。" TCC_NEWLINE "それがどれだけ僕の心を救ってくれたか、" TCC_NEWLINE "言葉では言い表\せない。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "ブルーノ。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "だから、" TCC_NEWLINE "君に感謝したい。" TCC_NEWLINE "そして、謝りたい。" TCC_NEWLINE "僕は君に多くの苦しみを与えてしまった。" TCC_NEWLINE "君の国を襲ったり、" TCC_NEWLINE "君の仲間を傷つけたり。。。" TCC_NEWLINE "許せないことばかりだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "ブルーノ、" TCC_NEWLINE "それはもう過去のことだ。" TCC_NEWLINE "今はもう大丈夫だよ。" TCC_NEWLINE "僕は君を責めないし、" TCC_NEWLINE "恨んでもいない。" TCC_NEWLINE "君は暗黒の魔力に操られていただけだ。" TCC_NEWLINE "本当の君は優しくて勇敢で賢い人だ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "アルフォンス。。。" TCC_NEWLINE "ありがとう。" TCC_NEWLINE "君の言葉が嘘でないことを祈るよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "嘘じゃないよ。" TCC_NEWLINE "本当だよ。" TCC_NEWLINE "僕は君を信じてるし、" TCC_NEWLINE "応援してる。" TCC_NEWLINE "君が暗黒の魔力から" TCC_NEWLINE "完全に解放される日まで、" TCC_NEWLINE "ずっとそばにいるよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT "ありがとう、" TCC_NEWLINE "アルフォンス。" TCC_NEWLINE "君は本当に素晴らしい友だ。" TCC_NEWLINE "これからもよろしく頼むよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT "こちらこそ、" TCC_NEWLINE "ブルーノ。" TCC_NEWLINE "これからも一緒に戦おうね。" TCC_NEWLINE

            TCC_OPEN_LEFT
                TCC_CLEAR_FACE,
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

       [TEXT_SUPPORT_CONVERSATION_BRUNO_ANNA_TEMP] = TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
            TCC_OPEN_RIGHT
            TCC_LOAD_FACE PORTRAIT_ANNA
            "ザカリア。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
            "アンナ隊長。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

       [TEXT_SUPPORT_CONVERSATION_BRUNO_SHARENA_TEMP] = TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
            TCC_OPEN_RIGHT
            TCC_LOAD_FACE PORTRAIT_SHARENA
            "ザカリア。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
            "シャロン王女。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_CLEAR_FACE,

       [TEXT_JOB_NAME_MAGE_KNIGHT] = "マージナイト",

       [TEXT_JOB_HELP_MAGE_KNIGHT] = "魔法と杖を使う　魔道騎士"TCC_NEWLINE"装備「理・光・闇・杖」",

       [TEXT_OPTION_LANGUAGE] = "言語",

       [TEXT_OPTION_JP] = "日本語",

       [TEXT_OPTION_EN] = "Ｅｎｇｌｉｓｈ",

       [TEXT_OPTION_JP_HELP] = "ゲーム内の言語を日本語に変更する",

       [TEXT_OPTION_EN_HELP] = "Ｃｈａｎｇｅ　ｌａｎｇｕａｇｅ　ｔｏ　Ｅｎｇｌｉｓｈ",

       [TEXT_OPTION_SUMMONER_GENDER] = "マイユニットの性別",

       [TEXT_OPTION_SUMMONER_GENDER_MALE] = "男",

       [TEXT_OPTION_SUMMONER_GENDER_FEMALE] = "女",

       [TEXT_OPTION_SUMMONER_GENDER_MYSTERY] = "謎",

       [TEXT_OPTION_SUMMONER_GENDER_MALE_HELP] = "男性",

       [TEXT_OPTION_SUMMONER_GENDER_FEMALE_HELP] = "女性",

       [TEXT_OPTION_SUMMONER_GENDER_MYSTERY_HELP] = "不明",

       [TEXT_OPTION_SUMMONER_APPEARANCE] = "マイユニットの外見",

       [TEXT_OPTION_SUMMONER_APPEARANCE_1] = "１",

       [TEXT_OPTION_SUMMONER_APPEARANCE_1_HELP] = "外見１",

       [TEXT_OPTION_SUMMONER_APPEARANCE_2] = "２",

       [TEXT_OPTION_SUMMONER_APPEARANCE_2_HELP] = "外見２",

       [TEXT_OPTION_SUMMONER_APPEARANCE_3] = "３",

       [TEXT_OPTION_SUMMONER_APPEARANCE_3_HELP] = "外見３",

       [TEXT_OPTION_SUMMONER_APPEARANCE_4] = "４",

       [TEXT_OPTION_SUMMONER_APPEARANCE_4_HELP] = "外見４",

       [MID_SCENARIO_OPENING_S1601_EN_TEST] = TCC_OPEN_LEFT
              TCC_LOAD_FACE PORTRAIT_MIRABILIS
               TCC_OPEN_RIGHT
               TCC_LOAD_FACE PORTRAIT_MIRABILIS
               "Ｈｉ’ｓ" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_LEFT
               "Ｈｅｌｌｏ" TCC_NEWLINE TCC_PUSH_A
               TCC_CLEAR_FACE
               TCC_OPEN_RIGHT
               TCC_CLEAR_FACE,

       [TEXT_OPTION_RANDOM_MODE] = "ランダムモード",

       [TEXT_OPTION_PSEUDO_RANDOM] = "ギジ",

       [TEXT_OPTION_REAL_RANDOM] = "リアル",

       [TEXT_OPTION_PSEUDO_RANDOM_HELP] = "ギジランダムを使う",

       [TEXT_OPTION_REAL_RANDOM_HELP] = "リアルランダム（乱数をよそくできない）",

       [TEXT_OPTION_TRUE_HIT] = "命中判定",

       [TEXT_OPTION_TRUE_HIT_ON] = "実効命中率",

       [TEXT_OPTION_TRUE_HIT_OFF] = "表\示命中率",

       [TEXT_OPTION_TRUE_HIT_ON_HELP] = "命中判定の際に乱数が２つ使用される",

       [TEXT_OPTION_TRUE_HIT_OFF_HELP] = "命中判定の際に乱数が１つ使用される",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL] = "ザコ敵の奥義",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_NONE] = "無",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_WEAK] = "弱",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_STRONG] = "強",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_MIXED] = "優",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_NONE_HELP] = "ザコ敵は奥義を持ってない",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_WEAK_HELP] = "ザコ敵は弱い奥義を持っている",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_STRONG_HELP] = "ザコ敵は強い奥義を持っている",

       [TEXT_OPTION_ENEMY_SPECIAL_SKILL_LEVEL_MIXED_HELP] = "ザコ敵は全ての奥義を持っている",

       [TEXT_JOB_NAME_HALBERDIER] = "ハルバーディア",

       [TEXT_JOB_HELP_HALBERDIER] = "槍闘士　ソ\ルジャーが昇格する",

       [ITEM_NAME_IRON_DAGGER] = "てつの暗器",

       [ITEM_HELP_IRON_DAGGER] = "戦闘後に敵の守備、魔防ー３",

       [ITEM_NAME_STEEL_DAGGER] = "はがねの暗器",

       [ITEM_HELP_STEEL_DAGGER] = "戦闘後に敵の守備、魔防ー５",

       [ITEM_NAME_SILVER_DAGGER] = "ぎんの暗器",

       [ITEM_HELP_SILVER_DAGGER] = "戦闘後に敵の守備、魔防ー７",

       [ITEM_NAME_POISON_DAGGER] = "秘毒の暗器",

       [ITEM_HELP_POISON_DAGGER] = "歩行特効。歩行なら、敵の守備、魔防ー６",

       [ITEM_NAME_SMOKE_DAGGER] = "紫えんの暗器",

       [ITEM_HELP_SMOKE_DAGGER] = "敵の周囲２マスの敵の守備、魔防ー６",

       [ITEM_NAME_ROGUE_DAGGER] = "盗賊の暗器",

       [ITEM_HELP_ROGUE_DAGGER] = "敵の守備、魔防ー５、自分の守備、魔防＋５",

       [720] = "死の皇女専用",

       [ITEM_NAME_SACRED_SEAL_DEFLECT_MELEE] = "連撃防御剣槍斧",

       [ITEM_HELP_SACRED_SEAL_DEFLECT_MELEE] = "剣、槍、斧の敵から連続して攻撃を受けた時、２回目以降のダメージを８割軽減",

       [ITEM_NAME_SACRED_SEAL_DEFLECT_MISSILE] = "連撃防御弓暗器",

       [ITEM_HELP_SACRED_SEAL_DEFLECT_MISSILE] = "弓、暗器の敵から連続して攻撃を受けた時、２回目以降のダメージを８割軽減",

       [ITEM_NAME_SACRED_SEAL_DEFLECT_MAGIC] = "連撃防御魔道",

       [ITEM_HELP_SACRED_SEAL_DEFLECT_MAGIC] = "魔法の敵から連続して攻撃を受けた時、２回目以降のダメージを８割軽減",

       [CONVO_HELBINDI_JOIN] = TCC_OPEN_LEFT TCC_LOAD_FACE PORTRAIT_YLGR
           "ハイハイ" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_RIGHT TCC_LOAD_FACE PORTRAIT_HELBINDI
               "クソ\ガキ？" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_LEFT
               "ガキではない" TCC_NEWLINE
               "私はユルグ" TCC_NEWLINE
               "なぜここに？" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_RIGHT
               "俺は敗れた後で、貧民街の人々は皆殺された" TCC_NEWLINE
               "アイツもなくなった" TCC_NEWLINE TCC_PUSH_A
               "妹がいない俺は" TCC_NEWLINE
               "戦う理由を持ってないから" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_LEFT
               "ひとりじゃ寂しいから一緒に来てよ" TCC_NEWLINE
               "これからあなたは私たちの大切な家族だ" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_RIGHT
               "ガキを守るのは面倒だけど" TCC_NEWLINE
               "あの王様を討つなら俺も同行する" TCC_NEWLINE
               "まずは目の前の敵をぶっ殺す！" TCC_NEWLINE TCC_PUSH_A,

       [TEXT_GENERIC_HEL_NAME] = "死の兵士",

       [TEXT_GENERIC_HEL_HELP] = "死の王国ヘルの兵士",

       [TEXT_JOB_NAME_REVANANT] = "マミー",

       [TEXT_JOB_HELP_REVANANT] = "よみがえった亡者　鋭い爪で相手を襲うが、動きは遅い",

       [TEXT_JOB_NAME_BONEWALKER] = "ヘルボーン",

       [TEXT_JOB_HELP_BONEWALKER] = "動き出した骸骨　様々な武器を使って、襲い掛かる",

       [TEXT_JOB_NAME_PHANTOM] = "亡霊戦士",

       [TEXT_JOB_HELP_PHANTOM] = "かつて亡くなった戦士",

       [TEXT_JOB_NAME_UNDEAD_MANAKETE] = "マムクート",

       [TEXT_JOB_HELP_UNDEAD_MANAKETE] = "死してよみがえったマムクート",

       [TEXT_JOB_NAME_GHOST_FIRE] = "鬼火",

       [TEXT_JOB_HELP_GHOST_FIRE] = "亡霊火　空中を浮遊する火の玉",

       [TEXT_JOB_NAME_SKELEMONK] = "スケルトン神官",

       [TEXT_JOB_HELP_SKELEMONK] = "神官の骸骨　様々な魔法を使って、襲い掛かる",

       [TEXT_ITEM_NAME_SHARP_CLAW] = "するどい爪",

       [TEXT_ITEM_NAME_ROTTEN_CLAW] = "くさった爪",

       [TEXT_ITEM_NAME_FETID_CLAW] = "くさった長爪",

       [TEXT_ITEM_NAME_POISON_CLAW] = "どくの爪",

       [TEXT_ITEM_NAME_LETHAL_CLAW] = "もうどくの爪",

       [TEXT_ITEM_NAME_WRETCHED_AIR] = "ふはいのブレス",

       [TEXT_ITEM_HELP_WRETCHED_AIR] = "あらゆるものを腐敗に導く屍竜の息吹",

       [TEXT_ITEM_HELP_SHARP_CLAW] = "鋭利な爪",

       [TEXT_ITEM_HELP_ROTTEN_CLAW] = "腐敗した爪",

       [TEXT_ITEM_HELP_FETID_CLAW] = "腐敗した長い爪",

       [TEXT_ITEM_HELP_POISON_CLAW] = "毒がぬられた爪",

       [TEXT_ITEM_HELP_LETHAL_CLAW] = "毒がぬられた強力な爪",

       [TEXT_JOB_HELP_BISHOP] = "死者に対し絶大な力を発揮する聖職者",

       [TEXT_JOB_NAME_WOLF] = "狼",

       [TEXT_JOB_HELP_WOLF] = "オオカミ　素早い動きと鋭い牙で襲い掛かる",

       [TEXT_ITEM_NAME_FIERY_FANG] = "灼熱の牙",

       [TEXT_ITEM_HELP_FIERY_FANG] = "鋭い牙",

       [TEXT_ITEM_NAME_HELL_FANG] = "焦熱の牙",

       [TEXT_ITEM_HELP_HELL_FANG] = "長く鋭い牙",

       [TEXT_ITEM_NAME_NIGHTMARE_FANG] = "悪夢の牙",

       [TEXT_ITEM_HELP_NIGHTMARE_FANG] = "悪夢の女王の鋭い牙　速さ＋３",

       [TEXT_ITEM_NAME_BREIDABLIK] = "ブレイザブリク",

       [TEXT_ITEM_HELP_BREIDABLIK] = "異世界の神器　"TCC_SUMMONER_NAME"専用",

       [TEXT_CHARACTER_NAME_GENERIC_ELF] = "エルフ兵",

       [TEXT_CHARACTER_HELP_GENERIC_ELF] = "悪夢の国スヴァルトアルフの兵士",

       [TEXT_JOB_NAME_DIVINE_MANAKETE] = "マムクート",

       [TEXT_JOB_HELP_DIVINE_MANAKETE] = "神竜族",

       [TEXT_ITEM_NAME_DIVINE_DRAGONSTONE] = "光のブレス",

       [TEXT_ITEM_HELP_DIVINE_DRAGONSTONE] = "すべてをじょうかする神竜の息吹",

       [TEXT_ITEM_NAME_ARMORED_BOOTS] = "重装のブーツ",

       [TEXT_ITEM_HELP_ARMORED_BOOTS] = "ターン開始時、自身のＨＰが１００パーセントなら、移動＋１（１ターン、重複しない）",

       [TEXT_CHARACTER_NAME_FREYJA] = "フレイヤ",

       [TEXT_CHARACTER_HELP_FREYJA] = "悪夢の国スヴァルトアルフの女王。兄フロージを愛し、兄のすべてを独占したいと望む。",

       [TEXT_CHARACTER_NAME_TAKUMI] = "タクミ",

       [TEXT_CHARACTER_HELP_TAKUMI] = "白夜王国の王子。神器【風神弓】の使い手。自己けんじ欲が強く、ひねくれ屋。",

       [TEXT_ITEM_NAME_FUJIN_YUMI] = "風神弓",

       [TEXT_ITEM_HELP_FUJIN_YUMI] = "飛行特効　タクミ専用　魔防＋３",

       [TEXT_CHARACTER_NAME_FREYR] = "フロージ",

       [TEXT_CHARACTER_HELP_FREYR] = "夢の国アルフの王。夢を司る神で、人々の安らぎを望んでいる。",

       [TEXT_JOB_NAME_STEAM_DRAGON] = "スチームドラゴン",

       [TEXT_JOB_HELP_STEAM_DRAGON] = "魔道かがくを駆使した飛行機動兵器",

       [TEXT_ITEM_NAME_SCALDING_BREATH] = "じょうきのブレス",

       [TEXT_ITEM_HELP_SCALDING_BREATH] = "高温の蒸気",

       [TEXT_CHARACTER_NAME_OTR] = "オッテル",

       [TEXT_CHARACTER_HELP_OTR] = "ニザヴェリル王ファフニールの義理の弟でレギンの兄。兄を崇拝しその野望に加担する。",

       [TEXT_CHARACTER_NAME_FAFNIR] = "ファフニール",

       [TEXT_CHARACTER_HELP_FAFNIR] = "ニザヴェリル王国の王。一兵士から成り上がった。過去の記憶を失っている。",

       [TEXT_ITEM_SACRED_SEAL_NIOAVELLIR_AXIOM_NAME] = "ニザヴェリルの理",

       [TEXT_ITEM_SACRED_SEAL_NIOAVELLIR_AXIOM_HELP] = "自身が受けるダメージは０になる",

       [TEXT_CHARACTER_NAME_DAGR] = "ダグ",

       [TEXT_CHARACTER_HELP_DAGR] = "ヨトゥン王国の第二王女。ノートの双子の妹。陽気で大らか。好戦的な性格。",

       [TEXT_CHARACTER_NAME_GENERIC_JOTUNHEIMR] = "ヨトゥン兵",

       [TEXT_CHARACTER_HELP_GENERIC_JOTUNHEIMR] = "巨人族の国ヨトゥンの兵士",

       [TEXT_CHARACTER_NAME_NOTT] = "ノート",

       [TEXT_CHARACTER_HELP_NOTT] = "ヨトゥン王国の第一王女。ダグの双子の姉。優雅で美しいものを好む。",

       [TEXT_SUPPORT_AVATAR_TAKUMI]= TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_TAKUMI
               "。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_RIGHT
               TCC_LOAD_FACE PORTRAIT_AVATAR
               "。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_LEFT
               TCC_CLEAR_FACE
               TCC_OPEN_RIGHT
               TCC_CLEAR_FACE,

        [TEXT_SUPPORT_AVATAR_TAKUMI_C] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_AVATAR
                "タクミ、ちょっといいかな？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_TAKUMI
                "ん？何だよ、"TCC_SUMMONER_NAME"。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "君は弓の使い手だよね。" TCC_NEWLINE
                "僕も弓に興味があってさ。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "興味があるだけで" TCC_NEWLINE
                "弓が使えると思ってるのか？" TCC_NEWLINE
                "弓は簡単に扱える武器じゃないぞ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうだろうね。" TCC_NEWLINE
                "だからこそ、" TCC_NEWLINE
                "君に教えてもらいたいんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "教えてもらいたい？" TCC_NEWLINE
                "お前、俺に何か恩でもあるのか？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "恩？" TCC_NEWLINE
                "いや、そういうわけじゃなくて。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "じゃあ何で俺に頼むんだ？" TCC_NEWLINE
                "他に弓の使い手はいくらでもいるだろう。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "確かにそうだけど。。。" TCC_NEWLINE
                "君は特別だと思うんだ。" TCC_NEWLINE
                "弓の扱い方はもちろん、" TCC_NEWLINE
                "戦闘の判断力や気迫も素晴らしい。" TCC_NEWLINE
                "僕は君に憧れてるんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "憧れてる？" TCC_NEWLINE
                "お前、本気で言ってるのか？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "本気だよ。" TCC_NEWLINE
                "僕は君のような弓の使い手になりたいんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "。。。ふん。" TCC_NEWLINE
                "そう言われても困るな。" TCC_NEWLINE
                "俺はお前の師匠になる気はないぞ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうか。。。" TCC_NEWLINE
                "残念だけど、仕方ないね。" TCC_NEWLINE
                "でも、僕は諦めないよ。" TCC_NEWLINE
                "君が教えてくれるまで、" TCC_NEWLINE
                "頑張って練習するよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "。。。まったく、しつこい奴だな。" TCC_NEWLINE
                "。。。分かったよ。" TCC_NEWLINE
                "一回だけな。" TCC_NEWLINE
                "一回だけ、" TCC_NEWLINE
                "弓の基礎を教えてやる。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "本当かい？" TCC_NEWLINE
                "やった！" TCC_NEWLINE
                "ありがとう、タクミ！" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "感謝するなら早く準備しろよ。" TCC_NEWLINE
                "時間がもったいない。" TCC_NEWLINE
                "それに、俺は厳しいぞ。" TCC_NEWLINE
                "泣き言は聞かないからな。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "大丈夫だよ。" TCC_NEWLINE
                "僕は君について行ける自信があるから。" TCC_NEWLINE
                "さあ、行こう！" TCC_NEWLINE TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_AVATAR_TAKUMI_B] =
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_AVATAR
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_TAKUMI
                "おい、"TCC_SUMMONER_NAME"。" TCC_NEWLINE
                "今日の練習はどうだった？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "タクミ、こんにちは。" TCC_NEWLINE
                "今日の練習は。。。" TCC_NEWLINE
                "まあまあかな。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "まあまあ？" TCC_NEWLINE
                "それじゃあダメだぞ。" TCC_NEWLINE
                "もっと自信を持てよ。" TCC_NEWLINE
                "お前は弓の才能\があるんだから。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "そう言ってくれると嬉しいけど。。。" TCC_NEWLINE
                "でも、まだまだ足りないよ。" TCC_NEWLINE
                "君のように的確に狙えないし、" TCC_NEWLINE
                "動きもぎこちないし。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そんなことないぞ。" TCC_NEWLINE
                "お前はすごく上達してる。" TCC_NEWLINE
                "俺が教えたことをしっかり覚えて、" TCC_NEWLINE
                "実践に活かしてる。" TCC_NEWLINE
                "俺はお前の成長を誇りに思うよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "本当？" TCC_NEWLINE
                "ありがとう、タクミ。" TCC_NEWLINE
                "君のおかげで弓に対する情熱が湧いてきたよ。" TCC_NEWLINE
                "君は僕にとって最高の師匠だよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "師匠か。。。" TCC_NEWLINE
                "そんな大それたことを言われても困るな。" TCC_NEWLINE
                "俺はただ、" TCC_NEWLINE
                "お前に弓の楽しさを伝えたかっただけだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "弓の楽しさ。。。" TCC_NEWLINE
                "君は弓が好きなんだね。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "当然だろう。" TCC_NEWLINE
                "弓は俺の命だからな。" TCC_NEWLINE
                "俺は弓があれば何でもできると思ってる。" TCC_NEWLINE
                "敵を倒すのはもちろん、" TCC_NEWLINE
                "仲間を守るのも、" TCC_NEWLINE
                "自分を表\現するのも。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "自分を表\現する？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ああ。" TCC_NEWLINE
                "弓は言葉よりも強いと思うんだ。" TCC_NEWLINE
                "言葉は嘘をつくことができるけど、" TCC_NEWLINE
                "弓は嘘をつかない。" TCC_NEWLINE
                "弓は使う者の心をそのまま反映する。" TCC_NEWLINE
                "だから、" TCC_NEWLINE
                "俺は弓で自分の気持ちを伝えたいんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "なるほど。。。" TCC_NEWLINE
                "君は弓に対して深い思い入れがあるんだね。" TCC_NEWLINE
                "それは素晴らしいことだと思うよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "お前もそう思ってくれるか？" TCC_NEWLINE
                "ありがとう、"TCC_SUMMONER_NAME"。" TCC_NEWLINE
                "お前は俺の気持ちを理解してくれる" TCC_NEWLINE
                "数少ない人だ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "僕もありがとう、タクミ。" TCC_NEWLINE
                "君は僕に弓の魅力を教えてくれた" TCC_NEWLINE
                "数少ない人だ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "お互いに感謝しあえる仲間だな。" TCC_NEWLINE
                "これからも一緒に弓を極めていこうぜ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "うん、約束だよ。" TCC_NEWLINE
                "これからも一緒に頑張ろう！" TCC_NEWLINE TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

        [TEXT_SUPPORT_AVATAR_TAKUMI_A] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_TAKUMI
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_AVATAR
                "タクミ、" TCC_NEWLINE
                "その弓は風神弓というんだよね？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ああ、そうだ。" TCC_NEWLINE
                "俺の専用武器だ。" TCC_NEWLINE
                "なぜ聞く？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "いや、ただ興味があってね。" TCC_NEWLINE
                "どんな力があるのかなと思って。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "どんな力か。。。" TCC_NEWLINE
                "まず、" TCC_NEWLINE
                "この弓は風を操ることができるんだ。" TCC_NEWLINE
                "矢は風で作られているから、" TCC_NEWLINE
                "弦も矢も見えないんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "へえ、すごいね。" TCC_NEWLINE
                "じゃあ、どうやって撃つの？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "心で撃つんだよ。" TCC_NEWLINE
                "心が晴れていれば、" TCC_NEWLINE
                "矢は的に向かって飛ぶ。" TCC_NEWLINE
                "でも、心が曇っていれば、" TCC_NEWLINE
                "矢は飛ばない。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "心が曇っているというと。。。？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "自信がなかったり、" TCC_NEWLINE
                "迷ったり、怒ったりしたときだ。" TCC_NEWLINE
                "この弓は俺の心と一体になっているから、" TCC_NEWLINE
                "俺の感情に影響されるんだ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "なるほど。。。" TCC_NEWLINE
                "それは大変そうだね。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そうでもないさ。" TCC_NEWLINE
                "俺はこの弓と長く付き合ってきたから、" TCC_NEWLINE
                "だいたいコントロールできるようになった。" TCC_NEWLINE
                "それに、お前がそばにいてくれると、" TCC_NEWLINE
                "心が安定するからな。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "そう言ってくれると嬉しいよ。" TCC_NEWLINE
                "僕も君がそばにいてくれると、心強いよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ありがとう、"TCC_SUMMONER_NAME"。" TCC_NEWLINE
                "お前は俺の大切な仲間だ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "僕もありがとう、タクミ。" TCC_NEWLINE
                "君は僕の大切な存在だ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "大切な存在。。。か。" TCC_NEWLINE
                "お前も俺にとって大切な存在だ。" TCC_NEWLINE
                "お前がいなかったら、" TCC_NEWLINE
                "俺は今頃どうなっていたかわからない。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "どういう意味だい？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "。。。実はな、俺は昔、" TCC_NEWLINE
                "自分の世界で戦争に巻き込まれて、" TCC_NEWLINE
                "苦しんでいたんだ。" TCC_NEWLINE
                "自分の力を信じられなくて、" TCC_NEWLINE
                "仲間や家族とも離れ離れになって。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "そんなことがあったのか。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "あったんだよ。" TCC_NEWLINE
                "でも、お前が俺を召喚してくれたおかげで、" TCC_NEWLINE
                "俺は変われたんだ。" TCC_NEWLINE
                "お前は俺の力を認めてくれたし、" TCC_NEWLINE
                "俺の心を開いてくれたし、" TCC_NEWLINE
                "俺のそばにいてくれた。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "それは僕も同じだよ。" TCC_NEWLINE
                "君が僕に教えてくれたことはたくさんあるよ。" TCC_NEWLINE
                "君は僕の心を癒してくれたし、" TCC_NEWLINE
                "僕の力を引き出してくれたし、" TCC_NEWLINE
                "僕の仲間になってくれた。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "じゃあ、" TCC_NEWLINE
                "これからも一緒に戦おうぜ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "うん、そうしよう。" TCC_NEWLINE
                "これからも一緒に戦おうね。" TCC_NEWLINE TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE,

       [TEXT_SUPPORT_BRUNO_VERONICA] = TCC_OPEN_LEFT
           TCC_LOAD_FACE PORTRAIT_BRUNO_MASKED
               "ここか。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_RIGHT
               TCC_LOAD_FACE PORTRAIT_VERONICA
               "お兄様。。。" TCC_NEWLINE TCC_PUSH_A
               TCC_OPEN_LEFT
               TCC_CLEAR_FACE
               TCC_OPEN_RIGHT
               TCC_CLEAR_FACE,

       [TEXT_SUPPORT_HRID_GUNNTHRA] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_HRID
                    "スリーズ、祖国を守るのが私たちの務め" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_GUNNTHRA
                    "ええ" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_HRID_FJORM] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_HRID
                    "すまない、フィヨルム。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_FJORM
                    "兄上。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_HRID_YURG] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_YLGR
                    "兄様っ、フリーズ兄様。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_HRID
                    "ユルグはここにいたのか" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_GUNNTHRA_FJORM] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_GUNNTHRA
                    "フィヨルム、私のかわいい妹。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_FJORM
                    "姉上" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_GUNNTHRA_YURG] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_YLGR
                    "姉様っ、スリーズ姉様。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_GUNNTHRA
                    "まあ、珍しいですねユルグ。"
                    TCC_NEWLINE
                    "こんな朝早くに起きるなんて。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_FJORM_YURG] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_YLGR
                    "姉様っ、フィヨルム姉様。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_FJORM
                    "珍しいですね。" TCC_NEWLINE
                    "いつもならユルグは" TCC_NEWLINE
                    "まだ眠っている時間なのに。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_YURG_HELBINDI] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_YLGR
                    "あなたって、" TCC_NEWLINE
                    "思ってたより良い人なんだね。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_HELBINDI
                    "ああ？"
                    TCC_NEWLINE
                    "ぶち殺すぞガキが。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_LOKI_SURTR] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_LOKI
                    "王様、私の身体なら、煮るなり焼くなりお好きになさって。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_SURTR
                    "下がれロキ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_SURTR_LAEVATAIN] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_SURTR
                    "レーヴァテイン！" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_LAEVATAIN
                    "はい" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_SURTR_LAEGJARN] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_SURTR
                    "良かろう、行け。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_LAEGJARN
                    "承知致しました。。。父上。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_LAEVATAIN_LAEGJARN] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_LAEVATAIN
                    "姉上。。。おけがは？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_LAEGJARN
                    "大丈夫よ、ありがとうレーヴァテイン。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_HEL_EIR] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_EIR
                    "お母様。。。"TCC_NEWLINE TCC_PUSH_A
                    "お母様にとっては、私は娘じゃなかった。"TCC_NEWLINE
                    "でも、私にとっては、お母様はたった一人の家族だった。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_HEL
                    "。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_HEL_LIF] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_HEL
                    "リーヴ" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_LIF
                    "はい" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_HEL_SRASIR] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_HEL
                    "スラシル" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_THRASIR
                    "はい" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_LIF_SRASIR] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_LIF
                    "ああ" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_THRASIR
                    "どうしたの？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_MIRABILIS_PEONY] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_PEONY
                    "おねぼうさん、起きて。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_MIRABILIS
                    "ふわぁ。。。"TCC_NEWLINE
                    "おはようございますぅ。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_FREYJA_TRIANDRA] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_FREYJA
                    "スカビオサ。私と共にいらっしゃい。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_TRIANDRA
                    "はい、フレイヤ様。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_FREYJA_PLUMERIA] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_FREYJA
                    "プルメリア。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_PLUMERIA
                    "ああ、フレイヤ様。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_TRIANDRA_PLUMERIA] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_PLUMERIA
                    "早くフレイヤ様のご命令を果たして、スヴァルトアルフに帰りたいです。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_TRIANDRA
                    "そうね。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_GUSTAF_ALFONSE] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_GUSTAF
                    "アルフォンス" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_ALFONSE
                    "父上" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_GUSTAF_SHARENA] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_GUSTAF
                    "シャロン" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_SHARENA
                    "お父様" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_AVATAR_ANNA] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_HOOD
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_ANNA
                    TCC_SUMMONER_NAME"さんのスキルのおかげで、" TCC_NEWLINE
                    "戦闘はかなり順調に進んでるよ。" TCC_NEWLINE TCC_PUSH_A
                    "あなたがいてくれて、" TCC_NEWLINE
                    "本当によかった。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                    "いいえ、全部隊長の指揮のおかけだよ。" TCC_NEWLINE
                    "隊長はいつも私たちを勝利に導いていく。" TCC_NEWLINE
                    "これからもよろしくお願いします！" TCC_NEWLINE TCC_PUSH_A
                    TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_AVATAR_ANNA_C] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_AVATAR
                "アンナさん、" TCC_NEWLINE
                "ちょっといいですか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "あら、"TCC_SUMMONER_NAME"さん。" TCC_NEWLINE
                "どうしたの？" TCC_NEWLINE
                "何か用事でも？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "実は、この前の戦闘でお世話になった" TCC_NEWLINE
                "お礼を言いたくて。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええ、それはどういたしまして。" TCC_NEWLINE
                "私はただ、仲間を助けたかっただけよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "でも、あなたは自分の身を危険に" TCC_NEWLINE
                "さらしてまで私を守ってくれました。" TCC_NEWLINE
                "それに、あの時の作戦も" TCC_NEWLINE
                "あなたの提案でしたよね。" TCC_NEWLINE
                "あれがなかったら、" TCC_NEWLINE
                "私たちは勝てなかったかもしれません。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そう言ってもらえると嬉しいわ。" TCC_NEWLINE
                "私は戦闘のことなら得意なんだから。" TCC_NEWLINE
                "商売のセンスもあるしね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "商売のセンス？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええ、私は商人なのよ。" TCC_NEWLINE
                "戦場で見つけた貴重品や" TCC_NEWLINE
                "敵の装備品を売ったり買ったりして、" TCC_NEWLINE
                "利益を得るのが趣味なの。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "趣味？！" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そうよ、趣味。" TCC_NEWLINE
                "だって、商売は楽しいものじゃないと" TCC_NEWLINE
                "ダメでしょ？" TCC_NEWLINE
                "お金を稼ぐだけじゃつまらないわ。" TCC_NEWLINE
                "お客さんと交渉したり、" TCC_NEWLINE
                "競争相手と駆け引きしたり、" TCC_NEWLINE
                "新しい商品を探したりするのが面白いのよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "すごいですね。" TCC_NEWLINE
                "私には想像もつきません。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そう？" TCC_NEWLINE
                "でも、あなたもすごいわよ。" TCC_NEWLINE
                "召喚師として英雄たちを呼び出したり、" TCC_NEWLINE
                "指揮官として作戦を立てたりするのは" TCC_NEWLINE
                "大変でしょう？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "ええ、それなりに大変ですが。。。" TCC_NEWLINE
                "でも、私は仲間や国を守るために" TCC_NEWLINE
                "やっているだけです。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "私も同じよ。" TCC_NEWLINE
                "仲間や国を守るために" TCC_NEWLINE
                "戦っているんだから。" TCC_NEWLINE
                "それに、戦闘中に見つけた物品は" TCC_NEWLINE
                "自分のものにする権利があると思うのよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうですか。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "もちろん、" TCC_NEWLINE
                "必要な物品は仲間に分け与えるわよ。" TCC_NEWLINE
                "私は強欲ではないから。" TCC_NEWLINE
                "でも、余分な物品は自由に" TCC_NEWLINE
                "扱ってもいいでしょ？" TCC_NEWLINE
                "それが商人のだいごみなんだから。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "なるほど。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_SUMMONER_NAME"さんも興味があったら、" TCC_NEWLINE
                "一緒に商売してみませんか？" TCC_NEWLINE
                "私が教えてあげるわよ。" TCC_NEWLINE
                "商売のコツやテクニックをね。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "えっ、私にできるでしょうか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "できるできる。" TCC_NEWLINE
                "あなたは頭がいいし、" TCC_NEWLINE
                "人望もあるし、" TCC_NEWLINE
                "素質は十\分よ。" TCC_NEWLINE
                "私と一緒になれば、" TCC_NEWLINE
                "すぐに商売のプロになれるわ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そう言われると、" TCC_NEWLINE
                "ちょっと興味がわきますね。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "それなら、" TCC_NEWLINE
                "さっそく始めましょうか？" TCC_NEWLINE
                "私が持っているこの宝石を、" TCC_NEWLINE
                "あなたに売ってあげましょう。" TCC_NEWLINE
                "どうですか？" TCC_NEWLINE
                "この輝き、この色合い、この重さ。" TCC_NEWLINE
                "これはとても貴重なものなんですよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "本当ですか？" TCC_NEWLINE
                "でも、私にはお金がありません。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "大丈夫よ。" TCC_NEWLINE
                "今回は特別に、" TCC_NEWLINE
                "あなたにサービスしてあげるわ。" TCC_NEWLINE
                "ただし、条件があるのよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "条件？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええ。" TCC_NEWLINE
                "この宝石を受け取ったら、" TCC_NEWLINE
                "私とレベルＣの支援関係に" TCC_NEWLINE
                "なってくれること。" TCC_NEWLINE
                "それだけよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "えっ？！" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_AVATAR_ANNA_B] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_AVATAR
                "アンナさん、" TCC_NEWLINE
                "ちょっといいですか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "あら、" TCC_NEWLINE
                TCC_SUMMONER_NAME"さん。" TCC_NEWLINE
                "どうしたの？" TCC_NEWLINE
                "何か用事でも？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "実は、この前あなたからもらった" TCC_NEWLINE
                "宝石についてなんですが。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ああ、あれね。" TCC_NEWLINE
                "どうしたの？" TCC_NEWLINE
                "気に入ってくれたかしら？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "ええ、とてもきれいで" TCC_NEWLINE
                "素敵な宝石です。" TCC_NEWLINE
                "でも、それが問題なんです。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "問題？" TCC_NEWLINE
                "どういうこと？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "この宝石、" TCC_NEWLINE
                "実はとても高価なものだと聞きました。" TCC_NEWLINE
                "戦場で見つけたものだと言っていましたが、" TCC_NEWLINE
                "本当にそうなんですか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええ、もちろんよ。" TCC_NEWLINE
                "私は嘘はつかないから。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "でも、こんなに貴重なものを" TCC_NEWLINE
                "私にタダでくれるなんて、" TCC_NEWLINE
                "ありえませんよ。" TCC_NEWLINE
                "何か裏があるんじゃないですか？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "裏？そんなことないわよ。" TCC_NEWLINE
                "私はただ、あなたに感謝の" TCC_NEWLINE
                "気持ちを伝えたかっただけよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "感謝の気持ち？" TCC_NEWLINE
                "私に？" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええ。" TCC_NEWLINE
                "あなたは私にとって" TCC_NEWLINE
                "大切な仲間だから。" TCC_NEWLINE
                "私は仲間を大事にするタイプなのよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "そうですか。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そうよ。" TCC_NEWLINE
                "だから、" TCC_NEWLINE
                "この宝石は私からのプレゼントなの。" TCC_NEWLINE
                "あなたが喜んでくれると" TCC_NEWLINE
                "思って渡したのよ。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "でも、これは私には重すぎます。" TCC_NEWLINE
                "こんなに高価なものを受け取る" TCC_NEWLINE
                "資格はありません。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そんなこと言わないでよ。" TCC_NEWLINE
                "あなたは十\分に価値があるわ。" TCC_NEWLINE
                "私はあなたのことを尊敬しているし、" TCC_NEWLINE
                "信頼しているし、" TCC_NEWLINE
                "好きだし。。。" TCC_NEWLINE
                TCC_PUSH_A
            TCC_OPEN_LEFT
                "好き？" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                "えっ？！" TCC_NEWLINE
                TCC_PUSH_A
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_AVATAR_ANNA_A] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE PORTRAIT_ANNA
            TCC_OPEN_LEFT
                TCC_LOAD_FACE PORTRAIT_AVATAR
                "アンナさん、" TCC_NEWLINE
                "ちょっといいですか？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "あら、"TCC_SUMMONER_NAME"さん。" TCC_NEWLINE
                "どうしたの？" TCC_NEWLINE
                "何か用事でも？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "実は、この前のあなたの発言" TCC_NEWLINE
                "についてなんですが。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ああ、あれね。" TCC_NEWLINE
                "どうしたの？" TCC_NEWLINE
                "気になっていたの？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "ええ、とても気になっていました。" TCC_NEWLINE
                "あなたは私のことを好きだと" TCC_NEWLINE
                "言いましたよね。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええ、そう言いました。" TCC_NEWLINE
                "それがどうかしました？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "それがどうかしたというか。。。" TCC_NEWLINE
                "あなたは私に何を求めているんですか？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "求めている？" TCC_NEWLINE
                "そんなことはないわよ。" TCC_NEWLINE
                "私はただ、" TCC_NEWLINE
                "あなたに自分の気持ちを" TCC_NEWLINE
                "伝えたかっただけよ。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "自分の気持ち？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "ええ。" TCC_NEWLINE
                "私はあなたのことを好きなんだから。" TCC_NEWLINE
                "恋愛感情で好きなんだから。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "恋愛感情？！" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                "そうよ。恋愛感情。" TCC_NEWLINE
                "あなたは私のことをどう思っているの？" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                "私は。。。" TCC_NEWLINE TCC_PUSH_A
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_FREYR_FREYJA] =
           TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_FREYJA
                    "兄様。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_FREYR
                    "フレイヤ。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_TRIANDRA_PEONY] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_TRIANDRA
            TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_PEONY
                    "姉上" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                    "。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

       [TEXT_SUPPORT_DAGR_NOTT] =
            TCC_OPEN_RIGHT
                TCC_LOAD_FACE
                    PORTRAIT_DAGR
            TCC_OPEN_LEFT
                TCC_LOAD_FACE
                    PORTRAIT_NOTT
                    "あ、素敵！" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_RIGHT
                    "バカ姉貴、また男にメロメロ。。。" TCC_NEWLINE TCC_PUSH_A
            TCC_OPEN_LEFT
                TCC_CLEAR_FACE
            TCC_OPEN_RIGHT
                TCC_CLEAR_FACE
        ,

#include "texts.txt"
};

extern const char * lastText;
extern char decodedText[];
extern const char * compressedText[];

void decompressText(const char *src, char *dst);
int getStringTextWidth(const char *str);
char *getCharTextWidth(char *str, unsigned int *pWidth);

void stripTextControlCode(char *textIn, char *textOut, int maxLength)
{
    char *textOutGuard = textOut + maxLength;

    while(*textIn)
    {
        // single byte control code
        if(*textIn > 0 && *textIn < 0x20)
        {
            textIn++;
            continue;
        }

        // double byte control code
        if(*textIn == -128) // 0x80
        {
            textIn += 2;
            continue;
        }

        // double byte encoding
        if(*textIn < 0) // 0x81 ~
            *textOut++ = *textIn++;

        *textOut++ = *textIn++;

        // prevent overflow
        if(textOut > textOutGuard - 3)
            break;
    }

    // end of string
    *textOut = 0;
}

char *decodeText(int textID)
{
    char *p = texts[textID];

    if(textID == TEXT_SPECIAL_SKILL_HELP)
        p = getSpecialSkillDescriptionText();
    if(textID == TEXT_ASSIST_SKILL_NAME_IN_ACTION_MENU)
        p = getAssistSkillNameTextInActionMenu();
    if(textID == TEXT_ASSIST_SKILL_HELP_IN_ACTION_MENU)
        p = getAssistSkillDescriptionTextInActionMenu();
    if(textID == TEXT_ASSIST_SKILL_HELP_IN_STAT_SCREEN)
        p = getAssistSkillDescriptionTextInStatScreen();
    if(textID == TEXT_PASSIVE_SKILL_A_HELP)
        p = getPassiveSkillAHelpText();
    if(textID == TEXT_PASSIVE_SKILL_B_HELP)
        p = getPassiveSkillBHelpText();
    if(textID == TEXT_PASSIVE_SKILL_C_HELP)
        p = getPassiveSkillCHelpText();
    if(textID == TEXT_PASSIVE_SKILL_S_HELP)
        p = getPassiveSkillSHelpText();
    if(textID == TEXT_NEW_PASSIVE_SKILL_UNLOCKED)
        p = getNewUnlockedPassiveSkillNameTextByCurrentAIS();

    if(p == NULL)
    {
        p = compressedText[textID];

        if(p != lastText)
            decompressText(p, decodedText);

        lastText = p;

        return decodedText;
    }

    if(p == lastText)
        return decodedText;

    lastText = p;

    char *p0 = p;
    char *q = decodedText;
    unsigned int maxLineWidth = TEXT_LINE_WIDTH_MAX;
    if(textID == TEXT_SPECIAL_SKILL_HELP || textID == TEXT_ASSIST_SKILL_HELP_IN_ACTION_MENU || textID == TEXT_ASSIST_SKILL_HELP_IN_STAT_SCREEN || textID == TEXT_PASSIVE_SKILL_A_HELP || textID == TEXT_PASSIVE_SKILL_B_HELP || textID == TEXT_PASSIVE_SKILL_C_HELP || textID == TEXT_PASSIVE_SKILL_S_HELP)
        maxLineWidth = SKILL_HELP_WIDTH_MAX;

    // copy text directly
    if (getStringTextWidth(p) <= maxLineWidth)
        while (*p)
            *q++ = *p++;
    else {
        // add new lines automatically
        unsigned int charWidth = 0;
        unsigned int lineWidth = 0;

        while (*p) {
            if (*p > 0 && *p < 0x20)
                *q++ = *p++;
            else {
                char *p_next = getCharTextWidth(p, &charWidth);
                lineWidth += charWidth;
                if (lineWidth > maxLineWidth) {
                    *q++ = 1; // new line
                    lineWidth = charWidth;
                }
                while (*p && p < p_next)
                    *q++ = *p++;
            }
        }
    }

    // add 0 to end string
    *q = 0;

    if(getStringTextWidth(p0) > maxLineWidth)
    {
        Debugf("AutoNewLine for text 0x%x, width %d -> %d", textID, getStringTextWidth(p0), getStringTextWidth(decodedText));
    }

    return decodedText;
}

char *decodeTextInjector(int textID)
{
    return decodeText(textID);
}

const char textBubblePositionYInDialogue = 5; // StartTalkOpen()
