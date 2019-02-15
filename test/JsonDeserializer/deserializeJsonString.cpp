// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("Valid JSON strings value") {
  struct TestCase {
    const char* input;
    const char* expectedOutput;
  };

  TestCase testCases[] = {
      {"\"hello world\"", "hello world"},
      {"\'hello world\'", "hello world"},
      {"\"1\\\"2\\\\3\\/4\\b5\\f6\\n7\\r8\\t9\"", "1\"2\\3/4\b5\f6\n7\r8\t9"},
      {"'\\u0041'", "A"},
      {"'\\u00e4'", "\xc3\xa4"},      // ä
      {"'\\u00E4'", "\xc3\xa4"},      // ä
      {"'\\u3042'", "\xe3\x81\x82"},  // あ

  };
  const size_t testCount = sizeof(testCases) / sizeof(testCases[0]);

  DynamicJsonDocument doc(4096);

  for (size_t i = 0; i < testCount; i++) {
    const TestCase& testCase = testCases[i];
    CAPTURE(testCase.input);
    DeserializationError err = deserializeJson(doc, testCase.input);
    REQUIRE(err == DeserializationError::Ok);
    REQUIRE(doc.as<std::string>() == testCase.expectedOutput);
  }
}
