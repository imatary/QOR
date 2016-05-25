
#ifndef CODEQOR_TYPES_UNICODE_H_3
#define CODEQOR_TYPES_UNICODE_H_3

#include "CompilerQOR.h"

#define UNICODE_DATA_VERSION Unicode_5_0
#define UNICODE_LAST_CODEPOINT 0x10ffff

//------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//------------------------------------------------------------------------------
	namespace nsUnicodeTables 
	{

	//------------------------------------------------------------------------------
    struct Properties 
	{
        unsigned short category         : 8; /* 5 needed */
        unsigned short line_break_class : 8; /* 6 needed */
        unsigned short direction        : 8; /* 5 needed */
        unsigned short combiningClass   : 8;
        unsigned short joining          : 2;
        signed short digitValue : 6; /* 5 needed */
        unsigned short unicodeVersion   : 4;
        unsigned short lowerCaseSpecial : 1;
        unsigned short upperCaseSpecial : 1;
        unsigned short titleCaseSpecial : 1;
        unsigned short caseFoldSpecial  : 1; /* currently unused */
        signed short mirrorDiff    : 16;
        signed short lowerCaseDiff : 16;
        signed short upperCaseDiff : 16;
        signed short titleCaseDiff : 16;
        signed short caseFoldDiff  : 16;
        unsigned short graphemeBreak    : 8; /* 4 needed */
        unsigned short wordBreak        : 8; /* 4 needed */
        unsigned short sentenceBreak    : 8; /* 4 needed */
    };

    __QOR_INTERFACE( __CODEQOR ) const Properties * __QCMP_FASTCALL properties( unsigned int ucs4 );
    __QOR_INTERFACE( __CODEQOR ) const Properties * __QCMP_FASTCALL properties( unsigned short ucs2 );

	//------------------------------------------------------------------------------
    // See http://www.unicode.org/reports/tr24/tr24-5.html
    enum Script 
	{
        Common,
        Greek,
        Cyrillic,
        Armenian,
        Hebrew,
        Arabic,
        Syriac,
        Thaana,
        Devanagari,
        Bengali,
        Gurmukhi,
        Gujarati,
        Oriya,
        Tamil,
        Telugu,
        Kannada,
        Malayalam,
        Sinhala,
        Thai,
        Lao,
        Tibetan,
        Myanmar,
        Georgian,
        Hangul,
        Ogham,
        Runic,
        Khmer,
        Nko,
        Inherited,
        ScriptCount = Inherited,
        Latin = Common,
        Ethiopic = Common,
        Cherokee = Common,
        CanadianAboriginal = Common,
        Mongolian = Common,
        Hiragana = Common,
        Katakana = Common,
        Bopomofo = Common,
        Han = Common,
        Yi = Common,
        OldItalic = Common,
        Gothic = Common,
        Deseret = Common,
        Tagalog = Common,
        Hanunoo = Common,
        Buhid = Common,
        Tagbanwa = Common,
        Limbu = Common,
        TaiLe = Common,
        LinearB = Common,
        Ugaritic = Common,
        Shavian = Common,
        Osmanya = Common,
        Cypriot = Common,
        Braille = Common,
        Buginese = Common,
        Coptic = Common,
        NewTaiLue = Common,
        Glagolitic = Common,
        Tifinagh = Common,
        SylotiNagri = Common,
        OldPersian = Common,
        Kharoshthi = Common,
        Balinese = Common,
        Cuneiform = Common,
        Phoenician = Common,
        PhagsPa = Common
    };

	//------------------------------------------------------------------------------
    enum 
	{ 
		ScriptSentinel = 32 
	};

	//------------------------------------------------------------------------------
    enum GraphemeBreak 
	{
        GraphemeBreakOther,
        GraphemeBreakCR,
        GraphemeBreakLF,
        GraphemeBreakControl,
        GraphemeBreakExtend,
        GraphemeBreakL,
        GraphemeBreakV,
        GraphemeBreakT,
        GraphemeBreakLV,
        GraphemeBreakLVT
    };

	//------------------------------------------------------------------------------
    enum WordBreak 
	{
        WordBreakOther,
        WordBreakFormat,
        WordBreakKatakana,
        WordBreakALetter,
        WordBreakMidLetter,
        WordBreakMidNum,
        WordBreakNumeric,
        WordBreakExtendNumLet
    };

	//------------------------------------------------------------------------------
    enum SentenceBreak 
	{
        SentenceBreakOther,
        SentenceBreakSep,
        SentenceBreakFormat,
        SentenceBreakSp,
        SentenceBreakLower,
        SentenceBreakUpper,
        SentenceBreakOLetter,
        SentenceBreakNumeric,
        SentenceBreakATerm,
        SentenceBreakSTerm,
        SentenceBreakClose
    };

	//------------------------------------------------------------------------------
    // see http://www.unicode.org/reports/tr14/tr14-19.html
    // we don't use the XX, AI and CB properties and map them to AL instead.
    // as we don't support any EBDIC based OS'es, NL is ignored and mapped to AL as well.
    enum LineBreakClass 
	{
        LineBreak_OP, LineBreak_CL, LineBreak_QU, LineBreak_GL, LineBreak_NS,
        LineBreak_EX, LineBreak_SY, LineBreak_IS, LineBreak_PR, LineBreak_PO,
        LineBreak_NU, LineBreak_AL, LineBreak_ID, LineBreak_IN, LineBreak_HY,
        LineBreak_BA, LineBreak_BB, LineBreak_B2, LineBreak_ZW, LineBreak_CM,
        LineBreak_WJ, LineBreak_H2, LineBreak_H3, LineBreak_JL, LineBreak_JV,
        LineBreak_JT, LineBreak_SA, LineBreak_SG,
        LineBreak_SP, LineBreak_CR, LineBreak_LF, LineBreak_BK
    };

    __QOR_INTERFACE( __CODEQOR ) nsUnicodeTables::LineBreakClass __QCMP_FASTCALL lineBreakClass( unsigned int ucs4 );
    __QOR_INTERFACE( __CODEQOR ) int __QCMP_FASTCALL script( unsigned int ucs4 );

	}//nsUnicodeTables

}//nsCodeQOR

#endif//CODEQOR_TYPES_UNICODE_H_3
