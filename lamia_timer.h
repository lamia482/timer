/***************************
 > File: lamia_timer.h
 > Date: 2018/09/22
 > Author: lamia
 > Question: 实现Linux下计时(精确到纳秒)
 > Method: index为计时器编号，此类允许同时存在多个计时器，
           按index这个编号区分，start表示开始第index个的
           计时器开始计时，当该计时器不存在会新建一个，
           同理stop也接受index为参数，表示结束该编号的计时器，
           
           secsByPow：eps为幂，例：设该函数输出为A，eps为2，
                      index为0， 则表示第index个计时器对应的
                      时间为 A * 10^eps 秒，_collectTime同理
                      
           seconds, millisecs, microsecs, nanosecs 都接受index
                     为参数，分别输出对应计时器的计时时长，
                     单位分别为 秒，毫秒，微秒，纳秒
                     
           clear, clearAll 用于清理相应编号的计时器
           
           _EXIST_BY_ERROR_: 该宏定义存在时，当访问非法计时器
                     // 时（如不存在），会抛出异常，若不存在，
                     则返回计时-1表明计时器不存在
***************************/
#ifndef LAMIA_TIMER_H_
#define LAMIA_TIMER_H_
#include <bits/stdc++.h>
#include <time.h>

namespace lamia {

#define _EXIST_BY_ERROR_

typedef float LamiaTimerCount;
typedef int LamiaIndexDtype;

class LamiaTimer {
public:
  LamiaTimer(void);
  virtual ~LamiaTimer(void);
  virtual LamiaIndexDtype timerSize(void) const;
  virtual void start(LamiaIndexDtype index = 0);
  virtual void stop(LamiaIndexDtype index = 0);
  virtual LamiaTimerCount secsByPow(LamiaIndexDtype eps, LamiaIndexDtype index = 0);
  virtual LamiaTimerCount seconds(LamiaIndexDtype index = 0);
  virtual LamiaTimerCount millisecs(LamiaIndexDtype index = 0);
  virtual LamiaTimerCount microsecs(LamiaIndexDtype index = 0);
  virtual LamiaTimerCount nanosecs(LamiaIndexDtype index = 0);
  virtual void clear(LamiaIndexDtype index);
  virtual void clearAll(void);
protected:
  virtual void _insertIndex(LamiaIndexDtype index);
  virtual void _deleteIndex(LamiaIndexDtype index);
  virtual LamiaTimerCount _collectTime(LamiaIndexDtype index, LamiaIndexDtype eps);
private:
  LamiaIndexDtype index_size_;
  std::set<LamiaIndexDtype> index_set_;
  std::map<LamiaIndexDtype, timespec*> start_timespecs_, stop_timespecs_;
  std::map<LamiaIndexDtype, LamiaTimerCount> eps_;
};

} // ! namespace lamia
#endif // ! LAMIA_TIMER_H_
