//
//  CCEffectSprite.h
//  2dxOpenGLES2
//
//  Created by Jon Wayne on 14-3-21.
//
//

#ifndef ___dxOpenGLES2__CCEffectSprite__
#define ___dxOpenGLES2__CCEffectSprite__

#include <cocos2d.h>
#include "CCEffectSpriteTemplate.h"

USING_NS_CC;

enum EffectSpriteMode
{
    kNormal,
    kSimpleBlur,
    kGaussianBlur,
	kTreeSimpleBlur,
	kStroke,
	kGlow,
	kFloatingGlow,
	kTemplate,
};

// uniform location index
enum UniformLocationIndex
{
    kUniformSampler1,
    kUniformSampler2,
    kUniformBlurDis,
	kUniformStrokeColor,
    
    UniformIndexNum
};

// uniform names
#define UniformSampler1                 "u_Texture1"
#define UniformSampler2                 "u_Texture2"
#define UniformBlurDis                  "u_BlurDis"
#define UniformStrokeColor              "u_StrokeColor"

class CCEffectSprite : public CCSprite
{
public:
    CCEffectSprite();
    virtual ~CCEffectSprite();
    
    static CCEffectSprite *create();
    
    virtual bool init();
    
    void setMode(EffectSpriteMode mode);
	void setTemplateType(TemplateType type);
    
    void setTexture1(CCTexture2D *tex);
    void setTexture2(CCTexture2D *tex);

	void setStrokeColor(ccColor3B strokeColor);
private:
	void visitTreeSimpleBlur();
	void visitGlow();

    void drawSimpleBlur();
    void drawGaussianBlur();
	void drawFloatingGlow();
    
	virtual void visit();
    virtual void draw();
	void spriteDraw();

private:
	EffectSpriteMode _mode;
    
    CCTexture2D *_texture1;
    CCTexture2D *_texture2;
    
    GLint _uniforms[UniformIndexNum];
    
	GLuint _framebuffer;
	GLuint _texture;

	CCSize _screenBufferSize;
	float _pixelSpan;

	ccColor3B _strokeColor;
};

#endif /* defined(___dxOpenGLES2__CCEffectSprite__) */
