//
//  CCEffectSpriteTemplate.h
//  2dxOpenGLES2
//
//  Created by Jon Wayne on 14-3-21.
//
//

#ifndef ___dxOpenGLES2__CCEffectSpriteTemplate__
#define ___dxOpenGLES2__CCEffectSpriteTemplate__

#include <cocos2d.h>

USING_NS_CC;


enum TemplateType
{
    kTemplateBlur,
    kTemplateSharpen,
    kTemplateDilate,
    kTemplateErode,
    kTemplateLaplacianEdgeDetection,
    kTemplateSobelEdgeDetection,
};

static const char *vertexSource = 
"\
attribute vec4 a_position;\
attribute vec4 a_color;\
attribute vec2 a_texCoord;\
\
varying vec4 v_Color;\
varying vec2 v_TexCoord;\
\
void main()\
{\
    gl_Position = CC_MVPMatrix * a_position;\
    v_Color = a_color;\
    v_TexCoord = a_texCoord;\
}\
";

static const char *fragSource1 = 
"\
uniform sampler2D CC_Texture0;\
uniform sampler2D u_Texture1;\
uniform sampler2D u_Texture2;\
uniform vec2 u_BlurDis;\
\
varying vec4 v_Color;\
varying vec2 v_TexCoord;\
\
void main()\
{\
    vec4 currColor = v_Color * texture2D(CC_Texture0, v_TexCoord);\
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0); \
    int kernelSpan[5] = {-2, -1, 0, 1, 2};\
";

static const char *fragSource3 = 
"\
    for (int i = 0; i < 5; ++i)\
    {\
        for (int j = 0; j < 5; ++j)\
        {\
            vec2 currPos = v_TexCoord + vec2(float(kernelSpan[i]) * u_BlurDis.x, float(kernelSpan[j]) * u_BlurDis.y);\
            finalColor = finalColor + texture2D(CC_Texture0, currPos) * float(kernel[i*5+j]);\
        }\
    }\
    gl_FragColor = finalColor / kernelFactor;\
}";

static const char *fragSource2[] = 
{
    //kTemplateBlur
    "int kernel[25] = \
    {\
        1,  4,  7,  4, 1,\
        4, 16, 26, 16, 4,\
        7, 26, 41, 26, 7,\
        4, 16, 26, 16, 4,\
        1,  4,  7,  4, 1,\
    };\
    float kernelFactor = 273.0;",
    //kTemplateSharpen
    "int kernel[25] = \
    {\
        1, 1,   1, 1, 1,\
        1, 1,   1, 1, 1,\
        1, 1, -14, 1, 1,\
        1, 1,   1, 1, 1,\
        1, 1,   1, 1, 1,\
    };\
    float kernelFactor = 14.0;",
    //kTemplateDilate
    "int kernel[25] = \
    {\
        -1, -1, -1, -1, -1,\
        -1, -1, -1, -1, -1,\
        -1, -1, 24, -1, -1,\
        -1, -1, -1, -1, -1,\
        -1, -1, -1, -1, -1,\
    };\
    float kernelFactor = 14.0;",
};

#endif /* defined(___dxOpenGLES2__CCEffectSpriteTemplate__) */