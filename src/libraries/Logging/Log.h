#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "Utility.hpp"

enum class LogType{
  Info,
  Warning,
  Error,
  Critical
};
// Converts a LogType to a string.
std::string logTypeToString(LogType type) {
  if(type == LogType::Info){
    return "[Info]";
  }
  if(type == LogType::Warning){
    return "[Warning]";
  }
  if(type == LogType::Error){
    return "[Error]";
  }
  if(type == LogType::Critical){
    return "[Critical]";
  }
  return "";
}

struct LogMessage{
  std::time_t time;
  LogType type;
  std::string message;
};

//Writes the log message to a generic stream
template<class STREAM>
void writeLog(STREAM &stream, const LogMessage &lm){
  stream << put_time(&lm.time ,"%c")
    << ": " 
    <<  logTypeToString(lm.type) 
    << ": " << lm.message << std::endl;
}

auto writeLogToConsole = [](const LogMessage &lm){
  writeLog(std::cout,lm);
};
//Handles the logging, should not be used directly
struct Log{
  std::vector<LogMessage> logs;
  std::ofstream outputFile;
  Log(){
    using namespace std::chrono;
    auto time = system_clock::to_time_t(system_clock::now());
    auto date = put_time(&time , "%F");
    std::string path = "GeKo-"+date + ".log";
    //FIXME: Need default log location.
    outputFile.open(path);
  }
  ~Log(){
    outputFile.close();
  }
  void addMessage(LogType type, std::string msg){
    auto time = std::chrono::system_clock::now();
    auto lm = LogMessage{std::chrono::system_clock::to_time_t(time)
      ,type
      ,msg};
    logs.push_back(lm);
    //FIXME: Blocks the current thread
    writeLog(outputFile,lm);
  }
  void print(){
    for(const LogMessage &lm : logs ){
      writeLogToConsole(lm);
    }
  }
};


