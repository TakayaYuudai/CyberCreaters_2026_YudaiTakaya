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
 36;
 -8.28815;-0.42189;-9.13729;,
 8.15566;-0.42189;-9.13729;,
 11.41790;-4.08049;-16.28144;,
 -11.55039;-4.08049;-16.28144;,
 14.37939;-8.46092;-20.55752;,
 -14.51188;-8.46092;-20.55752;,
 14.37939;-12.66294;-20.55752;,
 -14.51188;-12.66294;-20.55752;,
 8.15566;-0.42189;-9.13729;,
 8.15566;-0.42189;9.73825;,
 11.41790;-4.08049;16.88236;,
 11.41790;-4.08049;-16.28144;,
 14.37939;-8.46092;21.15848;,
 14.37939;-8.46092;-20.55752;,
 14.37939;-12.66294;21.15848;,
 14.37939;-12.66294;-20.55752;,
 8.15566;-0.42189;9.73825;,
 -8.28815;-0.42189;9.73825;,
 -11.55039;-4.08049;16.88236;,
 11.41790;-4.08049;16.88236;,
 -14.51188;-8.46092;21.15848;,
 14.37939;-8.46092;21.15848;,
 -14.51188;-12.66294;21.15848;,
 14.37939;-12.66294;21.15848;,
 -8.28815;-0.42189;9.73825;,
 -8.28815;-0.42189;-9.13729;,
 -11.55039;-4.08049;-16.28144;,
 -11.55039;-4.08049;16.88236;,
 -14.51188;-8.46092;-20.55752;,
 -14.51188;-8.46092;21.15848;,
 -14.51188;-12.66294;-20.55752;,
 -14.51188;-12.66294;21.15848;,
 8.15566;-0.42189;-9.13729;,
 -8.28815;-0.42189;-9.13729;,
 -14.51188;-12.66294;-20.55752;,
 14.37939;-12.66294;-20.55752;;
 
 14;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;24,9,32,33;,
 4;34,35,14,31;;
 
 MeshMaterialList {
  4;
  14;
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  1;;
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
  17;
  -0.276325;0.946133;-0.168753;,
  -0.458992;0.820222;-0.341412;,
  0.000000;0.377109;-0.926169;,
  0.000000;0.000000;-1.000000;,
  0.276325;0.946133;-0.168753;,
  0.458991;0.820222;-0.341412;,
  0.276325;0.946133;0.168753;,
  0.458991;0.820223;0.341411;,
  0.956147;0.292886;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.276325;0.946133;0.168753;,
  -0.458991;0.820223;0.341411;,
  0.000000;0.377111;0.926168;,
  0.000000;0.000000;1.000000;,
  -0.956147;0.292886;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  14;
  4;0,4,5,1;,
  4;1,5,2,2;,
  4;2,2,3,3;,
  4;4,6,7,5;,
  4;5,7,8,8;,
  4;8,8,9,9;,
  4;6,10,11,7;,
  4;7,11,12,12;,
  4;12,12,13,13;,
  4;10,0,1,11;,
  4;11,1,14,14;,
  4;14,14,15,15;,
  4;10,6,4,0;,
  4;16,16,16,16;;
 }
 MeshTextureCoords {
  36;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
