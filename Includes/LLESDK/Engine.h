#ifndef LUNALUXENGINE_GAMEENGINE_H
#define LUNALUXENGINE_GAMEENGINE_H
#include <LLESDK/types.h>
#include <render/Buffer.h>
#include <render/Shader.h>
#include <render/Renderer.h>
#include <fs/Reader.h>
#define PUSHTOENGINE(vertexbuffer,indexbuffer,shader)\
LunaLuxEngine::Renderer::get().pushDataToRenderer(vertexbuffer, indexbuffer, shader);
#endif