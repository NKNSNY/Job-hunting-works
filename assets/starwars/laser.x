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
 -0.14567;0.14567;7.91335;,
 -0.08641;0.17132;8.42650;,
 -0.09336;0.09336;9.37003;,
 -0.17132;0.08641;8.42650;,
 0.00000;0.18399;8.67976;,
 0.00000;0.10031;9.68785;,
 0.00000;0.00000;10.02553;,
 -0.10031;0.00000;9.68785;,
 -0.18399;0.00000;8.67976;,
 0.14567;0.14567;7.91335;,
 0.17132;0.08641;8.42650;,
 0.09336;0.09336;9.37003;,
 0.08641;0.17132;8.42650;,
 0.18399;0.00000;8.67976;,
 0.10031;0.00000;9.68785;,
 0.14567;-0.14567;7.91335;,
 0.08641;-0.17132;8.42650;,
 0.09336;-0.09336;9.37003;,
 0.17132;-0.08641;8.42650;,
 0.00000;-0.18399;8.67976;,
 0.00000;-0.10031;9.68785;,
 -0.14567;-0.14567;7.91335;,
 -0.17132;-0.08641;8.42650;,
 -0.09336;-0.09336;9.37003;,
 -0.08641;-0.17132;8.42650;,
 0.14567;0.14567;7.91335;,
 0.17132;0.17132;6.72815;,
 0.21850;0.09336;6.86719;,
 0.17132;0.08641;8.42650;,
 0.18399;0.18399;5.00000;,
 0.23439;0.10031;5.00000;,
 0.25128;0.00000;5.00000;,
 0.23439;0.00000;7.00624;,
 0.18399;0.00000;8.67976;,
 0.14567;0.14567;2.08665;,
 0.17132;0.08641;1.57350;,
 0.21850;0.09336;3.13281;,
 0.17132;0.17132;3.27185;,
 0.18399;0.00000;1.32024;,
 0.23439;0.00000;2.99376;,
 0.14567;-0.14567;2.08665;,
 0.17132;-0.17132;3.27185;,
 0.21850;-0.09336;3.13281;,
 0.17132;-0.08641;1.57350;,
 0.18399;-0.18399;5.00000;,
 0.23439;-0.10031;5.00000;,
 0.14567;-0.14567;7.91335;,
 0.17132;-0.08641;8.42650;,
 0.21850;-0.09336;6.86719;,
 0.17132;-0.17132;6.72815;,
 0.14567;0.14567;2.08665;,
 0.08641;0.17132;1.57350;,
 0.09336;0.09336;0.62997;,
 0.17132;0.08641;1.57350;,
 0.00000;0.18399;1.32024;,
 0.00000;0.10031;0.31215;,
 0.00000;0.00000;-0.02553;,
 0.10031;0.00000;0.31215;,
 0.18399;0.00000;1.32024;,
 -0.14567;0.14567;2.08665;,
 -0.17132;0.08641;1.57350;,
 -0.09336;0.09336;0.62997;,
 -0.08641;0.17132;1.57350;,
 -0.18399;0.00000;1.32024;,
 -0.10031;0.00000;0.31215;,
 -0.14567;-0.14567;2.08665;,
 -0.08641;-0.17132;1.57350;,
 -0.09336;-0.09336;0.62997;,
 -0.17132;-0.08641;1.57350;,
 0.00000;-0.18399;1.32024;,
 0.00000;-0.10031;0.31215;,
 0.14567;-0.14567;2.08665;,
 0.17132;-0.08641;1.57350;,
 0.09336;-0.09336;0.62997;,
 0.08641;-0.17132;1.57350;,
 -0.14567;0.14567;2.08665;,
 -0.17132;0.17132;3.27185;,
 -0.21850;0.09336;3.13281;,
 -0.17132;0.08641;1.57350;,
 -0.18399;0.18399;5.00000;,
 -0.23439;0.10031;5.00000;,
 -0.25128;0.00000;5.00000;,
 -0.23439;0.00000;2.99376;,
 -0.18399;0.00000;1.32024;,
 -0.14567;0.14567;7.91335;,
 -0.17132;0.08641;8.42650;,
 -0.21850;0.09336;6.86719;,
 -0.17132;0.17132;6.72815;,
 -0.18399;0.00000;8.67976;,
 -0.23439;0.00000;7.00624;,
 -0.14567;-0.14567;7.91335;,
 -0.17132;-0.17132;6.72815;,
 -0.21850;-0.09336;6.86719;,
 -0.17132;-0.08641;8.42650;,
 -0.18399;-0.18399;5.00000;,
 -0.23439;-0.10031;5.00000;,
 -0.14567;-0.14567;2.08665;,
 -0.17132;-0.08641;1.57350;,
 -0.21850;-0.09336;3.13281;,
 -0.17132;-0.17132;3.27185;,
 -0.08641;0.17132;1.57350;,
 -0.09336;0.21850;3.13281;,
 -0.17132;0.17132;3.27185;,
 0.00000;0.23439;2.99376;,
 0.00000;0.25128;5.00000;,
 -0.10031;0.23439;5.00000;,
 -0.18399;0.18399;5.00000;,
 0.17132;0.17132;3.27185;,
 0.09336;0.21850;3.13281;,
 0.08641;0.17132;1.57350;,
 0.18399;0.18399;5.00000;,
 0.10031;0.23439;5.00000;,
 0.14567;0.14567;7.91335;,
 0.08641;0.17132;8.42650;,
 0.09336;0.21850;6.86719;,
 0.17132;0.17132;6.72815;,
 0.00000;0.18399;8.67976;,
 0.00000;0.23439;7.00624;,
 -0.14567;0.14567;7.91335;,
 -0.17132;0.17132;6.72815;,
 -0.09336;0.21850;6.86719;,
 -0.08641;0.17132;8.42650;,
 -0.14567;-0.14567;7.91335;,
 -0.08641;-0.17132;8.42650;,
 -0.09336;-0.21850;6.86719;,
 -0.17132;-0.17132;6.72815;,
 0.00000;-0.18399;8.67976;,
 0.00000;-0.23439;7.00624;,
 0.00000;-0.25128;5.00000;,
 -0.10031;-0.23439;5.00000;,
 -0.18399;-0.18399;5.00000;,
 0.14567;-0.14567;7.91335;,
 0.17132;-0.17132;6.72815;,
 0.09336;-0.21850;6.86719;,
 0.08641;-0.17132;8.42650;,
 0.18399;-0.18399;5.00000;,
 0.10031;-0.23439;5.00000;,
 0.08641;-0.17132;1.57350;,
 0.09336;-0.21850;3.13281;,
 0.17132;-0.17132;3.27185;,
 0.00000;-0.23439;2.99376;,
 -0.17132;-0.17132;3.27185;,
 -0.09336;-0.21850;3.13281;,
 -0.08641;-0.17132;1.57350;;
 
 96;
 4;3,2,1,0;,
 4;1,2,5,4;,
 4;5,2,7,6;,
 4;7,2,3,8;,
 4;12,11,10,9;,
 4;10,11,14,13;,
 4;14,11,5,6;,
 4;5,11,12,4;,
 4;18,17,16,15;,
 4;16,17,20,19;,
 4;20,17,14,6;,
 4;14,17,18,13;,
 4;24,23,22,21;,
 4;22,23,7,8;,
 4;7,23,20,6;,
 4;20,23,24,19;,
 4;28,27,26,25;,
 4;26,27,30,29;,
 4;30,27,32,31;,
 4;32,27,28,33;,
 4;37,36,35,34;,
 4;35,36,39,38;,
 4;39,36,30,31;,
 4;30,36,37,29;,
 4;43,42,41,40;,
 4;41,42,45,44;,
 4;45,42,39,31;,
 4;39,42,43,38;,
 4;49,48,47,46;,
 4;47,48,32,33;,
 4;32,48,45,31;,
 4;45,48,49,44;,
 4;53,52,51,50;,
 4;51,52,55,54;,
 4;55,52,57,56;,
 4;57,52,53,58;,
 4;62,61,60,59;,
 4;60,61,64,63;,
 4;64,61,55,56;,
 4;55,61,62,54;,
 4;68,67,66,65;,
 4;66,67,70,69;,
 4;70,67,64,56;,
 4;64,67,68,63;,
 4;74,73,72,71;,
 4;72,73,57,58;,
 4;57,73,70,56;,
 4;70,73,74,69;,
 4;78,77,76,75;,
 4;76,77,80,79;,
 4;80,77,82,81;,
 4;82,77,78,83;,
 4;87,86,85,84;,
 4;85,86,89,88;,
 4;89,86,80,81;,
 4;80,86,87,79;,
 4;93,92,91,90;,
 4;91,92,95,94;,
 4;95,92,89,81;,
 4;89,92,93,88;,
 4;99,98,97,96;,
 4;97,98,82,83;,
 4;82,98,95,81;,
 4;95,98,99,94;,
 4;102,101,100,75;,
 4;100,101,103,54;,
 4;103,101,105,104;,
 4;105,101,102,106;,
 4;109,108,107,34;,
 4;107,108,111,110;,
 4;111,108,103,104;,
 4;103,108,109,54;,
 4;115,114,113,112;,
 4;113,114,117,116;,
 4;117,114,111,104;,
 4;111,114,115,110;,
 4;121,120,119,118;,
 4;119,120,105,106;,
 4;105,120,117,104;,
 4;117,120,121,116;,
 4;125,124,123,122;,
 4;123,124,127,126;,
 4;127,124,129,128;,
 4;129,124,125,130;,
 4;134,133,132,131;,
 4;132,133,136,135;,
 4;136,133,127,128;,
 4;127,133,134,126;,
 4;139,138,137,40;,
 4;137,138,140,69;,
 4;140,138,136,128;,
 4;136,138,139,135;,
 4;143,142,141,96;,
 4;141,142,129,130;,
 4;129,142,140,128;,
 4;140,142,143,69;;
 
 MeshMaterialList {
  2;
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
   0.800000;0.047059;0.244706;1.000000;;
   10.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.058824;0.305882;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  104;
  -0.703216;0.703216;0.104757;,
  0.703216;0.703216;0.104757;,
  0.703216;-0.703216;0.104757;,
  -0.703216;-0.703216;0.104757;,
  0.925316;0.378692;0.019549;,
  0.925316;0.378692;-0.019549;,
  0.925316;-0.378692;-0.019549;,
  0.925316;-0.378692;0.019549;,
  0.703216;0.703216;-0.104757;,
  -0.703216;0.703216;-0.104757;,
  -0.703216;-0.703216;-0.104757;,
  0.703216;-0.703216;-0.104757;,
  -0.925316;0.378692;-0.019549;,
  -0.925316;0.378692;0.019549;,
  -0.925316;-0.378692;0.019549;,
  -0.925316;-0.378692;-0.019549;,
  -0.378692;0.925316;-0.019549;,
  0.378692;0.925316;-0.019549;,
  0.378692;0.925316;0.019549;,
  -0.378692;0.925316;0.019549;,
  -0.378692;-0.925316;0.019549;,
  0.378692;-0.925316;0.019549;,
  0.378692;-0.925316;-0.019549;,
  -0.378692;-0.925316;-0.019549;,
  -0.471869;0.880403;0.047219;,
  -0.258742;0.957096;0.130459;,
  -0.986207;-0.000000;0.165518;,
  -0.880403;0.471869;0.047219;,
  0.880403;0.471869;0.047219;,
  0.957096;0.258742;0.130459;,
  0.471869;0.880403;0.047219;,
  0.471869;-0.880403;0.047219;,
  0.258742;-0.957096;0.130459;,
  0.880403;-0.471869;0.047219;,
  -0.880403;-0.471869;0.047219;,
  -0.471869;-0.880403;0.047219;,
  0.706972;0.706972;0.019522;,
  0.935204;0.354110;0.000000;,
  0.999807;0.000000;0.019665;,
  0.880403;0.471869;-0.047219;,
  0.999807;0.000000;-0.019665;,
  0.706972;0.706972;-0.019522;,
  0.706972;-0.706972;-0.019522;,
  0.935204;-0.354110;0.000000;,
  0.880403;-0.471869;-0.047219;,
  0.706972;-0.706972;0.019522;,
  0.471869;0.880403;-0.047219;,
  0.258742;0.957096;-0.130459;,
  0.986207;0.000000;-0.165518;,
  -0.880403;0.471869;-0.047219;,
  -0.957096;0.258742;-0.130459;,
  -0.471869;0.880403;-0.047219;,
  -0.471869;-0.880403;-0.047219;,
  -0.258742;-0.957096;-0.130459;,
  -0.880403;-0.471869;-0.047219;,
  0.471869;-0.880403;-0.047219;,
  -0.706972;0.706972;-0.019522;,
  -0.935204;0.354110;0.000000;,
  -0.999807;0.000000;-0.019665;,
  -0.999807;0.000000;0.019665;,
  -0.706972;0.706972;0.019522;,
  -0.706972;-0.706972;0.019522;,
  -0.935204;-0.354110;0.000000;,
  -0.706972;-0.706972;-0.019522;,
  0.000000;0.999807;-0.019665;,
  -0.354110;0.935204;0.000000;,
  0.354110;0.935204;0.000000;,
  0.000000;0.999807;0.019665;,
  0.000000;-0.999807;0.019665;,
  -0.354110;-0.935204;0.000000;,
  0.354110;-0.935204;0.000000;,
  0.000000;-0.999807;-0.019665;,
  -0.693224;0.693224;0.197184;,
  1.000000;0.000000;0.000000;,
  0.693224;0.693224;-0.197184;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.998462;0.055437;,
  0.998462;0.000000;0.055437;,
  0.000000;-0.998462;0.055437;,
  -0.998462;0.000000;0.055437;,
  0.707107;0.707107;0.000000;,
  0.998462;0.000000;-0.055437;,
  0.707107;-0.707107;0.000000;,
  0.000000;0.998462;-0.055437;,
  -0.998462;0.000000;-0.055437;,
  0.000000;-0.998462;-0.055437;,
  -0.707107;0.707107;0.000000;,
  -0.707107;-0.707107;0.000000;,
  -0.706649;0.706649;0.035995;,
  -0.706649;-0.706649;0.035995;,
  0.706649;0.706649;0.035995;,
  0.706649;-0.706649;0.035995;,
  0.706649;0.706649;-0.035995;,
  0.706649;-0.706649;-0.035995;,
  -0.706649;0.706649;-0.035995;,
  -0.706649;-0.706649;-0.035995;,
  0.693224;0.693224;0.197184;,
  0.693224;-0.693224;0.197184;,
  -0.693224;-0.693224;0.197184;,
  -0.693224;0.693224;-0.197184;,
  -0.693224;-0.693224;-0.197184;,
  0.693224;-0.693224;-0.197184;;
  96;
  4;27,0,24,90;,
  4;24,0,25,78;,
  4;25,0,26,72;,
  4;26,0,27,81;,
  4;30,1,28,92;,
  4;28,1,29,79;,
  4;29,1,98,98;,
  4;25,1,30,78;,
  4;33,2,31,93;,
  4;31,2,32,80;,
  4;32,2,99,99;,
  4;29,2,33,79;,
  4;35,3,34,91;,
  4;34,3,26,81;,
  4;26,3,100,100;,
  4;32,3,35,80;,
  4;28,4,36,92;,
  4;36,4,37,82;,
  4;37,4,38,73;,
  4;38,4,28,79;,
  4;41,5,39,94;,
  4;39,5,40,83;,
  4;40,5,37,73;,
  4;37,5,41,82;,
  4;44,6,42,95;,
  4;42,6,43,84;,
  4;43,6,40,73;,
  4;40,6,44,83;,
  4;45,7,33,93;,
  4;33,7,38,79;,
  4;38,7,43,73;,
  4;43,7,45,84;,
  4;39,8,46,94;,
  4;46,8,47,85;,
  4;47,8,48,74;,
  4;48,8,39,83;,
  4;51,9,49,96;,
  4;49,9,50,86;,
  4;50,9,101,101;,
  4;47,9,51,85;,
  4;54,10,52,97;,
  4;52,10,53,87;,
  4;53,10,102,102;,
  4;50,10,54,86;,
  4;55,11,44,95;,
  4;44,11,48,83;,
  4;48,11,103,103;,
  4;53,11,55,87;,
  4;49,12,56,96;,
  4;56,12,57,88;,
  4;57,12,58,75;,
  4;58,12,49,86;,
  4;60,13,27,90;,
  4;27,13,59,81;,
  4;59,13,57,75;,
  4;57,13,60,88;,
  4;34,14,61,91;,
  4;61,14,62,89;,
  4;62,14,59,75;,
  4;59,14,34,81;,
  4;63,15,54,97;,
  4;54,15,58,86;,
  4;58,15,62,75;,
  4;62,15,63,89;,
  4;56,16,51,96;,
  4;51,16,64,85;,
  4;64,16,65,76;,
  4;65,16,56,88;,
  4;46,17,41,94;,
  4;41,17,66,82;,
  4;66,17,64,76;,
  4;64,17,46,85;,
  4;36,18,30,92;,
  4;30,18,67,78;,
  4;67,18,66,76;,
  4;66,18,36,82;,
  4;24,19,60,90;,
  4;60,19,65,88;,
  4;65,19,67,76;,
  4;67,19,24,78;,
  4;61,20,35,91;,
  4;35,20,68,80;,
  4;68,20,69,77;,
  4;69,20,61,89;,
  4;31,21,45,93;,
  4;45,21,70,84;,
  4;70,21,68,77;,
  4;68,21,31,80;,
  4;42,22,55,95;,
  4;55,22,71,87;,
  4;71,22,70,77;,
  4;70,22,42,84;,
  4;52,23,63,97;,
  4;63,23,69,89;,
  4;69,23,71,77;,
  4;71,23,52,87;;
 }
 MeshTextureCoords {
  144;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;;
 }
 MeshVertexColors {
  144;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;,
  120;1.000000;1.000000;1.000000;1.000000;,
  121;1.000000;1.000000;1.000000;1.000000;,
  122;1.000000;1.000000;1.000000;1.000000;,
  123;1.000000;1.000000;1.000000;1.000000;,
  124;1.000000;1.000000;1.000000;1.000000;,
  125;1.000000;1.000000;1.000000;1.000000;,
  126;1.000000;1.000000;1.000000;1.000000;,
  127;1.000000;1.000000;1.000000;1.000000;,
  128;1.000000;1.000000;1.000000;1.000000;,
  129;1.000000;1.000000;1.000000;1.000000;,
  130;1.000000;1.000000;1.000000;1.000000;,
  131;1.000000;1.000000;1.000000;1.000000;,
  132;1.000000;1.000000;1.000000;1.000000;,
  133;1.000000;1.000000;1.000000;1.000000;,
  134;1.000000;1.000000;1.000000;1.000000;,
  135;1.000000;1.000000;1.000000;1.000000;,
  136;1.000000;1.000000;1.000000;1.000000;,
  137;1.000000;1.000000;1.000000;1.000000;,
  138;1.000000;1.000000;1.000000;1.000000;,
  139;1.000000;1.000000;1.000000;1.000000;,
  140;1.000000;1.000000;1.000000;1.000000;,
  141;1.000000;1.000000;1.000000;1.000000;,
  142;1.000000;1.000000;1.000000;1.000000;,
  143;1.000000;1.000000;1.000000;1.000000;;
 }
}