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
 64;
 40.06153;0.00000;0.00000;,
 41.52829;-0.00000;3.54098;,
 29.36493;29.36493;3.54098;,
 28.32781;28.32781;0.00000;,
 45.06925;-0.00000;5.00769;,
 31.86877;31.86877;5.00769;,
 48.61021;-0.00000;3.54098;,
 34.37264;34.37264;3.54098;,
 50.07695;0.00000;-0.00000;,
 35.40977;35.40977;0.00000;,
 48.61021;0.00000;-3.54098;,
 34.37264;34.37264;-3.54098;,
 45.06925;0.00000;-5.00769;,
 31.86877;31.86877;-5.00769;,
 41.52829;0.00000;-3.54098;,
 29.36493;29.36493;-3.54098;,
 -0.00000;41.52829;3.54098;,
 -0.00000;40.06153;0.00000;,
 -0.00000;45.06925;5.00769;,
 -0.00000;48.61021;3.54098;,
 -0.00000;50.07695;0.00000;,
 -0.00000;48.61021;-3.54097;,
 -0.00000;45.06925;-5.00769;,
 -0.00000;41.52829;-3.54097;,
 -29.36493;29.36493;3.54098;,
 -28.32781;28.32781;0.00000;,
 -31.86877;31.86877;5.00769;,
 -34.37264;34.37264;3.54098;,
 -35.40977;35.40977;0.00000;,
 -34.37264;34.37264;-3.54098;,
 -31.86877;31.86877;-5.00769;,
 -29.36493;29.36493;-3.54098;,
 -41.52829;-0.00000;3.54098;,
 -40.06153;-0.00000;-0.00000;,
 -45.06925;-0.00000;5.00769;,
 -48.61021;-0.00000;3.54098;,
 -50.07695;-0.00000;-0.00000;,
 -48.61021;-0.00000;-3.54098;,
 -45.06925;-0.00000;-5.00769;,
 -41.52829;-0.00000;-3.54098;,
 -29.36492;-29.36495;3.54097;,
 -28.32780;-28.32781;-0.00000;,
 -31.86877;-31.86877;5.00769;,
 -34.37264;-34.37265;3.54097;,
 -35.40976;-35.40978;-0.00000;,
 -34.37264;-34.37265;-3.54098;,
 -31.86877;-31.86877;-5.00769;,
 -29.36492;-29.36495;-3.54098;,
 0.00000;-41.52829;3.54097;,
 0.00000;-40.06153;-0.00000;,
 0.00000;-45.06925;5.00769;,
 0.00000;-48.61021;3.54097;,
 0.00000;-50.07695;-0.00000;,
 0.00000;-48.61021;-3.54098;,
 0.00000;-45.06925;-5.00769;,
 0.00000;-41.52829;-3.54098;,
 29.36492;-29.36494;3.54097;,
 28.32780;-28.32781;-0.00000;,
 31.86877;-31.86877;5.00769;,
 34.37264;-34.37265;3.54097;,
 35.40976;-35.40978;-0.00000;,
 34.37264;-34.37265;-3.54098;,
 31.86877;-31.86877;-5.00769;,
 29.36492;-29.36494;-3.54098;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,17,25,31;,
 4;25,24,32,33;,
 4;24,26,34,32;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,25,33,39;,
 4;33,32,40,41;,
 4;32,34,42,40;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,33,41,47;,
 4;41,40,48,49;,
 4;40,42,50,48;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,41,49,55;,
 4;49,48,56,57;,
 4;48,50,58,56;,
 4;50,51,59,58;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,49,57,63;,
 4;57,56,1,0;,
 4;56,58,4,1;,
 4;58,59,6,4;,
 4;59,60,8,6;,
 4;60,61,10,8;,
 4;61,62,12,10;,
 4;62,63,14,12;,
 4;63,57,0,14;;
 
 MeshMaterialList {
  1;
  64;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Visual Studio 2015\\Projects\\03_DirectX_cpp\\C++����01\\Cpp_001_RockDash\\dcpp_001_ACT\\data\\TEXTURE\\GOAL\\goaltape_all.png";
   }
  }
 }
 MeshNormals {
  64;
  -1.000000;0.000000;0.000000;,
  -0.698871;0.000000;0.715248;,
  -0.000001;-0.000000;1.000000;,
  0.698871;-0.000000;0.715248;,
  1.000000;-0.000000;-0.000000;,
  0.698871;0.000000;-0.715248;,
  -0.000001;0.000000;-1.000000;,
  -0.698871;0.000000;-0.715248;,
  -0.707107;-0.707107;-0.000000;,
  -0.494176;-0.494176;0.715248;,
  -0.000001;-0.000001;1.000000;,
  0.494176;0.494176;0.715248;,
  0.707107;0.707107;0.000000;,
  0.494176;0.494176;-0.715248;,
  -0.000001;-0.000001;-1.000000;,
  -0.494176;-0.494176;-0.715248;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.698871;0.715248;,
  0.000000;-0.000001;1.000000;,
  -0.000000;0.698871;0.715248;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;0.698871;-0.715248;,
  0.000000;-0.000001;-1.000000;,
  0.000000;-0.698871;-0.715248;,
  0.707107;-0.707107;-0.000000;,
  0.494176;-0.494176;0.715248;,
  0.000001;-0.000001;1.000000;,
  -0.494176;0.494176;0.715248;,
  -0.707107;0.707107;0.000000;,
  -0.494176;0.494176;-0.715248;,
  0.000001;-0.000001;-1.000000;,
  0.494176;-0.494176;-0.715248;,
  1.000000;0.000000;-0.000000;,
  0.698871;0.000000;0.715248;,
  0.000001;-0.000000;1.000000;,
  -0.698871;-0.000000;0.715248;,
  -1.000000;0.000000;0.000000;,
  -0.698871;0.000000;-0.715248;,
  0.000001;0.000000;-1.000000;,
  0.698871;0.000000;-0.715248;,
  0.707107;0.707107;0.000000;,
  0.494176;0.494176;0.715248;,
  0.000001;0.000001;1.000000;,
  -0.494176;-0.494176;0.715248;,
  -0.707107;-0.707107;0.000000;,
  -0.494176;-0.494176;-0.715248;,
  0.000001;0.000001;-1.000000;,
  0.494176;0.494176;-0.715248;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.698871;0.715248;,
  -0.000000;0.000001;1.000000;,
  0.000000;-0.698871;0.715248;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.698871;-0.715248;,
  0.000000;0.000001;-1.000000;,
  -0.000000;0.698871;-0.715248;,
  -0.707107;0.707107;0.000000;,
  -0.494176;0.494176;0.715248;,
  -0.000001;0.000001;1.000000;,
  0.494176;-0.494176;0.715248;,
  0.707107;-0.707107;-0.000000;,
  0.494176;-0.494176;-0.715248;,
  -0.000001;0.000001;-1.000000;,
  -0.494176;0.494176;-0.715248;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,48,56,63;,
  4;56,57,1,0;,
  4;57,58,2,1;,
  4;58,59,3,2;,
  4;59,60,4,3;,
  4;60,61,5,4;,
  4;61,62,6,5;,
  4;62,63,7,6;,
  4;63,56,0,7;;
 }
 MeshTextureCoords {
  64;
  0.869320;0.500000;,
  0.882842;0.629538;,
  0.770710;0.629538;,
  0.761149;0.500000;,
  0.915485;0.683194;,
  0.793792;0.683194;,
  0.948129;0.629538;,
  0.816875;0.629538;,
  0.961650;0.500000;,
  0.826436;0.500000;,
  0.948129;0.370462;,
  0.816875;0.370462;,
  0.915485;0.316806;,
  0.793792;0.316806;,
  0.882842;0.370462;,
  0.770710;0.370462;,
  0.500000;0.629538;,
  0.500000;0.500000;,
  0.500000;0.683194;,
  0.500000;0.629538;,
  0.500000;0.500000;,
  0.500000;0.370462;,
  0.500000;0.316806;,
  0.500000;0.370462;,
  0.229290;0.629538;,
  0.238851;0.500000;,
  0.206208;0.683194;,
  0.183125;0.629538;,
  0.173564;0.500000;,
  0.183125;0.370462;,
  0.206208;0.316806;,
  0.229290;0.370462;,
  0.117158;0.629538;,
  0.130680;0.500000;,
  0.084515;0.683194;,
  0.051871;0.629538;,
  0.038350;0.500000;,
  0.051871;0.370462;,
  0.084515;0.316806;,
  0.117158;0.370462;,
  0.229290;0.629538;,
  0.238851;0.500000;,
  0.206208;0.683194;,
  0.183125;0.629538;,
  0.173564;0.500000;,
  0.183125;0.370462;,
  0.206208;0.316806;,
  0.229290;0.370462;,
  0.500000;0.629538;,
  0.500000;0.500000;,
  0.500000;0.683194;,
  0.500000;0.629538;,
  0.500000;0.500000;,
  0.500000;0.370462;,
  0.500000;0.316806;,
  0.500000;0.370462;,
  0.770710;0.629538;,
  0.761149;0.500000;,
  0.793792;0.683194;,
  0.816875;0.629538;,
  0.826436;0.500000;,
  0.816875;0.370462;,
  0.793792;0.316806;,
  0.770710;0.370462;;
 }
}
