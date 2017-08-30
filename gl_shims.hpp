#ifndef GL_SHIMS_HPP
#define GL_SHIMS_HPP 1

#ifndef PROTOTYPES
#define PROTOTYPES 1
#include "glcorearb.h"

bool init_gl_shims();
//Prototypes for 1.0,1.1 functionality, pretty sure that already exists:

extern "C" {


// GL_VERSION_1_0 prototypes:
GLAPI void APIENTRY glCullFace (GLenum mode);
GLAPI void APIENTRY glFrontFace (GLenum mode);
GLAPI void APIENTRY glHint (GLenum target, GLenum mode);
GLAPI void APIENTRY glLineWidth (GLfloat width);
GLAPI void APIENTRY glPointSize (GLfloat size);
GLAPI void APIENTRY glPolygonMode (GLenum face, GLenum mode);
GLAPI void APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI void APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
GLAPI void APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
GLAPI void APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
GLAPI void APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
GLAPI void APIENTRY glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
GLAPI void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
GLAPI void APIENTRY glDrawBuffer (GLenum buf);
GLAPI void APIENTRY glClear (GLbitfield mask);
GLAPI void APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLAPI void APIENTRY glClearStencil (GLint s);
GLAPI void APIENTRY glClearDepth (GLdouble depth);
GLAPI void APIENTRY glStencilMask (GLuint mask);
GLAPI void APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GLAPI void APIENTRY glDepthMask (GLboolean flag);
GLAPI void APIENTRY glDisable (GLenum cap);
GLAPI void APIENTRY glEnable (GLenum cap);
GLAPI void APIENTRY glFinish (void);
GLAPI void APIENTRY glFlush (void);
GLAPI void APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
GLAPI void APIENTRY glLogicOp (GLenum opcode);
GLAPI void APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
GLAPI void APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GLAPI void APIENTRY glDepthFunc (GLenum func);
GLAPI void APIENTRY glPixelStoref (GLenum pname, GLfloat param);
GLAPI void APIENTRY glPixelStorei (GLenum pname, GLint param);
GLAPI void APIENTRY glReadBuffer (GLenum src);
GLAPI void APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
GLAPI void APIENTRY glGetBooleanv (GLenum pname, GLboolean *data);
GLAPI void APIENTRY glGetDoublev (GLenum pname, GLdouble *data);
GLAPI GLenum APIENTRY glGetError (void);
GLAPI void APIENTRY glGetFloatv (GLenum pname, GLfloat *data);
GLAPI void APIENTRY glGetIntegerv (GLenum pname, GLint *data);
GLAPI const GLubyte *APIENTRY glGetString (GLenum name);
GLAPI void APIENTRY glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
GLAPI void APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
GLAPI void APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
GLAPI GLboolean APIENTRY glIsEnabled (GLenum cap);
GLAPI void APIENTRY glDepthRange (GLdouble near, GLdouble far);
GLAPI void APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);


}

#endif //PROTOTYPES

//--------------------------------------------------------

#ifndef DO
#define DO(TYPE, NAME) 	extern PFNGL ## TYPE ## PROC gl ## NAME;
#endif



// GL_VERSION_1_1 extensions:
DO(DRAWARRAYS, DrawArrays)
DO(DRAWELEMENTS, DrawElements)
DO(GETPOINTERV, GetPointerv)
DO(POLYGONOFFSET, PolygonOffset)
DO(COPYTEXIMAGE1D, CopyTexImage1D)
DO(COPYTEXIMAGE2D, CopyTexImage2D)
DO(COPYTEXSUBIMAGE1D, CopyTexSubImage1D)
DO(COPYTEXSUBIMAGE2D, CopyTexSubImage2D)
DO(TEXSUBIMAGE1D, TexSubImage1D)
DO(TEXSUBIMAGE2D, TexSubImage2D)
DO(BINDTEXTURE, BindTexture)
DO(DELETETEXTURES, DeleteTextures)
DO(GENTEXTURES, GenTextures)
DO(ISTEXTURE, IsTexture)

// GL_VERSION_1_2 extensions:
DO(DRAWRANGEELEMENTS, DrawRangeElements)
DO(TEXIMAGE3D, TexImage3D)
DO(TEXSUBIMAGE3D, TexSubImage3D)
DO(COPYTEXSUBIMAGE3D, CopyTexSubImage3D)

// GL_VERSION_1_3 extensions:
DO(ACTIVETEXTURE, ActiveTexture)
DO(SAMPLECOVERAGE, SampleCoverage)
DO(COMPRESSEDTEXIMAGE3D, CompressedTexImage3D)
DO(COMPRESSEDTEXIMAGE2D, CompressedTexImage2D)
DO(COMPRESSEDTEXIMAGE1D, CompressedTexImage1D)
DO(COMPRESSEDTEXSUBIMAGE3D, CompressedTexSubImage3D)
DO(COMPRESSEDTEXSUBIMAGE2D, CompressedTexSubImage2D)
DO(COMPRESSEDTEXSUBIMAGE1D, CompressedTexSubImage1D)
DO(GETCOMPRESSEDTEXIMAGE, GetCompressedTexImage)

// GL_VERSION_1_4 extensions:
DO(BLENDFUNCSEPARATE, BlendFuncSeparate)
DO(MULTIDRAWARRAYS, MultiDrawArrays)
DO(MULTIDRAWELEMENTS, MultiDrawElements)
DO(POINTPARAMETERF, PointParameterf)
DO(POINTPARAMETERFV, PointParameterfv)
DO(POINTPARAMETERI, PointParameteri)
DO(POINTPARAMETERIV, PointParameteriv)
DO(BLENDCOLOR, BlendColor)
DO(BLENDEQUATION, BlendEquation)

// GL_VERSION_1_5 extensions:
DO(GENQUERIES, GenQueries)
DO(DELETEQUERIES, DeleteQueries)
DO(ISQUERY, IsQuery)
DO(BEGINQUERY, BeginQuery)
DO(ENDQUERY, EndQuery)
DO(GETQUERYIV, GetQueryiv)
DO(GETQUERYOBJECTIV, GetQueryObjectiv)
DO(GETQUERYOBJECTUIV, GetQueryObjectuiv)
DO(BINDBUFFER, BindBuffer)
DO(DELETEBUFFERS, DeleteBuffers)
DO(GENBUFFERS, GenBuffers)
DO(ISBUFFER, IsBuffer)
DO(BUFFERDATA, BufferData)
DO(BUFFERSUBDATA, BufferSubData)
DO(GETBUFFERSUBDATA, GetBufferSubData)
DO(UNMAPBUFFER, UnmapBuffer)
DO(GETBUFFERPARAMETERIV, GetBufferParameteriv)
DO(GETBUFFERPOINTERV, GetBufferPointerv)

// GL_VERSION_2_0 extensions:
DO(BLENDEQUATIONSEPARATE, BlendEquationSeparate)
DO(DRAWBUFFERS, DrawBuffers)
DO(STENCILOPSEPARATE, StencilOpSeparate)
DO(STENCILFUNCSEPARATE, StencilFuncSeparate)
DO(STENCILMASKSEPARATE, StencilMaskSeparate)
DO(ATTACHSHADER, AttachShader)
DO(BINDATTRIBLOCATION, BindAttribLocation)
DO(COMPILESHADER, CompileShader)
DO(CREATEPROGRAM, CreateProgram)
DO(CREATESHADER, CreateShader)
DO(DELETEPROGRAM, DeleteProgram)
DO(DELETESHADER, DeleteShader)
DO(DETACHSHADER, DetachShader)
DO(DISABLEVERTEXATTRIBARRAY, DisableVertexAttribArray)
DO(ENABLEVERTEXATTRIBARRAY, EnableVertexAttribArray)
DO(GETACTIVEATTRIB, GetActiveAttrib)
DO(GETACTIVEUNIFORM, GetActiveUniform)
DO(GETATTACHEDSHADERS, GetAttachedShaders)
DO(GETATTRIBLOCATION, GetAttribLocation)
DO(GETPROGRAMIV, GetProgramiv)
DO(GETPROGRAMINFOLOG, GetProgramInfoLog)
DO(GETSHADERIV, GetShaderiv)
DO(GETSHADERINFOLOG, GetShaderInfoLog)
DO(GETSHADERSOURCE, GetShaderSource)
DO(GETUNIFORMLOCATION, GetUniformLocation)
DO(GETUNIFORMFV, GetUniformfv)
DO(GETUNIFORMIV, GetUniformiv)
DO(GETVERTEXATTRIBDV, GetVertexAttribdv)
DO(GETVERTEXATTRIBFV, GetVertexAttribfv)
DO(GETVERTEXATTRIBIV, GetVertexAttribiv)
DO(GETVERTEXATTRIBPOINTERV, GetVertexAttribPointerv)
DO(ISPROGRAM, IsProgram)
DO(ISSHADER, IsShader)
DO(LINKPROGRAM, LinkProgram)
DO(SHADERSOURCE, ShaderSource)
DO(USEPROGRAM, UseProgram)
DO(UNIFORM1F, Uniform1f)
DO(UNIFORM2F, Uniform2f)
DO(UNIFORM3F, Uniform3f)
DO(UNIFORM4F, Uniform4f)
DO(UNIFORM1I, Uniform1i)
DO(UNIFORM2I, Uniform2i)
DO(UNIFORM3I, Uniform3i)
DO(UNIFORM4I, Uniform4i)
DO(UNIFORM1FV, Uniform1fv)
DO(UNIFORM2FV, Uniform2fv)
DO(UNIFORM3FV, Uniform3fv)
DO(UNIFORM4FV, Uniform4fv)
DO(UNIFORM1IV, Uniform1iv)
DO(UNIFORM2IV, Uniform2iv)
DO(UNIFORM3IV, Uniform3iv)
DO(UNIFORM4IV, Uniform4iv)
DO(UNIFORMMATRIX2FV, UniformMatrix2fv)
DO(UNIFORMMATRIX3FV, UniformMatrix3fv)
DO(UNIFORMMATRIX4FV, UniformMatrix4fv)
DO(VALIDATEPROGRAM, ValidateProgram)
DO(VERTEXATTRIB1D, VertexAttrib1d)
DO(VERTEXATTRIB1DV, VertexAttrib1dv)
DO(VERTEXATTRIB1F, VertexAttrib1f)
DO(VERTEXATTRIB1FV, VertexAttrib1fv)
DO(VERTEXATTRIB1S, VertexAttrib1s)
DO(VERTEXATTRIB1SV, VertexAttrib1sv)
DO(VERTEXATTRIB2D, VertexAttrib2d)
DO(VERTEXATTRIB2DV, VertexAttrib2dv)
DO(VERTEXATTRIB2F, VertexAttrib2f)
DO(VERTEXATTRIB2FV, VertexAttrib2fv)
DO(VERTEXATTRIB2S, VertexAttrib2s)
DO(VERTEXATTRIB2SV, VertexAttrib2sv)
DO(VERTEXATTRIB3D, VertexAttrib3d)
DO(VERTEXATTRIB3DV, VertexAttrib3dv)
DO(VERTEXATTRIB3F, VertexAttrib3f)
DO(VERTEXATTRIB3FV, VertexAttrib3fv)
DO(VERTEXATTRIB3S, VertexAttrib3s)
DO(VERTEXATTRIB3SV, VertexAttrib3sv)
DO(VERTEXATTRIB4NBV, VertexAttrib4Nbv)
DO(VERTEXATTRIB4NIV, VertexAttrib4Niv)
DO(VERTEXATTRIB4NSV, VertexAttrib4Nsv)
DO(VERTEXATTRIB4NUB, VertexAttrib4Nub)
DO(VERTEXATTRIB4NUBV, VertexAttrib4Nubv)
DO(VERTEXATTRIB4NUIV, VertexAttrib4Nuiv)
DO(VERTEXATTRIB4NUSV, VertexAttrib4Nusv)
DO(VERTEXATTRIB4BV, VertexAttrib4bv)
DO(VERTEXATTRIB4D, VertexAttrib4d)
DO(VERTEXATTRIB4DV, VertexAttrib4dv)
DO(VERTEXATTRIB4F, VertexAttrib4f)
DO(VERTEXATTRIB4FV, VertexAttrib4fv)
DO(VERTEXATTRIB4IV, VertexAttrib4iv)
DO(VERTEXATTRIB4S, VertexAttrib4s)
DO(VERTEXATTRIB4SV, VertexAttrib4sv)
DO(VERTEXATTRIB4UBV, VertexAttrib4ubv)
DO(VERTEXATTRIB4UIV, VertexAttrib4uiv)
DO(VERTEXATTRIB4USV, VertexAttrib4usv)
DO(VERTEXATTRIBPOINTER, VertexAttribPointer)

// GL_VERSION_2_1 extensions:
DO(UNIFORMMATRIX2X3FV, UniformMatrix2x3fv)
DO(UNIFORMMATRIX3X2FV, UniformMatrix3x2fv)
DO(UNIFORMMATRIX2X4FV, UniformMatrix2x4fv)
DO(UNIFORMMATRIX4X2FV, UniformMatrix4x2fv)
DO(UNIFORMMATRIX3X4FV, UniformMatrix3x4fv)
DO(UNIFORMMATRIX4X3FV, UniformMatrix4x3fv)

// GL_VERSION_3_0 extensions:
DO(COLORMASKI, ColorMaski)
DO(GETBOOLEANI_V, GetBooleani_v)
DO(GETINTEGERI_V, GetIntegeri_v)
DO(ENABLEI, Enablei)
DO(DISABLEI, Disablei)
DO(ISENABLEDI, IsEnabledi)
DO(BEGINTRANSFORMFEEDBACK, BeginTransformFeedback)
DO(ENDTRANSFORMFEEDBACK, EndTransformFeedback)
DO(BINDBUFFERRANGE, BindBufferRange)
DO(BINDBUFFERBASE, BindBufferBase)
DO(TRANSFORMFEEDBACKVARYINGS, TransformFeedbackVaryings)
DO(GETTRANSFORMFEEDBACKVARYING, GetTransformFeedbackVarying)
DO(CLAMPCOLOR, ClampColor)
DO(BEGINCONDITIONALRENDER, BeginConditionalRender)
DO(ENDCONDITIONALRENDER, EndConditionalRender)
DO(VERTEXATTRIBIPOINTER, VertexAttribIPointer)
DO(GETVERTEXATTRIBIIV, GetVertexAttribIiv)
DO(GETVERTEXATTRIBIUIV, GetVertexAttribIuiv)
DO(VERTEXATTRIBI1I, VertexAttribI1i)
DO(VERTEXATTRIBI2I, VertexAttribI2i)
DO(VERTEXATTRIBI3I, VertexAttribI3i)
DO(VERTEXATTRIBI4I, VertexAttribI4i)
DO(VERTEXATTRIBI1UI, VertexAttribI1ui)
DO(VERTEXATTRIBI2UI, VertexAttribI2ui)
DO(VERTEXATTRIBI3UI, VertexAttribI3ui)
DO(VERTEXATTRIBI4UI, VertexAttribI4ui)
DO(VERTEXATTRIBI1IV, VertexAttribI1iv)
DO(VERTEXATTRIBI2IV, VertexAttribI2iv)
DO(VERTEXATTRIBI3IV, VertexAttribI3iv)
DO(VERTEXATTRIBI4IV, VertexAttribI4iv)
DO(VERTEXATTRIBI1UIV, VertexAttribI1uiv)
DO(VERTEXATTRIBI2UIV, VertexAttribI2uiv)
DO(VERTEXATTRIBI3UIV, VertexAttribI3uiv)
DO(VERTEXATTRIBI4UIV, VertexAttribI4uiv)
DO(VERTEXATTRIBI4BV, VertexAttribI4bv)
DO(VERTEXATTRIBI4SV, VertexAttribI4sv)
DO(VERTEXATTRIBI4UBV, VertexAttribI4ubv)
DO(VERTEXATTRIBI4USV, VertexAttribI4usv)
DO(GETUNIFORMUIV, GetUniformuiv)
DO(BINDFRAGDATALOCATION, BindFragDataLocation)
DO(GETFRAGDATALOCATION, GetFragDataLocation)
DO(UNIFORM1UI, Uniform1ui)
DO(UNIFORM2UI, Uniform2ui)
DO(UNIFORM3UI, Uniform3ui)
DO(UNIFORM4UI, Uniform4ui)
DO(UNIFORM1UIV, Uniform1uiv)
DO(UNIFORM2UIV, Uniform2uiv)
DO(UNIFORM3UIV, Uniform3uiv)
DO(UNIFORM4UIV, Uniform4uiv)
DO(TEXPARAMETERIIV, TexParameterIiv)
DO(TEXPARAMETERIUIV, TexParameterIuiv)
DO(GETTEXPARAMETERIIV, GetTexParameterIiv)
DO(GETTEXPARAMETERIUIV, GetTexParameterIuiv)
DO(CLEARBUFFERIV, ClearBufferiv)
DO(CLEARBUFFERUIV, ClearBufferuiv)
DO(CLEARBUFFERFV, ClearBufferfv)
DO(CLEARBUFFERFI, ClearBufferfi)
DO(ISRENDERBUFFER, IsRenderbuffer)
DO(BINDRENDERBUFFER, BindRenderbuffer)
DO(DELETERENDERBUFFERS, DeleteRenderbuffers)
DO(GENRENDERBUFFERS, GenRenderbuffers)
DO(RENDERBUFFERSTORAGE, RenderbufferStorage)
DO(GETRENDERBUFFERPARAMETERIV, GetRenderbufferParameteriv)
DO(ISFRAMEBUFFER, IsFramebuffer)
DO(BINDFRAMEBUFFER, BindFramebuffer)
DO(DELETEFRAMEBUFFERS, DeleteFramebuffers)
DO(GENFRAMEBUFFERS, GenFramebuffers)
DO(CHECKFRAMEBUFFERSTATUS, CheckFramebufferStatus)
DO(FRAMEBUFFERTEXTURE1D, FramebufferTexture1D)
DO(FRAMEBUFFERTEXTURE2D, FramebufferTexture2D)
DO(FRAMEBUFFERTEXTURE3D, FramebufferTexture3D)
DO(FRAMEBUFFERRENDERBUFFER, FramebufferRenderbuffer)
DO(GETFRAMEBUFFERATTACHMENTPARAMETERIV, GetFramebufferAttachmentParameteriv)
DO(GENERATEMIPMAP, GenerateMipmap)
DO(BLITFRAMEBUFFER, BlitFramebuffer)
DO(RENDERBUFFERSTORAGEMULTISAMPLE, RenderbufferStorageMultisample)
DO(FRAMEBUFFERTEXTURELAYER, FramebufferTextureLayer)
DO(FLUSHMAPPEDBUFFERRANGE, FlushMappedBufferRange)
DO(BINDVERTEXARRAY, BindVertexArray)
DO(DELETEVERTEXARRAYS, DeleteVertexArrays)
DO(GENVERTEXARRAYS, GenVertexArrays)
DO(ISVERTEXARRAY, IsVertexArray)

// GL_VERSION_3_1 extensions:
DO(DRAWARRAYSINSTANCED, DrawArraysInstanced)
DO(DRAWELEMENTSINSTANCED, DrawElementsInstanced)
DO(TEXBUFFER, TexBuffer)
DO(PRIMITIVERESTARTINDEX, PrimitiveRestartIndex)
DO(COPYBUFFERSUBDATA, CopyBufferSubData)
DO(GETUNIFORMINDICES, GetUniformIndices)
DO(GETACTIVEUNIFORMSIV, GetActiveUniformsiv)
DO(GETACTIVEUNIFORMNAME, GetActiveUniformName)
DO(GETUNIFORMBLOCKINDEX, GetUniformBlockIndex)
DO(GETACTIVEUNIFORMBLOCKIV, GetActiveUniformBlockiv)
DO(GETACTIVEUNIFORMBLOCKNAME, GetActiveUniformBlockName)
DO(UNIFORMBLOCKBINDING, UniformBlockBinding)

// GL_VERSION_3_2 extensions:
DO(DRAWELEMENTSBASEVERTEX, DrawElementsBaseVertex)
DO(DRAWRANGEELEMENTSBASEVERTEX, DrawRangeElementsBaseVertex)
DO(DRAWELEMENTSINSTANCEDBASEVERTEX, DrawElementsInstancedBaseVertex)
DO(MULTIDRAWELEMENTSBASEVERTEX, MultiDrawElementsBaseVertex)
DO(PROVOKINGVERTEX, ProvokingVertex)
DO(FENCESYNC, FenceSync)
DO(ISSYNC, IsSync)
DO(DELETESYNC, DeleteSync)
DO(CLIENTWAITSYNC, ClientWaitSync)
DO(WAITSYNC, WaitSync)
DO(GETINTEGER64V, GetInteger64v)
DO(GETSYNCIV, GetSynciv)
DO(GETINTEGER64I_V, GetInteger64i_v)
DO(GETBUFFERPARAMETERI64V, GetBufferParameteri64v)
DO(FRAMEBUFFERTEXTURE, FramebufferTexture)
DO(TEXIMAGE2DMULTISAMPLE, TexImage2DMultisample)
DO(TEXIMAGE3DMULTISAMPLE, TexImage3DMultisample)
DO(GETMULTISAMPLEFV, GetMultisamplefv)
DO(SAMPLEMASKI, SampleMaski)

#endif //GL_SHIMS_HPP
