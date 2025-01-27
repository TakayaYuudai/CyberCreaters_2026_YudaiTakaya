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
 31;
 4.18363;-13.87581;4.44563;,
 4.18363;-0.07661;8.46291;,
 -4.25700;-0.07661;8.46291;,
 -4.25700;-13.87581;4.44563;,
 -5.07551;-13.05730;3.87810;,
 -5.07551;-0.22678;7.61522;,
 -5.07551;-0.15453;-6.86747;,
 -5.07551;-13.05730;-2.75609;,
 -4.25700;-13.87581;-3.30281;,
 -4.25700;-0.17706;-7.69138;,
 4.18363;-0.17706;-7.69138;,
 4.18363;-13.87581;-3.30281;,
 4.18363;-13.87581;4.44563;,
 -4.25700;-13.87581;4.44563;,
 -4.25700;-13.87581;-3.30281;,
 4.18363;-13.87581;-3.30281;,
 4.18363;-13.87581;4.44563;,
 4.18363;-13.87581;-3.30281;,
 5.00213;-13.05730;-2.75609;,
 5.00213;-13.05730;3.87810;,
 4.18363;-0.07661;8.46291;,
 5.00211;-0.22678;7.61522;,
 -5.07551;-0.22678;7.61522;,
 -5.07551;-13.05730;3.87810;,
 -5.07551;-13.05730;3.87810;,
 -5.07551;-13.05730;-2.75609;,
 -5.07551;-13.05730;-2.75609;,
 -5.07551;-0.15453;-6.86747;,
 5.00213;-0.15453;-6.86747;,
 5.00213;-13.05730;-2.75609;,
 5.00213;-0.15453;-6.86747;;
 
 11;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,16,19,21;,
 4;22,23,3,2;,
 4;14,13,24,25;,
 4;9,8,26,27;,
 4;11,10,28,29;,
 4;18,30,21,19;;
 
 MeshMaterialList {
  2;
  11;
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
  14;
  0.900856;-0.348431;-0.258947;,
  0.371843;-0.282925;-0.884130;,
  0.901771;-0.342979;0.263009;,
  0.369381;-0.259776;0.892230;,
  -0.900855;-0.348434;-0.258950;,
  -0.371840;-0.282926;-0.884131;,
  -0.901769;-0.342983;0.263012;,
  -0.369375;-0.259777;0.892232;,
  0.919337;-0.119753;-0.374805;,
  0.918290;-0.110688;0.380120;,
  -0.918288;-0.110691;0.380125;,
  -0.919336;-0.119754;-0.374808;,
  0.382686;-0.923878;-0.000000;,
  -0.382684;-0.923879;0.000000;;
  11;
  4;3,3,7,7;,
  4;6,10,11,4;,
  4;5,5,1,1;,
  4;12,13,13,12;,
  4;12,12,0,2;,
  4;3,3,2,9;,
  4;10,6,7,7;,
  4;13,13,6,4;,
  4;5,5,4,11;,
  4;1,1,8,0;,
  4;0,8,9,2;;
 }
 MeshTextureCoords {
  31;
  0.509000;0.004670;,
  0.509000;0.135210;,
  0.429540;0.135090;,
  0.429540;0.004550;,
  0.174220;0.258560;,
  0.168500;0.132890;,
  0.301150;0.164350;,
  0.234910;0.273270;,
  0.325690;0.317730;,
  0.325700;0.186700;,
  0.405140;0.186300;,
  0.405130;0.317340;,
  0.541920;0.827980;,
  0.541920;0.748530;,
  0.614860;0.748530;,
  0.614860;0.827980;,
  0.010680;0.021740;,
  0.081550;0.004550;,
  0.078560;0.013220;,
  0.017880;0.027930;,
  0.004550;0.156890;,
  0.012160;0.153600;,
  0.421800;0.133520;,
  0.421800;0.012160;,
  0.547270;0.740730;,
  0.609730;0.740730;,
  0.317840;0.310360;,
  0.317840;0.186950;,
  0.412690;0.186470;,
  0.412690;0.309890;,
  0.144780;0.122140;;
 }
}
