#ifndef ASYNCLOG_HPP
#define ASYNCLOG_HPP

#include "_public.hpp"

using namespace lxybx;

/// @brief 日志级别
enum LogLevel {
	DEBUG = 0, //调试
	INFO = 1, //信息
	WARN = 2, //警告
	ERROR = 3, //错误
	START = 4, //开始
	END = 5, //结束
};

//将日志级别转换为字符串
extern std::string str_level(const LogLevel& loglevel);

/// @brief 【单例】异步日志
class AsyncLog {
private:
	std::ofstream _fout; //文件输出流
	std::string _filename; //日志文件名
	std::ios::openmode _openmode; //文件打开模式
	bool _b_filebuffer; //是否使用文件缓冲区
	bool _b_backup; //是否切换日志文件
	int _max_filesize; //日志文件最大大小

	std::queue<std::string> _task_queue; //任务队列
	std::mutex _task_mutex; //任务队列互斥锁
	std::condition_variable _task_cond; //任务队列条件变量
	std::atomic<bool> _b_exit; //退出标志

	std::thread _work_thread; //工作线程

	//禁用拷贝构造、赋值
	AsyncLog(const AsyncLog&) = delete;
	AsyncLog& operator=(const AsyncLog&) = delete;

	//构造函数：开启工作线程
	AsyncLog(const int max_filesize);
public:
	//获取单例
	static AsyncLog& GetInstance(const int max_filesize = 100);

	//打开文件
	bool open(const std::string& filename, const std::ios::openmode openmode = std::ios::out | std::ios::app, const bool b_backup = true, const bool b_filebuffer = false);

	//【生产者】添加任务
	template <typename ...Args>
	void write(const LogLevel loglevel, const char* fmt, Args... args);

	//析构函数：退出工作线程、关闭文件
	~AsyncLog();

#if 0
	//【禁用】通知退出
	void Stop();
#endif
private:
	//【消费者】工作线程
	void work_thread();

	//开启工作线程
	void start();

	//处理任务
	bool dispose_task(const std::string& task_str);

	//切换日志文件
	bool switch_file();
};


//【生产者】添加任务
template <typename... Args>
inline void AsyncLog::write(const LogLevel loglevel, const char *fmt, Args... args)
{
	//加锁、打包任务入队、解锁、通知
	std::unique_lock<std::mutex> ulk(_task_mutex);

	if (_b_exit) { return; }

	_task_queue.emplace("[" + curr_time_output() + "][" + str_level(loglevel) + "] " + str_format(fmt, args...));

	bool b_need_notify = (_task_queue.size() == 1) ? true : false;

	ulk.unlock();

	if (b_need_notify) {
		_task_cond.notify_one();
	}
}



#endif // ASYNCLOG_HPP
