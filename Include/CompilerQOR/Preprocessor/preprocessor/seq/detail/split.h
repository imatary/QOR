//split.h

# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef QOR_PREPROCESSOR_SEQ_DETAIL_SPLIT_H_1
#define QOR_PREPROCESSOR_SEQ_DETAIL_SPLIT_H_1

#include "../../config/config.h"

//QOR_PP_SEQ_SPLIT

#define QOR_PP_SEQ_SPLIT( n, seq )		QOR_PP_SEQ_SPLIT_D( n, seq )

#if	~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_MWCC()
#	define QOR_PP_SEQ_SPLIT_D( n, seq )	( QOR_PP_SEQ_SPLIT_ ## n seq )
#else//MWCC
#	define QOR_PP_SEQ_SPLIT_D( n, seq ) ( QOR_P_SEQ_SPLIT_ ## n ## seq )
#endif

#define QOR_PP_SEQ_SPLIT_1(x) (x),
#define QOR_PP_SEQ_SPLIT_2(x) (x) QOR_PP_SEQ_SPLIT_1
#define QOR_PP_SEQ_SPLIT_3(x) (x) QOR_PP_SEQ_SPLIT_2
#define QOR_PP_SEQ_SPLIT_4(x) (x) QOR_PP_SEQ_SPLIT_3
#define QOR_PP_SEQ_SPLIT_5(x) (x) QOR_PP_SEQ_SPLIT_4
#define QOR_PP_SEQ_SPLIT_6(x) (x) QOR_PP_SEQ_SPLIT_5
#define QOR_PP_SEQ_SPLIT_7(x) (x) QOR_PP_SEQ_SPLIT_6
#define QOR_PP_SEQ_SPLIT_8(x) (x) QOR_PP_SEQ_SPLIT_7
#define QOR_PP_SEQ_SPLIT_9(x) (x) QOR_PP_SEQ_SPLIT_8
#define QOR_PP_SEQ_SPLIT_10(x) (x) QOR_PP_SEQ_SPLIT_9
#define QOR_PP_SEQ_SPLIT_11(x) (x) QOR_PP_SEQ_SPLIT_10
#define QOR_PP_SEQ_SPLIT_12(x) (x) QOR_PP_SEQ_SPLIT_11
#define QOR_PP_SEQ_SPLIT_13(x) (x) QOR_PP_SEQ_SPLIT_12
#define QOR_PP_SEQ_SPLIT_14(x) (x) QOR_PP_SEQ_SPLIT_13
#define QOR_PP_SEQ_SPLIT_15(x) (x) QOR_PP_SEQ_SPLIT_14
#define QOR_PP_SEQ_SPLIT_16(x) (x) QOR_PP_SEQ_SPLIT_15
#define QOR_PP_SEQ_SPLIT_17(x) (x) QOR_PP_SEQ_SPLIT_16
#define QOR_PP_SEQ_SPLIT_18(x) (x) QOR_PP_SEQ_SPLIT_17
#define QOR_PP_SEQ_SPLIT_19(x) (x) QOR_PP_SEQ_SPLIT_18
#define QOR_PP_SEQ_SPLIT_20(x) (x) QOR_PP_SEQ_SPLIT_19
#define QOR_PP_SEQ_SPLIT_21(x) (x) QOR_PP_SEQ_SPLIT_20
#define QOR_PP_SEQ_SPLIT_22(x) (x) QOR_PP_SEQ_SPLIT_21
#define QOR_PP_SEQ_SPLIT_23(x) (x) QOR_PP_SEQ_SPLIT_22
#define QOR_PP_SEQ_SPLIT_24(x) (x) QOR_PP_SEQ_SPLIT_23
#define QOR_PP_SEQ_SPLIT_25(x) (x) QOR_PP_SEQ_SPLIT_24
#define QOR_PP_SEQ_SPLIT_26(x) (x) QOR_PP_SEQ_SPLIT_25
#define QOR_PP_SEQ_SPLIT_27(x) (x) QOR_PP_SEQ_SPLIT_26
#define QOR_PP_SEQ_SPLIT_28(x) (x) QOR_PP_SEQ_SPLIT_27
#define QOR_PP_SEQ_SPLIT_29(x) (x) QOR_PP_SEQ_SPLIT_28
#define QOR_PP_SEQ_SPLIT_30(x) (x) QOR_PP_SEQ_SPLIT_29
#define QOR_PP_SEQ_SPLIT_31(x) (x) QOR_PP_SEQ_SPLIT_30
#define QOR_PP_SEQ_SPLIT_32(x) (x) QOR_PP_SEQ_SPLIT_31
#define QOR_PP_SEQ_SPLIT_33(x) (x) QOR_PP_SEQ_SPLIT_32
#define QOR_PP_SEQ_SPLIT_34(x) (x) QOR_PP_SEQ_SPLIT_33
#define QOR_PP_SEQ_SPLIT_35(x) (x) QOR_PP_SEQ_SPLIT_34
#define QOR_PP_SEQ_SPLIT_36(x) (x) QOR_PP_SEQ_SPLIT_35
#define QOR_PP_SEQ_SPLIT_37(x) (x) QOR_PP_SEQ_SPLIT_36
#define QOR_PP_SEQ_SPLIT_38(x) (x) QOR_PP_SEQ_SPLIT_37
#define QOR_PP_SEQ_SPLIT_39(x) (x) QOR_PP_SEQ_SPLIT_38
#define QOR_PP_SEQ_SPLIT_40(x) (x) QOR_PP_SEQ_SPLIT_39
#define QOR_PP_SEQ_SPLIT_41(x) (x) QOR_PP_SEQ_SPLIT_40
#define QOR_PP_SEQ_SPLIT_42(x) (x) QOR_PP_SEQ_SPLIT_41
#define QOR_PP_SEQ_SPLIT_43(x) (x) QOR_PP_SEQ_SPLIT_42
#define QOR_PP_SEQ_SPLIT_44(x) (x) QOR_PP_SEQ_SPLIT_43
#define QOR_PP_SEQ_SPLIT_45(x) (x) QOR_PP_SEQ_SPLIT_44
#define QOR_PP_SEQ_SPLIT_46(x) (x) QOR_PP_SEQ_SPLIT_45
#define QOR_PP_SEQ_SPLIT_47(x) (x) QOR_PP_SEQ_SPLIT_46
#define QOR_PP_SEQ_SPLIT_48(x) (x) QOR_PP_SEQ_SPLIT_47
#define QOR_PP_SEQ_SPLIT_49(x) (x) QOR_PP_SEQ_SPLIT_48
#define QOR_PP_SEQ_SPLIT_50(x) (x) QOR_PP_SEQ_SPLIT_49
#define QOR_PP_SEQ_SPLIT_51(x) (x) QOR_PP_SEQ_SPLIT_50
#define QOR_PP_SEQ_SPLIT_52(x) (x) QOR_PP_SEQ_SPLIT_51
#define QOR_PP_SEQ_SPLIT_53(x) (x) QOR_PP_SEQ_SPLIT_52
#define QOR_PP_SEQ_SPLIT_54(x) (x) QOR_PP_SEQ_SPLIT_53
#define QOR_PP_SEQ_SPLIT_55(x) (x) QOR_PP_SEQ_SPLIT_54
#define QOR_PP_SEQ_SPLIT_56(x) (x) QOR_PP_SEQ_SPLIT_55
#define QOR_PP_SEQ_SPLIT_57(x) (x) QOR_PP_SEQ_SPLIT_56
#define QOR_PP_SEQ_SPLIT_58(x) (x) QOR_PP_SEQ_SPLIT_57
#define QOR_PP_SEQ_SPLIT_59(x) (x) QOR_PP_SEQ_SPLIT_58
#define QOR_PP_SEQ_SPLIT_60(x) (x) QOR_PP_SEQ_SPLIT_59
#define QOR_PP_SEQ_SPLIT_61(x) (x) QOR_PP_SEQ_SPLIT_60
#define QOR_PP_SEQ_SPLIT_62(x) (x) QOR_PP_SEQ_SPLIT_61
#define QOR_PP_SEQ_SPLIT_63(x) (x) QOR_PP_SEQ_SPLIT_62
#define QOR_PP_SEQ_SPLIT_64(x) (x) QOR_PP_SEQ_SPLIT_63
#define QOR_PP_SEQ_SPLIT_65(x) (x) QOR_PP_SEQ_SPLIT_64
#define QOR_PP_SEQ_SPLIT_66(x) (x) QOR_PP_SEQ_SPLIT_65
#define QOR_PP_SEQ_SPLIT_67(x) (x) QOR_PP_SEQ_SPLIT_66
#define QOR_PP_SEQ_SPLIT_68(x) (x) QOR_PP_SEQ_SPLIT_67
#define QOR_PP_SEQ_SPLIT_69(x) (x) QOR_PP_SEQ_SPLIT_68
#define QOR_PP_SEQ_SPLIT_70(x) (x) QOR_PP_SEQ_SPLIT_69
#define QOR_PP_SEQ_SPLIT_71(x) (x) QOR_PP_SEQ_SPLIT_70
#define QOR_PP_SEQ_SPLIT_72(x) (x) QOR_PP_SEQ_SPLIT_71
#define QOR_PP_SEQ_SPLIT_73(x) (x) QOR_PP_SEQ_SPLIT_72
#define QOR_PP_SEQ_SPLIT_74(x) (x) QOR_PP_SEQ_SPLIT_73
#define QOR_PP_SEQ_SPLIT_75(x) (x) QOR_PP_SEQ_SPLIT_74
#define QOR_PP_SEQ_SPLIT_76(x) (x) QOR_PP_SEQ_SPLIT_75
#define QOR_PP_SEQ_SPLIT_77(x) (x) QOR_PP_SEQ_SPLIT_76
#define QOR_PP_SEQ_SPLIT_78(x) (x) QOR_PP_SEQ_SPLIT_77
#define QOR_PP_SEQ_SPLIT_79(x) (x) QOR_PP_SEQ_SPLIT_78
#define QOR_PP_SEQ_SPLIT_80(x) (x) QOR_PP_SEQ_SPLIT_79
#define QOR_PP_SEQ_SPLIT_81(x) (x) QOR_PP_SEQ_SPLIT_80
#define QOR_PP_SEQ_SPLIT_82(x) (x) QOR_PP_SEQ_SPLIT_81
#define QOR_PP_SEQ_SPLIT_83(x) (x) QOR_PP_SEQ_SPLIT_82
#define QOR_PP_SEQ_SPLIT_84(x) (x) QOR_PP_SEQ_SPLIT_83
#define QOR_PP_SEQ_SPLIT_85(x) (x) QOR_PP_SEQ_SPLIT_84
#define QOR_PP_SEQ_SPLIT_86(x) (x) QOR_PP_SEQ_SPLIT_85
#define QOR_PP_SEQ_SPLIT_87(x) (x) QOR_PP_SEQ_SPLIT_86
#define QOR_PP_SEQ_SPLIT_88(x) (x) QOR_PP_SEQ_SPLIT_87
#define QOR_PP_SEQ_SPLIT_89(x) (x) QOR_PP_SEQ_SPLIT_88
#define QOR_PP_SEQ_SPLIT_90(x) (x) QOR_PP_SEQ_SPLIT_89
#define QOR_PP_SEQ_SPLIT_91(x) (x) QOR_PP_SEQ_SPLIT_90
#define QOR_PP_SEQ_SPLIT_92(x) (x) QOR_PP_SEQ_SPLIT_91
#define QOR_PP_SEQ_SPLIT_93(x) (x) QOR_PP_SEQ_SPLIT_92
#define QOR_PP_SEQ_SPLIT_94(x) (x) QOR_PP_SEQ_SPLIT_93
#define QOR_PP_SEQ_SPLIT_95(x) (x) QOR_PP_SEQ_SPLIT_94
#define QOR_PP_SEQ_SPLIT_96(x) (x) QOR_PP_SEQ_SPLIT_95
#define QOR_PP_SEQ_SPLIT_97(x) (x) QOR_PP_SEQ_SPLIT_96
#define QOR_PP_SEQ_SPLIT_98(x) (x) QOR_PP_SEQ_SPLIT_97
#define QOR_PP_SEQ_SPLIT_99(x) (x) QOR_PP_SEQ_SPLIT_98
#define QOR_PP_SEQ_SPLIT_100(x) (x) QOR_PP_SEQ_SPLIT_99
#define QOR_PP_SEQ_SPLIT_101(x) (x) QOR_PP_SEQ_SPLIT_100
#define QOR_PP_SEQ_SPLIT_102(x) (x) QOR_PP_SEQ_SPLIT_101
#define QOR_PP_SEQ_SPLIT_103(x) (x) QOR_PP_SEQ_SPLIT_102
#define QOR_PP_SEQ_SPLIT_104(x) (x) QOR_PP_SEQ_SPLIT_103
#define QOR_PP_SEQ_SPLIT_105(x) (x) QOR_PP_SEQ_SPLIT_104
#define QOR_PP_SEQ_SPLIT_106(x) (x) QOR_PP_SEQ_SPLIT_105
#define QOR_PP_SEQ_SPLIT_107(x) (x) QOR_PP_SEQ_SPLIT_106
#define QOR_PP_SEQ_SPLIT_108(x) (x) QOR_PP_SEQ_SPLIT_107
#define QOR_PP_SEQ_SPLIT_109(x) (x) QOR_PP_SEQ_SPLIT_108
#define QOR_PP_SEQ_SPLIT_110(x) (x) QOR_PP_SEQ_SPLIT_109
#define QOR_PP_SEQ_SPLIT_111(x) (x) QOR_PP_SEQ_SPLIT_110
#define QOR_PP_SEQ_SPLIT_112(x) (x) QOR_PP_SEQ_SPLIT_111
#define QOR_PP_SEQ_SPLIT_113(x) (x) QOR_PP_SEQ_SPLIT_112
#define QOR_PP_SEQ_SPLIT_114(x) (x) QOR_PP_SEQ_SPLIT_113
#define QOR_PP_SEQ_SPLIT_115(x) (x) QOR_PP_SEQ_SPLIT_114
#define QOR_PP_SEQ_SPLIT_116(x) (x) QOR_PP_SEQ_SPLIT_115
#define QOR_PP_SEQ_SPLIT_117(x) (x) QOR_PP_SEQ_SPLIT_116
#define QOR_PP_SEQ_SPLIT_118(x) (x) QOR_PP_SEQ_SPLIT_117
#define QOR_PP_SEQ_SPLIT_119(x) (x) QOR_PP_SEQ_SPLIT_118
#define QOR_PP_SEQ_SPLIT_120(x) (x) QOR_PP_SEQ_SPLIT_119
#define QOR_PP_SEQ_SPLIT_121(x) (x) QOR_PP_SEQ_SPLIT_120
#define QOR_PP_SEQ_SPLIT_122(x) (x) QOR_PP_SEQ_SPLIT_121
#define QOR_PP_SEQ_SPLIT_123(x) (x) QOR_PP_SEQ_SPLIT_122
#define QOR_PP_SEQ_SPLIT_124(x) (x) QOR_PP_SEQ_SPLIT_123
#define QOR_PP_SEQ_SPLIT_125(x) (x) QOR_PP_SEQ_SPLIT_124
#define QOR_PP_SEQ_SPLIT_126(x) (x) QOR_PP_SEQ_SPLIT_125
#define QOR_PP_SEQ_SPLIT_127(x) (x) QOR_PP_SEQ_SPLIT_126
#define QOR_PP_SEQ_SPLIT_128(x) (x) QOR_PP_SEQ_SPLIT_127
#define QOR_PP_SEQ_SPLIT_129(x) (x) QOR_PP_SEQ_SPLIT_128
#define QOR_PP_SEQ_SPLIT_130(x) (x) QOR_PP_SEQ_SPLIT_129
#define QOR_PP_SEQ_SPLIT_131(x) (x) QOR_PP_SEQ_SPLIT_130
#define QOR_PP_SEQ_SPLIT_132(x) (x) QOR_PP_SEQ_SPLIT_131
#define QOR_PP_SEQ_SPLIT_133(x) (x) QOR_PP_SEQ_SPLIT_132
#define QOR_PP_SEQ_SPLIT_134(x) (x) QOR_PP_SEQ_SPLIT_133
#define QOR_PP_SEQ_SPLIT_135(x) (x) QOR_PP_SEQ_SPLIT_134
#define QOR_PP_SEQ_SPLIT_136(x) (x) QOR_PP_SEQ_SPLIT_135
#define QOR_PP_SEQ_SPLIT_137(x) (x) QOR_PP_SEQ_SPLIT_136
#define QOR_PP_SEQ_SPLIT_138(x) (x) QOR_PP_SEQ_SPLIT_137
#define QOR_PP_SEQ_SPLIT_139(x) (x) QOR_PP_SEQ_SPLIT_138
#define QOR_PP_SEQ_SPLIT_140(x) (x) QOR_PP_SEQ_SPLIT_139
#define QOR_PP_SEQ_SPLIT_141(x) (x) QOR_PP_SEQ_SPLIT_140
#define QOR_PP_SEQ_SPLIT_142(x) (x) QOR_PP_SEQ_SPLIT_141
#define QOR_PP_SEQ_SPLIT_143(x) (x) QOR_PP_SEQ_SPLIT_142
#define QOR_PP_SEQ_SPLIT_144(x) (x) QOR_PP_SEQ_SPLIT_143
#define QOR_PP_SEQ_SPLIT_145(x) (x) QOR_PP_SEQ_SPLIT_144
#define QOR_PP_SEQ_SPLIT_146(x) (x) QOR_PP_SEQ_SPLIT_145
#define QOR_PP_SEQ_SPLIT_147(x) (x) QOR_PP_SEQ_SPLIT_146
#define QOR_PP_SEQ_SPLIT_148(x) (x) QOR_PP_SEQ_SPLIT_147
#define QOR_PP_SEQ_SPLIT_149(x) (x) QOR_PP_SEQ_SPLIT_148
#define QOR_PP_SEQ_SPLIT_150(x) (x) QOR_PP_SEQ_SPLIT_149
#define QOR_PP_SEQ_SPLIT_151(x) (x) QOR_PP_SEQ_SPLIT_150
#define QOR_PP_SEQ_SPLIT_152(x) (x) QOR_PP_SEQ_SPLIT_151
#define QOR_PP_SEQ_SPLIT_153(x) (x) QOR_PP_SEQ_SPLIT_152
#define QOR_PP_SEQ_SPLIT_154(x) (x) QOR_PP_SEQ_SPLIT_153
#define QOR_PP_SEQ_SPLIT_155(x) (x) QOR_PP_SEQ_SPLIT_154
#define QOR_PP_SEQ_SPLIT_156(x) (x) QOR_PP_SEQ_SPLIT_155
#define QOR_PP_SEQ_SPLIT_157(x) (x) QOR_PP_SEQ_SPLIT_156
#define QOR_PP_SEQ_SPLIT_158(x) (x) QOR_PP_SEQ_SPLIT_157
#define QOR_PP_SEQ_SPLIT_159(x) (x) QOR_PP_SEQ_SPLIT_158
#define QOR_PP_SEQ_SPLIT_160(x) (x) QOR_PP_SEQ_SPLIT_159
#define QOR_PP_SEQ_SPLIT_161(x) (x) QOR_PP_SEQ_SPLIT_160
#define QOR_PP_SEQ_SPLIT_162(x) (x) QOR_PP_SEQ_SPLIT_161
#define QOR_PP_SEQ_SPLIT_163(x) (x) QOR_PP_SEQ_SPLIT_162
#define QOR_PP_SEQ_SPLIT_164(x) (x) QOR_PP_SEQ_SPLIT_163
#define QOR_PP_SEQ_SPLIT_165(x) (x) QOR_PP_SEQ_SPLIT_164
#define QOR_PP_SEQ_SPLIT_166(x) (x) QOR_PP_SEQ_SPLIT_165
#define QOR_PP_SEQ_SPLIT_167(x) (x) QOR_PP_SEQ_SPLIT_166
#define QOR_PP_SEQ_SPLIT_168(x) (x) QOR_PP_SEQ_SPLIT_167
#define QOR_PP_SEQ_SPLIT_169(x) (x) QOR_PP_SEQ_SPLIT_168
#define QOR_PP_SEQ_SPLIT_170(x) (x) QOR_PP_SEQ_SPLIT_169
#define QOR_PP_SEQ_SPLIT_171(x) (x) QOR_PP_SEQ_SPLIT_170
#define QOR_PP_SEQ_SPLIT_172(x) (x) QOR_PP_SEQ_SPLIT_171
#define QOR_PP_SEQ_SPLIT_173(x) (x) QOR_PP_SEQ_SPLIT_172
#define QOR_PP_SEQ_SPLIT_174(x) (x) QOR_PP_SEQ_SPLIT_173
#define QOR_PP_SEQ_SPLIT_175(x) (x) QOR_PP_SEQ_SPLIT_174
#define QOR_PP_SEQ_SPLIT_176(x) (x) QOR_PP_SEQ_SPLIT_175
#define QOR_PP_SEQ_SPLIT_177(x) (x) QOR_PP_SEQ_SPLIT_176
#define QOR_PP_SEQ_SPLIT_178(x) (x) QOR_PP_SEQ_SPLIT_177
#define QOR_PP_SEQ_SPLIT_179(x) (x) QOR_PP_SEQ_SPLIT_178
#define QOR_PP_SEQ_SPLIT_180(x) (x) QOR_PP_SEQ_SPLIT_179
#define QOR_PP_SEQ_SPLIT_181(x) (x) QOR_PP_SEQ_SPLIT_180
#define QOR_PP_SEQ_SPLIT_182(x) (x) QOR_PP_SEQ_SPLIT_181
#define QOR_PP_SEQ_SPLIT_183(x) (x) QOR_PP_SEQ_SPLIT_182
#define QOR_PP_SEQ_SPLIT_184(x) (x) QOR_PP_SEQ_SPLIT_183
#define QOR_PP_SEQ_SPLIT_185(x) (x) QOR_PP_SEQ_SPLIT_184
#define QOR_PP_SEQ_SPLIT_186(x) (x) QOR_PP_SEQ_SPLIT_185
#define QOR_PP_SEQ_SPLIT_187(x) (x) QOR_PP_SEQ_SPLIT_186
#define QOR_PP_SEQ_SPLIT_188(x) (x) QOR_PP_SEQ_SPLIT_187
#define QOR_PP_SEQ_SPLIT_189(x) (x) QOR_PP_SEQ_SPLIT_188
#define QOR_PP_SEQ_SPLIT_190(x) (x) QOR_PP_SEQ_SPLIT_189
#define QOR_PP_SEQ_SPLIT_191(x) (x) QOR_PP_SEQ_SPLIT_190
#define QOR_PP_SEQ_SPLIT_192(x) (x) QOR_PP_SEQ_SPLIT_191
#define QOR_PP_SEQ_SPLIT_193(x) (x) QOR_PP_SEQ_SPLIT_192
#define QOR_PP_SEQ_SPLIT_194(x) (x) QOR_PP_SEQ_SPLIT_193
#define QOR_PP_SEQ_SPLIT_195(x) (x) QOR_PP_SEQ_SPLIT_194
#define QOR_PP_SEQ_SPLIT_196(x) (x) QOR_PP_SEQ_SPLIT_195
#define QOR_PP_SEQ_SPLIT_197(x) (x) QOR_PP_SEQ_SPLIT_196
#define QOR_PP_SEQ_SPLIT_198(x) (x) QOR_PP_SEQ_SPLIT_197
#define QOR_PP_SEQ_SPLIT_199(x) (x) QOR_PP_SEQ_SPLIT_198
#define QOR_PP_SEQ_SPLIT_200(x) (x) QOR_PP_SEQ_SPLIT_199
#define QOR_PP_SEQ_SPLIT_201(x) (x) QOR_PP_SEQ_SPLIT_200
#define QOR_PP_SEQ_SPLIT_202(x) (x) QOR_PP_SEQ_SPLIT_201
#define QOR_PP_SEQ_SPLIT_203(x) (x) QOR_PP_SEQ_SPLIT_202
#define QOR_PP_SEQ_SPLIT_204(x) (x) QOR_PP_SEQ_SPLIT_203
#define QOR_PP_SEQ_SPLIT_205(x) (x) QOR_PP_SEQ_SPLIT_204
#define QOR_PP_SEQ_SPLIT_206(x) (x) QOR_PP_SEQ_SPLIT_205
#define QOR_PP_SEQ_SPLIT_207(x) (x) QOR_PP_SEQ_SPLIT_206
#define QOR_PP_SEQ_SPLIT_208(x) (x) QOR_PP_SEQ_SPLIT_207
#define QOR_PP_SEQ_SPLIT_209(x) (x) QOR_PP_SEQ_SPLIT_208
#define QOR_PP_SEQ_SPLIT_210(x) (x) QOR_PP_SEQ_SPLIT_209
#define QOR_PP_SEQ_SPLIT_211(x) (x) QOR_PP_SEQ_SPLIT_210
#define QOR_PP_SEQ_SPLIT_212(x) (x) QOR_PP_SEQ_SPLIT_211
#define QOR_PP_SEQ_SPLIT_213(x) (x) QOR_PP_SEQ_SPLIT_212
#define QOR_PP_SEQ_SPLIT_214(x) (x) QOR_PP_SEQ_SPLIT_213
#define QOR_PP_SEQ_SPLIT_215(x) (x) QOR_PP_SEQ_SPLIT_214
#define QOR_PP_SEQ_SPLIT_216(x) (x) QOR_PP_SEQ_SPLIT_215
#define QOR_PP_SEQ_SPLIT_217(x) (x) QOR_PP_SEQ_SPLIT_216
#define QOR_PP_SEQ_SPLIT_218(x) (x) QOR_PP_SEQ_SPLIT_217
#define QOR_PP_SEQ_SPLIT_219(x) (x) QOR_PP_SEQ_SPLIT_218
#define QOR_PP_SEQ_SPLIT_220(x) (x) QOR_PP_SEQ_SPLIT_219
#define QOR_PP_SEQ_SPLIT_221(x) (x) QOR_PP_SEQ_SPLIT_220
#define QOR_PP_SEQ_SPLIT_222(x) (x) QOR_PP_SEQ_SPLIT_221
#define QOR_PP_SEQ_SPLIT_223(x) (x) QOR_PP_SEQ_SPLIT_222
#define QOR_PP_SEQ_SPLIT_224(x) (x) QOR_PP_SEQ_SPLIT_223
#define QOR_PP_SEQ_SPLIT_225(x) (x) QOR_PP_SEQ_SPLIT_224
#define QOR_PP_SEQ_SPLIT_226(x) (x) QOR_PP_SEQ_SPLIT_225
#define QOR_PP_SEQ_SPLIT_227(x) (x) QOR_PP_SEQ_SPLIT_226
#define QOR_PP_SEQ_SPLIT_228(x) (x) QOR_PP_SEQ_SPLIT_227
#define QOR_PP_SEQ_SPLIT_229(x) (x) QOR_PP_SEQ_SPLIT_228
#define QOR_PP_SEQ_SPLIT_230(x) (x) QOR_PP_SEQ_SPLIT_229
#define QOR_PP_SEQ_SPLIT_231(x) (x) QOR_PP_SEQ_SPLIT_230
#define QOR_PP_SEQ_SPLIT_232(x) (x) QOR_PP_SEQ_SPLIT_231
#define QOR_PP_SEQ_SPLIT_233(x) (x) QOR_PP_SEQ_SPLIT_232
#define QOR_PP_SEQ_SPLIT_234(x) (x) QOR_PP_SEQ_SPLIT_233
#define QOR_PP_SEQ_SPLIT_235(x) (x) QOR_PP_SEQ_SPLIT_234
#define QOR_PP_SEQ_SPLIT_236(x) (x) QOR_PP_SEQ_SPLIT_235
#define QOR_PP_SEQ_SPLIT_237(x) (x) QOR_PP_SEQ_SPLIT_236
#define QOR_PP_SEQ_SPLIT_238(x) (x) QOR_PP_SEQ_SPLIT_237
#define QOR_PP_SEQ_SPLIT_239(x) (x) QOR_PP_SEQ_SPLIT_238
#define QOR_PP_SEQ_SPLIT_240(x) (x) QOR_PP_SEQ_SPLIT_239
#define QOR_PP_SEQ_SPLIT_241(x) (x) QOR_PP_SEQ_SPLIT_240
#define QOR_PP_SEQ_SPLIT_242(x) (x) QOR_PP_SEQ_SPLIT_241
#define QOR_PP_SEQ_SPLIT_243(x) (x) QOR_PP_SEQ_SPLIT_242
#define QOR_PP_SEQ_SPLIT_244(x) (x) QOR_PP_SEQ_SPLIT_243
#define QOR_PP_SEQ_SPLIT_245(x) (x) QOR_PP_SEQ_SPLIT_244
#define QOR_PP_SEQ_SPLIT_246(x) (x) QOR_PP_SEQ_SPLIT_245
#define QOR_PP_SEQ_SPLIT_247(x) (x) QOR_PP_SEQ_SPLIT_246
#define QOR_PP_SEQ_SPLIT_248(x) (x) QOR_PP_SEQ_SPLIT_247
#define QOR_PP_SEQ_SPLIT_249(x) (x) QOR_PP_SEQ_SPLIT_248
#define QOR_PP_SEQ_SPLIT_250(x) (x) QOR_PP_SEQ_SPLIT_249
#define QOR_PP_SEQ_SPLIT_251(x) (x) QOR_PP_SEQ_SPLIT_250
#define QOR_PP_SEQ_SPLIT_252(x) (x) QOR_PP_SEQ_SPLIT_251
#define QOR_PP_SEQ_SPLIT_253(x) (x) QOR_PP_SEQ_SPLIT_252
#define QOR_PP_SEQ_SPLIT_254(x) (x) QOR_PP_SEQ_SPLIT_253
#define QOR_PP_SEQ_SPLIT_255(x) (x) QOR_PP_SEQ_SPLIT_254
#define QOR_PP_SEQ_SPLIT_256(x) (x) QOR_PP_SEQ_SPLIT_255

#endif//QOR_PREPROCESSOR_SEQ_DETAIL_SPLIT_H_1
