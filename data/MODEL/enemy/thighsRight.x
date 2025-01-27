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
 144;
 -9.48187;-0.08721;-12.22130;,
 -4.65342;-0.08721;-12.22130;,
 -5.15989;-10.93000;-13.47658;,
 -10.49484;-10.93000;-13.47658;,
 0.17501;-0.08721;-12.22130;,
 0.17501;-10.93000;-13.47658;,
 5.00346;-0.08721;-12.22130;,
 5.50996;-10.93000;-13.47658;,
 9.83194;-0.08721;-12.22130;,
 10.84489;-10.93000;-13.47658;,
 -5.69016;-23.03430;-14.79081;,
 -11.55537;-23.03430;-14.79081;,
 0.17501;-23.03430;-14.79081;,
 6.04025;-23.03430;-14.79081;,
 11.90546;-23.03430;-14.79081;,
 -5.13336;-34.95489;-13.41079;,
 -10.44175;-34.95489;-13.41079;,
 0.17501;-34.95489;-13.41079;,
 5.48341;-34.95489;-13.41079;,
 10.79180;-34.95489;-13.41079;,
 -4.65342;-45.85888;-12.22130;,
 -9.48187;-45.85888;-12.22130;,
 0.17501;-45.85888;-12.22130;,
 5.00346;-45.85888;-12.22130;,
 9.83194;-45.85888;-12.22130;,
 9.83194;-0.08721;-12.22130;,
 9.83194;-0.08721;-6.23792;,
 10.84489;-10.93000;-6.86552;,
 10.84489;-10.93000;-13.47658;,
 9.83194;-0.08721;-0.25451;,
 10.84489;-10.93000;-0.25451;,
 9.83194;-0.08721;5.72889;,
 10.84489;-10.93000;6.35650;,
 9.83194;-0.08721;11.71229;,
 10.84489;-10.93000;12.96753;,
 11.90546;-23.03430;-7.52269;,
 11.90546;-23.03430;-14.79081;,
 11.90546;-23.03430;-0.25451;,
 11.90546;-23.03430;7.01365;,
 11.90546;-23.03430;14.28182;,
 10.79180;-34.95489;-6.83262;,
 10.79180;-34.95489;-13.41079;,
 10.79180;-34.95489;-0.25451;,
 10.79180;-34.95489;6.32365;,
 10.79180;-34.95489;12.90177;,
 9.83194;-45.85888;-6.23792;,
 9.83194;-45.85888;-12.22130;,
 9.83194;-45.85888;-0.25451;,
 9.83194;-45.85888;5.72889;,
 9.83194;-45.85888;11.71229;,
 9.83194;-0.08721;11.71229;,
 5.00346;-0.08721;11.71229;,
 5.50996;-10.93000;12.96753;,
 10.84489;-10.93000;12.96753;,
 0.17501;-0.08721;11.71229;,
 0.17501;-10.93000;12.96753;,
 -4.65342;-0.08721;11.71229;,
 -5.15989;-10.93000;12.96753;,
 -9.48187;-0.08721;11.71229;,
 -10.49484;-10.93000;12.96753;,
 6.04025;-23.03430;14.28182;,
 11.90546;-23.03430;14.28182;,
 0.17501;-23.03430;14.28182;,
 -5.69016;-23.03430;14.28182;,
 -11.55537;-23.03430;14.28182;,
 5.48341;-34.95489;12.90177;,
 10.79180;-34.95489;12.90177;,
 0.17501;-34.95489;12.90177;,
 -5.13336;-34.95489;12.90177;,
 -10.44175;-34.95489;12.90177;,
 5.00346;-45.85888;11.71229;,
 9.83194;-45.85888;11.71229;,
 0.17501;-45.85888;11.71229;,
 -4.65342;-45.85888;11.71229;,
 -9.48187;-45.85888;11.71229;,
 -9.48187;-0.08721;11.71229;,
 -9.48187;-0.08721;5.72889;,
 -10.49484;-10.93000;6.35650;,
 -10.49484;-10.93000;12.96753;,
 -9.48187;-0.08721;-0.25451;,
 -10.49484;-10.93000;-0.25451;,
 -9.48187;-0.08721;-6.23792;,
 -10.49484;-10.93000;-6.86552;,
 -9.48187;-0.08721;-12.22130;,
 -10.49484;-10.93000;-13.47658;,
 -11.55537;-23.03430;7.01365;,
 -11.55537;-23.03430;14.28182;,
 -11.55537;-23.03430;-0.25451;,
 -11.55537;-23.03430;-7.52269;,
 -11.55537;-23.03430;-14.79081;,
 -10.44175;-34.95489;6.32365;,
 -10.44175;-34.95489;12.90177;,
 -10.44175;-34.95489;-0.25451;,
 -10.44175;-34.95489;-6.83262;,
 -10.44175;-34.95489;-13.41079;,
 -9.48187;-45.85888;5.72889;,
 -9.48187;-45.85888;11.71229;,
 -9.48187;-45.85888;-0.25451;,
 -9.48187;-45.85888;-6.23792;,
 -9.48187;-45.85888;-12.22130;,
 -4.65342;-0.08721;11.71229;,
 -4.65342;-0.08721;5.72889;,
 -9.48187;-0.08721;5.72889;,
 0.17501;-0.08721;5.72889;,
 5.00346;-0.08721;11.71229;,
 5.00346;-0.08721;5.72889;,
 9.83194;-0.08721;5.72889;,
 -4.65342;-0.08721;-0.25451;,
 -9.48187;-0.08721;-0.25451;,
 0.17501;-0.08721;-0.25451;,
 5.00346;-0.08721;-0.25451;,
 9.83194;-0.08721;-0.25451;,
 -4.65342;-0.08721;-6.23792;,
 -9.48187;-0.08721;-6.23792;,
 0.17501;-0.08721;-6.23792;,
 5.00346;-0.08721;-6.23792;,
 9.83194;-0.08721;-6.23792;,
 -4.65342;-0.08721;-12.22130;,
 -9.48187;-0.08721;-12.22130;,
 0.17501;-0.08721;-12.22130;,
 5.00346;-0.08721;-12.22130;,
 9.83194;-0.08721;-12.22130;,
 -9.48187;-45.85888;5.72889;,
 -4.65342;-45.85888;5.72889;,
 -4.65342;-45.85888;11.71229;,
 0.17501;-45.85888;5.72889;,
 5.00346;-45.85888;5.72889;,
 5.00346;-45.85888;11.71229;,
 9.83194;-45.85888;5.72889;,
 -9.48187;-45.85888;-0.25451;,
 -4.65342;-45.85888;-0.25451;,
 0.17501;-45.85888;-0.25451;,
 5.00346;-45.85888;-0.25451;,
 9.83194;-45.85888;-0.25451;,
 -9.48187;-45.85888;-6.23792;,
 -4.65342;-45.85888;-6.23792;,
 0.17501;-45.85888;-6.23792;,
 5.00346;-45.85888;-6.23792;,
 9.83194;-45.85888;-6.23792;,
 -9.48187;-45.85888;-12.22130;,
 -4.65342;-45.85888;-12.22130;,
 0.17501;-45.85888;-12.22130;,
 5.00346;-45.85888;-12.22130;,
 9.83194;-45.85888;-12.22130;;
 
 96;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;,
 4;11,10,15,16;,
 4;10,12,17,15;,
 4;12,13,18,17;,
 4;13,14,19,18;,
 4;16,15,20,21;,
 4;15,17,22,20;,
 4;17,18,23,22;,
 4;18,19,24,23;,
 4;25,26,27,28;,
 4;26,29,30,27;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;28,27,35,36;,
 4;27,30,37,35;,
 4;30,32,38,37;,
 4;32,34,39,38;,
 4;36,35,40,41;,
 4;35,37,42,40;,
 4;37,38,43,42;,
 4;38,39,44,43;,
 4;41,40,45,46;,
 4;40,42,47,45;,
 4;42,43,48,47;,
 4;43,44,49,48;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;53,52,60,61;,
 4;52,55,62,60;,
 4;55,57,63,62;,
 4;57,59,64,63;,
 4;61,60,65,66;,
 4;60,62,67,65;,
 4;62,63,68,67;,
 4;63,64,69,68;,
 4;66,65,70,71;,
 4;65,67,72,70;,
 4;67,68,73,72;,
 4;68,69,74,73;,
 4;75,76,77,78;,
 4;76,79,80,77;,
 4;79,81,82,80;,
 4;81,83,84,82;,
 4;78,77,85,86;,
 4;77,80,87,85;,
 4;80,82,88,87;,
 4;82,84,89,88;,
 4;86,85,90,91;,
 4;85,87,92,90;,
 4;87,88,93,92;,
 4;88,89,94,93;,
 4;91,90,95,96;,
 4;90,92,97,95;,
 4;92,93,98,97;,
 4;93,94,99,98;,
 4;75,100,101,102;,
 4;100,54,103,101;,
 4;54,104,105,103;,
 4;104,33,106,105;,
 4;102,101,107,108;,
 4;101,103,109,107;,
 4;103,105,110,109;,
 4;105,106,111,110;,
 4;108,107,112,113;,
 4;107,109,114,112;,
 4;109,110,115,114;,
 4;110,111,116,115;,
 4;113,112,117,118;,
 4;112,114,119,117;,
 4;114,115,120,119;,
 4;115,116,121,120;,
 4;122,123,124,96;,
 4;123,125,72,124;,
 4;125,126,127,72;,
 4;126,128,49,127;,
 4;129,130,123,122;,
 4;130,131,125,123;,
 4;131,132,126,125;,
 4;132,133,128,126;,
 4;134,135,130,129;,
 4;135,136,131,130;,
 4;136,137,132,131;,
 4;137,138,133,132;,
 4;139,140,135,134;,
 4;140,141,136,135;,
 4;141,142,137,136;,
 4;142,143,138,137;;
 
 MeshMaterialList {
  4;
  96;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.426400;0.426400;0.426400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.021600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.743200;0.768800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  49;
  0.000000;0.115003;-0.993365;,
  0.000000;0.115003;-0.993365;,
  0.000000;0.115003;-0.993365;,
  0.000000;0.111473;-0.993768;,
  0.000000;0.111473;-0.993768;,
  0.000000;-0.003551;-0.999994;,
  0.000000;-0.003551;-0.999994;,
  0.000000;-0.003551;-0.999994;,
  0.000000;-0.111723;-0.993739;,
  0.000000;-0.108445;-0.994102;,
  0.000000;-0.108445;-0.994103;,
  0.995665;0.093016;0.000000;,
  0.995928;0.090151;0.000000;,
  0.000000;-0.003551;-0.999994;,
  0.999996;-0.002878;-0.000000;,
  0.999996;-0.002878;-0.000000;,
  0.995910;-0.090354;-0.000000;,
  0.995910;-0.090354;-0.000000;,
  0.996148;-0.087689;-0.000000;,
  0.996148;-0.087689;-0.000000;,
  0.000000;0.114999;0.993366;,
  0.000000;0.111473;0.993767;,
  0.000000;0.111473;0.993767;,
  0.999996;-0.002878;-0.000000;,
  0.000000;-0.003550;0.999994;,
  0.000000;-0.003550;0.999994;,
  0.000000;-0.003550;0.999994;,
  0.000000;-0.111723;0.993739;,
  0.000000;-0.111723;0.993739;,
  0.000000;-0.108443;0.994103;,
  0.000000;-0.108443;0.994103;,
  0.000000;0.114999;0.993366;,
  -0.995664;0.093018;0.000000;,
  -0.995928;0.090150;0.000000;,
  -0.999996;-0.002878;0.000000;,
  -0.999996;-0.002878;0.000000;,
  0.000000;-0.111723;0.993739;,
  -0.995910;-0.090353;0.000000;,
  0.000000;-0.108443;0.994103;,
  -0.996148;-0.087692;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.995665;0.093016;0.000000;,
  0.999996;-0.002878;-0.000000;,
  -0.995664;0.093018;0.000000;,
  -0.995928;0.090150;0.000000;,
  -0.999996;-0.002878;0.000000;,
  -0.999996;-0.002878;0.000000;,
  -0.995910;-0.090353;0.000000;;
  96;
  4;0,1,4,3;,
  4;1,1,3,4;,
  4;1,2,4,3;,
  4;2,0,4,4;,
  4;3,4,6,5;,
  4;4,3,7,6;,
  4;3,4,5,7;,
  4;4,4,13,5;,
  4;5,6,8,8;,
  4;6,7,8,8;,
  4;7,5,8,8;,
  4;5,13,8,8;,
  4;8,8,10,9;,
  4;8,8,10,10;,
  4;8,8,10,10;,
  4;8,8,9,10;,
  4;42,11,12,12;,
  4;11,11,12,12;,
  4;11,11,12,12;,
  4;11,11,12,12;,
  4;12,12,14,43;,
  4;12,12,15,14;,
  4;12,12,15,15;,
  4;12,12,23,15;,
  4;43,14,16,17;,
  4;14,15,17,16;,
  4;15,15,17,17;,
  4;15,23,17,17;,
  4;17,16,18,18;,
  4;16,17,19,18;,
  4;17,17,19,19;,
  4;17,17,18,19;,
  4;31,20,21,21;,
  4;20,20,22,21;,
  4;20,20,21,22;,
  4;20,31,21,21;,
  4;21,21,24,24;,
  4;21,22,25,24;,
  4;22,21,26,25;,
  4;21,21,25,26;,
  4;24,24,27,27;,
  4;24,25,28,27;,
  4;25,26,27,28;,
  4;26,25,36,27;,
  4;27,27,29,29;,
  4;27,28,29,29;,
  4;28,27,30,29;,
  4;27,36,38,30;,
  4;44,32,33,45;,
  4;32,32,33,33;,
  4;32,32,33,33;,
  4;32,44,33,33;,
  4;45,33,34,46;,
  4;33,33,34,34;,
  4;33,33,35,34;,
  4;33,33,47,35;,
  4;46,34,37,48;,
  4;34,34,37,37;,
  4;34,35,37,37;,
  4;35,47,37,37;,
  4;48,37,39,39;,
  4;37,37,39,39;,
  4;37,37,39,39;,
  4;37,37,39,39;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;,
  4;41,41,41,41;;
 }
 MeshTextureCoords {
  144;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  1.000000;0.750000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;;
 }
}
