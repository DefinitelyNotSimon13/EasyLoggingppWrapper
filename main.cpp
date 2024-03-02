#include "LoggingWrapper.hpp"
#include "easylogging++.h"
#include <chrono>
#include <iostream>
#include <cstdio>

INITIALIZE_EASYLOGGINGPP

std::chrono::duration<double, std::milli> test1(int runs);
std::chrono::duration<double, std::milli> test2(int runs);
std::chrono::duration<double, std::milli> test3(int runs);
std::chrono::duration<double, std::milli> test4(int runs);
void setupEasylogging();

void removeFile() {
  std::remove("myeasylog.log");
}
const char* filename = "myeasylog.log";
int main() {
  setupEasylogging();
  std::chrono::duration<double, std::milli> duration;
  std::chrono::duration<double, std::milli> duration2;
  std::chrono::duration<double, std::milli> duration3;
  std::chrono::duration<double, std::milli> duration4;
  int runs = 1000000;
  for (int i = 0; i < 10; i++){
    removeFile();
    duration += test1(runs);
    if(i != 0){
      duration /= 2;
    }
    removeFile();
    duration2 += test2(runs);
    if(i != 0){
      duration2 /= 2;
    }
    removeFile();
    duration3 += test3(runs);
    if(i != 0){
      duration3 /= 2;
    }
    removeFile();
    duration4 += test4(runs);
    if(i != 0){
      duration4 /= 2;
    }
  }

  OUTPUT << "Execution std::cout: " << duration.count() << " miliseconds"
           << std::endl;
  OUTPUT << "Execution easylogging++: " << duration2.count() << " miliseconds"
           << std::endl;
  OUTPUT << "Execution cout and el: " << duration3.count() << " miliseconds"
           << std::endl;
  OUTPUT << "Execution wrapper: " << duration4.count() << " miliseconds"
           << std::endl;

  return 0;
}

std::chrono::duration<double, std::milli> test1(int runs) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < runs; i++) {
    std::cout << "std::cout - " << i << "\n";
  }
  auto end = std::chrono::high_resolution_clock::now();
  return end - start;
}

std::chrono::duration<double, std::milli> test2(int runs) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < runs; i++) {
    LOG(INFO) << "log - " << i;
  }
  auto end = std::chrono::high_resolution_clock::now();
  return end - start;
}

std::chrono::duration<double, std::milli> test3(int runs) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < runs; i++) {
    std::cout << "log and cout - " << i << "\n";
    LOG(INFO) << "log and cout -" << i;
  }
  auto end = std::chrono::high_resolution_clock::now();
  return end - start;
}

std::chrono::duration<double, std::milli> test4(int runs) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < runs; i++) {
    utils::log(true) << "wrapper - " << i << "\n";
  }
  auto end = std::chrono::high_resolution_clock::now();
  return end - start;
}

void setupEasylogging() {
  el::Configurations conf("easylogging.conf");
  el::Loggers::reconfigureAllLoggers(conf);
}
