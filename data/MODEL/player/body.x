xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 283;
 -5.81156;9.99359;5.40704;,
 -5.80471;9.92545;-6.00750;,
 -11.26457;7.70649;-5.85848;,
 -11.27489;7.71266;8.80067;,
 -4.40009;4.34497;-9.74529;,
 -5.50514;8.35681;-6.01825;,
 -8.90644;7.59846;-6.78969;,
 -7.08500;3.58653;-9.20004;,
 -6.28728;-8.02449;-5.82840;,
 -5.80382;-7.93447;4.04875;,
 -6.28900;-10.46702;3.86405;,
 -6.58696;-10.46702;-5.84372;,
 -0.10819;4.34497;-9.74529;,
 -0.10819;3.58653;-9.20004;,
 -11.66197;-4.69634;6.32489;,
 -11.66197;-1.09619;6.32489;,
 -10.79922;-1.95117;6.32489;,
 -10.79922;-5.55140;6.32489;,
 -0.10819;9.99359;5.40704;,
 -0.10819;7.71266;8.80067;,
 -4.52441;5.33337;-11.64751;,
 -6.78642;3.90731;-12.12604;,
 -7.11582;3.31124;-12.24824;,
 -7.11582;-6.06574;-12.24824;,
 -11.66197;-9.92178;-5.84372;,
 -11.66197;7.16750;-5.84372;,
 -7.11582;-6.06574;-12.24824;,
 -6.35233;-5.88345;-12.72722;,
 -6.56618;-6.61740;-12.23495;,
 -7.11582;3.31124;-12.24824;,
 -6.78642;3.90731;-12.12604;,
 -6.35233;3.12887;-12.72722;,
 -11.66197;7.16837;9.54286;,
 -0.10819;7.16837;9.54286;,
 -11.10697;-10.46702;-5.84372;,
 -11.10772;-10.46702;9.01081;,
 -11.66197;-9.92280;9.54286;,
 -11.66197;-9.92178;-5.84372;,
 -11.27489;7.71266;8.80067;,
 -11.26457;7.70649;-5.85848;,
 -11.66197;7.16837;9.54286;,
 -0.10819;-6.61740;-12.23495;,
 -0.10819;-5.88345;-12.72722;,
 -6.78642;3.90731;-12.12604;,
 -6.56618;-6.61740;-12.23495;,
 -7.11582;-6.06574;-12.24824;,
 -0.10819;9.80215;5.20694;,
 -5.70361;9.80215;5.20694;,
 -5.70361;9.80215;5.20694;,
 -5.50514;9.37620;-6.01825;,
 -5.80471;9.92545;-6.00750;,
 -5.81156;9.99359;5.40704;,
 -4.40009;5.10115;-9.74529;,
 -4.52441;5.33337;-11.64751;,
 -0.10819;-8.29700;10.18554;,
 -10.24702;-8.29700;10.18554;,
 -11.66197;-9.92280;9.54286;,
 -0.10819;-9.92280;9.54286;,
 -10.24702;-8.23802;10.18554;,
 -11.66197;7.16837;9.54286;,
 -11.66197;-4.69634;6.32489;,
 -11.66197;-4.69583;-3.49160;,
 -11.66197;-9.92280;9.54286;,
 -11.66197;-1.09655;-3.49160;,
 -11.66197;-1.09619;6.32489;,
 -10.79922;-5.55140;6.32489;,
 -10.79922;-1.95117;6.32489;,
 -10.79922;-1.95162;-3.49160;,
 -10.79922;-5.55092;-3.49160;,
 -11.66197;-4.69583;-3.49160;,
 -11.66197;-4.69634;6.32489;,
 -10.79922;-5.55140;6.32489;,
 -10.79922;-5.55092;-3.49160;,
 -11.66197;-1.09655;-3.49160;,
 -11.66197;-4.69583;-3.49160;,
 -10.79922;-5.55092;-3.49160;,
 -10.79922;-1.95162;-3.49160;,
 -11.66197;-1.09619;6.32489;,
 -11.66197;-1.09655;-3.49160;,
 -10.79922;-1.95162;-3.49160;,
 -10.79922;-1.95117;6.32489;,
 -0.10819;-8.23802;10.18554;,
 -0.10819;7.16837;9.54286;,
 -4.40009;5.10115;-9.74529;,
 -0.10819;5.10115;-9.74529;,
 -0.10819;5.33337;-11.64751;,
 -0.10819;3.90731;-12.12604;,
 -0.10819;3.12887;-12.72722;,
 -11.10772;-10.46702;9.01081;,
 -0.10819;-10.46702;9.01081;,
 -0.10819;3.90731;-12.12604;,
 -0.10819;-6.61740;-12.23495;,
 -0.10819;-9.65450;-7.82597;,
 -6.05240;-9.65450;-7.82597;,
 -6.58696;-10.46702;-5.84372;,
 -5.70361;9.80215;5.20694;,
 -0.10819;9.80215;5.20694;,
 -0.10819;8.64089;5.36950;,
 -5.50514;8.64089;5.36950;,
 -5.50514;8.64089;5.36950;,
 -5.50514;8.35681;-6.01825;,
 -0.10819;5.10115;-9.74529;,
 -4.40009;5.10115;-9.74529;,
 -4.40009;4.34497;-9.74529;,
 -7.08500;3.58653;-9.20004;,
 -8.90644;7.59846;-6.78969;,
 -5.69941;-7.84458;-7.63661;,
 -5.69941;-7.84458;-7.63661;,
 -0.10819;-7.93447;-7.70737;,
 -8.90644;7.66763;6.81274;,
 -8.90644;7.66763;6.81274;,
 -0.10819;7.66763;6.81274;,
 -0.10819;-7.93447;4.04875;,
 -5.80382;-7.93447;4.04875;,
 -5.50514;8.64089;5.36950;,
 -0.10819;8.64089;5.36950;,
 -0.10819;7.66763;6.81274;,
 -8.90644;7.66763;6.81274;,
 -5.50514;8.35681;-6.01825;,
 -8.90644;7.59846;-6.78969;,
 -6.28900;-10.46702;3.86405;,
 -0.10819;-10.46702;4.29605;,
 -6.05240;-9.65450;-7.82597;,
 -6.05240;-9.65450;-7.82597;,
 -0.10819;-9.65450;-7.82597;,
 -0.10819;-10.46702;9.01081;,
 -6.28900;-10.46702;3.86405;,
 -0.10819;-10.46702;4.29605;,
 -5.53159;9.34888;-6.03049;,
 -0.55784;8.92233;-6.11383;,
 -5.41070;8.69808;4.25811;,
 -5.75638;8.96349;5.39461;,
 -5.41070;8.69808;4.25811;,
 -0.55784;8.92233;-6.11383;,
 0.52700;13.25035;-1.80491;,
 -2.83782;13.25035;2.68271;,
 -5.75638;8.96349;5.39461;,
 -3.35805;13.64547;3.07101;,
 -3.51486;13.46205;-1.66128;,
 -5.53159;9.34888;-6.03049;,
 0.52700;13.25035;-1.80491;,
 -0.55784;8.92233;-6.11383;,
 -5.53159;9.34888;-6.03049;,
 -3.51486;13.46205;-1.66128;,
 -2.86704;13.63171;3.52562;,
 -5.25443;8.96349;5.84923;,
 -0.10819;8.96349;5.57178;,
 -0.10819;13.76880;3.79318;,
 -4.90005;8.69808;4.71309;,
 -5.25443;8.96349;5.84923;,
 -0.10819;8.96349;5.57178;,
 -0.10819;8.69808;4.55552;,
 -5.41070;8.69808;4.25811;,
 -2.83782;13.25035;2.68271;,
 -2.32712;13.25035;3.13767;,
 -4.90005;8.69808;4.71309;,
 -3.35805;13.64547;3.07101;,
 -5.75638;8.96349;5.39461;,
 -0.10819;13.25035;3.52511;,
 -0.10819;8.69808;4.55552;,
 10.03062;-8.29700;10.18554;,
 10.03062;5.54254;10.18554;,
 5.59515;9.99359;5.40704;,
 11.05850;7.71266;8.80067;,
 11.04815;7.70649;-5.85848;,
 5.58826;9.92545;-6.00750;,
 4.18369;4.34497;-9.74529;,
 6.86860;3.58653;-9.20004;,
 8.69003;7.59846;-6.78969;,
 5.28865;8.35681;-6.01825;,
 6.07087;-8.02449;-5.82840;,
 6.37056;-10.46702;-5.84372;,
 6.07260;-10.46702;3.86405;,
 5.58741;-7.93447;4.04875;,
 11.44554;-4.69634;6.32489;,
 10.58280;-5.55140;6.32489;,
 10.58280;-1.95117;6.32489;,
 11.44554;-1.09619;6.32489;,
 6.56997;3.90731;-12.12604;,
 4.30796;5.33337;-11.64751;,
 6.89938;3.31124;-12.24824;,
 11.44554;7.16750;-5.84372;,
 11.44554;-9.92178;-5.84372;,
 6.89938;-6.06574;-12.24824;,
 6.89938;-6.06574;-12.24824;,
 6.34976;-6.61740;-12.23495;,
 6.13593;-5.88345;-12.72722;,
 6.89938;3.31124;-12.24824;,
 6.13593;3.12887;-12.72722;,
 6.56997;3.90731;-12.12604;,
 11.44554;7.16837;9.54286;,
 10.89058;-10.46702;-5.84372;,
 11.44554;-9.92178;-5.84372;,
 11.44554;-9.92280;9.54286;,
 10.89131;-10.46702;9.01081;,
 11.05850;7.71266;8.80067;,
 11.44554;7.16837;9.54286;,
 11.04815;7.70649;-5.85848;,
 6.56997;3.90731;-12.12604;,
 6.34976;-6.61740;-12.23495;,
 6.89938;-6.06574;-12.24824;,
 5.48721;9.80215;5.20694;,
 5.48721;9.80215;5.20694;,
 5.59515;9.99359;5.40704;,
 5.58826;9.92545;-6.00750;,
 5.28865;9.37620;-6.01825;,
 4.30796;5.33337;-11.64751;,
 4.18369;5.10115;-9.74529;,
 11.44554;-9.92280;9.54286;,
 11.44554;7.16837;9.54286;,
 11.44554;-4.69634;6.32489;,
 11.44554;-9.92280;9.54286;,
 11.44554;-4.69583;-3.49160;,
 11.44554;-1.09655;-3.49160;,
 11.44554;-1.09619;6.32489;,
 10.58280;-5.55140;6.32489;,
 10.58280;-5.55092;-3.49160;,
 10.58280;-1.95162;-3.49160;,
 10.58280;-1.95117;6.32489;,
 11.44554;-4.69583;-3.49160;,
 10.58280;-5.55092;-3.49160;,
 10.58280;-5.55140;6.32489;,
 11.44554;-4.69634;6.32489;,
 11.44554;-1.09655;-3.49160;,
 10.58280;-1.95162;-3.49160;,
 10.58280;-5.55092;-3.49160;,
 11.44554;-4.69583;-3.49160;,
 11.44554;-1.09619;6.32489;,
 10.58280;-1.95117;6.32489;,
 10.58280;-1.95162;-3.49160;,
 11.44554;-1.09655;-3.49160;,
 4.18369;5.10115;-9.74529;,
 10.89131;-10.46702;9.01081;,
 6.37056;-10.46702;-5.84372;,
 5.83596;-9.65450;-7.82597;,
 5.48721;9.80215;5.20694;,
 5.28865;8.64089;5.36950;,
 5.28865;8.35681;-6.01825;,
 5.28865;8.64089;5.36950;,
 4.18369;5.10115;-9.74529;,
 4.18369;4.34497;-9.74529;,
 6.86860;3.58653;-9.20004;,
 5.48301;-7.84458;-7.63661;,
 8.69003;7.59846;-6.78969;,
 5.48301;-7.84458;-7.63661;,
 8.69003;7.66763;6.81274;,
 8.69003;7.66763;6.81274;,
 5.58741;-7.93447;4.04875;,
 5.28865;8.64089;5.36950;,
 8.69003;7.66763;6.81274;,
 5.28865;8.35681;-6.01825;,
 8.69003;7.59846;-6.78969;,
 6.07260;-10.46702;3.86405;,
 5.83596;-9.65450;-7.82597;,
 5.83596;-9.65450;-7.82597;,
 6.07260;-10.46702;3.86405;,
 5.22331;8.33826;-6.07643;,
 5.53998;8.96349;5.39461;,
 5.19425;8.69808;4.25811;,
 -0.57727;8.92233;-6.11383;,
 5.19425;8.69808;4.25811;,
 2.62138;13.25035;2.68271;,
 -0.74339;13.25035;-1.80491;,
 -0.57727;8.92233;-6.11383;,
 5.53998;8.96349;5.39461;,
 5.22331;8.33826;-6.07643;,
 3.29841;13.46205;-1.66128;,
 3.14165;13.64547;3.07101;,
 -0.74339;13.25035;-1.80491;,
 3.29841;13.46205;-1.66128;,
 5.22331;8.33826;-6.07643;,
 -0.57727;8.92233;-6.11383;,
 2.65063;13.63171;3.52562;,
 5.03803;8.96349;5.84923;,
 5.03803;8.96349;5.84923;,
 4.68360;8.69808;4.71309;,
 5.19425;8.69808;4.25811;,
 4.68360;8.69808;4.71309;,
 2.11068;13.25035;3.13767;,
 2.62138;13.25035;2.68271;,
 5.53998;8.96349;5.39461;,
 3.14165;13.64547;3.07101;,
 6.37069;-10.46713;-5.84414;;
 
 136;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,4,7,13;,
 4;14,15,16,17;,
 4;18,0,3,19;,
 4;1,20,21,2;,
 4;22,23,24,25;,
 3;26,27,28;,
 3;29,30,31;,
 4;19,3,32,33;,
 4;34,35,36,37;,
 4;38,39,25,40;,
 4;31,27,26,29;,
 4;41,28,27,42;,
 4;39,43,22,25;,
 4;44,34,37,45;,
 4;46,47,0,18;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;60,61,24,62;,
 4;63,64,40,25;,
 4;64,60,62,40;,
 4;61,63,25,24;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;58,81,82,59;,
 4;83,84,85,20;,
 4;30,86,87,31;,
 4;88,89,57,56;,
 4;20,85,90,21;,
 4;27,31,87,42;,
 3;91,92,44;,
 3;92,93,44;,
 3;93,94,44;,
 3;94,34,44;,
 4;95,96,97,98;,
 4;49,48,99,100;,
 4;101,102,4,12;,
 4;52,49,100,103;,
 4;104,105,8,106;,
 4;13,7,107,108;,
 4;105,109,9,8;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,114,117,119;,
 4;120,113,112,121;,
 4;106,8,11,122;,
 4;107,123,124,108;,
 4;125,35,126,127;,
 4;34,94,126,35;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;131,130,148,149;,
 4;150,149,148,151;,
 4;152,153,154,155;,
 4;145,144,156,157;,
 4;154,158,159,155;,
 4;54,160,161,81;,
 4;162,163,164,165;,
 4;166,167,168,169;,
 4;170,171,172,173;,
 4;12,13,167,166;,
 4;174,175,176,177;,
 4;18,19,163,162;,
 4;165,164,178,179;,
 4;180,181,182,183;,
 3;184,185,186;,
 3;187,188,189;,
 4;19,33,190,163;,
 4;191,192,193,194;,
 4;195,196,181,197;,
 4;188,187,184,186;,
 4;41,42,186,185;,
 4;197,181,180,198;,
 4;199,200,192,191;,
 4;46,18,162,201;,
 4;202,203,204,205;,
 4;205,204,206,207;,
 4;54,57,208,160;,
 4;160,208,209,161;,
 4;210,211,182,212;,
 4;213,181,196,214;,
 4;214,196,211,210;,
 4;212,182,181,213;,
 4;215,216,217,218;,
 4;219,220,221,222;,
 4;223,224,225,226;,
 4;227,228,229,230;,
 4;161,209,82,81;,
 4;231,179,85,84;,
 4;189,188,87,86;,
 4;232,208,57,89;,
 4;179,178,90,85;,
 4;186,42,87,188;,
 3;191,233,199;,
 3;233,234,199;,
 3;199,234,91;,
 3;234,92,91;,
 4;235,236,97,96;,
 4;205,237,238,202;,
 4;101,12,166,239;,
 4;207,240,237,205;,
 4;241,242,170,243;,
 4;13,108,244,167;,
 4;243,170,173,245;,
 4;246,247,112,111;,
 4;248,249,116,115;,
 4;250,251,249,248;,
 4;252,121,112,247;,
 4;242,253,171,170;,
 4;244,108,124,254;,
 4;125,127,255,194;,
 4;191,194,255,233;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,147,146,273;,
 4;257,274,275,258;,
 4;150,151,275,274;,
 4;276,277,278,279;,
 4;273,280,281,272;,
 4;278,277,159,158;,
 4;255,127,126,94;,
 4;234,255,94,93;,
 4;172,253,171,282;,
 3;49,231,83;,
 3;49,237,231;;
 
 MeshMaterialList {
  2;
  136;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.068800;0.800000;0.552000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  173;
  -0.594392;-0.248898;-0.764688;,
  -0.250629;-0.262280;-0.931877;,
  -0.217845;-0.714351;-0.665016;,
  -0.121368;0.801717;-0.585252;,
  0.976433;0.196039;0.090266;,
  -0.250040;-0.968235;-0.000015;,
  -0.215184;-0.191286;0.957656;,
  0.000000;0.328028;-0.944668;,
  -0.202827;0.933674;0.295152;,
  0.968495;0.244755;0.045954;,
  -0.364791;0.865361;-0.343625;,
  -1.000000;0.000000;0.000000;,
  -0.343481;-0.876022;-0.338535;,
  -0.335060;0.885373;0.322257;,
  -0.211606;0.021327;0.977122;,
  -0.574254;0.732014;-0.366590;,
  -0.967187;-0.254066;0.000010;,
  -0.611220;0.217787;-0.760907;,
  -0.273363;0.516319;-0.811595;,
  -0.254867;0.271128;-0.928188;,
  0.000000;0.000000;-1.000000;,
  -0.966835;-0.255402;-0.000015;,
  -0.915920;-0.281426;-0.286164;,
  -0.932897;0.227211;-0.279424;,
  -0.154710;0.317268;0.935631;,
  -0.923017;-0.384760;0.000016;,
  0.000000;-0.921701;0.387901;,
  0.000000;-0.544061;0.839045;,
  0.000000;0.818347;0.574724;,
  -0.007823;0.507699;0.861499;,
  0.000000;-0.729309;-0.684185;,
  0.000000;-0.291122;-0.956686;,
  0.000000;0.471229;-0.882011;,
  0.000000;0.322914;-0.946428;,
  0.000000;0.328028;-0.944668;,
  0.000000;0.829955;0.557830;,
  0.000000;0.992631;0.121179;,
  0.000000;-0.248985;0.968507;,
  -0.009604;0.083439;0.996467;,
  0.066461;-0.304731;0.950117;,
  0.000000;-0.529733;-0.848165;,
  0.207181;-0.864549;0.457855;,
  0.000000;0.306632;0.951828;,
  -0.000000;0.078103;-0.996945;,
  0.999393;0.012963;-0.032347;,
  0.990275;0.006558;0.138971;,
  0.951880;-0.000051;0.306472;,
  0.071972;-0.240841;0.967892;,
  -0.000000;0.022918;0.999737;,
  0.000000;0.174439;-0.984668;,
  -0.000000;0.368922;0.929461;,
  0.983565;0.178763;-0.025365;,
  0.987448;-0.153196;-0.038431;,
  -0.000000;-0.019029;-0.999819;,
  0.981167;-0.161531;0.105925;,
  0.000000;-0.823525;-0.567280;,
  -0.174609;-0.884465;-0.432706;,
  -0.407735;-0.911568;-0.052870;,
  0.751725;-0.493381;0.437590;,
  -0.000000;-0.970290;0.241943;,
  -0.000001;-0.266601;-0.963807;,
  -0.892247;0.451527;0.004426;,
  0.000000;0.386746;0.922186;,
  -0.287949;-0.955549;0.063334;,
  -0.074910;-0.974685;0.210662;,
  0.333458;-0.424000;-0.842039;,
  -0.303395;0.509710;0.805076;,
  -0.768322;0.551110;0.325515;,
  0.594403;-0.248894;-0.764681;,
  0.250639;-0.262281;-0.931874;,
  0.254698;-0.690010;-0.677506;,
  0.121368;0.801717;-0.585252;,
  -0.976434;0.196043;0.090248;,
  0.250048;-0.968233;-0.000015;,
  0.142908;-0.127035;0.981549;,
  0.000000;0.328028;-0.944668;,
  0.202826;0.933674;0.295152;,
  -0.968492;0.244768;0.045947;,
  0.364790;0.865361;-0.343626;,
  1.000000;0.000000;0.000000;,
  0.343491;-0.876017;-0.338537;,
  0.335066;0.885370;0.322258;,
  0.131749;0.071065;0.988733;,
  0.574260;0.732009;-0.366591;,
  0.967187;-0.254064;0.000010;,
  0.611228;0.217789;-0.760900;,
  0.273365;0.516321;-0.811593;,
  0.254876;0.271132;-0.928184;,
  0.966837;-0.255394;-0.000015;,
  0.915923;-0.281417;-0.286163;,
  0.932899;0.227205;-0.279424;,
  0.142201;0.374655;0.916195;,
  0.923018;-0.384757;0.000016;,
  -0.066462;-0.304732;0.950116;,
  0.000000;-0.529732;-0.848165;,
  -0.207178;-0.864550;0.457854;,
  -0.999393;0.012961;-0.032347;,
  -0.990275;0.006559;0.138972;,
  -0.951879;-0.000047;0.306474;,
  -0.071973;-0.240842;0.967892;,
  -0.983565;0.178763;-0.025365;,
  -0.904846;-0.424534;-0.032004;,
  -0.937496;-0.341868;0.065016;,
  0.143923;-0.871354;-0.469072;,
  0.234601;-0.971480;0.034484;,
  -0.787023;-0.348881;0.508799;,
  0.905580;0.423816;-0.017483;,
  0.197738;-0.974462;0.106413;,
  0.074908;-0.974685;0.210660;,
  -0.333459;-0.423999;-0.842039;,
  0.303395;0.509709;0.805076;,
  0.780372;0.539711;0.315803;,
  -0.749416;-0.661700;-0.023002;,
  0.000000;0.583722;0.811953;,
  -0.978905;0.204318;-0.000148;,
  0.000000;0.722570;-0.691298;,
  0.000000;0.722570;-0.691298;,
  0.956529;0.291630;0.002165;,
  0.899634;0.432939;-0.056763;,
  0.873957;0.485996;-0.002535;,
  0.919540;0.377104;-0.110627;,
  -0.147700;-0.380972;0.912713;,
  0.703941;0.710259;0.000036;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.933713;-0.358022;,
  0.000000;-0.699066;0.715057;,
  0.000000;0.318128;-0.948048;,
  -0.105257;-0.962506;-0.250004;,
  0.996422;0.084252;0.006769;,
  0.988205;0.042584;0.147097;,
  0.958746;0.000000;0.284264;,
  0.919808;0.166381;0.355347;,
  0.969943;0.175882;0.168156;,
  0.006573;0.022917;0.999716;,
  0.017550;0.078091;-0.996792;,
  0.000000;-0.829096;-0.559107;,
  0.129177;-0.949086;-0.287313;,
  0.244796;-0.969464;0.014637;,
  0.034929;-0.019018;-0.999209;,
  0.954332;-0.166482;0.248062;,
  0.005760;-0.086435;0.996241;,
  -0.000000;-0.086436;0.996257;,
  0.000000;-1.000000;-0.000000;,
  0.030679;0.710004;-0.703529;,
  0.561719;-0.535675;-0.630494;,
  0.000000;0.583722;0.811953;,
  0.978907;0.204308;-0.000148;,
  0.000000;0.722570;-0.691298;,
  -0.956522;0.291651;0.002169;,
  -0.873954;0.486002;-0.002531;,
  -0.899631;0.432945;-0.056768;,
  -0.919536;0.377112;-0.110640;,
  0.147703;-0.380972;0.912713;,
  -0.703945;0.710255;0.000036;,
  0.025702;0.878141;-0.477710;,
  0.187397;-0.921265;-0.340812;,
  -0.988205;0.042603;0.147088;,
  -0.996418;0.084290;0.006772;,
  -0.958752;0.000000;0.284243;,
  -0.919809;0.166380;0.355343;,
  -0.969943;0.175882;0.168154;,
  -0.006573;0.022917;0.999716;,
  -0.017550;0.078091;-0.996792;,
  -0.129174;-0.949087;-0.287313;,
  -0.244791;-0.969465;0.014637;,
  -0.034929;-0.019018;-0.999209;,
  -0.893094;-0.434123;0.117979;,
  -0.005760;-0.086435;0.996241;,
  0.006864;-0.998338;-0.057227;,
  0.030106;0.686684;-0.726333;,
  -0.561720;-0.535674;-0.630495;,
  0.035071;0.700717;-0.712577;,
  0.069973;0.740911;-0.667948;;
  136;
  4;8,10,15,13;,
  4;39,41,41,47;,
  4;45,44,52,54;,
  4;42,113,113,50;,
  4;20,20,20,20;,
  4;35,8,13,28;,
  4;10,3,18,15;,
  4;17,0,22,23;,
  3;0,1,2;,
  3;17,18,19;,
  4;28,13,24,29;,
  4;12,5,21,22;,
  4;13,15,23,114;,
  4;19,1,0,17;,
  4;30,2,1,31;,
  4;15,18,17,23;,
  4;2,12,22,0;,
  4;34,7,115,116;,
  4;117,9,118,119;,
  4;9,4,120,118;,
  4;37,6,121,27;,
  4;6,14,24,121;,
  4;11,11,22,21;,
  4;16,16,114,23;,
  4;16,11,21,114;,
  4;11,16,23,22;,
  4;11,25,25,11;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;16,16,25,25;,
  4;14,38,29,24;,
  4;124,36,36,3;,
  4;18,32,33,19;,
  4;125,26,27,121;,
  4;3,126,32,18;,
  4;1,19,33,31;,
  3;30,55,2;,
  3;55,56,2;,
  3;56,127,2;,
  3;127,12,2;,
  4;7,34,40,40;,
  4;9,117,128,129;,
  4;123,123,39,42;,
  4;4,9,129,130;,
  4;131,132,45,46;,
  4;50,47,133,48;,
  4;132,51,44,45;,
  4;49,49,43,134;,
  4;40,40,135,136;,
  4;41,137,136,41;,
  4;138,134,43,53;,
  4;46,45,54,139;,
  4;133,140,141,48;,
  4;26,5,142,142;,
  4;12,127,142,5;,
  4;57,57,63,63;,
  4;58,58,58,58;,
  4;67,67,61,61;,
  4;143,143,143,143;,
  4;66,66,62,62;,
  4;63,63,64,64;,
  4;59,64,64,59;,
  4;144,144,65,65;,
  4;66,66,67,67;,
  4;65,60,60,65;,
  4;37,74,82,38;,
  4;76,81,83,78;,
  4;93,99,95,95;,
  4;97,102,101,96;,
  4;42,50,145,145;,
  4;20,20,20,20;,
  4;35,28,81,76;,
  4;78,83,86,71;,
  4;85,90,89,68;,
  3;68,70,69;,
  3;85,87,86;,
  4;28,29,91,81;,
  4;80,89,88,73;,
  4;81,146,90,83;,
  4;87,85,68,69;,
  4;30,31,69,70;,
  4;83,90,85,86;,
  4;70,68,89,80;,
  4;34,116,147,75;,
  4;148,149,150,77;,
  4;77,150,151,72;,
  4;37,27,152,74;,
  4;74,152,91,82;,
  4;79,88,89,79;,
  4;84,90,146,84;,
  4;84,146,88,79;,
  4;79,89,90,84;,
  4;79,79,92,92;,
  4;153,153,153,153;,
  4;123,123,123,123;,
  4;84,92,92,84;,
  4;82,91,29,38;,
  4;154,71,36,36;,
  4;86,87,33,32;,
  4;125,152,27,26;,
  4;71,86,32,126;,
  4;69,31,33,87;,
  3;80,155,70;,
  3;155,103,70;,
  3;70,103,30;,
  3;103,55,30;,
  4;75,94,40,34;,
  4;77,156,157,148;,
  4;123,42,93,123;,
  4;72,158,156,77;,
  4;159,98,97,160;,
  4;50,48,161,99;,
  4;160,97,96,100;,
  4;49,162,43,49;,
  4;94,163,135,40;,
  4;95,95,163,164;,
  4;165,53,43,162;,
  4;98,166,102,97;,
  4;161,48,141,167;,
  4;26,142,168,73;,
  4;80,73,168,155;,
  4;104,107,107,104;,
  4;105,105,105,105;,
  4;111,106,106,111;,
  4;169,169,169,169;,
  4;110,62,62,110;,
  4;107,108,108,107;,
  4;59,59,108,108;,
  4;170,109,109,170;,
  4;110,111,111,110;,
  4;109,109,60,60;,
  4;168,142,142,127;,
  4;103,168,127,56;,
  4;101,166,102,112;,
  3;171,154,124;,
  3;171,172,154;;
 }
 MeshTextureCoords {
  283;
  0.556380;0.399780;,
  0.556260;0.326650;,
  0.591570;0.325990;,
  0.591730;0.419860;,
  0.282870;0.605380;,
  0.285490;0.578340;,
  0.307950;0.579670;,
  0.300700;0.607330;,
  0.563500;0.568060;,
  0.627050;0.567480;,
  0.625940;0.583800;,
  0.563450;0.583800;,
  0.255580;0.609890;,
  0.256350;0.614650;,
  0.523490;0.965060;,
  0.523490;0.988220;,
  0.517930;0.982720;,
  0.517930;0.959550;,
  0.519630;0.399780;,
  0.519780;0.419860;,
  0.548240;0.287210;,
  0.562870;0.263900;,
  0.246360;0.442530;,
  0.185940;0.442530;,
  0.161190;0.381520;,
  0.271310;0.381520;,
  0.872490;0.954720;,
  0.877470;0.953380;,
  0.876030;0.958270;,
  0.872490;0.894380;,
  0.874600;0.890590;,
  0.877470;0.895390;,
  0.594260;0.424220;,
  0.519810;0.424220;,
  0.674240;0.363040;,
  0.674240;0.267320;,
  0.677860;0.263900;,
  0.677860;0.363050;,
  0.274810;0.287200;,
  0.274780;0.381650;,
  0.271310;0.282380;,
  0.917640;0.958320;,
  0.917700;0.953420;,
  0.250190;0.441780;,
  0.645270;0.423600;,
  0.648860;0.423690;,
  0.519640;0.398360;,
  0.555690;0.398360;,
  0.517080;0.595220;,
  0.503290;0.666280;,
  0.499870;0.665360;,
  0.516180;0.593660;,
  0.524600;0.696110;,
  0.520360;0.707680;,
  0.654470;0.758250;,
  0.719800;0.758240;,
  0.728940;0.768790;,
  0.654490;0.768790;,
  0.719800;0.669080;,
  0.728940;0.658670;,
  0.194860;0.303110;,
  0.194870;0.366360;,
  0.161180;0.282380;,
  0.218060;0.366360;,
  0.218060;0.303110;,
  0.221840;0.843580;,
  0.245040;0.843580;,
  0.245040;0.906830;,
  0.221850;0.906830;,
  0.242330;0.726310;,
  0.242330;0.789550;,
  0.236830;0.789410;,
  0.236830;0.726170;,
  0.862190;0.959190;,
  0.862190;0.982380;,
  0.856630;0.987890;,
  0.856630;0.964700;,
  0.102410;0.480080;,
  0.102410;0.416830;,
  0.108030;0.416840;,
  0.108030;0.480090;,
  0.654470;0.669080;,
  0.654490;0.658680;,
  0.547460;0.299220;,
  0.519810;0.299220;,
  0.519780;0.287210;,
  0.917630;0.890640;,
  0.917700;0.895430;,
  0.725390;0.772350;,
  0.654510;0.772360;,
  0.519840;0.263900;,
  0.603660;0.423600;,
  0.603430;0.375820;,
  0.641730;0.375820;,
  0.645110;0.363040;,
  0.978820;0.838290;,
  0.978820;0.874340;,
  0.971290;0.874320;,
  0.971290;0.839560;,
  0.524600;0.595930;,
  0.509680;0.667780;,
  0.254790;0.605080;,
  0.282070;0.600580;,
  0.529340;0.697210;,
  0.541920;0.493250;,
  0.557740;0.467410;,
  0.551760;0.566890;,
  0.303800;0.681290;,
  0.268350;0.687740;,
  0.645360;0.466970;,
  0.093350;0.623380;,
  0.150040;0.623640;,
  0.150040;0.723040;,
  0.113340;0.722870;,
  0.339680;0.883150;,
  0.374460;0.883150;,
  0.374530;0.892460;,
  0.317840;0.892460;,
  0.339710;0.809770;,
  0.317850;0.804810;,
  0.110180;0.739090;,
  0.149950;0.739420;,
  0.550590;0.578560;,
  0.307950;0.692450;,
  0.270160;0.698680;,
  0.603370;0.267320;,
  0.643190;0.300490;,
  0.603370;0.297700;,
  0.902560;0.647450;,
  0.898850;0.649070;,
  0.900120;0.596170;,
  0.902560;0.588910;,
  0.108090;0.930440;,
  0.108090;0.983380;,
  0.077190;0.968660;,
  0.078340;0.939820;,
  0.285170;0.986900;,
  0.254790;0.972250;,
  0.255410;0.941760;,
  0.285170;0.928390;,
  0.988700;0.112130;,
  0.988700;0.145970;,
  0.984250;0.145130;,
  0.985980;0.111950;,
  0.542820;0.949580;,
  0.572630;0.934270;,
  0.572680;0.967420;,
  0.541920;0.967370;,
  0.896910;0.593150;,
  0.899400;0.585900;,
  0.866200;0.586830;,
  0.866020;0.593380;,
  0.237230;0.964800;,
  0.207410;0.948000;,
  0.207580;0.944770;,
  0.237400;0.961570;,
  0.542780;0.946400;,
  0.572680;0.931020;,
  0.207740;0.930520;,
  0.237400;0.930680;,
  0.719800;0.758240;,
  0.719800;0.669080;,
  0.556380;0.399780;,
  0.591730;0.419860;,
  0.591570;0.325990;,
  0.556260;0.326650;,
  0.282870;0.605380;,
  0.300700;0.607330;,
  0.307950;0.579670;,
  0.285490;0.578340;,
  0.563500;0.568060;,
  0.563450;0.583800;,
  0.625940;0.583800;,
  0.627050;0.567480;,
  0.523490;0.965060;,
  0.517930;0.959550;,
  0.517930;0.982720;,
  0.523490;0.988220;,
  0.562870;0.263900;,
  0.548240;0.287210;,
  0.246360;0.442530;,
  0.271310;0.381520;,
  0.161190;0.381520;,
  0.185940;0.442530;,
  0.872490;0.954720;,
  0.876030;0.958270;,
  0.877470;0.953380;,
  0.872490;0.894380;,
  0.877470;0.895390;,
  0.874600;0.890590;,
  0.594260;0.424220;,
  0.674240;0.363040;,
  0.677860;0.363050;,
  0.677860;0.263900;,
  0.674240;0.267320;,
  0.274810;0.287200;,
  0.271310;0.282380;,
  0.274780;0.381650;,
  0.250190;0.441780;,
  0.645270;0.423600;,
  0.648860;0.423690;,
  0.555690;0.398360;,
  0.517080;0.595220;,
  0.516180;0.593660;,
  0.499870;0.665360;,
  0.503290;0.666280;,
  0.520360;0.707680;,
  0.524600;0.696110;,
  0.728940;0.768790;,
  0.728940;0.658670;,
  0.194860;0.303110;,
  0.161180;0.282380;,
  0.194870;0.366360;,
  0.218060;0.366360;,
  0.218060;0.303110;,
  0.221840;0.843580;,
  0.221850;0.906830;,
  0.245040;0.906830;,
  0.245040;0.843580;,
  0.242330;0.726310;,
  0.236830;0.726170;,
  0.236830;0.789410;,
  0.242330;0.789550;,
  0.862190;0.959190;,
  0.856630;0.964700;,
  0.856630;0.987890;,
  0.862190;0.982380;,
  0.102410;0.480080;,
  0.108030;0.480090;,
  0.108030;0.416840;,
  0.102410;0.416830;,
  0.547460;0.299220;,
  0.725390;0.772350;,
  0.645110;0.363040;,
  0.641730;0.375820;,
  0.978820;0.838290;,
  0.971290;0.839560;,
  0.509680;0.667780;,
  0.524600;0.595930;,
  0.282070;0.600580;,
  0.529340;0.697210;,
  0.541920;0.493250;,
  0.551760;0.566890;,
  0.557740;0.467410;,
  0.303800;0.681290;,
  0.645360;0.466970;,
  0.093350;0.623380;,
  0.113340;0.722870;,
  0.339680;0.883150;,
  0.317840;0.892460;,
  0.339710;0.809770;,
  0.317850;0.804810;,
  0.110180;0.739090;,
  0.550590;0.578560;,
  0.307950;0.692450;,
  0.643190;0.300490;,
  0.902560;0.647450;,
  0.902560;0.588910;,
  0.900120;0.596170;,
  0.898850;0.649070;,
  0.108090;0.930440;,
  0.078340;0.939820;,
  0.077190;0.968660;,
  0.108090;0.983380;,
  0.285170;0.986900;,
  0.285170;0.928390;,
  0.255410;0.941760;,
  0.254790;0.972250;,
  0.988700;0.112130;,
  0.985980;0.111950;,
  0.984250;0.145130;,
  0.988700;0.145970;,
  0.542820;0.949580;,
  0.572630;0.934270;,
  0.899400;0.585900;,
  0.896910;0.593150;,
  0.237230;0.964800;,
  0.237400;0.961570;,
  0.207580;0.944770;,
  0.207410;0.948000;,
  0.572680;0.931020;,
  0.542780;0.946400;,
  0.000000;0.000000;;
 }
}
