//////////////////////////////////////////////////////////////////////////////
//
//    API.CPP
//
//    Copyright © 2006, Rehno Lindeque. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////////
/*                               DOCUMENTATION                              */
/*
    DESCRIPTION:
      Defines common basic types for use in OpenRE backends.

    TODO:
      Move common data to BaseRE (e.g. globals)
      + NB! Remove GLU dependency
      + Create an API abstraction layer in BaseRE
*/
/*                              COMPILER MACROS                             */
#pragma warning(push)
#pragma warning(disable:4311)
#pragma warning(disable:4312)

/*                                 INCLUDES                                 */
// Windows
#ifdef _WIN32
  #include <windows.h>
#endif

// OpenGL
#include <GL/GLee.h>
#include <GL/gl.h>
#include <GL/glu.h> // (temporary)

//
#include "api.h"

using namespace BaseRE;
using namespace GlRasRE;
/*                                  GLOBALS                                 */
#ifdef _WIN32
  stack<HDC> deviceContexts; // Windows
  stack<HGLRC> renderContexts; // OpenGL
  HDC oldHDC = null;
  HGLRC oldHRC = null;
  HWND hwnd;
#endif
RE_DISPLAY_MODE displayMode = RE_TEMPORARY;
//old: Quads quads;

/*                               IMPLEMENTATION                             */

REid reBeginScene()
{
  //if(activeComposite.top()) return null; // error
  if(state.top() != GLOBAL)
    return (REid)null; //error
  state.push(SCENE_COMPOSITE);
  //DEPRICATED: GlRasScene* scene = createObject<GlRasScene>();
  GlRasScene* scene = beginObject<GlRasScene>();
  activeScene = scene;
  activeComposites.push(scene);
  return (REid)scene;
}

void reEndScene()
{
  if(state.top() != SCENE_COMPOSITE)
    return; // error

  //todo : scene.build ??
  GlRasScene* scene = (GlRasScene*)activeComposites.top();
  scene->build();
  endObject<GlRasScene>();
  state.pop();
  activeComposites.pop();
}

/*void reDelScene(REid scene)
{
  if(state.top() != GLOBAL)
    return; //error

  // todo: check type id
  delete (Scene*)scene;
}*/

// frame
REid reBeginFrame()
{
  //DEPRICATED GlRasFrame* frame = createObject<GlRasFrame>();
  GlRasFrame* frame = beginObject<GlRasFrame>();
  activeComposites.push(frame);
  state.push(FRAME_COMPOSITE);
  return (REid)frame;
}

void reEndFrame()
{
  if(state.top() != FRAME_COMPOSITE)
    return; // error

  GlRasFrame* frame = (GlRasFrame*)activeComposites.top();
  frame->build();
  endObject<GlRasFrame>();
  state.pop();
  activeComposites.pop();
}

/*void reDelFrame(REid frame)
{
  if(state.top() != GLOBAL)
    return; //error

  // todo: check type id
  delete (Frame*)frame;
}*/

// frame parameters
void reTranslate(float x, float y, float z)
{
  //todo
}

// elements
REuint reGetElementsLength(REid elements)
{
  return ((GlRasElements*)elements)->getStream()->getLength();
}

REid reElements(RE_BASIC_TYPE type, REuint nElements, void* elements)
{
  GlRasElements* elementsObject = beginObject<GlRasElements>();
  elementsObject->create(type, nElements);
  elementsObject->setElements(elements);
  return (REid)elementsObject;
}

REid reBeginElements(RE_BASIC_TYPE type, REuint nElements)
{
  GlRasElements* elements = beginObject<GlRasElements>();
  elements->create(type, nElements);
  return (REid)elements;
}

void reEndElements()
{
  GlRasElements* elements = (GlRasElements*)activeObjects.top();
  elements->build();
  endObject<GlRasElements>();
}

void reElement(void* element)
{
  GlRasElements* elements = (GlRasElements*)activeObjects.top();
  elements->addElement(element);
}

void reElementf(REfloat element)
{
  GlRasElements* elements = (GlRasElements*)activeObjects.top();
  elements->addElement(&element);
}

void reElement2f(REfloat val1, REfloat val2)
{
  GlRasElements* elements = (GlRasElements*)activeObjects.top();
  float element[] = { val1, val2 };
  elements->addElement(element);
}
void reElement3f(REfloat, REfloat, REfloat)
{
  //todo
}
void reElement4f(REfloat, REfloat, REfloat, REfloat)
{
  //todo
}

void reElementd(REdouble)
{
  //todo
}
void reElement2d(REdouble, REdouble)
{
  //todo
}
void reElement3d(REdouble, REdouble, REdouble)
{
  //todo
}
void reElement4d(REdouble, REdouble, REdouble, REdouble)
{
  //todo
}

void reElementui8(REuint8)
{
  //todo
}
void reElement2ui8(REuint8, REuint8)
{
  //todo
}
void reElement3ui8(REuint8, REuint8, REuint8)
{
  //todo
}
void reElement4ui8(REuint8, REuint8, REuint8, REuint8)
{
  //todo
}

void reElementi8(REint8)
{
  //todo
}
void reElement2i8(REint8, REint8)
{
  //todo
}
void reElement3i8(REint8, REint8, REint8)
{
  //todo
}
void reElement4i8(REint8, REint8, REint8, REint8)
{
  //todo
}

void reElementui16(REuint16)
{
  //todo
}
void reElement2ui16(REuint16, REuint16)
{
  //todo
}
void reElement3ui16(REuint16, REuint16, REuint16)
{
  //todo
}
void reElement4ui16(REuint16, REuint16, REuint16, REuint16)
{
  //todo
}

void reElementi16(REint16)
{
  //todo
}
void reElement2i16(REint16, REint16)
{
  //todo
}
void reElement3i16(REint16, REint16, REint16)
{
  //todo
}
void reElement4i16(REint16, REint16, REint16, REint16)
{
  //todo
}

void reElementui32(REuint32)
{
  //todo
}
void reElement2ui32(REuint32, REuint32)
{
  //todo
}
void reElement3ui32(REuint32, REuint32, REuint32)
{
  //todo
}
void reElement4ui32(REuint32, REuint32, REuint32, REuint32)
{
  //todo
}

void reElementi32(REint32)
{
  //todo
}
void reElement2i32(REint32, REint32)
{
  //todo
}
void reElement3i32(REint32, REint32, REint32)
{
  //todo
}
void reElement4i32(REint32, REint32, REint32, REint32)
{
  //todo
}

void reElementui64(REuint64)
{
  //todo
}
void reElement2ui64(REuint64, REuint64)
{
  //todo
}
void reElement3ui64(REuint64, REuint64, REuint64)
{
  //todo
}
void reElement4ui64(REuint64, REuint64, REuint64, REuint64)
{
  //todo
}

void reElementi64(REint64)
{
  //todo
}
void reElement2i64(REint64, REint64)
{
  //todo
}
void reElement3i64(REint64, REint64, REint64)
{
  //todo
}
void reElement4i64(REint64, REint64, REint64, REint64)
{
  //todo
}

/* geometry */
REid reBeginGeometry(RE_GEOMETRY type)
{
  Geometry* geometry;
  switch(type)
  {
  case RE_MESH_GEOMETRY:
    geometry = beginGeometry<GlRasMesh>();
    break;
  default:
    //todo: error
    break;
  }
  activeScene->geometry.push_back(geometry);
  return (REid)geometry;
}
void reEndGeometry()
{
  ((GlRasMesh*)activeGeometry)->build();
  endGeometry<GlRasMesh>();
}

/* mesh geometry */
REid reBeginPoints(REuint nPoints)
{
  return (REid)beginComponent<Points>();
}
void reEndPoints()
{
  endComponent<Points>();
}

REid reBeginVertices(REuint nVertices)
{
  return (REid)beginComponent<Vertices>();
}

void reEndVertices()
{
  endComponent<Vertices>();
}

REid reBeginEdges(REuint nEdges)
{
  return (REid)beginComponent<Edges>();
}

void reEndEdges()
{
  endComponent<Edges>();
}

REid reBeginPrimitives(REuint nPrimitives)
{
  return (REid)beginComponent<Primitives>();
}

void reEndPrimitives()
{
  endComponent<Primitives>();
}
REid reBeginMap()
{
  return (REid)beginComponent<Map>();
}
void reEndMap()
{
  endComponent<Map>();
}

//todo: void reAttribute(RE_ATTRIBUTE attribute, void* attribute);
void reAttributes(RE_ATTRIBUTE attribute, REid elements)
{
  if(activeComponent == null)
    return;
  activeComponent->addAttributes(attribute, elements);
}

void reBeginTriangles()
{
  //todo
}

void reEndTriangles()
{
  //todo
}

void reBeginQuads()
{
  //todo
}

void reEndQuads()
{
  //todo
}

void rePoints(REid points, REuint offset, REuint length)
{
  // HERE LAST: A construct is triangles, quads, polygons, lines, points etc.
  //todo: ((Construct*)((Mesh*)activeGeometry)->constructs.top())->points = points;
  ((Mesh*)activeGeometry)->points = (Points*)points;
}

void reVertices(REid vertices, REuint offset, REuint length)
{
  ((Mesh*)activeGeometry)->vertices = (Vertices*)vertices;
}

void reEdges(REid edges, REuint offset, REuint length)
{
  ((Mesh*)activeGeometry)->edges = (Edges*)edges;
}

void rePrimitives(REid primitives, REuint offset, REuint length)
{
  ((Mesh*)activeGeometry)->primitives = (Primitives*)primitives;
}

void reMap(REid map)
{
  ((Mesh*)activeGeometry)->map = (Map*)map;
}

// triangles
//void reBeginTriangle()
//{
//}
//void reEndTriangle()
//{
//}
//void reBeginTriangles(REuint ntriangles)
//{
//}
//void reEndTriangles()
//{
//}
//void reBeginQuad()
//{
//}
//void reEndQuad()
//{
//}
//void reBeginQuads(REuint nquads)
//{
//  quads.clear();
//  quads.nQuads = nquads;
//  state.push(QUADS_OBJECT);
//}
//void reEndQuads()
//{
//  if(state.top() != QUADS_OBJECT)
//    return; // error
//
//  if(quads.vertices == null)
//    return; // error
//  activeComposite.top()->addQuads(quads);
//
//  state.pop();
//}

// geometric parameters
/*void reVertexV(REfloat* vertex)
{
}

void reVerticesV(REfloat* vertices, REuint nVertices, REuint vertexStride)
{
  switch(state.top())
  {
  case QUADS_OBJECT:
    quads.vertices = vertices;
    if(nVertices == 0)
      quads.nVertices = quads.nQuads * 4;
    else
      quads.nVertices = nVertices;
    if(vertexStride == 0)
      quads.vertexStride = 3*sizeof(REfloat);
    else
      quads.vertexStride = vertexStride;
    break;
  }
}

void reIndex(REuint16 index)
{
}

void reIndicesV(REuint16* indices, REuint indexStride)
{
  switch(state.top())
  {
  case QUADS_OBJECT:
    quads.indices = indices;
    if(indexStride == 0)
      quads.indexStride = sizeof(REuint16);
    else
      quads.indexStride = indexStride;
    break;
  }
}*/
/*
void reColorV(REfloat* color)
{
}

void reColorP(REfloat* color)
{
}
void reColorsV(REfloat* color, REuint vertexStride, REuint primitiveStride)
{
}
void reColorsP(REfloat* color, REuint primitiveStride)
{
}
void reNormalV(REfloat* normal)
{
}
void reNormalP(REfloat* normal)
{
}
void reNormalsV(REfloat* normals, REuint vertexStride, REuint primitiveStride)
{
}
void reNormalsP(REfloat* normals, REuint primitiveStride)
{
}
*/

REid reBeginCamera(bool referenceFrame)
{
  Camera* camera;
  if(referenceFrame)
  {
    REid frame = reBeginFrame();
    //DEPRICATED: camera = createObject<Camera>();
    camera = beginObject<Camera>();
    camera->frame = frame;
  }
  else
  {
    //DEPRICATED: camera = createObject<Camera>();
    camera = beginObject<Camera>();
    Composite* composite = activeComposites.top();
    while(composite)
    {
      if(composite->type == FRAME)
      {
        camera->frame = (REid)(Frame*)composite;
        break;
      }
      composite = composite->parent;
    }
  }
  camera->referenceFrame = referenceFrame;
  return (REid)camera;
}

void reEndCamera()
{
  Camera* camera = (Camera*)activeObjects.top();
  endObject<Camera>();
  if(camera->referenceFrame)
    reEndFrame();
}

REid reBeginRender(RE_RENDER_TARGET renderTarget, REid scene)
{
  //Depricated: Render* render = createObject<Render>();
  Render* render = beginObject<Render>();
  render->scene = (Scene*)scene;
  switch(displayMode)
  {
  case RE_TEMPORARY:
    break;
  case RE_PERSISTENT:
    break;
  case RE_INCREMENTAL:
    break;
  }
  // todo?

  /* Depricated? state.push(RENDER); */
  return (REid)render;
}

void reEndRender()
{
  /* Depricated?
  if(state.top() != RENDER)
    return; // error
  state.pop();*/
  endObject<Render>();
}

void reCamera(REid camera)
{
  /* Depricated?
  if(state.top() != RENDER)
    return;*/
  if(activeObjects.top()->type != RENDER)
    return; //error
  ((Render*)activeObjects.top())->camera = (Camera*)camera;
}

void reParameter(RE_PARAMETER type, REid param)
{
  /*DEPRICATED:
  if(activeObject.top()->type != RENDER)
    return; //error
  */
  //todo
  //((Render*)activeObjects.top())->setParameter();
}

void reQuality(RE_PARAMETER type, REid param, float quality)
{
  /*DEPRICATED:
  if(activeObjects.top()->type != RENDER)
    return; //error
  */
  //todo
  //((Render*)activeObjects.top())->setParameter();
}

void reParameterQuality(RE_PARAMETER type, REid param, REint quality)
{
  /*DEPRICATED:
  if(activeObjects.top()->type != RENDER)
    return; //error
  */
  //todo
  //((Render*)activeObjects.top())->setParameter();
}

void reParameterQuality(RE_PARAMETER type, REid param, float quality)
{
  /*DEPRICATED:
  if(activeObject.top()->type != RENDER)
    return; //error
  */
  //todo
  //((Render*)activeObject.top())->setParameter();
}

const REParameterInfo* reGetParameters(RE_PARAMETER type, int& num)
{
  switch(type)
  {
  case RE_GLOBAL_ILLUMINATION:
    num = sizeof(globalIlluminationInfo) / sizeof(globalIlluminationInfo[0]);
    return globalIlluminationInfo;
  case RE_LOCAL_ILLUMINATION:
    //todo
    num = 0;
    return null;
  default:
    num = 0;
    return null; //error
  }
}

const RESettingInfo* reGetParameterQualitySettings(RE_PARAMETER type, REid param, int& num)
{
  switch(type)
  {
  case RE_GLOBAL_ILLUMINATION:
    switch(param)
    {
    case RE_AMBIENT_OCCLUSION:
      num = sizeof(ambientOcclusionQualityInfo) / sizeof(ambientOcclusionQualityInfo[0]);
      return ambientOcclusionQualityInfo;
    default:
      num = 0;
      return null; //error
    }
  case RE_LOCAL_ILLUMINATION:
    //todo
    num = 0;
    return null;
  default:
    num = 0;
    return null; //error
  }
}

void reRender(REid render)
{
  // initialize variables
  Render* r = (Render*)render;
  if(r == null)
    return; //error
  if(r->scene == null)
    return; //error
  GlRasScene& scene = *(GlRasScene*)r->scene;

  //todo: scene.background.render()
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // temporary: render everything in white
  glColor3f(1.0f, 1.0f, 1.0f);

  // set up window
  {
    glViewport(0, 0, 800, 600);
  }

  //todo: set up camera
  {
    glMatrixMode(GL_PROJECTION);
    if(r->camera)
    //if(false)
    {
      Matrix4 transformation;
      r->camera->getTransform(transformation);
      glLoadMatrixf(transformation);
    }
    else
    {
      //TEMP:
      glLoadIdentity();
      gluPerspective(45.0f, 800.0f/600.0f,0.1f,100.0f); // todo: replace with custom function
      //todo: set backplane to world max and front plane to geom closest to camera??? (This will allow best z-buffer precision)

      /*float rotX, rotY, rotZ;
      camera.rotation.get(rotX, rotY, rotZ);
      glRotatef(-rotX*180.0/PI, 1.0f, 0.0f, 0.0f);
      glRotatef(-rotY*180.0/PI, 0.0f, 1.0f, 0.0f);
      glRotatef(-rotZ*180.0/PI, 0.0f, 0.0f, 1.0f);*/

      /*float locX, locY, locZ;
      camera.location.get(locX, locY, locZ);
      glTranslatef(-locX, -locY, -locZ);*/
      glTranslatef(0.0f, -0.0f, -20.0f);
    }
  }

  // todo: set up world
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //// render test quad
  //{
  //  glColor3f(0.5f, 0.5f, 0.5f);
  //  glBegin(GL_QUADS);
  //    glVertex3f(-1.0f, 1.0f, 0.0f);
  //    glVertex3f( 1.0f, 1.0f, 0.0f);
  //    glVertex3f( 1.0f,-1.0f, 0.0f);
  //    glVertex3f(-1.0f,-1.0f, 0.0f);
  //  glEnd();
  //  glColor3f(1.0f, 1.0f, 1.0f);
  //}

  // render scene
  {
    // enable render options
    glEnable(GL_DEPTH_TEST);

    // clear background & zbuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  // old: precalculate ambient occlusion data (now done in endscene)
  for(list<Geometry*>::iterator i = scene.geometry.begin(); i != scene.geometry.end(); ++i)
  {
    // initialize variables
    if((*i)->type != MESH_GEOMETRY)
      continue;
    Mesh& geometry          = *(Mesh*)*i;
    Points* points          = geometry.points;
    Vertices* vertices      = geometry.vertices;
    Edges* edges            = geometry.edges;
    Primitives* primitives  = geometry.primitives;
    Map* map                = geometry.map;

    if(vertices == null)
      continue; // error - no vertices

    // retrieve attributes
    GlRasElements* locationElements = null,
                 * indexElements = null,
                 * normAreaElements = null;
    GlStream* vertexStream = null,
            * indexStream = null,
            * normAreaStream = null;

    if(points)
      locationElements = (GlRasElements*)points->getAttributes(RE_LOCATION);

    if(locationElements != null)
    {
      indexElements = (GlRasElements*)vertices->getAttributes(RE_INDEX);
      normAreaElements = (GlRasElements*)vertices->getAttributes(RE_EXT_BENT_NORMAL_AREA);
    }
    else
    {
      locationElements = (GlRasElements*)vertices->getAttributes(RE_LOCATION);
      if(locationElements == null)
        return; //error
      normAreaElements = (GlRasElements*)vertices->getAttributes(RE_EXT_BENT_NORMAL_AREA);
      indexElements = null;
    }

    vertexStream = locationElements->getStream();
    if(indexElements)
      indexStream = indexElements->getStream();
    if(normAreaElements)
      normAreaStream = normAreaElements->getStream();

    // calculate ambient occlusion
    GlStream occlusionStream;
    if(normAreaStream)
    {
      // create occlusion stream (one occlusion value per vertex)
      occlusionStream.create(vertexStream->getLength(), VEC4_FLOAT16_STREAM, null); //FLOAT16_STREAM?

      // create (& bind) occlusion kernel
      GlKernel kernel;
      kernel.build(fsCalculateDiscOcclusion1Pass, vsTexCoord1);
      kernel.bind();

      // set kernel parameters
      kernel.setUniform1i("vertices", 0);
      kernel.setUniform1i("normDiscs", 1);
      kernel.setUniform1f("nEmitters", (float)vertexStream->getLength());

      // bind vertices, vertex normals & disc area
      vertexStream->bindTexture(0);
      normAreaStream->bindTexture(1);

      // create & bind render target
      GlRenderTarget renderTarget;
      renderTarget.create();
      renderTarget.bind();

      // bind occlusion values as output
      occlusionStream.bindOutput(0);

      // execute kernel
      kernel.execute();

      // unbind occlusion values from output
      occlusionStream.unbindOutput(0);

      // unbind & destroy render target
      renderTarget.unbind();
      renderTarget.destroy();

      // unbind discs and vertices
      normAreaStream->unbindTexture(1);
      vertexStream->unbindTexture(0);

      // destroy kernel
      //GlKernel::restoreFixedFunction();
      kernel.unbind();
      kernel.destroy();
    }

    // render scene geometry
    {
      // temporary: disable textures (shouldn't be needed once shaders are used)
      glActiveTexture(GL_TEXTURE1);
      glDisable(GL_TEXTURE_2D);
      glActiveTexture(GL_TEXTURE0);
      glDisable(GL_TEXTURE_2D);
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

      // create (& bind) shader program
      GlShader shader;
      uint occlusionAttributeIndex = 0;
      if(normAreaStream)
      {
        shader.build(fsRenderAO, vsRenderAO);
        shader.bind();

        // get shader parameters
        occlusionAttributeIndex = shader.getAttribute("occlusion");
      }

      // bind vertices
      GLuint VBO = vertexStream->bindVertexBuffer();
      glVertexPointer(3, GL_FLOAT, 0, (char*)null);
      glEnableClientState(GL_VERTEX_ARRAY);

      // bind normals
      /* todo:
      GLuint NBO = normalStream->bindVertexBuffer();
      glNormalPointer(GL_FLOAT, 0, (char*)null);
      glEnableClientState(GL_NORMAL_ARRAY);*/

      // bind occlusion values
      if(normAreaStream)
      {
        GLuint ABO = occlusionStream.bindVertexAttributeBuffer();
        glVertexAttribPointer(occlusionAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, (char*)null);
        glEnableVertexAttribArray(occlusionAttributeIndex);
      }

      // bind indices
      GLuint IBO = indexStream->bindIndexBuffer();

      //todo: is this correct??
      /*NOT SUPPORTED BY OPENGL: if(indexStream->getInternElementSize() == 4)
        glIndexPointer(GL_UNSIGNED_INT, 0, (char*)null);
      else*/
      glIndexPointer(GL_UNSIGNED_SHORT, 0, (char*)null);

      glEnableClientState(GL_INDEX_ARRAY);

      //enable lighting (temporary)
      {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        float pos[4] = { 4.0, 4.0, 5.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
      }

      // draw triangles
      /*NOT SUPPORTED BY OPENGL: if(indexStream->getInternElementSize() == 4)
        glDrawElements(GL_TRIANGLES, indexStream->getLength(), GL_UNSIGNED_INT, null);
      else*/
      glDrawElements(GL_TRIANGLES, indexStream->getLength(), GL_UNSIGNED_SHORT, null);
      //glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_SHORT, null);

      // unbind buffers
      if(normAreaStream)
        glDisableVertexAttribArray(occlusionAttributeIndex);
      //todo: glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_INDEX_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
      if(normAreaStream)
        occlusionStream.unbindVertexAttributeBuffer();
      indexStream->unbindIndexBuffer();
      vertexStream->unbindVertexBuffer();

      // unbind shader program
      if(normAreaStream)
      {
        shader.unbind();
        shader.destroy();
      }
    }
  }

  // disable render options
  {
      glEnable(GL_DEPTH_TEST);
  }

  /*Old: GlStream occlusionStream;
  {
    // create occlusion stream (one occlusion value per vertex)
    occlusionStream.create(scene.geometry.vertexStream.getLength(), VEC4_FLOAT16_STREAM, null); //FLOAT16_STREAM?

    // create (& bind) occlusion kernel
    GlKernel kernel;
    kernel.build(fsCalculateDiscOcclusion1Pass, vsTexCoord1);
    kernel.bind();

    // set kernel parameters
    kernel.setUniform1i("vertices", 0);
    kernel.setUniform1i("normDiscs", 1);
    kernel.setUniform1f("nEmitters", (float)scene.geometry.vertexStream.getLength());

    // bind vertices, vertex normals & disc area
    scene.geometry.vertexStream.bindTexture(0);
    scene.geometry.normDiscStream.bindTexture(1);

    // create & bind render target
    GlRenderTarget renderTarget;
    renderTarget.create();
    renderTarget.bind();

    // bind occlusion values as output
    occlusionStream.bindOutput(0);

    // execute kernel
    kernel.execute();

    // unbind occlusion values from output
    occlusionStream.unbindOutput(0);

    // unbind & destroy render target
    renderTarget.unbind();
    renderTarget.destroy();

    // unbind discs and vertices
    scene.geometry.normDiscStream.unbindTexture(1);
    scene.geometry.vertexStream.unbindTexture(0);

    // destroy kernel
    //GlKernel::restoreFixedFunction();
    kernel.unbind();
    kernel.destroy();
  }*/



  // Debug: Render streams
  /*{
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 800, 600);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0f, -1.0f, 0.0f);
    glScalef(2.0f, 2.0f, 0.0f);

    float vertices[] = { 0.0f, 1.0f,
                         1.0f, 1.0f,
                         1.0f, 0.0f,
                         0.0f, 0.0f };
    float texcoords[] = { 0.0f, 0.0f,
                          1.0f, 0.0f,
                          1.0f, 1.0f,
                          0.0f, 1.0f };

    //scene.geometry.vertexStream.bindTexture(0);
    //scene.geometry.normDiscStream.bindTexture(0);
    occlusionStream.bindTexture(0);
    //temp:
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    // restore transform
    glPopMatrix();
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_MODELVIEW);
  }*/
}

// misc
void reDebugRender(REid object, REuint flag)
{
  //todo
}

void reInit()
{
  GLeeInit();

  // Set up texture viewport
  glViewport(0, 0, 512, 512);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glTranslatef(-1.0f, -1.0f, 0.0f);
  glScalef(2.0f, 2.0f, 0.0f);

  // OpenGL Rendering Quality Hints
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glHint(GL_FOG_HINT, GL_NICEST);
  glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
  glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);
  //glHint(GL_TEXTURE_COMPRESSION_HINT, ?? (GL_FASTEST\GL_DONT_CARE\GL_NICEST));

  glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
	//?? glEnable(GL_CULL_FACE);
  //glDisable(GL_CULL_FACE); //??

  state.push(GLOBAL);
  activeComposites.push(null);
}

void reShutdown()
{
 /* triangleStream.destroy();*/

  // Restore previous OpenGL Render Contex and GDI Device Context (needed?)
  wglMakeCurrent(oldHDC, oldHRC);

  // Destroy all other contexts
  while(!renderContexts.empty())
  {
    wglDeleteContext(renderContexts.top());
    renderContexts.pop();
  }
  while(!renderContexts.empty())
  {
    ReleaseDC(hwnd, deviceContexts.top());
    deviceContexts.pop();
  }
}

void reDisplayMode(RE_DISPLAY_MODE displayMode)
{
  ::displayMode = displayMode;
}

void reDisplay()
{
  //temp: show generated rays
  //glBindTexture(GL_TEXTURE_2D, rayStream.getHandle());
  //glBindTexture(GL_TEXTURE_2D, triangleStream.getHandle());
/*  glBindTexture(GL_TEXTURE_2D, displayStream.getHandle());
  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
  glEnd();  */

  switch(displayMode)
  {
  case RE_TEMPORARY:
    // Swap display buffers
    if(deviceContexts.empty())
      return; //error
    SwapBuffers(deviceContexts.top());
    break;
  case RE_INCREMENTAL:
  case RE_PERSISTENT:
    // Swap display buffers
    if(deviceContexts.empty())
      return; //error
//  glCopyPixels(x,y,50, 50, GL
    SwapBuffers(deviceContexts.top());
    break;
  }
}

REid reCopyRenderContext(REid originalRC)
{
  /*todo

  // Store the original contexts
  oldHRC = wglGetCurrentContext();
  OldHDC = wglGetCurrentDC();

  // Assume that the old RC was the same type as the current
  todo: wglCopyContext(HGLRC, HGLRC, UINT)
  */
  return (REid)null;
}

void reBackgroundColor(REfloat* color)
{
  //todo
}

void reDelObject(REid object)
{
  if(state.top() != GLOBAL)
    return; //error
  delObject((Object*)object);
}

void reInstance(REid object)
{

}

#ifdef _WIN32
RErc wreCreateRenderContext(HWND hwnd)
{
  /* PFD_SWAP_EXCHANGE flag alows the back buffer to be swapped rather than copied
     Also, this is important for SLI cards (see GPU_Programming_Guide.pdf by nvidia) */

  // Store the original contexts (needed?)
  oldHRC = wglGetCurrentContext();
  oldHDC = wglGetCurrentDC();
  ::hwnd = hwnd;

  // Get & store the window's Device Context
  HDC hDC = ::GetDC(hwnd);
  if(!hDC)
    return null;
  deviceContexts.push(hDC);

  // Set up an appropriate pixel format
  int pixelFormat;
  static PIXELFORMATDESCRIPTOR PFD =
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
    PFD_SUPPORT_OPENGL |
    PFD_SWAP_EXCHANGE | //PFD_SWAP_COPY
    PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32,
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    16,
    0,
    0,
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
  };

  if(!(pixelFormat = ChoosePixelFormat(hDC, &PFD)))
  {
    ReleaseDC(hwnd, hDC);
    deviceContexts.pop();
    return null;
  }
  if(!SetPixelFormat(hDC, pixelFormat, &PFD))
  {
    ReleaseDC(hwnd, hDC);
    deviceContexts.pop();
    return null;
  }

  // Set up an appropriate pixel format

  HGLRC hRC;
  if(!(hRC = wglCreateContext(hDC)))
  {
    ReleaseDC(hwnd, hDC);
    deviceContexts.pop();
    return null;
  }
  if(!(wglMakeCurrent(hDC, hRC)))
  {
    wglMakeCurrent(oldHDC, oldHRC);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
    deviceContexts.pop();
    return null;
  }
  renderContexts.push(hRC);
  return (RErc)hRC;
}
#endif

/*                              COMPILER MACROS                             */
#pragma warning(pop)
