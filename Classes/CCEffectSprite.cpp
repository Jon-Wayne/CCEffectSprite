//
//  CCEffectSprite.cpp
//  2dxOpenGLES2
//
//  Created by Jon Wayne on 14-3-21.
//
//

#include "CCEffectSprite.h"

CCEffectSprite::CCEffectSprite()
{
    _mode = kNormal;
    _texture1 = NULL;
    _texture2 = NULL;
}

CCEffectSprite::~CCEffectSprite()
{
    CC_SAFE_RELEASE(_texture1);
    CC_SAFE_RELEASE(_texture2);
}

CCEffectSprite *CCEffectSprite::create()
{
    CCEffectSprite *obj = new CCEffectSprite();
    
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    
    return NULL;
}

bool CCEffectSprite::init()
{
    if (CCSprite::init()) {
        CCEGLView *eglView = CCDirector::sharedDirector()->getOpenGLView();
        float zoomScale = eglView->getFrameZoomFactor();
        CCSize frameSize = eglView->getFrameSize();
        _screenBufferSize = CCSizeMake(frameSize.width*zoomScale, frameSize.height*zoomScale);
        CCLOG("frameSize : %f, %f", frameSize.width, frameSize.height);
        
        _pixelSpan = 0.0f;

        return true;
    } else {
        return false;
    }
}

void CCEffectSprite::setMode(EffectSpriteMode mode)
{
    if (_mode == mode) {
        return;
    }
    
    _mode = mode;
    
    switch (_mode) {
        case kNormal:
        {
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
            break;
        }
        case kSimpleBlur:
        {
            // shader
            CCGLProgram *program = new CCGLProgram();
            program->initWithVertexShaderFilename("CCEffectSpriteSimpleBlur.vsh", "CCEffectSpriteSimpleBlur.fsh");
            
            // built-in attributes and uniforms by 2dx
            program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            program->link();
            program->updateUniforms();
            
            // new
            _uniforms[kUniformSampler1] = glGetUniformLocation(program->getProgram(), UniformSampler1);
            _uniforms[kUniformSampler2] = glGetUniformLocation(program->getProgram(), UniformSampler2);
            _uniforms[kUniformBlurDis] = glGetUniformLocation(program->getProgram(), UniformBlurDis);
            
            setShaderProgram(program);

            _pixelSpan = 1.0f;

            break;
        }
        case kGaussianBlur:
        {
            // shader
            CCGLProgram *program = new CCGLProgram();
            program->initWithVertexShaderFilename("CCEffectSpriteGaussianBlur.vsh", "CCEffectSpriteGaussianBlur.fsh");
            
            // built-in attributes and uniforms by 2dx
            program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            program->link();
            program->updateUniforms();
            
            // new
            _uniforms[kUniformSampler1] = glGetUniformLocation(program->getProgram(), UniformSampler1);
            _uniforms[kUniformSampler2] = glGetUniformLocation(program->getProgram(), UniformSampler2);
            _uniforms[kUniformBlurDis] = glGetUniformLocation(program->getProgram(), UniformBlurDis);
            
            setShaderProgram(program);

            _pixelSpan = 0.5f;

            break;
        }
        case kTreeSimpleBlur:
        {
            // shader
            CCGLProgram *program = new CCGLProgram();
            program->initWithVertexShaderFilename("CCEffectSpriteSimpleBlur.vsh", "CCEffectSpriteSimpleBlur.fsh");
            
            // built-in attributes and uniforms by 2dx
            program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            program->link();
            program->updateUniforms();
            
            // new
            _uniforms[kUniformSampler1] = glGetUniformLocation(program->getProgram(), UniformSampler1);
            _uniforms[kUniformSampler2] = glGetUniformLocation(program->getProgram(), UniformSampler2);
            _uniforms[kUniformBlurDis] = glGetUniformLocation(program->getProgram(), UniformBlurDis);
            
            setShaderProgram(program);

            _pixelSpan = 2.0f;

            break;
        }
        case kStroke:
        {
            // shader
            CCGLProgram *program = new CCGLProgram();
            program->initWithVertexShaderFilename("CCEffectSpriteStroke.vsh", "CCEffectSpriteStroke.fsh");
            
            // built-in attributes and uniforms by 2dx
            program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            program->link();
            program->updateUniforms();
            
            // new
            _uniforms[kUniformSampler1] = glGetUniformLocation(program->getProgram(), UniformSampler1);
            _uniforms[kUniformSampler2] = glGetUniformLocation(program->getProgram(), UniformSampler2);
            _uniforms[kUniformBlurDis] = glGetUniformLocation(program->getProgram(), UniformBlurDis);
            _uniforms[kUniformStrokeColor] = glGetUniformLocation(program->getProgram(), UniformStrokeColor);
            
            setShaderProgram(program);

            _pixelSpan = 3.0f;
            _strokeColor = ccc3(0, 255, 0);

            break;
        }
        case kGlow:
        {
            // shader
            CCGLProgram *program = new CCGLProgram();
            program->initWithVertexShaderFilename("CCEffectSpriteGlow.vsh", "CCEffectSpriteGlow.fsh");
            
            // built-in attributes and uniforms by 2dx
            program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            program->link();
            program->updateUniforms();
            
            // new
            _uniforms[kUniformSampler1] = glGetUniformLocation(program->getProgram(), UniformSampler1);
            _uniforms[kUniformSampler2] = glGetUniformLocation(program->getProgram(), UniformSampler2);
            _uniforms[kUniformBlurDis] = glGetUniformLocation(program->getProgram(), UniformBlurDis);
            _uniforms[kUniformStrokeColor] = glGetUniformLocation(program->getProgram(), UniformStrokeColor);
            
            setShaderProgram(program);

            _pixelSpan = 1.5f;

            break;
        }
        case kFloatingGlow:
        {
            // shader
            CCGLProgram *program = new CCGLProgram();
            program->initWithVertexShaderFilename("CCEffectSpriteFloatingGlow.vsh", "CCEffectSpriteFloatingGlow.fsh");
            
            // built-in attributes and uniforms by 2dx
            program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
            program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
            program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
            program->link();
            program->updateUniforms();
            
            // new
            _uniforms[kUniformSampler1] = glGetUniformLocation(program->getProgram(), UniformSampler1);
            _uniforms[kUniformSampler2] = glGetUniformLocation(program->getProgram(), UniformSampler2);
            _uniforms[kUniformBlurDis] = glGetUniformLocation(program->getProgram(), UniformBlurDis);
            _uniforms[kUniformStrokeColor] = glGetUniformLocation(program->getProgram(), UniformStrokeColor);
            
            glUniform1i(_uniforms[kUniformSampler1], 1);

            setShaderProgram(program);

            break;
        }
        case kTemplate:
        {
            setTemplateType(kTemplateBlur);

            break;
        }
        default:
            
            break;
    }
}

void CCEffectSprite::setTemplateType(TemplateType type)
{
    if (!fragSource2[type]) {
        return;
    }
    // shader
    CCGLProgram *program = new CCGLProgram();
    const GLchar * vs = (GLchar*)vertexSource;
    char buffer[1024] = {0};
    sprintf(buffer, "%s%s%s", fragSource1, fragSource2[type], fragSource3);
    const GLchar * fs = (GLchar*)buffer;
    CCLOG("%s\n%s", vs, fs);
    program->initWithVertexShaderByteArray(vs, fs);
    
    // built-in attributes and uniforms by 2dx
    program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    program->link();
    program->updateUniforms();
    
    // new
    _uniforms[kUniformSampler1] = glGetUniformLocation(program->getProgram(), UniformSampler1);
    _uniforms[kUniformSampler2] = glGetUniformLocation(program->getProgram(), UniformSampler2);
    _uniforms[kUniformBlurDis] = glGetUniformLocation(program->getProgram(), UniformBlurDis);
    
    setShaderProgram(program);

    _pixelSpan = 1.0f;
}

void CCEffectSprite::setTexture1(CCTexture2D *tex)
{
    if (!tex) return;
    
    CC_SAFE_RETAIN(tex);
    CC_SAFE_RELEASE(_texture1);
    _texture1 = tex;
}

void CCEffectSprite::setTexture2(CCTexture2D *tex)
{
    if (!tex) return;
    
    CC_SAFE_RETAIN(tex);
    CC_SAFE_RELEASE(_texture2);
    _texture2 = tex;
}

void CCEffectSprite::setStrokeColor(ccColor3B strokeColor)
{
    _strokeColor = strokeColor;
}

void CCEffectSprite::drawSimpleBlur()
{
    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    ccGLBindTexture2D(m_pobTexture->getName());
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    
    // uniforms
    float blursDis[2] = {_pixelSpan/getTextureRect().size.width, _pixelSpan/getTextureRect().size.height};
    glUniform2f(_uniforms[kUniformBlurDis], blursDis[0], blursDis[1]);
    
    // attributes
    GLint size = sizeof(ccV3F_C4B_T2F);
    long data = (long)&m_sQuad;
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, size, (GLvoid *)data);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, size, (GLvoid *)(data + sizeof(ccVertex3F)));
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, size, (GLvoid *)(data + sizeof(ccVertex3F) + sizeof(ccColor4B)));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void CCEffectSprite::drawGaussianBlur()
{
    float blursDis[2] = {_pixelSpan/getTextureRect().size.width, _pixelSpan/_screenBufferSize.height};
    GLint size = sizeof(ccV3F_C4B_T2F);
    long data = (long)&m_sQuad;

    /**/
    // gen a empty texture
    // size is just used to decide how high the picture qulity is finally.
    // or size must be the frame size, cause the real drawn pixels must be the same with buffer's.
    // (the real problem is, when frame size is not same with buffer size, what will happpen?)
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _screenBufferSize.width, _screenBufferSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // gen a off-screen framebuffer
    GLint oldFBO;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldFBO);
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        CCLOG("glCheckFramebufferStatus ERROR! 0x%04x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    
    
    // ************ first draw ******************
    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    // ccGLBindTexture2D(m_pobTexture->getName());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pobTexture->getName());
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    
    // uniforms
    glUniform2f(_uniforms[kUniformBlurDis], blursDis[0], 0.00f);
    
    // attributes
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, size, (GLvoid *)data);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, size, (GLvoid *)(data + sizeof(ccVertex3F)));
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, size, (GLvoid *)(data + sizeof(ccVertex3F) + sizeof(ccColor4B)));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // ******************************************
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
    
    
    // ************** second draw *****************
    // reset stack
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    glViewport(0, 0, _screenBufferSize.width, _screenBufferSize.height);
    
    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    // ccGLBindTexture2D(m_pobTexture->getName());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

    // uniforms
    glUniform2f(_uniforms[kUniformBlurDis], 0.00f, blursDis[1]);
    
    // attributes
    // do not add any other render info, just do another direction blur:
    ccV3F_C4B_T2F_Quad tempQuad;
    memset(&tempQuad, 0, sizeof(tempQuad));
    // vertices are located in the 4 corners of the whole viewport.
    tempQuad.tl.vertices = vertex3(-1, 1, -1);
    tempQuad.bl.vertices = vertex3(-1, -1, -1);
    tempQuad.tr.vertices = vertex3(1, 1, -1);
    tempQuad.br.vertices = vertex3(1, -1, -1);
    // color is black which won't change any color info.
    tempQuad.tl.colors = ccc4(255, 255, 255, 255);
    tempQuad.bl.colors = ccc4(255, 255, 255, 255);
    tempQuad.tr.colors = ccc4(255, 255, 255, 255);
    tempQuad.br.colors = ccc4(255, 255, 255, 255);
    // UV y-coords is also fliped just like what CCSprite did in above step.
    tempQuad.tl.texCoords = tex2(0, 1);
    tempQuad.bl.texCoords = tex2(0, 0);
    tempQuad.tr.texCoords = tex2(1, 1);
    tempQuad.br.texCoords = tex2(1, 0);
    data = (long)&tempQuad;
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, size, (GLvoid *)data);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, size, (GLvoid *)(data + sizeof(ccVertex3F)));
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, size, (GLvoid *)(data + sizeof(ccVertex3F) + sizeof(ccColor4B)));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // restore stack
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
    CCDirector::sharedDirector()->setViewport();
    // **************************************
    
    /**/
    glDeleteTextures(1, &_texture);
    glDeleteFramebuffers(1, &_framebuffer);
}

void CCEffectSprite::drawFloatingGlow()
{
    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    ccGLBindTexture2D(m_pobTexture->getName());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texture1->getName());
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    
    // uniforms
    float blursDis[2] = {_pixelSpan/getTextureRect().size.width, _pixelSpan/getTextureRect().size.height};
    glUniform2f(_uniforms[kUniformBlurDis], blursDis[0], blursDis[1]);
    
    // attributes
    GLint size = sizeof(ccV3F_C4B_T2F);
    long data = (long)&m_sQuad;
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, size, (GLvoid *)data);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, size, (GLvoid *)(data + sizeof(ccVertex3F)));
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, size, (GLvoid *)(data + sizeof(ccVertex3F) + sizeof(ccColor4B)));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void CCEffectSprite::visitTreeSimpleBlur()
{
    float blursDis[2] = {_pixelSpan/_screenBufferSize.width, _pixelSpan/_screenBufferSize.height};
    GLint size = sizeof(ccV3F_C4B_T2F);
    long data = (long)&m_sQuad;

    /**/
    // gen a empty texture
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _screenBufferSize.width, _screenBufferSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // gen a off-screen framebuffer
    GLint oldFBO;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldFBO);
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        CCLOG("glCheckFramebufferStatus ERROR! 0x%04x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    
    
    // ************ first draw ******************
    CCNode::visit();
    // ******************************************
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
    
    
    // ************** second draw *****************
    // reset stack
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    glViewport(0, 0, _screenBufferSize.width, _screenBufferSize.height);
    
    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

    // uniforms
    glUniform2f(_uniforms[kUniformBlurDis], blursDis[0], blursDis[1]);
    if (_mode == kStroke) {
        glUniform3f(_uniforms[kUniformStrokeColor], (float)_strokeColor.r/255.0f, (float)_strokeColor.g/255.0f, (float)_strokeColor.b/255.0f);
    }
    
    // attributes
    ccV3F_C4B_T2F_Quad tempQuad;
    memset(&tempQuad, 0, sizeof(tempQuad));
    tempQuad.tl.vertices = vertex3(-1, 1, -1);
    tempQuad.bl.vertices = vertex3(-1, -1, -1);
    tempQuad.tr.vertices = vertex3(1, 1, -1);
    tempQuad.br.vertices = vertex3(1, -1, -1);
    tempQuad.tl.colors = ccc4(255, 255, 255, 255);
    tempQuad.bl.colors = ccc4(255, 255, 255, 255);
    tempQuad.tr.colors = ccc4(255, 255, 255, 255);
    tempQuad.br.colors = ccc4(255, 255, 255, 255);
    tempQuad.tl.texCoords = tex2(0, 1);
    tempQuad.bl.texCoords = tex2(0, 0);
    tempQuad.tr.texCoords = tex2(1, 1);
    tempQuad.br.texCoords = tex2(1, 0);
    data = (long)&tempQuad;
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, size, (GLvoid *)data);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, size, (GLvoid *)(data + sizeof(ccVertex3F)));
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, size, (GLvoid *)(data + sizeof(ccVertex3F) + sizeof(ccColor4B)));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // restore stack
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
    CCDirector::sharedDirector()->setViewport();
    // **************************************
    
    /**/
    glDeleteTextures(1, &_texture);
    glDeleteFramebuffers(1, &_framebuffer);
}

void CCEffectSprite::visitGlow()
{
    float blursDis[2] = {_pixelSpan/_screenBufferSize.width, _pixelSpan/_screenBufferSize.height};
    GLint size = sizeof(ccV3F_C4B_T2F);
    long data = (long)&m_sQuad;

    /**/
    // gen a empty texture
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _screenBufferSize.width, _screenBufferSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // gen a off-screen framebuffer
    GLint oldFBO;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldFBO);
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        CCLOG("glCheckFramebufferStatus ERROR! 0x%04x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    
    
    // ************ first draw ******************
    CCNode::visit();
    // ******************************************
    
    
    
    // gen a empty texture
    GLuint _texture2;
    glGenTextures(1, &_texture2);
    glBindTexture(GL_TEXTURE_2D, _texture2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _screenBufferSize.width, _screenBufferSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // gen a off-screen framebuffer
    GLuint _framebuffer2;
    glGenFramebuffers(1, &_framebuffer2);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer2);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture2, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        CCLOG("glCheckFramebufferStatus ERROR! 0x%04x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }

    
    // ************** second draw *****************
    // reset stack
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    glViewport(0, 0, _screenBufferSize.width, _screenBufferSize.height);
    
    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

    // uniforms
    glUniform2f(_uniforms[kUniformBlurDis], blursDis[0], 0.0f);
    
    // attributes
    ccV3F_C4B_T2F_Quad tempQuad;
    memset(&tempQuad, 0, sizeof(tempQuad));
    tempQuad.tl.vertices = vertex3(-1, 1, -1);
    tempQuad.bl.vertices = vertex3(-1, -1, -1);
    tempQuad.tr.vertices = vertex3(1, 1, -1);
    tempQuad.br.vertices = vertex3(1, -1, -1);
    tempQuad.tl.colors = ccc4(255, 255, 255, 255);
    tempQuad.bl.colors = ccc4(255, 255, 255, 255);
    tempQuad.tr.colors = ccc4(255, 255, 255, 255);
    tempQuad.br.colors = ccc4(255, 255, 255, 255);
    tempQuad.tl.texCoords = tex2(0, 1);
    tempQuad.bl.texCoords = tex2(0, 0);
    tempQuad.tr.texCoords = tex2(1, 1);
    tempQuad.br.texCoords = tex2(1, 0);
    data = (long)&tempQuad;
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, size, (GLvoid *)data);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, size, (GLvoid *)(data + sizeof(ccVertex3F)));
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, size, (GLvoid *)(data + sizeof(ccVertex3F) + sizeof(ccColor4B)));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // **************************************
    


    // ************** third draw *****************
    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);

    CC_NODE_DRAW_SETUP();
    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture2);
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

    // uniforms
    glUniform2f(_uniforms[kUniformBlurDis], 0.0f, blursDis[1]);

    // attributes
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, size, (GLvoid *)data);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, size, (GLvoid *)(data + sizeof(ccVertex3F)));
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, size, (GLvoid *)(data + sizeof(ccVertex3F) + sizeof(ccColor4B)));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // **************************************
    
    // restore stack
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();
    CCDirector::sharedDirector()->setViewport();

    /**/
    glDeleteTextures(1, &_texture);
    glDeleteFramebuffers(1, &_framebuffer);
    glDeleteTextures(1, &_texture2);
    glDeleteFramebuffers(1, &_framebuffer2);
}


void CCEffectSprite::visit()
{
    switch (_mode) {
        case kTreeSimpleBlur:
        case kStroke:
            visitTreeSimpleBlur();
            break;
        case kGlow:
            visitGlow();
            break;
        default:
            CCNode::visit();
            break;
    }
}

void CCEffectSprite::draw()
{
    switch (_mode) {
        case kNormal:
            CCSprite::draw();
            break;
        case kSimpleBlur:
            drawSimpleBlur();
            break;
        case kGaussianBlur:
            drawGaussianBlur();
            break;
        case kFloatingGlow:
            drawFloatingGlow();
            break;
        case kTemplate:
            drawSimpleBlur();
            break;
        default:
            CCSprite::draw();
            break;
    }
    
    CHECK_GL_ERROR_DEBUG();
    CC_INCREMENT_GL_DRAWS(1);
}

void CCEffectSprite::spriteDraw(void)
{
    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");

    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");

    // reset all data, just model view matrix is fine.
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    kmGLLoadIdentity();
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPushMatrix();
    kmGLLoadIdentity();/**/

    // test
    m_sQuad.tl.vertices = vertex3(-0.5, 0.5, 1.0);
    m_sQuad.bl.vertices = vertex3(-0.5, -0.5, 1.0);
    m_sQuad.tr.vertices = vertex3(0.5, 0.5, 1.0);
    m_sQuad.br.vertices = vertex3(0.5, -0.5, 1.0);

    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

    ccGLBindTexture2D( m_pobTexture->getName() );
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
    long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN

    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CHECK_GL_ERROR_DEBUG();

    // set old
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLPopMatrix();
    kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPopMatrix();/**/

#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    CCPoint vertices[4]={
        ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
        ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
        ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
        ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
    };
    ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    CCSize s = this->getTextureRect().size;
    CCPoint offsetPix = this->getOffsetPosition();
    CCPoint vertices[4] = {
        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW

    CC_INCREMENT_GL_DRAWS(1);

    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}