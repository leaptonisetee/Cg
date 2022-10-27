// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers.
#endif

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "include/components/collider.h"
#include "include/components/fpsCounter.h"
#include "include/components/mesh.h"
#include "include/components/scene.h"
#include "include/camera.h"
#include "include/colors.h"
#include "include/component.h"
#include "include/delegates.h"
#include "include/game.h"
#include "include/input.h"
#include "include/keys.h"
#include "include/material.h"
#include "include/mesh.h"
#include "include/render.h"
#include "include/shader.h"
#include "include/shapes.h"
#include "include/timer.h"
#include "include/transform.h"
#include "include/utils.h"
#include "include/window.h"

#endif //PCH_H
