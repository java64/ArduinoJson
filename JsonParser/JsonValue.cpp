/*
 * Arduino JSON library
 * Benoit Blanchon 2014 - MIT License
 */

#include <stdlib.h> // for strtol, strtod
#include "JsonArray.h"
#include "JsonObject.h"
#include "JsonValue.h"

using namespace ArduinoJson::Parser;
using namespace ArduinoJson::Internal;

JsonValue JsonValue::operator[](int index)
{
    return JsonArray(json, token)[index];
}

JsonValue JsonValue::operator[](const char* key)
{
    return JsonObject(json, token)[key];
}

JsonValue::operator bool()
{
    if (!token.isPrimitive()) return 0;

    char *text = token.getText(json);

    // "true"
    if (text[0] == 't') return true;

    // "false"
    if (text[0] == 'f') return false;

    // "null"
    if (text[0] == 'n') return false;

    // number
    return strtol(text, 0, 0) != 0;
}

JsonValue::operator double()
{
    return token.isPrimitive() ? strtod(token.getText(json), 0) : 0;
}

JsonValue::operator long()
{
    return token.isPrimitive() ? strtol(token.getText(json), 0, 0) : 0;
}

JsonValue::operator char*()
{
    return token.isString() || token.isPrimitive() ? token.getText(json) : 0;
}

JsonValue::operator JsonArray()
{
    return token.isArray()
        ? JsonArray(json, token)
        : JsonArray::null();
}

JsonValue::operator JsonObject()
{
    return token.isObject()
        ? JsonObject(json, token)
        : JsonObject::null();
}