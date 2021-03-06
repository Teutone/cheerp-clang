// RUN: %clang_cc1 -std=c++11 -S -emit-llvm -o %t-c++11.ll %s -triple x86_64-apple-darwin10 
// RUN: FileCheck %s < %t-c++11.ll
// RUN: %clang_cc1  -std=c++98 -S -emit-llvm -o %t.ll %s -triple x86_64-apple-darwin10 
// RUN: diff %t.ll  %t-c++11.ll

// rdar://12897704

struct sAFSearchPos {
    unsigned char *pos;
    unsigned char count;
};

static volatile struct sAFSearchPos testPositions;
// CHECK: @_ZL13testPositions = internal global %struct._Z12sAFSearchPos zeroinitializer

static volatile struct sAFSearchPos arrayPositions[100][10][5];
// CHECK: @_ZL14arrayPositions = internal global [100 x [10 x [5 x %struct._Z12sAFSearchPos]]] zeroinitializer

int main() {
  return testPositions.count + arrayPositions[10][4][3].count; 
}
