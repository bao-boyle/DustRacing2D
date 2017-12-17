// This file is part of Dust Racing 2D.
// Copyright (C) 2013 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#ifndef SHADERS30_H
#define SHADERS30_H

static const char * carVsh =
"#version 130\n"
""
"in        vec3  inVertex;\n"
"in        vec3  inNormal;\n"
"in        vec2  inTexCoord;\n"
"in        vec4  inColor;\n"
"uniform   vec4  scale = vec4(1, 1, 1, 1);\n"
"uniform   vec4  color;\n"
"uniform   mat4  vp;\n"
"uniform   mat4  v;\n"
"uniform   mat4  model;\n"
"uniform   vec4  dd = vec4(1, 1, 1, 1);\n"
"uniform   vec4  dc = vec4(1, 1, 1, 1);\n"
"uniform   vec4  sd = vec4(1, 1, 1, 1);\n"
"uniform   vec4  sc = vec4(1, 1, 1, 1);\n"
"uniform   vec4  ac = vec4(1, 1, 1, 1);\n"
"uniform   float sCoeff = 1;\n"
"out       vec4  ddRotated;\n"
"out       vec2  texCoord0;\n"
"out       vec2  texCoord1;\n"
"out       vec4  vColor;\n"
"out       mat4  normalRot;\n"
""
"void main()\n"
"{\n"
"    gl_Position = vp * model * (vec4(inVertex, 1) * scale);\n"
""
"    // We need this for normal mapping in the fragment shader.\n"
"    normalRot = mat4(mat3(model));\n"
"    ddRotated = vec4(dd.xyz, 0) * normalRot;\n"
""
"    texCoord0 = inTexCoord;\n"
"    texCoord1 = (normalRot * vec4(inTexCoord, 0.0, 0.0)).xy;\n"
""
"    vec3 vNormalEye = (v * model * vec4(inNormal, 1)).xyz;\n"
"    vec3 vVertexEye = (v * model * vec4(inVertex, 1) * scale).xyz;\n"
""
"    vec3 eye = vec3(0, 0, 1);\n"
"    vec3 pos = vVertexEye;\n"
"    vec3 V   = normalize(eye - pos);\n"
"    vec3 L   = normalize(-eye);\n"
"    vec3 N   = normalize(-vNormalEye);\n"
""
"    float si = max(0.0, pow(dot(reflect(L, N), V), sCoeff));\n"""
"    vColor = inColor * vec4(ac.rgb, 1.0) * ac.a + vec4(sc.xyz, 1.0) * si;\n"
"}\n";

static const char * carFsh =
"#version 130\n"
""
"in      vec4      ddRotated;\n"
"in      vec2      texCoord0;\n"
"in      vec2      texCoord1;\n"
"in      vec4      vColor;\n"
"uniform sampler2D tex0;\n"
"uniform sampler2D tex1;\n"
"uniform sampler2D tex2;\n"
"uniform vec4      dd = vec4(1, 1, 1, 1);\n"
"uniform vec4      dc = vec4(1, 1, 1, 1);\n"
"uniform float     dCoeff = 1;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    vec4 texColor = texture2D(tex0, texCoord0);\n"
"    vec4 sky      = texture2D(tex1, texCoord1);\n"
"    vec4 normal   = texture2D(tex2, texCoord0);\n"
""
"    if (texColor.a < 0.1)\n"
"    {\n"
"        discard;\n"
"    }\n"
"    else\n"
"    {\n"
"        vec3 N = normalize((normal.xyz - vec3(0.5, 0.5, 0.5)) * 2.0);\n"
"        float di = dot(-ddRotated.xyz, N) * dc.a;\n"
"        float refl = 0.33 * ((1.0 - texColor.r) + texColor.g + (1.0 - texColor.b));\n"
"        refl *= refl * refl;\n"
"        fragColor = 0.80 * (sky * refl + texColor * (1.0 - refl)) + 0.20 * (vec4(dc.rgb, 1.0) * di * dCoeff + vColor);\n"
"    }\n"
"}\n";

static const char * menuVsh =
"#version 130\n"
""
"in vec3 inVertex;\n"
"in vec2 inTexCoord;\n"
"in vec4 inColor;\n"
"uniform vec4 color = vec4(1, 1, 1, 1);\n"
"uniform vec4 scale = vec4(1, 1, 1, 1);\n"
"uniform mat4 vp;\n"
"uniform mat4 model;\n"
"out vec4 vColor;\n"
"out vec2 texCoord0;\n"
""
"void main()\n"
"{\n"
"    gl_Position = vp * model * (vec4(inVertex, 1) * scale);\n"
"    texCoord0 = inTexCoord;\n"
"    vColor = inColor * color;\n"
"}\n";

static const char * menuFsh =
"#version 130\n"
""
"in vec2 texCoord0;\n"
"in vec4 vColor;\n"
"uniform sampler2D tex0;\n"
"uniform float fade = 1;\n"
"out vec4 fragColor;\n"
""
"void main(void)\n"
"{\n"
"    vec4 texColor = texture2D(tex0, texCoord0);\n"
"    if (texColor.a < 0.1)\n"
"    {\n"
"        discard;\n"
"    }\n"
"    else\n"
"    {\n"
"        fragColor = vColor * texColor * fade;\n"
"    }\n"
"}\n";

static const char * fboVsh =
"#version 130\n"
""
"in  vec3 inVertex;\n"
"in  vec2 inTexCoord;\n"
"out vec2 texCoord0;\n"
""
"void main()\n"
"{\n"
"    gl_Position = vec4(inVertex, 1);\n"
"    texCoord0 = inTexCoord;\n"
"}\n";

static const char * fboFsh =
"#version 130\n"
""
"uniform sampler2D tex0;\n"
"uniform float     fade = 1;\n"
"in      vec2      texCoord0;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    fragColor = texture2D(tex0, texCoord0) * fade;\n"
"}\n";

static const char * tileVsh =
"#version 130\n"
""
"in      vec3  inVertex;\n"
"in      vec3  inNormal;\n"
"in      vec2  inTexCoord;\n"
"in      vec4  inColor;\n"
"uniform vec4  scale = vec4(1, 1, 1, 1);\n"
"uniform mat4  vp;\n"
"uniform mat4  model;\n"
"uniform vec4  dd = vec4(1, 1, 1, 1);\n"
"uniform vec4  dc = vec4(1, 1, 1, 1);\n"
"uniform vec4  ac = vec4(1, 1, 1, 1);\n"
"uniform  float dCoeff = 1;\n"
"out     vec2  texCoord0;\n"
"out     vec2  texCoord1;\n"
"out     vec4  vColor;\n"
""
"void main()\n"
"{\n"
"    gl_Position = vp * model * (vec4(inVertex, 1) * scale);\n"
"    float di = dot(dd.xyz, -inNormal) * dc.a;\n"
"    vColor = inColor * (\n"
"        vec4(ac.rgb, 1.0) * ac.a +\n"
"        vec4(dc.rgb, 1.0) * di * dCoeff);\n"
""
"    texCoord0 = inTexCoord;\n"
"    texCoord1 = inTexCoord;\n"
"}\n";

static const char * tile3dFsh =
"#version 130\n"
""
"uniform sampler2D tex0;\n"
"uniform sampler2D tex1;\n"
"uniform sampler2D tex2;\n"
"in      vec2      texCoord0;\n"
"in      vec4      vColor;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    vec4 color0 = texture2D(tex0, texCoord0);\n"
"    vec4 color1 = texture2D(tex1, texCoord0);\n"
"    vec4 color2 = texture2D(tex2, texCoord0);\n"
""
"    if (color0.a < 0.01)\n"
"    {\n"
"        discard;\n"
"    }\n"
"    else\n"
"    {\n"
"        if (color0.r == 0.0 && color0.b == 0.0)\n"
"        {\n"
"            color0 = mix(color1, color2, color0.g);\n"
"        }\n"
"        else if (color0.g == 0.0 && color0.b == 0.0)\n"
"        {\n"
"            color0 = color1;\n"
"        }\n"
""
"        fragColor = color0 * vColor;\n"
"    }\n"
"}\n";

#endif // SHADERS30_H
