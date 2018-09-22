#include "lamia_timer.h"

namespace lamia {

LamiaTimer::LamiaTimer(void) {
  index_size_ = 0;
  _insertIndex(index_size_);
  eps_ = {
    {0, 1e0}, {1, 1e1}, {2, 1e2}, {3, 1e3}, {4, 1e4}, 
    {5, 1e5}, {6, 1e6}, {7, 1e7}, {8, 1e8}, {9, 1e9}, 
  };
}

LamiaTimer::~LamiaTimer(void) {
  clearAll();
  index_set_.clear();
  start_timespecs_.clear();
  stop_timespecs_.clear();
}

LamiaIndexDtype LamiaTimer::timerSize(void) const {
  return index_size_;
}

void LamiaTimer::start(LamiaIndexDtype index) {
  if(0 == index_set_.count(index)) {
    _insertIndex(index);
  }
  clock_gettime(CLOCK_MONOTONIC, start_timespecs_[index]);
}

void LamiaTimer::stop(LamiaIndexDtype index) {
  if(0 == index_set_.count(index)) {
    _insertIndex(index);
  }
  clock_gettime(CLOCK_MONOTONIC, stop_timespecs_[index]);
}

LamiaTimerCount LamiaTimer::secsByPow(LamiaIndexDtype eps, LamiaIndexDtype index) {
  return _collectTime(index, std::abs(eps));
}

LamiaTimerCount LamiaTimer::seconds(LamiaIndexDtype index) {
  return _collectTime(index, 0);
}

LamiaTimerCount LamiaTimer::millisecs(LamiaIndexDtype index) {
  return _collectTime(index, 3);
}

LamiaTimerCount LamiaTimer::microsecs(LamiaIndexDtype index) {
  return _collectTime(index, 6);
}

LamiaTimerCount LamiaTimer::nanosecs(LamiaIndexDtype index) {
  return _collectTime(index, 9);
}

void LamiaTimer::clear(LamiaIndexDtype index) {
  if(0 == index_set_.count(index)) return;
  _deleteIndex(index);
}

void LamiaTimer::clearAll(void) {
  for(auto &m: index_set_) clear(m);
}

LamiaTimerCount LamiaTimer::_collectTime(LamiaIndexDtype index, LamiaIndexDtype eps) {
  if(nullptr == stop_timespecs_[index] or nullptr == start_timespecs_[index]) {
  #ifdef _EXIST_BY_ERROR_
    throw "timer of index: " + std::to_string(index) + " is not created!\n";
  #else
    return -1.;
  #endif // ! _EXIST_BY_ERROR_
  }
  LamiaTimerCount t = \
     (stop_timespecs_[index]->tv_sec - \
     start_timespecs_[index]->tv_sec) * eps_[eps]+ \
     (stop_timespecs_[index]->tv_nsec - \
     start_timespecs_[index]->tv_nsec) / eps_[9-eps];
  return t;
}

void LamiaTimer::_insertIndex(LamiaIndexDtype index) {
  index_set_.insert(index);
  start_timespecs_[index] = new timespec;
  stop_timespecs_[index] = new timespec;
  ++index_size_;
}

void LamiaTimer::_deleteIndex(LamiaIndexDtype index) {
  index_set_.erase(index);
  delete start_timespecs_[index];
  start_timespecs_.erase(index);
  delete stop_timespecs_[index];
  stop_timespecs_.erase(index);
  --index_size_;
}

} // ! namespace lamia
