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
 129;
 -2.54727;-3.19150;10.06464;,
 3.41906;-3.19150;10.06464;,
 3.41906;0.01455;7.59770;,
 -2.54727;0.01455;7.59770;,
 -3.32532;-9.41283;9.28659;,
 -3.32532;-3.45615;9.28659;,
 -3.32532;-9.41283;4.57938;,
 -3.32532;-0.76348;7.21467;,
 -3.32532;-0.76348;-2.83305;,
 -3.32532;-7.37716;2.36230;,
 -3.32532;-7.37716;-1.55414;,
 -3.32532;-9.41283;-3.77120;,
 -3.32532;-4.41808;-9.76335;,
 -3.32532;-9.41283;-9.76335;,
 -2.54727;0.01455;7.59770;,
 3.41906;0.01455;7.59770;,
 3.41906;0.01455;-3.02564;,
 -2.54727;0.01455;-3.02564;,
 3.41906;-3.94878;-10.54140;,
 -2.54727;-3.94878;-10.54140;,
 3.59242;-7.37716;2.36230;,
 3.59242;-9.41283;4.57938;,
 3.59242;-9.00238;4.57938;,
 3.59242;-6.96667;2.36230;,
 4.19713;-9.41283;-9.76335;,
 4.19713;-4.41808;-9.76335;,
 4.19713;-9.41283;-3.77120;,
 4.19713;-0.76348;-2.83305;,
 4.19713;-7.37716;-1.55414;,
 4.19713;-0.76348;7.21467;,
 4.19713;-7.37716;2.36230;,
 4.19713;-9.41283;4.57938;,
 4.19713;-9.41283;9.28659;,
 4.19713;-3.45615;9.28659;,
 -2.72060;-9.41283;-3.77120;,
 -2.72060;-9.41283;-9.93669;,
 -2.72060;-9.00238;-9.93669;,
 -2.72060;-9.00238;-3.77120;,
 3.59242;-9.41283;9.45992;,
 -2.72060;-9.41283;9.45992;,
 -2.72060;-9.00238;9.45992;,
 3.59242;-9.00238;9.45992;,
 -2.72060;-9.41283;4.57938;,
 -2.72060;-7.37716;2.36230;,
 -2.72060;-6.96667;2.36230;,
 -2.72060;-9.00238;4.57938;,
 3.59242;-9.41283;9.45992;,
 3.59242;-9.00238;9.45992;,
 3.41906;-9.41283;10.06464;,
 -2.54727;-9.41283;10.06464;,
 4.19713;-9.41283;-9.76335;,
 4.19713;-9.41283;-3.77120;,
 3.64696;-9.41283;-9.99125;,
 3.59242;-9.41283;-3.77120;,
 3.59242;-9.41283;-9.93669;,
 3.41906;-9.41283;-10.54140;,
 -2.72060;-9.41283;-9.93669;,
 -2.54727;-9.41283;-10.54140;,
 -2.77515;-9.41283;-9.99125;,
 -2.72060;-9.41283;4.57938;,
 -2.72060;-9.41283;9.45992;,
 -3.32532;-9.41283;4.57938;,
 -2.77515;-9.41283;9.51448;,
 -3.32532;-9.41283;9.28659;,
 4.19713;-9.41283;4.57938;,
 4.19713;-9.41283;9.28659;,
 3.59242;-9.41283;4.57938;,
 3.64696;-9.41283;9.51448;,
 3.59242;-9.41283;9.45992;,
 3.41906;-9.41283;10.06464;,
 -2.54727;-9.41283;10.06464;,
 -2.72060;-9.41283;-3.77120;,
 -3.32532;-9.41283;-3.77120;,
 -3.32532;-9.41283;-9.76335;,
 3.59242;-7.37716;2.36230;,
 4.19713;-7.37716;2.36230;,
 3.59242;-7.37716;-1.55414;,
 4.19713;-7.37716;-1.55414;,
 -2.72060;-7.37716;-1.55414;,
 -3.32532;-7.37716;-1.55414;,
 -2.72060;-7.37716;2.36230;,
 -3.32532;-7.37716;2.36230;,
 3.59242;-9.00238;-3.77120;,
 -2.72060;-9.00238;-3.77120;,
 -2.72060;-9.00238;-9.93669;,
 3.59242;-9.00238;-9.93669;,
 3.59242;-9.00238;9.45992;,
 -2.72060;-9.00238;9.45992;,
 -2.72060;-9.00238;4.57938;,
 3.59242;-9.00238;4.57938;,
 -2.72060;-6.96667;2.36230;,
 3.59242;-6.96667;2.36230;,
 -2.72060;-6.96667;-1.55414;,
 3.59242;-6.96667;-1.55414;,
 -2.72060;-9.41283;9.45992;,
 -2.72060;-9.00238;9.45992;,
 -2.72060;-7.37716;-1.55414;,
 -2.72060;-6.96667;-1.55414;,
 3.59242;-7.37716;-1.55414;,
 3.59242;-6.96667;-1.55414;,
 -2.72060;-9.41283;-9.93669;,
 3.59242;-9.41283;-9.93669;,
 3.59242;-9.00238;-9.93669;,
 -2.72060;-9.00238;-9.93669;,
 3.59242;-9.41283;-9.93669;,
 3.59242;-9.41283;-3.77120;,
 3.59242;-9.00238;-3.77120;,
 3.59242;-9.00238;-9.93669;,
 3.41906;-9.41283;-10.54140;,
 3.41906;-3.94878;-10.54140;,
 4.19713;-4.41808;-9.76335;,
 4.19713;-9.41283;-9.76335;,
 3.41906;0.01455;7.59770;,
 3.41906;-3.19150;10.06464;,
 3.41906;-9.41283;10.06464;,
 -3.32532;-3.45615;9.28659;,
 -3.32532;-9.41283;9.28659;,
 -2.54727;0.01455;-3.02564;,
 -2.54727;-3.94878;-10.54140;,
 -2.54727;-3.94878;-10.54140;,
 -2.54727;-9.41283;-10.54140;,
 -3.32532;-9.41283;-9.76335;,
 -3.32532;-4.41808;-9.76335;,
 3.41906;-3.94878;-10.54140;,
 3.41906;0.01455;-3.02564;,
 -2.54727;-3.19150;10.06464;,
 -2.54727;0.01455;7.59770;,
 -3.32532;-0.76348;-2.83305;,
 -3.32532;-0.76348;7.21467;;
 
 78;
 4;0,1,2,3;,
 3;4,5,6;,
 3;5,7,6;,
 3;7,8,6;,
 3;6,8,9;,
 3;9,8,10;,
 3;10,8,11;,
 3;8,12,11;,
 3;12,13,11;,
 4;14,15,16,17;,
 4;17,16,18,19;,
 4;20,21,22,23;,
 3;24,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;27,29,28;,
 3;28,29,30;,
 3;30,29,31;,
 3;31,29,32;,
 3;29,33,32;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;21,46,47,22;,
 4;48,1,0,49;,
 3;50,51,52;,
 3;51,53,52;,
 3;53,54,52;,
 3;52,54,55;,
 3;54,56,55;,
 3;55,56,57;,
 3;56,58,57;,
 3;59,60,61;,
 3;60,62,61;,
 3;62,63,61;,
 3;64,65,66;,
 3;65,67,66;,
 3;67,68,66;,
 3;67,69,68;,
 3;68,69,60;,
 3;69,70,60;,
 3;70,62,60;,
 3;56,71,58;,
 3;71,72,58;,
 3;72,73,58;,
 4;66,74,75,64;,
 4;74,76,77,75;,
 4;76,53,51,77;,
 4;71,78,79,72;,
 4;78,80,81,79;,
 4;80,59,61,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;93,92,83,82;,
 4;94,42,45,95;,
 4;96,34,37,97;,
 4;98,20,23,99;,
 4;100,101,102,103;,
 4;43,96,97,44;,
 4;104,105,106,107;,
 4;105,98,99,106;,
 3;55,50,52;,
 3;70,63,62;,
 3;65,69,67;,
 3;73,57,58;,
 4;108,109,110,111;,
 4;112,113,33,29;,
 4;113,114,32,33;,
 4;115,116,49,0;,
 4;117,118,12,8;,
 4;119,120,121,122;,
 4;123,124,27,25;,
 4;124,112,29,27;,
 4;125,126,7,5;,
 4;14,17,127,128;,
 4;120,119,109,108;;
 
 MeshMaterialList {
  2;
  78;
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
  37;
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.931825;0.362907;,
  0.000000;-0.970791;0.239925;,
  0.000000;-0.931824;0.362912;,
  0.942471;0.172661;-0.286246;,
  0.382674;0.817217;-0.430948;,
  0.400830;0.295071;0.867334;,
  0.874515;0.156207;0.459154;,
  -0.435458;0.464960;-0.770836;,
  -0.942473;0.172658;-0.286242;,
  -0.930977;0.117584;0.345625;,
  -0.400836;0.295071;0.867331;,
  0.392464;0.892825;-0.220987;,
  0.954886;0.288272;-0.071351;,
  0.980991;0.174100;0.085712;,
  0.419158;0.814552;0.401013;,
  -0.419164;0.814550;0.401011;,
  -0.937364;0.312529;0.153862;,
  -0.977854;0.203155;-0.050284;,
  -0.392470;0.892823;-0.220986;,
  0.923877;0.000000;-0.382689;,
  -0.382683;0.000000;0.923880;,
  -0.923880;0.000000;0.382683;,
  0.967537;0.000000;0.252728;,
  0.382678;0.000000;0.923882;,
  -0.923880;0.000000;-0.382683;,
  0.000000;-0.931826;-0.362905;,
  0.000000;-0.984011;-0.178107;,
  0.000000;-0.931826;-0.362905;,
  0.000000;-0.984011;-0.178107;,
  0.000000;-0.931824;-0.362909;,
  0.000000;0.000000;1.000000;,
  0.382678;0.000000;-0.923882;,
  -0.382683;0.000000;-0.923880;;
  78;
  4;14,9,18,19;,
  3;25,13,3;,
  3;13,20,3;,
  3;20,21,3;,
  3;3,21,3;,
  3;3,21,3;,
  3;3,21,3;,
  3;21,12,3;,
  3;12,28,3;,
  4;19,18,15,22;,
  4;22,15,8,11;,
  4;3,3,3,3;,
  3;23,7,2;,
  3;7,16,2;,
  3;2,16,2;,
  3;16,17,2;,
  3;2,17,2;,
  3;2,17,2;,
  3;2,17,26;,
  3;17,10,26;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;27,9,14,24;,
  3;0,5,0;,
  3;5,5,0;,
  3;5,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;29,0,30;,
  3;0,0,30;,
  3;0,0,30;,
  3;31,0,32;,
  3;0,0,32;,
  3;0,0,32;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,5,0;,
  3;5,5,0;,
  3;5,0,0;,
  4;32,31,31,31;,
  4;31,4,4,31;,
  4;4,5,5,4;,
  4;5,4,4,5;,
  4;4,29,29,4;,
  4;29,29,30,29;,
  4;6,6,0,0;,
  4;0,0,33,33;,
  4;33,33,33,33;,
  4;33,33,6,6;,
  4;6,6,6,6;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;34,34,34,34;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;35,35,7,23;,
  4;18,9,10,17;,
  4;9,27,26,10;,
  4;13,25,24,14;,
  4;22,11,12,21;,
  4;11,36,28,12;,
  4;8,15,16,7;,
  4;15,18,17,16;,
  4;14,19,20,13;,
  4;19,22,21,20;,
  4;36,11,35,35;;
 }
 MeshTextureCoords {
  129;
  0.060720;0.780610;,
  0.004550;0.780620;,
  0.004680;0.750840;,
  0.060850;0.750840;,
  0.421800;0.271120;,
  0.477870;0.271120;,
  0.421800;0.315420;,
  0.503220;0.290620;,
  0.503220;0.385200;,
  0.440960;0.336290;,
  0.440960;0.373160;,
  0.421800;0.394020;,
  0.468820;0.450430;,
  0.421800;0.450430;,
  0.643200;0.073250;,
  0.699360;0.073300;,
  0.699360;0.172680;,
  0.643200;0.172620;,
  0.699030;0.247170;,
  0.642870;0.247120;,
  0.303080;0.349190;,
  0.283920;0.328320;,
  0.287780;0.328320;,
  0.306950;0.349190;,
  0.004560;0.298280;,
  0.051580;0.298280;,
  0.004560;0.354670;,
  0.085980;0.363500;,
  0.023720;0.375530;,
  0.085980;0.458050;,
  0.023720;0.412390;,
  0.004560;0.433250;,
  0.004560;0.477550;,
  0.060640;0.477550;,
  0.150020;0.541340;,
  0.150020;0.599360;,
  0.146160;0.599360;,
  0.146160;0.541340;,
  0.713470;0.840890;,
  0.713470;0.781470;,
  0.717320;0.781470;,
  0.717320;0.840880;,
  0.150020;0.462760;,
  0.130860;0.483620;,
  0.126990;0.483620;,
  0.146160;0.462760;,
  0.283920;0.282380;,
  0.287780;0.282380;,
  0.004550;0.839180;,
  0.060720;0.839170;,
  0.388880;0.334170;,
  0.388880;0.390570;,
  0.383700;0.332020;,
  0.383190;0.390570;,
  0.383190;0.332530;,
  0.381550;0.326840;,
  0.323760;0.332540;,
  0.325390;0.326840;,
  0.323250;0.332020;,
  0.323760;0.469190;,
  0.323760;0.515130;,
  0.318070;0.469190;,
  0.323250;0.515650;,
  0.318070;0.513500;,
  0.388880;0.469180;,
  0.388880;0.513500;,
  0.383190;0.469180;,
  0.383700;0.515640;,
  0.383190;0.515130;,
  0.381550;0.520820;,
  0.325390;0.520820;,
  0.323760;0.390580;,
  0.318070;0.390580;,
  0.318070;0.334170;,
  0.382960;0.448280;,
  0.388650;0.448280;,
  0.382960;0.411410;,
  0.388650;0.411410;,
  0.323530;0.411410;,
  0.317840;0.411410;,
  0.323530;0.448280;,
  0.317840;0.448280;,
  0.714120;0.525010;,
  0.654700;0.525010;,
  0.654700;0.466970;,
  0.714120;0.466970;,
  0.714120;0.649560;,
  0.654700;0.649560;,
  0.654700;0.603620;,
  0.714120;0.603620;,
  0.654470;0.582710;,
  0.713900;0.582710;,
  0.654470;0.545840;,
  0.713900;0.545840;,
  0.150020;0.416830;,
  0.146160;0.416830;,
  0.130860;0.520480;,
  0.126990;0.520480;,
  0.303080;0.386050;,
  0.306950;0.386050;,
  0.825040;0.452100;,
  0.825040;0.392680;,
  0.828900;0.392680;,
  0.828900;0.452100;,
  0.283920;0.464960;,
  0.283920;0.406920;,
  0.287780;0.406920;,
  0.287780;0.464960;,
  0.851940;0.247170;,
  0.903300;0.247110;,
  0.898480;0.254300;,
  0.851540;0.254350;,
  0.093300;0.461840;,
  0.063120;0.485060;,
  0.004550;0.485060;,
  0.068080;0.783230;,
  0.068080;0.839300;,
  0.510520;0.387120;,
  0.473210;0.457860;,
  0.903300;0.190960;,
  0.851940;0.191010;,
  0.851540;0.183550;,
  0.898480;0.183500;,
  0.055980;0.291140;,
  0.093300;0.361870;,
  0.480340;0.263900;,
  0.510520;0.287120;,
  0.635810;0.171640;,
  0.635810;0.077650;;
 }
}
