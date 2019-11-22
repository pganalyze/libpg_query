const char* tests[] = {
  "SELECT 1",
  "[{\"RawStmt\": {\"stmt\": {\"SelectStmt\": {\"targetList\": [{\"ResTarget\": {\"val\": {\"A_Const\": {\"val\": {\"Integer\": {\"ival\": 1}}, \"location\": 7}}, \"location\": 7}}], \"op\": 0}}}}]"
};

size_t testsLength = __LINE__ - 4;
