#ifndef CPP_COURSE_TS_QUEUE_H
#define CPP_COURSE_TS_QUEUE_H

#include <queue>
#include <mutex>

template<typename T>
class queue_guard {
 public:
  bool empty();

  template <typename U>
  void push(U&& val);

  T pop();

 private:
  std::queue<T> q;
  std::mutex mtx;
};



template<typename T>
bool queue_guard<T>::empty() 
{
	std::lock_guard<std::mutex> guard(mtx);
	return q.empty();
}

template<typename T>
template<typename U>
void queue_guard<T>::push(U&& val)
{
	std::lock_guard<std::mutex> guard(mtx);
	q.push(std::forward<U>(val));
}

template<typename T>
T queue_guard<T>::pop()
{
	std::lock_guard<std::mutex> guard(mtx);
	if (q.empty()) {
	  return T();
	}
	auto item = q.front();
	q.pop();
	return item;
}

#endif //CPP_COURSE_TS_QUEUE_H
